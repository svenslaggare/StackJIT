#include "program.h"
#include "codegenerator.h"
#include "instructions.h"

Program::~Program() {
    //Free the functions
    for (auto func : Functions) {
        delete func.second;
    }
}