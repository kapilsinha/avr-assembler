#include <string>
#include <iostream>
//#include <utility>

using namespace std;

// (string operand, int loc); loc is index into the line
typedef pair<int, string> LocPair;

void error(int line_number, int loc, string msg);