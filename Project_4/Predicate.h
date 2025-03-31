#ifndef PROJECT_2_PREDICATE_H
#define PROJECT_2_PREDICATE_H

#include "Parameter.h"
#include <utility>
#include <vector>
#include <string>

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
    std::string getName() {
        return id;
    }

    ///   Print Predicate and their Parameters   ///
    std::string toString() {
        std::stringstream out;
        out << id + "(";
        for (unsigned i = 0; i < parameters.size(); i++) {
            out << parameters.at(i).getParameter();
            if (i < parameters.size() - 1)
                out << ",";
        }
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
