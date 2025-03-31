#ifndef LAB_2_PARSER_H
#define LAB_2_PARSER_H

#include <iostream>
#include <utility>
#include <vector>
#include "Token.h"
#include "Predicate.h"
#include "DatalogProgram.h"
#include "Rule.h"

// SK(A,B) Predicate: SK, parameters: (A,B) individually referred to sometimes as constants: A, B
// Reads in text and associates it with its respective tokens
class Parser {
public:
	///   Constructor   ///
	explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

	///   Analyze the first token in vector   ///
	TokenType tokenType() const {
		return tokens.at(0).getType();
	}
	std::string tokenValue() const {
		return tokens.at(0).getValue();
	}
	void advanceToken() {
		tokens.erase(tokens.begin()); // erase the first (thus, advance to the second)
	}
	void throwError() {
		std::cout << "Failure!" << std::endl;
		std::cout << "  " << tokens.at(0).toString() << std::endl;
		exit(1);
	}

	///   Returns the name (value) of the token found (if valid)   ///
	std::string match(TokenType type) {
		while (tokenType() == COMMENT)
			advanceToken();
		if (tokenType() == type) {
			std::string returnVal = tokenValue();
			advanceToken();
			return returnVal;
		} else throwError();
		return "";
		//throw std::invalid_argument("\nError in Parser.h on Line " + std::to_string(__LINE__) + "\n" + Token::typeName(tokenType()) + " encountered, but " + Token::typeName(t) + " was needed.");
	}

	/*****************************************
	*   DATATYPE INFO COLLECTING FUNCTIONS   *
	*****************************************/
	Predicate headPredicate() { // This is the left-hand argument in each rule
		Predicate head(match(ID));
		match(LEFT_PAREN);
		head.addValue(match(ID));
		idList(head);
		match(RIGHT_PAREN);
		return head;
	}
	void parameter(Predicate& p) {
		if (tokenType() == STRING)
			p.addValue(match(STRING));
		else if (tokenType() == ID)
			p.addValue(match(ID));
	}
	void predicate(Predicate& p) {
		if (tokenType() == ID) {
			p = Predicate(match(ID));
			match(LEFT_PAREN);
			parameter(p);
			parameterList(p);
			match(RIGHT_PAREN);
		}
	}
	void scheme() { // Collect each scheme and their parameters
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
	void fact() {
		if (tokenType() == ID) {
			Predicate p(match(ID)); // SNAP
			match(LEFT_PAREN);
			p.addValue(match(STRING)); // Add everything inside
			datalog.addToDomain(p.getParameters().back().getParameter()); // Add contents to datalog
			stringList(p); // parse all the strings
			match(RIGHT_PAREN);
			match(PERIOD);
			datalog.addToFacts(p); // Add the whole parsed info to datalog
		} else throwError();
		//throw std::invalid_argument("\nError in Parser.h on Line " + std::to_string(__LINE__) + "\n" + Token::typeName(tokenType()) + " encountered, but " + Token::typeName(t) + " was needed.");
	}
	void rule() {
		Rule rule(headPredicate()); // collect first predicate in rule headPredicate :- other predicates
		match(COLON_DASH);
		Predicate p("");
		predicate(p); // other predicates
		rule.addPredicate(p); // add to rule
		predicateList(p, rule); // recursively add the rest, in here the parameters are also collected
		match(PERIOD);
		datalog.addToRules(rule); // add to the datalog vector
	}
	void query() { // Collects each ID and parameter in the query into p
		Predicate p("");
		predicate(p);
		match(Q_MARK);
		datalog.addToQueries(p);
	}

	/***********************************************
	*   RECURSIVELY CALLING COLLECTING FUNCTIONS   *
	***********************************************/
	void idList(Predicate& p) { // Generally used to recurse over IDs used as parameters, IDs and strings are different
		if (tokenType() == COMMA) {
			match(COMMA);
			p.addValue(match(ID)); // B, C, D
			idList(p);
		}
	}
	void stringList(Predicate& p) { // This is used in facts which has many strings to recurse over
		if (tokenType() == COMMA) {
			match(COMMA);
			p.addValue(match(STRING));
			datalog.addToDomain(p.getParameters().back().getParameter());
			stringList(p);
		}
	}
	void parameterList(Predicate& p) {
		if (tokenType() == COMMA) {
			match(COMMA);
			parameter(p);
			parameterList(p);
		}
	}
	void predicateList(Predicate& p, Rule& rule) { // Each rule has a list of predicates following the :- that it collects, each predicate has parameters that it collects
		if (tokenType() == COMMA) {
			match(COMMA);
			predicate(p);
			rule.addPredicate(p);
			predicateList(p, rule);
		}
	}
	void schemeList() {
		if (tokenType() == ID) {
			scheme();
			schemeList();
		}
	}
	void factList() {
		if (tokenType() == ID) {
			fact();
			factList();
		}
	}
	void ruleList() {
		if (tokenType() == ID) {
			rule();
			ruleList();
		}
	}
	void queryList() {
		if (tokenType() == ID) {
			query();
			queryList();
		}
	}

	///   Collect all info into the datalog private vectors   ///
	DatalogProgram datalogProgram() {
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
		return datalog;
	}

	/************************
	*   PRIVATE VARIABLES   *
	************************/
private:
	std::vector<Token> tokens;
	DatalogProgram datalog;
};


#endif //LAB_2_PARSER_H
