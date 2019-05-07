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
    int line_number;
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


/* ARITHMETIC AND LOGICAL (ALU) INSTRUCTIONS */

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

class AndInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand1;
    LocPair operand2;
    string opcode;

public:
    AndInstruction(LocPair operand1, LocPair operand2);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class OrInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand1;
    LocPair operand2;
    string opcode;

public:
    OrInstruction(LocPair operand1, LocPair operand2);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class EorInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand1;
    LocPair operand2;
    string opcode;

public:
    EorInstruction(LocPair operand1, LocPair operand2);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class IncInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    IncInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class DecInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    DecInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class TstInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    TstInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class ClrInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    ClrInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class MulInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand1;
    LocPair operand2;
    string opcode;

public:
    MulInstruction(LocPair operand1, LocPair operand2);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};


/* BRANCH INSTRUCTIONS */

class RjmpInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    RjmpInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class JmpInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    JmpInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class RcallInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    RcallInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class CallInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    CallInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class RetInstruction : public Instruction {
private:
    string name;
    int size;
    string opcode;

public:
    RetInstruction(void);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class RetiInstruction : public Instruction {
private:
    string name;
    int size;
    string opcode;

public:
    RetiInstruction(void);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class CpInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand1;
    LocPair operand2;
    string opcode;

public:
    CpInstruction(LocPair operand1, LocPair operand2);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class CpiInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand1;
    LocPair operand2;
    string opcode;

public:
    CpiInstruction(LocPair operand1, LocPair operand2);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class BreqInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    BreqInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class BrneInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    BrneInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class BrgeInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    BrgeInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class BrltInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    BrltInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};


/* DATA TRANSFER INSTRUCTIONS */

class MovInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand1;
    LocPair operand2;
    string opcode;

public:
    MovInstruction(LocPair operand1, LocPair operand2);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class LdiInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand1;
    LocPair operand2;
    string opcode;

public:
    LdiInstruction(LocPair operand1, LocPair operand2);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class LdsInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand1;
    LocPair operand2;
    string opcode;

public:
    LdsInstruction(LocPair operand1, LocPair operand2);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class LdInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    LdInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class StsInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand1;
    LocPair operand2;
    string opcode;

public:
    StsInstruction(LocPair operand1, LocPair operand2);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class StInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    StInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class InInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand1;
    LocPair operand2;
    string opcode;

public:
    InInstruction(LocPair operand1, LocPair operand2);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class OutInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand1;
    LocPair operand2;
    string opcode;

public:
    OutInstruction(LocPair operand1, LocPair operand2);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class PushInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    PushInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class PopInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    PopInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};


/* BIT AND BIT_TEST INSTRUCTIONS */

class LslInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    LslInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class LsrInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    LsrInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class AsrInstruction : public Instruction {
private:
    string name;
    int size;
    LocPair operand;
    string opcode;

public:
    AsrInstruction(LocPair operand);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class NopInstruction : public Instruction {
private:
    string name;
    int size;
    string opcode;

public:
    NopInstruction(void);
    void createOpcode(void);
    void print(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};