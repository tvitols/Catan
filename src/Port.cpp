//
// Created by tvito on 9/16/2025.
//

#include "Port.h"

Port::Port(const Trade pTrade, const coords pLocation){
    trade = pTrade;
    shipLocation = pLocation;
}


bool Port::setBuilding(Building *pBuilding) {\
    //Calling parent function
    bool toReturn = Vertex::setBuilding(pBuilding);
    //Adding trade to owner of Building
    building->setTrade(trade);
    return toReturn;

}

Trade Port::getTrade() const {
    return trade;
}

std::string Port::getShipToken() const {
    //Obtaining image based on Trade type
    std::string file = "static/";
    switch (trade.give.type) {
        case wood: file += "wood"; break;
        case sheep: file += "sheep"; break;
        case brick: file += "brick"; break;
        case stone: file += "stone"; break;
        case wheat: file += "wheat"; break;
        case null : file += "null"; break;
        default: ;
    }
    file += "_ship.png";
    return file;
}

double Port::getShipX() const {
    return shipLocation.x;
}

double Port::getShipY() const {
    return shipLocation.y;
}

bool Port::isPort() const {
    return true;
}
