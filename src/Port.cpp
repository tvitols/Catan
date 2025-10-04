//
// Created by tvito on 9/16/2025.
//

#include "Port.h"

Port::Port(const Trade pTrade){
    trade = pTrade;
}


bool Port::setBuilding(Building *pBuilding) {
    bool toReturn = Vertex::setBuilding(pBuilding);
    building->setTrade(trade);
    return toReturn;

}

Trade Port::getTrade() const {
    return trade;
}
