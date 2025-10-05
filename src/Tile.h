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
    //roll that accesses tile
    int key;
    resourceType rtype;
    std::vector<Edge*> edges = std::vector<Edge*>(6);
    std::vector<Vertex*> vertices = std::vector<Vertex*>(6);
    coords coordinates;
    //buffer for getTile
    const int XBUFFER = 35;
    const int YBUFFER = 55;

public:
    /**
     * default constructor
     */
    Tile();
    /**
     * initializes variables, setting key to 0
     * @param _edges vector of Edges
     * @param _vertices vector of Vertices
     */
    Tile(const std::vector<Edge*>& _edges, const std::vector<Vertex*>& _vertices);
    /**
     * initializes variables
     * @param _edges vector of Edges
     * @param _vertices vector of Vertices
     * @param key key of Tile
     */
    Tile(const std::vector<Edge*>& _edges, const std::vector<Vertex*>& _vertices, int key);

    /**
     * initializes variables
     * @param _edges vector of Edges
     * @param _vertices vector of Vertices
     * @param key key of Tile
     * @param rtype resourceType of Tile
     */
    Tile(const std::vector<Edge *> &_edges, const std::vector<Vertex *> &_vertices, int key, resourceType rtype);


    /**
     * prints Tile
     */
    void printTile();

    /**
     * sets vertices[index] to vertex
     * @param index index of vertex
     * @param vertex
     */
    void setVertex(int index, Vertex* vertex);

    /**
     *
     * @param index index of vertex
     * @return vertices[index]
     */
    Vertex* getVertex(int index) const;

    /**
     *
     * @param index index of edge
     * @return edges[index]
     */
    Edge* getEdge(int index) const;

    /**
     * if roll equals key, tile is not robbed, and resourceType is not null,
     * iterates through vertices and calls vertex->collectResources(rtype)
     * @param roll roll of player
     */
    void collectResources(int roll) const;

    /**
     * sets rob to robbed
     * @param robbed
     */
    void rob(bool robbed);

    /**
     *
     * @return robbed
     */
    bool isRobbed() const;

    /**
     *
     * @return resourceTyep
     */
    resourceType getResourceType();

    /**
     *
     * @return key
     */
    int getKey();

    /**
     * sets coordinates.x to x and coordinates.y to y
     * @param x x coordinate
     * @param y y coordinate
     */
    void setCoordinates(int x, int y);

    /**
     * iterates through vertices
     * if the name of vertex->getPlayerInfo(name) != ""
     * pushes back vertex->getPlayerInfo(name)
     * @param name name of player moving Robber
     * @return vector of vertex->getPlayerInfo(name)
     */
    std::vector<std::tuple<std::string, std::vector<int>>> otherPlayerResources(std::string name);

    /**
     *
     * @return coordinates
     */
    coords getCoordinates();

    /**
     *
     * @param pCoordinates coordinates to check
     * @return true if coordinates are within buffer, false otherwise
     */
    bool getTile(coords pCoordinates);

    /**
     * sets all Vertex coordinates
     */
    void setVerticeCoords();

    /**
     * sets all Edge coordinates and tilts
     */
    void setEdgeCoords();

    /**
     * iterates through Edges, calling edge->getEdge(coordinates)
     * @param pCoordinates coordinates to check
     * @return if edge->getEdge(coordinates) == true: edge, nullptr otherwise
     */
    Edge* getEdge(coords coordinates);

    /**
     * iterates through Vertices, calling vertex->getVertex(coordinates)
     * @param pCoordinates coordinates to check
     * @return if vertex->getVertex(coordinates) == true: vertex, nullptr otherwise
     */
    Vertex* getVertice(coords pCoordinates) const;
    /**
     * iterates through each Vertex, checking if getName() == name
     * @param name name of player to steal from
     * @return if getName() == name: Vertex->stealResources(), otherwise null Resource
     */
    Resource stealResource(std::string name);

};



#endif //TILE_H
