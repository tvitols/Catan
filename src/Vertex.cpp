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
        //Obtaining player info from the Building
        playerName = building->getPlayerName();
        playerResources = building->getPlayerResources();
        //Changing playerName if it equals the name passed
        if (playerName == name) {
            playerName = "";
        }
    }
    //Returning a tuple of the name and resources of the player associated with the Vertex
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
    //Checking if the coordinates are within the BUFFER of the Vertex
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
    //Adding Building
    building = pBuilding;
    occupied = true;
    //Incrementing the owner's victory points
    building->getOwner()->addVP(1);
    return true;
}

bool Vertex::upgradeBuilding(Player* player) {
    //Checking if there is a building, if the owner of said building is the correct player
    //and if the building is already a city
    if (!isOccupied() || building->getOwner() != player || building->isCity()) return false;
    //If all correct, upgrading the building to a city
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
    return "";
}