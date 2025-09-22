//
// Created by tvito on 9/16/2025.
//

#include "Building.h"

void Building::giveResources(int roll) {
    if (roll == tileKey) {
        owner->addResource(Resource(resource,num));
    }
}
