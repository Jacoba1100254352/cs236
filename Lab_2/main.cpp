#include <iostream>
#include <vector>
#include "Parser.h"
#include "Token.h"

/*
 * This main function demonstrates how to instantiate and use the Parser with
 * a simple sequence of Tokens. It parses a "scheme" according to the logic
 * defined in Parser::scheme().
 */
int main(int argc, char* argv[])
{
	// Create a vector of Token objects representing a small token sequence
	const std::vector<Token> tokens = {
		Token(ID, "Ned", 2),
		Token(LEFT_PAREN, "(", 2), // This was commented out
		Token(ID, "Ted", 2),
		Token(COMMA, ",", 2),
		Token(ID, "Zed", 2),
		Token(RIGHT_PAREN, ")", 2),
	};

	// Instantiate the Parser with the token list
	Parser p(tokens);

	// Attempt to parse using the "scheme" rule
	p.scheme();

	return 0;
}
