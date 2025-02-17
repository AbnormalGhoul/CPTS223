// TestListMyJosephus.cpp
#include "ListMyJosephus.h"
#include <iostream>
#include <ctime>

int main() {
    int M = 3, N = 10;
    ListMyJosephus game(M, N);
    clock_t start = clock();
    game.eliminateDestination();
    clock_t end = clock();
    game.printAllDestinations();
    std::cout << "Execution Time: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
    return 0;
}