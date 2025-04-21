#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

class Product {
public:
    string uniqId;
    string productName;
    string brandName;
    string asin;
    vector<string> categories;
    string sellingPrice;

    Product() = default;

    // Constructor using CSV fields
    Product(const vector<string>& fields) {
        uniqId = fields[0];
        productName = fields[1];
        brandName = fields[2];
        asin = fields[3];

        string categoriesStr = fields[4].empty() ? "NA" : fields[4];
        stringstream ss(categoriesStr);
        string category;
        while (getline(ss, category, '|')) {
            categories.push_back(trim(category));
        }

        sellingPrice = fields[7];
    }

    // Converts price string to float
    float getSellingPrice() const {
        try {
            string cleaned = sellingPrice;
            cleaned.erase(remove(cleaned.begin(), cleaned.end(), '$'), cleaned.end());
            cleaned.erase(remove(cleaned.begin(), cleaned.end(), ','), cleaned.end());
            return stof(cleaned);
        } catch (...) {
            return 0.0f;
        }
    }

    void printDetails() const {
        cout << fixed << setprecision(2);
        cout << "Uniq Id: " << uniqId << endl;
        cout << "Product Name: " << productName << endl;
        cout << "Brand Name: " << brandName << endl;
        cout << "ASIN: " << asin << endl;
        cout << "Categories: ";
        for (const auto& cat : categories) {
            cout << cat << " | ";
        }
        cout << endl;
        cout << "Selling Price: $" << getSellingPrice() << endl;
    }

private:
    static string trim(const string &str) {
        size_t start = str.find_first_not_of(" \t\n\r");
        if (start == string::npos) return "";
        size_t end = str.find_last_not_of(" \t\n\r");
        return str.substr(start, end - start + 1);
    }
};

#endif