//
// Created by tvito on 9/16/2025.
//

#ifndef ROAD_H
#define ROAD_H

#include "Structure.h"

class Road : public Structure {

    // 0 = upright, 1 = tilt left, 2 = tilt right
    tilt orientation = {};

public:
    /**
     * default constructor
     */
    Road() = default;
    /**
     * sets owner to player
     * @param player player that owns the Road
     */
    explicit Road(Player* player);
    /**
     * default destructor
     */
    ~Road() = default;

    /**
     * sets orientation to orient
     * @param orient tilt
     */
    void place(tilt orient);

    /**
     *
     * @return image of road depending on tilt
     */
    std::string getImg() const;
};



#endif //ROAD_H
