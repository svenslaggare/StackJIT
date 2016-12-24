#pragma once
#include <string>
#include "../stackjit.h"
#include "../vmstate.h"

namespace stackjit {
	class ManagedFunction;
	class FunctionDefinition;
	class Type;
	class ClassType;
	class ArrayType;

	//Defines the runtime
	namespace Runtime {
		//Returns the vm state
		VMState* vmState();

		//The standard output stream (used for printing from programs, not the VM)
		std::ostream& standardOutputStream();

		//Initializes the runtime using the given VM state
		void initialize(VMState* vmState);

		//Sets the standard output stream
		void setStandardOutputStream(std::ostream& standardOutputStream);

		//Prints the given stack frame
		void printStackFrame(RegisterValue* basePtr, ManagedFunction* func);

		//Prints the given register value
		void printRegister(RegisterValue value);

		//Functions not intended to be called from outside the runtime.
		namespace Internal {
			//Converts the given value to a string
			std::string valueToString(RegisterValue value, const Type* type);

			//Prints the alive objects
			void printAliveObjects(RegisterValue* basePtr, ManagedFunction* func, int instIndex, std::string indentation = "");
		};

		//Compiles the given function
		void compileFunction(ManagedFunction* callee, int callOffset, int checkStart, int checkEnd, FunctionDefinition* funcToCall);

		//Returns the exact address of the given virtual function
		BytePtr getVirtualFunctionAddress(RawClassRef rawClassRef, int index);

		//Tries to collect garbage
		void garbageCollect(RegisterValue* basePtr, ManagedFunction* func, int instIndex, int generation);

		//Creates a new array of the given type and length
		RawArrayRef newArray(const ArrayType* arrayType, int length);

		//Creates a new class of the given type
		RawClassRef newClass(const ClassType* classType);

		//Creates a new string of the given length
		RawClassRef newString(const char* string, int length);

		//Marks the given object card
		void markObjectCard(RawObjectRef rawObjectRef);

		//Stops the execution
		void runtimeError(std::string errorMessage);

		//Signals that an invalid array creation has been made
		void invalidArrayCreation();

		//Signals that an invalid array access has been made
		void arrayOutOfBoundsError();

		//Signals that a null reference has been made
		void nullReferenceError();

		//Signals that the call stack has run out of memory
		void stackOverflow();
	}
}
