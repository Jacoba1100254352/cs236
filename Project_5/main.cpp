#include <fstream>
#include <vector>
#include "Parser.h"
#include "Scanner.h"
#include "Interpreter.h"

int main(__attribute__((unused)) int argc, char* argv[]) {
	std::stringstream buffer;
	std::string input = "../input.txt";
	buffer << std::ifstream(input).rdbuf();

	Interpreter(Parser(Scanner(buffer.str()).scanToken()).datalogProgram()).run();
	return 0;
}
