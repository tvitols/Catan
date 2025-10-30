//
// Created by lilas on 10/4/2025.
//

#ifndef CATAN_ROADBUILDING_H
#define CATAN_ROADBUILDING_H

#include "Card.h"


class RoadBuilding : public Card {
    const int type = 2;

public:
    /**
     * calls Card() with specific name and description
     */
    RoadBuilding();

    /**
     * gives number for Player and Game to switch on
     * @param object
     * @return 2
     */
    int play(void* object) override;

    /**
     *
     * @return type
     */
    int getType() const override;
};


#endif //CATAN_ROADBUILDING_H