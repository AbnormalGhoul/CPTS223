#include <iostream>
#include <string>
#include "inventorysystem.h"

using namespace std;

InventorySystem inventorySystem;

void printHelp() {
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
}

bool validCommand(string line) {
    return (line == ":help") ||
           (line.rfind("find ", 0) == 0) ||
           (line.rfind("listInventory ", 0) == 0);
}

void evalCommand(string line) {
    if (line == ":help") {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find ", 0) == 0) {
        string inventoryId = line.substr(5);
        const Product* product = inventorySystem.findProduct(inventoryId);
        if (product) {
            product->printDetails();
        } else {
            cout << "Inventory/Product not found" << endl;
        }
    }
    // if line starts with listInventory
    else if (line.rfind("listInventory ", 0) == 0) {
        string category = line.substr(13);
        auto products = inventorySystem.listProductsByCategory(category);
        if (!products.empty()) {
            for (const auto& product : products) {
                product->printSummary();
            }
            cout << "Found " << products.size() << " products in category '" << category << "'" << endl;
        } else {
            cout << "Invalid Category" << endl;
        }
    }
}

void bootStrap() {
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    
    // Load inventory data with the correct filename
    if (!inventorySystem.loadInventory("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data.csv")) {
        cout << "Failed to load inventory data. Exiting." << endl;
        exit(1);
    }
    
    cout << "\n> ";
}

int main(int argc, char const *argv[]) {
    string line;
    bootStrap();
    while (getline(cin, line) && line != ":quit") {
        if (validCommand(line)) {
            evalCommand(line);
        } else {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    return 0;
}