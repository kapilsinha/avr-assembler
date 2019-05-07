#include <bitset>
#include "helper.h"

void error(int line_number, int loc, string msg) {
    cout << "Error (line " << line_number << " char " << loc << "): "
         << msg << endl;
    exit(1);
}

string decimal_to_binary(int n, int bits) {
    if (n < 0){ // check if negative and alter the number
        n += (1 << bits);
    }
    string result = "";
    while(n > 0) {
        result = to_string(n % 2) + result;
        n = n/2;
    }
    while ((int) result.size() < bits) {
        result = "0" + result;
    }
    return result.substr(result.size() - bits, result.size());
}

string decimal_to_hex(int n) {
    // Assumes that n >= 0
    string result = "";
    while (n > 0) {
        int x = n % 16;
        if (x < 10)
            result = to_string(x) + result;
        else {
            string y (1, 'a' + x - 10);
            result = y + result;
        }
        n = n/16;
    }
    if (result.size() == 0) {
        result = "0";
    } 
    return result;
}

/* 
 * string n should not have a 0x prefix
 * Ex: hex_to_decimal("a6") -> 166
 * Returns -1 upon error - the calling function must handle this
 */
int hex_to_decimal(string n) {
    int result = 0;
    int i = n.size();
    for (char &c : n) {
        i--;
        if (c - '0' >= 0 && c - '0' <= 9) {
            result += (c - '0') * (1 << (i * 4));
        }
        else if (c - 'a' >= 0 && c - 'a' <= 5) {
            result += (c - 'a' + 10) * (1 << (i * 4));
        }
        else {
            result = -1;
            break;
        }
    }
    return result;
}

/*
 * Converts a binary number (must have a multiple of 16 digits)
 * NOTE: The output hex will be little-endian
 * Ex: binary -> 91800060 -> 80 91 60 00
 */
string binary_to_hex(string n) {
    if (n.size() > 16) {
        return binary_to_hex(n.substr(0, 16))
            + binary_to_hex(n.substr(16, n.size() - 16));
    }
    string result = "";
    string temp = "";
    int x;
    for (int i = 0; i < (int) n.size(); i += 4) {
        x = (n[i] - '0') * 8 + (n[i + 1] - '0') * 4
            + (n[i + 2] - '0') * 2 + (n[i + 3] - '0');
        if (x < 10) {
            temp += to_string(x);
        }
        else {
            string y (1, 'a' + x - 10);
            temp += y;
        }
        if (temp.size() == 2) {
            result = temp + " " + result;
            temp = "";
        }
    }
    return result;
}

/*
 * Convert decimal number to binary equivalent string with [int bits] bits
 * Ex: toUnsignedBinary(15, 5) -> "01111"
 * Raise error if # is not in [0, 2^bits - 1]
 */
string TransformOperand::toUnsignedBinary(int line_number, int loc,
    int decimal, int bits) {
    if (decimal < 0 || decimal >= (1 << bits)) {
        string err_msg = "Value out of range. Must be in [0, 2^"
            + to_string(bits) + " - 1]";
        error(line_number, loc, err_msg);
    }
    return decimal_to_binary(decimal, bits);
}

/*
 * Convert decimal number to binary equivalent string with [int bits] bits
 * using two's complement
 * Ex: toSignedBinary(-64, 7) -> "1000000"
 * Raise error if # is not in [-2^(bits - 1), 2^(bits - 1) - 1]
 */
string TransformOperand::toSignedBinary(int line_number, int loc,
    int decimal, int bits) {
    if (decimal < -(1 << (bits - 1)) || decimal >= (1 << (bits - 1))) {
        string err_msg = "Value out of range. Must be in [-2^"
            + to_string(bits - 1) + ", 2^" + to_string(bits - 1) + " - 1]";
        error(line_number, loc, err_msg);
    }
    return decimal_to_binary(decimal, bits);
}

/*
 * Convert "r#" -> #
 * Ex: "r10" -> 10
 * Raise error if string does not start with 'r' or
 *             if # is not in [0, 31]
 */
int TransformOperand::extractRegisterNumber(int line_number, int loc,
    string reg) {
    if (reg[0] != 'r') {
        string err_msg = "Invalid register (name must start with 'r')";
        error(line_number, loc, err_msg);
    }
    int x;
    try {
        x = stoi(reg.substr(1, reg.size()));
    }
    catch (invalid_argument const &e) {
        string err_msg = "Invalid register (must be r0 - r31)";
        error(line_number, loc, err_msg);
    }
    if (x < 0 || x > 31) {
        string err_msg = "Invalid register (must be r0 - r31)";
        error(line_number, loc, err_msg);
    }
    return x;
}

/*
 * Converts "r#" -> binary equivalent of #
 * Ex: "r2" -> "00010"
 * Raise error if string does not start with 'r' or
 *             if # is not in [0, 31]
 */
string TransformOperand::transformGeneralRegister(int line_number, int loc,
    string reg) {
    int decimal = TransformOperand::extractRegisterNumber(line_number, loc, reg);
    return TransformOperand::toUnsignedBinary(line_number, loc, decimal, 5);
}

/*
 * Transform bits, constants, and immediates into binary equivalent string
 * Ex: transformUnsignedImmediate("2", 4) -> "0010"
 * Raise error if input is not in [0, 2^bits - 1]
 */
