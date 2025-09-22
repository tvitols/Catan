//
// Created by tvito on 9/16/2025.
//

#include "Player.h"

#include <algorithm>
#include <iostream>

#include "City.h"
#include "Settlement.h"

Player::Player(const std::string *pname) {
    name = *pname;
}

void Player::getResource(const resourceType r, const int num = 1) {
    resources[r] += num;
}

tuple<resourceType, int> Player::giveResource(resourceType r, int num) {
    resources[r] -= num;
    return std::make_tuple(r,  num);
}

void Player::showResources() {
    for (int i = 0; i < 5; i++) {
        cout<<(resourceType)i;
    }
    cout << endl;
    for (const auto r : resources) {
        cout << r << endl;
    }
    cout << endl;
}

void Player::takeTurn() {
    const int roll = dice() + dice();
    cout << "You rolled a " << roll << endl;
    cout << "Collecting Resources" << endl;
    cout << "You got " << endl;
    for (const auto b : buildings) {
        auto[r,num] = b->giveResources(roll);
        getResource(r,num);
    }
    char choice;
    while (!choice) {
        cout << "Select an option to \n- (b)uy something\n- (e)nd turn\n- (t)rade\n";
        cin >> choice;
        checkCin(&choice);
        switch (choice) {
            case 'b': case 'B': buyMenu(); choice = 0; break;
            case 'e': case 'E': return;
            case 't': case 'T': choice = 0; cout<<"Sorry, this functionality isn't currently implemented" <<endl; break;
            default: choice = 0; cout << "Invalid choice" << endl; break;
        }
    }

}

void Player::buyMenu() {

    char choice;
    Road road;
    Settlement settlement;
    City city;
    while (!choice) {
        cout << "Select an option to buy\n- (r)oad\n- (s)ettlement\n- (c)ity\n- (d)evelopment card";
        cout << endl << "Or press (b) to go back" << endl;
        cin >> choice;
        checkCin(&choice);
        switch (choice){
            case 'r': case 'R': road = Road();
                                road.buy();
                                break;
            case 's': case 'S': settlement = Settlement();
                                settlement.buy();
                                break;
            case 'c': case 'C': city = City();
                                city.buy();
                                break;
            case 'd': case 'D': buyDevCard();

            case 'b': case 'B': return;

            default: choice = 0; cout << "Invalid choice" << endl; break;
        }
    }
}

void Player::buyDevCard() {

}

bool Player::addVP(int pVP) {
    return true;
}

void Player::removeVP(int pVP) {
}

std::string Player::getName() const {
    return name;
}

bool Player::hasWon() {
    return false;
}
