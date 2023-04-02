#pragma once
#include <iostream>

template<class T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int linkedListSize;
public:
    LinkedList() : head(nullptr), tail(nullptr), linkedListSize(0) {}


    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }


    bool isEmpty() const {
        return head == nullptr;
    }


    int GetSize() const {
        return linkedListSize;
    }


    void PushBack(const T& data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        linkedListSize++;
    }


    void Pop(Node* node) {
        if (node == head) {
            head = head->next;
        }
        else {
            Node* previous = head;
            while (previous->next != node) {
                previous = previous->next;
            }
            previous->next = node->next;
        }
        linkedListSize--;
    }


    Node* operator[](int index) const {
        Node* current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current;
    }


    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
        Node* current = list.head;
        while (current != nullptr) {
            os << current->data << "\n";
            current = current->next;
        }
        return os;
    }


    Node* FindNode(const T& data) const {
        Node* current = head;
        while (current != nullptr && !(current->data == data)) {
            current = current->next;
        }
        return current;
    }
};