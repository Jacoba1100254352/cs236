#ifndef PROJECT_2_SCHEME_H
#define PROJECT_2_SCHEME_H


#include "algorithm"
#include <string>
#include <vector>

//
class Scheme : public std::vector<std::string> {
public:
    ///   Constructor   ///
    explicit Scheme(std::vector<std::string> names) : std::vector<std::string>(std::move(names)) { }

    Scheme() = default;

/*    void addNames(const std::string& name) {
        names.push_back(name);
    }
    std::vector<std::string> getNames() {
        return names;
    }*/

    static unsigned index(std::vector<std::string> names, const std::string& value) {
        auto it = std::find(names.begin(), names.end(), value);
        if (it == names.end()) throw std::invalid_argument("Value does not exist, Line: " + to_string(__LINE__)); // in " + std::string(__FILE_NAME__) + "
        return std::distance(names.begin(), it);
    }

    /************************
    *   PRIVATE VARIABLES   *
    ************************/
private:
    std::vector<std::string> names;
};


#endif //PROJECT_2_SCHEME_H
