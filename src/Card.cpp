//
// Created by tvito on 9/16/2025.
//

#include "Card.h"

#include <iostream>
#include <ostream>

Card::Card(std::string pName, std::string pDescription) {
    name = pName;
    description = pDescription;
}

void Card::play(void (*func)()) {
    if (isActive()) {
        func();
    }
}

void Card::print() const {
    std::cout << name + ": " + description << std::endl;
}

bool Card::isActive() const {
    return active;
}

void Card::makeActive() {
    active = true;
}
