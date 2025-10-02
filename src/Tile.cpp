//
// Created by tvito on 9/16/2025.
//

#include "Tile.h"


// Constructors
Tile::Tile() : key(0), rtype() {}
Tile::Tile(const std::vector<Edge *>& _edges, const std::vector<Vertex *>& _vertices) : key(0), rtype(), edges(_edges), vertices(_vertices){}
Tile::Tile(const std::vector<Edge *> &_edges, const std::vector<Vertex *> &_vertices, const int key) : key(key), rtype(), edges(_edges), vertices(_vertices) {}
Tile::Tile(const std::vector<Edge *> &_edges, const std::vector<Vertex *> &_vertices, const int key, const resourceType rtype) : key(key), rtype(rtype), edges(_edges), vertices(_vertices) {}

void Tile::printTile() {

}

void Tile::setVertex(int index, Vertex *vertex) {
    vertices[index] = vertex;
}

void Tile::collectResources(const int roll) const {
    if (rtype != null && roll == key && !hasRobber) {
        for (const auto& vertex : vertices) {
            vertex->collectResources(rtype);
        }
    }

}

void Tile::isRobbed(bool robbed) {
    hasRobber = robbed;
}

resourceType Tile::getResourceType() {
    return rtype;
}

int Tile::getKey() {
    return key;
}

std::vector<std::tuple<std::string, std::vector<int>>> Tile::otherPlayerResources(std::string name) {
    std::vector<std::tuple<std::string, std::vector<int>>> playerResources;
    std::tuple<std::string, std::vector<int>> vertexInfo;
    for (const auto& vertex : vertices) {
        if (get<0>(vertex->getPlayerInfo(name)) != ""){
            vertexInfo = vertex->getPlayerInfo(name);
            playerResources.push_back(vertexInfo);
        }
    }
    return playerResources;
}

void Tile::setCoordinates(int x, int y) {
    coordinates.x = x;
    coordinates.y = y;
}

coords Tile::getCoordinates() {
    return coordinates;
}

bool Tile::getTile(coords pCoordinates) {
    if (pCoordinates.x >= (coordinates.x -XBUFFER) && pCoordinates.x <= (coordinates.x + XBUFFER)) {
        if (pCoordinates.y >= (coordinates.y -YBUFFER) && pCoordinates.y <= (coordinates.y + YBUFFER)) {
            return true;
        }
        return false;
    }
    return false;
}

void Tile::setVerticeCoords() {
    vertices[0]->setCoordinates(coordinates.x, coordinates.y - 70);
    vertices[1]->setCoordinates(coordinates.x + 50, coordinates.y - 32);
    vertices[2]->setCoordinates(coordinates.x + 50, coordinates.y + 32);
    vertices[3]->setCoordinates(coordinates.x, coordinates.y + 70);
    vertices[4]->setCoordinates(coordinates.x - 50, coordinates.y + 32);
    vertices[5]->setCoordinates(coordinates.x - 50, coordinates.y - 32);
}

Vertex* Tile::getVertice(coords coordinates) {
    for (Vertex *vertex : vertices) {
        if (vertex->getVertex(coordinates)) {
            return vertex;
        }
    }
    return nullptr;
}

// resourceType Tile::stealResource(std::string name) {
//     for (const auto& vertex : vertices) {
//         if (get<0>(vertex->getPlayerInfo(name)) == "\t") {
//             return vertex->stealResources();
//         }
//     }
// }
