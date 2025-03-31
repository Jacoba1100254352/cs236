#ifndef PROJECT_2_RULE_H
#define PROJECT_2_RULE_H

#include "Predicate.h"
#include <utility>
#include <vector>
#include <sstream>

class Rule {
private:
    Predicate headPredicate;
    std::vector<Predicate> bodyPredicates;
public:
    explicit Rule(Predicate headPredicate) : headPredicate(std::move(headPredicate)) {}
    void addPredicate(const Predicate& p) {
        bodyPredicates.push_back(p);
    }
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
};


#endif //PROJECT_2_RULE_H
