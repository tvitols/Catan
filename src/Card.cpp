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
    std::string top = "__";
    const std::string side = "|";
    for (int i = 0; i < name.length(); i++) {
        top += "_";
    }
    std::cout << top << std::endl;
    std::cout << side << name << side << std::endl;
    for (int i = 0; i < description.length()%name.size(); i++) {
        std::cout << side << description.substr(i*name.size(),name.size()) << side << std::endl;
    }
    std::cout << top << std::endl;
}

bool Card::isActive() const {
    return active;
}

void Card::makeActive() {
    active = true;
}
