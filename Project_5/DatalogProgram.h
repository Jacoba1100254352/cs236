#ifndef PROJECT_2_DATALOG_PROGRAM_H
#define PROJECT_2_DATALOG_PROGRAM_H

#include <sstream>
#include <set>
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"

//
class DatalogProgram {
public:
	///   Add Info to Vectors   ///
	void addToSchemes(Predicate& p) {
		schemes.push_back(p);
	}
	void addToFacts(Predicate& p) {
		facts.push_back(p);
	}
	void addToQueries(Predicate& p) {
		queries.push_back(p);
	}
	void addToRules(Rule& r) {
		rules.push_back(r);
	}
	void addToDomain(const std::string& d) {
		domain.insert(d);
	}

	///   Get Vectors   ///
	std::vector<Predicate> getSchemes() {
		return schemes;
	}
	std::vector<Predicate> getFacts() {
		return facts;
	}
	std::vector<Predicate> getQueries() {
		return queries;
	}
	std::vector<Rule> getRules() {
		return rules;
	}

	///   Print Datalog Info from Vectors   ///
	std::string toString() {
		std::stringstream out;

		out << "Schemes(" << schemes.size() << ((schemes.empty()) ? "):\n" : "):\n  ");
		for (Predicate& scheme : schemes)
			out << scheme.toString() << "\n" << ((&scheme != &*(--schemes.end())) ? "  " : "");

		out << "Facts(" << facts.size() << ((facts.empty()) ? "):\n" : "):\n  ");
		for (Predicate& fact : facts)
			out << fact.toString() << ".\n" << ((&fact != &*(--facts.end())) ? "  " : "");

		out << "Rules(" << rules.size() << ((rules.empty()) ? "):\n" : "):\n  ");
		for (Rule& rule : rules)
			out << rule.toString() << "\n" << ((&rule != &*(--rules.end())) ? "  " : ""); // FUN option: out << rule.toString() << "\n" << ((&rule != &*(--rules.end())) ? "  " : "Queries(" + std::to_string(queries.size()) + ((queries.empty()) ? "):\n" : "):\n  "));

		out << "Queries(" << queries.size() << ((queries.empty()) ? "):\n" : "):\n  ");
		for (Predicate& query : queries)
			out << query.toString() << "?\n" << ((&query != &*(--queries.end())) ? "  " : "");

		out << "Domain(" << domain.size() << ((domain.empty()) ? "):\n" : "):\n  ");
		for (const std::string& d : domain)
			out << d << ((&d != &*(--domain.end())) ? "\n  " : "\n");
		return out.str();
	}

	/************************
	*   PRIVATE VARIABLES   *
	************************/
private:
	std::vector<Predicate> schemes;
	std::vector<Predicate> facts;
	std::vector<Predicate> queries;
	std::vector<Rule> rules;
	std::set<std::string> domain;
};


#endif //PROJECT_2_DATALOG_PROGRAM_H
