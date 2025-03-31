#ifndef PROJECT_2_RELATION_H
#define PROJECT_2_RELATION_H


#include <utility>

#include "set"
#include "Scheme.h"
#include "Tuple.h"

//
class Relation {
public:
    ///   Constructor   ///
    Relation(std::string name, Scheme scheme) : name(std::move(name)), scheme(std::move(scheme)) { }
    Relation() = default;

    ///      ///
    bool addTuple(const Tuple& tuple) { // if the tuple was not already in the set this returns true, otherwise false
        return tuples.insert(tuple).second;
    }
    unsigned size() const {
        return tuples.size();
    }

    ///      ///
    std::string toString() const {
        std::stringstream out;
        if (!Tuple(scheme).empty())
            for (const Tuple & tuple : tuples)
                out << "  " << tuple.toString(scheme) << std::endl;
        return out.str();
    }

    ///      ///
    const string& getName() const {
        return name;
    }
    void setName(const string& tempName) {
        Relation::name = tempName;
    }

    ///      ///
    const Scheme& getScheme() const {
        return scheme;
    }
    void setScheme(const Scheme& tempScheme) {
        scheme = tempScheme;
    }

    ///   Select Functions   ///
    Relation select(unsigned index, const std::string& value) const {
        Relation result(name, scheme);
        for (const Tuple & tuple : tuples)
            if (tuple.at(index) == value)
                result.addTuple(tuple);
        return result;
    }
    Relation select(unsigned index1, unsigned index2) const {
        Relation result(name, scheme);
        for (const Tuple & tuple : tuples)
            if (tuple.at(index1) == tuple.at(index2))
                result.addTuple(tuple);
        return result;
    }

    // prints every unique tuple based on the col provided
    Relation project(const std::vector<unsigned>& colsToKeep) {
/*         Iterate, make new header, pushback old header at column
        Scheme newScheme;
        std::cout << "colsToKeep size = " << colsToKeep.size() << " and scheme size = " << scheme.size() << " and scheme.getNames() size = " << scheme.getNames().size() << std::endl;
        for (const unsigned & col : colsToKeep)
            newScheme.addNames(scheme.at(col));

         v replace scheme*/
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
        for (const Tuple & tuple : tuples)
            result.addTuple(tuple);
        return result;
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
