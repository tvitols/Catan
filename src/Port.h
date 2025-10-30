//
// Created by tvito on 9/16/2025.
//

#ifndef PORT_H
#define PORT_H

#include "Vertex.h"


class Port : public Vertex {

    coords shipLocation;
    Trade trade;

    public:

    /**
     * initializes variables
     * @param pTrade trade of Port
     * @param pLocation coodinates of Port
     */
    explicit Port(const Trade pTrade, const coords pLocation);

    /**
     * calls Vertex::setBuilding(pBuilding)
     * adds Trade to Building
     * @param pBuilding Building to place on Vertex
     * @return Vertex::setBuilding(pBuilding)
     */
    bool setBuilding(Building *pBuilding) override;
    /**
     *
     * @return trade
     */
    Trade getTrade() const;

    /**
     *
     * @return string of png of Port depending on Trade type
     */
    std::string getShipToken() const;
    /**
     *
     * @return shipLocation.x
     */
    double getShipX() const;
    /**
     *
     * @return shipLocation.y
     */
    double getShipY() const;

    /**
     *
     * @return true
     */
    bool isPort() const override;
};



#endif //PORT_H
