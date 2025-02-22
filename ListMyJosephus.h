#ifndef LISTMYJOSEPHUS_H
#define LISTMYJOSEPHUS_H

#include "Destination.h"
#include <list>
#include <iostream>
#include <vector>
#include <string>

class ListMyJosephus {
private:
    int M, N;
    std::list<Destination> circle;

public:
    ListMyJosephus(int m, int n, const std::vector<std::string>& cityNames);
    ~ListMyJosephus();
    void clear();
    bool isEmpty() const;
    int currentSize() const;
    void eliminateDestination();
    void printAllDestinations(std::ostream& os = std::cout) const;};

#endif