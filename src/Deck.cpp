//
// Created by tvito on 9/16/2025.
//

#include "Deck.h"

#include "CustomUtils.h"


Deck::Deck() {
    for (int i = 0; i < 14; i++) {
        cards.push_back(new Knight());
        if (i <2) {
            cards.push_back(new Monoply());
            cards.push_back(new RoadBuilding());
            cards.push_back(new YearOfPlenty());
        }
        if (i < 5) {
            cards.push_back(new VictoryPointCard(i));
        }
    }
    shuffle();
}

Deck::Deck(int seed) {
    for (int i = 0; i < 14; i++) {
        cards.push_back(new Knight());
        if (i <2) {
            cards.push_back(new Monoply());
            cards.push_back(new RoadBuilding());
            cards.push_back(new YearOfPlenty());
        }
        if (i < 5) {
            cards.push_back(new VictoryPointCard(i));
        }
    }
    shuffle(seed);
}

void Deck::shuffle() {
    std::shuffle(cards.begin(),cards.end(),generator_);
}

void Deck::shuffle(const int seed) {
    std::shuffle(cards.begin(),cards.end(),std::mt19937(seed));
}

Card * Deck::Deal() {
    Card *ret = cards[cards.size() - 1];
    cards.pop_back();
    return ret;
}
