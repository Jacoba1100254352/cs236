#ifndef PROJECT_2_DATALOGPROGRAM_H
#define PROJECT_2_DATALOGPROGRAM_H

#include <sstream>
#include <set>
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {
private:
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Predicate> queries;
    std::vector<Rule> rules;
    std::set<std::string> domain;
public:
    void addToSchemes(Predicate& p) {
        schemes.push_back(p);
    }
    void addToFacts(Predicate& p) {
        facts.push_back(p);
    }
    void addToQueries(Predicate& p) {
        queries.push_back(p);
    }
    void addToRules(Rule& r) {
        rules.push_back(r);
    }
    void addToDomain(const std::string& d) {
        domain.insert(d);
    }
    std::string toString() {
        std::stringstream out;
        out << "Schemes(" << schemes.size() << ((schemes.empty()) ? "):\n" : "):\n  ");
        for (unsigned i = 0; i < schemes.size(); i++) {
            out << schemes[i].toString() << "\n";
            if (i != schemes.size() - 1)
                out << "  ";
        }
        out << "Facts(" << facts.size() << ((facts.empty()) ? "):\n" : "):\n  ");
        for (unsigned i = 0; i < facts.size(); i++) {
            out << facts[i].toString() << ".\n";
            if (i != facts.size() - 1)
                out << "  ";
        }
        out << "Rules(" << rules.size() << ((rules.empty()) ? "):\n" : "):\n  ");
        for (unsigned i = 0; i < rules.size(); i++) {
            out << rules[i].toString() << "\n";
            if (i != rules.size() - 1)
                out << "  ";
        }
        out << "Queries(" << queries.size() << ((queries.empty()) ? "):\n" : "):\n  ");
        for (unsigned i = 0; i < queries.size(); i++) {
            out << queries[i].toString() << "?\n";
            if (i != queries.size() - 1)
                out << "  ";
        }
        out << "Domain(" << domain.size() << ((domain.empty()) ? "):\n" : "):\n  ");
        for (auto & d : domain) {
            out << d;
            out << ((&d != &*(--domain.end())) ? "\n  " : "\n");
        }
        return out.str();
    }
};


#endif //PROJECT_2_DATALOGPROGRAM_H
