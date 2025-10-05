//
// Created by lilas on 10/4/2025.
//

#ifndef CATAN_KNIGHTCARD_H
#define CATAN_KNIGHTCARD_H

#include "Card.h"


class KnightCard : public Card{
    const int type = 1;

public:
    KnightCard();

    int play(void* object) override;

    int getType() const override;
};


#endif //CATAN_KNIGHTCARD_H