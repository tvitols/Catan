//
// Created by tvito on 9/16/2025.
//

#ifndef CARDSTACK_H
#define CARDSTACK_H

#include "Card.h"
#include "Deck.h"

class CardStack {

    std::vector<Card *> cards = {};

public:
    CardStack() = default;
    ~CardStack() = default;

    std::string draw(Deck* &deck);
    void show() const;
    int play(std::vector<int>* resources, int* vp);

    bool isEmpty() const;

};



#endif //CARDSTACK_H
