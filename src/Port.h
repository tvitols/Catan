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
    //Port() = default;

    explicit Port(const Trade pTrade, const coords pLocation);

    bool setBuilding(Building *pBuilding) override;
    Trade getTrade() const;

    std::string getShipToken() const;
    double getShipX() const;
    double getShipY() const;

    bool isPort() const override;
};



#endif //PORT_H
