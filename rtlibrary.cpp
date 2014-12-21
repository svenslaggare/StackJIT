#include <iostream>
#include <string.h>

#include "rtlibrary.h"
#include "amd64.h"
#include "objects.h"
#include "vmstate.h"
#include "program.h"
#include "type.h"
#include "codegenerator.h"

extern VMState vmState;

void rt_printStackFrame(long* basePtr, Function* func) {
    int numArgs = func->numArgs();
    int numLocals = func->numLocals();

    std::cout << "----Start StackFrame----" << std::endl;
    std::cout << "Func: " << func->name() << std::endl;
    std::cout << "Num args: " << numArgs << std::endl;
    std::cout << "Num locals: " << numLocals << std::endl;

    long* argsStart = basePtr - 1;
    long* localsStart = basePtr - 1 - numArgs;

    if (numArgs > 0) {
        std::cout << "Args: " << std::endl;
        for (int i = 0; i < numArgs; i++) {
            std::cout << i << ": " << argsStart[-i] << std::endl;
            //std::cout << i << ": " << argsStart[-i] << " (" << func->arguments()[i]->name() << ")" << std::endl;
        }

        std::cout << std::endl;
    }

    if (numLocals > 0) {
        std::cout << "Locals: " << std::endl;
        for (int i = 0; i < numLocals; i++) {
            std::cout << i << ": " << localsStart[-i] << std::endl;
            //std::cout << i << ": " << localsStart[-i] << " (" << func->getLocal(i)->name() << ")" << std::endl;
        }

        std::cout << std::endl;
    }
    
    std::cout << "----End StackFrame----" << std::endl;
}

void rt_pushFunc(Function* func, int instIndex) {
    vmState.pushFunc(func, instIndex);
}

void rt_popFunc() {
    vmState.popFunc();
}

void rt_printStackTrace(long* basePtr, int level) {
    if (level > 50 || basePtr == nullptr) {
        return;
    }

    std::cout << basePtr << " from " << "0x" << std::hex << *basePtr << std::dec << std::endl;
    rt_printStackTrace((long*)*basePtr, level + 1);
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

void rt_printAliveObjects(long* basePtr, Function* func, int instIndex, std::string indentation = "") {
    int numArgs = func->numArgs();
    int numLocals = func->numLocals();
    auto operandTypes = func->instructionOperandTypes.at(instIndex);
    int stackSize = operandTypes.size();

    long* argsStart = basePtr - 1;
    long* localsStart = basePtr - 1 - numArgs;
    long* stackStart = basePtr - 1 - numArgs - numLocals;

    if (numArgs > 0) {
        std::cout << indentation << "Args: " << std::endl;
        for (int i = 0; i < numArgs; i++) {
            std::cout << indentation << i << ": " << argsStart[-i] << " (" << func->arguments()[i]->name() << ")" << std::endl;
        }

        std::cout << std::endl;
    }

    if (numLocals > 0) {
        std::cout << indentation << "Locals: " << std::endl;
        for (int i = 0; i < numLocals; i++) {
            std::cout << indentation << i << ": " << localsStart[-i] << " (" << func->getLocal(i)->name() << ")" << std::endl;
        }

        std::cout << std::endl;
    }

    if (stackSize > 0) {
        std::cout << indentation << "Stack: " << std::endl;
        for (int i = 0; i < stackSize; i++) {
            std::cout << indentation << i << ": " << stackStart[-i] << " (" << operandTypes[i]->name() << ")" << std::endl;
        }
    }
}

void rt_findAliveObjects(long* basePtr, Function* func, int instIndex) {
    int numArgs = func->numArgs();
    int numLocals = func->numLocals();
    auto operandTypes = func->instructionOperandTypes[instIndex];
    int stackSize = operandTypes.size();

    long* argsStart = basePtr - 1;
    long* localsStart = basePtr - 1 - numArgs;
    long* stackStart = basePtr - 1 - numArgs - numLocals;

    if (numArgs > 0) {
        for (int i = 0; i < numArgs; i++) {
            // argsStart[-i];
            // func->arguments().at(i)->name();
        }
    }

    if (numLocals > 0) {
        for (int i = 0; i < numLocals; i++) {
            // localsStart[-i];
            // func->getLocal(i)->name();
        }
    }

    if (stackSize > 0) {
        for (int i = 0; i < stackSize; i++) {
            // stackStart[-i];
            // operandTypes.at(i)->name();
        }
    }
}

void rt_garbageCollect(long* basePtr, Function* func, int instIndex) {
    auto startStr = "-----Start GC in func " + func->name() + " (" + std::to_string(instIndex) + ")-----";
    std::cout << startStr << std::endl;
    //std::cout << "-----Start GC in func " << func->name() << " (inst " << instIndex << ")-----" << std::endl;

    std::cout << "Stack trace: " << std::endl;

    std::cout << func->name() << " (" << instIndex << ")" << std::endl;
    rt_printAliveObjects(basePtr, func, instIndex, "\t");

    int topFuncIndex = 0;
    for (auto callEntry : vmState.callStack()) {
        auto topFunc = callEntry.first;
        auto callPoint = callEntry.second;
        std::cout << topFunc->name() << " (" << callPoint << ")" << std::endl;
        auto callBasePtr = findBasePtr(basePtr, 0, topFuncIndex);
        rt_printAliveObjects(callBasePtr, topFunc, callPoint, "\t");
        topFuncIndex++;
    }

    printTimes('-', startStr.length() / 2 - 3);
    std::cout << "End GC";
    printTimes('-', (startStr.length() + 1) / 2 - 3);
    std::cout << std::endl;
    //std::cout << "---------------End GC---------------" << std::endl;
}

long rt_newArray(Type* type, int size) {
    auto elemSize = TypeSystem::sizeOfType(type);

    int memSize = sizeof(int) + size * elemSize;
    unsigned char* arrayPtr = new unsigned char[memSize];
    memset(arrayPtr, 0, memSize);

    //Add the array to the list of objects
    vmState.newObject(new ArrayHandle(arrayPtr, memSize, type, size));

    //Set the size of the array
    IntToBytes converter;
    converter.IntValue = size;
    arrayPtr[0] = converter.ByteValues[0];
    arrayPtr[1] = converter.ByteValues[1];
    arrayPtr[2] = converter.ByteValues[2];
    arrayPtr[3] = converter.ByteValues[3];

    return (long)arrayPtr;
}

long rt_newObject(Type* type) {
    auto structType = static_cast<StructType*>(type);

    int memSize = vmState.getStructMetadata(structType->structName())->getSize();
    unsigned char* structPtr = new unsigned char[memSize];
    memset(structPtr, 0, memSize);

    //Add the struct to the list of objects
    vmState.newObject(new StructHandle(structPtr, memSize, type));

    return (long)structPtr;
}

void rt_runtimeError(std::string errorMessage) {
    throw std::runtime_error(errorMessage);
}

void rt_arrayOutOfBoundsError() {
    rt_runtimeError("Array index is out of bounds.");
}

void rt_nullReferenceError() {
    rt_runtimeError("Null reference error.");
}