//
// Created by tvito on 9/16/2025.
//

#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <vector>


class Structure {
    //Create Player pointer to the player that owns the structure
    enum necessaryResources : int {wood = 0, stone = 0, brick = 0, sheep = 0, wheat = 0};
    int victoryPoint;

    public:
    Structure() = default;
    ~Structure() = default;

    bool place();
    bool buy();

    //Adds the number of victory points each structure is worth to the Player
    int addsVictoryPoint();



};



#endif //STRUCTURE_H
