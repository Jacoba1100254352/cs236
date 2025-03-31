#ifndef PROJECT_2_PARAMETER_H
#define PROJECT_2_PARAMETER_H

#include <string>
#include <utility>

class Parameter {
public:
	explicit Parameter(std::string parameter) : parameter(std::move(parameter)) {}
	std::string getParameter() const {
		return parameter;
	}

	/************************
	*   PRIVATE VARIABLES   *
	************************/
private:
	std::string parameter{};
};


#endif //PROJECT_2_PARAMETER_H
