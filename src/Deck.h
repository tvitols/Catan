//
// Created by tvito on 9/16/2025.
//

#ifndef DECK_H
#define DECK_H
#include <vector>

#include "Card.h"


class Deck {
     std::vector<Card*> cards;


public:
     Deck();
     explicit Deck (int seed);
     ~Deck() = default;

     void shuffle();
     void shuffle(int seed);

     Card* Deal();
};



#endif //DECK_H
