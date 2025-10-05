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

Vertex* Tile::getVertex(const int index) const {
    return vertices[index];
}

Edge* Tile::getEdge(const int index) const {
    return edges[index];
}

void Tile::collectResources(const int roll) const {
    //Makes sure it is not the desert tile, that the key got rolled, and that it isn't robbed
    if (rtype != null && roll == key && !hasRobber) {
        //Iterates through Vertices
        for (const auto& vertex : vertices) {
            vertex->collectResources(rtype);
        }
    }

}

void Tile::rob(bool robbed) {
    hasRobber = robbed;
}

bool Tile::isRobbed() const {
    return hasRobber;
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
    //Iterates through Vertices
    for (const auto& vertex : vertices) {
        //Makes sure the info from getPlayerInfo is valid
        if (get<0>(vertex->getPlayerInfo(name)) != ""){
            //Adds it to the vector
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
    //Checks if the coordinates are within the BUFFERs
    if (pCoordinates.x >= (coordinates.x -XBUFFER) && pCoordinates.x <= (coordinates.x + XBUFFER)) {
        if (pCoordinates.y >= (coordinates.y -YBUFFER) && pCoordinates.y <= (coordinates.y + YBUFFER)) {
            return true;
        }
        return false;
    }
    return false;
}

void Tile::setVerticeCoords() {
    //Setting Vertice coordinates based on Tile coordinates
    vertices[0]->setCoordinates(coordinates.x, coordinates.y - 70);
    vertices[1]->setCoordinates(coordinates.x + 50, coordinates.y - 32);
    vertices[2]->setCoordinates(coordinates.x + 50, coordinates.y + 32);
    vertices[3]->setCoordinates(coordinates.x, coordinates.y + 70);
    vertices[4]->setCoordinates(coordinates.x - 50, coordinates.y + 32);
    vertices[5]->setCoordinates(coordinates.x - 50, coordinates.y - 32);
}

void Tile::setEdgeCoords() {
    //Setting Edge coordinates based on Tile coordinates
    edges[0]->setCoordinates(coordinates.x + 25, coordinates.y - 51, left);
    edges[1]->setCoordinates(coordinates.x + 50, coordinates.y, upright);
    edges[2]->setCoordinates(coordinates.x + 25, coordinates.y + 51, right);
    edges[3]->setCoordinates(coordinates.x - 25, coordinates.y + 51, left);
    edges[4]->setCoordinates(coordinates.x - 50, coordinates.y, upright);
    edges[5]->setCoordinates(coordinates.x - 25, coordinates.y - 51, right);
}

Edge* Tile::getEdge(coords coordinates) {
    //Iterating through Edges
    for (Edge *edge : edges) {
        //If the Edge is correct, returning the Edge
        if (edge->getEdge(coordinates)) {
            return edge;
        }
    }
    return nullptr;
}

Vertex* Tile::getVertice(const coords pCoordinates) const {
    //Iterating through Vertices
    for (Vertex *vertex : vertices) {
        //If the Vertex is correct, returning the vertex
        if (vertex->getVertex(pCoordinates)) {
            return vertex;
        }
    }
    return nullptr;
}

Resource Tile::stealResource(std::string name) {
    for (const auto& vertex : vertices) {
        //Checking if the name of a building on the Vertex is the correct name
        if (vertex->getName() == name) {
            return vertex->stealResources();
        }
    }
    return Resource(null, 0);
}
