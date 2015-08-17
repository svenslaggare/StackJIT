#include "rtlibrary.h"
#include "amd64.h"
#include "objects.h"
#include "vmstate.h"
#include "function.h"
#include "type.h"
#include "stackframe.h"
#include "helpers.h"
#include "stackjit.h"
#include <iostream>
#include <string.h>

extern VMState vmState;

void Runtime::printStackFrame(long* basePtr, Function* func) {
    using namespace Runtime::Internal;

    auto numArgs = func->numParams();
    auto numLocals = func->numLocals();

    std::cout << "----Start StackFrame----" << std::endl;
    std::cout << "Func: " << func->name() << std::endl;
    std::cout << "Num args: " << numArgs << std::endl;
    std::cout << "Num locals: " << numLocals << std::endl;

    std::cout << std::endl;
    std::cout << "Values:" << std::endl;
    printAliveObjects(basePtr, func, (int)func->instructions.size() - 1, "\t");

    std::cout << "----End StackFrame----" << std::endl;
}

namespace {
    void printStackTrace(long* basePtr, int level) {
        if (basePtr == nullptr) {
            return;
        }

        std::cout << basePtr << " from " << "0x" << std::hex << *basePtr << std::dec << std::endl;
        printStackTrace((long*)*basePtr, level + 1);
    }

    void printTimes(char c, int times) {
        for (int i = 0; i < times; i++) {
            std::cout << c;
        }
    }

    long* findBasePtr(long* basePtr, int currentIndex, int index) {
        if (basePtr == nullptr) {
            return nullptr;
        }

        if (currentIndex == index) {
            return (long*)*basePtr;
        }

        return findBasePtr((long*)*basePtr, currentIndex + 1, index);
    }

    void printValue(long value, const Type* type) {
        if (TypeSystem::isReferenceType(type)) {
            if (value == 0) {
                std::cout << "nullref";
            } else {
                std::cout << "0x" << std::hex << value << std::dec;
            }
        } else if (type->name() == "Float") {
            int floatPattern = (int)value;
            float floatValue = *(reinterpret_cast<float*>(&floatPattern));
            std::cout << floatValue;
        } else {
            std::cout << value;
        }

        std::cout << " (" + type->name() + ")";
    }
}

void Runtime::compileFunction(Function* callee, int callOffset, int checkStart, int checkEnd, FunctionDefinition* funcToCall) {
	auto toCallSignature = vmState.binder().functionSignature(*funcToCall);

	vmState.engine().compileFunction(toCallSignature);

	if (vmState.enableDebug && vmState.printLazyPatching) {
		std::cout
			<< "Patching call to " << toCallSignature << " at " << vmState.binder().functionSignature(*callee)
			<< ", offset: " << callOffset << ", check offset: " << checkStart << "." << std::endl;
	}

	//Get a pointer to the function code
	auto funcCodePtr = (unsigned char*)vmState.binder().getFunction(*callee).entryPoint();

	//The address of the called function
	long calledFuncAddr = funcToCall->entryPoint();

	//Update the call target
	int target = (int)(calledFuncAddr - ((long)funcCodePtr + callOffset + 5));
	Helpers::setInt(funcCodePtr, callOffset + 1, target);

	//Replace this check at the call site with a branch to end of the check
	funcCodePtr[checkStart] = 0xe9;
	Helpers::setInt(funcCodePtr, checkStart + 1, checkEnd - (checkStart + 5));
}

