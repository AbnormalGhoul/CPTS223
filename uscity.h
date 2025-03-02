#ifndef USCITY_H
#define USCITY_H

#include <string>

class USCity {
public:
    std::string city;
    std::string state;

    USCity(const std::string& c = "", const std::string& s = "")
        : city(c), state(s) {}
};

#endif