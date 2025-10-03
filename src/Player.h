//
// Created by tvito on 9/16/2025.
//

#ifndef PLAYER_H
#define PLAYER_H


#include <set>
#include <string>
#include <vector>

#include "CardStack.h"
#include "customUtils.h"

enum playerColor : int {red = 0, white = 1, blue = 2, green = 3};

class Player {

    std::string name;
    int vp = 0;
                            //    w,s,b,s,wh
    std::vector<int> resources = {0,0,0,0,0};
    std::vector<Resource> collected = {};
    CardStack devCards;
    playerColor color;
    std::set<Trade> allowedTrades = {Trade(Resource(null,4),Resource(null, 1))};

    public:

        Player(const std::string *pname, playerColor pColor);

    //add resource to player
    void addResource(Resource r);

    //take resourcce from player
    bool removeResource(Resource r);

    //does the same as removeResource but with a vector of Resources
    bool removeResource(const std::vector<Resource> &r);

    //show players resources
    void showResources();


    //take their turn
    int takeTurn(const std::vector<Player*>& players, int action);

    void showCollectedResources();

    //display options to buy things
    int buyMenu();

    int buyDevCard();

    // adds vp, return true if player has over 10 vp
    bool addVP(int pVP);

    //remove vp from a player
    void removeVP(int pVP);

    std::string getName() const;

    bool hasWon();

    friend bool operator==(const Player &lhs, const Player &rhs);
    friend bool operator!=(const Player &lhs, const Player &rhs);

    void addTrade(const Trade &t);

    bool trade(std::vector<Resource>get, std::vector<Resource>give);

    bool initiateTrade(std::vector<Player*> players);

    bool rolledASeven();

    void loseHalfOfCards();

    std::string moveRobber(std::vector<std::tuple<std::string, std::vector<int>>> stuffToSteal);

    std::vector<int> getResources();

    std::string getName();

    std::string getColor() const;
};



#endif //PLAYER_H
