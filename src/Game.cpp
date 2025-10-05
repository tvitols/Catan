//
// Created by tvito on 9/24/2025.
//

#include "Game.h"
#include "Road.h"
#include "Building.h"
#include <windows.h>

Game::Game() : board(Board::generateBoard()), adjGraph(AdjacencyGraph(&board)) {
    players = {
        new Player(new std::string("Player 1"), red), new Player(new std::string("Player 2"), white)
    };
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
            int action = 200;
            coords xy;
            std::string name;
            while (action != 0) {
                action = (player->takeTurn(players, action, deck));
                switch (action) {
                    case 0: break;
                    case 1: case 2: case 3: action = player->takeTurn(players,placeStructure(player, action),deck); break;
                    case 4:
                        xy = board.printBoard((player)->getName().append(", where would you like to move the robber?"));
                        while (board.getTile(xy) == nullptr) {
                            std::cout << "You didn't chose a tile!" << std::endl;
                            xy = board.printBoard((player)->getName().append(", where would you like to move the robber?"));
                        }
                        board.moveRobber(board.getTile(xy));
                        name = player->moveRobber(board.otherPlayerResources(player->getName()));
                        if (!name.empty()) {
                            player->addResource(board.getRandomResource(name));
                        }
                        break;
                    case 5:
                        for (int i = 0; i < 2; i++) {
                            while (placeStructure(player,3) != -3) {
                                std::cout << "Invalid Placement" << std::endl;
                            }
                        }
                        action = player->takeTurn(players,action,deck);
                        break;
                    case 6: board.printBoard("",true); std::cout << "hi" <<std::endl;action = player->takeTurn(players,placeStructure(player, 0),deck); break;
                    default: action = 0; break;
                }
            }
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
    std::string name = player->moveRobber(board.otherPlayerResources(player->getName()));
    if (!name.empty()) {
        player->addResource(board.getRandomResource(name));
    }
}

int Game::placeStructure(Player *player, const int type) {

    switch (type) {
        case 1: {
            Vertex* vertex = board.getVertex("Place a settlement");
            if (adjGraph.checkVertex(vertex,player) && vertex->setBuilding(new Building(player))) {
                return 1;
            }
            return -1;
        }
        case 2: {
            if (board.getVertex("Select a settlement to upgrade")->upgradeBuilding(player)) {
                return 2;
            }
            return -2;
        }
        case 3: {
            Edge* edge = board.getEdge("Place a road");
            if (adjGraph.checkEdge(edge,player) && edge->setRoad(new Road(player))) {
                return 3;
            }
            return -3;
        }
        default: return 0;
    }


}


void Game::setUp() {

    auto iter = players.begin();

    while (iter != players.end()) {
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

    --iter;

    while (iter >= players.begin()) {
        Vertex* vertex;
        Building* building = new Building(*iter);
        while (true) {
            vertex = board.getVertex((*iter)->getName().append(", place another settlement"));
            if (adjGraph.checkVertex(vertex,*iter,true) && vertex->setBuilding(building)) {
                    break;
            }
            std::cout << "INVALID PLACEMENT" << std::endl;
            Sleep(500);
        }

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
