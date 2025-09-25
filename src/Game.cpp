//
// Created by tvito on 9/24/2025.
//

#include "Game.h"

Game::Game() : board(Board::generateBoard()) {
    players = {new Player(new std::string("Player 1")), new Player(new std::string("Player 2"))};
}

void Game::Play() {
    while (!gameOver) {
        for (const auto &player : players) {
            std::cout << player->getName() << ", your turn!" << std::endl;
            std::cout << "During other players turns, you collected: ";
            player->showCollectedResources();
            const int roll = dice() + dice();
            std::cout << "You rolled a " << roll << std::endl;
            std::cout << "Collecting Resources..." << std::endl;
            board.collectResources(roll);
            std::cout << "You got ";
            player->showCollectedResources();
            player->takeTurn(players);
            gameOver = player->hasWon();
        }
    }
}

void Game::takeTurn(Player *player) {
}
