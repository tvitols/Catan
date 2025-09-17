//
// Created by tvito on 9/16/2025.
//

#ifndef ROBBER_H
#define ROBBER_H
#include "Tile.h"


class Robber {

    Tile*currentTile;

    public:

    Robber();
    ~Robber();

    void move(Tile* currentTile);

};



#endif //ROBBER_H
