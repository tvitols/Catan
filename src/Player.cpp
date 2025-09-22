//
// Created by tvito on 9/16/2025.
//

#include "CustomUtils.h"

#include "Player.h"
#include <iostream>

#include "City.h"
#include "Settlement.h"

Player::Player(const std::string *pname) {
    name = *pname;
}

void Player::addResource(Resource r) {
    resources[r.type] += r.num;
}

bool Player::removeResource(Resource r) {
    if (resources[r.type] >= r.num) {
        resources[r.type] -= r.num;
        return true;
    }
    return false;
}

void Player::showResources() {
    for (int i = 0; i < 5; i++) {
        cout << static_cast<resourceType>(i) << "\t";
    }
    cout << endl;
    for (const auto r : resources) {
        cout << r << "\t";
    }
    cout << endl;
}

void Player::takeTurn() {
    const int roll = dice() + dice();
    cout << "You rolled a " << roll << endl;
    cout << "Collecting Resources" << endl;
    cout << "You got " << endl;
    int collected = 0;
    for (const auto b : buildings) {
        if (auto[r,num] = b->giveResources(roll); num) {
            cout << (collected?", and ":"") << num << " " << r;
            collected += num;
            addResource(r);
        }
    }
    cout << (collected?"!":"nothing!") << endl;
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
                                cout << (road.buy()?"Success":"Insufficient resources") << endl;
                                break;
            case 's': case 'S': settlement = Settlement();
                                cout << (settlement.buy()?"Success":"Insufficient resources") << endl;
                                break;
            case 'c': case 'C': city = City();
                                cout << (city.buy()?"Success":"Insufficient resources") << endl;
                                break;
            case 'd': case 'D': buyDevCard();

            case 'b': case 'B': return;

            default: choice = 0; cout << "Invalid choice" << endl; break;
        }
    }
}

void Player::buyDevCard() {
}

//returns true if that puts the player over 10
bool Player::addVP(int pVP) {
    pVP += pVP;
    return hasWon();
}

void Player::removeVP(int pVP) {
    vp -= pVP;
}

std::string Player::getName() const {
    return name;
}

bool Player::hasWon() {
    return vp>=10;
}

bool operator==(const Player &lhs, const Player &rhs) {
   return rhs.getName() == lhs.getName();
}

bool operator!=(const Player &lhs, const Player &rhs) {
    return !(lhs == rhs);
}
