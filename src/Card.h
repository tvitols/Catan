//
// Created by tvito on 9/16/2025.
//

#ifndef CARD_H
#define CARD_H
#include <string>


class Card {

protected:
    /**
     * constructor
     * @param pName name of Card
     * @param pDescription description of Card
     */
    Card(std::string pName, std::string pDescription);
    /**
     * default destructor
     */
    ~Card() = default;
    //name of Card
    std::string name;
    //description of Card
    std::string description;
    //whether card can be played
    bool active = false;

public:

    /**
     * virtual class to be overridden
     * @param object object to be modified
     * @return integer of Card to be switched on
     */
    virtual int play(void* object) = 0;
    /**
     * prints name and description of Card
     */
    void print() const;
    /**
     * virtual class to be overridden
     * @return type
     */
    virtual int getType() const = 0;

    /**
     *
     * @return active
     */
    bool isActive() const;
    /**
     * sets active to true
     */
    void makeActive();

    /**
     *
     * @return name
     */
    std::string getName();

};



#endif //CARD_H
