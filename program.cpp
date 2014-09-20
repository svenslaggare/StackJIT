#include "program.h"
#include "codegenerator.h"
#include "instructions.h"

Function::Function(std::string name, std::vector<Type*> arguments, Type* returnType)
: name(name), arguments(arguments), returnType(returnType) {

}

int Function::numArgs() const {
	return arguments.size();
}

Program::~Program() {
    //Free the functions
    for (auto func : Functions) {
        delete func.second;
    }
}