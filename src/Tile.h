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
    coords coordinates;
    const int XBUFFER = 35;
    const int YBUFFER = 55;

public:
    Tile();
    Tile(const std::vector<Edge*>& _edges, const std::vector<Vertex*>& _vertices);
    Tile(const std::vector<Edge*>& _edges, const std::vector<Vertex*>& _vertices, int key);

    Tile(const std::vector<Edge *> &_edges, const std::vector<Vertex *> &_vertices, int key, resourceType rtype);


    void printTile();

    void setVertex(int index, Vertex* vertex);

    void collectResources(int roll) const;

    void isRobbed(bool robbed);

    resourceType getResourceType();

    int getKey();

    void setCoordinates(int x, int y);

    std::vector<std::tuple<std::string, std::vector<int>>> otherPlayerResources(std::string name);

    coords getCoordinates();

    bool getTile(coords pCoordinates);

    void setVerticeCoords();

    Vertex* getVertice(coords coordinates);
    // resourceType stealResource(std::string name);

};



#endif //TILE_H
