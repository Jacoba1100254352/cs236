#ifndef LAB_1_TOKEN_H
#define LAB_1_TOKEN_H

#include <string>
#include <sstream>
#include <utility>

using namespace std;

enum TokenType {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDOFFILE,
};

class Token {

private:
    TokenType type;
    string value;
    unsigned line;

public:
    Token(TokenType type, string value, unsigned line)
    : type(type), value(std::move(value)), line(line) { }

    string toString() {
        stringstream out;
        out << "(" << typeName(type) << ",\"" << value << "\"," << line << ")";
        return out.str();
    }

    static string typeName(TokenType types) {
        switch (types) {
            case COMMA:
                return "COMMA";
            case PERIOD:
                return "PERIOD";
            case Q_MARK:
                return "Q_MARK";
            case LEFT_PAREN:
                return "LEFT_PAREN";
            case RIGHT_PAREN:
                return "RIGHT_PAREN";
            case COLON:
                return "COLON";
            case COLON_DASH:
                return "COLON_DASH";
            case MULTIPLY:
                return "MULTIPLY";
            case ADD:
                return "ADD";
            case SCHEMES:
                return "SCHEMES";
            case FACTS:
                return "FACTS";
            case RULES:
                return "RULES";
            case QUERIES:
                return "QUERIES";
            case ID:
                return "ID";
            case STRING:
                return "STRING";
            case COMMENT:
                return "COMMENT";
            case UNDEFINED:
                return "UNDEFINED";
            case ENDOFFILE:
                return "EOF";
            default:
                return "NULL";
        }
    }
};

#endif //LAB_1_TOKEN_H
