#ifndef LAB_2_TOKEN_H
#define LAB_2_TOKEN_H

#include <sstream>
#include <string>
//#include <utility>

/*
 * TokenType: An enumeration of possible token types that the parser might use.
 * Each token in the input is assigned one of these types.
 */
enum TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    ENDOFFILE,
};

/*
 * Token: Represents a single token, consisting of a type (TokenType),
 * a string value (the text from input), and a line number.
 */
class Token {
private:
    TokenType type; // Token category (e.g., COMMA, ID, etc.)
    std::string value; // The lexeme or raw text
    unsigned line; // The line number where this token was encountered

public:
    // Constructor: initializes a Token with a type, value, and line number
    Token(const TokenType type, std::string value, const unsigned line)
        : type(type), value(std::move(value)), line(line) {}

    // Returns a string with a human-readable representation of the token
    std::string toString() const
    {
        std::stringstream out;
        out << "(" << typeName(type) << ",\"" << value << "\"," << line << ")";
        return out.str();
    }

    // Getter for the token type
    TokenType getType() const
    {
        return type;
    }

    /*
     * Converts a TokenType to its corresponding string name for display.
     * Used by toString() or anywhere else a string representation is needed.
     */
    static std::string typeName(const TokenType types)
    {
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
};

#endif //LAB_2_TOKEN_H
