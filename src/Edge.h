//
// Created by tvito on 9/16/2025.
//

#ifndef EDGE_H
#define EDGE_H
#include "customUtils.h"


#include "Road.h"

class Edge {
    bool shown = false;
    coords coordinates = {0, 0};
    int YBUFFER = 19;
    int XBUFFER = 25;
    bool occupied = false;
    Road* road = nullptr;

public:

    bool isShown();

    void show();
    void reset();

    coords getCoordinates();

    bool isOccupied() const;

    std::string getOccupiedImg();

    void setCoordinates(int x, int y);

    bool getEdge(coords fCoordinates);

};



#endif //EDGE_H
