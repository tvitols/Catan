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
            player->addResource(Resource(wood, 15));
            std::cout << "During other players turns, you collected: ";
            player->showCollectedResources();
            const int roll = 7;
                //dice() + dice();
            std::cout << "You rolled a " << roll << std::endl;
            if (roll == 7) {
                int otherPlayersRobbed = 0;
                std:: cout << "The Robber will now steal cards from anyone with over 7 cards!" << std::endl;
                for (const auto &robbed : players) {
                    if (robbed != player) {
                        if (robbed->rolledASeven()) {
                            otherPlayersRobbed++;
                            std::cout << "\n";
                            robbed -> loseHalfOfCards();
                        }
                    }
                }
                if (otherPlayersRobbed != 0) {
                    std::cout << "\nOkay " << player->getName() << " back to your turn" << std::endl;
                }
                if (player->rolledASeven()) {
                    player -> loseHalfOfCards();
                }
                else {
                    std::cout << "You had less than 7 cards!" << std::endl;
                }
            }
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
