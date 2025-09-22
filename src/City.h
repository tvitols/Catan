//
// Created by tvito on 9/16/2025.
//

#ifndef CITY_H
#define CITY_H

#include "Building.h"

//Necessary Resources: stone = 3, wheat = 2
class City : Building{


public:
    City();
    ~City();

    //Depends on where we want to have the vertex
    //If they have the vertex, then make sure that the vertex used to be a house
    bool checksIfHouse(Vertex vertex);
    void buy();

};



#endif //CITY_H
