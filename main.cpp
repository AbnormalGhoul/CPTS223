#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <functional>

using namespace std;

// Product class to store all product information
class Product {
public:
    string uniqId;
    string productName;
    string brandName;
    string asin;
    vector<string> categories;
    string upcEanCode;
    string listPrice;
    string sellingPrice;
    string quantity;
    string modelNumber;
    string aboutProduct;
    string productSpecification;
    string technicalDetails;
    string shippingWeight;
    string productDimensions;
    string image;
    string variants;
    string sku;
    string productUrl;
    string stock;
    string productDetails;
    string dimensions;
    string color;
    string ingredients;
    string directionToUse;
    string isAmazonSeller;
    string sizeQuantityVariant;
    string productDescription;

    void printDetails() const {
        cout << "Uniq Id: " << uniqId << endl;
        cout << "Product Name: " << productName << endl;
        cout << "Brand Name: " << brandName << endl;
        cout << "Asin: " << asin << endl;
        cout << "Categories: ";
        for (const auto& cat : categories) {
            cout << cat << " | ";
        }
        cout << endl;
        cout << "List Price: " << listPrice << endl;
        cout << "Selling Price: " << sellingPrice << endl;
        // If I wanted to I would add more fields for all the data values in the .csv file
        // But I don't think I need any more
    }
};

// Hash Table implementation
template <typename K, typename V>
class HashTable {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(K k, V v) : key(k), value(v), next(nullptr) {}
    };

    static const int TABLE_SIZE = 10007; // A large prime number
    Node** table;
    hash<K> hashFunction;

public:
    HashTable() {
        table = new Node*[TABLE_SIZE]();
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* entry = table[i];
            while (entry != nullptr) {
                Node* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
        delete[] table;
    }

    void insert(const K& key, const V& value) {
        int hashValue = hashFunction(key) % TABLE_SIZE;
        Node* prev = nullptr;
        Node* entry = table[hashValue];

        while (entry != nullptr && entry->key != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr) {
            entry = new Node(key, value);
            if (prev == nullptr) {
                table[hashValue] = entry;
            } else {
                prev->next = entry;
            }
        } else {
            entry->value = value; // Update existing
        }
    }

    bool find(const K& key, V& value) {
        int hashValue = hashFunction(key) % TABLE_SIZE;
        Node* entry = table[hashValue];

        while (entry != nullptr) {
            if (entry->key == key) {
                value = entry->value;
                return true;
            }
            entry = entry->next;
        }
        return false;
    }
};

// MultiMap implementation for categories
template <typename K, typename V>
class MultiMap {
private:
    struct ListNode {
        V value;
        ListNode* next;
        ListNode(V v) : value(v), next(nullptr) {}
    };

    struct MapNode {
        K key;
        ListNode* head;
        MapNode* next;
        MapNode(K k) : key(k), head(nullptr), next(nullptr) {}
    };

    MapNode* head;

public:
    MultiMap() : head(nullptr) {}

    ~MultiMap() {
        MapNode* curr = head;
        while (curr != nullptr) {
            MapNode* nextMapNode = curr->next;
            ListNode* currListNode = curr->head;
            while (currListNode != nullptr) {
                ListNode* nextListNode = currListNode->next;
                delete currListNode;
                currListNode = nextListNode;
            }
            delete curr;
            curr = nextMapNode;
        }
    }

    void insert(const K& key, const V& value) {
        MapNode* curr = head;
        MapNode* prev = nullptr;

        // Finds the MapNode with the given key
        while (curr != nullptr && curr->key != key) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == nullptr) {
            // If key is not found, then create a new MapNode
            curr = new MapNode(key);
            if (prev == nullptr) {
                head = curr;
            } else {
                prev->next = curr;
            }
        }

        // Add a new ListNode to the MapNode
        ListNode* newListNode = new ListNode(value);
        newListNode->next = curr->head;
        curr->head = newListNode;
    }

    bool find(const K& key, vector<V>& values) {
        MapNode* curr = head;
        while (curr != nullptr) {
            if (curr->key == key) {
                ListNode* listNode = curr->head;
                while (listNode != nullptr) {
                    values.push_back(listNode->value);
                    listNode = listNode->next;
                }
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
};

// Global data structures
HashTable<string, Product> productTable;
MultiMap<string, pair<string, string>> categoryMap;

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
    getline(file, line); // Skips the header

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

        if (fields.size() < 20) continue; // Skips all the incomplete records

        Product product;
        product.uniqId = fields[0];
        product.productName = fields[1];
        product.brandName = fields[2];
        product.asin = fields[3];
        
        // Parses the categories
        string categoriesStr = fields[4].empty() ? "NA" : fields[4];
        product.categories = split(categoriesStr, '|');
        for (auto& cat : product.categories) {
            cat = trim(cat);
        }

        product.upcEanCode = fields[5];
        product.listPrice = fields[6];
        product.sellingPrice = fields[7];
        product.quantity = fields[8];
        product.modelNumber = fields[9];
        product.aboutProduct = fields[10];
        product.productSpecification = fields[11];
        product.technicalDetails = fields[12];
        product.shippingWeight = fields[13];
        product.productDimensions = fields[14];
        product.image = fields[15];
        product.variants = fields[16];
        product.sku = fields[17];
        product.productUrl = fields[18];
        product.stock = fields[19];

        // Inserts into product table
        productTable.insert(product.uniqId, product);

        // Inserts into category map
        if (product.categories.empty()) {
            categoryMap.insert("NA", make_pair(product.uniqId, product.productName));
        } else {
            for (const auto& cat : product.categories) {
                categoryMap.insert(cat, make_pair(product.uniqId, product.productName));
            }
        }
    }

    file.close();
}

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
        string category = line.substr(14);
        vector<pair<string, string>> products;
        if (categoryMap.find(category, products)) {
            for (const auto& p : products) {
                cout << p.first << " - " << p.second << endl;
            }
        } else {
            cout << "Invalid Category" << endl;
        }
    }
}

void bootStrap() {
    cout << "\n Welcome to the Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";
    
    // Loads data from CSV
    loadData("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data.csv");
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