//
// Created by tvito on 9/24/2025.
//

#ifndef CATAN_GAME_H
#define CATAN_GAME_H
#include "Board.h"
#include "Robber.h"


class Game {

    Board board;
    std::vector<Player*> players;
    int numTurns = 0;
    bool gameOver = false;
    Robber robber;
    Robber* robberPtr;

    public:

    Game();
    explicit Game(const std::vector<Player*>& players) : robber(Robber()), robberPtr(&robber), board(Board::generateBoard(robberPtr)), players(players) {};
    Game(const std::vector<Player*>& players, int seed) : robber(Robber()), robberPtr(&robber), board(Board::generateBoard(seed)), players(players) {};
    ~Game() = default;

    int Play();
    void takeTurn(Player* player);

};


#endif //CATAN_GAME_H