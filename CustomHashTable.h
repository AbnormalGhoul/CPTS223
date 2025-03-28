// #ifndef CUSTOMHASHTABLE_H
// #define CUSTOMHASHTABLE_H

// #include <iostream>
// #include <vector>
// #include <list>
// #include <string>
// #include <functional>

// // Structure to represent an inventory item
// struct Product {
//     std::string id;
//     std::string name;
//     std::string category;
//     std::string details;

//     Product() {} // Default constructor

//     Product(std::string id, std::string name, std::string cat, std::string det)
//         : id(id), name(name), category(cat), details(det) {}
// };


// // Custom hash table using separate chaining
// template <typename K, typename V>
// class CustomHashTable {
// private:
//     std::vector<std::list<std::pair<K, V>>> table;
//     size_t capacity;
//     size_t size;
    
//     size_t hashFunction(const K& key) const {
//         return std::hash<K>{}(key) % capacity;
//     }
    
// public:
//     CustomHashTable(size_t cap = 1000) : capacity(cap), size(0) {
//         table.resize(capacity);
//     }
    
//     void insert(const K& key, const V& value) {
//         size_t index = hashFunction(key);
//         for (auto& pair : table[index]) {
//             if (pair.first == key) {
//                 pair.second = value;
//                 return;
//             }
//         }
//         table[index].emplace_back(key, value);
//         size++;
//     }
    
//     bool find(const K& key, V& value) const {
//         size_t index = hashFunction(key);
//         for (const auto& pair : table[index]) {
//             if (pair.first == key) {
//                 value = pair.second;
//                 return true;
//             }
//         }
//         return false;
//     }
    
//     std::vector<V> findByCategory(const std::string& category) const {
//         std::vector<V> result;
//         for (const auto& bucket : table) {
//             for (const auto& pair : bucket) {
//                 if (pair.second.category == category) {
//                     result.push_back(pair.second);
//                 }
//             }
//         }
//         return result;
//     }

//     void forEach(std::function<void(const std::string&, Product&)> func) {
//         for (auto& bucket : table) { // Assuming `table` is a vector of lists
//             for (auto& pair : bucket) {
//                 func(pair.first, pair.second);
//             }
//         }
//     }
    
// };

// #endif // CUSTOMHASHTABLE_H
