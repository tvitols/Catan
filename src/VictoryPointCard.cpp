//
// Created by lilas on 10/4/2025.
//

#include "VictoryPointCard.h"

#include <iostream>

VictoryPoint::VictoryPoint(int i) : Card(names[i], "Adds 1 Victory Point"){}

int VictoryPoint::play(void* object) {
    (*(static_cast<int*>(object)))++;
    std::cout << "You got a victory point!" << std::endl;
    return 0;
}

int VictoryPoint::getType() const{
    return type;
}
