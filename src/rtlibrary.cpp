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

union IntFloatConverter {
    int IntValue;
    float FloatValue;
};

void printValue(long value, const Type* type) {
    if (TypeSystem::isReferenceType(type)) {
        if (value == 0) {
            std::cout << "nullref";
        } else {
            std::cout << "0x" << std::hex << value << std::dec;
        }
    } else if (type->name() == "Float") {
        //int floatPattern = 1096149893;
        //float floatValue = *(reinterpret_cast<float*>(&floatPattern));

        std::cout << value;
    } else {
        std::cout << value;
    }

    std::cout << " (" + type->name() + ")";
}

void Runtime::printAliveObjects(long* basePtr, Function* func, int instIndex, std::string indentation) {
    int numArgs = func->numArgs();
    int numLocals = func->numLocals();
    auto operandTypes = func->instructionOperandTypes.at(instIndex);
    int stackSize = operandTypes.size();

    long* argsStart = basePtr - 1;
    long* localsStart = basePtr - 1 - numArgs;
    //long* stackStart = basePtr - numArgs - numLocals - (func->stackSize() / 8);
    //long* stackStart = basePtr - 1 - numArgs - numLocals - (func->stackSize() / 8) + stackSize;
    long* stackStart = basePtr - 1 - (func->stackSize() / 8);

    if (numArgs > 0) {
        std::cout << indentation << "Args: " << std::endl;
        for (int i = 0; i < numArgs; i++) {
            //std::cout << indentation << i << ": " << argsStart[-i] << " (" << func->arguments()[i]->name() << ")" << std::endl;
            std::cout << indentation << i << ": ";
            printValue(argsStart[-i], func->arguments()[i]);
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    if (numLocals > 0) {
        std::cout << indentation << "Locals: " << std::endl;
        for (int i = 0; i < numLocals; i++) {
            //std::cout << indentation << i << ": " << localsStart[-i] << " (" << func->getLocal(i)->name() << ")" << std::endl;
            std::cout << indentation << i << ": ";
            printValue(localsStart[-i], func->getLocal(i));
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    if (stackSize > 0) {
        std::cout << indentation << "Stack: " << std::endl;
        for (int i = 0; i < stackSize; i++) {
            //std::cout << indentation << i << ": " << stackStart[-i] << " (" << operandTypes[i]->name() << ")" << std::endl;
            std::cout << indentation << i << ": ";
            printValue(stackStart[-i], operandTypes[i]);
            std::cout << std::endl;
        }
    }
}

void printObject(ObjectHandle* handle) {
    std::cout 
        << "0x" << std::hex << (long)handle->handle() << std::dec << ": " << handle->size()
        << " bytes (" << handle->type()->name() << ")" << std::endl;
}

void Runtime::markObject(ObjectHandle* handle) {
    if (!handle->isMarked()) {
        if (TypeSystem::isArray(handle->type())) {
            auto arrayHandle = static_cast<ArrayHandle*>(handle);
            auto arrayType = static_cast<const ArrayType*>(handle->type());

            handle->mark();

            //Mark ref elements
            if (TypeSystem::isReferenceType(arrayType->elementType())) {
                long* elemenetsPtr = (long*)(arrayHandle->handle() + 4);

                for (int i = 0; i < arrayHandle->length(); i++) {
                    markValue(elemenetsPtr[i], arrayType->elementType());
                }
            }
        } else if (TypeSystem::isStruct(handle->type())) {
            handle->mark();

            auto structType = static_cast<const StructType*>(handle->type());
            auto structMetadata = vmState.getStructMetadata(structType);

            //Mark ref fields
            for (auto fieldEntry : structMetadata.fields()) {
                auto field = fieldEntry.second;

                if (TypeSystem::isReferenceType(field.type)) {
                    long fieldValue = *((long*)handle->handle() + field.offset);
                    markValue(fieldValue, field.type);
                }
            }
        }
    }
}

void Runtime::markValue(long value, const Type* type) {
    unsigned char* objPtr = (unsigned char*)value;

    //Don't mark nulls
    if (objPtr == nullptr) {
        return;
    }

    if (TypeSystem::isReferenceType(type)) {
        if (vmState.getObjects().count(objPtr) > 0) {
            Runtime::markObject(vmState.getObjects().at(objPtr));
        } else {
            if (vmState.enableDebug) {
                //Due to a bug in the root finding, its possible to mark invalid values.
                std::cout << "Marking invalid object (0x" << std::hex << value << std::dec << ")" << std::endl;
            }
        }
    }
}

void Runtime::markObjects(long* basePtr, Function* func, int instIndex) {
    int numArgs = func->numArgs();
    int numLocals = func->numLocals();
    auto operandTypes = func->instructionOperandTypes.at(instIndex);
    int stackSize = operandTypes.size();

    long* argsStart = basePtr - 1;
    long* localsStart = basePtr - 1 - numArgs;
    long* stackStart = basePtr - 1 - (func->stackSize() / 8);

    if (numArgs > 0) {
        for (int i = 0; i < numArgs; i++) {
            Runtime::markValue(argsStart[-i], func->arguments()[i]);
        }
    }

    if (numLocals > 0) {
        for (int i = 0; i < numLocals; i++) {
            Runtime::markValue(localsStart[-i], func->getLocal(i));
        }
    }

    if (stackSize > 0) {
        for (int i = 0; i < stackSize; i++) {
            Runtime::markValue(stackStart[-i], operandTypes[i]);
        }
    }
}

void Runtime::sweepObjects() {
    std::vector<ObjectHandle*> objectsToRemove;

    for (auto objEntry : vmState.getObjects()) {
        auto obj = objEntry.second;

        if (!obj->isMarked()) {
            objectsToRemove.push_back(obj);

            if (vmState.enableDebug) {
                std::cout << "Deleted object: ";
                printObject(obj);
            }
        } else {
            obj->unmark();
        }
    }

    for (auto obj : objectsToRemove) {
        vmState.deleteObject(obj);
    }
}

void Runtime::garbageCollect(long* basePtr, Function* func, int instIndex) {
    int startStrLength = 0;

    if (vmState.enableDebug) {
        auto startStr = "-----Start GC in func " + func->name() + " (" + std::to_string(instIndex) + ")-----";
        std::cout << startStr << std::endl;
        startStrLength = startStr.length();
    }

    if (vmState.enableDebug) {
        std::cout << "Alive objects: " << std::endl;

        for (auto objEntry : vmState.getObjects()) {
            auto obj = objEntry.second;
            printObject(obj);
        }
    }
    
    if (vmState.enableDebug) {
        std::cout << "Stack trace: " << std::endl;
        std::cout << func->name() << " (" << instIndex << ")" << std::endl;
        Runtime::printAliveObjects(basePtr, func, instIndex, "\t");
    }

    Runtime::markObjects(basePtr, func, instIndex);

    int topFuncIndex = 0;
    for (auto callEntry : vmState.callStack()) {
        auto topFunc = callEntry.first;
        auto callPoint = callEntry.second;
        auto callBasePtr = findBasePtr(basePtr, 0, topFuncIndex);

        if (vmState.enableDebug) {
            std::cout << topFunc->name() << " (" << callPoint << ")" << std::endl;
        }

        Runtime::printAliveObjects(callBasePtr, topFunc, callPoint, "\t");
        Runtime::markObjects(callBasePtr, topFunc, callPoint);

        topFuncIndex++;
    }

    Runtime::sweepObjects();

    if (vmState.enableDebug) {
        printTimes('-', startStrLength / 2 - 3);
        std::cout << "End GC";
        printTimes('-', (startStrLength + 1) / 2 - 3);
        std::cout << std::endl;
    }
}

long Runtime::newArray(Type* elementType, int length) {
    auto elemSize = TypeSystem::sizeOfType(elementType);

    std::size_t memSize = sizeof(int) + length * elemSize;
    unsigned char* arrayPtr = new unsigned char[memSize];
    memset(arrayPtr, 0, memSize);

    //Add the array to the list of objects
    vmState.newObject(new ArrayHandle(arrayPtr, memSize, vmState.getType(TypeSystem::arrayTypeName(elementType)), length));

    //Set the size of the array
    IntToBytes converter;
    converter.IntValue = length;
    arrayPtr[0] = converter.ByteValues[0];
    arrayPtr[1] = converter.ByteValues[1];
    arrayPtr[2] = converter.ByteValues[2];
    arrayPtr[3] = converter.ByteValues[3];

    if (vmState.enableDebug) {
        std::cout
            << "Allocted array (size: " << memSize << " bytes, length: " << length << ", type: " << elementType->name()
            << ") at " << (long)arrayPtr
            << std::endl;
    }

    return (long)arrayPtr;
}

long Runtime::newObject(Type* type) {
    auto structType = static_cast<StructType*>(type);

    std::size_t memSize = vmState.getStructMetadata(structType->structName()).size();
    unsigned char* structPtr = new unsigned char[memSize];
    memset(structPtr, 0, memSize);

    //Add the struct to the list of objects
    vmState.newObject(new StructHandle(structPtr, memSize, type));

    if (vmState.enableDebug) {
        std::cout
            << "Allocted object (size: " << memSize << " bytes, type: " <<  type->name() 
            << ") at " << (long)structPtr
            << std::endl;
    }

    return (long)structPtr;
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