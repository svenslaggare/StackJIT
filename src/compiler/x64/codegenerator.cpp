#include "../../type/type.h"
#include "../../vmstate.h"
#include "../../runtime/runtime.h"
#include "../../core/instruction.h"
#include "exceptions.h"
#include "../../stackjit.h"
#include "../../helpers.h"
#include "../callingconvention.h"
#include "../../core/functionsignature.h"
#include "amd64assembler.h"
#include <string.h>
#include <iostream>

namespace stackjit {
	namespace {
		//Returns the size of the given type
		DataSize sizeOf(const Type* type) {
			auto size = TypeSystem::sizeOfType(type);
			DataSize dataSize = DataSize::Size64;
			if (size == 4) {
				dataSize = DataSize::Size32;
			} else if (size == 1) {
				dataSize = DataSize::Size8;
			}

			return dataSize;
		}
	}

	MacroFunctionContext::MacroFunctionContext(const VMState& vmState,
											   const CallingConvention& callingConvention,
											   const ExceptionHandling& exceptionHandling,
											   FunctionCompilationData& functionData,
											   const Instruction& instruction,
											   const int instructionIndex)
			: vmState(vmState),
			  callingConvention(callingConvention),
			  exceptionHandling(exceptionHandling),
			  functionData(functionData),
			  instruction(instruction),
			  instructionIndex(instructionIndex) {

	}

	CodeGenerator::CodeGenerator(const CallingConvention& callingConvention, const ExceptionHandling& exceptionHandling)
			: mCallingConvention(callingConvention), mExceptionHandling(exceptionHandling) {

	}

	void CodeGenerator::defineMacro(const FunctionDefinition& function, MacroFunction macroFunction) {
		mMacros.insert({ FunctionSignature::from(function).str(), macroFunction });
	}

	bool CodeGenerator::compileAtRuntime(const VMState& vmState,
										 const FunctionDefinition& funcToCall,
										 std::string funcSignature) {
		return vmState.config.lazyJIT
			   && funcToCall.isManaged()
			   && !vmState.engine().jitCompiler().hasCompiled(funcSignature);
	}

	void CodeGenerator::generateCall(Amd64Assembler& assembler, BytePtr funcPtr, IntRegister addressRegister, bool shadowSpaceNeeded) {
		if (shadowSpaceNeeded) {
			assembler.sub(Registers::SP, mCallingConvention.calculateShadowStackSize());
		}

		assembler.moveLong(addressRegister, (PtrValue)funcPtr);
		assembler.call(addressRegister);

		if (shadowSpaceNeeded) {
			assembler.add(Registers::SP, mCallingConvention.calculateShadowStackSize());
		}
	}

	void CodeGenerator::generateGCCall(CodeGen& generatedCode, ManagedFunction& function, int instructionIndex, int generation) {
		Amd64Assembler assembler(generatedCode);
		assembler.move(RegisterCallArguments::Arg0, Registers::BP); //BP as the first argument
		assembler.moveLong(RegisterCallArguments::Arg1,	(PtrValue)&function); //Address of the function as second argument
		assembler.moveInt(RegisterCallArguments::Arg2, instructionIndex); //Current inst index as third argument
		assembler.moveInt(RegisterCallArguments::Arg3, generation); //Generation as fourth argument
		generateCall(assembler, (BytePtr)&Runtime::garbageCollect);
	}

	void CodeGenerator::generateInitializeFunction(FunctionCompilationData& functionData) {
		auto& function = functionData.function;
		Amd64Assembler assembler(functionData.function.generatedCode());

		//Calculate the size of the stack aligned to 16 bytes
		std::size_t neededStackSize = (function.def().numParameters() + function.numLocals() + function.operandStackSize())
									  * Amd64Backend::REGISTER_SIZE;
		std::size_t stackSize = ((neededStackSize + 15) / 16) * 16;

		//Save the base pointer
		assembler.push(Registers::BP);
		assembler.move(Registers::BP, Registers::SP);

		//Make room for the variables on the stack
		if (stackSize > 0) {
			assembler.sub(Registers::SP, (int)stackSize);
		}

		mCallingConvention.moveArgsToStack(functionData);
		generateZeroLocals(functionData.function, assembler);
	}

