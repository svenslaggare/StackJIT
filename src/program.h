#pragma once
#include <string>
#include <map>

class Function;

//Represents a program
struct Program {
    std::map<std::string, Function*> functions;
    ~Program();
};