#ifndef AVL_MAP_H
#define AVL_MAP_H

#include <algorithm>
#include <iostream>
#include <stack>

// AVLNode class
template <typename Key, typename Value>
class AVLNode {
public:
    Key key;
    Value value;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const Key& k, const Value& v)
        : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
};

// avl-map class
template <typename Key, typename Value>
class avl_map {
private:
    AVLNode<Key, Value>* root;
    // Helper functions for AVL operations
    int height(AVLNode<Key, Value>* node) {
        return node ? node->height : 0;
    }
    int balanceFactor(AVLNode<Key, Value>* node) {
        return height(node->right) - height(node->left);
    }

    // AVL Tree Right Rotation
    AVLNode<Key, Value>* rotateRight(AVLNode<Key, Value>* node) {
        AVLNode<Key, Value>* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        node->height = std::max(height(node->left), height(node->right)) + 1;
        leftChild->height = std::max(height(leftChild->left), height(leftChild->right)) + 1;
        return leftChild;
    }

    // AVL Tree Left Rotation
    AVLNode<Key, Value>* rotateLeft(AVLNode<Key, Value>* node) {
        AVLNode<Key, Value>* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        node->height = std::max(height(node->left), height(node->right)) + 1;
        rightChild->height = std::max(height(rightChild->left), height(rightChild->right)) + 1;
        return rightChild;
    }

    // Function for determining if balance factor is off (and fixes it, w/ rotations)
    AVLNode<Key, Value>* balance(AVLNode<Key, Value>* node) {
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->right) < 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->left) > 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        return node;
    }

    // Inserts nodes into the AVL tree (recursively)
    AVLNode<Key, Value>* insertHelper(AVLNode<Key, Value>* node, const Key& key, const Value& value) {
        if (!node) return new AVLNode<Key, Value>(key, value);
        if (key < node->key)
            node->left = insertHelper(node->left, key, value);
        else if (key > node->key)
            node->right = insertHelper(node->right, key, value);
        else
            node->value = value; // Update value if key already exists
        node->height = std::max(height(node->left), height(node->right)) + 1;
        return balance(node);
    }

    // Deletes nodes from AVL tree (recursively)
    AVLNode<Key, Value>* eraseHelper(AVLNode<Key, Value>* node, const Key& key) {
        if (!node) return nullptr;
        if (key < node->key)
            node->left = eraseHelper(node->left, key);
        else if (key > node->key)
            node->right = eraseHelper(node->right, key);
        else {
            if (!node->left || !node->right) {
                AVLNode<Key, Value>* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            AVLNode<Key, Value>* temp = findMin(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = eraseHelper(node->right, temp->key);
        }
        node->height = std::max(height(node->left), height(node->right)) + 1;
        return balance(node);
    }

    AVLNode<Key, Value>* findMin(AVLNode<Key, Value>* node) {
        while (node->left) node = node->left;
        return node;
    }

public:
    avl_map() : root(nullptr) {}

    void insert(const Key& key, const Value& value) {
        root = insertHelper(root, key, value);
    }

    void erase(const Key& key) {
        root = eraseHelper(root, key);
    }

    // Non-const version of find
    Value* find(const Key& key) {
        AVLNode<Key, Value>* current = root;
        while (current) {
            if (key < current->key)
                current = current->left;
            else if (key > current->key)
                current = current->right;
            else
                return &current->value;
        }
        return nullptr;
    }

    // Const version of find
    const Value* find(const Key& key) const {
        const AVLNode<Key, Value>* current = root;
        while (current) {
            if (key < current->key)
                current = current->left;
            else if (key > current->key)
                current = current->right;
            else
                return &current->value;
        }
        return nullptr;
    }

    // Iterator class
    class iterator {
    private:
        AVLNode<Key, Value>* current;
        std::stack<AVLNode<Key, Value>*> stack; // Stack for in-order traversal

        void pushLeft(AVLNode<Key, Value>* node) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
        }

    public:
        iterator(AVLNode<Key, Value>* node) {
            pushLeft(node); // Initializes the stack with the leftmost nodes
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            } else {
                current = nullptr;
            }
        }

        Value& operator*() { return current->value; }

        iterator& operator++() {
            if (current->right) {
                pushLeft(current->right); // Moves to the leftmost node of the right subtree
            }
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            } else {
                current = nullptr; // End of traversal
            }
            return *this;
        }
        bool operator!=(const iterator& other) { return current != other.current; }
    };
    iterator begin() { return iterator(root); }
    iterator end() { return iterator(nullptr); }
};

#endif 