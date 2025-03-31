#ifndef PROJECT_3_INTERPRETER_H
#define PROJECT_3_INTERPRETER_H

#include <utility>
#include <iostream>

#include "DatalogProgram.h"
#include "Database.h"

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

    }
    void evalQueries(){
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

    /************************
    *   PRIVATE VARIABLES   *
    ************************/
private:
    DatalogProgram program;
    Database database;
};


#endif //PROJECT_3_INTERPRETER_H
