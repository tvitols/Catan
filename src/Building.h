//
// Created by tvito on 9/16/2025.
//

#ifndef BUILDING_H
#define BUILDING_H


#include "Structure.h"
#include "CustomUtils.h"


class Building : public Structure {

protected:
    //number of resources to give to owner
    int num;


public:

    /**
     * default constructor
     */
    Building() = default;
    /**
     * sets owner equal to pOwner
     * @param pOwner owner of Building
     */
    explicit Building(Player* pOwner);
    /**
     * default destructor
     */
    ~Building() = default;


    /**
     * if the owner exists, calls owner->addResource(rType)
     * @param rType specific Resource
     */
    void giveResources(resourceType rType);

    /**
     *
     * @return owner name
     */
    std::string getPlayerName();

    /**
     *
     * @return owner resources
     */
    std::vector<int> getPlayerResources();

    /**
     *
     * @return num == 2
     */
    bool isCity();

    /**
     * adds a VP to owner
     * changes num to 2
     */
    void upgradeToCity();

    /**
     * returns an image of either a City or Settlement,
     * depending on which type of Building it is
     * @return file string of image of Building
     */
    std::string getImg() const;

    /**
     * calls owner->addTrade(pTrade)
     * @param pTrade specific Trade to add
     */
    void setTrade(Trade pTrade);

    /**
     * chooses a random resource from owner (that is not 0), and removes that resource from the owner
     * @return Resource chosen
     */
    Resource stealResources();

};



#endif //BUILDING_H
