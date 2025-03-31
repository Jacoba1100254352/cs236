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

int main(int argc, char *argv[]) {
    //ifstream infile("../project3-passoff/60/input61.txt");
    //ifstream infile("../project3-passoff/20/input24.txt");
    ifstream infile(argv[1]);
    stringstream buffer;
    buffer << infile.rdbuf();
    infile.close();

    Interpreter interpreter(Parser(Scanner(buffer.str()).scanToken()).datalogProgram());
    interpreter.run();
    //std::vector<std::string> names = { "ID", "Name", "Major" };
    //
    //Scheme scheme(names);
    //
    //Relation relation("student", scheme);
    //
    //std::vector<std::string> values[] = {
    //        {"'42'", "'Ann'", "'CS'"},
    //        {"'32'", "'Bob'", "'CS'"},
    //        {"'64'", "'Ned'", "'EE'"},
    //        {"'16'", "'Jim'", "'EE'"},
    //};
    //
    //for (auto& value : values) {
    //    Tuple tuple(value);
    //    std::cout << tuple.toString(scheme) << std::endl; // Format it with the names=value
    //    relation.addTuple(tuple); // add each to the relation
    //}
    //
    //std::cout << relation.project({2}).toString();
}
