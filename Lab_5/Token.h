#ifndef LAB_1_TOKEN_H
#define LAB_1_TOKEN_H

#include <string>
#include <sstream>
#include <utility>

enum TokenType {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDOFFILE,
};

// Collects/Organizes Words and symbols found in the input
class Token {

public:
    ///   Constructor   ///
    Token(TokenType type, std::string value, unsigned line)
    : type(type), value(std::move(value)), line(line) { }

    ///   Print and format the type, item, and line number   ///
    std::string toString() {
        return "(" + typeName(type) + ",\"" + value + "\"," + std::to_string(line) + ")";
    }

    ///   Get Local Variables   ///
    TokenType getType() const {
        return type;
    }
    std::string getValue() const {
        return value;
    }

    ///   Return a string signifying the datatype provided   ///
    static std::string typeName(TokenType types) {
        switch (types) {
            case COMMA: return "COMMA";
            case PERIOD: return "PERIOD";
            case Q_MARK: return "Q_MARK";
            case LEFT_PAREN: return "LEFT_PAREN";
            case RIGHT_PAREN: return "RIGHT_PAREN";
            case COLON: return "COLON";
            case COLON_DASH: return "COLON_DASH";
            case MULTIPLY: return "MULTIPLY";
            case ADD: return "ADD";
            case SCHEMES: return "SCHEMES";
            case FACTS: return "FACTS";
            case RULES: return "RULES";
            case QUERIES: return "QUERIES";
            case ID: return "ID";
            case STRING: return "STRING";
            case COMMENT: return "COMMENT";
            case UNDEFINED: return "UNDEFINED";
            case ENDOFFILE: return "EOF";
            default: return "NULL";
        }
    }

    /************************
    *   PRIVATE VARIABLES   *
    ************************/
private:
    TokenType type;
    std::string value;
    unsigned line;
};

#endif //LAB_1_TOKEN_H
