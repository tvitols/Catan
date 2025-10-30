//
// Created by tvito on 9/16/2025.
//

#ifndef VERTEX_H
#define VERTEX_H
#include "Building.h"


class Vertex {

protected:
    Building* building = nullptr;
    const int BUFFER = 7;
    coords coordinates = {0,0};
    bool occupied = false;

    public:
    /**
     * default constructor
     */
    Vertex() {};
    /**
     * default destructor
     */
    ~Vertex() = default;

    /**
     * calls building->giveResource(rtype) if building exists
     * @param rtype type resource to collect
     */
    void collectResources(resourceType rtype) const;

    /**
     * checks if the building exists
     * checks if building->getName() is equal to name, setting name to "" if true
     * @param name name of player moving Robber
     * @return name and resources of player associated with Vertex
     */
    std::tuple<std::string, std::vector<int>> getPlayerInfo(std::string name);

    /**
     * sets coordinates.x to x and coordinates.y to y
     * @param x x coordinate
     * @param y y coordinate
     */
    void setCoordinates(int x, int y);

    /**
     *
     * @return coordinates
     */
    coords getCoordinates();

    /**
     * checks if the coords corresponds to coordinates
     * @param fCoordinates coords to check
     * @return true if it corresponds to the Vertex, false otherwise
     */
    bool getVertex(coords fCoordinates);

    /**
     *
     * @return occupied
     */
    bool isOccupied() const;

    /**
     * checks if Vertex is occupied
     * sets Building if it isn't
     * Adds a victory point to the Building's owner
     * @param pBuilding Building to add
     * @return true if can be placed, false otherwise
     */
    virtual bool setBuilding(Building* pBuilding);

    /**
     * upgrades a settlement to a city
     * @param player player attempting to upgrade
     * @return true if player is owner and building is not already a city, false otherwise
     */
    bool upgradeBuilding(Player* player);

    /**
     *
     * @return building
     */
    Building* getBuilding() const;

    /**
     *
     * @return building->getImg()
     */
    std::string getOccupiedImg();

    /**
     *
     * @return false
     */
    virtual bool isPort() const;

    /**
     *
     * @return building->stealResources()
     */
    Resource stealResources();

    /**
     *
     * @return building->getName() if building exists
     */
    std::string getName();
};



#endif //VERTEX_H
