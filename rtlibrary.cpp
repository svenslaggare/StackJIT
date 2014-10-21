#include <iostream>
#include <string.h>

#include "rtlibrary.h"
#include "amd64.h"
#include "objects.h"
#include "vmstate.h"
#include "program.h"
#include "type.h"

extern VMState vmState;

void rt_printStackFrame(long* basePtr, Function* func) {
    int numArgs = func->numArgs();
    int numLocals = func->numLocals;

    std::cout << "----Start StackFrame----" << std::endl;
    std::cout << "Func: " << func->name << std::endl;
    std::cout << "Num args: " << numArgs << std::endl;
    std::cout << "Num locals: " << numLocals << std::endl;

    long* argsStart = basePtr - 1;
    long* localsStart = basePtr - 1 - numArgs;

    if (numArgs > 0) {
        std::cout << std::endl;
        std::cout << "Args: " << std::endl;
        for (int i = 0; i < numArgs; i++) {
            std::cout << i << ": " << argsStart[-i] << std::endl;
        }
    }

    std::cout << std::endl;

    std::cout << "Locals: " << std::endl;
    for (int i = 0; i < numLocals; i++) {
        std::cout << i << ": " << localsStart[-i] << std::endl;
    }
    
    std::cout << "----End StackFrame----" << std::endl;
}

long rt_newArray(Type* type, int size) {
    auto elemSize = TypeSystem::sizeOfType(type);

    int memSize = sizeof(int) + size * elemSize;
    unsigned char* arrayPtr = new unsigned char[memSize];
    memset(arrayPtr, 0, memSize);

    //Add the array to the list of objects
    vmState.Objects.push_back(new ArrayHandle(arrayPtr, memSize, type, size));

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
    //std::cout << "Created object of type: " << type->name() << std::endl;
    auto structType = static_cast<StructType*>(type);

    int memSize = vmState.getStructMetadata(structType->structName())->getSize();
    unsigned char* structPtr = new unsigned char[memSize];
    memset(structPtr, 0, memSize);

    //Add the struct to the list of objects
    vmState.Objects.push_back(new StructHandle(structPtr, memSize, type));

    return (long)structPtr;
}

void rt_runtimeError(std::string errorMessage) {
    throw std::runtime_error(errorMessage);
}

void rt_arrayOutOfBoundsError() {
    rt_runtimeError("Array index is out of bounds.");
}