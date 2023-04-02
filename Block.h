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

    Block() : selectorsCount(0), attributesCount(0) {}


    friend std::ostream& operator<<(std::ostream& os, const Block& block) {
        os << block.selectors << block.attributes << "\n\n";
        return os;
    }
};