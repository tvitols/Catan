//
// Created by tvito on 9/24/2025.
//

#include "Game.h"
#include "Road.h"
#include "Building.h"


// Allow cross platform sleep
#ifndef CATAN_OVERRIDESLEEP_H
#include <windows.h>
#endif
#ifdef CATAN_OVERRIDESLEEP_H
#include <unistd.h>
#define Sleep sleep
#endif

Game::Game() : board(Board::generateBoard()), adjGraph(AdjacencyGraph(&board)), deck(new Deck()) {
    players = {
        new Player(new std::string("Player 1"), red), new Player(new std::string("Player 2"), white)
    };
}

int Game::Play() {
    // // Clear the input before starting game
    // std::cin.clear();
    // std::string junk;
    // std::getline(std::cin,junk);

    // Run loop until game is over
    while (!gameOver) {
        // Loop through all players
        for (const auto player : players) {

            //Let them know whose turn it is
            std::cout << std::endl << player->getName() << ", your turn!" << std::endl << std::endl;

            // Show resources that they collected during other players' turns
            std::cout << "During other players turns, you collected: ";
            player->showCollectedResources();
            std::cout << std::endl;

            // Roll the dice
            const int roll = dice() + dice();
            std::cout << "You rolled a " << roll << std::endl << std::endl;

            // If the roll is a 7, handle it
            if (roll == 7) {
                onA7(player);
            }else { // Collect Resources
                std::cout << "Collecting Resources..." << std::endl;
                board.collectResources(roll);
                std::cout << "You got ";
                player->showCollectedResources();
            }
            std::cout << std::endl;

            /* Action holds the code that allows communication between player and board
             *
             * Codes as follows:
             *
             * 200 - start of turn (input only)
             * 0 - end of turn (return only)
             *
             * The following indicate an attempt as a return and are passed as is for a success or negative for a failure
             * 1 - Place a settlement
             * 2 - Place a city
             * 3 - Place a road
             * 4 - Play a "Knight" Dev Card
             * 5 - Play a "Road Building" Dev Card
             * 6 - View Board
             *
             * Invalid codes will end turn
             */
            int action = (player->takeTurn(players, 200, deck));
            while (action != 0) {
                switch (action) {
                    // Place structure and update action
                    case 1: case 2: case 3: action = player->takeTurn(players,placeStructure(player, action),deck); break;

                    // Play a knight
                    case 4: {
                        // Get a tile to move the robber to
                        coords xy = board.printBoard((player)->getName().append(", where would you like to move the robber?"));
                        while (board.getTile(xy) == nullptr) {
                            std::cout << "You didn't chose a tile!" << std::endl;
                            xy = board.printBoard((player)->getName().append(", where would you like to move the robber?"));
                        }

                        // Move the robber
                        board.moveRobber(board.getTile(xy));

                        // Steal a resource from a player
                        std::string name = player->moveRobber(board.otherPlayerResources(player->getName()));
                        if (!name.empty()) {
                            Resource stolen = board.getRandomResource(name);
                            player->addResource(stolen);
                            std::cout << "You got " << stolen.type << "!" << std::endl << std::endl;
                        }

                        //Update action
                        action = (player->takeTurn(players, action, deck));
                        break;
                    }
                    // Play Road Building
                    case 5:
                        //Place two roads
                        for (int i = 0; i < 2; i++) {
                            while (placeStructure(player,3) == -3) {
                                std::cout << "Invalid Placement" << std::endl << std::endl;
                            }
                        }

                        //update action
                        action = player->takeTurn(players,action,deck);
                        break;

                    // View the board, update action
                    case 6: board.printBoard("Press anywhere to exit"); action = player->takeTurn(players,6,deck); break;

                    // Errors end turn
                    default: action = 0; break;
                }
            }
            // If the player has won end the game
            gameOver = player->hasWon();
            winners.push_back(player);
            if (gameOver) {
                break;
            }
        }
    }

    // Give every other player their last turn
    for (const auto player : players) {

        if (player == winners[0]) {
            continue;
        }

        //Let them know whose turn it is
        std::cout << std::endl << player->getName() << ", this is your final turn!" << std::endl << std::endl;

        // Show resources that they collected during other players' turns
        std::cout << "During other players turns, you collected: ";
        player->showCollectedResources();
        std::cout << std::endl;

        // Roll the dice
        const int roll = dice() + dice();
        std::cout << "You rolled a " << roll << std::endl << std::endl;

        // If the roll is a 7, handle it
        if (roll == 7) {
            onA7(player);
        }else { // Collect Resources
            std::cout << "Collecting Resources..." << std::endl;
            board.collectResources(roll);
            std::cout << "You got ";
            player->showCollectedResources();
        }
        std::cout << std::endl;

        /* Action holds the code that allows communication between player and board
         *
         * Codes as follows:
         *
         * 200 - start of turn (input only)
         * 0 - end of turn (return only)
         *
         * The following indicate an attempt as a return and are passed as is for a success or negative for a failure
         * 1 - Place a settlement
         * 2 - Place a city
         * 3 - Place a road
         * 4 - Play a "Knight" Dev Card
         * 5 - Play a "Road Building" Dev Card
         * 6 - View Board
         *
         * Invalid codes will end turn
         */
        int action = (player->takeTurn(players, 200, deck));
        while (action != 0) {
            switch (action) {
                // Place structure and update action
                case 1: case 2: case 3: action = player->takeTurn(players,placeStructure(player, action),deck); break;

                // Play a knight
                case 4: {
                    // Get a tile to move the robber to
                    coords xy = board.printBoard((player)->getName().append(", where would you like to move the robber?"));
                    while (board.getTile(xy) == nullptr) {
                        std::cout << "You didn't chose a tile!" << std::endl;
                        xy = board.printBoard((player)->getName().append(", where would you like to move the robber?"));
                    }

                    // Move the robber
                    board.moveRobber(board.getTile(xy));

                    // Steal a resource from a player
                    std::string name = player->moveRobber(board.otherPlayerResources(player->getName()));
                    if (!name.empty()) {
                        Resource stolen = board.getRandomResource(name);
                        player->addResource(stolen);
                        std::cout << "You got " << stolen.type << "!" << std::endl << std::endl;
                    }

                    //Update action
                    action = (player->takeTurn(players, action, deck));
                    break;
                }
                // Play Road Building
                case 5:
                    //Place two roads
                    for (int i = 0; i < 2; i++) {
                        while (placeStructure(player,3) == -3) {
                            std::cout << "Invalid Placement" << std::endl << std::endl;
                        }
                    }

                    //update action
                    action = player->takeTurn(players,action,deck);
                    break;

                // View the board, update action
                case 6: board.printBoard("Press anywhere to exit"); action = player->takeTurn(players,6,deck); break;

                // Errors end turn
                default: action = 0; break;
            }
        }
        // If the player has won end the game
        if (player->hasWon()) {
            winners.push_back(player);
        }
    }

    std::cout << "Congratulations ";
    auto player = winners.begin();
    while (player != winners.end()) {
        std::cout << (*player)->getName() << (player+1 == winners.end()?"":", ");
        ++player;
    }
    std::cout << (winners.size()==1?" you win!":" you all tie!");

    // return 0 to end game
    return 0;
}

