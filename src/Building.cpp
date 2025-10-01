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


// resourceType Building::stealResource() {
//     srand(time(NULL));
//     int randNum = rand() % 5;
//     while (!owner->removeResource(Resource(static_cast<resourceType>(randNum), 1))) {
//         randNum = rand() % 5;
//     }
//     return static_cast<resourceType>(randNum);
// }