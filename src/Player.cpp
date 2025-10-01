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
                    std::cout << "You don't have enough sheep for that trade!" << std::endl;
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
                    std::cout << "You don't have enough stone for that trade!" << std::endl;
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
                    std::cout << "You don't have enough brick for that trade!" << std::endl;
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
                    std::cout << "You don't have enough wheat for that trade!" << std::endl;
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

bool Player::rolledASeven() {
    int numberOfResources = 0;
    for (int num : resources) {
        numberOfResources += num;
    }
    if (numberOfResources <= 7) {
        return false;
    }
    return true;
}

//Should they be allowed to get rid of more Resources than they need to?
void Player::loseHalfOfCards() {
    int numberOfResources = 0;
    for (int num : resources) {
        numberOfResources += num;
    }
    std::cout << name << ": you have over 7 cards! \nYou need to get rid of " << std::to_string(numberOfResources / 2) << " them" << std::endl;
    std::cout << "You have: " << std::endl;
    showResources();
    int gottenRidOf = 0;
    std::vector<Resource> removed;
    char choice;
    while (gottenRidOf < numberOfResources/2) {
        int numResource = 0;
        std::cout << "Would you like to get rid of (w)ood, (s)heep, (b)rick, s(t)one w(h)eat: ";
        std::cin >> choice;
        checkCin(&choice);
        switch (choice) {
            case 'w': case 'W':
                std::cout << "How much wood would you like to get rid of? ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[wood]) {
                    std::cout << "You don't have enough wood!" << std::endl;
                    break;
                }
                gottenRidOf += numResource;
                removed.push_back(Resource(wood, numResource));
                break;
            case 's': case 'S':
                std::cout << "How many sheep would you like to get rid of? ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[sheep]) {
                    std::cout << "You don't have enough sheep!" << std::endl;
                    break;
                }
                gottenRidOf += numResource;
                removed.push_back(Resource(sheep, numResource));
                break;
            case 't': case 'T': choice = 0;
                std::cout << "How many stones do you want to get rid of? ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[stone]) {
                    std::cout << "You don't have enough stone!" << std::endl;
                    break;
                }
                gottenRidOf += numResource;
                removed.push_back(Resource(stone, numResource));
                break;
            case 'b': case 'B': choice = 0;
                std::cout << "How many bricks do you want to get rid of? ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[brick]) {
                    std::cout << "You don't have enough brick!" << std::endl;
                    break;
                }
                gottenRidOf += numResource;
                removed.push_back(Resource(brick, numResource));
                break;
            case 'h': case 'H': choice = 0;
                std::cout << "How much wheat do you want to get rid of? ";
                numResource = getIntFromUser();
                while (numResource == -1) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[wheat]) {
                    std::cout << "You don't have enough wheat!" << std::endl;
                    break;
                }
                gottenRidOf += numResource;
                removed.push_back(Resource(wheat, numResource));
                break;
            default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
        }
        if (removeResource(removed) && gottenRidOf >= numberOfResources / 2) {
            std::cout << "The robber has taken half of your cards!" << std::endl;
        }
        else if (gottenRidOf >= numberOfResources) {
            std::cout << "Something went wrong with the robber stealing your cards! Let's try again!" << std::endl;
            gottenRidOf = 0;
        }
        removed.clear();
    }
}

std::string Player::moveRobber(std::vector<std::tuple<std::string, std::vector<int>>> stuffToSteal) {
    //Do the shit with actually moving the robber
    int choice;
    resourceType gained;
    if (!stuffToSteal.empty()) {
        bool canStealFrom = false;
        while (!canStealFrom) {
            std::cout << "Who would you like to steal from?" << std::endl;
            for (int i = 0; i < stuffToSteal.size(); i++) {
                std::cout << "(" << std::to_string(i+1) << ") " << get<0>(stuffToSteal[i]) << std::endl;
            }
            choice = getIntFromUser();
            //Validates that the input is a valid choice
            while (choice == -1 || choice > stuffToSteal.size()) {
                std::cout << "Invalid input. Please enter a number > 0 and < " << std::to_string(stuffToSteal.size()) << ": " << std::endl;
                choice = getIntFromUser();
            }
            //Steals from the player if they have resources
            int numberOfResources = 0;
            for (int resource : get<1>(stuffToSteal[choice-1])) {
                numberOfResources += resource;
            }
            if (numberOfResources > 0) {
                canStealFrom = true;
                return get<0>(stuffToSteal[choice-1]);
            }
            else {
                std::cout << "They don't have any resources to steal!" << std::endl;
            }
        }
    }
    else {
        std::cout << "There's no one on that tile!" << std::endl;
    }
    return "";
}

std::vector<int> Player::getResources() {
    return resources;
}

std::string Player::getName() {
    return name;
}

