//
// Created by tvito on 9/16/2025.
//

#include "Robber.h"

Robber::Robber() : currentTile(nullptr) {
}

void Robber::move(Tile *newTile) {
    //Changes Tile
    currentTile->rob(false);
    currentTile = newTile;
    //Stops new currentTile to give resources to players
    currentTile->rob(true);
}

void Robber::setCurrentTile(Tile *newTile) {
    currentTile = newTile;
    currentTile->rob(true);
}

Tile* Robber::getCurrentTile() {
    return currentTile;
}

std::vector<std::tuple<std::string, std::vector<int>>> Robber::otherPlayerResources(std::string name) {
    return currentTile->otherPlayerResources(name);
}

Resource Robber::getRandomResource(std::string name) {
    return currentTile->stealResource(name);
}
