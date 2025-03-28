#ifndef MULTIMAP_H
#define MULTIMAP_H

#include <string>
#include <vector>
#include <functional>

// Forward declaration
template <typename K, typename V> class HashMap;

template <typename K, typename V>
class MultiMap {
private:
    HashMap<K, std::vector<V>> map;

public:
    void insert(const K& key, const V& value);
    bool find(const K& key, std::vector<V>& values) const;
    void clear();
    size_t size() const;
};

// Include HashMap after the class definition
#include "hashmap.h"

template <typename K, typename V>
void MultiMap<K, V>::insert(const K& key, const V& value) {
    std::vector<V> values;
    if (map.find(key, values)) {
        values.push_back(value);
        map.insert(key, values);
    } else {
        map.insert(key, {value});
    }
}

template <typename K, typename V>
bool MultiMap<K, V>::find(const K& key, std::vector<V>& values) const {
    return map.find(key, values);
}

template <typename K, typename V>
void MultiMap<K, V>::clear() {
    map.clear();
}

template <typename K, typename V>
size_t MultiMap<K, V>::size() const {
    return map.size();
}

#endif // MULTIMAP_H