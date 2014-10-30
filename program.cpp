#include "program.h"
#include "codegenerator.h"
#include "instructions.h"
#include <stdexcept>

Function::Function(std::string name, std::vector<Type*> arguments, Type* returnType)
: name(name), arguments(arguments), returnType(returnType) {

}

int Function::numArgs() const {
	return arguments.size();
}

int Function::numLocals() const {
	return localTypes.size();
}

void Function::setNumLocals(int count) {
	localTypes.resize(count);
}

Type* Function::getLocal(int index) const {
	return localTypes.at(index);
}

void Function::setLocal(int index, Type* type) {
	if (index >= 0 && index < localTypes.size()) {
		localTypes[index] = type;
	} else {
		throw std::out_of_range("index");
	}
}

Program::~Program() {
    //Free the functions
    for (auto func : functions) {
        delete func.second;
    }
}