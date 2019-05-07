#include <string>
#include <iostream>

using namespace std;

// (string operand, int loc); loc is index into the line
typedef pair<int, string> LocPair;

void error(int line_number, int loc, string msg);
string decimal_to_binary(int n, int bits);

/*
 * Class that encapsulates methods to transform operands from string to
 * binary form. Each function raises errors if the input is incorrect.
 */
class TransformOperand {
public:
	int line_number;
	int loc;

	string toUnsignedBinary(int line_number, int loc, int decimal, int bits);
	string toSignedBinary(int line_number, int loc, int decimal, int bits);
	int extractRegisterNumber(int line_number, int loc, string reg);
	string transformGeneralRegister(int line_number, int loc, string reg);
	string transformUnsignedImmediate(int line_number, int loc, string immediate, int bits);
	string transformSignedImmediate(int line_number, int loc, string immediate, int bits);
	string transformRegisterPair(int line_number, int loc, string pair);
	string transformUpperRegister(int line_number, int loc, string reg);
	string transformLowerRegister(int line_number, int loc, string reg);
	string transformLabel(int line_number, int loc, int label_PC, int bits, int line_PC);
};