	void CodeGenerator::generateZeroLocals(ManagedFunction& function, Amd64Assembler& assembler) {
		//Zero the locals
		if (function.numLocals() > 0) {
			assembler.bitwiseXor(Registers::AX, Registers::AX);	//Zero rax

			for (int i = 0; i < function.numLocals(); i++) {
				int localOffset = (int)((i + function.def().numParameters() + 1) * -Amd64Backend::REGISTER_SIZE);
				assembler.move({ Registers::BP, localOffset }, Registers::AX);
			}
		}
	}

	void CodeGenerator::pushFunc(VMState& vmState, FunctionCompilationData& functionData, int instructionIndex, Amd64Assembler& assembler) {
		auto& function = functionData.function;

		//Get the top pointer
		auto topPtr = (BytePtr)vmState.engine().callStack().topPtr();
		assembler.move(Registers::AX, topPtr);
		assembler.add(Registers::AX, sizeof(CallStackEntry));

		//Check if overflow
		mExceptionHandling.addStackOverflowCheck(
			functionData,
			(PtrValue)(vmState.engine().callStack().start() + vmState.engine().callStack().size()));

		//Store the entry
		assembler.moveLong(Registers::CX, (PtrValue)&function);
		assembler.move({ Registers::AX, 0 }, Registers::CX);
		assembler.moveInt(Registers::CX, instructionIndex);
		assembler.move({ Registers::AX, sizeof(ManagedFunction*) }, Registers::CX);

		//Update the top pointer
		assembler.move(topPtr, Registers::AX);
	}

	void CodeGenerator::popFunc(VMState& vmState, Amd64Assembler& assembler) {
		//Get the top pointer
		auto topPtr = (BytePtr)vmState.engine().callStack().topPtr();
		assembler.move(Registers::AX, topPtr);
		assembler.add(Registers::AX, -(int)sizeof(CallStackEntry));

		//Update the top pointer
		assembler.move(topPtr, Registers::AX);
	}

	void CodeGenerator::printRegister(Amd64Assembler& assembler, IntRegister reg) {
		//Save registers
		assembler.push(Registers::AX);
		assembler.push(Registers::CX);
		assembler.push(Registers::DX);
		assembler.push(ExtendedRegisters::R8);
		assembler.push(ExtendedRegisters::R9);
		assembler.push(ExtendedRegisters::R10);
		assembler.push(ExtendedRegisters::R11);

		assembler.move(RegisterCallArguments::Arg0, reg);
		generateCall(assembler, (BytePtr)&Runtime::printRegister);

		//Restore registers
		assembler.pop(ExtendedRegisters::R11);
		assembler.pop(ExtendedRegisters::R10);
		assembler.pop(ExtendedRegisters::R9);
		assembler.pop(ExtendedRegisters::R8);
		assembler.pop(Registers::DX);
		assembler.pop(Registers::CX);
		assembler.pop(Registers::AX);
	}

	void CodeGenerator::addCardMarking(const VMState& vmState, Amd64Assembler& assembler, Registers objectRegister) {
		auto& generation = vmState.gc().oldGeneration();

		if (generation.numCards() > 0) {
			//First check if the object is inside the correct generation
			BytePtr heapStart = generation.heap().start();
			BytePtr heapEnd = generation.heap().end();

			//heapStart <= AX
			assembler.moveLong(Registers::CX, (std::int64_t)heapStart);
			assembler.compare(Registers::CX, objectRegister);
			std::size_t firstJump = assembler.data().size();
			assembler.jump(JumpCondition::GreaterThan, 0, true);

			//heapEnd >= AX
			assembler.moveLong(Registers::CX, (std::int64_t)heapEnd);
			assembler.compare(Registers::CX, objectRegister);
			std::size_t secondJump = assembler.data().size();
			assembler.jump(JumpCondition::LessThan, 0, true);

			//Inside generation, mark
//			assembler.move(RegisterCallArguments::Arg0, objectRegister);
//			generateCall(generatedCode, (BytePtr)&Runtime::markObjectCard);

			//Calculate the card number: AX = (AX - heapStart) / cardSize
			assembler.moveLong(Registers::CX, (std::int64_t)heapStart);
			assembler.sub(Registers::AX, Registers::CX);
			assembler.moveInt(Registers::CX, (std::int32_t)generation.cardSize());

			assembler.signExtend(Registers::CX, DataSize::Size64);
			assembler.div(Registers::CX, false, true);

			//Mark the card: generation.cardTable()[AX] = 1;
			assembler.moveLong(Registers::CX, (std::int64_t)generation.cardTable());
			assembler.add(Registers::AX, Registers::CX);
			assembler.move(MemoryOperand(Registers::AX), 1);

			//Set the jump targets
			Helpers::setValue(assembler.data(), firstJump + 2, (int)(assembler.data().size() - firstJump - 6));
			Helpers::setValue(assembler.data(), secondJump + 2, (int)(assembler.data().size() - secondJump - 6));
		}
	}

