#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "avl_map.h"
#include "uscity.h"

// Function to randomly sample 'n' elements from a list
template <typename T>
std::vector<T> randomSample(const std::list<T>& source, size_t n) {
    std::vector<T> result(source.begin(), source.end()); // Copy list to vector
    std::shuffle(result.begin(), result.end(), std::mt19937{std::random_device{}()}); // Shuffles the vector
    result.resize(n); 
    return result;
}

// Parses the csv file
void parseCSV(const std::string& filename, avl_map<int, USCity>& avlMap, std::map<int, USCity>& stdMap, std::list<int>& zipCodes) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }
    std::string line;
    bool isFirstLine = true; // To skip the header row
    while (std::getline(file, line)) {
        if (isFirstLine) {
            isFirstLine = false; // Skips the header row
            continue;
        }
        if (line.empty()) {
            continue; // Skips empty lines
        }
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        // Splits the line by commas
        while (std::getline(ss, token, ',')) {
            // Removes quotation marks from the token
            token.erase(std::remove(token.begin(), token.end(), '"'), token.end());
            tokens.push_back(token);
        }
        // Ensures there are enough columns in the CSV
        if (tokens.size() < 5) {
            std::cerr << "Warning: Skipping malformed line: " << line << std::endl;
            continue;
        }
        // Extracts ZIP code (first column)
        try {
            int zip = std::stoi(tokens[0]); // Converts ZIP code to integer
            std::string city = tokens[3];   // City is the 4th column
            std::string state = tokens[4];  // State is the 5th column
            // Inserts into both maps
            avlMap.insert(zip, USCity(city, state));
            stdMap.insert({zip, USCity(city, state)});
            zipCodes.push_back(zip);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Warning: Invalid ZIP code in line: " << line << std::endl;
            continue; // Skips this line if ZIP code is invalid
        }
    }
}

void benchmarkLookups(const avl_map<int, USCity>& avlMap, const std::map<int, USCity>& stdMap, const std::list<int>& zipCodes) {
    // Randomly selects 1000 ZIP codes using our custom function
    std::vector<int> selectedZips = randomSample(zipCodes, 1000);

    // Benchmark avl_map
    auto start = std::chrono::high_resolution_clock::now();
    for (int zip : selectedZips) {
        avlMap.find(zip); // This now calls find (const)
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> avlTime = end - start;

    // Benchmark std::map
    start = std::chrono::high_resolution_clock::now();
    for (int zip : selectedZips) {
        stdMap.find(zip);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> stdTime = end - start;

    std::cout << "avl_map lookup time: " << avlTime.count() << " seconds\n";
    std::cout << "std::map lookup time: " << stdTime.count() << " seconds\n";
}

int main() {
    avl_map<int, USCity> avlMap;
    std::map<int, USCity> stdMap;
    std::list<int> zipCodes;

    parseCSV("uszips.csv", avlMap, stdMap, zipCodes);
    benchmarkLookups(avlMap, stdMap, zipCodes);

    return 0;
}