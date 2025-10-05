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

void Card::print() const {
    if (!active) {
        std::cout << name + " (Unavailable): " + description << std::endl;
    }
    else {
        std::cout << name + ": " + description << std::endl;
    }
}

bool Card::isActive() const {
    return active;
}

void Card::makeActive() {
    active = true;
}

std::string Card::getName() {
    return name;
}
