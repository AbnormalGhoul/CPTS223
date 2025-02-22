#ifndef DESTINATION_H
#define DESTINATION_H

#include <string>
#include <iostream>

class Destination {
private:
    int position;
    std::string name;

public:
    Destination(int pos, std::string cityName);
    ~Destination();
    void printPosition() const;
    void printDestinationName() const;
    std::string getName() const;
};

#endif