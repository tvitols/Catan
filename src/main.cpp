//
// Created by tvito on 9/16/2025.
//

#include <iostream>
#include <vector>

#include "CustomUtils.h"
#include "Info.h"
#include "Player.h"
#include "Game.h"
#include "cppgraphics.hpp"

using namespace std;

int runGUI(bool fullscreen);
int runCLI();

int main(const int argc, char *argv[]) {

    if (argc == 1) {
        return runCLI();
    }

    const string mode = argv[1];

    if (mode == "GUI" || mode == "g") {
        if (argc == 3 && string(argv[2]) == "f") {
            return runGUI(true);

        }
        return runGUI(false);
    }

    if (mode == "CLI" || mode == "c") {
        return runCLI();
    }

    return -1;
}

int runGUI(bool fullscreen) {


    cg::create_window("Catan",-1,-1,fullscreen);

    double xSize = cg::get_window_width();
    double ySize = cg::get_window_height();

    cg::text_centered("Welcome to Catan",xSize/2, ySize/5,50.);

    cg::set_color(cg::White);
    cg::rectangle(xSize/6,ySize/3,300,100);
    cg::set_color(cg::DarkGreen);
    cg::text("Play",xSize/6+50,ySize/3+25,200,50);

    while (cg::wait_until_mouse(-1) != cg::MouseLeft) {}

    if (xSize / 6 < cg::get_mouse_x() && cg::get_mouse_x() < xSize / 6 + 300 &&
        ySize/3 < cg::get_mouse_y() && cg::get_mouse_y() < ySize / 3 + 100) {

        const string n1 = "TV";
        const string n2 = "LE";

        const vector<Player *> players = {new Player(&n1),new Player(&n2)};
        auto game = Game(players);
        return game.Play();
    }

    cg::wait_until_closed();

    return 0;
}


int runCLI() {

    cout << "Welcome to Catan" << endl;

    char choice = (char)NULL;
    while (!choice) {
        cout << "Press (p) to play, (r) for the rules, (i) for more info, or (q) to quit: ";
        cin >> choice;
        checkCin(&choice);
        switch (choice){
            case 'p': case 'P':  break;

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

    vector<Player*> players;
    string name;
    for (int i = 0; i < numPlayers; i++) {
        cout << "Player " << i + 1 << ", enter your name: ";
        cin >> name;
        if (name.empty() || name.length() > 50) {
            cout << "Invalid name." << endl;
            i --; break;
        }
        players.push_back(new Player(&name));
    }

    auto game = Game(players);
    return game.Play();

}
