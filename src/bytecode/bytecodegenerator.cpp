#include "bytecodegenerator.h"
#include <algorithm>

namespace stackjit {
	namespace {
		const std::unordered_map<unsigned char, std::string> opCodeTable = {
			{ (unsigned char)OpCodes::NOP,                           "nop" },
			{ (unsigned char)OpCodes::POP,                           "pop" },
			{ (unsigned char)OpCodes::DUPLICATE,                     "dup" },
			{ (unsigned char)OpCodes::ADD,                           "add" },
			{ (unsigned char)OpCodes::SUB,                           "sub" },
			{ (unsigned char)OpCodes::MUL,                           "mul" },
			{ (unsigned char)OpCodes::DIV,                           "div" },
			{ (unsigned char)OpCodes::LOAD_TRUE,                     "ldtrue" },
			{ (unsigned char)OpCodes::LOAD_FALSE,                    "ldfalse" },
			{ (unsigned char)OpCodes::AND,                           "and" },
			{ (unsigned char)OpCodes::OR,                            "or" },
			{ (unsigned char)OpCodes::NOT,                           "not" },
			{ (unsigned char)OpCodes::CONVERT_INT_TO_FLOAT,          "convinttofloat" },
			{ (unsigned char)OpCodes::CONVERT_FLOAT_TO_INT,          "convfloattoint" },
			{ (unsigned char)OpCodes::COMPARE_EQUAL,                 "cmpeq" },
			{ (unsigned char)OpCodes::COMPARE_NOT_EQUAL,             "cmpne" },
			{ (unsigned char)OpCodes::COMPARE_GREATER_THAN,          "cmpgt" },
			{ (unsigned char)OpCodes::COMPARE_GREATER_THAN_OR_EQUAL, "cmpge" },
			{ (unsigned char)OpCodes::COMPARE_LESS_THAN,             "cmplt" },
			{ (unsigned char)OpCodes::COMPARE_LESS_THAN_OR_EQUAL,    "cmple" },
			{ (unsigned char)OpCodes::LOAD_NULL,                     "ldnull" },
			{ (unsigned char)OpCodes::LOAD_ARRAY_LENGTH,             "ldlen" },
			{ (unsigned char)OpCodes::RET,                           "ret" },
			{ (unsigned char)OpCodes::BRANCH_EQUAL,                  "beq" },
			{ (unsigned char)OpCodes::BRANCH_NOT_EQUAL,              "bne" },
			{ (unsigned char)OpCodes::BRANCH_GREATER_THAN,           "bgt" },
			{ (unsigned char)OpCodes::BRANCH_GREATER_THAN_OR_EQUAL,  "bge" },
			{ (unsigned char)OpCodes::BRANCH_LESS_THAN,              "blt" },
			{ (unsigned char)OpCodes::BRANCH_LESS_THAN_OR_EQUAL,     "ble" },
			{ (unsigned char)OpCodes::NEW_ARRAY,                     "newarr" },
			{ (unsigned char)OpCodes::STORE_ELEMENT,                 "stelem" },
			{ (unsigned char)OpCodes::LOAD_ELEMENT,                  "ldelem" },
			{ (unsigned char)OpCodes::STORE_FIELD,                   "stfield" },
			{ (unsigned char)OpCodes::LOAD_FIELD,                    "ldfield" },
			{ (unsigned char)OpCodes::LOAD_INT,                      "ldint" },
			{ (unsigned char)OpCodes::LOAD_FLOAT,                    "ldfloat" },
			{ (unsigned char)OpCodes::LOAD_CHAR,                     "ldchar" },
			{ (unsigned char)OpCodes::CALL,                          "call" },
			{ (unsigned char)OpCodes::CALL_INSTANCE,                 "callinst" },
			{ (unsigned char)OpCodes::CALL_VIRTUAL,                  "callvirt" },
			{ (unsigned char)OpCodes::LOAD_ARG,                      "ldarg" },
			{ (unsigned char)OpCodes::NEW_OBJECT,                    "newobj" },
			{ (unsigned char)OpCodes::BRANCH,                        "br" },
			{ (unsigned char)OpCodes::LOAD_STRING,                   "ldstr" },
			{ (unsigned char)OpCodes::LOAD_LOCAL,                    "ldloc" },
			{ (unsigned char)OpCodes::STORE_LOCAL,                   "stloc" },
		};
	}

