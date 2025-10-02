//
// Created by tvito on 9/16/2025.
//

#include "Road.h"

bool Road::buy() {
    return true;
}

std::string Road::getImg() const {
        std::string file = "static/road_";
        file += owner->getName();
        switch (orientation) {
            case 0: file += "_u"; break;
            case 1: file += "_l"; break;
            case 2: file += "_r"; break;
            default: return "";
        }
        file += ".png";
        return file;
}
