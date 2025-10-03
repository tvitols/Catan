//
// Created by tvito on 9/24/2025.
//

#ifndef CATAN_GAME_H
#define CATAN_GAME_H

#include "Board.h"
#include "Robber.h"
#include "AdjacencyGraph.h"


class Game {

    Board board;
    std::vector<Player*> players;
    int numTurns = 0;
    bool gameOver = false;

    AdjacencyGraph adjGraph;

    public:

    Game();
    explicit Game(const std::vector<Player*>& players) : board(Board::generateBoard()), players(players),adjGraph(AdjacencyGraph(&board)){};
    Game(const std::vector<Player*>& players, const int seed) : board(Board::generateBoard(seed)), players(players),adjGraph(AdjacencyGraph(&board)) {};
    ~Game() = default;

    int Play();
    void onA7(Player* player);
    void takeTurn(Player* player);
    void setUp();

};


#endif //CATAN_GAME_H