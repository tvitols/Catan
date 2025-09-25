//
// Created by tvito on 9/16/2025.
//

#ifndef BUILDING_H
#define BUILDING_H


#include "Structure.h"
#include "customUtils.h"


class Building : public Structure {

protected:

    int num;
    Player* owner;


public:
    Building() = default;
    explicit Building(Player* owner) : Structure(), num(0), owner(owner) {};
    ~Building() = default;


    //obtains a vector of resources from the vertice
    //multiplies each resource by the modifier
    //returns type and number or resources
    void giveResources(resourceType rType);

    //bool place(Vertex vertex);
    bool buy();

    bool upgradeToCity();

};



#endif //BUILDING_H
