#include <iostream>
#include "../src/Deck.h"
//
// Created by tvito on 9/16/2025.
//
bool testDeck();

int main() {
    if (testDeck()) {
        std::cout << "PASSED ALL DECK CASES" << std::endl;
    }

    return 0;
}

bool testDeck() {
    Deck deck = Deck();
    for (int i = 0; i < 26; i ++) {
        deck.Deal();
    }
}