void Game::onA7(Player* player) {

    // Keep track of if we rob other players
    int otherPlayersRobbed = 0;

    // Remove cards for greedy people
    std:: cout << "The Robber will now steal cards from anyone with over 7 cards!" << std::endl << std::endl;
    for (const auto &robbed : players) {
        if (robbed != player) {
            if (robbed->rolledASeven()) {
                otherPlayersRobbed++;
                std::cout << std::endl;
                robbed -> loseHalfOfCards();
            }
        }
    }

    // If other players were robbed, shift back to main player's turn. If no players were robbed this is not necessary
    if (otherPlayersRobbed != 0) {
        std::cout << std::endl << std::endl << std::endl << "\nOkay " << player->getName() << " back to your turn" << std::endl << std::endl;
    }

    // Steal half of main player's cards if necessary
    if (player->rolledASeven()) {
        player -> loseHalfOfCards();
    }
    else {
        std::cout << "You had less than 7 cards!" << std::endl << std::endl;
    }

    //Move the Robber
    coords xy = board.printBoard((player)->getName().append(", where would you like to move the robber?"));
    while (board.getTile(xy) == nullptr) {
        std::cout << "You didn't chose a tile!" << std::endl;
        xy = board.printBoard((player)->getName().append(", where would you like to move the robber?"));
    }
    board.moveRobber(board.getTile(xy));

    // Steal from a player
    std::string name = player->moveRobber(board.otherPlayerResources(player->getName()));
    if (!name.empty()) {
        Resource stolen = board.getRandomResource(name);
        player->addResource(stolen);
        std::cout << "You got " << stolen.type << "!" << std::endl << std::endl;
    }
}

