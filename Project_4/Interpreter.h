#ifndef PROJECT_3_INTERPRETER_H
#define PROJECT_3_INTERPRETER_H

#include <utility>
#include <iostream>

#include "DatalogProgram.h"
#include "Database.h"
#include "Rule.h"

class Interpreter {
public:
    explicit Interpreter(DatalogProgram program) : program(std::move(program)){}

    void run() {
        evalSchemes();
        evalFacts();
        evalRules(); // Should finish later
        evalQueries();
    }

    void evalSchemes() { //Predicate: Snap(A,B,C,D), name: Snap, contents: A,B,C,D
        for (Predicate & p : program.getSchemes()) {
            Relation newRelation;
            std::vector<std::string> contents;
            for (Parameter param : p.getParameters()) // adds A,B,C,D to vector
                contents.push_back(param.getParameter());
            newRelation.setScheme(Scheme(contents));
            newRelation.setName(p.getName());
            database.insert(newRelation);
        }
    }
    void evalFacts() { // We assume each fact has an associated scheme, no need for error checking
        for (Predicate p : program.getFacts()) {
            Relation& r = database.getRelationByRef(p.getName());
            std::vector<std::string> contents;
            for (Parameter param : p.getParameters())
                contents.push_back(param.getParameter());
            r.addTuple(Tuple(contents));
            // If something isn't working, may need to add: database.insert(r);
        }
    }
    void evalRules() {
        //cn(c, n) :- snap(S, n, A, P), csg(c, S, G)
        std::cout << "Rule Evaluation" << std::endl;
        evalRuleListFixedPointAlg(program.getRules());
    }
    void evalQueries(){
        std::cout << "Query Evaluation" << std::endl;
        for(Predicate p : program.getQueries()) {
            Relation r = evalPredicate(p);
            std::cout << p.toString() << "? ";
            if(r.size() != 0){
                std::cout << "Yes(" << r.size() << ")" << std::endl
                          << r.toString();

            } else std::cout << "No" << std::endl;
            //cout << r.toString();
        }
    }

    Relation evalPredicate(Predicate predicate) {
        Relation currRel = database.getRelationCopy(predicate.getName()); // Grab each relation (called in a loop) in queries
        //std::cout << database.toString() << std::endl;
        std::vector<unsigned> colsToKeep;
        std::vector<std::string> names;

        // Loop through each parameter (A, 'son', C, D...) for each predicate (all parameters in facts for example)
        // If it's an ID: store here, otherwise if it is a Datalog string: do a select on it
        for (unsigned row = 0; row < predicate.getParameters().size(); row++) {
            std::string currParam = predicate.getParameters().at(row).getParameter();

            if (currParam.at(0) == '\'') // or currParam.isConst() where a constant param starts with a '
                currRel = currRel.select(row, currParam); // select constants
            else {
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

        currRel = currRel.project(colsToKeep);
        currRel = currRel.rename(names); // : Scheme has col (parameter) A, but Query calls it X (variable), so we need to rename it
        return currRel;
    }
    void singlePass(const std::vector<Rule>& rules) {
        for(Rule rule : rules){
            /*
             Join all the body predicates together into a single rule
             for each body predicate p call evaluatePredicates(p)
             join all those together into relation currRelation

            project()
            rename()
            unionize()*/

            std::cout << rule.toString() << std::endl;

            std::vector<Relation> bodyRelations;

            // Join
            for(const Predicate & currPred : rule.getBodyPredicates())
                bodyRelations.push_back(evalPredicate(currPred));

            // Skips loop if body size is 1
            Relation result = bodyRelations.at(0);
            for (unsigned i = 1; i < bodyRelations.size(); i++)
                result = result.natJoin(bodyRelations.at(i));

            // Project
            std::vector<unsigned> keptCols;
            for(Parameter parameter : rule.getHeadPredicate().getParameters())
                for(unsigned i = 0; i < result.getScheme().size(); i++)
                    if(parameter.getParameter() == result.getScheme().at(i))
                        keptCols.push_back(i);
/*          result = result.project(keptCols);

            ///Step 3: Rename
            std::string name = rule.getHeadPredicate().getName();
            result = result.rename(database.getRelationReference(name).getScheme());

            ///Step 4: unionize
            database.getRelationReference(name).unionize(result);*/
            database.getRelationByRef(rule.getHeadPredicate().getName()).unionize(result.project(keptCols).rename(database.getRelationByRef(rule.getHeadPredicate().getName()).getScheme()));
        }
    }

/*    void evalRulesListOnce(const std::vector<Rule>& rules) {
        for (Rule currRule : rules) {
            std::cout << currRule.toString() << std::endl;
            std::vector<Relation> bodyRelations;
            for(const Predicate & currPredicate : currRule.getBodyPredicates()) {
                Relation currRelation = evalPredicate(currPredicate);
                bodyRelations.push_back(currRelation);
            }

            Relation resultRelation = bodyRelations.at(0);
            for (unsigned i = 1; i < bodyRelations.size(); i++) // will only do anything if resultRelation is > 1 :)
                resultRelation = Relation::natJoin(resultRelation, bodyRelations.at(i));
            // TODO: Write the logic below and finish natJoin method
            // snap(S,n, A, P), snap(S, n, A, P), snap(S, n, A, P), snap(S, n, A, P)

            //   0  1              0  1  2  3  4  5
            //cn(c, n) :- snap+csg(S, n, A, P, c, G)
            //project({4,1});

            database.getRelationByRef(currRule.getHeadPredicate().getName()).unionize(resultRelation.rename(database.getRelationByRef(currRule.getHeadPredicate().getName()).getScheme())); // String name = currRule.getHeadPredicate().getName(); // resultRelation = resultRelation.rename(database.getRelationRef(name).getScheme());
        }
    }*/
    void evalRuleListFixedPointAlg(const std::vector<Rule>& rules) {
        unsigned sizeBefore;
        unsigned sizeAfter;
        unsigned numPasses = 0;
        do {
            numPasses++;
            sizeBefore = database.size();
            singlePass(rules);
            sizeAfter = database.size();
        } while(sizeBefore != sizeAfter); // Keep doing this until no unique tuples are found

        std::cout << "\nSchemes populated after " << numPasses << " passes through the Rules.\n" << std::endl;
    }

    /************************
    *   PRIVATE VARIABLES   *
    ************************/
private:
    DatalogProgram program;
    Database database;
};


#endif //PROJECT_3_INTERPRETER_H
