#ifndef LAB_1_SCANNER_H
#define LAB_1_SCANNER_H

#include <cctype>
#include <string>
#include <vector>
#include "Token.h"

using namespace std;

class Scanner {
private:
	string input;
	unsigned line = 1;

public:
	explicit Scanner(string inputs) : input(std::move(inputs)) {}

	vector<Token> scanToken()
	{
		vector<Token> tokens;
		TokenType type = COMMA;
		string value = ",";
		unsigned size;
		unsigned newLine = 0;

		while (!input.empty()) {
			line = (newLine != 0) ? newLine : line;
			newLine = 0;

			while (isspace(input.at(0)) && input.at(0) != '\n')
				input = input.substr(1);

			switch (input.at(0)) {
				case '\n': line += 1;
					input = input.substr(1);
					continue;

				case ',': type = COMMA;
					size = 1;
					break;

				case '.': type = PERIOD;
					size = 1;
					break;

				case '?': type = Q_MARK;
					size = 1;
					break;

				case '(': type = LEFT_PAREN;
					size = 1;
					break;

				case ')': type = RIGHT_PAREN;
					size = 1;
					break;

				case ':': if (input.size() > 1 && input.at(1) == '-') {
						type = COLON_DASH;
						size = 2;
					} else {
						type = COLON;
						size = 1;
					}
					break;

				case '*': type = MULTIPLY;
					size = 1;
					break;

				case '+': type = ADD;
					size = 1;
					break;

				case '\'':
				{
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

				case '#':
				{
					bool error = false;
					unsigned pos = 0;
					if (input.at(1) == '|') {
						error = true;
						for (unsigned i = 0; i < input.size(); i++) {
							if (input.at(i) == '\n') {
								if (newLine == 0)
									newLine = line + 1;
								else newLine++;
							}
							if (input.at(i) == '|' && i != input.size() - 1 && input.at(i + 1) == '#') {
								error = false;
								pos = i + 2;
								break;
							}
						}
					}
					type = (!error) ? COMMENT : UNDEFINED;
					size = (pos != 0) ? input.substr(0, pos).size() : input.substr(0, input.find('\n')).size();
					break;
				}

				default: if (input.substr(0, (static_cast<string>("Schemes").size())) == "Schemes" && !isalpha(input.at(static_cast<string>("Schemes").size()))) {
						type = SCHEMES;
						size = 7;
					} else if (input.substr(0, (static_cast<string>("Facts").size())) == "Facts" && !isalpha(input.at(static_cast<string>("Facts").size()))) {
						type = FACTS;
						size = 5;
					} else if (input.substr(0, (static_cast<string>("Rules").size())) == "Rules" && !isalpha(input.at(static_cast<string>("Rules").size()))) {
						type = RULES;
						size = 5;
					} else if (input.substr(0, (static_cast<string>("Queries").size())) == "Queries" && !isalpha(input.at(static_cast<string>("Queries").size()))) {
						type = QUERIES;
						size = 7;
					} else if (isalpha(input.at(0))) {
						type = ID;
						unsigned pos = 0;
						for (unsigned i = 0; i < input.size(); i++)
							if (!isalpha(input.at(i)) && !isdigit(input.at(i))) {
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


			tokens.emplace_back(type, value, line);
		}

		if (input.empty()) {
			line = (newLine != 0) ? newLine : line;
			tokens.emplace_back(ENDOFFILE, "", line);
		} else throw invalid_argument("Buffer is still not empty, Line " + to_string(__LINE__));

		return tokens;
	}
};

#endif //LAB_1_SCANNER_H
