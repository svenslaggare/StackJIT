#include <iostream>
#include <string.h>
#include <sys/mman.h>

#include <vector>

enum OpCodes
{
    PUSH_INT,
    ADD,
    SUB,
    MUL,
    DIV,
    LOAD_LOCAL,
    STORE_LOCAL
};

struct Instruction {
    OpCodes OpCode;
    int Value;
};

const int NUM_LOCALS = 8;

union IntToBytes {
    int IntValue;
    unsigned char ByteValues[4];
};

union LongToBytes {
    long LongValue;
    unsigned char ByteValues[8];
};

Instruction makeInstruction(OpCodes opCode) {
    Instruction inst;
    inst.OpCode = opCode;
    return inst;
}

Instruction makePushInt(int value) {
    Instruction inst;
    inst.OpCode = OpCodes::PUSH_INT;
    inst.Value = value;
    return inst;
}

Instruction makeLoadLocal(int local) {
    Instruction inst;
    inst.Value = local;
    inst.OpCode = OpCodes::LOAD_LOCAL;
    return inst;
}

Instruction makeStoreLocal(int local) {
    Instruction inst;
    inst.Value = local;
    inst.OpCode = OpCodes::STORE_LOCAL;
    return inst;
}

std::vector<std::string> tokenizeInput() {
    std::vector<std::string> tokens;
    std::string token;

    char c = ' ';

    while (true) {
        c = getchar();

        if (c == EOF) {
            break;
        }

        if (isspace(c)) {
            tokens.push_back(token);
            token = "";
        } else {
            token += c;
        }
    }

    tokens.push_back(token);

    return tokens;
}

void parseTokens(const std::vector<std::string>& tokens, std::vector<Instruction>& instructions) {
    for (int i = 0; i < tokens.size(); i++) {
        std::string current = tokens[i];

        if (current == "PUSH") {
            int value = stoi(tokens[i + 1]);
            instructions.push_back(makePushInt(value));
        }

        if (current == "ADD") {
            instructions.push_back(makeInstruction(OpCodes::ADD));
        }

        if (current == "LDLOC") {
            int local = stoi(tokens[i + 1]);
            instructions.push_back(makeLoadLocal(local));
        }

        if (current == "STLOC") {
            int local = stoi(tokens[i + 1]);
            instructions.push_back(makeStoreLocal(local));
        }
    }
}

int main(int argc, char* argv[]) {
    std::vector<Instruction> input;
    std::vector<unsigned char> generatedCode;
    int locals[NUM_LOCALS] = {0};
    locals[0] = 1337;
    locals[1] = 0;

    //Tokenize the input
    auto tokens = tokenizeInput();

    //Parse it
    parseTokens(tokens, input);

    //Generate the code for the program
    for (auto current : input) {
        switch (current.OpCode) {
            case OpCodes::PUSH_INT:
                //An operand, push the value
                generatedCode.push_back(0x68); //push <value>

                //Convert the int to four bytes
                IntToBytes converter;
                converter.IntValue = current.Value;
                generatedCode.push_back(converter.ByteValues[0]);
                generatedCode.push_back(converter.ByteValues[1]);
                generatedCode.push_back(converter.ByteValues[2]);
                generatedCode.push_back(converter.ByteValues[3]);
                break;
            case OpCodes::ADD:
            case OpCodes::SUB:
            case OpCodes::MUL:
            case OpCodes::DIV:
                //Pop 2 operands
                generatedCode.push_back(0x59); //pop ecx
                generatedCode.push_back(0x58); //pop eax

                //Apply the operator
                switch (current.OpCode) {
                    case OpCodes::ADD:
                        generatedCode.push_back(0x01); //add eax, ecx
                        generatedCode.push_back(0xc8);
                        break;
                    case OpCodes::SUB:
                        generatedCode.push_back(0x29); //sub eax, ecx
                        generatedCode.push_back(0xc8);
                        break;
                    case OpCodes::MUL:
                        generatedCode.push_back(0x0f); //imul eax, ecx
                        generatedCode.push_back(0xaf);
                        generatedCode.push_back(0xc1);
                        break;
                    case OpCodes::DIV:
                        generatedCode.push_back(0xf7); //idiv ecx
                        generatedCode.push_back(0xf9);
                        break;
                    default:
                        break;
                }

                //Push the result
                generatedCode.push_back(0x50); //push eax
                break;
            case OpCodes::LOAD_LOCAL:
                {
                    //Load eax with the given local
                    long localsAddr = (long)(&locals[0 + current.Value]);

                    LongToBytes converter;
                    converter.LongValue = localsAddr;

                    generatedCode.push_back(0xa1); //mov eax, [<int>]
                    generatedCode.push_back(converter.ByteValues[0]);
                    generatedCode.push_back(converter.ByteValues[1]);
                    generatedCode.push_back(converter.ByteValues[2]);
                    generatedCode.push_back(converter.ByteValues[3]);
                    generatedCode.push_back(converter.ByteValues[4]);
                    generatedCode.push_back(converter.ByteValues[5]);
                    generatedCode.push_back(converter.ByteValues[6]);
                    generatedCode.push_back(converter.ByteValues[7]);

                    //Push the loaded value
                    generatedCode.push_back(0x50); //push eax
                }
                break;
            case OpCodes::STORE_LOCAL:
                {
                    //Pop the top operand
                    generatedCode.push_back(0x58); //pop eax

                    //Store eax at the given local
                    long localsAddr = (long)(&locals[0 + current.Value]);

                    LongToBytes converter;
                    converter.LongValue = localsAddr;

                    generatedCode.push_back(0xa3); //mov [<int>], eax
                    generatedCode.push_back(converter.ByteValues[0]);
                    generatedCode.push_back(converter.ByteValues[1]);
                    generatedCode.push_back(converter.ByteValues[2]);
                    generatedCode.push_back(converter.ByteValues[3]);
                    generatedCode.push_back(converter.ByteValues[4]);
                    generatedCode.push_back(converter.ByteValues[5]);
                    generatedCode.push_back(converter.ByteValues[6]);
                    generatedCode.push_back(converter.ByteValues[7]);
                }
                break;
            default:
                break;
        }
    }

    generatedCode.push_back(0x58); //pop eax
    generatedCode.push_back(0xc3); //ret

    unsigned char* code = generatedCode.data();
    int length = generatedCode.size();

    // Allocate writable/executable memory.
    // Note: real programs should not map memory both writable
    // and executable because it is a security risk.
    void *mem = mmap(NULL, length, PROT_WRITE | PROT_EXEC,
        MAP_ANON | MAP_PRIVATE, -1, 0);
    memcpy(mem, code, length);

    //Convert the generated code to a function pointer
    int (*program)() = (int (*)())mem;

    //Execute the program
    std::cout << "Program output: " << std::endl;
    std::cout << program() << std::endl;

    std::cout << std::endl;
    std::cout << "Locals: " << std::endl;

    for (int i = 0; i < NUM_LOCALS; i++) {
        std::cout << i << ": " << locals[i] << std::endl;
    }

    return 0;
}