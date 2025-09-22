//
// Created by tvito on 9/16/2025.
//

#include "Building.h"

std::tuple<resourceType, int> Building::giveResources(int roll) {
    return std::make_tuple(resourceType::wood, 1);
}
