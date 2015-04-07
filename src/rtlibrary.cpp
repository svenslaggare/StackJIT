#include <iostream>
#include <string.h>

#include "rtlibrary.h"
#include "amd64.h"
#include "objects.h"
#include "vmstate.h"
#include "function.h"
#include "type.h"
#include "codegenerator.h"

extern VMState vmState;

void Runtime::pushFunc(Function* func, int instIndex) {
    vmState.pushFunc(func, instIndex);
}

void Runtime::popFunc() {
    vmState.popFunc();
}

void Runtime::printStackFrame(long* basePtr, Function* func) {
    using namespace Runtime::Internal;

    int numArgs = func->numArgs();
    int numLocals = func->numLocals();

    std::cout << "----Start StackFrame----" << std::endl;
    std::cout << "Func: " << func->name() << std::endl;
    std::cout << "Num args: " << numArgs << std::endl;
    std::cout << "Num locals: " << numLocals << std::endl;

    std::cout << std::endl;
    std::cout << "Values:" << std::endl;
    printAliveObjects(basePtr, func, func->instructions.size() - 1, "\t");

    std::cout << "----End StackFrame----" << std::endl;
}

void printStackTrace(long* basePtr, int level) {
    if (level > 50 || basePtr == nullptr) {
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

void Runtime::Internal::printAliveObjects(long* basePtr, Function* func, int instIndex, std::string indentation) {
    int numArgs = func->numArgs();
    int numLocals = func->numLocals();
    auto operandTypes = func->preInstructionOperandTypes.at(instIndex);
    int stackSize = operandTypes.size();

    long* argsStart = basePtr - 1;
    long* localsStart = basePtr - 1 - numArgs;
    long* stackStart = basePtr - 1 - (func->stackSize() / 8);

    if (numArgs > 0) {
        std::cout << indentation << "Args: " << std::endl;
        for (int i = 0; i < numArgs; i++) {
            std::cout << indentation << i << ": ";
            printValue(argsStart[-i], func->arguments()[i]);
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    if (numLocals > 0) {
        std::cout << indentation << "Locals: " << std::endl;
        for (int i = 0; i < numLocals; i++) {
            std::cout << indentation << i << ": ";
            printValue(localsStart[-i], func->getLocal(i));
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    if (stackSize > 0) {
        std::cout << indentation << "Stack: " << std::endl;
        for (int i = 0; i < stackSize; i++) {
            std::cout << indentation << i << ": ";
            printValue(stackStart[-i], operandTypes[stackSize - 1 - i]);
            std::cout << std::endl;
        }
    }
}

void Runtime::Internal::markObjects(long* basePtr, Function* func, int instIndex) {
    auto& gc = vmState.gc();

    int numArgs = func->numArgs();
    int numLocals = func->numLocals();
    auto operandTypes = func->preInstructionOperandTypes.at(instIndex);
    int stackSize = operandTypes.size();

    long* argsStart = basePtr - 1;
    long* localsStart = basePtr - 1 - numArgs;
    long* stackStart = basePtr - 1 - (func->stackSize() / 8);

    if (numArgs > 0) {
        for (int i = 0; i < numArgs; i++) {
            gc.markValue(argsStart[-i], func->arguments()[i]);
        }
    }

    if (numLocals > 0) {
        for (int i = 0; i < numLocals; i++) {
            gc.markValue(localsStart[-i], func->getLocal(i));
        }
    }

    if (stackSize > 0) {
        for (int i = 0; i < stackSize; i++) {
            gc.markValue(stackStart[-i], operandTypes[stackSize - 1 - i]);
        }
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

        int topFuncIndex = 0;
        for (auto callEntry : vmState.callStack()) {
            auto topFunc = callEntry.first;
            auto callPoint = callEntry.second;
            auto callBasePtr = findBasePtr(basePtr, 0, topFuncIndex);

            if (vmState.enableDebug) {
                std::cout << topFunc->name() << " (" << callPoint << ")" << std::endl;
            }

            if (vmState.enableDebug) {
                printAliveObjects(callBasePtr, topFunc, callPoint, "\t");
            }
            
            markObjects(callBasePtr, topFunc, callPoint);

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

long Runtime::newArray(Type* elementType, int length) {
    return (long)(vmState.gc().newArray(elementType, length));
}

long Runtime::newObject(Type* type) {
    auto structType = static_cast<StructType*>(type);
    return (long)(vmState.gc().newStruct(structType));
}

long Runtime::newString(const char* string, int length) {
    auto elemType = vmState.typeProvider().makeType(TypeSystem::toString(PrimitiveTypes::Char));
    auto strPtr = vmState.gc().newArray(elemType, length);
    
    for (int i = 0; i < length; i++) {
        strPtr[i + 4] = string[i];
    }

    return (long)strPtr;
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