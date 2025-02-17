// VectorMyJosephus.h
#ifndef VECTORMYJOSEPHUS_H
#define VECTORMYJOSEPHUS_H

#include "Destination.h"
#include <vector>
#include <iostream>

class VectorMyJosephus {
private:
    int M, N;
    std::vector<Destination> circle;

public:
    VectorMyJosephus(int m, int n);
    ~VectorMyJosephus();
    void clear();
    bool isEmpty() const;
    int currentSize() const;
    void eliminateDestination();
    void printAllDestinations() const;
};

#endif // VECTORMYJOSEPHUS_H