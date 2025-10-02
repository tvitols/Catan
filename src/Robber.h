//
// Created by tvito on 9/16/2025.
//

#ifndef ROBBER_H
#define ROBBER_H
#include "Tile.h"


class Robber {

    Tile* currentTile;

    public:

    Robber();
    ~Robber() = default;

    //iterate through the tile vertices and return a list of players on that tile
    void move(Tile* newTile);

    void setCurrentTile(Tile* newTile);

    Tile* getCurrentTile();

    std::vector<std::tuple<std::string, std::vector<int>>> otherPlayerResources(std::string name);

    // resourceType stealResource(std::string name);

};



#endif //ROBBER_H
