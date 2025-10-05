//
// Created by tvito on 9/16/2025.
//

#include "CardStack.h"
#include "CustomUtils.h"

#include <iostream>

std::string CardStack::draw(Deck *&deck) {
    std::string result = "You drew a ";
    cards.push_back(deck->Deal());
    result += cards.back()->getName();
    return result;
}

void CardStack::show() const {
    int i = 1;
    for (const auto card : cards) {
        std::cout << i++ << ". ";
        card->print();
        std::cout << std::endl;
    }
    std::cout << i << ". Go Back" << std::endl;
}

int CardStack::play(std::vector<int>* resources, int* vp) {
    std::cout << "Select an option from the list below" << std::endl;
    show();
    int choice = 0;
    while (choice < 1) {
        choice = getIntFromUser();
        if (choice < 1) {
            std::cout << "Invalid choice" << std::endl;
        }else {
            if (choice == cards.size()+1) {
                return -1;
            }
            if (!cards[choice]->isActive()) {
                std::cout << "Card can not be played on the same turn you bought it" << std::endl;
                choice = 0;
            }
        }
    }
    int ret;
    switch (cards[choice]->getType()) {
        case 3:
            ret = cards[choice]->play(resources);
            cards.erase(cards.begin()+choice-1);
            return ret;
        case 5:
            ret = cards[choice]->play(vp);
            cards.erase(cards.begin()+choice-1);
            return ret;
        default:
            ret = cards[choice]->play(nullptr);
            cards.erase(cards.begin()+choice-1);
            return ret;
    }

}

void CardStack::makeActive() const {
    if (!isEmpty()) {
        for (const auto card : cards) {
            card->makeActive();
        }
    }
}

bool CardStack::isEmpty() const {
    return cards.empty();
}
