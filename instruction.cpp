#include "as.h"
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

    // Arithmetic and Logic (ALU) instructions
    if (string("add").compare(instruction.second) == 0)
        instr = new AddInstruction(operand1, operand2);
    else if (string("sub").compare(instruction.second) == 0)
        instr = new SubInstruction(operand1, operand2);
    else if (string("and").compare(instruction.second) == 0)
        instr = new AndInstruction(operand1, operand2);
    else if (string("or").compare(instruction.second) == 0)
        instr = new OrInstruction(operand1, operand2);
    else if (string("eor").compare(instruction.second) == 0)
        instr = new EorInstruction(operand1, operand2);
    else if (string("inc").compare(instruction.second) == 0)
        instr = new IncInstruction(operand1);
    else if (string("dec").compare(instruction.second) == 0)
        instr = new DecInstruction(operand1);
    else if (string("tst").compare(instruction.second) == 0)
        instr = new TstInstruction(operand1);
    else if (string("clr").compare(instruction.second) == 0)
        instr = new ClrInstruction(operand1);
    else if (string("mul").compare(instruction.second) == 0)
        instr = new MulInstruction(operand1, operand2);
    
    // Data Transfer Instructions
    else if (string("rjmp").compare(instruction.second) == 0)
        instr = new RjmpInstruction(operand1);
    else if (string("jmp").compare(instruction.second) == 0)
        instr = new JmpInstruction(operand1);
    else if (string("rcall").compare(instruction.second) == 0)
        instr = new RcallInstruction(operand1);
    else if (string("call").compare(instruction.second) == 0)
        instr = new CallInstruction(operand1);
    else if (string("ret").compare(instruction.second) == 0)
        instr = new RetInstruction();
    else if (string("reti").compare(instruction.second) == 0)
        instr = new RetiInstruction();
    else if (string("cp").compare(instruction.second) == 0)
        instr = new CpInstruction(operand1, operand2);
    else if (string("cpi").compare(instruction.second) == 0)
        instr = new CpiInstruction(operand1, operand2);
    else if (string("breq").compare(instruction.second) == 0)
        instr = new BreqInstruction(operand1);
    else if (string("brne").compare(instruction.second) == 0)
        instr = new BrneInstruction(operand1);
    else if (string("brge").compare(instruction.second) == 0)
        instr = new BrgeInstruction(operand1);
    else if (string("brlt").compare(instruction.second) == 0)
        instr = new BrltInstruction(operand1);
    
    // Data Transfer Instructions
    else if (string("mov").compare(instruction.second) == 0)
        instr = new MovInstruction(operand1, operand2);
    else if (string("ldi").compare(instruction.second) == 0)
        instr = new LdiInstruction(operand1, operand2);
    else if (string("lds").compare(instruction.second) == 0)
        instr = new LdsInstruction(operand1, operand2);
    else if (string("ld").compare(instruction.second) == 0)
        instr = new LdInstruction(operand1);
    else if (string("sts").compare(instruction.second) == 0)
        instr = new StsInstruction(operand1, operand2);
    else if (string("st").compare(instruction.second) == 0)
        instr = new StInstruction(operand1);
    else if (string("in").compare(instruction.second) == 0)
        instr = new InInstruction(operand1, operand2);
    else if (string("out").compare(instruction.second) == 0)
        instr = new OutInstruction(operand1, operand2);
    else if (string("push").compare(instruction.second) == 0)
        instr = new PushInstruction(operand1);
    else if (string("pop").compare(instruction.second) == 0)
        instr = new PopInstruction(operand1);

    // Bit and Bit-Test Instructions
    else if (string("lsl").compare(instruction.second) == 0)
        instr = new LslInstruction(operand1);
    else if (string("lsr").compare(instruction.second) == 0)
        instr = new LsrInstruction(operand1);
    else if (string("asr").compare(instruction.second) == 0)
        instr = new AsrInstruction(operand1);
    else if (string("nop").compare(instruction.second) == 0)
        instr = new NopInstruction();
    
    else {
        // Instruction name does not map to any of our instructions
        string err_msg = "Invalid instruction";
        error(line_number, instruction.first, err_msg);
    }
    instr->line_number = line_number;
    return instr;
}


/* ARITHMETIC AND LOGICAL (ALU) INSTRUCTIONS */

void AddInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand1().first, getOperand1().second);
    string rr = t->transformGeneralRegister
        (line_number, getOperand2().first, getOperand2().second);
    opcode = "000011" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void SubInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand1().first, getOperand1().second);
    string rr = t->transformGeneralRegister
        (line_number, getOperand2().first, getOperand2().second);
    opcode = "000110" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void AndInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand1().first, getOperand1().second);
    string rr = t->transformGeneralRegister
        (line_number, getOperand2().first, getOperand2().second);
    opcode = "001000" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void OrInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand1().first, getOperand1().second);
    string rr = t->transformGeneralRegister
        (line_number, getOperand2().first, getOperand2().second);
    opcode = "001010" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void EorInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand1().first, getOperand1().second);
    string rr = t->transformGeneralRegister
        (line_number, getOperand2().first, getOperand2().second);
    opcode = "001001" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void IncInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand().first, getOperand().second);
    opcode = "1001010" + rd + "0011";
}

void DecInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand().first, getOperand().second);
    opcode = "1001010" + rd + "1010";
}

void TstInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand().first, getOperand().second);
    opcode = "001000" + rd.substr(0, 1) + rd + rd.substr(1, 4);
}

void ClrInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand().first, getOperand().second);
    opcode = "001001" + rd.substr(0, 1) + rd + rd.substr(1, 4);
}

void MulInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand1().first, getOperand1().second);
    string rr = t->transformGeneralRegister
        (line_number, getOperand2().first, getOperand2().second);
    opcode = "100111" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}


/* BRANCH INSTRUCTIONS */

void RjmpInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(getOperand().second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, getOperand().first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string offset = t->transformLabel
        (line_number, getOperand().first, it->second, 12, current_PC);
    opcode = "1100" + offset;
}

void JmpInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(getOperand().second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, getOperand().first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string address = t->transformLabel
        (line_number, getOperand().first, it->second, 22, 0);
    opcode = "1001010" + address.substr(0, 5) + "110" + address.substr(5, 17);
}

void RcallInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(getOperand().second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, getOperand().first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string offset = t->transformLabel
        (line_number, getOperand().first, it->second, 12, current_PC);
    opcode = "1101" + offset;
}

void CallInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(getOperand().second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, getOperand().first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string address = t->transformLabel
        (line_number, getOperand().first, it->second, 22, 0);
    opcode = "1001010" + address.substr(0, 5) + "111" + address.substr(5, 17);
}

void RetInstruction::createOpcode(void) {
    opcode = "1001010100001000";
}

void RetiInstruction::createOpcode(void) {
    opcode = "1001010100011000";
}

void CpInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand1().first, getOperand1().second);
    string rr = t->transformGeneralRegister
        (line_number, getOperand2().first, getOperand2().second);
    opcode = "000101" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void CpiInstruction::createOpcode(void) {
    string rd = t->transformUpperRegister
        (line_number, getOperand1().first, getOperand1().second);
    string immed = t->transformUnsignedImmediate
        (line_number, getOperand2().first, getOperand2().second, 8);
    opcode = "0011" + immed.substr(0, 4) + rd + immed.substr(4, 4);
}

void BreqInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(getOperand().second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, getOperand().first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string offset = t->transformLabel
        (line_number, getOperand().first, it->second, 6, current_PC);
    opcode = "111100" + offset + "001";
}

void BrneInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(getOperand().second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, getOperand().first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string offset = t->transformLabel
        (line_number, getOperand().first, it->second, 6, current_PC);
    opcode = "111101" + offset + "001";
}

void BrgeInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(getOperand().second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, getOperand().first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string offset = t->transformLabel
        (line_number, getOperand().first, it->second, 6, current_PC);
    opcode = "111101" + offset + "100";
}

void BrltInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(getOperand().second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, getOperand().first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string offset = t->transformLabel
        (line_number, getOperand().first, it->second, 6, current_PC);
    opcode = "111100" + offset + "100";
}


/* DATA TRANSFER INSTRUCTIONS */

void MovInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand1().first, getOperand1().second);
    string rr = t->transformGeneralRegister
        (line_number, getOperand2().first, getOperand2().second);
    opcode = "001011" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void LdiInstruction::createOpcode(void) {
    string rd = t->transformUpperRegister
        (line_number, getOperand1().first, getOperand1().second);
    string immed = t->transformUnsignedImmediate
        (line_number, getOperand2().first, getOperand2().second, 8);
    opcode = "1110" + immed.substr(0, 4) + rd + immed.substr(4, 4);
}

void LdsInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand1().first, getOperand1().second);
    string immed = t->transformUnsignedImmediate
        (line_number, getOperand2().first, getOperand2().second, 16);
    opcode = "1001000" + rd + "0000" + immed;
}

void LdInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand().first, getOperand().second);
    opcode = "1001000" + rd + "1100";
}

void StsInstruction::createOpcode(void) {
    string immed = t->transformUnsignedImmediate
        (line_number, getOperand1().first, getOperand1().second, 16);
    string rd = t->transformGeneralRegister
        (line_number, getOperand2().first, getOperand2().second);
    opcode = "1001001" + rd + "0000" + immed;
}

void StInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand().first, getOperand().second);
    opcode = "1001001" + rd + "1100";
}

void InInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand1().first, getOperand1().second);
    string io = t->transformUnsignedImmediate
        (line_number, getOperand2().first, getOperand2().second, 6);
    opcode = "10110" + io.substr(0, 2) + rd + io.substr(2, 4);
}

void OutInstruction::createOpcode(void) {
    string io = t->transformUnsignedImmediate
        (line_number, getOperand1().first, getOperand1().second, 6);
    string rr = t->transformGeneralRegister
        (line_number, getOperand2().first, getOperand2().second);
    opcode = "10111" + io.substr(0, 2) + rr + io.substr(2, 4);
}

void PushInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand().first, getOperand().second);
    opcode = "1001001" + rd + "1111";
}

void PopInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand().first, getOperand().second);
    opcode = "1001000" + rd + "1111";
}


/* BIT AND BIT_TEST INSTRUCTIONS */

void LslInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand().first, getOperand().second);
    opcode = "000011" + rd.substr(0, 1) + rd + rd.substr(1, 4);
}

void LsrInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand().first, getOperand().second);
    opcode = "1001010" + rd + "0110";
}

void AsrInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, getOperand().first, getOperand().second);
    opcode = "1001010" + rd + "0101";
}

void NopInstruction::createOpcode(void) {
    opcode = "0000000000000000";
}