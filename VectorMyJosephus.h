#ifndef VECTORMYJOSEPHUS_H
#define VECTORMYJOSEPHUS_H

#include "Destination.h"
#include <vector>
#include <iostream>
#include <string>

class VectorMyJosephus {
private:
    int M, N;
    std::vector<Destination> circle;

public:
    VectorMyJosephus(int m, int n, const std::vector<std::string>& cityNames);
    ~VectorMyJosephus();
    void clear();
    bool isEmpty() const;
    int currentSize() const;
    void eliminateDestination();
    void printAllDestinations(std::ostream& os = std::cout) const;};

#endif