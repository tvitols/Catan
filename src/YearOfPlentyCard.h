//
// Created by lilas on 10/4/2025.
//

#ifndef CATAN_YEAROFPLENTY_H
#define CATAN_YEAROFPLENTY_H

#include "Card.h"


class YearOfPlenty : public Card {
    const std::string description = "Adds Two Resources of Players Choice";
    std::string name = "Year of Plenty";
    const int type = 2;

public:
    YearOfPlenty();

    int play(void *object) override;

    int getType() const override;

    void print() const override;
};


#endif //CATAN_YEAROFPLENTY_H