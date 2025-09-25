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
    int key;
    resourceType rtype;
    std::vector<Edge*> edges = std::vector<Edge*>(6);
    std::vector<Vertex*> vertices = std::vector<Vertex*>(6);

public:
    Tile();
    Tile(const std::vector<Edge*>& _edges, const std::vector<Vertex*>& _vertices);
    Tile(const std::vector<Edge*>& _edges, const std::vector<Vertex*>& _vertices, int key);

    Tile(const std::vector<Edge *> &_edges, const std::vector<Vertex *> &_vertices, int key, resourceType rtype);


    void printTile();

    void setVertex(int index, Vertex* vertex);

    void collectResources(int roll) const;

};



#endif //TILE_H
