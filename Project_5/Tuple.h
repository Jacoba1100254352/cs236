#ifndef PROJECT_2_TUPLE_H
#define PROJECT_2_TUPLE_H

#include <utility>
#include <sstream>
#include <string>
#include <vector>
#include "Scheme.h"

//
class Tuple : public std::vector<std::string> {
public:
	///   Constructor   ///
	explicit Tuple(std::vector<std::string> values) : std::vector<std::string>(std::move(values)) {}
	Tuple() = default;

	///   Print Function   ///
	std::string toString(const Scheme& scheme) const {
		std::stringstream out;
		for (unsigned i = 0; i < size(); i++) {
			if (i > 0) out << ", ";
			out << scheme.at(i) << "=" << at(i);
		}
		return out.str();
	}
};


#endif //PROJECT_2_TUPLE_H
