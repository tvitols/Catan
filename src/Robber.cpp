//
// Created by tvito on 9/16/2025.
//

#include "Robber.h"

Robber::Robber() {
}

void Robber::move(Tile *currentTile) {
    currentTile->isRobbed(false);
    this->currentTile = currentTile;
    this->currentTile->isRobbed(true);
}

void Robber::setCurrentTile(Tile *newTile) {
    currentTile = newTile;
}

std::vector<std::tuple<std::string, std::vector<int>>> Robber::otherPlayerResources(std::string name) {
    return currentTile->otherPlayerResources(name);
}

resourceType Robber::stealResource(std::string name) {
    return currentTile->stealResource(name);
}
