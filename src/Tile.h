//
// Created by tvito on 9/16/2025.
//

#ifndef TILE_H
#define TILE_H
#include <vector>
#include "Edge.h"
#include "Vertex.h"


class Tile {
    bool hasRobber = false;
    std::vector<Edge*> edges = std::vector<Edge*>(6);
    std::vector<Vertex*> vertices = std::vector<Vertex*>(6);

public:
    Tile();
    Tile(const std::vector<Edge*>& _edges, const std::vector<Vertex*>& _vertices);

    void printTile();

    void setVertex(int index, Vertex* vertex);

};



#endif //TILE_H
