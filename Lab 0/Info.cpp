//
// Created by BYU CS 236 on 3/22/2021.
//

#include "Info.h"

#include <utility>

Info::Info(const std::string& type, const std::string& info) {
    this->type = stringToEnum(type);
    this->info = info;
}

std::string Info::enumToString(Info::InfoType type) {
    switch(type) {
        case TITLE:
            return "title";
        case AUTHOR:
            return "author";
        case GENRE:
            return "genre";
        case PAGES:
            return "pages";
        case HOURS:
            return "hours";
        default:
            return "";
    }
}

Info::InfoType Info::stringToEnum(const std::string& string) {
    return (string == "title") ? TITLE :
           (string == "author") ? AUTHOR :
           (string == "genre") ? GENRE :
           (string == "pages") ? PAGES :
           (string == "hours") ? HOURS :
                                 UNRECOGNIZED;
}

Info::InfoType Info::getType() {
    return type;
}

std::string Info::getInfo() {
    return info;
}
