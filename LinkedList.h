// LinkedList.h
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T data) : data(data), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
public:
    LinkedList() : head(nullptr) {}
    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    void insertAtFront(T data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = head;
        head = newNode;
    }

    void removeNode(T data) {
        Node<T>* current = head;
        Node<T>* previous = nullptr;

        while (current != nullptr && current->data != data) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) return;

        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }

        delete current;
    }

    Node<T>* getHead() const {
        return head;
    }
};

#endif // LINKEDLIST_H