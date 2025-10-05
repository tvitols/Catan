//
// Created by lilas on 10/4/2025.
//

#include "RoadBuilding.h"

RoadBuilding::RoadBuilding() : Card("Road Building", "Builds 2 Roads"){}

int RoadBuilding::play(void* object) {
    return 2;
}

int RoadBuilding::getType() const {
    return type;
}