//
// Created by tvito on 9/16/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include <vector>

#include "Tile.h"
#include "Robber.h"


class Board {
    //Vector of Tiles on the Board
    std::vector<std::vector<Tile*>> tiles;


    /**
     * calls generateTiles()
     * sets the current Tile of Robber to the desert
     * @param pRobber specific Robber to use
     */
    explicit Board(Robber* pRobber);
    /**
     * calls generateTiles()
     * sets the current Tile of Robber to the desert
     * @param seed specific seed to use
     */
    explicit Board(int seed);
    /**
     * Creates a vector of Edges
     * Creates a vector of Vertices (some being Ports)
     * Initializes a vector of vectors of Tiles, each with the 6 corresponding Edges and Vertices
     * Sets the coordinates for all Tiles, Edges, and Vertices
     * @param twist specific twist to use
     */
    void generateTiles(std::mt19937 twist);
    /**
     * Sets robber to a nullptr initially
     */
    Robber* robber = nullptr;


public:
    /**
     * default constructor
     */
    Board();
    /**
     * default destructor
     */
    ~Board();

    /**
     *
     * @return Board()
     */
    static Board generateBoard();
    /**
     *
     * @param robber Robber being passed to the Board
     * @return Board(robber)
     */
    static Board generateBoard(Robber* robber);
    /**
     * @param seed specific seed to be used
     * @return a Board(robber)
     */
    static Board generateBoard(int seed);

    /**
     * graphically displays the Tiles, Ports, and Structures on Board
     * @param message message to be displayed
     * @return the coords of a place the user clicks
     */
    coords printBoard(const std::string &message);

    /**
     * iterates through all Tiles and calls collectResources(roll) on them
     * @param roll dice roll of the round
     */
    void collectResources(int roll) const;


    /**
     * called otherPlayerResources(name) on Robber
     * @param name name of player moving Robber
     * @return a vector of the names and resources of all players on the currentTile of the Robber
     */
    std::vector<std::tuple<std::string, std::vector<int>>> otherPlayerResources(std::string name);

    /**
     *
     * @param coordinates coords of an Edge
     * @return Edge if the coords correspond to a Edge, nullptr otherwise
     */
    Edge* getEdge(coords coordinates);
    /**
     *
     * @param coordinates coords of a Vertex
     * @return Vertex if the coords correspond to a Vertex, nullptr otherwise
     */
    Vertex* getVertex(coords coordinates);
    /**
     *
     * @param message message user wants to display with Board
     * @return calls getEdge(coords) with coords obtained from printBoard()
     */
    Edge* getEdge(const std::string &message);
    /**
     *
     * @param message message user wants to display with Board
     * @return calls getVertex(coords) with coords obtained from printBoard()
     */
    Vertex* getVertex(const std::string &message);
    /**
     *
     * @param coordinates coords of a Tile
     * @return Tile if the coords correspond to a Tile, nullptr otherwise
     */
    Tile* getTile(coords coordinates);
    /**
     *
     * @return vector of the vectors of Tiles
     */
    std::vector<std::vector<Tile*>> getTiles();

    /**
     * calls move() from Robber
     * @param tile Tile to move Robber to
     */
    void moveRobber(Tile* tile);

    /**
     * calls getRandomResource() from Robber
     * @param name name of player to steal resources from
     * @return the random Resource stolen
     */
    Resource getRandomResource(std::string name);

};


#endif //BOARD_H
