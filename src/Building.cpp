//
// Created by tvito on 9/16/2025.
//

#include "Building.h"

void Building::giveResources(resourceType rType) {
    owner->addResource(Resource(rType,num));
}
