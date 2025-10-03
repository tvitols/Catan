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
    int victoryPoint;

public:
    Structure() = default;

    virtual ~Structure() = default;

    Player* getOwner();

};



#endif //STRUCTURE_H
