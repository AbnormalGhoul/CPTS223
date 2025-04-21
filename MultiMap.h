#ifndef MULTIMAP_H
#define MULTIMAP_H

#include <vector>
using namespace std;

// Multimap implementation
// Maps a key to multiple values (stored in a linked list)
template <typename K, typename V>
class MultiMap {
private:
    struct ListNode {
        V value;
        ListNode* next;
        ListNode(const V& v) : value(v), next(nullptr) {}
    };

    struct MapNode {
        K key;
        ListNode* head;
        MapNode* next;
        MapNode(const K& k) : key(k), head(nullptr), next(nullptr) {}
    };

    MapNode* head;

public:
    MultiMap() : head(nullptr) {}

    ~MultiMap() {
        MapNode* m = head;
        while (m) {
            ListNode* l = m->head;
            while (l) {
                ListNode* tempL = l;
                l = l->next;
                delete tempL;
            }
            MapNode* tempM = m;
            m = m->next;
            delete tempM;
        }
    }

    void insert(const K& key, const V& value) {
        MapNode* curr = head;
        MapNode* prev = nullptr;
        while (curr && curr->key != key) {
            prev = curr;
            curr = curr->next;
        }

        if (!curr) {
            curr = new MapNode(key);
            if (!prev) head = curr;
            else prev->next = curr;
        }

        ListNode* newNode = new ListNode(value);
        newNode->next = curr->head;
        curr->head = newNode;
    }

    bool find(const K& key, vector<V>& results) {
        MapNode* curr = head;
        while (curr) {
            if (curr->key == key) {
                ListNode* node = curr->head;
                while (node) {
                    results.push_back(node->value);
                    node = node->next;
                }
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
};

#endif