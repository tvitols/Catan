//
// Created by tvito on 9/16/2025.
//

#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "Player.h"


class Structure {


protected:
    //Create Player pointer to the player that owns the structure
    Player* owner;
    int victoryPoint;

public:
    /**
     * default constructor
     */
    Structure() = default;

    /**
     * default destructor
     */
    virtual ~Structure() = default;

    /**
     *
     * @return owner
     */
    Player* getOwner();

};



#endif //STRUCTURE_H
