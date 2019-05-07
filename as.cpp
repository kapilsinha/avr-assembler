#include <iostream>
#include <fstream>
#include "as.h"

using namespace std;

map<string, int> symbol_table; // Map labels to PC
vector<Line*> lines;           // Vector of Line structs from the code
int current_PC;                // Current PC

void print_symbol_table(void) {
    cout << "Symbol table" << endl;
    for(map<string, int>::const_iterator it = symbol_table.begin();
        it != symbol_table.end(); ++it) {
        cout << "Label: " << it->first << ", PC: " << it->second << endl;
    }
}

void print_lines(void) {
    cout << "Vector<Line*>" << endl;
    for(vector<Line*>::iterator it = lines.begin(); it != lines.end(); ++it) {
        (*it)->print();
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " assembly_file" << endl;
    }
    ifstream inFile(argv[1]);

    if (!inFile) {
        cout << "Unable to open assembly file" << endl;
        exit(1);
    }

    /* Initialization of variables and structures */
    initInstructions();

    /* Iterate over the lines to fill our vector<Line*> and symbol table */
    current_PC = 0;
    int line_number = 0;
    string line;
    while (getline(inFile, line)) {
        line_number++;
        parseLine(line, line_number);
    }
    inFile.close();

    /* Iterate over vector<Line*> and create our opcodes */
    current_PC = 0;
    cout << "Vector<Line*>" << endl;
    for(vector<Line*>::iterator it = lines.begin(); it != lines.end(); ++it) {
        (*it)->getInstruction()->createOpcode();
        current_PC += (*it)->getInstruction()->getSize();
    }
    
    cout << "PC: " << current_PC << endl;
    print_symbol_table();
    print_lines();

    return 0;
}
