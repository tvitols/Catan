//
// Created by tvito on 9/16/2025.
//

#include "CardStack.h"
#include "CustomUtils.h"

#include <iostream>

std::string CardStack::draw(Deck *&deck) {
    //Prints what type of DevCard you drew
    std::string result = "You drew a ";
    //Adds that card to the Deck
    cards.push_back(deck->Deal());
    result += cards.back()->getName();
    return result;
}

void CardStack::show() const {
    //Shows list of DevCards in hand
    int i = 1;
    for (const auto card : cards) {
        std::cout << i++ << ". ";
        card->print();
        std::cout << std::endl;
    }
    std::cout << i << ". Go Back" << std::endl;
}

int CardStack::play(std::vector<int>* resources, int* vp) {
    //Prompts user for DevCard to play
    std::cout << "Select an option from the list below" << std::endl;
    show();
    int choice = 0;
    while (choice < 1) {
        //input validation
        choice = getIntFromUser();
        if (choice < 1) {
            std::cout << "Invalid choice" << std::endl;
        }else {
            if (choice == cards.size()+1) {
                return -1;
            }
            //Checks if the card is active
            if (!cards[choice-1]->isActive()) {
                std::cout << "Card can not be played on the same turn you bought it" << std::endl;
                choice = 0;
                std::cout << "Select an option from the list below" << std::endl;
                show();
            }
        }
    }

    int ret;
    //Plays the Card chosen
    //Removes the Card played
    switch (cards[choice-1]->getType()) {
        case 3:
            ret = cards[choice-1]->play(resources);
            cards.erase(cards.begin()+choice-1);
            return ret;
        case 5:
            ret = cards[choice-1]->play(vp);
            cards.erase(cards.begin()+choice-1);
            return ret;
        default:
            ret = cards[choice-1]->play(nullptr);
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
