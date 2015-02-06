#pragma once
#include <string>
#include <unordered_map>

class Function;

//Represents a program
struct Program {
    std::unordered_map<std::string, Function*> functions;

    //Creates a new program
    Program();
    ~Program();

    //Prevent the program from being copied
    Program(const Program&) = delete;
    Program& operator=(const Program&) = delete;
};