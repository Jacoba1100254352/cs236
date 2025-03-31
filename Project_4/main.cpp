//#include <iostream>
//#include <map>
#include <fstream>
#include <vector>
#include "Token.h"
#include "Parser.h"
#include "Scanner.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Interpreter.h"

int main(int argc, char *argv[]) {
    std::stringstream buffer;
    std::string input = argv[1]; //"../project4-passoff/80/input84.txt"; // "../input.txt"; // argv[1];
    buffer << std::ifstream(input).rdbuf();

    Interpreter(Parser(Scanner(buffer.str()).scanToken()).datalogProgram()).run();


    return 0;
}
