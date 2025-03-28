#include "product.h"
#include <sstream>
#include <algorithm>
#include <iostream> // Added this line

Product::Product(const std::string& csvLine) {
    std::istringstream ss(csvLine);
    std::string field;

    // Helper lambda to read a quoted field
    auto readQuotedField = [&](std::istringstream& ss) {
        std::string field;
        if (ss.peek() == '"') {
            ss.get(); // skip opening quote
            std::getline(ss, field, '"'); // read until closing quote
            if (ss.peek() == ',') ss.get(); // skip comma if present
        } else {
            std::getline(ss, field, ',');
        }
        return field;
    };

    // Parse each field
    uniqId = readQuotedField(ss);
    productName = readQuotedField(ss);
    brandName = readQuotedField(ss);
    asin = readQuotedField(ss);
    
    // Parse categories (split by |)
    std::string categoriesStr = readQuotedField(ss);
    if (categoriesStr.empty()) {
        categories.push_back("NA");
    } else {
        std::istringstream catStream(categoriesStr);
        std::string category;
        while (std::getline(catStream, category, '|')) {
            // Trim whitespace from category
            category.erase(0, category.find_first_not_of(" \t"));
            category.erase(category.find_last_not_of(" \t") + 1);
            categories.push_back(category);
        }
    }

    upcEanCode = readQuotedField(ss);
    listPrice = readQuotedField(ss);
    sellingPrice = readQuotedField(ss);
    quantity = readQuotedField(ss);
    modelNumber = readQuotedField(ss);
    aboutProduct = readQuotedField(ss);
    productSpecification = readQuotedField(ss);
    technicalDetails = readQuotedField(ss);
    shippingWeight = readQuotedField(ss);
    productDimensions = readQuotedField(ss);
    image = readQuotedField(ss);
    variants = readQuotedField(ss);
    sku = readQuotedField(ss);
    productUrl = readQuotedField(ss);
    stock = readQuotedField(ss);
    productDetails = readQuotedField(ss);
    dimensions = readQuotedField(ss);
    color = readQuotedField(ss);
    ingredients = readQuotedField(ss);
    directionToUse = readQuotedField(ss);
    isAmazonSeller = readQuotedField(ss);
    sizeQuantityVariant = readQuotedField(ss);
    productDescription = readQuotedField(ss);
}

void Product::printDetails() const {
    std::cout << "Uniq Id: " << uniqId << "\n";
    std::cout << "Product Name: " << productName << "\n";
    std::cout << "Brand Name: " << (brandName.empty() ? "N/A" : brandName) << "\n";
    std::cout << "ASIN: " << asin << "\n";
    
    std::cout << "Categories: ";
    for (size_t i = 0; i < categories.size(); ++i) {
        if (i != 0) std::cout << " | ";
        std::cout << categories[i];
    }
    std::cout << "\n";
    
    std::cout << "Price: " << (sellingPrice.empty() ? "N/A" : sellingPrice) << "\n";
    std::cout << "Quantity: " << (quantity.empty() ? "N/A" : quantity) << "\n";
    std::cout << "Model Number: " << (modelNumber.empty() ? "N/A" : modelNumber) << "\n";
    std::cout << "Shipping Weight: " << (shippingWeight.empty() ? "N/A" : shippingWeight) << "\n";
    std::cout << "Product Dimensions: " << (productDimensions.empty() ? "N/A" : productDimensions) << "\n";
}

void Product::printSummary() const {
    std::cout << "ID: " << uniqId << " | Name: " << productName << "\n";
}