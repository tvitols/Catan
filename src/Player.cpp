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
                    std::cout << name + ": Trade Completed!" << endl;
                }
                else {
                    std::cout << name + ": Trade Failed!" << endl;
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
    cout << "\n" + name + ": Trade Offered! \nYou recieve: " << endl;
    for (Resource resourceGet : get) {
        cout << to_string(resourceGet.num) << " " << static_cast<resourceType>(resourceGet.type) << endl;
    }
    cout << "\nYou give: " << endl;
    for (Resource resourceGive : give) {
        cout << to_string(resourceGive.num) << " " << static_cast<resourceType>(resourceGive.type) << endl;
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

    char choice;
    while (!choice) {
        int numResources;
        std::cout << "Would you like to get (w)ood, (s)heep, (b)rick, s(t)one w(h)eat, (f)inish, or (q)uit: ";
        std::cin >> choice;
        checkCin(&choice);
        switch (choice) {
            case 'w': case 'W': choice = 0;
                cout << "How much wood do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(wood, numResource));
                break;
            case 's': case 'S': choice = 0;
                cout << "How many sheep do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(sheep, numResource));
                break;
            case 't': case 'T': choice = 0;
                cout << "How many stones do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(wood, numResource));
                break;
            case 'b': case 'B': choice = 0;
                cout << "How many bricks do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(wood, numResource));
                break;
            case 'h': case 'H': choice = 0;
                cout << "How much wheat do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(wheat, numResource));
                break;
            case 'f': case 'F': choice = 1; break;
            case 'q': case 'Q':
                return false;
            default: choice = 0; cout << "Invalid choice" << endl; break;
        }
    }

    choice = 0;
    while (!choice) {
        int numResources;
        std::cout << "Would you like to get (w)ood, (s)heep, (b)rick, s(t)one w(h)eat, (f)inish, or (q)uit: ";
        std::cin >> choice;
        checkCin(&choice);
        switch (choice) {
            case 'w': case 'W': choice = 0;
                cout << "How much wood do you trade? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[wood]) {
                    cout << "You don't have enough wood for that trade!" << endl;
                    break;
                }
                offer.push_back(Resource(wood, numResource));
                break;
            case 's': case 'S': choice = 0;
                cout << "How many sheep do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[sheep]) {
                    cout << "You don't have enough wood for that trade!" << endl;
                    break;
                }
                offer.push_back(Resource(sheep, numResource));
                break;
            case 't': case 'T': choice = 0;
                cout << "How many stones do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[stone]) {
                    cout << "You don't have enough wood for that trade!" << endl;
                    break;
                }
                offer.push_back(Resource(stone, numResource));
                break;
            case 'b': case 'B': choice = 0;
                cout << "How many bricks do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[brick]) {
                    cout << "You don't have enough wood for that trade!" << endl;
                    break;
                }
                offer.push_back(Resource(brick, numResource));
                break;
            case 'h': case 'H': choice = 0;
                cout << "How much wheat do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[wheat]) {
                    cout << "You don't have enough wood for that trade!" << endl;
                    break;
                }
                offer.push_back(Resource(wheat, numResource));
                break;
            case 'f': case 'F': choice = 1; break;
            case 'q': case 'Q':
                return false;
            default: choice = 0; cout << "Invalid choice" << endl; break;
        }
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
