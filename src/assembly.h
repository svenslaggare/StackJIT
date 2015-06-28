#pragma once
#include <string>
#include <unordered_map>

class Function;

//The type of the assembly
enum class AssemblyType {
	//The assembly is a program. This requires an entry point (main function)
	Program,
	//The assembly is a library. A library cannot be executed.
	Library
};

//Represents an assembly
class Assembly {
private:
	AssemblyType mType;
public:
	//The functions defined in the assembly
    std::unordered_map<std::string, Function*> functions;

    //Creates a new assembly
    Assembly(AssemblyType type);
    ~Assembly();

    //Prevent the assembly from being copied
    Assembly(const Assembly&) = delete;
    Assembly& operator=(const Assembly&) = delete;

    //Move
    Assembly(Assembly&& other);
    Assembly& operator=(Assembly&& rhs);

    //Returns the type of the assembly
    AssemblyType type() const;
};