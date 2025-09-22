//
// Created by tvito on 9/16/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "Tile.h"


class Board {

    std::vector<Tile*> tiles = std::vector<Tile*>(6);

    Board();

public:
    ~Board();

    static Board generateBoard();
    static Board generateBoard(int seed);

    void printBoard();

};



#endif //BOARD_H
