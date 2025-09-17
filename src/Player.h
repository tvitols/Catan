//
// Created by tvito on 9/16/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

#include "Building.h"
#include "CardStack.h"
#include "Road.h"


enum resourceType : int {wood = 0, sheep = 1, brick = 2, stone = 3, wheat = 4};

class Player {

    std::string name;
    int vp = 0;
    //                            w,s,b,s,wh
    std::vector<int> resources = {0,0,0,0,0};
    std::vector<Road*> roads;
    std::vector<Building*> buildings;
    CardStack devCards;

    public:

    explicit Player(std::string name);

    //add resource to player
    void getResource(resourceType r, int num);

    //take resourcce from player
    void giveResource(resourceType r, int num);

    //show players resources
    void showResources();

    //take their turn
    void takeTurn();

    //display options to buy things
    void buyMenu();

    // adds vp, return true if player has over 10 vp
    bool addVP(int pVP);

    //remove vp from a player
    void removeVP(int pVP);

    std::string getName() const;

    bool hasWon();
};



#endif //PLAYER_H
