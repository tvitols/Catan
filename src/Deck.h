//
// Created by tvito on 9/16/2025.
//

#ifndef DECK_H
#define DECK_H
#include <vector>

#include "Card.h"


class Deck {
     //vector of Cards
     std::vector<Card*> cards;


public:
     /**
      * pushes back 15 KnightCards, 5 VictoryPointCards, and
      * 2 of MonopolyCard, YearOfPlentyCard, and RoadBuildingCard in random order
      */
     Deck();
     /**
      * pushes back 15 KnightCards, 5 VictoryPointCards, and
      * 2 of MonopolyCard, YearOfPlentyCard, and RoadBuildingCard in random order
      * @param seed specific seed to use
      */
     explicit Deck (int seed);
     /**
      * default destructor
      */
     ~Deck() = default;

     /**
      * shuffles the deck
      */
     void shuffle();
     /**
      * shuffles the deck
      * @param seed specific seed to use
      */
     void shuffle(int seed);

     /**
      * removes a Card from the deck
      * @return Card that got removed
      */
     Card* Deal();
};



#endif //DECK_H
