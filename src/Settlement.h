//
// Created by tvito on 9/16/2025.
//

#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include "Building.h"

class Settlement : Building {

public:
    //Sets modifier to 1
    //Sets enumerated variables to the correct amount (wood = 1, wheat = 1, brick = 1, sheep = 1)
    Settlement() = default;
    ~Settlement() = default;

    //obtains a vector of resources from the vertice
    //multiplies each resource by the modifier
    //calls the getResources() function of the player that owns the building
    void giveResources(vector<int> resources);

    //yeah don't worry about this right now it's a mess
    bool place(Vertex vertex);

    //Checks whether the player has enough resources
    //returns true if they do and false otherwise
    bool buy();

};



#endif //SETTLEMENT_H
