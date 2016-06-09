#include "runtime.h"
#include "../compiler/amd64.h"
#include "../vmstate.h"
#include "../core/function.h"
#include "../type/type.h"
#include "stackframe.h"
#include "../helpers.h"
#include "../stackjit.h"
#include "native.h"
#include "../core/functionsignature.h"
#include <iostream>

namespace Runtime {
	VMState vmState;
};

namespace {
	//Prints the given value
	void printValue(RegisterValue value, const Type* type) {
		if (TypeSystem::isReferenceType(type)) {
			if (value == 0) {
				std::cout << "nullref";
			} else {
				std::cout << "0x" << std::hex << value << std::dec;
			}
		} else if (type->name() == TypeSystem::toString(PrimitiveTypes::Float)) {
			int floatPattern = (int)value;
			float floatValue = *(reinterpret_cast<float*>(&floatPattern));
			std::cout << floatValue;
		} else {
			std::cout << value;
		}

		std::cout << " (" + type->name() + ")";
	}
}

void Runtime::printStackFrame(RegisterValue* basePtr, ManagedFunction* func) {
	using namespace Runtime::Internal;

	auto numArgs = func->def().numParams();
	auto numLocals = func->numLocals();

	std::cout << "----Start StackFrame----" << std::endl;
	std::cout << "Func: " << func->def().name() << std::endl;
	std::cout << "Num args: " << numArgs << std::endl;
	std::cout << "Num locals: " << numLocals << std::endl;

	std::cout << std::endl;
	std::cout << "Values:" << std::endl;
	printAliveObjects(basePtr, func, (int)func->instructions().size() - 1, "\t");

	std::cout << "----End StackFrame----" << std::endl;
}

void Runtime::compileFunction(ManagedFunction* callee, int callOffset, int checkStart, int checkEnd,
							  FunctionDefinition* funcToCall) {
	auto toCallSignature = FunctionSignature::from(*funcToCall).str();

	//Compile the function (if needed)
	try {
		vmState.engine().compileFunction(toCallSignature);
	} catch (std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		exit(0);
	}

	if (vmState.enableDebug && vmState.printLazyPatching) {
		std::cout
		<< "Patching call to " << toCallSignature << " at " << FunctionSignature::from(callee->def()).str()
		<< ", offset: " << callOffset << ", check offset: " << checkStart << "." << std::endl;
	}

	//Get a pointer to the function code
	auto codePtr = callee->def().entryPoint();

	//The address of the called function
	auto calledFuncPtr = funcToCall->entryPoint();

	//Update the call target
	int target = (int)(calledFuncPtr - (codePtr + callOffset + 5));
	Helpers::setValue(codePtr, (std::size_t)callOffset + 1, target);

	//Replace this check at the call site with a branch to end of the check
	codePtr[checkStart] = 0xe9;
	Helpers::setValue(codePtr, (std::size_t)checkStart + 1, checkEnd - (checkStart + 5));
}

void Runtime::Internal::printAliveObjects(RegisterValue* basePtr, ManagedFunction* func, int instIndex,
										  std::string indentation) {
	StackFrame stackFrame(basePtr, func, instIndex);
	auto numArgs = func->def().numParams();
	auto numLocals = func->numLocals();
	auto stackSize = stackFrame.operandStackSize();

	if (numArgs > 0) {
		std::cout << indentation << "Args: " << std::endl;

		for (std::size_t i = 0; i < numArgs; i++) {
			std::cout << indentation << i << ": ";
			auto arg = stackFrame.getArgument(i);
			printValue(arg.value(), arg.type());
			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	if (numLocals > 0) {
		std::cout << indentation << "Locals: " << std::endl;

		for (std::size_t i = 0; i < numLocals; i++) {
			std::cout << indentation << i << ": ";
			auto local = stackFrame.getLocal(i);
			printValue(local.value(), local.type());
			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	if (stackSize > 0) {
		std::cout << indentation << "Stack: " << std::endl;

		for (std::size_t i = 0; i < stackSize; i++) {
			std::cout << indentation << i << ": ";
			auto operand = stackFrame.getStackOperand(i);
			printValue(operand.value(), operand.type());
			std::cout << std::endl;
		}
	}
}

RegisterValue* Runtime::Internal::findBasePtr(RegisterValue* currentBasePtr, int currentIndex, int targetIndex) {
	if (currentBasePtr == nullptr) {
		return nullptr;
	}

	if (currentIndex == targetIndex) {
		return (RegisterValue*)*currentBasePtr;
	}

	return findBasePtr((RegisterValue*)*currentBasePtr, currentIndex + 1, targetIndex);
}

void Runtime::garbageCollect(RegisterValue* basePtr, ManagedFunction* func, int instIndex) {
	GCRuntimeInformation runtimeInformation(basePtr, func, instIndex);
	vmState.gc().collect(runtimeInformation);
}

unsigned char* Runtime::newArray(const ArrayType* arrayType, int length) {
	return vmState.gc().newArray(arrayType, length);
}

unsigned char* Runtime::newObject(const ClassType* classType) {
	return vmState.gc().newClass(classType);
}

unsigned char* Runtime::newString(const char* string, int length) {
	//Allocate the underlying char array
	auto charsPtr = vmState.gc().newArray(StringRef::charArrayType(), length);

	//Set the value for the char array
	for (int i = 0; i < length; i++) {
		charsPtr[i + StackJIT::ARRAY_LENGTH_SIZE] = (unsigned char)string[i];
	}

	//Allocate the string object
	auto strPr = vmState.gc().newClass(StringRef::stringType());

	//Set the chars field
	StringRef::setCharsField(strPr, (char*)charsPtr);

	return strPr;
}

void Runtime::runtimeError(std::string errorMessage) {
	std::cout << "Error: " << errorMessage << std::endl;
	exit(0);
}

void Runtime::invalidArrayCreation() {
	Runtime::runtimeError("The length of the array must be >= 0.");
}

void Runtime::arrayOutOfBoundsError() {
	Runtime::runtimeError("Array index is out of bounds.");
}

void Runtime::nullReferenceError() {
	Runtime::runtimeError("Null reference.");
}

void Runtime::stackOverflow() {
	Runtime::runtimeError("Stack overflow.");
}