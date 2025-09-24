//
// Created by tvito on 9/16/2025.
//

#include "Tile.h"

Tile::Tile() = default;

Tile::Tile(const std::vector<Edge *>& _edges, const std::vector<Vertex *>& _vertices) {
    this->edges = _edges;
    this->vertices = _vertices;
}

void Tile::printTile() {

}

void Tile::setVertex(int index, Vertex *vertex) {
    vertices[index] = vertex;
}
