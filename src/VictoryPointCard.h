//
// Created by lilas on 10/4/2025.
//

#ifndef CATAN_VICTORTYPOINT_H
#define CATAN_VICTORTYPOINT_H

#include "Card.h"
#include "vector"


class VictoryPoint : public Card{

    const std::vector<std::string> names = {"Library", "Market", "Chapel", "Great Hall", "University"};
    const int type = 5;

    public:
    VictoryPoint(int i);

    int play(void* &object) override;

    int getType() const override;

    void print() const override;

};


#endif //CATAN_VICTORTYPOINT_H