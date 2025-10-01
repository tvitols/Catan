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

std::tuple<std::string, std::vector<int>> Building::getPlayerInfo(std::string name) {
    if (owner->getName() == name) {
        return std::make_tuple("\t", std::vector<int>());
    }

    std::tuple<std::string, std::vector<int>> result= make_tuple(owner->getName(), owner->getResources());
    return result;
}

resourceType Building::stealResource() {
    srand(time(NULL));
    int randNum = rand() % 5;
    while (!owner->removeResource(Resource(static_cast<resourceType>(randNum), 1))) {
        randNum = rand() % 5;
    }
    return static_cast<resourceType>(randNum);
}