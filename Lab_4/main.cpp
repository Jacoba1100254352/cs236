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
    //ifstream infile("../input.txt");
    ifstream infile(argv[1]);
    stringstream buffer;
    buffer << infile.rdbuf();
    infile.close();

    //Interpreter interpreter(Parser(Scanner(buffer.str()).scanToken()).datalogProgram());
    //interpreter.run();

    Relation studentRelation("students", Scheme( {"ID", "Name", "Major"} ));

    vector<string> studentValues[] = {
            {"'42'", "'Ann'", "'CS'"},
            {"'64'", "'Ned'", "'EE'"},
    };

    for (auto& value : studentValues)
        studentRelation.addTuple(Tuple(value));

    studentRelation.join(studentRelation);

    Relation courseRelation("courses", Scheme( {"ID", "Course"} ));

    vector<string> courseValues[] = {
            {"'42'", "'CS 100'"},
            {"'32'", "'CS 232'"},
    };

    for (auto& value : courseValues)
        courseRelation.addTuple(Tuple(value));

    studentRelation.join(courseRelation);


    return 0;
}
