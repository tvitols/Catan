//
// Created by lilas on 10/4/2025.
//

#ifndef CATAN_ROADBUILDING_H
#define CATAN_ROADBUILDING_H

#include "Card.h"


class RoadBuilding : public Card {
    const int type = 2;

public:
    RoadBuilding();

    int play(void* object) override;

    int getType() const override;
};


#endif //CATAN_ROADBUILDING_H