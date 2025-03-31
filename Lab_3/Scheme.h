#ifndef PROJECT_2_SCHEME_H
#define PROJECT_2_SCHEME_H

#include <utility>

#include "string"
#include "vector"

class Scheme : public std::vector<std::string> {

public:

    explicit Scheme(std::vector<std::string> names) : std::vector<std::string>(std::move(names)) { }

};


#endif //PROJECT_2_SCHEME_H
