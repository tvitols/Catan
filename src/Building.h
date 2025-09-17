//
// Created by tvito on 9/16/2025.
//

#ifndef BUILDING_H
#define BUILDING_H

#include <vector>

#include "Resource.h"
#include "Structure.h"
using namespace std;

class Building : Structure{
    //1 for a settlement or 2 for a city
    //Multiply the resources you recieve by this modifier (if that makes sense)
    int modifier;

    public:
    Building();
    ~Building();

    //obtains a vector of resources from the vertice
    //multiplies each resource by the modifier
    //calls the getResources() function of the player that owns the building
    void giveResources(vector<Resource> resources);

    bool place(Vertex vertex);
    bool buy();

};



#endif //BUILDING_H
