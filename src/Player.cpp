//
// Created by tvito on 9/16/2025.
//

#include "Player.h"
#include <iostream>
#include <vector>
#include <string>

Player::Player(const std::string *pname) {
    name = *pname;
}

void Player::addResource(const Resource r) {
    resources[r.type] += r.num;
    collected.push_back(r);
}

bool Player::removeResource(const Resource r) {
    if (resources[r.type] >= r.num) {
        resources[r.type] -= r.num;
        return true;
    }
    return false;
}

bool Player::removeResource(const std::vector<Resource> &r) {
    bool canRemove = true;
    for (Resource resource : r) {
        if (resource.num >= resources[resource.type]) {
            canRemove = false;
        }
    }
    if (canRemove) {
        for (const auto resource : r) {
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

void Player::takeTurn(const std::vector<Player*>& players) {
    char choice = static_cast<char>(NULL);
    while (!choice) {
        std::cout << "Select an option to \n- (b)uy something\n- (e)nd turn\n- (t)rade\n";
        std::cin >> choice;
        checkCin(&choice);
        switch (choice) {
            case 'b': case 'B': buyMenu(); choice = 0; break;
            case 'e': case 'E': return;
            case 't': case 'T': choice = 0;
                if (initiateTrade(players)) {
                    std::cout << name + ": Trade Completed!" << std::endl;
                }
                else {
                    std::cout << name + ": Trade Failed!" << std::endl;
                }
                break;
            default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
        }
    }

}

void Player::showCollectedResources() {
    if (!collected.empty()) {
        for (auto r : collected) {
            std::cout << r << "\t";
        }
        std::cout << "!" << std::endl;
    }else {
        std::cout << "nothing!" <<std::endl;
    }
    collected.clear();
}

void Player::buyMenu() {

    char choice;
    while (!choice) {
        std::cout << "Select an option to buy\n- (r)oad\n- (s)ettlement\n- (c)ity\n- (d)evelopment card";
        std::cout << std::endl << "Or press (b) to go back" << std::endl;
        std::cin >> choice;
        checkCin(&choice);
        switch (choice){
            case 'r': case 'R':
                                //std::cout << (road.buy()?"Success":"Insufficient resources") << std::endl;
                                break;
            case 's': case 'S':
                                // std::cout << (settlement.buy()?"Success":"Insufficient resources") << std::endl;
                                break;
            case 'c': case 'C':
                                // std::cout << (city.buy()?"Success":"Insufficient resources") << std::endl;
                                break;
            case 'd': case 'D': buyDevCard();

            case 'b': case 'B': return;

            default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
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

    const std::string lhsName = lhs.getName();
    const std::string rhsName = rhs.getName();
    return lhsName == rhsName;

}

bool operator!=(const Player &lhs, const Player &rhs) {
    return !(lhs == rhs);
}

bool Player::trade(std::vector<Resource> get, std::vector<Resource> give) {
    char choice;
    std::cout << "\n" + name + ": Trade Offered! \nYou recieve: " << std::endl;
    for (Resource resourceGet : get) {
        std::cout << std::to_string(resourceGet.num) << " " << static_cast<resourceType>(resourceGet.type) << std::endl;
    }
    std::cout << "\nYou give: " << std::endl;
    for (Resource resourceGive : give) {
        std::cout << std::to_string(resourceGive.num) << " " << static_cast<resourceType>(resourceGive.type) << std::endl;
    }
    while (!choice) {
        std::cout << "Would you like to proceed? (y or n): ";
        std::cin >> choice;
        checkCin(&choice);
        switch (choice) {
            case 'y': case 'Y':
                if (removeResource(give)) {
                    std::cout << "Trade done!" << std::endl;
                }
                else {
                    std::cout << "Trade failed! You don't have enough resources!" << std::endl;
                    return false;
                }
                return true;
            case 'n': case 'N':
                std::cout << "Trade rejected!" << std::endl;
                return false;
            default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
        }
    }
}

bool Player::initiateTrade(std::vector<Player*> players) {
    std::vector<Resource> want;
    std::vector<Resource> offer;
    int numResource;

    char choice;
    while (!choice) {
        int numResources;
        std::cout << "Would you like to get (w)ood, (s)heep, (b)rick, s(t)one w(h)eat, (f)inish, or (q)uit: ";
        std::cin >> choice;
        checkCin(&choice);
        switch (choice) {
            case 'w': case 'W': choice = 0;
                std::cout << "How much wood do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(wood, numResource));
                break;
            case 's': case 'S': choice = 0;
                std::cout << "How many sheep do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(sheep, numResource));
                break;
            case 't': case 'T': choice = 0;
                std::cout << "How many stones do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(wood, numResource));
                break;
            case 'b': case 'B': choice = 0;
                std::cout << "How many bricks do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(wood, numResource));
                break;
            case 'h': case 'H': choice = 0;
                std::cout << "How much wheat do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(wheat, numResource));
                break;
            case 'f': case 'F': choice = 1; break;
            case 'q': case 'Q':
                return false;
            default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
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
                std::cout << "How much wood do you trade? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[wood]) {
                    std::cout << "You don't have enough wood for that trade!" << std::endl;
                    break;
                }
                offer.push_back(Resource(wood, numResource));
                break;
            case 's': case 'S': choice = 0;
                std::cout << "How many sheep do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[sheep]) {
                    std::cout << "You don't have enough wood for that trade!" << std::endl;
                    break;
                }
                offer.push_back(Resource(sheep, numResource));
                break;
            case 't': case 'T': choice = 0;
                std::cout << "How many stones do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[stone]) {
                    std::cout << "You don't have enough wood for that trade!" << std::endl;
                    break;
                }
                offer.push_back(Resource(stone, numResource));
                break;
            case 'b': case 'B': choice = 0;
                std::cout << "How many bricks do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[brick]) {
                    std::cout << "You don't have enough wood for that trade!" << std::endl;
                    break;
                }
                offer.push_back(Resource(brick, numResource));
                break;
            case 'h': case 'H': choice = 0;
                std::cout << "How much wheat do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[wheat]) {
                    std::cout << "You don't have enough wood for that trade!" << std::endl;
                    break;
                }
                offer.push_back(Resource(wheat, numResource));
                break;
            case 'f': case 'F': choice = 1; break;
            case 'q': case 'Q':
                return false;
            default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
        }
    }

    bool traded = false;
    for (Player* player : players) {
        if (player != this) {
            if (player->trade(offer, want)) {
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
