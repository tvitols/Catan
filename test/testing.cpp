#include <iostream>

#include "../src/CardStack.h"
#include "../src/CustomUtils.h"
#include "../src/Deck.h"
#include "../src/Player.h"
//
// Created by tvito on 9/16/2025.
//
bool testDeck();
bool testPlayer();
bool testCardStack();
bool testTrade();

int main() {
    if (testDeck()) {
        std::cout << "PASSED ALL DECK CASES" << std::endl;
    }
    if (testPlayer()) {
        std::cout << "PASSED ALL PLAYER CASES" << std::endl;
    }
    if (testCardStack()) {
        std::cout << "PASSED ALL CARDSTACK CASES" << std::endl;
    }
    if (testTrade()) {
        std::cout << "PASSED ALL TRADE CASES" << std::endl;
    }

    return 0;
}

bool testDeck() {
    bool passed = true;
    Deck deck = Deck();
    deck.shuffle();
    for (int i = 0; i < 25; i ++) {
        Card * card = deck.Deal();
        if (card == nullptr) {
            std::cout << "Failed Deck Deal test" << std::endl;
            passed = false;
            break;
        }
        if (card->isActive()) {
            std::cout << "Failed card active test" << std::endl;
            passed = false;
            break;
        }
        card->makeActive();
        switch (card->getType()) {
            case 0:

            case 1:
                if (card->play(nullptr) != 1) {
                    std::cout << "Failed Knight play test" << std::endl;
                    passed = false;
                }
                break;
            case 2:
                if (card->play(nullptr) != 2) {
                    std::cout << "Failed road building play test" << std::endl;
                    passed = false;
                }
                break;

            case 4:
                if (card->play(nullptr) != 3) {
                    std::cout << "Failed monopoly play test" << std::endl;
                    passed = false;
                }
                break;
            case 3: case 5:
                // Testing too complex for 11 pm
                break;
            default: break;
        }
    }
    if (deck.Deal() != nullptr) {
        passed = false;
    }
    return passed;
}

bool testCardStack() {
    bool passed = true;
    CardStack stack = CardStack();
    Deck* deck = new Deck();
    deck->shuffle();
    if (!stack.isEmpty()) {
        std::cout << "Failed initial empty stack test" << std::endl;
        passed = false;
    }
    stack.draw(deck);
    if (stack.isEmpty()) {
        std::cout << "Failed stack draw test" << std::endl;
        passed = false;
    }
    return passed;
}

bool testPlayer() {
    bool passed = true;
    const std::string name1 = "Test Player 1";
    const std::string name2 = "Test Player 2";
    Player* player = new Player(new std::string("Test Player 1"), red);
    Player* player2 = new Player(new std::string("Test Player 2"), blue);
    Player* player3 = new Player(new std::string("Test Player 1"), green);

    if (player->getName() != name1 || player2->getName() != name2 || player3->getName() != name1) {
        std::cout << "Failed name initialization test" << std::endl;
        passed = false;
    }

    if (player->getVP() != 0) {
        std::cout << "Failed VP initialization test" << std::endl;
        passed = false;
    }
    if (player->addVP(2)) {
        std::cout << "Failed add VP test" << std::endl;
        passed = false;
    }
    if (player->getVP() != 2) {
        std::cout << "Failed get VP test" << std::endl;
        passed = false;
    }
    player->removeVP(1);
    if (player->getVP() != 1) {
        std::cout << "Failed remove VP test" << std::endl;
        passed = false;
    }
    if (!player->addVP(9)) {
        std::cout << "Failed win on add VP test" << std::endl;
        passed = false;
    }
    if (!player->hasWon()) {
        std::cout << "Failed win test" << std::endl;
        passed = false;
    }
    if (player == player2 || player == player3 || player2 == player3) {
        std::cout << "Failed player pointer equality test" << std::endl;
        passed = false;
    }
    if (*player == *player2 || *player3 == *player2) {
        std::cout << "Failed player object equality test" << std::endl;
        passed = false;
    }
    if (*player != *player3) {
        std::cout << "Failed player object test" << std::endl;
        passed = false;
    }
    if (player->getArmy()) {
        std::cout << "Failed player army initialization test" << std::endl;
        passed = false;
    }

    return passed;
}

bool testTrade() {
    bool passed = true;

    Trade trade1 = {{wood,1},{stone,1}};
    Trade trade2 = {{sheep,1},{stone,1}};
    Trade trade3 = {{wood,1},{brick,1}};
    Trade trade4 = {{wood,2},{stone,1}};

    if (trade1 == trade2) {
        std::cout << "Failed trade equality test - dif types" << std::endl;
        passed = false;
    }

    if (trade1 != trade3) {
        std::cout << "Failed trade equality test - dif gets" << std::endl;
        passed = false;
    }

    if (trade1 == trade4) {
        std::cout << "Failed trade equality test - dif nums" << std::endl;
        passed = false;
    }

    return passed;
}