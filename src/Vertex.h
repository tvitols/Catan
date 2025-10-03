//
// Created by tvito on 9/16/2025.
//

#ifndef VERTEX_H
#define VERTEX_H
#include "Building.h"


class Vertex {

    //+- 50
    int x;
    //+- 32
    int y;
    Building* building = nullptr;
    const int BUFFER = 7;
    coords coordinates = {0,0};
    bool occupied = false;

    public:
    Vertex() :x(0), y(0){};
    ~Vertex() = default;
    Vertex(int x, int y) : x(x), y(y){};

    void collectResources(resourceType rtype) const;

    std::tuple<std::string, std::vector<int>> getPlayerInfo(std::string name);

    void setCoordinates(int x, int y);

    coords getCoordinates();

    bool getVertex(coords fCoordinates);

    bool isOccupied() const;

    bool setBuilding(Building* pBuilding);

    bool upgradeBuilding(Player* player);

    Building* getBuilding() const;

    std::string getOccupiedImg();

};



#endif //VERTEX_H
