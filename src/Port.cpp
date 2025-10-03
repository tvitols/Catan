//
// Created by tvito on 9/16/2025.
//

#include "Port.h"

void Port::setBuilding(Building *pBuilding) {
    Vertex::setBuilding(pBuilding);
    building->getOwner()->addTrade(trade);

}
