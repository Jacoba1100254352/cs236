#ifndef PROJECT_2_PREDICATE_H
#define PROJECT_2_PREDICATE_H

#include <utility>
#include <vector>
#include <string>

#include "Parameter.h"

// Handle and associate the Predicates and their parameters (each element under schemes, facts, etc. is a predicate)
class Predicate {
public:
	///   Constructor   ///
	explicit Predicate(std::string id) : id(std::move(id)) {}
	Predicate() = default;

	///   Vector Get and Set Functions   ///
	void addValue(const std::string& value) {
		parameters.emplace_back(value);
	}
	std::vector<Parameter> getParameters() {
		return parameters;
	}
	std::string getName() const {
		return id;
	}

	///   Print Predicate and their Parameters   ///
	std::string toString() const {
		std::stringstream out;
		out << id + "(";
		for (const Parameter& parameter : parameters)
			out << parameter.getParameter() << ((&parameter != &*(--parameters.end())) ? "," : ""); // "," : ")" doesn't work when parameters aren't large enough for it to run
		out << ")";
		return out.str();
	}

	/************************
	*   PRIVATE VARIABLES   *
	************************/
private:
	std::string id{};
	std::vector<Parameter> parameters{};
};


#endif //PROJECT_2_PREDICATE_H
