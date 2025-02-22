#include "ListMyJosephus.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> readDestinationsFromCSV(const std::string& filename) {
    std::vector<std::string> cityNames;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return cityNames;
    }

    std::string line;
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string city;
        while (std::getline(ss, city, ';')) {
            cityNames.push_back(city);
        }
    }

    file.close();
    return cityNames;
}

int main() {
    // Opens the results.log file for writing
    std::ofstream logFile("results.log", std::ios::app); // Append mode
    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open results.log for writing." << std::endl;
        return 1;
    }

    // Reads city names from CSV
    std::vector<std::string> cityNames = readDestinationsFromCSV("destinations.csv");
    if (cityNames.empty()) {
        std::cerr << "No destinations found in the CSV file." << std::endl;
        logFile << "No destinations found in the CSV file." << std::endl;
        logFile.close();
        return 1;
    }

    // Randomly selects N and M
    int N = cityNames.size(); // Use all cities from the CSV
    int M = rand() % (N - 1) + 1; // Random M where 1 <= M < N

    // Logs the parameters
    logFile << "ListMyJosephus Simulation: N = " << N << ", M = " << M << std::endl;

    // Initializes the game
    ListMyJosephus game(M, N, cityNames);

    // Runs simulation and measures time
    clock_t start = clock();
    game.eliminateDestination();
    clock_t end = clock();

    // Logs the final destination
    logFile << "Final Destination: ";
    game.printAllDestinations(logFile);

    // Logs the execution time
    double executionTime = (double)(end - start) / CLOCKS_PER_SEC;
    logFile << "Execution Time: " << executionTime << " seconds" << std::endl;
    logFile << "----------------------------------------" << std::endl;

    // Closes the log file
    logFile.close();

    return 0;
}