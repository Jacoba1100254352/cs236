#ifndef PROJECT_3_INTERPRETER_H
#define PROJECT_3_INTERPRETER_H

#include <utility>
#include <iostream>

#include "DatalogProgram.h"
#include "Database.h"
#include "Rule.h"
#include "Graph.h"

class Interpreter {
public:
	///   Constructor   ///
	explicit Interpreter(DatalogProgram program) : program(std::move(program)) {}

	///   Run All Evaluations Function   ///
	void run() {
		evalSchemes();
		evalFacts();
		evalRules();
		evalQueries();
	}

	///   Evaluations   ///
	void evalSchemes() { //Predicate: Snap(A,B,C,D), name: Snap, contents: A,B,C,D
		for (Predicate& p : program.getSchemes()) {
			Relation newRelation;
			std::vector<std::string> contents;
			for (const Parameter& param : p.getParameters()) // adds A,B,C,D to vector
				contents.push_back(param.getParameter());
			newRelation.setScheme(Scheme(contents));
			newRelation.setName(p.getName());
			database.insert(newRelation);
		}
	}
	void evalFacts() { // We assume each fact has an associated scheme, no need for error checking
		for (Predicate p : program.getFacts()) {
			std::vector<std::string> contents;
			for (const Parameter& param : p.getParameters())
				contents.push_back(param.getParameter());
			database.getRelationByRef(p.getName()).addTuple(Tuple(contents));
		}
	}
	void evalRules() {
		///   Initialize and print graphs   ///
		bool backwards = true;
		std::vector<Rule> rules = program.getRules();
		Graph graph = makeGraph(rules);

		std::cout << graph.toString();

		///    Evaluate Rules   ///
		std::cout << "\nRule Evaluation\n";

		//Evaluate SCC trees
		for (const std::set<unsigned>& SCC : graph.DFSForrest_SCC(makeGraph(rules, backwards).DFSForrest())) {
			std::vector<Rule> SpecificRules{};
			std::stringstream out;

			for (const unsigned& scc : SCC) {
				SpecificRules.push_back(rules.at(scc));
				out << 'R' << scc << ((&scc != &*(--SCC.end())) ? ',' : '\n');
			}
			if (!out.str().empty())
				std::cout << "SCC: " << out.str() << evalRuleListFixedPointAlg(SpecificRules) << out.str();
		}
	}
	void evalQueries() {
		std::cout << "\nQuery Evaluation\n";
		for (const Predicate& p : program.getQueries()) {
			Relation r = evalPredicate(p);
			std::cout << p.toString() << "? " << ((r.size() != 0) ? ("Yes(" + std::to_string(r.size()) + ")\n" + r.toString()) : ("No\n"));
		}
	}

	///   Predicate Evaluation   ///
	Relation evalPredicate(Predicate predicate) { // Returns the simplified predicates
		Relation currRel = database.getRelationCopy(predicate.getName()); // Grab each relation (called in a loop) in queries
		std::vector<unsigned> colsToKeep;
		std::vector<std::string> names; // Keeps track of each unique parameter

		// Loop through each parameter (A, 'son', C, D...) for each predicate (all parameters in facts for example)
		// If it's an ID: store here, otherwise if it is a Datalog string: do a select on it
		for (unsigned row = 0; row < predicate.getParameters().size(); row++) {
			std::string currParam = predicate.getParameters().at(row).getParameter();

			if (currParam.at(0) == '\'') // or currParam.isConst() where a constant param starts with a '
				currRel = currRel.select(row, currParam); // select each constant (as it goes through the loop)
			else {
				// Eliminate/omit duplicate parameters in the predicate
				bool seenBefore = false;
				unsigned col = 0;
				for (; col < names.size(); col++)
					if (names.at(col) == currParam) {
						seenBefore = true;
						break;
					}

				// Finds tuples with the same variable
				if (seenBefore)
					currRel = currRel.select(row, colsToKeep.at(col)); // select/add tuples with the same "variable" to the vector of tuples in relation
				else { // Mark to keep for the project and rename
					colsToKeep.push_back(row);
					names.push_back(currParam);
				}
			}
		}

		currRel = currRel.project(colsToKeep); // Keeps only columns with unique parameters in the predicate
		currRel = currRel.rename(names); // : Scheme has col (parameter) A, but Query calls it X (variable), so we need to rename it
		return currRel;
	}

