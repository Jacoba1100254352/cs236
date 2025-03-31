#include <iostream>
#include <fstream>
#include <string>
#include "Token.h"
#include "Scanner.h"

using namespace std;

int main(int argc, char *argv[]) {
    //Token t = Token(COMMA, ",", 2);

    ifstream infile("../input.txt");
    //ifstream infile(argv[1]);
    stringstream buffer;
    buffer << infile.rdbuf();
    infile.close();

    vector<Token> tokens = Scanner(buffer.str()).scanToken();

    for (auto & token : tokens)
        cout << token.toString() << endl;
    cout << "Total Tokens = " << tokens.size() << endl;

    return 0;
}
