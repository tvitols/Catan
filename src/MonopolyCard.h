//
// Created by lilas on 10/4/2025.
//

#ifndef CATAN_MONOPOLYCARD_H
#define CATAN_MONOPOLYCARD_H

#include "Card.h"

class MonopolyCard : public Card{
    const int type = 4;

public:
    /**
     * Calls Card() with specific name and description
     */
    MonopolyCard();

    /**
     *
     * @param object object to modify
     * @return 3
     */
    int play(void* object) override;

    /**
     *
     * @return type
     */
    int getType() const override;
};


#endif //CATAN_MONOPOLYCARD_H