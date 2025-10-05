//
// Created by lilas on 10/4/2025.
//

#ifndef CATAN_YEAROFPLENTY_H
#define CATAN_YEAROFPLENTY_H

#include "Card.h"


class YearOfPlenty : public Card {
    const int type = 3;

public:
    YearOfPlenty();

    int play(void* object) override;

    int getType() const override;

};


#endif //CATAN_YEAROFPLENTY_H