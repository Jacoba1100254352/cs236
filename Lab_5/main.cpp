//#include <iostream>
//#include <map>
#include <fstream>
#include <vector>
#include "Token.h"
#include "Parser.h"
#include "Scanner.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Interpreter.h"
#include "Node.h"
#include "Graph.h"

int main(int argc, char *argv[]) {
    std::stringstream buffer;
    std::string input = argv[1]; //"../project4-passoff/80/input84.txt"; // "../input.txt"; // argv[1];
    buffer << std::ifstream(input).rdbuf();

    Interpreter(Parser(Scanner(buffer.str()).scanToken()).datalogProgram()).run();


    return 0;
}

/*int main() {

    // predicate names for fake rules
    // first is name for head predicate
    // second is names for body predicates
    std::pair<std::string,std::vector<std::string>> ruleNames[] = {
            { "A", { "B", "C" } },
            { "B", { "A", "D" } },
            { "B", { "B" } },
            { "E", { "F", "G" } },
            { "E", { "E", "F" } },
    };

    std::vector<Rule> rules;

    for (std::pair<std::string, std::vector<std::string>> & rulePair : ruleNames) {
        Rule rule = Rule(Predicate(rulePair.first));
        for (std::string & bodyName : rulePair.second)
            rule.addPredicate(Predicate(bodyName));
        rules.push_back(rule);
    }

    std::cout << Interpreter::makeGraph(rules).toString();
}*/
