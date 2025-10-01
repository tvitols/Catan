//
// Created by tvito on 9/16/2025.
//

#ifndef VERTEX_H
#define VERTEX_H
#include "Building.h"


class Vertex {

    int x;
    int y;
    Building* building = nullptr;

    public:
    Vertex() :x(0), y(0){};
    ~Vertex() = default;
    Vertex(int x, int y) : x(x), y(y){};

    void collectResources(resourceType rtype) const;

    std::tuple<std::string, std::vector<int>> getPlayerInfo(std::string name);

    // resourceType stealResources();
};



#endif //VERTEX_H