	std::string ByteCodeGenerator::escapedString(std::string str) {
		std::string res = "";

		for (char c : str) {
			if (c == '"' || c == '\\') {
				res += "\\";
			}

			res += c;
		}

		return "\"" + res + "\"";
	}

	void ByteCodeGenerator::generateAttributes(std::ostream& stream,
											   const Loader::AttributeContainer& attributes) {
		for (auto& current : attributes) {
			auto& attribute = current.second;
			stream << "\t@" << attribute.name() << "(";

			bool isFirst = true;
			for (auto& keyValue : attribute.values()) {
				if (!isFirst) {
					stream << " ";
				} else {
					isFirst = false;
				}

				stream << keyValue.first << "=" << keyValue.second;
			}

			stream << ")" << std::endl;
		}
	}

	void ByteCodeGenerator::generateFunction(std::ostream& stream, const Loader::Function& function) {
		if (function.isExternal()) {
			stream << "extern " << Loader::getSignature(function) << " " << function.returnType() << std::endl;
		} else {
			if (function.isMemberFunction()) {
				stream << "member ";
			} else {
				stream << "func ";
			}

			stream << Loader::getSignature(function) << " " << function.returnType() << std::endl;

			stream << "{" << std::endl;

			ByteCodeGenerator::generateAttributes(stream, function.attributes());

			if (function.localTypes().size() > 0) {
				stream << "\t.locals " << function.localTypes().size() << std::endl;

				std::size_t i = 0;
				for (auto& local : function.localTypes()) {
					if (local != "") {
						stream << "\t.local " << i << " " << local << std::endl;
					}
					i++;
				}
			}

			for (auto& inst : function.instructions()) {
				auto opCode = opCodeTable.at((unsigned char)inst.opCode());
				std::transform(opCode.begin(), opCode.end(), opCode.begin(), ::toupper);
				stream << "\t" << opCode;

				switch (inst.format()) {
					case Loader::InstructionFormats::OpCodeOnly:
						break;
					case Loader::InstructionFormats::IntData:
						stream << " " << inst.intValue();
						break;
					case Loader::InstructionFormats::FloatData:
						stream << " " << inst.floatValue();
						break;
					case Loader::InstructionFormats::CharData:
						stream << " " << (int)inst.charValue();
						break;
					case Loader::InstructionFormats::StringData:
						stream << " " << inst.stringValue();
						break;
					case Loader::InstructionFormats::StringConstantData:
						stream << " " << escapedString(inst.stringValue());
						break;
					case Loader::InstructionFormats::Call: {
						stream << " " << inst.stringValue();
						stream << "(";
						bool isFirst = true;

						for (auto parameter : inst.callParameters()) {
							if (!isFirst) {
								stream << " ";
							} else {
								isFirst = false;
							}

							stream << parameter;
						}

						stream << ")";
						break;
					}
					case Loader::InstructionFormats::CallInstance: {
						stream << " " << inst.calledClassType() << "::" << inst.stringValue();
						stream << "(";
						bool isFirst = true;

						for (auto parameter : inst.callParameters()) {
							if (!isFirst) {
								stream << " ";
							} else {
								isFirst = false;
							}

							stream << parameter;
						}

						stream << ")";
						break;
					}
				}

				stream << std::endl;
			}

			stream << "}" << std::endl;
		}
	}

	void ByteCodeGenerator::generateClass(std::ostream& stream, const Loader::Class& classDef) {
		stream << "class " << classDef.name()
			   << (classDef.parentClassName() != "" ? (" extends " + classDef.parentClassName()) : "")
			   << std::endl;
		stream << "{" << std::endl;

		generateAttributes(stream, classDef.attributes());

		for (auto& field : classDef.fields()) {
			stream << "\t" << field.name() << " " << field.type() << std::endl;
			generateAttributes(stream, field.attributes());
		}

		stream << "}" << std::endl;
	}
}