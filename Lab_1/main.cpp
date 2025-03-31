#include <iostream>
#include "Token.h"
#include "Scanner.h"

using namespace std;

int main() {
    Token t = Token(COMMA, ",", 2);
    Scanner s = Scanner(",,");
    t = s.scanToken();
    cout << t.toString() << endl;
    return 0;
}
