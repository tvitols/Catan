//
// Created by tvito on 9/16/2025.
//

#include "Robber.h"

Robber::Robber() : currentTile(nullptr) {
}

void Robber::move(Tile *newTile) {
    currentTile->rob(false);
    currentTile = newTile;
    currentTile->rob(true);
    std::cout << currentTile->getResourceType() << std::endl;
}

void Robber::setCurrentTile(Tile *newTile) {
    currentTile = newTile;
}

Tile* Robber::getCurrentTile() {
    return currentTile;
}

std::vector<std::tuple<std::string, std::vector<int>>> Robber::otherPlayerResources(std::string name) {
    return currentTile->otherPlayerResources(name);
}

// resourceType Robber::stealResource(std::string name) {
//     return currentTile->stealResource(name);
// }
