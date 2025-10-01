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

// resourceType Vertex::stealResources() {
//     if (building != nullptr) {
//         return building->stealResource();
//     }
//     return null;
// }