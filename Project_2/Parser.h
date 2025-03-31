#ifndef LAB_2_PARSER_H
#define LAB_2_PARSER_H

#include <iostream>
#include <vector>
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include "Token.h"

class Parser {
private:
	std::vector<Token> tokens;
	DatalogProgram datalog;

public:
	explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

	TokenType tokenType() const
	{
		return tokens.at(0).getType();
	}

	std::string tokenValue() const
	{
		return tokens.at(0).getValue();
	}

	void advanceToken()
	{
		tokens.erase(tokens.begin());
	}

	void throwError() const
	{
		std::cout << "Failure!" << std::endl;
		std::cout << "  " << tokens.at(0).toString() << std::endl;
		exit(1);
	}

	std::string match(const TokenType t)
	{
		while (tokenType() == COMMENT)
			advanceToken();
		if (tokenType() == t) {
			std::string returnVal = tokenValue();
			advanceToken();
			return returnVal;
		} else throwError();
		return "";
		//throw std::invalid_argument("\nError in Parser.h on Line " + std::to_string(__LINE__) + "\n" + Token::typeName(tokenType()) + " encountered, but " + Token::typeName(t) + " was needed.");
	}

	Predicate headPredicate()
	{
		Predicate head(match(ID));
		match(LEFT_PAREN);
		head.addValue(match(ID));
		idList(head);
		match(RIGHT_PAREN);
		return head;
	}

	void parameter(Predicate& p)
	{
		if (tokenType() == STRING)
			p.addValue(match(STRING));
		else if (tokenType() == ID)
			p.addValue(match(ID));
	}

	void predicate(Predicate& p)
	{
		if (tokenType() == ID) {
			p = Predicate(match(ID));
			match(LEFT_PAREN);
			parameter(p);
			parameterList(p);
			match(RIGHT_PAREN);
		}
	}

	void idList(Predicate& p)
	{
		if (tokenType() == COMMA) {
			match(COMMA);
			p.addValue(match(ID)); // B, C, D
			idList(p);
		}
	}

	void stringList(Predicate& p)
	{
		if (tokenType() == COMMA) {
			match(COMMA);
			p.addValue(match(STRING));
			datalog.addToDomain(p.getParameters().back().getData());
			stringList(p);
		}
	}

	void parameterList(Predicate& p)
	{
		if (tokenType() == COMMA) {
			match(COMMA);
			parameter(p);
			parameterList(p);
		}
	}

	void predicateList(Predicate& p, Rule& rule)
	{
		if (tokenType() == COMMA) {
			match(COMMA);
			predicate(p);
			rule.addPredicate(p);
			predicateList(p, rule);
		}
	}

	void scheme()
	{
		// SNAP(A, B, C, D)
		if (tokenType() == ID) {
			Predicate p(match(ID)); // SNAP
			match(LEFT_PAREN);
			p.addValue(match(ID)); // A
			idList(p);
			match(RIGHT_PAREN);
			datalog.addToSchemes(p);
		} else throwError();
		//throw std::invalid_argument("\nError in Parser.h on Line " + std::to_string(__LINE__) + "\n" + Token::typeName(tokenType()) + " encountered, but " + Token::typeName(t) + " was needed.");
	}

	void fact()
	{
		if (tokenType() == ID) {
			Predicate p(match(ID)); // SNAP
			match(LEFT_PAREN);
			p.addValue(match(STRING)); // Add everything inside
			datalog.addToDomain(p.getParameters().back().getData()); // Add contents to datalog
			stringList(p); // parse all the strings
			match(RIGHT_PAREN);
			match(PERIOD);
			datalog.addToFacts(p); // Add the whole parsed info to datalog
		} else throwError();
		//throw std::invalid_argument("\nError in Parser.h on Line " + std::to_string(__LINE__) + "\n" + Token::typeName(tokenType()) + " encountered, but " + Token::typeName(t) + " was needed.");
	}

	void rule()
	{
		Rule rule(headPredicate());
		match(COLON_DASH);
		Predicate p("");
		predicate(p);
		rule.addPredicate(p);
		predicateList(p, rule);
		match(PERIOD);
		datalog.addToRules(rule);
	}

	void query()
	{
		Predicate p("");
		predicate(p);
		match(Q_MARK);
		datalog.addToQueries(p);
	}

	void schemeList()
	{
		if (tokenType() == ID) {
			scheme();
			schemeList();
		}
	}

	void factList()
	{
		if (tokenType() == ID) {
			fact();
			factList();
		}
	}

	void ruleList()
	{
		if (tokenType() == ID) {
			rule();
			ruleList();
		}
	}

	void queryList()
	{
		if (tokenType() == ID) {
			query();
			queryList();
		}
	}

	void datalogProgram()
	{
		match(SCHEMES);
		match(COLON);
		scheme();
		schemeList();
		match(FACTS);
		match(COLON);
		factList();
		match(RULES);
		match(COLON);
		ruleList();
		match(QUERIES);
		match(COLON);
		query();
		queryList();
		match(ENDOFFILE);
		std::cout << "Success!" << std::endl;
		std::cout << datalog.toString();
	}
};


#endif //LAB_2_PARSER_H
