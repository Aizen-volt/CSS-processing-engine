#pragma once
#define BLOCKS_IN_ARRAY 8

#include <iostream>
#include "Block.h"

using namespace std;

class Node {
public:
    Block* blocks;
    int blocksInUse;
    Node* next;
    Node* prev;

    Node() : next(nullptr), prev(nullptr) {
        blocksInUse = 1;
        blocks = new Block[BLOCKS_IN_ARRAY];
    }


    ~Node() {
        delete[] blocks;
    }


    Block& operator[](int index) const {
        if (index >= 0 && index < BLOCKS_IN_ARRAY)
            return blocks[index];
    }


    friend std::ostream& operator<<(std::ostream& os, Node* node) {
        for (int i = 0; i < node->blocksInUse; i++) {
            os << node->blocks[i];
        }
        return os;
    }
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;
    int doublyLinkedListSize;
    int allBlocksInUse;
    int blocksDeleted;

    DoublyLinkedList() : head(nullptr), tail(nullptr), doublyLinkedListSize(0), blocksDeleted(0), allBlocksInUse(1) {}


    ~DoublyLinkedList() {
        while (head->next != nullptr) {
            Node* current;
            current = head;
            head = head->next;
            delete current;
        }
    }


    int GetSize() const {
        return doublyLinkedListSize;
    }


    void AddNewNode() {
        Node* newNode = new Node();
        doublyLinkedListSize++;
        if (head == nullptr) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }


    void RemoveNode(Node* node) {
        doublyLinkedListSize--;
        //only node
        if (node == head && node == tail) {
            head = tail = nullptr;
            delete node;
            return;
        }
        //first node
        if (node == head) {
            head = node->next;
            head->prev = nullptr;
            delete node;
            return;
        }
        //last node
        if (node == tail) {
            tail = node->prev;
            tail->next = nullptr;
            delete node;
            return;
        }
        //middle node
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
    }


    Node* operator[](int index) const {
        return (index / 2 > doublyLinkedListSize) ? TraverseFromEnd(index) : TraverseFromStart(index);
    }


    Node* TraverseFromStart(int index) const {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current;
    }


    Node* TraverseFromEnd(int index) const {
        Node* current = tail;
        for (int i = doublyLinkedListSize - 1; i > index; i--) {
            current = current->prev;
        }
        return current;
    }


    bool AddNewBlock(Node* node) {
        bool nodeCreated = false;
        if (node->blocksInUse == BLOCKS_IN_ARRAY) {
            AddNewNode();
            node = node->next;
            nodeCreated = true;
        }
        else
            node->blocksInUse++;
        allBlocksInUse++;
        return nodeCreated;
    }


    int PrintBlocksCount() const {
        Node* current = head;
        int counter = 0;
        while (current != nullptr) {
            counter += current->blocksInUse;
            current = current->next;
        }
        return counter;
    }


    void PrintLastAttribute(const String& selectorName, const String& attributeName) const {
        Node* node = tail;
        while (node != nullptr) {
            for (int blockNumber = node->blocksInUse - 1; blockNumber >= 0; blockNumber--) {
                for (int selectorNumber = 0; selectorNumber < node->blocks[blockNumber].selectorsCount; selectorNumber++) {
                    if (node->blocks[blockNumber].selectors[selectorNumber]->data == selectorName) {
                        for (int attributeNumber = 0; attributeNumber < node->blocks[blockNumber].attributesCount; attributeNumber++) {
                            if (node->blocks[blockNumber].attributes[attributeNumber]->data.name == attributeName) {
                                cout << selectorName << ",E," << attributeName << " == " << node->blocks[blockNumber].attributes[attributeNumber]->data.value << "\n";
                                return;
                            }
                        }
                        break;
                    }
                }
            }

            node = node->prev;
        }
    }


