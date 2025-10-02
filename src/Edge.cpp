//
// Created by tvito on 9/16/2025.
//

#include "Edge.h"

coords Edge::getCoordinates() {
    return coordinates;
}

bool Edge::isOccupied() const {
    return occupied;
}

std::string Edge::getOccupiedImg() {
    return road->getImg();
}
