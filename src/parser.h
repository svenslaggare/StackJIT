#pragma once
#include "instructionset.h"
#include <vector>
#include <string>
#include <unordered_map>

//The assembly parser
namespace AssemblyParser {
	//The instruction formats
	enum class InstructionFormats : char {
		OpCodeOnly,
		IntData,
		FloatData,
		CharData,
		StrData,
		Call,
		CallInstance,
	};

	//Represents a parsed but not bound instruction.
	struct Instruction {
		//The instruction format
		InstructionFormats format;

	    //The op code
	    OpCodes opCode;

	    //Primitive values
	    float floatValue;
	    int intValue;
	    char charValue;
	    std::string strValue;

	    //Used by call instructions
	    std::vector<std::string> parameters;

	    //Used by the object instructions
	    std::string calledClassType;

	    //Creates a new instruction
	    Instruction();

	    //Creates a new instruction with the given op code
	    static Instruction make(OpCodes opCode);

	    //Creates a new instruction with an int as value
	    static Instruction makeWithInt(OpCodes opCode, int value);

	    //Creates a new instruction with a float as value
	    static Instruction makeWithFloat(OpCodes opCode, float value);

	    //Creates a new instruction with a char as value
	    static Instruction makeWithChar(OpCodes opCode, char value);

	    //Creates a new instruction with a string as the value
	    static Instruction makeWithStr(OpCodes opCode, std::string value);

	    //Creates a new call instruction
	    static Instruction makeCall(std::string funcName, std::vector<std::string> parameters);

	    //Creates a new call instance instruction
	    static Instruction makeCallInstance(std::string classType, std::string funcName, std::vector<std::string> parameters);

	    //Creates a new create object instruction
	    static Instruction makeNewObject(std::string classType, std::vector<std::string> parameters);
	};

	//Represents an attribute
	struct Attribute {
		std::string name;
		std::unordered_map<std::string, std::string> values;
	};

	//Represents an attributes container
	struct AttributeContainer {
		std::unordered_map<std::string, Attribute> attributes;
	};

	//Represents a function
	struct Function {
		std::string name;
		std::string returnType;
		std::vector<std::string> parameters;

		bool isMemberFunction;
		std::string className;
		std::string memberFunctionName;

		bool isExternal;

		std::vector<Instruction> instructions;
		std::vector<std::string> localTypes;

		AttributeContainer attributes;

		//Creates a new function
		Function();

		//Sets the number of locals
		void setNumLocals(int num);

		//Returns the number of locals
		std::size_t numLocals() const;
	};

	//Represents a field in a class
	struct Field {
		std::string name;
		std::string type;

		AttributeContainer attributes;
	};

	//Represents a class
	struct Class {
		std::string name;
		std::vector<Field> fields;

		AttributeContainer attributes;

		//Creates a new class
		Class();
	};

	//Represents an assembly
	struct Assembly {
		std::vector<Function> functions;
		std::vector<Class> classes;
	};

	//Returns the signature for the given function
	std::string getSignature(const AssemblyParser::Function& function);

	//Tokenizes from the given stream
	std::vector<std::string> tokenize(std::istream& stream);
	
	//Parses the given tokens into the given assembly
	void parseTokens(const std::vector<std::string>& tokens, AssemblyParser::Assembly& assembly);
}