// Strings are returned by value so many copies will be made (memory overhead)
#include <string>
#include <map>
#include "helper.h"

#define MAX_INSTRUCTION_LENGTH 6 // Longest operand (FMULSU) is 6 chars
#define OPERAND_SIZE 16          // AVR assembly uses 16-bit operands

using namespace std;

/* Abstract Instruction class */
class Instruction {
public:
    // Pure virtual functions
    virtual void createOpcode(void) = 0;
    virtual void print(void) = 0;

    // Name of instruction
    virtual string getName(void) = 0;
    // Size (in bytes) of the instruction
    virtual int getSize(void) = 0;
    // Bit representation of opcode in a string
    virtual string getOpcode(void) = 0;
};

// Create the instruction_map
void initInstructions(void);
// Create an Instruction subclass object
Instruction *makeInstruction(int line_number, LocPair instruction, LocPair operand1, LocPair operand2);

class AddInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand1;
    LocPair operand2;
    string opcode;

public:
    AddInstruction(LocPair operand1, LocPair operand2);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class SubInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand1;
    LocPair operand2;
    string opcode;

public:
    SubInstruction(LocPair operand1, LocPair operand2);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};
