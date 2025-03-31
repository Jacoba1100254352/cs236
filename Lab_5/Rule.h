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

    ///   Get and Set Function   ///
    void addPredicate(const Predicate& p) {
        bodyPredicates.push_back(p);
    }
    Predicate getHeadPredicate() const {
        return headPredicate;
    }
    std::vector<Predicate> getBodyPredicates() const {
        return bodyPredicates;
    }
    Predicate getBodyPredicate(unsigned pred) const {
        return bodyPredicates[pred];
    }

    unsigned size() const {
        return bodyPredicates.size();
    }

    ///   Print Predicate in Rule   ///
    std::string toString() const {
        std::stringstream out;
        out << headPredicate.toString() << " :- ";
        for (const Predicate & bodyPredicate : bodyPredicates)
            out << bodyPredicate.toString() << ((&bodyPredicate != &*(--bodyPredicates.end())) ? "," : "."); // There will always be body predicates so the loop will run no matter what so we don't need to worry about this line as we do in parameters
        return out.str();
    }

    /************************
    *   PRIVATE VARIABLES   *
    ************************/
private:
    Predicate headPredicate{};
    std::vector<Predicate> bodyPredicates{};
};


#endif //PROJECT_2_RULE_H
