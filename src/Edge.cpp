//
// Created by tvito on 9/16/2025.
//

#include "Edge.h"

void Edge::setCoordinates(int x, int y) {
    coordinates.x = x;
    coordinates.y = y;
}

bool Edge::getEdge(coords fCoordinates) {
    if (fCoordinates.x >= coordinates.x - XBUFFER && fCoordinates.x <= coordinates.x + XBUFFER && fCoordinates.y >= coordinates.y - YBUFFER && fCoordinates.y <= coordinates.y + YBUFFER) {
        std::cout << "Edge Coordinates: " << coordinates << std::endl;
        return true;
    }
    if (fCoordinates.x >= coordinates.x - 5 && fCoordinates.x <= coordinates.x + 5 && fCoordinates.y >= coordinates.y - 32 && fCoordinates.y <= coordinates.x + 32) {
        std::cout << "Edge Coordinates: " << coordinates << std::endl;
        return true;
    }
    return false;
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
