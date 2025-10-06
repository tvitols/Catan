//
// Created by tvito on 9/16/2025.
//

#include <iostream>
#include <vector>

#include "CustomUtils.h"
#include "Info.h"
#include "Player.h"
#include "Game.h"
#include <set>

using namespace std;

int main() {

    const string welcome =  " ___       __   _______   ___       ________  ________  _____ ______   _______           _________  ________          ________  ________  _________  ________  ________\n"
                            "|\\  \\     |\\  \\|\\  ___ \\ |\\  \\     |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\         |\\___   ___\\\\   __  \\        |\\   ____\\|\\   __  \\|\\___   ___\\\\   __  \\|\\   ___  \\    \n"
                            "\\ \\  \\    \\ \\  \\ \\   __/|\\ \\  \\    \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|        \\|___ \\  \\_\\ \\  \\|\\  \\       \\ \\  \\___|\\ \\  \\|\\  \\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\\\ \\  \\   \n"
                            " \\ \\  \\  __\\ \\  \\ \\  \\_|/_\\ \\  \\    \\ \\  \\    \\ \\  \\\\\\  \\ \\  \\\\|__| \\  \\ \\  \\_|/__           \\ \\  \\ \\ \\  \\\\\\  \\       \\ \\  \\    \\ \\   __  \\   \\ \\  \\ \\ \\   __  \\ \\  \\\\ \\  \\  \n"
                             " \\ \\  \\|\\__\\_\\  \\ \\  \\_|\\ \\ \\  \\____\\ \\  \\____\\ \\  \\\\\\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\           \\ \\  \\ \\ \\  \\\\\\  \\       \\ \\  \\____\\ \\  \\ \\  \\   \\ \\  \\ \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \n"
                              " \\ \\____________\\ \\_______\\ \\_______\\ \\_______\\ \\_______\\ \\__\\    \\ \\__\\ \\_______\\           \\ \\__\\ \\ \\_______\\       \\ \\_______\\ \\__\\ \\__\\   \\ \\__\\ \\ \\__\\ \\__\\ \\__\\\\ \\__\\\n"
                               " \\|____________|\\|_______|\\|_______|\\|_______|\\|_______|\\|__|     \\|__|\\|_______|            \\|__|  \\|_______|        \\|_______|\\|__|\\|__|    \\|__|  \\|__|\\|__|\\|__| \\|__|\n"
                                " \n\n______________________________________________________________________________________________________________________________________________________________________";

    cout << welcome << endl << endl << endl;

    int choice = 0;
    while (!choice) {
        cout << "Select an option to get started:"
                "\n1. Play"
                "\n2. Rules of Catan"
                "\n3. Info"
                "\n4. Quit"
                "\n>>> ";
        choice = getIntFromUser();
        switch (choice){
            case 1:  break;
            //Printing info
            case 2: choice = 0; Info::print_info(); break;
            //Printing rules
            case 3: choice = 0; Info::print_rules(); break;
            //Ending game
            case 4: return 0;

            default: choice = 0; cout << "Invalid choice" << endl; break;
        }
    }

    cout << "Enter the number of players (2-4): ";
    int numPlayers = getIntFromUser();
    //Validation
    while (numPlayers < 2 || numPlayers > 4){

        cout << "Invalid number of players. Select number of players (2-4): ";
        numPlayers = getIntFromUser();
    }
    //Creating Players
    vector<Player*> players;
    string name;
    vector<playerColor> availableColors = {red, white, blue, green};
    for (int i = 0; i < numPlayers; i++) {
        choice = 0;
        //Obtaining player name
        cout << "Player " << i + 1 << ", enter your name: ";
        getline(cin, name);
        cout << endl;
        if (name.empty() || name.length() > 50) {
            cout << "Invalid name." << endl;
            i --;
        }else {
            while (choice < 1 || choice > availableColors.size()+1) {
                cout << "Pick your color:" << endl;
                for (int j = 0; j < availableColors.size(); j++) {
                    cout << j+1 << ". " << (availableColors[j]) << endl;
                }
                cout << ">>> ";
                choice = getIntFromUser();
            }
            players.push_back(new Player(&name,static_cast<playerColor>(choice)));
            availableColors.erase(availableColors.begin()+choice-1);
            cout << endl;
        }
    }
    //Playing Game!
    auto game = Game(players);
    game.setUp();
    game.Play();
}