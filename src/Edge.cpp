//
// Created by tvito on 9/16/2025.
//

#include "Edge.h"

void Edge::setCoordinates(int x, int y, tilt fTilt) {
    coordinates.x = x;
    coordinates.y = y;
    type = fTilt;
}

bool Edge::getEdge(coords fCoordinates) {
    if (type != upright && fCoordinates.x >= coordinates.x - XBUFFER && fCoordinates.x <= coordinates.x + XBUFFER && fCoordinates.y >= coordinates.y - YBUFFER && fCoordinates.y <= coordinates.y + YBUFFER) {
        return true;
    }
    if (type == upright && (fCoordinates.x >= (coordinates.x - 10)) && (fCoordinates.x <= (coordinates.x + 10)) && (fCoordinates.y >= (coordinates.y - 32)) && (fCoordinates.y <= (coordinates.y + 32))) {
        return true;
    }
    return false;
}

bool Edge::setRoad(Road *pRoad) {
    if (occupied) return false;
    road = pRoad;
    road->place(type);
    occupied = true;
    return true;
}

Road * Edge::getRoad() {
    return road;
}

coords Edge::getCoordinates() {
    return coordinates;
}

bool Edge::isOccupied() const {
    return occupied;
}

std::string Edge::getOccupiedImg() {
    return road->getImg();
}