int Game::placeStructure(Player *player, const int type) {

    switch (type) {
        case 1: {
            // Get a vertex
            Vertex* vertex = board.getVertex("Place a settlement");

            // If it is a valid placement and the placement succeeds, success
            if (adjGraph.checkVertex(vertex,player) && vertex->setBuilding(new Building(player))) {
                return 1;
            }
            return -1;
        }
        case 2: {
            // Get a vertex and try to upgrade a building on it
            if (board.getVertex("Select a settlement to upgrade")->upgradeBuilding(player)) {
                return 2;
            }
            return -2;
        }
        case 3: {
            // Get an edge
            Edge* edge = board.getEdge("Place a road");

            // If it is a valid placement and the placement succeeds, success
            if (adjGraph.checkEdge(edge,player) && edge->setRoad(new Road(player))) {
                return 3;
            }
            return -3;
        }
        default: return 0;
    }


}


void Game::setUp() {

    // Create iterator to loop through players in snake draft
    auto iter = players.begin();

    // Loop forwards
    while (iter != players.end()) {
        // Place a settlement
        Vertex* vertex;
        Building* building = new Building(*iter);
        while (true) {
            vertex = board.getVertex((*iter)->getName().append(", place a settlement"));
            if (vertex != nullptr && adjGraph.checkVertex(vertex,*iter,true) && vertex->setBuilding(building)) {
                break;
            }
            std::cout << "INVALID PLACEMENT" << std::endl;
            Sleep(500);

        }

        // Place a road
        Edge* edge;
        Road* road= new Road(*iter);
        while (true) {
            edge = board.getEdge((*iter)->getName().append(", place a road"));
            if (edge != nullptr && adjGraph.checkEdge(edge,*iter) && edge->setRoad(road)) {
                break;
            }
            std::cout << "INVALID PLACEMENT" << std::endl;
            Sleep(500);
        }

        ++iter;
    }

    // Reset to avoid out-of-bounds
    --iter;

    //Loop backwards
    while (iter >= players.begin()) {

        // Place a second settlement
        Vertex* vertex;
        Building* building = new Building(*iter);
        while (true) {
            vertex = board.getVertex((*iter)->getName().append(", place another settlement"));
            if (vertex != nullptr && adjGraph.checkVertex(vertex,*iter,true) && vertex->setBuilding(building)) {
                    break;
            }
            std::cout << "INVALID PLACEMENT" << std::endl;
            Sleep(500);
        }

        // Place a second road
        Edge* edge;
        Road* road= new Road(*iter);
        while (true) {
            edge = board.getEdge((*iter)->getName().append(", place a road"));
            if (edge != nullptr && adjGraph.checkEdge(edge,*iter) && edge->setRoad(road)) {
                break;
            }
            std::cout << "INVALID PLACEMENT" << std::endl;
            Sleep(500);
        }

        --iter;
    }
}
