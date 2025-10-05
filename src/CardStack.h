//
// Created by tvito on 9/16/2025.
//

#ifndef CARDSTACK_H
#define CARDSTACK_H

#include "Card.h"
#include "Deck.h"

class CardStack {
    //vector of Cards
    std::vector<Card *> cards = {};

public:

    /**
     * default constructor
     */
    CardStack() = default;
    /**
     * default destructor
     */
    ~CardStack() = default;

    /**
     * adds Card from Deck to CardStack
     * @param deck Deck to obtain Card from
     * @return string of Card that was drawn
     */
    std::string draw(Deck* &deck);
    /**
     * prints out list of all Cards in vector
     */
    void show() const;
    /**
     * calls the play method of a Card in the stack
     * @param resources player resources
     * @param vp player victory points
     * @return integer of Card->play(object)
     */
    int play(std::vector<int>* resources, int* vp);

    /**
     * sets all Cards to active
     */
    void makeActive() const;

    /**
     *
     * @return return cards.empty()
     */
    bool isEmpty() const;

};



#endif //CARDSTACK_H
