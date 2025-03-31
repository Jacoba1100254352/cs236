#ifndef LAB_1_SCANNER_H
#define LAB_1_SCANNER_H

#include "Token.h"
#include <string>
#include <vector>
#include <utility>
#include <cctype>

// Classifies each character as its respective token then removes it to continue classifications (equivalent to lexer)
class Scanner {
public:
	///   Constructor   ///
	explicit Scanner(std::string inputs) : input(std::move(inputs)) {}

	///   Reads characters and identifies and outputs the datalog language tokens   ///
	std::vector<Token> scanToken() {
		std::vector<Token> tokens;
		TokenType type = COMMA;
		std::string value = ",";
		unsigned size;
		unsigned newLine = 0;

		while (!input.empty()) {
			line = (newLine != 0) ? newLine : line;
			newLine = 0;

			while (isspace(input.at(0)) && input.at(0) != '\n')
				input = input.substr(1);

			switch (input.at(0)) {
				case '\n':line += 1;
					input = input.substr(1);
					continue;

				case ',':type = COMMA;
					size = 1;
					break;

				case '.':type = PERIOD;
					size = 1;
					break;

				case '?':type = Q_MARK;
					size = 1;
					break;

				case '(':type = LEFT_PAREN;
					size = 1;
					break;

				case ')':type = RIGHT_PAREN;
					size = 1;
					break;

				case ':':
					if (input.size() > 1 && input.at(1) == '-') {
						type = COLON_DASH;
						size = 2;
					} else {
						type = COLON;
						size = 1;
					}
					break;

				case '*':type = MULTIPLY;
					size = 1;
					break;

				case '+':type = ADD;
					size = 1;
					break;

				case '\'': {
					unsigned pos = input.size(); // By default, we want to be able to remove the first character if something goes wrong
					for (unsigned i = 1; i < pos; i++)
						if (input.at(i) == '\n')
							newLine = (newLine == 0) ? line + 1 : newLine + 1;
						else if (i != pos - 1) {
							if (input.at(i) == '\'' && input.at(i + 1) != '\'') {
								type = STRING;
								pos = i + 1;
								break;
							} else if ((input.at(i) == '\'' && input.at(i + 1) == '\'' && i + 2 < pos))
								i++;
						} else type = UNDEFINED;
					if (type != STRING && type != UNDEFINED)
						type = UNDEFINED;
					size = input.substr(0, pos).size();
					break;
				}

				case '#':size = 1;
					if (input.at(size) == '|') {
						if (input.length() > 1) size++;
						while (input.at(size) != '|' && size < input.length() - 1) {
							if (input.at(size) == '\n') line++;
							size++;
						}
						if (input.at(size) == '|') size++;
					} else
						while (size < input.length() && input.at(size) != '\n')
							size++;

					if (input.at(size) != '#' && input.at(size) != '\n') {
						type = UNDEFINED;
						size++;
					} else {
						type = COMMENT;
						if (input.at(size) != '\n') size++;
					}
					break;

				default:
					if (input.substr(0, (static_cast<std::string>("Schemes").size())) == "Schemes" && !isalpha(input.at(static_cast<std::string>("Schemes").size()))) {
						type = SCHEMES;
						size = 7;
					} else if (input.substr(0, (static_cast<std::string>("Facts").size())) == "Facts" && !isalpha(input.at(static_cast<std::string>("Facts").size()))) {
						type = FACTS;
						size = 5;
					} else if (input.substr(0, (static_cast<std::string>("Rules").size())) == "Rules" && !isalpha(input.at(static_cast<std::string>("Rules").size()))) {
						type = RULES;
						size = 5;
					} else if (input.substr(0, (static_cast<std::string>("Queries").size())) == "Queries" && !isalpha(input.at(static_cast<std::string>("Queries").size()))) {
						type = QUERIES;
						size = 7;
					} else if (isalpha(input.at(0))) {
						type = ID;
						unsigned pos = 0;
						for (unsigned i = 0; i < input.size(); i++)
							if (!isalpha(input.at(i)) && !isdigit(input.at(i))) { // continue until a character is encountered that is neither a number or letter (ID = re, str/input = re' or re, or etc.
								pos = i;
								break;
							}
						size = input.substr(0, pos).size();
					} else if (!input.empty()) {
						type = UNDEFINED;
						size = 1;
					} else {
						type = ENDOFFILE;
						size = 0;
					}
					break;
			}
			value = input.substr(0, size);
			input = input.substr(size);

			// Needed for the Rules analysis to work properly, but why? Is there another way to fix this? (test input 84 from project 4 for an example)
			if (type != COMMENT)
				tokens.emplace_back(type, value, line);
		}

		if (input.empty()) {
			line = (newLine != 0) ? newLine : line;
			tokens.emplace_back(ENDOFFILE, "", line);
		} else throw std::invalid_argument("Buffer is still not empty, Line " + std::to_string(__LINE__));

		return tokens;
	}

	/************************
	*   PRIVATE VARIABLES   *
	************************/
private:
	std::string input;
	unsigned line = 1;
};

#endif //LAB_1_SCANNER_H
