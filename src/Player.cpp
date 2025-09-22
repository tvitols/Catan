//
// Created by tvito on 9/16/2025.
//

#include "CustomUtils.h"

#include "Player.h"
#include <iostream>

#include "Road.h"
#include "Settlement.h"
#include "City.h"
#include "Board.h"

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

bool Player::removeResource(vector<Resource> r) {
    bool canRemove = true;
    for (Resource resource : r) {
        if (resource.num >= resources[resource.type]) {
            canRemove = false;
        }
    }
    if (canRemove) {
        for (Resource resource : r) {
            removeResource(resource);
        }
    }
    else {
        return false;
    }
    return true;
}

void Player::showResources() {
    for (int i = 0; i < 5; i++) {
        std::cout << static_cast<resourceType>(i) << "\t";
    }
    std::cout << std::endl;
    for (const auto r : resources) {
        std::cout << r << "\t";
    }
    std::cout << std::endl;
}

void Player::takeTurn(std::vector<Player> players, Board* board) {
    const int roll = dice() + dice();
    std::cout << "You rolled a " << roll << std::endl;
    std::cout << "Collecting Resources" << std::endl;
    std::cout << "You got " << std::endl;
    int collected = 0;
    board->collectResources(roll);
    // for (const auto b : buildings) {
    //     if (auto[r,num] = b->giveResources(roll); num) {
    //         cout << (collected?", and ":"") << num << " " << r;
    //         collected += num;
    //         addResource(r);
    //     }
    // }
    std::cout << (collected?"!":"nothing!") << std::endl;
    char choice;
    while (!choice) {
        std::cout << "Select an option to \n- (b)uy something\n- (e)nd turn\n- (t)rade\n";
        std::cin >> choice;
        checkCin(&choice);
        switch (choice) {
            case 'b': case 'B': buyMenu(); choice = 0; break;
            case 'e': case 'E': return;
            case 't': case 'T': choice = 0;
                if (initiateTrade(players)) {
                    cout << "Trade Completed!" << endl;
                }
                else {
                    cout << "Trade Failed!" << endl;
                }
                break;
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

bool Player::trade(vector<Resource> get, vector<Resource> give) {
    char choice;
    cout << "Trade Offered! \n You recieve: " << endl;
    for (Resource resourceGet : get) {
        cout << resourceGet.num + " " + resourceGet.type << endl;
    }
    cout << "\nYou give: " << endl;
    for (Resource resourceGive : give) {
        cout << resourceGive.num + " " + resourceGive.type << endl;
    }
    while (!choice) {
        cout << "Would you like to proceed? (y or n): ";
        cin >> choice;
        checkCin(&choice);
        switch (choice) {
            case 'y': case 'Y':
                if (removeResource(give)) {
                    cout << "Trade done!" << endl;
                }
                else {
                    cout << "Trade failed! You don't have enough resources!" << endl;
                    return false;
                }
                return true;
            case 'n': case 'N':
                cout << "Trade rejected!" << endl;
                return false;
            default: choice = 0; cout << "Invalid choice" << endl; break;
        }
    }
}

bool Player::initiateTrade(vector<Player> players) {
    vector<Resource> want;
    vector<Resource> offer;
    int numResource;
    for (int i = 0; i < 5; i++) {
        Resource resourceWant;
        cout<<"How many " << static_cast<resourceType>(i) << " do you want? Minimum: 0 (or q to quit) ";
        cin >> numResource;
        checkCin(&numResource);

        if (numResource == 'q' || numResource == 'Q') {
            return false;
        }

        while (numResource < 0 ) {
            cout << "Invalid number of  " << static_cast<resourceType>(i) << "please enter value >= 0: ";
            cin >> numResource;
            checkCin(&numResource);
        }
        want.push_back(Resource(static_cast<resourceType>(i), numResource));
    }
    for (int i = 0; i < 5; i++) {
        Resource resourceOffer;
        cout << "How many " << static_cast<resourceType>(i) << " will you give? Minimum: 0 (or q to quit) " <<endl;
        cin >> numResource;
        checkCin(&numResource);

        if (numResource == 'q' || numResource == 'Q') {
            return false;
        }

        while (numResource < 0 || numResource > resources[static_cast<resourceType>(i)]){
            if (numResource < 0) {
                cout << "Invalid number of  " << static_cast<resourceType>(i) << "please enter value >= 0: ";
                cin >> numResource;
                checkCin(&numResource);
            }
            else {
                cout << "You dont have enough " << static_cast<resourceType>(i) << " to offer that! Please enter another value: ";
                cin >> numResource;
                checkCin(&numResource);
            }
        }
        offer.push_back(Resource(static_cast<resourceType>(i), numResource));
    }

    bool traded = false;
    for (Player player : players) {
        if (&player != this) {
            if (player.trade(offer, want)) {
                traded = true;
                break;
            }
        }
    }
    if (!traded) {
        return false;
    }
    removeResource(offer);
    for (Resource resource : want) {
        addResource(resource);
    }
    return true;

}
