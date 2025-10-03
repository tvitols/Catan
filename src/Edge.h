//
// Created by tvito on 9/16/2025.
//

#ifndef EDGE_H
#define EDGE_H
#include "customUtils.h"


#include "Road.h"

class Edge {
    coords coordinates = {0, 0};
    int YBUFFER = 19;
    int XBUFFER = 25;
    Road* road = nullptr;
    tilt type = {};
    bool occupied = false;


public:

    bool setRoad(Road* pRoad);
    Road* getRoad();

    coords getCoordinates();

    bool isOccupied() const;

    std::string getOccupiedImg();

    void setCoordinates(int x, int y, tilt fTilt);

    bool getEdge(coords fCoordinates);

};



#endif //EDGE_H
