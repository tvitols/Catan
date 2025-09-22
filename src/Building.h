//
// Created by tvito on 9/16/2025.
//

#ifndef BUILDING_H
#define BUILDING_H

#include <vector>

#include "Structure.h"
#include "Vertex.h"
#include "customUtils.h"
#include <tuple>

using namespace std;

class Building : Structure {
    //1 for a settlement or 2 for a city
    //Multiply the resources you recieve by this modifier (if that makes sense)
    int modifier;

    public:
    Building() = default;
    ~Building() = default;

    //obtains a vector of resources from the vertice
    //multiplies each resource by the modifier
    //returns type and number or resources
    std::tuple<resourceType,int> giveResources(int roll);

    bool place(Vertex vertex);
    bool buy();

};



#endif //BUILDING_H
