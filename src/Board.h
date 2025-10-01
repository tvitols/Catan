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

    void printBoard() const;

    void collectResources(int roll) const;

    void addRobber(Robber* robber);

    std::vector<std::tuple<std::string, std::vector<int>>> otherPlayerResources(std::string name);


};


#endif //BOARD_H
