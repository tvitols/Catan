//
// Created by tvito on 9/16/2025.
//

#include "Port.h"

Port::Port(resourceType rType) {
    if (type == null) {
        modifier = 3;
    }
    else {
        modifier = 2;
    }
    type = rType;
}

void Port::setBuilding(Building *pBuilding) {
    Vertex::setBuilding(pBuilding);
    building->getOwner()->addTrade(trade);

}
