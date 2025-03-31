#ifndef PROJECT_2_RULE_H
#define PROJECT_2_RULE_H

#include "Predicate.h"
#include <utility>
#include <vector>
#include <sstream>

// Add the predicates in the rule: the first predicate (head), and its following predicates (body)
class Rule {
public:
    ///   Constructor   ///
    explicit Rule(Predicate headPredicate) : headPredicate(std::move(headPredicate)) {}

    ///   Vector Set Function   ///
    void addPredicate(const Predicate& p) {
        bodyPredicates.push_back(p);
    }

    ///   Print Predicate in Rule   ///
    std::string toString() {
        std::stringstream out;
        out << headPredicate.toString() << " :- ";
        for (unsigned i = 0; i < bodyPredicates.size(); i++) {
            out << bodyPredicates[i].toString();
            if (i < bodyPredicates.size() - 1)
                out << ",";
        }
        out << ".";
        return out.str();
    }

    /************************
    *   PRIVATE VARIABLES   *
    ************************/
private:
    Predicate headPredicate;
    std::vector<Predicate> bodyPredicates;
};


#endif //PROJECT_2_RULE_H