string TransformOperand::transformUnsignedImmediate(int line_number, int loc,
    string immediate, int bits) {
    int decimal;
    try {
        if (immediate[0] == '$') {
            decimal = stoi(immediate.substr(1, immediate.size() - 1));
        }
        else if (immediate.substr(0, 2).compare("0x") == 0) {
            decimal = hex_to_decimal(immediate.substr(2, immediate.size() - 2));
        }
        else {
            decimal = stoi(immediate);
        }
    }
    catch (invalid_argument const &e) {
        string err_msg = "Invalid value: not an int";
        error(line_number, loc, err_msg);
    }
    if (decimal < 0 || decimal >= (1 << bits)) {
        string err_msg = "Value out of range. Must be in [0, 2^"
            + to_string(bits) + " - 1]";
        error(line_number, loc, err_msg);
    }
    return TransformOperand::toUnsignedBinary(line_number, loc, decimal, bits);
}

/*
 * Transform bits, constants, and immediates into binary equivalent string
 * using two's complement
 * Ex: transformSignedImmediate("-2", 4) -> "1110"
 * Raise error if input is not in [-2^(bits - 1), 2^(bits - 1) - 1]
 */
string TransformOperand::transformSignedImmediate(int line_number, int loc,
    string immediate, int bits) {
    int decimal;
    try {
        if (immediate[0] == '$') {
            decimal = stoi(immediate.substr(1, immediate.size() - 1));
        }
        else {
            decimal = stoi(immediate);
        }
    }
    catch (invalid_argument const &e) {
        string err_msg = "Invalid value: not an int";
        error(line_number, loc, err_msg);
    }
    if (decimal < -(1 << (bits - 1)) || decimal >= (1 << (bits - 1))) {
        string err_msg = "Value out of range. Must be in [-2^"
            + to_string(bits - 1) + ", 2^" + to_string(bits - 1) + " - 1]";
        error(line_number, loc, err_msg);
    }
    return TransformOperand::toSignedBinary(line_number, loc, decimal, bits);
}

/*
 * "r25:r24" -> "00"
 * "r27:r26" -> "01"
 * "r29:r28" -> "10"
 * "r31:r30" -> "11"
 * Raise error if input is not in the above
 */
string TransformOperand::transformRegisterPair(int line_number, int loc,
    string pair) {
    if (pair.compare("r25:r24") == 0) {
        return string("00");
    }
    if (pair.compare("r27:r26") == 0) {
        return string("01");
    }
    if (pair.compare("r29:r28") == 0) {
        return string("10");
    }
    if (pair.compare("r31:r30") == 0) {
        return string("11");
    }
    string err_msg = "Invalid register pair (must be 'r25:24', 'r27:r26', 'r29:r28', or 'r31:r30')";
    error(line_number, loc, err_msg);
    return "";
}

/*
 * "r#" -> binary equivalent of (# - 16)
 * Raise error if string does not start with 'r' or
 *             if (# - 16) is not in [0, 15]
 */
string TransformOperand::transformUpperRegister(int line_number, int loc,
    string reg) {
    if (reg[0] != 'r') {
        string err_msg = "Invalid register (name must start with 'r')";
        error(line_number, loc, err_msg);
    }
    int decimal;
    try {
        decimal = stoi(reg.substr(1, reg.size())) - 16;
    }
    catch (invalid_argument const &e) {
        string err_msg = "Invalid register (must be r16 - r31)";
        error(line_number, loc, err_msg);
    }
    if (decimal < 0 || decimal > 15) {
        string err_msg = "Invalid register (must be r16 - r31)";
        error(line_number, loc, err_msg);
    }
    return TransformOperand::toUnsignedBinary(line_number, loc, decimal, 4);
}

/*
 * "r#" -> #
 * Raise error if string does not start with 'r' or
 *             if # is not in [0, 15]
 */
string TransformOperand::transformLowerRegister(int line_number, int loc,
    string reg) {
    if (reg[0] != 'r') {
        string err_msg = "Invalid register (name must start with 'r')";
        error(line_number, loc, err_msg);
    }
    int decimal;
    try {
        decimal = stoi(reg.substr(1, reg.size()));
    }
    catch (invalid_argument const &e) {
        string err_msg = "Invalid register (must be r0 - r15)";
        error(line_number, loc, err_msg);
    }
    if (decimal < 0 || decimal > 15) {
        string err_msg = "Invalid register (must be r0 - 15)";
        error(line_number, loc, err_msg);
    }
    return TransformOperand::toUnsignedBinary(line_number, loc, decimal, 4);
}

/*
 * Returns binary equivalent string of
 * (symbol_table[label] - line_PC) = (label_PC - line_PC)
 * Raise error if (label_PC - line_PC) < -2^(bits - 1) or
 *             if (label_PC - line_PC) > 2^(bits - 1) - 1
 * Note: Error checking to determine whether the label is in the symbol
 * table must be done in the calling function since we do not access
 * the symbol table here
 */
string TransformOperand::transformLabel(int line_number, int loc,
    int label_PC, int bits, int line_PC) {
    return TransformOperand::transformSignedImmediate
        (line_number, loc, to_string(label_PC - line_PC), bits);
}
