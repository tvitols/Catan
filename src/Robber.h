//
// Created by tvito on 9/16/2025.
//

#ifndef ROBBER_H
#define ROBBER_H
#include "Tile.h"


class Robber {

    Tile* currentTile;

    public:

    /**
     * default constructor
     */
    Robber();
    /**
     * default destructor
     */
    ~Robber() = default;

    /**
     * changes robbed on currentTile to false
     * sets currentTile to newTile
     * changes robbed on new currentTile to true
     * @param newTile Tile to move to
     */
    void move(Tile* newTile);

    /**
     * sets currentTile to newTile
     * @param newTile Tile to start with
     */
    void setCurrentTile(Tile* newTile);

    /**
     *
     * @return currentTile
     */
    Tile* getCurrentTile();

    /**
     * calls currentTile->otherPlayerResources(name)
     * @param name
     * @return vector of all names and resources of players on tile (whose names do not equal name)
     */
    std::vector<std::tuple<std::string, std::vector<int>>> otherPlayerResources(std::string name);

    /**
     *
     * @param name name of player to steal from
     * @return currentTile->stealResource(name);
     */
    Resource getRandomResource(std::string name);

};



#endif //ROBBER_H
