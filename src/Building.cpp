//
// Created by tvito on 9/16/2025.
//

#include "Building.h"
#include <time.h>

void Building::giveResources(resourceType rType) {
    if (owner != nullptr) {
        owner->addResource(Resource(rType,num));
    }

}

std::string Building::getPlayerName() {
    return owner->getName();
}

std::vector<int> Building::getPlayerResources() {
    return owner->getResources();
}

const std::string Building::getImg() {
    std::string file = "static/";
    switch (num) {
        case 1: file += "settlement_"; break;
        case 2: file += "city_"; break;
        default: return "";
    }
    file += owner->getName();
    file += ".png";

    return file;
}