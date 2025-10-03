//
// Created by tvito on 9/16/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "Tile.h"
#include "Robber.h"


class Board {
    std::vector<std::vector<Tile*>> tiles;

    Board();
    explicit Board(Robber* pRobber);
    explicit Board(int seed);
    void generateTiles(std::mt19937 twist);
    Robber* robber = nullptr;



public:

    ~Board();

    static Board generateBoard();
    static Board generateBoard(Robber* robber);
    static Board generateBoard(int seed);

    coords printBoard(const std::string &message);

    void collectResources(int roll) const;


    std::vector<std::tuple<std::string, std::vector<int>>> otherPlayerResources(std::string name);

    Edge* getEdge(coords coordinates);
    Vertex* getVertex(coords coordinates);
    Structure* getStructure(double x, double y);
    Tile* getTile(coords coordinates);

    std::vector<std::vector<Tile*>> getTiles();

    void moveRobber(Tile* tile);

};


#endif //BOARD_H
