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
    std::tuple<std::string, std::vector<int>> result = std::make_tuple("\n", std::vector<int>());
    if (building) {
        result = building->getPlayerInfo(name);
    }
    return result;
}

resourceType Vertex::stealResources() {
    return building->stealResource();
}