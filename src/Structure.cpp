//
// Created by tvito on 9/16/2025.
//

#include "Structure.h"

bool Structure::buy() {
    return true;
}

bool Structure::addsVictoryPoint() {
    return owner->addVP(1);
}

Player* Structure::getOwner() {
    return owner;
}
