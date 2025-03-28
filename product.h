#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

class Product {
public:
    std::string uniqId;
    std::string productName;
    std::string brandName;
    std::string asin;
    std::vector<std::string> categories;
    std::string upcEanCode;
    std::string listPrice;
    std::string sellingPrice;
    std::string quantity;
    std::string modelNumber;
    std::string aboutProduct;
    std::string productSpecification;
    std::string technicalDetails;
    std::string shippingWeight;
    std::string productDimensions;
    std::string image;
    std::string variants;
    std::string sku;
    std::string productUrl;
    std::string stock;
    std::string productDetails;
    std::string dimensions;
    std::string color;
    std::string ingredients;
    std::string directionToUse;
    std::string isAmazonSeller;
    std::string sizeQuantityVariant;
    std::string productDescription;

    // Constructor that parses a CSV line
    Product(const std::string& csvLine);

    // Print all product details
    void printDetails() const;

    // Print summary (id and name)
    void printSummary() const;
};

#endif // PRODUCT_H