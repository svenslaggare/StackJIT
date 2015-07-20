#pragma once
//The list of op codes
enum class OpCodes : unsigned char {
	NOP,
	LOAD_INT,
	LOAD_FLOAT,
	LOAD_CHAR,
	POP,
	ADD,
	SUB,
	MUL,
	DIV,
	PUSH_TRUE,
	PUSH_FALSE,
	AND,
	OR,
	NOT,
	CONVERT_INT_TO_FLOAT,
	CONVERT_FLOAT_TO_INT,
	COMPARE_EQUAL,
	COMPARE_NOT_EQUAL,
	COMPARE_GREATER_THAN,
	COMPARE_GREATER_THAN_OR_EQUAL,
	COMPARE_LESS_THAN,
	COMPARE_LESS_THAN_OR_EQUAL,
	LOAD_LOCAL,
	STORE_LOCAL,
	CALL,
	CALL_INSTANCE,
	RET,
	LOAD_ARG,
	BRANCH,
	BRANCH_EQUAL,
	BRANCH_NOT_EQUAL,
	BRANCH_GREATER_THAN,
	BRANCH_GREATER_THAN_OR_EQUAL,
	BRANCH_LESS_THAN,
	BRANCH_LESS_THAN_OR_EQUAL,
	PUSH_NULL,
	NEW_ARRAY,
	LOAD_ELEMENT,
	STORE_ELEMENT,
	LOAD_ARRAY_LENGTH,
	NEW_OBJECT,
	LOAD_FIELD,
	STORE_FIELD,
	LOAD_STRING
};