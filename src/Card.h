//
// Created by tvito on 9/16/2025.
//

#ifndef CARD_H
#define CARD_H
#include <string>


class Card {

protected:
    Card(std::string pName, std::string pDescription);
    ~Card() = default;
    std::string name;
    std::string description;
    bool active = false;

public:

    void play(void (*func)());
    virtual void print() const = 0;
    virtual int getType() const = 0;

    bool isActive() const;
    void makeActive();

};



#endif //CARD_H
