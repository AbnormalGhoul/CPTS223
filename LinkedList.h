#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Node class template
template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

// LinkedList class template
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

public:
    // Constructor
    LinkedList() : head(nullptr), size(0) {}

    // Deconstructor
    ~LinkedList() {
        clear();
    }

    // Utility Function
    void insertAtFront(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        size++;
    }

    // Utility Function
    bool removeNode(const T& value) {
        if (!head) return false;

        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }

        Node<T>* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }

        if (current->next) {
            Node<T>* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return true;
        }
        return false;
    }

    // Utility Function
    void display() const {
        Node<T>* current = head;
        while (current) {
            cout << current->data.first << ": " << current->data.second << endl;
            current = current->next;
        }
    }

    // Utility Function
    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    // Utility Function
    int getSize() const {
        return size;
    }

    // Utility Function
    Node<T>* getHead() const {
        return head;
    }

    // Utility Function
    void setHead(Node<T>* newHead) {
        head = newHead;
    }

    // This function loads the data from the commands.csv file
    void loadFromCSV(const string& filename) {
        // Checks if file is open
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        // Will go through the file until the file is empty
        while (getline(file, line)) {
            stringstream ss(line);
            string command, description;

            // Parsing the data from the .csv file and putting it into a linked list
            if (getline(ss, command, ',') && getline(ss, description, ',')) {
                insertAtFront(make_pair(command, description));
            }
        }
        file.close();
    }

    // This function accepts a string of a filename and saves all data to said file
    // This function is mainly for commands.csv
    void saveToCSV(const string& filename) {
        ofstream file(filename);

        // Checks if file is open
        if (!file.is_open()) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        // Goes through the list and adds them to the file
        Node<T>* current = head;
        while (current) {
            file << current->data.first << "," << current->data.second << "\n";
            current = current->next;
        }

        file.close();
    }
};

#endif