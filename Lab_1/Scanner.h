#ifndef LAB_1_SCANNER_H
#define LAB_1_SCANNER_H

#include "Token.h"
#include <string>
#include <utility>
#include <cctype>

using namespace std;

class Scanner {
private:
    string input;

public:
    explicit Scanner(string inputs)
    : input(std::move(inputs)) { }

    Token scanToken() {
        TokenType type = COMMA;
        string value = ",";
        int line = 4;
        int size = 0;

        while (isspace(input.at(0)))
            input = input.substr(1);

        switch(input.at(0)) {
            case ',':
                type = COMMA;
                size = 1;
                break;
        }
        string values = input.substr(0, size);
        input = input.substr(size);

        return {type, value, line};
    }
};

#endif //LAB_1_SCANNER_H
