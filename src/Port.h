//
// Created by tvito on 9/16/2025.
//

#ifndef PORT_H
#define PORT_H

#include "Vertex.h"


class Port : public Vertex {

    Trade trade;

    public:
    //Port() = default;

    explicit Port(const Trade pTrade);
    ~Port() = default;

    bool setBuilding(Building *pBuilding) override;
    Trade getTrade() const;
};



#endif //PORT_H
