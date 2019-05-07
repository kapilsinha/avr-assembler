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

AddInstruction::AddInstruction(LocPair operand1, LocPair operand2) {
    name = "add";
    size = 2;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void AddInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand1.first, operand1.second);
    string rr = t->transformGeneralRegister
        (line_number, operand2.first, operand2.second);
    opcode = "000011" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void AddInstruction::print(void) {
    cout << name
         << "(" << operand1.second << " , " << operand2.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

SubInstruction::SubInstruction(LocPair operand1, LocPair operand2) {
    name = "sub";
    size = 2;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void SubInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand1.first, operand1.second);
    string rr = t->transformGeneralRegister
        (line_number, operand2.first, operand2.second);
    opcode = "000110" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void SubInstruction::print(void) {
    cout << name
         << "(" << operand1.second << " , " << operand2.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

AndInstruction::AndInstruction(LocPair operand1, LocPair operand2) {
    name = "and";
    size = 2;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void AndInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand1.first, operand1.second);
    string rr = t->transformGeneralRegister
        (line_number, operand2.first, operand2.second);
    opcode = "001000" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void AndInstruction::print(void) {
    cout << name
         << "(" << operand1.second << " , " << operand2.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

OrInstruction::OrInstruction(LocPair operand1, LocPair operand2) {
    name = "or";
    size = 2;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void OrInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand1.first, operand1.second);
    string rr = t->transformGeneralRegister
        (line_number, operand2.first, operand2.second);
    opcode = "001010" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void OrInstruction::print(void) {
    cout << name
         << "(" << operand1.second << " , " << operand2.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

EorInstruction::EorInstruction(LocPair operand1, LocPair operand2) {
    name = "eor";
    size = 2;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void EorInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand1.first, operand1.second);
    string rr = t->transformGeneralRegister
        (line_number, operand2.first, operand2.second);
    opcode = "001001" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void EorInstruction::print(void) {
    cout << name
         << "(" << operand1.second << " , " << operand2.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

IncInstruction::IncInstruction(LocPair operand) {
    name = "inc";
    size = 2;
    this->operand = operand;
}

void IncInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand.first, operand.second);
    opcode = "1001010" + rd + "0011";
}

void IncInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

DecInstruction::DecInstruction(LocPair operand) {
    name = "dec";
    size = 2;
    this->operand = operand;
}

void DecInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand.first, operand.second);
    opcode = "1001010" + rd + "1010";
}

void DecInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

TstInstruction::TstInstruction(LocPair operand) {
    name = "tst";
    size = 2;
    this->operand = operand;
}

void TstInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand.first, operand.second);
    opcode = "001000" + rd.substr(0, 1) + rd + rd.substr(1, 4);
}

void TstInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

ClrInstruction::ClrInstruction(LocPair operand) {
    name = "clr";
    size = 2;
    this->operand = operand;
}

void ClrInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand.first, operand.second);
    opcode = "001001" + rd.substr(0, 1) + rd + rd.substr(1, 4);
}

void ClrInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

MulInstruction::MulInstruction(LocPair operand1, LocPair operand2) {
    name = "mul";
    size = 2;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void MulInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand1.first, operand1.second);
    string rr = t->transformGeneralRegister
        (line_number, operand2.first, operand2.second);
    opcode = "100111" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void MulInstruction::print(void) {
    cout << name
         << "(" << operand1.second << " , " << operand2.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}


/* BRANCH INSTRUCTIONS */

RjmpInstruction::RjmpInstruction(LocPair operand) {
    name = "rjmp";
    size = 2;
    this->operand = operand;
}

void RjmpInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(operand.second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, operand.first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string offset = t->transformLabel
        (line_number, operand.first, it->second, 12, current_PC);
    opcode = "1100" + offset;
}

void RjmpInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

JmpInstruction::JmpInstruction(LocPair operand) {
    name = "jmp";
    size = 4;
    this->operand = operand;
}

void JmpInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(operand.second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, operand.first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string address = t->transformLabel
        (line_number, operand.first, it->second, 22, 0);
    opcode = "1001010" + address.substr(0, 5) + "110" + address.substr(5, 17);
}

void JmpInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

RcallInstruction::RcallInstruction(LocPair operand) {
    name = "rcall";
    size = 2;
    this->operand = operand;
}

void RcallInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(operand.second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, operand.first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string offset = t->transformLabel
        (line_number, operand.first, it->second, 12, current_PC);
    opcode = "1101" + offset;
}

void RcallInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

CallInstruction::CallInstruction(LocPair operand) {
    name = "call";
    size = 4;
    this->operand = operand;
}

void CallInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(operand.second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, operand.first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string address = t->transformLabel
        (line_number, operand.first, it->second, 22, 0);
    opcode = "1001010" + address.substr(0, 5) + "111" + address.substr(5, 17);
}

void CallInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

RetInstruction::RetInstruction(void) {
    name = "ret";
    size = 2;
}

void RetInstruction::createOpcode(void) {
    opcode = "1001010100001000";
}

void RetInstruction::print(void) {
    cout << name << "()"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

RetiInstruction::RetiInstruction(void) {
    name = "reti";
    size = 2;
}

void RetiInstruction::createOpcode(void) {
    opcode = "1001010100011000";
}

void RetiInstruction::print(void) {
    cout << name << "()"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

CpInstruction::CpInstruction(LocPair operand1, LocPair operand2) {
    name = "cp";
    size = 2;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void CpInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand1.first, operand1.second);
    string rr = t->transformGeneralRegister
        (line_number, operand2.first, operand2.second);
    opcode = "000101" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void CpInstruction::print(void) {
    cout << name
         << "(" << operand1.second << " , " << operand2.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

CpiInstruction::CpiInstruction(LocPair operand1, LocPair operand2) {
    name = "cpi";
    size = 2;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void CpiInstruction::createOpcode(void) {
    string rd = t->transformUpperRegister
        (line_number, operand1.first, operand1.second);
    string immed = t->transformUnsignedImmediate
        (line_number, operand2.first, operand2.second, 8);
    opcode = "0011" + immed.substr(0, 4) + rd + immed.substr(4, 4);
}

void CpiInstruction::print(void) {
    cout << name
         << "(" << operand1.second << " , " << operand2.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

BreqInstruction::BreqInstruction(LocPair operand) {
    name = "breq";
    size = 2;
    this->operand = operand;
}

void BreqInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(operand.second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, operand.first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string offset = t->transformLabel
        (line_number, operand.first, it->second, 6, current_PC);
    opcode = "111100" + offset + "001";
}

void BreqInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

BrneInstruction::BrneInstruction(LocPair operand) {
    name = "brne";
    size = 2;
    this->operand = operand;
}

void BrneInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(operand.second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, operand.first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string offset = t->transformLabel
        (line_number, operand.first, it->second, 6, current_PC);
    opcode = "111101" + offset + "001";
}

void BrneInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

BrgeInstruction::BrgeInstruction(LocPair operand) {
    name = "brge";
    size = 2;
    this->operand = operand;
}

void BrgeInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(operand.second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, operand.first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string offset = t->transformLabel
        (line_number, operand.first, it->second, 6, current_PC);
    opcode = "111101" + offset + "100";
}

void BrgeInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

BrltInstruction::BrltInstruction(LocPair operand) {
    name = "brlt";
    size = 2;
    this->operand = operand;
}

void BrltInstruction::createOpcode(void) {
    // If label is not in symbol table, throw error here
    map<string, int>::iterator it;
    it = symbol_table.find(operand.second);
    if (it == symbol_table.end()) {
        string err_msg = "Invalid label: not in symbol table";
        error(line_number, operand.first, err_msg);
    }
    // If label is in symbol table, pass in its PC (it->second) as an arg
    string offset = t->transformLabel
        (line_number, operand.first, it->second, 6, current_PC);
    opcode = "111100" + offset + "100";
}

void BrltInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}


/* DATA TRANSFER INSTRUCTIONS */

MovInstruction::MovInstruction(LocPair operand1, LocPair operand2) {
    name = "mov";
    size = 2;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void MovInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand1.first, operand1.second);
    string rr = t->transformGeneralRegister
        (line_number, operand2.first, operand2.second);
    opcode = "001011" + rr.substr(0, 1) + rd + rr.substr(1, 4);
}

void MovInstruction::print(void) {
    cout << name
         << "(" << operand1.second << " , " << operand2.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

LdiInstruction::LdiInstruction(LocPair operand1, LocPair operand2) {
    name = "ldi";
    size = 2;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void LdiInstruction::createOpcode(void) {
    string rd = t->transformUpperRegister
        (line_number, operand1.first, operand1.second);
    string immed = t->transformUnsignedImmediate
        (line_number, operand2.first, operand2.second, 8);
    opcode = "1110" + immed.substr(0, 4) + rd + immed.substr(4, 4);
}

void LdiInstruction::print(void) {
    cout << name
         << "(" << operand1.second << " , " << operand2.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

LdsInstruction::LdsInstruction(LocPair operand1, LocPair operand2) {
    name = "lds";
    size = 4;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void LdsInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand1.first, operand1.second);
    string immed = t->transformUnsignedImmediate
        (line_number, operand2.first, operand2.second, 16);
    opcode = "1001000" + rd + "0000" + immed;
}

void LdsInstruction::print(void) {
    cout << name
         << "(" << operand1.second << " , " << operand2.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

LdInstruction::LdInstruction(LocPair operand) {
    // Note that this is the regular ld instruction
    // (no increment/decrement or displacement)
    name = "ld";
    size = 2;
    this->operand = operand;
}

void LdInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand.first, operand.second);
    opcode = "1001000" + rd + "1100";
}

void LdInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

StsInstruction::StsInstruction(LocPair operand1, LocPair operand2) {
    name = "sts";
    size = 4;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void StsInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand1.first, operand1.second);
    string immed = t->transformUnsignedImmediate
        (line_number, operand2.first, operand2.second, 16);
    opcode = "1001001" + rd + "0000" + immed;
}

void StsInstruction::print(void) {
    cout << name
         << "(" << operand1.second << " , " << operand2.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

StInstruction::StInstruction(LocPair operand) {
    // Note that this is the regular ld instruction
    // (no increment/decrement or displacement)
    name = "st";
    size = 2;
    this->operand = operand;
}

void StInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand.first, operand.second);
    opcode = "1001001" + rd + "1100";
}

void StInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

InInstruction::InInstruction(LocPair operand1, LocPair operand2) {
    name = "in";
    size = 2;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void InInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand1.first, operand1.second);
    string io = t->transformUnsignedImmediate
        (line_number, operand2.first, operand2.second, 6);
    opcode = "10110" + io.substr(0, 2) + rd + io.substr(2, 4);
}

void InInstruction::print(void) {
    cout << name
         << "(" << operand1.second << " , " << operand2.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

OutInstruction::OutInstruction(LocPair operand1, LocPair operand2) {
    name = "out";
    size = 2;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void OutInstruction::createOpcode(void) {
    string io = t->transformUnsignedImmediate
        (line_number, operand1.first, operand1.second, 6);
    string rr = t->transformGeneralRegister
        (line_number, operand2.first, operand2.second);
    opcode = "10111" + io.substr(0, 2) + rr + io.substr(2, 4);
}

void OutInstruction::print(void) {
    cout << name
         << "(" << operand1.second << " , " << operand2.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

PushInstruction::PushInstruction(LocPair operand) {
    name = "push";
    size = 2;
    this->operand = operand;
}

void PushInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand.first, operand.second);
    opcode = "1001001" + rd + "1111";
}

void PushInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

PopInstruction::PopInstruction(LocPair operand) {
    name = "pop";
    size = 2;
    this->operand = operand;
}

void PopInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand.first, operand.second);
    opcode = "1001000" + rd + "1111";
}

void PopInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}


/* BIT AND BIT_TEST INSTRUCTIONS */

LslInstruction::LslInstruction(LocPair operand) {
    name = "lsl";
    size = 2;
    this->operand = operand;
}

void LslInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand.first, operand.second);
    opcode = "000011" + rd.substr(0, 1) + rd + rd.substr(1, 4);
}

void LslInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

LsrInstruction::LsrInstruction(LocPair operand) {
    name = "lsr";
    size = 2;
    this->operand = operand;
}

void LsrInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand.first, operand.second);
    opcode = "1001010" + rd + "0110";
}

void LsrInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

AsrInstruction::AsrInstruction(LocPair operand) {
    name = "asr";
    size = 2;
    this->operand = operand;
}

void AsrInstruction::createOpcode(void) {
    string rd = t->transformGeneralRegister
        (line_number, operand.first, operand.second);
    opcode = "1001010" + rd + "0101";
}

void AsrInstruction::print(void) {
    cout << name
         << "(" << operand.second << ")"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}

NopInstruction::NopInstruction(void) {
    name = "nop";
    size = 2;
}

void NopInstruction::createOpcode(void) {
    opcode = "0000000000000000";
}

void NopInstruction::print(void) {
    cout << name << "()"
         << " [size = " << size << ", opcode = " << opcode << "]"
         << endl;
}