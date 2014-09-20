#pragma once
#include "vmstate.h"

//The global state for the VM
static VMState vmState;

//Indicates if debugging is enabled
const bool ENABLE_DEBUG = true;

//Prints type checking if debug is enabled
const bool PRINT_TYPE_CHECKING = false;

//Prints the info about the stack frame if debug is enabled
const bool PRINT_STACK_FRAME = false;

//Indicates if the generated code is outputed as a file
const bool OUTPUT_GENERATED_CODE = false;