#ifndef LAB_1_TOKEN_H
#define LAB_1_TOKEN_H

#include <string>
#include <sstream>
#include <utility>

using namespace std;

enum TokenType {
    COMMA, ID, SCHEMES, STRING,
};

class Token {

private:
    TokenType type;
    string value;
    int line;

public:
    Token(TokenType type, string value, int line)
    : type(type), value(std::move(value)), line(line) { }

    string toString() {
        stringstream out;
        out << "(" << type << ",\"" << value << "\"," << line << ")";
        return out.str();
    }

    static string typeName(TokenType types) {
        switch (types) {
            case COMMA:
                return "COMMA";
            case ID:
                return "ID";
            case SCHEMES:
                return "SCHEMES";
            case STRING:
                return "STRING";
            default:
                return "NULL";
        }
    }
};

#endif //LAB_1_TOKEN_H
