//
// Created by tvito on 9/16/2025.
//

#ifndef CARD_H
#define CARD_H
#include <string>


class Card {

    std::string name;
    std::string description;
    bool active = false;


public:
    Card(std::string pName, std::string pDescription);
    ~Card() = default;

    virtual void play() = 0;
    void print() const;

    bool isActive() const;
    void makeActive();

};



#endif //CARD_H
