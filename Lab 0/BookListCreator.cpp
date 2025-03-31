//
// Created by BYU CS 236 on 3/22/2021.
//

#include <iostream>
#include "BookListCreator.h"

BookListCreator::BookListCreator(std::ifstream& input) : bookCreator(input) {}

std::vector<Book*> BookListCreator::createBookList() {
    while (bookCreator.hasMoreBooksToCreate())
        bookList.push_back(bookCreator.createBook());

    return bookList;
}
