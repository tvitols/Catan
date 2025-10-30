//
// Created by lilas on 10/4/2025.
//

#include "KnightCard.h"

KnightCard::KnightCard() : Card("Knight", "Moves the Robber"){}

int KnightCard::play(void* object) {
    return 1;
}

int KnightCard::getType() const {
    return type;
}