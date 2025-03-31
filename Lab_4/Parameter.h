#ifndef PROJECT_2_PARAMETER_H
#define PROJECT_2_PARAMETER_H

#include <string>
#include <utility>

class Parameter {
private:
    std::string parameter{};
public:
    explicit Parameter(std::string parameter) : parameter(std::move(parameter)) {}
    std::string getParameter() {
        return parameter;
    }
};


#endif //PROJECT_2_PARAMETER_H