	void CodeGenerator::generateInstruction(VMState& vmState,
											FunctionCompilationData& functionData,
											const Instruction& instruction,
											int instructionIndex) {
		auto& function = functionData.function;
		auto& operandStack = functionData.operandStack;
		auto& assembler = functionData.assembler;
		const int stackOffset = 1; //The offset for variables allocated on the stack

		//Make the mapping
		functionData.instructionNumMapping.push_back((int)assembler.size());

		switch (instruction.opCode()) {
			case OpCodes::NOP:
				assembler.data().push_back(0x90); //nop
				break;
			case OpCodes::POP:
				operandStack.popReg(Registers::AX);
				break;
			case OpCodes::DUPLICATE:
				operandStack.duplicate();
				break;
			case OpCodes::LOAD_INT:
				operandStack.pushInt(instruction.intValue);
				break;
			case OpCodes::LOAD_FLOAT: {
				//Extract the byte pattern for the float
				auto floatData = reinterpret_cast<const int*>(&instruction.floatValue);
				operandStack.pushInt(*floatData);
				break;
			}
			case OpCodes::LOAD_CHAR:
				operandStack.pushInt(instruction.charValue);
				break;
			case OpCodes::ADD:
			case OpCodes::SUB:
			case OpCodes::MUL:
			case OpCodes::DIV: {
				auto opType = instruction.operandTypes()[0];
				bool intOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Integer);
				bool floatOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Float);
				bool is32bits = true;

				//Pop 2 operands
				if (intOp) {
					operandStack.popReg(Registers::CX);
					operandStack.popReg(Registers::AX);
				} else if (floatOp) {
					operandStack.popReg(FloatRegisters::XMM0);
					operandStack.popReg(FloatRegisters::XMM1);
				}

				//Apply the operator
				switch (instruction.opCode()) {
					case OpCodes::ADD:
						if (intOp) {
							assembler.add(Registers::AX, Registers::CX, is32bits);
						} else if (floatOp) {
							assembler.add(FloatRegisters::XMM0, FloatRegisters::XMM1);
						}
						break;
					case OpCodes::SUB:
						if (intOp) {
							assembler.sub(Registers::AX, Registers::CX, is32bits);
						} else if (floatOp) {
							assembler.sub(FloatRegisters::XMM0, FloatRegisters::XMM1);
						}
						break;
					case OpCodes::MUL:
						if (intOp) {
							assembler.mult(Registers::AX, Registers::CX, is32bits);
						} else if (floatOp) {
							assembler.mult(FloatRegisters::XMM0, FloatRegisters::XMM1);
						}
						break;
					case OpCodes::DIV:
						if (intOp) {
							assembler.signExtend(Registers::AX, DataSize::Size32); //cdq
							assembler.div(Registers::CX, is32bits); //idiv eax, ecx
						} else if (floatOp) {
							assembler.div(FloatRegisters::XMM0, FloatRegisters::XMM1);
						}
						break;
					default:
						break;
				}

				//Push the result
				if (intOp) {
					operandStack.pushReg(Registers::AX);
				} else if (floatOp) {
					operandStack.pushReg(FloatRegisters::XMM0);
				}
				break;
			}
			case OpCodes::LOAD_TRUE:
				operandStack.pushInt(1);
				break;
			case OpCodes::LOAD_FALSE:
				operandStack.pushInt(0);
				break;
			case OpCodes::AND:
			case OpCodes::OR: {
				//Pop 2 operands
				operandStack.popReg(Registers::CX);
				operandStack.popReg(Registers::AX);
				bool is32bits = false;

				//Apply the operator
				switch (instruction.opCode()) {
					case OpCodes::AND:
						assembler.bitwiseAnd(Registers::AX, Registers::CX, is32bits);
						break;
					case OpCodes::OR:
						assembler.bitwiseOr(Registers::AX, Registers::CX, is32bits);
						break;
					default:
						break;
				}

				//Push the result
				operandStack.pushReg(Registers::AX);
				break;
			}
			case OpCodes::NOT:
				operandStack.popReg(Registers::AX);
				assembler.bitwiseNot(Registers::AX);
				assembler.bitwiseAnd(Registers::AX, 1); //Clear the other bits, so that the value is either 0 or 1.
				operandStack.pushReg(Registers::AX);
				break;
			case OpCodes::CONVERT_INT_TO_FLOAT:
				operandStack.popReg(Registers::AX);
				assembler.convert(FloatRegisters::XMM0, Registers::AX);
				operandStack.pushReg(FloatRegisters::XMM0);
				break;
			case OpCodes::CONVERT_FLOAT_TO_INT:
				operandStack.popReg(FloatRegisters::XMM0);
				assembler.convert(Registers::AX, FloatRegisters::XMM0);
				operandStack.pushReg(Registers::AX);
				break;
			case OpCodes::COMPARE_EQUAL:
			case OpCodes::COMPARE_NOT_EQUAL:
			case OpCodes::COMPARE_GREATER_THAN:
			case OpCodes::COMPARE_GREATER_THAN_OR_EQUAL:
			case OpCodes::COMPARE_LESS_THAN:
			case OpCodes::COMPARE_LESS_THAN_OR_EQUAL: {
				auto opType = instruction.operandTypes()[0];
				bool floatOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Float);
				bool intBasedType = !floatOp;
				bool unsignedComparison = false;

