#pragma once
#include "compiler.h"

//Represents a compiler for linux
class LinuxCompiler : public Compiler {
public:
	virtual void* allocateMemory(std::size_t size) override;
	virtual void makeExecutableMemory(void* memory, std::size_t size) override;
};