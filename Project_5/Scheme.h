#ifndef PROJECT_2_SCHEME_H
#define PROJECT_2_SCHEME_H

#include "algorithm"
#include <string>
#include <vector>

// the general form that the Facts, Rules, and Queries will follow: Snap(A, B, C, D)
class Scheme : public std::vector<std::string> {
public:
	///   Constructor   ///
	explicit Scheme(std::vector<std::string> names) : std::vector<std::string>(std::move(names)) {}
	Scheme() = default;
};


#endif //PROJECT_2_SCHEME_H
