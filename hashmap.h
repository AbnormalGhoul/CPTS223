#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <vector>
#include <functional>

template <typename K, typename V>
class HashMap {
private:
    struct Entry {
        K key;
        V value;
        Entry* next;
        
        Entry(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    std::vector<Entry*> buckets;
    size_t bucketCount;
    size_t itemCount;
    float loadFactor;
    
    size_t hash(const K& key) const {
        std::hash<K> hasher;
        return hasher(key) % bucketCount;
    }
    
    void rehash() {
        size_t newBucketCount = bucketCount * 2;
        std::vector<Entry*> newBuckets(newBucketCount, nullptr);
        
        for (size_t i = 0; i < bucketCount; ++i) {
            Entry* entry = buckets[i];
            while (entry != nullptr) {
                Entry* next = entry->next;
                size_t newIndex = std::hash<K>{}(entry->key) % newBucketCount;
                
                entry->next = newBuckets[newIndex];
                newBuckets[newIndex] = entry;
                
                entry = next;
            }
        }
        
        buckets = std::move(newBuckets);
        bucketCount = newBucketCount;
    }

public:
    HashMap(size_t initialCapacity = 16, float loadFactor = 0.75f) 
        : bucketCount(initialCapacity), itemCount(0), loadFactor(loadFactor) {
        buckets.resize(bucketCount, nullptr);
    }
    
    ~HashMap() {
        clear();
    }
    
    void insert(const K& key, const V& value) {
        if (itemCount >= bucketCount * loadFactor) {
            rehash();
        }
        
        size_t index = hash(key);
        Entry* entry = buckets[index];
        
        // Check if key already exists
        while (entry != nullptr) {
            if (entry->key == key) {
                entry->value = value; // Update existing value
                return;
            }
            entry = entry->next;
        }
        
        // Insert new entry at head of chain
        Entry* newEntry = new Entry(key, value);
        newEntry->next = buckets[index];
        buckets[index] = newEntry;
        itemCount++;
    }
    
    bool find(const K& key, V& value) const {
        size_t index = hash(key);
        Entry* entry = buckets[index];
        
        while (entry != nullptr) {
            if (entry->key == key) {
                value = entry->value;
                return true;
            }
            entry = entry->next;
        }
        
        return false;
    }

    bool find(const K& key, const V*& value) const {
        size_t index = hash(key);
        Entry* entry = buckets[index];
        
        while (entry != nullptr) {
            if (entry->key == key) {
                value = &entry->value;
                return true;
            }
            entry = entry->next;
        }
        
        return false;
    }
    
    void clear() {
        for (size_t i = 0; i < bucketCount; ++i) {
            Entry* entry = buckets[i];
            while (entry != nullptr) {
                Entry* next = entry->next;
                delete entry;
                entry = next;
            }
            buckets[i] = nullptr;
        }
        itemCount = 0;
    }
    
    size_t size() const {
        return itemCount;
    }
};

#endif // HASHMAP_H