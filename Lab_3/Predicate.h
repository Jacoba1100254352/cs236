#ifndef PROJECT_2_PREDICATE_H
#define PROJECT_2_PREDICATE_H

#include "Parameter.h"
#include <utility>
#include <vector>
#include <string>

class Predicate {
private:
    std::string id;
    std::vector<Parameter> parameters;

public:
    explicit Predicate(std::string id) : id(std::move(id)) {}
    void addValue(const std::string& value) {
        parameters.emplace_back(value);
    }
    std::vector<Parameter> getParameters() {
        return parameters;
    }
    std::string toString() {
        std::stringstream out;
        out << id + "(";
        for (unsigned i = 0; i < parameters.size(); i++) {
            out << parameters[i].getData();
            if (i < parameters.size() - 1)
                out << ",";
        }
        out << ")";
        return out.str();
    }
};


#endif //PROJECT_2_PREDICATE_H
