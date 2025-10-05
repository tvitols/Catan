//
// Created by tvito on 9/16/2025.
//

#include "Building.h"
#include <time.h>

Building::Building(Player* pOwner) : Structure(), num(1){
    owner = pOwner;
}

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

bool Building::isCity() {
    return num == 2;
}

void Building::upgradeToCity() {
    num = 2;
    owner->addVP(1);
}

std::string Building::getImg() const {
    std::string file = "static/";
    switch (num) {
        case 1: file += "settlement_"; break;
        case 2: file += "city_"; break;
        default: return "";
    }
    file += owner->getColor();
    file += ".png";

    return file;
}

void Building::setTrade(Trade pTrade) {
    owner->addTrade(pTrade);
}


Resource Building::stealResources() {
    srand(time(NULL));
    int randNum = rand() % 5;
    while (getPlayerResources()[randNum] == 0) {
        randNum = rand() % 5;
    }
    owner->removeResource(Resource(static_cast<resourceType>(randNum),1));
    return Resource(static_cast<resourceType>(randNum),1);
}