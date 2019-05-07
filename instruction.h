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

/* Abstract Instruction class that has no operands */
class NoOpInstruction : public Instruction {
public:
    void print(void) {
        cout << getName() << "()"
             << " [size = " << getSize() << ", opcode = " << getOpcode() << "]"
             << endl;
    }
};

/* Abstract Instruction class that has one operand */
class OneOpInstruction : public Instruction {
private:
    LocPair operand;
public:
    OneOpInstruction(LocPair operand) {
        this->operand = operand;
    }

    LocPair getOperand(void) { return this->operand; }

    void print(void) {
        cout << getName()
             << "(" << operand.second << ")"
             << " [size = " << getSize() << ", opcode = " << getOpcode() << "]"
             << endl;
    }
};

/* Abstract Instruction class that has two operands */
class TwoOpInstruction : public Instruction {
private:
    LocPair operand1;
    LocPair operand2;
public:
    TwoOpInstruction(LocPair operand1, LocPair operand2) {
        this->operand1 = operand1;
        this->operand2 = operand2;
    }

    LocPair getOperand1(void) { return this->operand1; }
    LocPair getOperand2(void) { return this->operand2; }

    void print(void) {
        cout << getName()
             << "(" << operand1.second << " , " << operand2.second << ")"
             << " [size = " << getSize() << ", opcode = " << getOpcode() << "]"
             << endl;
    }
};

// Create the instruction_map
void initInstructions(void);
// Create an Instruction subclass object
Instruction *makeInstruction(int line_number, LocPair instruction, LocPair operand1, LocPair operand2);


/* ARITHMETIC AND LOGICAL (ALU) INSTRUCTIONS */

class AddInstruction : public TwoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    AddInstruction(LocPair operand1, LocPair operand2) : TwoOpInstruction(operand1, operand2) {
        name = "add";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class SubInstruction : public TwoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    SubInstruction(LocPair operand1, LocPair operand2) : TwoOpInstruction(operand1, operand2) {
        name = "sub";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class AndInstruction : public TwoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    AndInstruction(LocPair operand1, LocPair operand2) : TwoOpInstruction(operand1, operand2) {
        name = "and";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class OrInstruction : public TwoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    OrInstruction(LocPair operand1, LocPair operand2) : TwoOpInstruction(operand1, operand2) {
        name = "or";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class EorInstruction : public TwoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    EorInstruction(LocPair operand1, LocPair operand2) : TwoOpInstruction(operand1, operand2) {
        name = "eor";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class IncInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    IncInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "inc";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class DecInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    DecInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "dec";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class TstInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    TstInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "tst";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class ClrInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    ClrInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "clr";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class MulInstruction : public TwoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    MulInstruction(LocPair operand1, LocPair operand2) : TwoOpInstruction(operand1, operand2) {
        name = "mul";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};


/* BRANCH INSTRUCTIONS */

class RjmpInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    RjmpInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "rjmp";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class JmpInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    JmpInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "jmp";
        size = 4;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class RcallInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    RcallInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "rcall";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class CallInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    CallInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "call";
        size = 4;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class RetInstruction : public NoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    RetInstruction() {
        name = "ret";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class RetiInstruction : public NoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    RetiInstruction() {
        name = "reti";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class CpInstruction : public TwoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    CpInstruction(LocPair operand1, LocPair operand2) : TwoOpInstruction(operand1, operand2) {
        name = "cp";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class CpiInstruction : public TwoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    CpiInstruction(LocPair operand1, LocPair operand2) : TwoOpInstruction(operand1, operand2) {
        name = "cpi";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class BreqInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    BreqInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "breq";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class BrneInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    BrneInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "brne";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class BrgeInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    BrgeInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "brge";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class BrltInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    BrltInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "brlt";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};


/* DATA TRANSFER INSTRUCTIONS */

class MovInstruction : public TwoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    MovInstruction(LocPair operand1, LocPair operand2) : TwoOpInstruction(operand1, operand2) {
        name = "mov";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class LdiInstruction : public TwoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    LdiInstruction(LocPair operand1, LocPair operand2) : TwoOpInstruction(operand1, operand2) {
        name = "ldi";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class LdsInstruction : public TwoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    LdsInstruction(LocPair operand1, LocPair operand2) : TwoOpInstruction(operand1, operand2) {
        name = "lds";
        size = 4;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class LdInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    LdInstruction(LocPair operand) : OneOpInstruction(operand) {
        // Note that this is the regular ld instruction 
        // (no increment/decrement or displacement)
        name = "ld";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class StsInstruction : public TwoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    StsInstruction(LocPair operand1, LocPair operand2) : TwoOpInstruction(operand1, operand2) {
        name = "sts";
        size = 4;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class StInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    StInstruction(LocPair operand) : OneOpInstruction(operand) {
        // Note that this is the regular st instruction 
        // (no increment/decrement or displacement)
        name = "st";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class InInstruction : public TwoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    InInstruction(LocPair operand1, LocPair operand2) : TwoOpInstruction(operand1, operand2) {
        name = "in";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class OutInstruction : public TwoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    OutInstruction(LocPair operand1, LocPair operand2) : TwoOpInstruction(operand1, operand2) {
        name = "out";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class PushInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    PushInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "push";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class PopInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    PopInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "pop";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};


/* BIT AND BIT_TEST INSTRUCTIONS */

class LslInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    LslInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "lsl";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class LsrInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    LsrInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "lsr";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class AsrInstruction : public OneOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    AsrInstruction(LocPair operand) : OneOpInstruction(operand) {
        name = "asr";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};

class NopInstruction : public NoOpInstruction {
private:
    string name;
    int size;
    string opcode;

public:
    NopInstruction() {
        name = "nop";
        size = 2;
    }
    void createOpcode(void);
    string getName(void) { return this->name; }
    int getSize(void) { return this->size; }
    string getOpcode(void) { return this->opcode; }
};