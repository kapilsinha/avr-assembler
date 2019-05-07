#include "helper.h"

void error(int line_number, int loc, string msg) {
    cout << "Error (line " << line_number << " char " << loc << "): "
         << msg << endl;
    exit(1);
}