void Runtime::Internal::printAliveObjects(long* basePtr, Function* func, int instIndex, std::string indentation) {
	StackFrame stackFrame(basePtr, func, instIndex);
	auto numArgs = func->numParams();
	auto numLocals = func->numLocals();
	auto stackSize = stackFrame.operandStackSize();

	if (numArgs > 0) {
		std::cout << indentation << "Args: " << std::endl;

		for (std::size_t i = 0; i < numArgs; i++) {
			std::cout << indentation << i << ": ";
			auto arg = stackFrame.getArgument(i);
			printValue(arg.value, arg.type);
			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	if (numLocals > 0) {
		std::cout << indentation << "Locals: " << std::endl;

		for (std::size_t i = 0; i < numLocals; i++) {
			std::cout << indentation << i << ": ";
			auto local = stackFrame.getLocal(i);
			printValue(local.value, local.type);
			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	if (stackSize > 0) {
		std::cout << indentation << "Stack: " << std::endl;

		for (std::size_t i = 0; i < stackSize; i++) {
			std::cout << indentation << i << ": ";
			auto operand = stackFrame.getStackOperand(i);
			printValue(operand.value, operand.type);
			std::cout << std::endl;
		}
	}
}

void Runtime::Internal::markObjects(long* basePtr, Function* func, int instIndex) {
    auto& gc = vmState.gc();

	StackFrame stackFrame(basePtr, func, instIndex);
	auto numArgs = func->numParams();
	auto numLocals = func->numLocals();
    auto stackSize = stackFrame.operandStackSize();

	for (std::size_t i = 0; i < numArgs; i++) {
		auto arg = stackFrame.getArgument(i);
		gc.markValue(arg.value, arg.type);
	}

	for (std::size_t i = 0; i < numLocals; i++) {
		auto local = stackFrame.getLocal(i);
		gc.markValue(local.value, local.type);
	}

	for (std::size_t i = 0; i < stackSize; i++) {
		auto operand = stackFrame.getStackOperand(i);
		gc.markValue(operand.value, operand.type);
	}
}

void Runtime::garbageCollect(long* basePtr, Function* func, int instIndex) {
    using namespace Runtime::Internal;
    auto& gc = vmState.gc();

    if (gc.beginGC()) {
        int startStrLength = 0;

        if (vmState.enableDebug) {
            auto startStr = "---------------Start GC in func " + func->name() + " (" + std::to_string(instIndex) + ")---------------";
            std::cout << startStr << std::endl;
            startStrLength = startStr.length();
        }
        
        if (vmState.enableDebug) {
            std::cout << "Stack trace: " << std::endl;
            std::cout << func->name() << " (" << instIndex << ")" << std::endl;
            printAliveObjects(basePtr, func, instIndex, "\t");
        }

        markObjects(basePtr, func, instIndex);

        auto topEntryPtr = vmState.engine().callStack().top();
		int topFuncIndex = 0;
		while (topEntryPtr > vmState.engine().callStack().start()) {
			auto callEntry = *topEntryPtr;
			auto topFunc = callEntry.function;
            auto callPoint = callEntry.callPoint;
            auto callBasePtr = findBasePtr(basePtr, 0, topFuncIndex);

			if (vmState.enableDebug) {
                std::cout << topFunc->name() << " (" << callPoint << ")" << std::endl;
            }

            if (vmState.enableDebug) {
                printAliveObjects(callBasePtr, topFunc, callPoint, "\t");
            }

            markObjects(callBasePtr, topFunc, callPoint);

			topEntryPtr--;
			topFuncIndex++;
		}

        if (vmState.enableDebug) {
            printTimes('-', startStrLength / 2 - 3);
            std::cout << "End GC";
            printTimes('-', (startStrLength + 1) / 2 - 3);
            std::cout << std::endl;
        }

        gc.endGC();
    }
}

unsigned char* Runtime::newArray(const Type* elementType, int length) {
    return vmState.gc().newArray(elementType, length);
}

unsigned char* Runtime::newObject(const Type* type) {
    auto classType = static_cast<const ClassType*>(type);
    return vmState.gc().newClass(classType);
}

unsigned char* Runtime::newString(const char* string, int length) {
    auto elemType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Char));
    auto strPtr = vmState.gc().newArray(elemType, length);
    
    for (int i = 0; i < length; i++) {
        strPtr[i + StackJIT::ARRAY_LENGTH_SIZE] = (unsigned char)string[i];
    }

    return strPtr;
}

void Runtime::runtimeError(std::string errorMessage) {
    throw std::runtime_error(errorMessage);
}

void Runtime::invalidArrayCreation() {
    Runtime::runtimeError("The length of the array must be >= 0.");
}

void Runtime::arrayOutOfBoundsError() {
    Runtime::runtimeError("Array index is out of bounds.");
}

void Runtime::nullReferenceError() {
    Runtime::runtimeError("Null reference error.");
}

void Runtime::stackOverflow() {
	Runtime::runtimeError("Stack overflow.");
}