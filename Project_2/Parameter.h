#ifndef PROJECT_2_PARAMETER_H
#define PROJECT_2_PARAMETER_H

#include <string>


class Parameter {
private:
	std::string data{};

public:
	explicit Parameter(std::string data) : data(std::move(data)) {}

	std::string getData()
	{
		return data;
	}
};


#endif //PROJECT_2_PARAMETER_H
