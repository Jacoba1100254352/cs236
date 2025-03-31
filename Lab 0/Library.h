//
// Created by BYU CS 236 on 3/22/2021.
//

#ifndef PROJECT_0_SOLUTION_LIBRARY_H
#define PROJECT_0_SOLUTION_LIBRARY_H

#include <vector>
#include <map>
#include "Book.h"

class Library {
public:
    explicit Library(std::vector<Book*> books);

    static std::string printMap(const std::map<std::string, std::vector<Book*>>& map);

    [[nodiscard]] std::string toString() const;

    friend std::ostream& operator<< (std::ostream& os, const Library& library) {
        os << library.toString();
        return os;
    }

private:
    void organizeBooksByAuthor();
    void organizeBooksByGenre();
    std::vector<Book*> books;
    std::map<std::string, std::vector<Book*>> booksByAuthor;
    std::map<std::string, std::vector<Book*>> booksByGenre;
};


#endif //PROJECT_0_SOLUTION_LIBRARY_H
