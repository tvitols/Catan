//
// Created by lilas on 10/4/2025.
//

#include "VictoryPoint.h"

#include <iostream>

VictoryPoint::VictoryPoint(int i) : Card(names[i], description){}

int VictoryPoint::getType() const{
    return type;
}

void VictoryPoint::print() const {
    std::cout << name + ": " + description << std::endl;
}
