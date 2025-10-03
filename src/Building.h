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


public:
    Building() = default;
    explicit Building(Player* pOwner);
    ~Building() = default;


    //obtains a vector of resources from the vertice
    //multiplies each resource by the modifier
    //returns type and number or resources
    void giveResources(resourceType rType);

    std::string getPlayerName();

    std::vector<int> getPlayerResources();

    bool isCity();

    void upgradeToCity();

    std::string getImg() const;

};



#endif //BUILDING_H