				//Compare
				if (intBasedType) {
					operandStack.popReg(Registers::CX);
					operandStack.popReg(Registers::AX);
					assembler.compare(Registers::AX, Registers::CX);
				} else if (floatOp) {
					operandStack.popReg(FloatRegisters::XMM1);
					operandStack.popReg(FloatRegisters::XMM0);
					assembler.compare(FloatRegisters::XMM0, FloatRegisters::XMM1);
					unsignedComparison = true;
				}

				//Jump
				std::size_t compareJump = assembler.size();
				std::size_t jump = 0;
				std::size_t trueBranchStart = 0;
				std::size_t falseBranchStart = 0;

				int target = 0;
				JumpCondition condition = JumpCondition::Always;
				switch (instruction.opCode()) {
					case OpCodes::COMPARE_EQUAL:
						condition = JumpCondition::Equal;
						break;
					case OpCodes::COMPARE_NOT_EQUAL:
						condition = JumpCondition::NotEqual;
						break;
					case OpCodes::COMPARE_GREATER_THAN:
						condition = JumpCondition::GreaterThan;
						break;
					case OpCodes::COMPARE_GREATER_THAN_OR_EQUAL:
						condition = JumpCondition::GreaterThanOrEqual;
						break;
					case OpCodes::COMPARE_LESS_THAN:
						condition = JumpCondition::LessThan;
						break;
					case OpCodes::COMPARE_LESS_THAN_OR_EQUAL:
						condition = JumpCondition::LessThanOrEqual;
						break;
					default:
						break;
				}

				assembler.jump(condition, target, unsignedComparison);

				//Both branches will have the same operand entry, reserve space
				operandStack.reserveSpace();

				//False branch
				falseBranchStart = assembler.size();
				operandStack.pushInt(0, false);
				jump = assembler.size();
				assembler.jump(JumpCondition::Always, 0);

				//True branch
				trueBranchStart = assembler.size();
				operandStack.pushInt(1, false);

