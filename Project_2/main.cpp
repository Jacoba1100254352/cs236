#include <iostream>
#include <fstream>
#include <vector>
#include "Token.h"
#include "Parser.h"
#include "Scanner.h"

int main(int argc, char* argv[])
{
    //ifstream infile("../input.txt");
    ifstream infile(argv[1]);
    stringstream buffer;
    buffer << infile.rdbuf();
    infile.close();

    vector<Token> tokens = Scanner(buffer.str()).scanToken();

    Parser p = Parser(tokens);
    p.datalogProgram();
}
