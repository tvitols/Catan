//
// Created by tvito on 9/16/2025.
//

#ifndef PLAYER_H
#define PLAYER_H


#include <string>
#include <vector>

#include "CardStack.h"
#include "customUtils.h"

class Player {

    std::string name;
    int vp = 0;
                            //    w,s,b,s,wh
    std::vector<int> resources = {0,0,0,0,0};
    std::vector<Resource> collected = {};
    CardStack devCards;

    public:

    explicit Player(const std::string *pname);

    //add resource to player
    void addResource(Resource r);

    //take resourcce from player
    bool removeResource(Resource r);

    //does the same as removeResource but with a vector of Resources
    bool removeResource(const std::vector<Resource> &r);

    //show players resources
    void showResources();


    //take their turn
    void takeTurn(const std::vector<Player*>& players);

    void showCollectedResources();

    //display options to buy things
    void buyMenu();

    void buyDevCard();

    // adds vp, return true if player has over 10 vp
    bool addVP(int pVP);

    //remove vp from a player
    void removeVP(int pVP);

    std::string getName() const;

    bool hasWon();

    friend bool operator==(const Player &lhs, const Player &rhs);
    friend bool operator!=(const Player &lhs, const Player &rhs);

    bool trade(std::vector<Resource>get, std::vector<Resource>give);

    bool initiateTrade(std::vector<Player*> players);
};



#endif //PLAYER_H
