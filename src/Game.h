//
// Created by tvito on 9/24/2025.
//

#ifndef CATAN_GAME_H
#define CATAN_GAME_H

#include "Board.h"
#include "AdjacencyGraph.h"
#include "Deck.h"

class Game {

    Board board;
    std::vector<Player*> players;
    int numTurns = 0;
    bool gameOver = false;
    AdjacencyGraph adjGraph;
    Deck* deck;

    public:

    Game();
    explicit Game(const std::vector<Player*>& players) : board(Board::generateBoard()), players(players),adjGraph(AdjacencyGraph(&board)), deck(new Deck()){};
    Game(const std::vector<Player*>& players, const int seed) : board(Board::generateBoard(seed)), players(players),adjGraph(AdjacencyGraph(&board)), deck(new Deck(seed)){};
    ~Game() = default;

    int Play();
    void onA7(Player* player);
    int placeStructure(Player* player, int type);
    void setUp();

};


#endif //CATAN_GAME_H