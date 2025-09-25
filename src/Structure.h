//
// Created by tvito on 9/16/2025.
//

#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "player.h"


class Structure {

protected:
    //Create Player pointer to the player that owns the structure
    Player* owner;
    enum necessaryResources : int {wood = 0, stone = 0, brick = 0, sheep = 0, wheat = 0};
    int victoryPoint;

public:
    Structure() = default;
    ~Structure() = default;

    bool place();
    bool buy();

    //Adds the number of victory points each structure is worth to the Player
    bool addsVictoryPoint();

    Player* getOwner();

};



#endif //STRUCTURE_H
