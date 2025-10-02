//
// Created by tvito on 9/16/2025.
//

#ifndef EDGE_H
#define EDGE_H

#include "Road.h"

class Edge {
    bool shown = false;
    bool occupied = false;
    Road* road = nullptr;
    coords coordinates = {0,0};

public:

    bool isShown();

    void show();
    void reset();

    coords getCoordinates();

    bool isOccupied() const;

    std::string getOccupiedImg();

};



#endif //EDGE_H