				//Set the jump targets
				Helpers::setValue(assembler.data(), jump + 1, (int)(assembler.size() - trueBranchStart));
				Helpers::setValue(assembler.data(), compareJump + 2, (int)(trueBranchStart - falseBranchStart));
				break;
			}
			case OpCodes::LOAD_LOCAL:
			case OpCodes::STORE_LOCAL: {
				int localOffset = (stackOffset + instruction.intValue + (int)function.def().numParameters())
								  * -Amd64Backend::REGISTER_SIZE;
				if (instruction.opCode() == OpCodes::LOAD_LOCAL) {
					assembler.move(Registers::AX, { Registers::BP, localOffset });
					operandStack.pushReg(Registers::AX);
				} else {
					operandStack.popReg(Registers::AX);
					assembler.move({ Registers::BP, localOffset }, Registers::AX);
				}
				break;
			}
			case OpCodes::CALL:
			case OpCodes::CALL_INSTANCE:
			case OpCodes::CALL_VIRTUAL: {
				std::string calledSignature = "";

				if (!instruction.isCallInstance()) {
					calledSignature = FunctionSignature::function(
						instruction.stringValue,
						instruction.parameters).str();
				} else {
					calledSignature = FunctionSignature::memberFunction(
						instruction.classType,
						instruction.stringValue,
						instruction.parameters).str();
				}

				const auto& funcToCall = vmState.binder().getFunction(calledSignature);

				if (mMacros.count(calledSignature) == 0) {
					bool needsToCompile = compileAtRuntime(vmState, funcToCall, calledSignature);
					std::size_t callIndex = 0;

					//Check if the called function needs to be compiled
					if (needsToCompile && !funcToCall.isVirtual()) {
						callIndex = generateCompileCall(assembler, function, funcToCall);
					}

					//Push the call
					pushFunc(vmState, functionData, instructionIndex, assembler);

					MemoryOperand firstArgOffset(
						Registers::BP,
						operandStack.getStackOperandOffset(operandStack.topIndex() - (int)funcToCall.numParameters() + 1));

					//Add null check
					if (instruction.isCallInstance()) {
						assembler.move(Registers::AX, firstArgOffset);
						mExceptionHandling.addNullCheck(functionData, Registers::AX);
					}

					//Get the address of the function to call
					BytePtr funcAddress = nullptr;

					//Handle virtual calls
					if (funcToCall.isManaged() && funcToCall.isVirtual()) {
						assembler.move(RegisterCallArguments::Arg0, firstArgOffset);
						assembler.moveInt(RegisterCallArguments::Arg1, funcToCall.classType()->metadata()->getVirtualFunctionIndex(funcToCall));
						generateCall(assembler, (BytePtr)&Runtime::getVirtualFunctionAddress);
						assembler.move(ExtendedRegisters::R12, RegisterCallArguments::ReturnValue);
					}

					//Align the stack
					int stackAlignment = mCallingConvention.calculateStackAlignment(functionData, funcToCall);
					if (stackAlignment > 0) {
						assembler.add(Registers::SP, -stackAlignment);
					}

					//Set the function arguments
					mCallingConvention.callFunctionArguments(functionData, funcToCall);

					//Shadow stack size may be needed
					int shadowStack = mCallingConvention.calculateShadowStackSize();
					if (shadowStack > 0) {
						assembler.sub(Registers::SP, shadowStack);
					}

					if (funcToCall.isManaged() && !funcToCall.isVirtual()) {
						if (!needsToCompile) {
							//Mark that the function call needs to be patched with the entry point later
							functionData.unresolvedCalls.push_back(
								UnresolvedFunctionCall(
									FunctionCallType::Relative,
									assembler.size(),
									funcToCall));
						} else {
							Helpers::setValue(assembler.data(), callIndex, (int)assembler.size());
						}

						//Make the call
						assembler.call(0);
					} else if (funcToCall.isManaged() && funcToCall.isVirtual()) {
						//Make the virtual call
						assembler.call(ExtendedRegisters::R12);
					} else {
						//Unmanaged functions are located beyond one int, direct addressing must be used.
						//Check if the function entry point is defined yet
						if (funcToCall.entryPoint() != 0) {
							funcAddress = funcToCall.entryPoint();
						} else {
							//Mark that the function call needs to be patched with the entry point later
							functionData.unresolvedCalls.push_back(
								UnresolvedFunctionCall(
									FunctionCallType::Absolute,
									assembler.size(),
									funcToCall));
						}

						//Make the call
						generateCall(assembler, funcAddress, Registers::AX, false);
					}

					//Unalign the stack
					if (stackAlignment + shadowStack > 0) {
						assembler.add(Registers::SP, stackAlignment + shadowStack);
					}

					//Push the result
					mCallingConvention.handleReturnValue(functionData, funcToCall);

					//Pop the call
					popFunc(vmState, assembler);
				} else {
					//Invoke the macro function
					mMacros[calledSignature]({
						vmState,
						mCallingConvention,
						mExceptionHandling,
						functionData,
						instruction,
						instructionIndex
					});
				}
				break;
			}
			case OpCodes::RET: {
				//If debug is enabled, print the stack frame before return
				if (vmState.config.enableDebug && vmState.config.printStackFrame) {
					assembler.move(RegisterCallArguments::Arg0, Registers::BP);
					assembler.moveLong(RegisterCallArguments::Arg1, (PtrValue)&function);
					generateCall(assembler, (BytePtr)&Runtime::printStackFrame);
				}

				mCallingConvention.makeReturnValue(functionData);

				//Restore the base pointer
				assembler.move(Registers::SP, Registers::BP);
				assembler.pop(Registers::BP);

				//Make the return
				assembler.ret();
				break;
			}
			case OpCodes::LOAD_ARG: {
				//Load rax with the argument
				assembler.move(
					Registers::AX,
					{ Registers::BP, (instruction.intValue + stackOffset) * -Amd64Backend::REGISTER_SIZE });

				//Push the loaded value
				operandStack.pushReg(Registers::AX);
				break;
			}
			case OpCodes::BRANCH: {
				assembler.jump(JumpCondition::Always, 0);

				//As the exact target in native instructions isn't known, defer to later.
				functionData.unresolvedBranches.insert({
					assembler.size() - 5,
					BranchTarget((unsigned int)instruction.intValue, 5)
				 });
				break;
			}
			case OpCodes::BRANCH_EQUAL:
			case OpCodes::BRANCH_NOT_EQUAL:
			case OpCodes::BRANCH_GREATER_THAN:
			case OpCodes::BRANCH_GREATER_THAN_OR_EQUAL:
			case OpCodes::BRANCH_LESS_THAN:
			case OpCodes::BRANCH_LESS_THAN_OR_EQUAL: {
				auto opType = instruction.operandTypes()[0];
				bool floatOp = TypeSystem::isPrimitiveType(opType, PrimitiveTypes::Float);
				bool intBasedType = !floatOp;
				bool unsignedComparison = false;

				//Compare
				if (intBasedType) {
					operandStack.popReg(Registers::CX);
					operandStack.popReg(Registers::AX);
					assembler.compare(Registers::AX, Registers::CX);
				} else if (floatOp) {
					operandStack.popReg(FloatRegisters::XMM1);
					operandStack.popReg(FloatRegisters::XMM0);
					assembler.compare(FloatRegisters::XMM0, FloatRegisters::XMM1);
					unsignedComparison = true;
				}

				JumpCondition condition = JumpCondition::Always;
				switch (instruction.opCode()) {
					case OpCodes::BRANCH_EQUAL:
						condition = JumpCondition::Equal;
						break;
					case OpCodes::BRANCH_NOT_EQUAL:
						condition = JumpCondition::NotEqual;
						break;
					case OpCodes::BRANCH_GREATER_THAN:
						condition = JumpCondition::GreaterThan;
						break;
					case OpCodes::BRANCH_GREATER_THAN_OR_EQUAL:
						condition = JumpCondition::GreaterThanOrEqual;
						break;
					case OpCodes::BRANCH_LESS_THAN:
						condition = JumpCondition::LessThan;
						break;
					case OpCodes::BRANCH_LESS_THAN_OR_EQUAL:
						condition = JumpCondition::LessThanOrEqual;
						break;
					default:
						break;
				}

				assembler.jump(condition, 0, unsignedComparison);

				//As the exact target in native instructions isn't known, defer to later.
				functionData.unresolvedBranches.insert({
					assembler.size() - 6,
					BranchTarget((unsigned int)instruction.intValue, 6)
				});
				break;
			}
			case OpCodes::LOAD_NULL:
				operandStack.pushInt(0);
				break;
			case OpCodes::NEW_ARRAY: {
				auto elementType = vmState.typeProvider().getType(instruction.stringValue);
				auto arrayType = static_cast<const ArrayType*>(
						vmState.typeProvider().getType(TypeSystem::arrayTypeName(elementType)));

				if (!vmState.config.disableGC) {
					generateGCCall(assembler.data(), function, instructionIndex);
				}

				//The pointer to the type as the first arg
				assembler.moveLong(RegisterCallArguments::Arg0, (PtrValue)arrayType);

				//Pop the size as the second arg
				operandStack.popReg(RegisterCallArguments::Arg1);

				//Check that the size >= 0
				mExceptionHandling.addArrayCreationCheck(functionData);

				//Call the newArray runtime function
				generateCall(assembler, (BytePtr)&Runtime::newArray);

				//Push the returned pointer
				operandStack.pushReg(Registers::AX);
				break;
			}
			case OpCodes::STORE_ELEMENT: {
				auto elementType = vmState.typeProvider().getType(instruction.stringValue);

				//Pop the operands
				operandStack.popReg(Registers::DX); //The value to store
				operandStack.popReg(ExtendedRegisters::R10); //The index of the element
				operandStack.popReg(Registers::AX); //The address of the array

				//Error checks
				mExceptionHandling.addNullCheck(functionData);
				mExceptionHandling.addArrayBoundsCheck(functionData);

				//Compute the address of the element
				assembler.mult(ExtendedRegisters::R10, (int)TypeSystem::sizeOfType(elementType));
				assembler.add(Registers::AX, ExtendedRegisters::R10);
				assembler.add(Registers::AX, stackjit::ARRAY_LENGTH_SIZE);

				//Store the element
				auto elementDataSize = sizeOf(elementType);
				MemoryOperand elementOffset(Registers::AX);
				if (elementDataSize != DataSize::Size8) {
					assembler.move(elementOffset, Registers::DX, elementDataSize);
				} else {
					assembler.move(elementOffset, Register8Bits::DL);
				}

				if (elementType->isReference()) {
					addCardMarking(vmState, assembler, Registers::AX);
				}
				break;
			}
			case OpCodes::LOAD_ELEMENT: {
				auto elementType = vmState.typeProvider().getType(instruction.stringValue);

				//Pop the operands
				operandStack.popReg(ExtendedRegisters::R10); //The index of the element
				operandStack.popReg(Registers::AX); //The address of the array

				//Error checks
				mExceptionHandling.addNullCheck(functionData);
				mExceptionHandling.addArrayBoundsCheck(functionData);

				//Compute the address of the element
				assembler.mult(ExtendedRegisters::R10, (int)TypeSystem::sizeOfType(elementType));
				assembler.add(Registers::AX, ExtendedRegisters::R10);
				assembler.add(Registers::AX, stackjit::ARRAY_LENGTH_SIZE);

				//Load the element
				auto elementDataSize = sizeOf(elementType);
				MemoryOperand elementOffset(Registers::AX);
				if (elementDataSize != DataSize::Size8) {
					assembler.move(Registers::CX, elementOffset, elementDataSize);
				} else {
					assembler.move(Register8Bits::CL, elementOffset);
				}

				operandStack.pushReg(Registers::CX);
				break;
			}
			case OpCodes::LOAD_ARRAY_LENGTH:
				//Pop the array ref
				operandStack.popReg(Registers::AX);

				//Null check
				mExceptionHandling.addNullCheck(functionData);

				//Get the size of the array (an int)
				assembler.move(Registers::AX, MemoryOperand(Registers::AX), DataSize::Size32);

				//Push the size
				operandStack.pushReg(Registers::AX);
				break;
			case OpCodes::NEW_OBJECT: {
				auto classType = instruction.classType;

				//Call the garbageCollect runtime function
				if (!vmState.config.disableGC) {
					generateGCCall(assembler.data(), function, instructionIndex);
				}

				//Push the call
				pushFunc(vmState, functionData, instructionIndex, assembler);

				//Check if the constructor needs to be compiled
				auto calledSignature = FunctionSignature::memberFunction(
					instruction.classType,
					instruction.stringValue,
					instruction.parameters).str();

				const auto& constructorToCall = vmState.binder().getFunction(calledSignature);

				bool needsToCompile = compileAtRuntime(vmState, constructorToCall, calledSignature);
				std::size_t callIndex = 0;
				if (needsToCompile) {
					callIndex = generateCompileCall(assembler, function, constructorToCall);
				}

				//Call the newClass runtime function
				assembler.moveLong(RegisterCallArguments::Arg0, (PtrValue)classType); //The pointer to the type
				generateCall(assembler, (BytePtr)&Runtime::newClass);

				//Save the reference
				assembler.move(ExtendedRegisters::R10, Registers::AX);

				//Align the stack
				int stackAlignment = mCallingConvention.calculateStackAlignment(functionData, constructorToCall);
				if (stackAlignment > 0) {
					assembler.add(Registers::SP, -stackAlignment);
				}

				//Set the constructor arguments
				assembler.move(RegisterCallArguments::Arg0, Registers::AX);
				int numArgs = (int)constructorToCall.parameters().size() - 1;

				for (int i = numArgs - 1; i >= 0; i--) {
					mCallingConvention.callFunctionArgument(
						functionData,
						i + 1,
						instruction.parameters.at((std::size_t)i),
						constructorToCall);
				}

				//Push the reference to the created object
				assembler.move(Registers::AX, ExtendedRegisters::R10);
				operandStack.pushReg(Registers::AX);

				//Shadow stack may be needed
				int shadowStack = mCallingConvention.calculateShadowStackSize();
				if (shadowStack > 0) {
					assembler.sub(Registers::SP, shadowStack);
				}

				if (!needsToCompile) {
					//Mark that the constructor needs to be patched with the entry point later
					functionData.unresolvedCalls.push_back(
						UnresolvedFunctionCall(
							FunctionCallType::Relative,
							assembler.size(),
							constructorToCall));
				} else {
					Helpers::setValue(assembler.data(), callIndex, (int)assembler.size());
				}

				//Call the constructor
				assembler.call(0);

				//Unalign the stack
				if (stackAlignment + shadowStack > 0) {
					assembler.add(Registers::SP, stackAlignment + shadowStack);
				}

				//This is for clean up after a call, as the constructor returns nothing.
				mCallingConvention.handleReturnValue(functionData, constructorToCall);

				//Pop the call
				popFunc(vmState, assembler);
				break;
			}
			case OpCodes::LOAD_FIELD:
			case OpCodes::STORE_FIELD: {
				//Get the field
				std::string className;
				std::string fieldName;
				TypeSystem::getClassAndFieldName(instruction.stringValue, className, fieldName);

				auto& classMetadata = vmState.classProvider().getMetadata(className);
				auto& field = classMetadata.fields().at(fieldName);
				int fieldOffset = (int)field.offset();

				//Get the size of the field
				auto fieldDataSize = sizeOf(field.type());

				if (instruction.opCode() == OpCodes::LOAD_FIELD) {
					//Pop the operand
					operandStack.popReg(Registers::AX); //The address of the object

					//Null check
					mExceptionHandling.addNullCheck(functionData);

					//Compute the address of the field
					assembler.add(Registers::AX, fieldOffset);

					//Load the field
					MemoryOperand fieldMemoryOperand(Registers::AX);
					if (fieldDataSize != DataSize::Size8) {
						assembler.move(Registers::CX, fieldMemoryOperand, fieldDataSize);
					} else {
						assembler.move(Register8Bits::CL, fieldMemoryOperand);
					}

					operandStack.pushReg(Registers::CX);
				} else {
					//Pop the operand
					operandStack.popReg(Registers::DX); //The value to store
					operandStack.popReg(Registers::AX); //The address of the object

					//Null check
					mExceptionHandling.addNullCheck(functionData);

					//Store the field
					MemoryOperand fieldMemoryOperand(Registers::AX, fieldOffset);
					if (fieldDataSize != DataSize::Size8) {
						assembler.move(fieldMemoryOperand, Registers::DX, fieldDataSize);
					} else {
						assembler.move(fieldMemoryOperand, Register8Bits::DL);
					}

					//Card marking
					if (field.type()->isReference()) {
						addCardMarking(vmState, assembler, Registers::AX);
					}
				}
				break;
			}
			case OpCodes::LOAD_STRING: {
				if (!vmState.config.disableGC) {
					generateGCCall(assembler.data(), function, instructionIndex);
				}

				//The pointer to the string as the first arg
				assembler.moveLong(RegisterCallArguments::Arg0, (PtrValue)instruction.stringValue.data());

				//The length of the string as the second arg
				assembler.moveInt(RegisterCallArguments::Arg1, (int)instruction.stringValue.length());

				//Call the newString runtime function
				generateCall(assembler, (BytePtr)&Runtime::newString);

				//Push the returned pointer
				operandStack.pushReg(Registers::AX);
				break;
			}
		}
	}
}
