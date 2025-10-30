//
// Created by lilas on 10/4/2025.
//

#ifndef CATAN_YEAROFPLENTY_H
#define CATAN_YEAROFPLENTY_H

#include "Card.h"


class YearOfPlenty : public Card {
    const int type = 3;

public:

    /**
     * calls Card() with a specific name and description
     */
    YearOfPlenty();

    /**
     * gives the player 2 resources
     * @param object player's resources
     * @return 0
     */
    int play(void* object) override;

    /**
     *
     * @return type
     */
    int getType() const override;

};


#endif //CATAN_YEAROFPLENTY_H