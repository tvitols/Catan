//
// Created by tvito on 9/16/2025.
//

#ifndef STRUCTURE_H
#define STRUCTURE_H
using namespace std;
#include <vector>;
#inlude <"Player.h";



class Structure {
    //The player that owns the structure
    Player* player;
    enum necessaryResources : int = {wood = 0, stone = 0, brick = 0, sheep = 0, wheat = 0};
    int victoryPoint;

    public:
    Structure();
    ~Structure();

    bool place();
    bool buy();

    //Adds the number of victory points each structure is worth to the Player
    int addsVictoryPoint();



};



#endif //STRUCTURE_H
