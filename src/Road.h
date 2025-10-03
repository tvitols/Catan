//
// Created by tvito on 9/16/2025.
//

#ifndef ROAD_H
#define ROAD_H

#include "Structure.h"

//Necessary Resources = wood = 1, brick = 1
class Road : public Structure {

    // 0 = upright, 1 = tilt left, 2 = tilt right
    tilt orientation = {};

public:
    Road() = default;
    explicit Road(Player* player);
    ~Road() = default;

    void place(tilt orient);

    std::string getImg() const;
};



#endif //ROAD_H
