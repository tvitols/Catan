//
// Created by tvito on 9/16/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "Tile.h"


class Board {
    std::vector<std::vector<Tile*>> tiles;

    Board();
    explicit Board(int seed);
    void generateTiles(std::mt19937 twist);


public:

    ~Board();

    static Board generateBoard();
    static Board generateBoard(int seed);

    void printBoard() const;

    void collectResources(int roll) const;

};


#endif //BOARD_H
