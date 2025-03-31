#ifndef PROJECT_2_RELATION_H
#define PROJECT_2_RELATION_H


#include <utility>

#include "set"
#include "Scheme.h"
#include "Tuple.h"

class Relation {

private:

    std::string name;
    Scheme scheme;
    std::set<Tuple> tuples{};

public:

    Relation(std::string name, Scheme scheme) : name(std::move(name)), scheme(std::move(scheme)) { }

    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }

    std::string toString() const {
        std::stringstream out;
        for (auto& tuple : tuples)
            out << tuple.toString(scheme) << std::endl;
        return out.str();
    }

    Relation select(int index, const std::string& value) const {
        Relation result(name, scheme);
        for (auto& tuple : tuples)
            if (tuple.at(index) == value)
                result.addTuple(tuple);
        return result;
    }

};


#endif //PROJECT_2_RELATION_H
