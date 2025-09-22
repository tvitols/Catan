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

class Building : public Structure {

protected:

    int tileKey;
    resourceType resource;
    int num;


public:
    Building() = default;
    ~Building() = default;


    //obtains a vector of resources from the vertice
    //multiplies each resource by the modifier
    //returns type and number or resources
    void giveResources(int roll);

    bool place(Vertex vertex);
    bool buy();

};



#endif //BUILDING_H
