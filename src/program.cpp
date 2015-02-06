#include "program.h"
#include "function.h"

Program::Program() {

}

Program::~Program() {
    //Free the functions
    for (auto func : functions) {
        delete func.second;
    }
}