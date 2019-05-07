#include <map>
#include <string>
#include <vector>
#include "line.h"

/*
 * Define these extern global variables so that any file that includes as.h
 * can access/manipulate these globals. They are actually declared in as.cpp
 */
extern map<string, int> symbol_table; // Map labels to PC
extern vector<Line*> lines;           // Vector of Line structs from the code
extern int current_PC;                // Current PC

void print_symbol_table(void);
void print_lines(void);