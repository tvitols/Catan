//
// Created by lilas on 10/4/2025.
//

#include "MonopolyCard.h"

MonopolyCard::MonopolyCard() : Card("Monopoly", "Claims all other players' resources of a specifically declared type"){}

int MonopolyCard::play(void* object) {
    return 3;
}

int MonopolyCard::getType() const {
    return type;
}