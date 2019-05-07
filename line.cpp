#include <iostream>
#include <sstream>
#include <algorithm> // used to replace all ','s with ' 's
#include "as.h"

using namespace std;

Line::Line(int line_number, string line_string, Instruction *instruction) {
    this->line_number = line_number;
    this->line_string = line_string;
    this->instruction = instruction;
}

void Line::print(void) {
    cout << "Line " << line_number << ": " << line_string << "    ";
    cout << "Instruction: ";
    instruction->print();
}

void parseLine(string line, int line_number) {
    string processed_line (line);
    // Replace commas with spaces so we can properly tokenize
    replace(processed_line.begin(), processed_line.end(), ',', ' ');
    // Lower-case all the chars
    transform(processed_line.begin(), processed_line.end(),
              processed_line.begin(), ::tolower);
    istringstream iss(processed_line);
    /*
     * status = 0 if we processed no instruction or operands
     * status = 1 if we processed the instruction and no operands
     * status = 2 if we processed the instruction and operand1
     * status = 3 if we processed the instruction, operand1, and operand2 (done)
     */
    int status = 0;
    LocPair instruction;
    LocPair operand1;
    LocPair operand2;

    int i = 0; // Index over the words
    int loc = 0; // Index over the characters
    for (string x; iss >> x; i++) {
        loc = (int) iss.tellg() - x.size();
        // If the word starts a comment [; or //], we finish parsing the line
        // Note that we do not consider multi-line comments
        if (x.front() == ';' || string("//").compare(x.substr(0, 2)) == 0) {
            break;
        }
        else if (status == 0) {
            // If "[label]:", add (label -> current_PC) to symbol table
            if (i == 0 && x.back() == ':') {
                string label = x.substr(0, x.size() - 1);
                pair <map<string, int>::iterator, bool> ptr; 
                ptr = symbol_table.insert(pair<string, int>(label, current_PC));
                // If the label is already in the symbol table, the label was
                // repeated in the input file
                if (!ptr.second) {
                    string err_msg = "'" + label + "' is a duplicate label";
                    error(line_number, loc, err_msg);
                }
            }
            // If the word starts with a ., it is a directive
            else if (x[0] == '.') {
                string err_msg = "Detected directive. Directives are not supported in this primitive assembler.";
                error(line_number, loc, err_msg);
            }
            // Else the word must be the instruction
            else {
                instruction = make_pair (loc, x);
                status++;
            }
        }
        else if (status == 1) {
            operand1 = make_pair (loc, x);
            status++;
        }
        else if (status == 2) {
            operand2 = make_pair (loc, x);
            status++;
        }
        else { // status == 3
            string err_msg = "Unknown value (line already contains instruction and operands)";
            error(line_number, loc, err_msg);
        }
    }

    if (status > 0) {
        // Create instruction
        Instruction *instr = makeInstruction(line_number, instruction,
                                             operand1, operand2);

        // Add line to Lines vector
        Line *line_struct = new Line(line_number, line, instr);
        lines.push_back(line_struct);

        // Update PC
        current_PC += instr->getSize();
    }
}
