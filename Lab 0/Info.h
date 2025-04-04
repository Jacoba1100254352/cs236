//
// Created by BYU CS 236 on 3/22/2021.
//

#ifndef PROJECT_0_SOLUTION_INFO_H
#define PROJECT_0_SOLUTION_INFO_H

#include <string>

class Info {
public:
    enum InfoType {TITLE, AUTHOR, GENRE, PAGES, HOURS, UNRECOGNIZED};
    Info(const std::string& type, const std::string& info);
    InfoType getType();
    std::string getInfo();
    static std::string enumToString(InfoType type);
private:
    InfoType type;
    std::string info;
    static InfoType stringToEnum(const std::string& string);
};


#endif //PROJECT_0_SOLUTION_INFO_H
