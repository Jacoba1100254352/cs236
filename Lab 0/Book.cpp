#include <string>
#include <sstream>
#include <utility>
#include "Book.h"

Book::Book(const std::string& title, const std::string& author) {
    this->title = title;
    this->author = author;
    genreSet = false;
    hoursSet = false;
    pagesSet = false;
}

void Book::setGenre(const std::string& gnr) {
    this->genre = gnr;
    genreSet = true;
}

void Book::setPages(const std::string& pgs) {
    int numPages;
    try {
        numPages = stoi(pgs);
        if (numPages < 0)
            throw "Invalid argument";
    }
    catch (const std::invalid_argument& e) {
        throw "Page value must be a whole number.";
    }
    this->pages = numPages;
    pagesSet = true;
}

void Book::setHours(const std::string& hrs) {
    double numHours;
    try {
        numHours = stod(hrs);
        if (numHours < 0)
            throw "Invalid argument";
    }
    catch (const std::invalid_argument& e) {
        throw "Hour value must be a positive number.";
    }
    this->hours = numHours;
    hoursSet = true;
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getGenre() const {
    return genre;
}

int Book::getPages() const {
    return pages;
}

double Book::getHours() const {
    return hours;
}

bool Book::hasGenre() const {
    return genreSet;
}

bool Book::hasPages() const {
    return pagesSet;
}

bool Book::hasHours() const {
    return hoursSet;
}

std::string Book::toString() const {
    std::ostringstream output;
    output << getTitle() << " by " << getAuthor();
    return output.str();
}
