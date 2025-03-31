#ifndef PROJECT_2_RELATION_H
#define PROJECT_2_RELATION_H

#include <iostream>
#include <utility>
#include <map>
#include <set>

#include "Scheme.h"
#include "Tuple.h"

//
class Relation {
public:
	///   Constructor   ///
	Relation(std::string name, Scheme scheme) : name(std::move(name)), scheme(std::move(scheme)) {}
	Relation() = default;

	///   Get and Set Functions   ///
	bool addTuple(const Tuple& tuple) { // if the tuple was not already in the set this returns true, otherwise false
		return tuples.insert(tuple).second;
	}
	std::set<Tuple> getTuples() {
		return tuples;
	}
	const std::string& getName() const {
		return name;
	}
	void setName(const std::string& tempName) {
		Relation::name = tempName;
	}
	const Scheme& getScheme() const {
		return scheme;
	}
	void setScheme(const Scheme& tempScheme) {
		scheme = tempScheme;
	}

	///   Size Function   ///
	unsigned size() const {
		return tuples.size();
	}

	///   Combine Functions   ///
	static Scheme combineSchemes(Scheme s1, Scheme s2, std::vector<unsigned>& uniqueColumns) {
		Scheme output;
		for (unsigned i = 0; i < s1.size(); i++)
			output.push_back(s1.at(i));

		for (unsigned uniqueColumn : uniqueColumns)
			output.push_back(s2.at(uniqueColumn));
		return output;
	}
	static Tuple combineTuples(Tuple t1, Tuple t2, const std::vector<unsigned>& uniqueColumns) {
		Tuple output;
		for (unsigned i = 0; i < t1.size(); i++)
			output.push_back(t1.at(i));

		for (unsigned uniqueColumn : uniqueColumns)
			output.push_back(t2.at(uniqueColumn));
		return output;
	}

	///   Select Functions   ///
	Relation select(unsigned index, const std::string& value) const { // Selects which rows to keep
		Relation result(name, scheme);
		for (const Tuple& tuple : tuples)
			if (tuple.at(index) == value)
				result.addTuple(tuple);
		return result;
	}
	Relation select(unsigned index1, unsigned index2) const {
		Relation result(name, scheme);
		for (const Tuple& tuple : tuples)
			if (tuple.at(index1) == tuple.at(index2))
				result.addTuple(tuple);
		return result;
	}

	///   Join Functions   ///
	static bool isJoinable(const Tuple& t1, const Tuple& t2, const std::map<unsigned, unsigned>& overlap) {
		return !std::any_of(overlap.begin(), overlap.end(), [t1, t2](const std::pair<unsigned, unsigned>& p) { return t1.at(p.first) != t2.at(p.second); });
	}
	Relation natJoin(Relation r) {

		// Variables
		Relation output;
		std::vector<unsigned> uniqueCols;
		std::map<unsigned, unsigned> overlap;

		// Find scheme overlap
		for (unsigned i = 0; i < r.getScheme().size(); i++) {
			bool isUnique = true;
			for (unsigned j = 0; j < scheme.size(); j++)
				if (r.getScheme().at(i) == scheme.at(j)) {
					overlap.insert({j, i});
					isUnique = false;
				}
			if (isUnique) uniqueCols.push_back(i);
		}

		output.setName(name + "+" + r.getName());

		// Combine schemes
		output.setScheme(combineSchemes(scheme, r.getScheme(), uniqueCols));

		// If combinable, combine
		for (const Tuple& t1 : tuples)
			for (const Tuple& t2 : r.getTuples())
				if (isJoinable(t1, t2, overlap))
					output.addTuple(combineTuples(t1, t2, uniqueCols));

		return output;
	}

	///   Project, Rename, and Unionize Functions   ///
	Relation project(const std::vector<unsigned>& colsToKeep) { // selects every unique tuple based on the col provided
		Relation result(name, scheme); // name, scheme, and tuples will be specific to the object that calls the function
		for (Tuple tuple : tuples) {
			Tuple newTuple; // create new tuple
			for (unsigned col : colsToKeep)
				newTuple.push_back(tuple.at(col)); // add each tuple element in colsToKeep to add to new tuple
			result.addTuple(newTuple); // add new tuple to (new) result
		}
		return result;
	}
	Relation rename(std::vector<std::string> newNames) {
		Relation result(name, Scheme(std::move(newNames)));
		for (const Tuple& tuple : tuples)
			result.addTuple(tuple);
		return result;
	}
	void unionize(Relation toAdd) {
		if (scheme != toAdd.getScheme())
			throw std::invalid_argument("Cannot combine b/c the schemes are different, Line " + std::to_string(__LINE__));

		for (const Tuple& tuple : toAdd.getTuples())
			if (addTuple(tuple) && !tuple.empty())
				std::cout << "  " << tuple.toString(scheme) << std::endl;
	}

	///   Print Function   ///
	std::string toString() const {
		std::stringstream out;
		if (!Tuple(scheme).empty())
			for (const Tuple& tuple : tuples)
				out << "  " << tuple.toString(scheme) << std::endl;
		return out.str();
	}

	/************************
	*   PRIVATE VARIABLES   *
	************************/
private:
	std::string name{};
	Scheme scheme;
	std::set<Tuple> tuples{};
};


#endif //PROJECT_2_RELATION_H
