#ifndef LAB_2_PARSER_H
#define LAB_2_PARSER_H

#include <iostream>
#include <vector>
#include "Token.h"

/*
 * The Parser class is responsible for consuming a list of Tokens and
 * ensuring they follow a certain grammar (or set of rules). In this
 * example, the grammar rules are simple and revolve around parsing
 * "schemes" (an ID, followed by a parenthesis, etc.).
 */
class Parser {
private:
    // Holds the list of Token objects to be parsed
    std::vector<Token> tokens;

public:
    // Constructor: Accepts a vector of Token objects
    explicit Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

    // Returns the TokenType of the current token (the first one in the vector)
    TokenType tokenType() const
    {
        return tokens.at(0).getType();
    }

    // Removes the first token from the list, moving to the next token
    void advanceToken()
    {
        tokens.erase(tokens.begin());
    }

    // Prints an error message (in a more robust system, you might throw an exception)
    static void throwError()
    {
        std::cout << "error" << std::endl;
    }

    /*
     * Attempts to match the current token's type with the expected type (t).
     * If they match, the parser advances to the next token.
     * If they don't match, the parser reports an error.
     */
    void match(TokenType t)
    {
        std::cout << "match: " << t << std::endl;
        if (tokenType() == t) {
            advanceToken();
        } else {
            throwError();
        }
    }

    /*
     * idList():
     *   - Checks if the current token is a COMMA. If yes, consume it, then consume an ID,
     *     and recursively call idList() again. This allows multiple IDs to be parsed
     *     if they are separated by commas.
     *   - If the current token isn't a COMMA, do nothing (lambda/empty production).
     */
    void idList()
    {
        if (tokenType() == COMMA) {
            match(COMMA);
            match(ID);
            idList();
        }
        // If it's not a COMMA, we do nothing here (end of the list).
    }

    /*
     * scheme():
     *   - Expects an ID, then LEFT_PAREN, then another ID,
     *     followed by any additional IDs separated by commas,
     *     and finally a RIGHT_PAREN.
     *   - If the sequence doesn't match, we throw an error.
     */
    void scheme()
    {
        if (tokenType() == ID) {
            match(ID);
            match(LEFT_PAREN);
            match(ID);
            idList();
            match(RIGHT_PAREN);
        } else {
            throwError();
        }
    }
};

#endif //LAB_2_PARSER_H
