#include <chrono>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <functional>

#include "Product.h"
#include "HashTable.h"
#include "MultiMap.h"
#include "Sort.h"

using namespace std::chrono;
using namespace std;

HashTable<string, Product> productTable;
MultiMap<string, Product> categoryMap;

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

string trim(const string &str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == string::npos) return "";
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

void loadData(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        vector<string> fields;
        string field;
        bool inQuotes = false;
        size_t start = 0;

        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == '"') {
                inQuotes = !inQuotes;
            } else if (line[i] == ',' && !inQuotes) {
                field = line.substr(start, i - start);
                fields.push_back(trim(field));
                start = i + 1;
            }
        }
        field = line.substr(start);
        fields.push_back(trim(field));

        if (fields.size() < 20) continue;

        Product product(fields);
        productTable.insert(product.uniqId, product);

        if (product.categories.empty()) {
            categoryMap.insert("NA", product);
        } else {
            for (const auto& cat : product.categories) {
                categoryMap.insert(cat, product);
            }
        }
    }
    file.close();
}

void printHelp() {
    cout << "Supported commands:\n"
         << "1. find <inventoryid>\n"
         << "2. listInventory <category> [merge] [desc]\n"
         << "\n";
}

bool validCommand(string line) {
    return (line == ":help") ||
           (line.rfind("find ", 0) == 0) ||
           (line.rfind("listInventory ", 0) == 0);
}

#include <chrono>
using namespace std::chrono;

void evalCommand(string line) {
    if (line == ":help") {
        printHelp();
    }
    else if (line.rfind("find ", 0) == 0) {
        string inventoryId = line.substr(5);
        Product product;
        if (productTable.find(inventoryId, product)) {
            product.printDetails();
        } else {
            cout << "Inventory/Product not found" << endl;
        }
    }
    else if (line.rfind("listInventory ", 0) == 0) {
        vector<string> tokens;
        istringstream iss(line);
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            cout << "Invalid syntax. Use :help for reference.\n";
            return;
        }

        string category = tokens[1];
        string sortMethod = "";
        string order = "";

        if (tokens.size() == 3) {
            if (tokens[2] == "desc") {
                order = "desc";
            } else {
                sortMethod = tokens[2];
            }
        } else if (tokens.size() >= 4) {
            sortMethod = tokens[2];
            order = tokens[3];
        }

        vector<Product> results;
        if (categoryMap.find(category, results)) {
            auto comparator = (order == "desc") ?
                [](const Product& a, const Product& b) { return a.getSellingPrice() > b.getSellingPrice(); } :
                [](const Product& a, const Product& b) { return a.getSellingPrice() < b.getSellingPrice(); };

            auto start = high_resolution_clock::now();

            if (sortMethod == "merge") {
                mergeSort<Product>(results, comparator);
            } else {
                insertionSort<Product>(results, comparator);
            }

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start).count();
            cout << "[Timing] Sort completed in " << duration << " microseconds.\n";

            for (const auto& product : results) {
                cout << product.uniqId << " - " << product.productName << " - $" << product.getSellingPrice() << endl;
            }
        } else {
            cout << "Invalid Category" << endl;
        }
    }
}

void bootStrap() {
    cout << "\n Welcome to the Amazon Inventory Query System" << endl;
    cout << " Enter :quit to exit. Type :help for supported commands.\n";
    loadData("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data.csv");
}

int main(int argc, char const *argv[]) {
    string line;
    bootStrap();
    cout << "> ";
    while (getline(cin, line) && line != ":quit") {
        if (validCommand(line)) {
            evalCommand(line);
        } else {
            cout << "Command not supported. Use :help for supported commands." << endl;
        }
        cout << "> ";
    }
    return 0;
}
