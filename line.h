#include <string>
#include "instruction.h"

using namespace std;

class Line {
private:
    int line_number;
    string line_string;
    Instruction *instruction;
public:
    Line(int line_number, string line_string, Instruction *instruction);
    void print(void);

    int getLineNumber(void) { return line_number; }
    string getLineString(void) { return line_string; }
    Instruction *getInstruction(void) { return instruction; }
};

void parseLine(string line, int line_number);
