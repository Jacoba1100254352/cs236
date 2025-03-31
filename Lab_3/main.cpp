#include <iostream>
#include <vector>
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"

int main() {

    std::vector<std::string> names = { "ID", "Name", "Major" };

    Scheme scheme(names);

    Relation relation("student", scheme);

    std::vector<std::string> values[] = {
            {"'42'", "'Ann'", "'CS'"},
            {"'32'", "'Bob'", "'CS'"},
            {"'64'", "'Ned'", "'EE'"},
            {"'16'", "'Jim'", "'EE'"},
    };

    for (auto& value : values) {
        Tuple tuple(value);
        std::cout << tuple.toString(scheme) << std::endl;
        relation.addTuple(tuple);
    }

    std::cout << "relation:" << std::endl;
    std::cout << relation.toString();

    Relation result = relation.select(2, "'CS'");

    std::cout << "select Major='CS' result:" << std::endl;
    std::cout << result.toString();

}
