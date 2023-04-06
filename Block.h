#pragma once
#include "String.h"
#include "LinkedList.h"
#include "Attribute.h"

class Block {
public:
    LinkedList<String> selectors;
    LinkedList<Attribute> attributes;
    int selectorsCount;
    int attributesCount;
    bool deleted;

    Block() : selectorsCount(0), attributesCount(0), deleted(true) {}


    friend std::ostream& operator<<(std::ostream& os, const Block& block) {
        os << block.selectors << block.attributes << "\n\n";
        return os;
    }
};