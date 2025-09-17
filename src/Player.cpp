//
// Created by tvito on 9/16/2025.
//

#include "Player.h"

Player::Player(const std::string *pname) {
    name = *pname;
}

std::string Player::getName() const {
    return name;
}
