//
// Created by tvito on 9/16/2025.
//

#include "Vertex.h"

void Vertex::collectResources(const resourceType rtype) const {
    if (building) {
        building->giveResources(rtype);
    }

}
