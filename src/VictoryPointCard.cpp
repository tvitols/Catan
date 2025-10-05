//
// Created by lilas on 10/4/2025.
//

#include "VictoryPointCard.h"

#include <iostream>

VictoryPoint::VictoryPoint(int i) : Card(names[i], description){}

int VictoryPoint::play(void *object) {
    (*(static_cast<int*>(object)))++;
    return 0;
}

int VictoryPoint::getType() const{
    return type;
}
