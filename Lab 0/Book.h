//
// Created by BYU CS 236 on 3/22/2021.
//

#ifndef PROJECT_0_SOLUTION_BOOK_H
#define PROJECT_0_SOLUTION_BOOK_H

#include <string>
#include <iostream>

class Book {
public:
    Book(const std::string& title, const std::string& author);

    void setGenre(const std::string& genre);

    void setPages(const std::string& pages);

    void setHours(const std::string& hours);

    [[nodiscard]] std::string getTitle() const;

    [[nodiscard]] std::string getAuthor() const;

    [[nodiscard]] std::string getGenre() const;

    [[nodiscard]] int getPages() const;

    [[nodiscard]] double getHours() const;

    [[nodiscard]] bool hasGenre() const;

    [[nodiscard]] bool hasPages() const;

    [[nodiscard]] bool hasHours() const;

    [[nodiscard]] std::string toString() const;

    friend std::ostream& operator<< (std::ostream& os, const Book& book) {
        os << book.toString();
        return os;
    }

private:
    std::string title;
    std::string author;
    std::string genre = "uncategorized";
    int pages = 0;
    double hours = 0;
    bool genreSet;
    bool pagesSet;
    bool hoursSet;
};


#endif //PROJECT_0_SOLUTION_BOOK_H
