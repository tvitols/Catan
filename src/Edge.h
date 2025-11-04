//
// Created by tvito on 9/16/2025.
//

#ifndef EDGE_H
#define EDGE_H
#include "CustomUtils.h"


#include "Road.h"

class Edge {
    coords coordinates = {0, 0};
    //buffer of X and Y coords for getEdge
    int YBUFFER = 19;
    int XBUFFER = 25;
    Road* road = nullptr;
    //tilt of the edge
    tilt type = {};
    bool occupied = false;


public:

    /**
     * places a road on the Edge
     * sets occupied to true
     * @param pRoad road to place
     * @return false if occupied, true otherwise
     */
    bool setRoad(Road* pRoad);
    /**
     *
     * @return road
     */
    Road* getRoad();

    /**
     *
     * @return coordinates
     */
    coords getCoordinates();

    /**
     *
     * @return occupied
     */
    bool isOccupied() const;

    /**
     *
     * @return road->getImage()
     */
    std::string getOccupiedImg();

    /**
     * sets coordinates and tilt
     * @param x x coordinate
     * @param y y coordinate
     * @param fTilt type of tilt
     */
    void setCoordinates(int x, int y, tilt fTilt);

    /**
     * checks if the coords corresponds to coordinates
     * @param fCoordinates coords to check
     * @return true if it corresponds to the Edge, false otherwise
     */
    bool getEdge(coords fCoordinates);

};



#endif //EDGE_H
