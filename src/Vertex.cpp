//
// Created by tvito on 9/16/2025.
//

#include "Vertex.h"

void Vertex::collectResources(const resourceType rtype) const {

    if (building != nullptr) {
        building->giveResources(rtype);
    }

}

std::tuple<std::string, std::vector<int>> Vertex::getPlayerInfo(std::string name) {
    std::string playerName = "";
    std::vector<int> playerResources;
    if (building != nullptr) {
        playerName = building->getPlayerName();
        playerResources = building->getPlayerResources();
        if (playerName == name) {
            playerName = "";
        }
    }
    std::tuple<std::string, std::vector<int>> result = std::make_tuple(playerName, playerResources);
    return result;
}

void Vertex::setCoordinates(int x, int y) {
    coordinates.x = x;
    coordinates.y = y;
}

coords Vertex::getCoordinates() {
    return coordinates;
}

bool Vertex::getVertex(coords fCoordinates) {
    if (fCoordinates.x >= coordinates.x - BUFFER && fCoordinates.x <= coordinates.x + BUFFER) {
        if (fCoordinates.y >= coordinates.y - BUFFER && fCoordinates.y <= coordinates.y + BUFFER) {
            return true;
        }
        return false;
    }
    return false;
}

bool Vertex::isOccupied() const {
    return occupied;
}

bool Vertex::setBuilding(Building *pBuilding){
    if (occupied) return false;
    building = pBuilding;
    occupied = true;
    building->getOwner()->addVP(1);
    return true;
}

bool Vertex::upgradeBuilding(Player* player) {
    if (!isOccupied() || building->getOwner() != player || building->isCity()) return false;
    building->upgradeToCity();
    return true;

}

Building * Vertex::getBuilding() const {
    return building;
}

std::string Vertex::getOccupiedImg() {
    return building->getImg();
}

bool Vertex::isPort() const {
    return false;
}

Resource Vertex::stealResources() {
    return building->stealResources();
}

std::string Vertex::getName() {
    if (building != nullptr) {
        return building->getPlayerName();
    }
    return NULL;
}