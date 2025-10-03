//
// Created by tvito on 9/24/2025.
//

#include "Game.h"

Game::Game() : board(Board::generateBoard()) {
    players = {new Player(new std::string("Player 1"),red), new Player(new std::string("Player 2"),white)};
}

int Game::Play() {
    while (!gameOver) {
        for (const auto &player : players) {
            std::cout << player->getName() << ", your turn!" << std::endl;
            std::cout << "During other players turns, you collected: ";
            player->showCollectedResources();
            const int roll = dice() + dice();
            std::cout << "You rolled a " << roll << std::endl;
            if (roll == 7) {
                onA7(player);
            }else {
                std::cout << "Collecting Resources..." << std::endl;
                board.collectResources(roll);
                std::cout << "You got ";
                player->showCollectedResources();
            }
            player->takeTurn(players);
            gameOver = player->hasWon();
        }
    }
    return 0;
}

void Game::onA7(Player* player) {
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
    coords xy = board.printBoard((player)->getName().append(", where would you like to move the robber?"));
    while (board.getTile(xy) == nullptr) {
        std::cout << "You didn't chose a tile!" << std::endl;
        xy = board.printBoard((player)->getName().append(", where would you like to move the robber?"));
    }
    board.moveRobber(board.getTile(xy));
    player->moveRobber(board.otherPlayerResources(player->getName()));
    //TODO: implement getting a random resource
}

void Game::takeTurn(Player *player) {
}

void Game::setUp() {

    auto iter = players.begin();

    while (iter != players.end()) {
        coords xy = board.printBoard((*iter)->getName().append(", place a settlement"));
        board.getEdge(xy);
        std::cout << xy << std::endl;
        xy = board.printBoard((*iter)->getName().append(", place a road"));
        board.getEdge(xy);
        std::cout << xy << std::endl;

        ++iter;
    }

    --iter;

    while (iter >= players.begin()) {
        coords xy = board.printBoard((*iter)->getName().append(", place another settlement"));
        board.getEdge(xy);
        std::cout << xy << std::endl;
        xy = board.printBoard((*iter)->getName().append(", place another road"));
        board.getEdge(xy);
        std::cout << xy << std::endl;

        --iter;
    }
}
