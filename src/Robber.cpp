//
// Created by tvito on 9/16/2025.
//

#include "Robber.h"

Robber::Robber() {
}

void Robber::move(Tile *newTile) {
    currentTile->isRobbed(false);
    currentTile = newTile;
    currentTile->isRobbed(true);
    std::cout << currentTile->getResourceType() << std::endl;
}

void Robber::setCurrentTile(Tile *newTile) {
    currentTile = newTile;
}

resourceType Robber::getCurrentTile() {
    return currentTile->getResourceType();
}

std::vector<std::tuple<std::string, std::vector<int>>> Robber::otherPlayerResources(std::string name) {
    return currentTile->otherPlayerResources(name);
}

// resourceType Robber::stealResource(std::string name) {
//     return currentTile->stealResource(name);
// }
