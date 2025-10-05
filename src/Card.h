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

    virtual int play(void* object) = 0;
    virtual void print() const = 0;


    bool isActive() const;
    void makeActive();

    std::string getName();

};



#endif //CARD_H
