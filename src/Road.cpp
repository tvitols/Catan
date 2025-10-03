//
// Created by tvito on 9/16/2025.
//

#include "Road.h"

Road::Road(Player *player) {
    owner = player;
}



void Road::place(const tilt orient) {
    orientation = orient;
}

std::string Road::getImg() const {
        std::string file = "static/road_";
        file += owner->getColor();
        switch (orientation) {
            case upright: file += "_u"; break;
            case left: file += "_l"; break;
            case right: file += "_r"; break;
            default: return "";
        }
        file += ".png";
        return file;
}
