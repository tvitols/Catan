//
// Created by tvito on 9/24/2025.
//

#ifndef CATAN_GAME_H
#define CATAN_GAME_H

#include "Board.h"
#include "AdjacencyGraph.h"
#include "Deck.h"

class Game {


    /**
     * The Board for the game
     */
    Board board;
    /**
     * The vector of players. Size is between 2 and 4
     */
    std::vector<Player*> players;

    /**
     * Holds whether the game is over
     */
    bool gameOver = false;
    /**
     * A graph representation of the board to allow for adjacency checking and placement validation
     */
    AdjacencyGraph adjGraph;
    /**
     * The deck of development cards
     */
    Deck* deck;

    public:

    /**
     * A dummy constructor that creates a new game with "Player 1" and "Player 2"
     */
    Game();
    /**
     * Creates a new game with given list of players, uses default randomization
     * @param players The list of players for the game
     */
    explicit Game(const std::vector<Player*>& players) : board(Board::generateBoard()), players(players),adjGraph(AdjacencyGraph(&board)), deck(new Deck()){};
    /**
     * Creates a new game with given list of players, uses seed to seed the board generation
     * @param players The list of players for the game
     * @param seed The seed for the board
     */
    Game(const std::vector<Player*>& players, const int seed) : board(Board::generateBoard(seed)), players(players),adjGraph(AdjacencyGraph(&board)), deck(new Deck(seed)){};
    /**
     * Trivial Deconstructor
     */
    ~Game() = default;

    /**
     * Plays the game. Make sure to run Game::setUp() before running play;
     * @returns 0 on completion of game, -1 on critical error
     */
    int Play();
    /**
     * Function to handle events when a player that rolls a 7
     * @param player The player who rolled the 7
     */
    void onA7(Player* player);
    /**
     * Function to allow a player to place a structure on the board
     * @param player The player that needs to place the structure
     * @param type  The type of structure to place: 1 - Settlement, 2 - City, 3 - Road
     * @return
     */
    int placeStructure(Player* player, int type);
    /**
     * Function to perform basic board setup (i.e. placing starting structures) before the game starts. Always run before Game::Play()
     */
    void setUp();

};


#endif //CATAN_GAME_H