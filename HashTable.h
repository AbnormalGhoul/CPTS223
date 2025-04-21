#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <functional>
#include <string>

using namespace std;

// A hash table using separate chaining
template <typename K, typename V>
class HashTable {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    static const int TABLE_SIZE = 10007; // large prime
    Node** table;
    hash<K> hashFunction;

public:
    HashTable() {
        table = new Node*[TABLE_SIZE]();
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* entry = table[i];
            while (entry) {
                Node* temp = entry;
                entry = entry->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(const K& key, const V& value) {
        int index = hashFunction(key) % TABLE_SIZE;
        Node* entry = table[index];
        Node* prev = nullptr;

        while (entry && entry->key != key) {
            prev = entry;
            entry = entry->next;
        }

        if (!entry) {
            Node* newNode = new Node(key, value);
            if (!prev) table[index] = newNode;
            else prev->next = newNode;
        } else {
            entry->value = value;
        }
    }

    bool find(const K& key, V& value) {
        int index = hashFunction(key) % TABLE_SIZE;
        Node* entry = table[index];
        while (entry) {
            if (entry->key == key) {
                value = entry->value;
                return true;
            }
            entry = entry->next;
        }
        return false;
    }
};

#endif
