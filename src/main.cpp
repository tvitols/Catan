//
// Created by tvito on 9/16/2025.
//

#include <iostream>
#include <vector>

#include "CustomUtils.h"
#include "Info.h"
#include "Player.h"
#include "Board.h"

using namespace std;

int main() {

    cout << "Welcome to Catan" << endl;

    char choice;
    while (!choice) {
        cout << "Press (p) to play, (r) for the rules, (i) for more info, or (q) to quit: ";
        cin >> choice;
        checkCin(&choice);
        switch (choice){
            case 'p': case 'P': break;

            case 'i': case 'I': choice = 0; Info::print_info(); break;

            case 'r': case 'R': choice = 0; Info::print_rules(); break;

            case 'q': case 'Q': return 0;

            default: choice = 0; cout << "Invalid choice" << endl; break;
        }
    }

    int numPlayers;
    cout << "Select number of players (2-4): ";
    cin >> numPlayers;
    checkCin(&numPlayers);
    while (numPlayers < 2 || numPlayers > 4){

        cout << "Invalid number of players. Select number of players (2-4): ";
        cin >> numPlayers;
        checkCin(&numPlayers);
    }
    cout << "Players: " << numPlayers << endl;

    vector<Player> players;
    string name;
    for (int i = 0; i < numPlayers; i++) {
        cout << "Player " << i + 1 << ", enter your name: ";
        cin >> name;
        if (name.empty() || name.length() > 50) {
            cout << "Invalid name." << endl;
            i --; break;
        }
        players.emplace_back(&name);
    }
    Board board = Board::generateBoard();
    bool gameWon = false;
    int p = 10;
    while (!gameWon) {
        for (auto &player : players) {
            cout << player.getName() << ", your turn!" << endl;
            // player.takeTurn();
            // gameWon = player.hasWon();
            gameWon = !(--p);
        }
    }

}