//
// Created by tvito on 9/24/2025.
//

#ifndef CATAN_GAME_H
#define CATAN_GAME_H
#include "Board.h"
#include "Player.h"
#include "Robber.h"


class Game {

    Board board;
    std::vector<Player*> players;
    int numTurns = 0;
    bool gameOver = false;

    public:

    Game();
    explicit Game(const std::vector<Player*>& players) : board(Board::generateBoard()), players(players) {};
    Game(const std::vector<Player*>& players, int seed) : board(Board::generateBoard(seed)), players(players) {};
    ~Game() = default;

    void Play();
    void takeTurn(Player* player);

};


#endif //CATAN_GAME_H