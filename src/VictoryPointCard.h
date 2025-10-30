//
// Created by lilas on 10/4/2025.
//

#ifndef CATAN_VICTORTYPOINT_H
#define CATAN_VICTORTYPOINT_H

#include "Card.h"
#include "vector"


static const std::vector<std::string> names = {"Library", "Market", "Chapel", "Great Hall", "University"};

class VictoryPoint : public Card{

    const int type = 5;

    public:
    /**
     * calls Card() with specific name and description
     * @param i index of name
     */
    VictoryPoint(int i);

    /**
     * increments player's victoryPoints by 1
     * @param object victoryPoints of player
     * @return 0
     */
    int play(void* object) override;

    /**
     *
     * @return type
     */
    int getType() const override;

};


#endif //CATAN_VICTORTYPOINT_H