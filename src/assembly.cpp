#include "assembly.h"
#include "function.h"

Assembly::Assembly(AssemblyType type)
	: mType(type) {

}

Assembly::~Assembly() {
    //Free the functions
    for (auto func : functions) {
        delete func.second;
    }
}

Assembly::Assembly(Assembly&& other)
	: functions(std::move(other.functions)) {

}

Assembly& Assembly::operator=(Assembly&& rhs) {
	functions = std::move(rhs.functions);
	return *this;
}

AssemblyType Assembly::type() const {
	return mType;
}