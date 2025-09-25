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
    if (roll == key) {
        for (const auto& vertex : vertices) {
            vertex->collectResources(rtype);
        }
    }

}
