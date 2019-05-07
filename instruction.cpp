#include "instruction.h"
#include <iostream>

// Map instruction string -> subclass e.g. ("add" -> AddInstruction)
map<string, Instruction*> instruction_map;
// Class encapsulating the functions used to transform operands into
// our desired form
TransformOperand *t = new TransformOperand();

void initInstructions(void) {
    // TODO: Get rid of the if statements in makeInstruction and replace it
    // by using instruction_map
    // Initialize instruction_map here
    return;
}

Instruction *makeInstruction(int line_number, LocPair instruction,
                             LocPair operand1, LocPair operand2) {
    Instruction *instr;
    if (string("add").compare(instruction.second) == 0) {
        instr = new AddInstruction(operand1, operand2);
    }
    else if (string("sub").compare(instruction.second) == 0) {
        instr = new SubInstruction(operand1, operand2);
    }
    else {
        // Instruction name does not map to any of our instructions
        string err_msg = "Invalid instruction";
        error(line_number, instruction.first, err_msg);
    }
    instr->line_number = line_number;
    return instr;
}

AddInstruction::AddInstruction(LocPair operand1, LocPair operand2) {
    this->name = "add";
    this->size = 2;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void AddInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (this->line_number, operand1.first, operand1.second);
    string rr = t->transformGeneralRegister
        (this->line_number, operand2.first, operand2.second);
    this->opcode = "000011" + rr.substr(0, 1) + rd + rr.substr(1, rd.size() - 1);
}

void AddInstruction::print(void) {
    cout << this->name
         << "(" << this->operand1.second << " , " << this->operand2.second << ")"
         << " [size = " << this->size << ", opcode = " << this->opcode << "]"
         << endl;
}

SubInstruction::SubInstruction(LocPair operand1, LocPair operand2) {
    this->name = "sub";
    this->size = 2;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

// TODO: Actually implement this
void SubInstruction::createOpcode(void) {
    this->opcode = "0000000000000000";
}

void SubInstruction::print(void) {
    cout << this->name
         << "(" << this->operand1.second << " , " << this->operand2.second << ")"
         << " [size = " << this->size << ", opcode = " << this->opcode << "]"
         << endl;
}