    void PrintAttValue(const String& sectionNumber, const String& attName, int nodeNumber, int blockNumber) {
        Node* node = nodeNumber > doublyLinkedListSize / 2 ? TraverseFromEnd(nodeNumber) : TraverseFromStart(nodeNumber);
        int attributesCount = node->blocks[blockNumber].attributesCount;
        for (int i = 0; i < attributesCount; i++) {
            if (node->blocks[blockNumber].attributes[i]->data.name == attName) {
                cout << sectionNumber << ",A," << attName << " == " << node->blocks[blockNumber].attributes[i]->data.value << "\n";
                return;
            }
        }
    }


    void CountAttribute(const String& attName) {
        Node* node = head;
        int counter = 0;
        while (node != nullptr) {
            for (int blockNumber = 0; blockNumber < node->blocksInUse; blockNumber++) {
                for (int attributeNumber = 0; attributeNumber < node->blocks[blockNumber].attributesCount; attributeNumber++) {
                    if (node->blocks[blockNumber].attributes[attributeNumber]->data.name == attName) {
                        counter++;
                        break;
                    }
                }
            }
            node = node->next;
        }
        cout << attName << ",A,? == " << counter << "\n";
    }


    void CountSelector(const String& selector) {
        Node* node = head;
        int counter = 0;
        while (node != nullptr) {
            for (int blockNumber = 0; blockNumber < node->blocksInUse; blockNumber++) {
                for (int selectorNumber = 0; selectorNumber < node->blocks[blockNumber].selectorsCount; selectorNumber++) {
                    if (node->blocks[blockNumber].selectors[selectorNumber]->data == selector) {
                        counter++;
                        break;
                    }
                }
            }
            node = node->next;
        }
        cout << selector << ",S,? == " << counter << "\n";
    }


    void AddSelector(const String& selector, int currentNode, int currentBlock) {
        Node* current = currentNode > doublyLinkedListSize / 2 ? TraverseFromEnd(currentNode) : TraverseFromStart(currentNode);
        current->blocks[currentBlock].selectors.PushBack(selector);
        current->blocks[currentBlock].selectorsCount++;
    }


    bool FindAttribute(const Attribute& attribute, int currentNode, int currentBlock) {
        Node* current = currentNode > doublyLinkedListSize / 2 ? TraverseFromEnd(currentNode) : TraverseFromStart(currentNode);
        int attributesToCheck = current->blocks[currentBlock].attributesCount;
        for (int i = 0; i < attributesToCheck; i++) {
            if (attribute.name == current->blocks[currentBlock].attributes[i]->data.name) {
                current->blocks[currentBlock].attributes[i]->data.value = attribute.value;
                return true;
            }
        }
        return false;
    }


    void AddAttribute(const Attribute& attribute, int currentNode, int currentBlock) {
        Node* current = currentNode > doublyLinkedListSize / 2 ? TraverseFromEnd(currentNode) : TraverseFromStart(currentNode);
        current->blocks[currentBlock].attributes.PushBack(attribute);
        current->blocks[currentBlock].attributesCount++;
    }


    void RemoveLastBlock(Node* node) {
        node->blocksInUse--;
        allBlocksInUse--;
        if (node->blocksInUse <= 0)
            RemoveNode(node);
    }


    bool RemoveBlock(int nodeNumber, int blockNumber) {
        if (nodeNumber >= doublyLinkedListSize)
            return false;

        Node* current = (nodeNumber > doublyLinkedListSize / 2 ? TraverseFromEnd(nodeNumber) : TraverseFromStart(nodeNumber));

        if (blockNumber >= current->blocksInUse)
            return false;

        if (current->blocksInUse == 1) {
            RemoveNode(current);

            return true;
        }

        if (current->blocksInUse > blockNumber) {
            for (int i = blockNumber + 1; i < current->blocksInUse; i++) {
                current->blocks[i - 1] = current->blocks[i];
            }
        }
        current->blocksInUse--;
        allBlocksInUse--;
        return false;
    }


    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList& list) {
        for (int i = 0; i < list.doublyLinkedListSize; i++) {
            os << list[i];
        }
        return os;
    }
};