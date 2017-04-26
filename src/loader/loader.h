#pragma once
#include "../core/instructionset.h"
#include <vector>
#include <string>
#include <unordered_map>

namespace stackjit {
	namespace Loader {
		//The instruction formats
		enum class InstructionFormats : char {
			OpCodeOnly,
			IntData,
			FloatData,
			CharData,
			StringData,
			StringConstantData,
			Call,
			CallInstance,
		};

		//Represents a parsed but not bound instruction.
		class Instruction {
		private:
			//The instruction format
			InstructionFormats mFormat;

		    //The op code
		    OpCodes mOpCode;

		    //Primitive values
		    float mFloatValue;
		    int mIntValue;
		    char mCharValue;
		    std::string mStringValue;

		    //Used by call instructions
		    std::vector<std::string> mCallParameters;

		    //Used by the object instructions
		    std::string mCalledClassType;
		public:
		    //Creates a new instruction
		    Instruction(InstructionFormats format, OpCodes opCode);

			//Returns the instruction format
			InstructionFormats format() const;

			//Returns the OP code
			OpCodes opCode() const;

			//Returns the float value
			float floatValue() const;

			//Returns the int value
			int intValue() const;

			//Returns the char value
			char charValue() const;

			//Returns the string value
			const std::string& stringValue() const;

			//Returns the call parameters
			const std::vector<std::string>& callParameters() const;

			//Returns the type of the called class for object instructions
			const std::string& calledClassType() const;

		    //Creates a new instruction with the given op code
		    static Instruction make(OpCodes opCode);

		    //Creates a new instruction with an int as value
		    static Instruction makeWithInt(OpCodes opCode, int value);

		    //Creates a new instruction with a float as value
		    static Instruction makeWithFloat(OpCodes opCode, float value);

		    //Creates a new instruction with a char as value
		    static Instruction makeWithChar(OpCodes opCode, char value);

		    //Creates a new instruction with a string as the value
		    static Instruction makeWithString(OpCodes opCode, std::string value);

			//Creates a new instruction with a string constant as the value
			static Instruction makeWithStringConstant(OpCodes opCode, std::string value);

		    //Creates a new call instruction
		    static Instruction makeCall(std::string funcName, std::vector<std::string> parameters);

		    //Creates a new call instance instruction
		    static Instruction makeCallInstance(std::string classType, std::string funcName, std::vector<std::string> parameters);

			//Creates a new call virtual instruction
			static Instruction makeCallVirtual(std::string classType, std::string funcName, std::vector<std::string> parameters);

		    //Creates a new create object instruction
		    static Instruction makeNewObject(std::string classType, std::vector<std::string> parameters);
		};

		//Represents an attribute
		class Attribute {
		private:
			std::string mName;
			std::unordered_map<std::string, std::string> mValues;
		public:
			//Creates a new attribute with the given name
			Attribute(std::string name);

			//Returns the name of the attribute
			const std::string& name() const;

			//Returns the values
			const std::unordered_map<std::string, std::string>& values() const;
			std::unordered_map<std::string, std::string>& values();
		};

		//Represents an attributes container
		using AttributeContainer = std::unordered_map<std::string, Attribute>;

		//Represents a function
		class Function {
		private:
			std::string mName;
			std::string mReturnType;
			std::vector<std::string> mParameters;

			bool mIsMemberFunction;
			std::string mClassName;
			std::string mMemberFunctionName;

			bool mIsExternal;

			std::vector<Instruction> mInstructions;
			std::vector<std::string> mLocalTypes;

			AttributeContainer mAttributes;
		public:
			//Creates a new function
			Function();
			Function(std::string name, std::string returnType, const std::vector<std::string>& parameters, bool isExternal = false);

			//Returns the name of the function
			std::string name() const;

			//Returns the return type
			std::string returnType() const;

			//Returns the parameter types
			const std::vector<std::string>& parameters() const;

			//Indicates if the function is an external defined one
			bool isExternal() const;

			//Indicates if the function is a member function
			bool isMemberFunction() const;
			bool& isMemberFunction();

			//Returns the name of the class if member function
			std::string className() const;
			std::string& className();

			//Returns the name of the function if member function
			std::string memberFunctionName() const;
			std::string& memberFunctionName();

			//Returns the instructions
			const std::vector<Instruction>& instructions() const;
			std::vector<Instruction>& instructions();

			//Returns the type of the locals
			const std::vector<std::string>& localTypes() const;
			std::vector<std::string>& localTypes();

			const AttributeContainer& attributes() const;
			AttributeContainer& attributes();

			//Sets the number of locals
			void setNumLocals(int num);

			//Returns the number of locals
			std::size_t numLocals() const;

			//Returns a string representation of the current function
			std::string toString() const;
		};

		//Represents a field in a class
		class Field {
		private:
			std::string mName;
			std::string mType;

			AttributeContainer mAttributes;
		public:
			//Creates a new field
			Field(std::string name, std::string type);

			//Returns the name of the field
			const std::string& name() const;

			//Returns the type of the field
			const std::string& type() const;

			//Returns the attributes
			const AttributeContainer& attributes() const;
			AttributeContainer& attributes();
		};

		//Represents a class
		class Class {
		private:
			const std::string mName;
			std::vector<Field> mFields;
			std::string mParentClassName;

			AttributeContainer mAttributes;
		public:
			//Creates a new class of the given name
			Class(std::string name);
			Class();

			//Returns the name of the class
			const std::string& name() const;

			//Returns the fields
			const std::vector<Field>& fields() const;
			std::vector<Field>& fields();

			//Returns the name of the parent class
			std::string parentClassName() const;
			std::string& parentClassName();

			//Returns the attributes
			const AttributeContainer& attributes() const;
			AttributeContainer& attributes();
		};

		//Represents an assembly
		class Assembly {
		private:
			std::string mName;
			std::vector<Function> mFunctions;
			std::vector<Class> mClasses;
		public:
			//Creates a new assembly with the given name
			Assembly(std::string name);

			//Returns the name of the assembly
			const std::string& name() const;

			//Returns the functions
			const std::vector<Function>& functions() const;
			std::vector<Function>& functions();

			//Returns the classes
			const std::vector<Class>& classes() const;
			std::vector<Class>& classes();
		};

		//Returns the signature for the given function
		std::string getSignature(const Loader::Function& function);
	}
}