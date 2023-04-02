#pragma once
#include "String.h"

class Attribute {
public:
    String name;
    String value;

    friend std::ostream& operator<<(std::ostream& os, const Attribute& attribute) {
        os << "ATRYBUT " << attribute.name << " " << attribute.value;
        return os;
    }

    bool operator==(const Attribute& right) const {
        return name == right.name && value == right.value;
    }
};