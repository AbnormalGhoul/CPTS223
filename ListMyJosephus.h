// ListMyJosephus.h
#ifndef LISTMYJOSEPHUS_H
#define LISTMYJOSEPHUS_H

#include "Destination.h"
#include <list>
#include <iostream>

class ListMyJosephus {
private:
    int M, N;
    std::list<Destination> circle;

public:
    ListMyJosephus(int m, int n);
    ~ListMyJosephus();
    void clear();
    bool isEmpty() const;
    int currentSize() const;
    void eliminateDestination();
    void printAllDestinations() const;
};

#endif // LISTMYJOSEPHUS_H