	///   Make Graph   ///
	static Graph makeGraph(const std::vector<Rule>& rules, bool backwards = false) {
		Graph graph(rules.size());

		for (unsigned fromID = 0; fromID < rules.size(); fromID++)
			for (unsigned pred = 0; pred < rules.at(fromID).getBodyPredicates().size(); pred++) // Loop through the body predicates the from-rule points to
				for (unsigned toID = 0; toID < rules.size(); toID++)
					if (rules.at(toID).getHeadPredicate().getName() == rules.at(fromID).getBodyPredicates().at(pred).getName()) // if to-Head == from-Body
						graph.addEdge((backwards) ? toID : fromID, (backwards) ? fromID : toID); // (fromID == toID || Forward.getNodes().at(fromID).isSelfDependent1()));

		return graph;
	}

	///   Continual Rule Evaluation   ///
	void singlePass(const std::vector<Rule>& rules) {
		for (const Rule& rule : rules) {
			/*
			 Join all the body predicates together into a single rule
			 for each body predicate p call evaluatePredicates(p)
			 join all those together into relation currRelation

			project()
			rename()
			unionize()*/

			// Print each rule (Head :- Body)
			std::cout << rule.toString() << std::endl;

			std::vector<Relation> bodyRelations;

			// Join
			for (const Predicate& currPred : rule.getBodyPredicates())
				bodyRelations.push_back(evalPredicate(currPred)); // Simplify and combine important relations

			// Skips loop if body size is 1
			Relation result = bodyRelations.at(0);
			for (unsigned i = 1; i < bodyRelations.size(); i++)
				result = result.natJoin(bodyRelations.at(i));

			// Project
			std::vector<unsigned> keptCols;
			for (const Parameter& parameter : rule.getHeadPredicate().getParameters())
				for (unsigned i = 0; i < result.getScheme().size(); i++)
					if (parameter.getParameter() == result.getScheme().at(i)) // If a parameter in the head is equal to a scheme in the body
						keptCols.push_back(i);
/*          result = result.project(keptCols);

            ///Step 3: Rename
            std::string name = rule.getHeadPredicate().getName();
            result = result.rename(database.getRelationByRef(name).getScheme());

            ///Step 4: unionize
            database.getRelationByRef(name).unionize(result);*/
			database.getRelationByRef(rule.getHeadPredicate().getName()).unionize(result.project(keptCols).rename(database.getRelationByRef(rule.getHeadPredicate().getName()).getScheme()));
		}
	}
	std::string evalRuleListFixedPointAlg(const std::vector<Rule>& rules) {
		unsigned sizeBefore, sizeAfter, numPasses = 0;
		do {
			numPasses++;
			sizeBefore = database.size();
			singlePass(rules);
			sizeAfter = database.size();
		} while (sizeBefore != sizeAfter && ((rules.size() != 1) || isSelfDependent(rules))); // Keep doing this until no unique tuples are found so nodes aren't locked in a cycle

		return std::to_string(numPasses) + " passes: ";
	}

	///   Check Self Dependency Function   ///
	static bool isSelfDependent(const std::vector<Rule>& rules) {
		std::vector<Predicate> loop = rules.at(0).getBodyPredicates();
		return std::any_of(loop.begin(), loop.end(), [rules](const Predicate& predicate) { return (predicate.getName() == rules.at(0).getHeadPredicate().getName()); });
	}

	/************************
	*   PRIVATE VARIABLES   *
	************************/
private:
	DatalogProgram program;
	Database database;
};


#endif //PROJECT_3_INTERPRETER_H
