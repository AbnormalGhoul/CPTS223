#include "inventorysystem.h"
#include <fstream>
#include <iostream>

bool InventorySystem::loadInventory(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }

    // Skip header line
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        try {
            Product product(line);
            
            // Add to id map
            idToProductMap.insert(product.uniqId, product);
            
            // Add to category map
            const Product* productPtr = nullptr;
            if (idToProductMap.find(product.uniqId, productPtr)) {
                for (const auto& category : product.categories) {
                    categoryToProductsMap.insert(category, productPtr);
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << e.what() << "\n";
            continue;
        }
    }

    file.close();
    return true;
}

const Product* InventorySystem::findProduct(const std::string& inventoryId) const {
    const Product* product = nullptr;
    if (idToProductMap.find(inventoryId, product)) {
        return product;
    }
    return nullptr;
}

std::vector<const Product*> InventorySystem::listProductsByCategory(const std::string& category) const {
    std::vector<const Product*> result;
    std::vector<const Product*> products;
    
    if (categoryToProductsMap.find(category, products)) {
        for (const auto& product : products) {
            result.push_back(product);
        }
    }
    return result;
}