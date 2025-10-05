//
// Created by tvito on 9/16/2025.
//

#include "Player.h"

#include <functional>
#include <iostream>
#include <vector>
#include <string>

Player::Player(const std::string *pname, playerColor pColor) {
    name = *pname;
    color = pColor;
    allowedTrades.push_back(Trade(Resource(null, 4), Resource(null, 1)));
}

void Player::addResource(const Resource r) {
    resources[r.type] += r.num;
    collected.push_back(r);
}

void Player::addResource(const std::vector<Resource> &r) {
    for (const Resource r : r) {
        resources[r.type] += r.num;
    }
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

bool Player::checkLargestArmy(const std::vector<Player *> &vector) {
    if (army < 3) {
        return false;
    }
    Player *max = nullptr;
    for (auto player : vector) {
        if (player != this) {
            if (player->hasLargestArmy()) {
                max = player;
            }
            if (player->getArmy() > army) {
                return false;
            }

        }
    }
    if (max != nullptr) {
        max->removeVP(2);
    }
    largestArmy = true;
    addVP(2);
    return true;
}

bool Player::hasLargestArmy() const {
    return largestArmy;
}

int Player::takeTurn(const std::vector<Player*>& players, int action, Deck* &deck) {
    int choice = 0;
    switch (action) {
        case 200:
            devCards.makeActive();
            break;
        case -1:
            std::cout << "Invalid Placement for a settlement. Resources have been refunded." << std::endl;
            while (!choice) {
                std::cout << "Would you like to try again?\n1. yes\n2. no\n>>> ";
                choice = getIntFromUser();
                switch (choice) {
                    case 1: return 1;
                    case 2:
                        addResource({{wood,1},{brick,1},{wheat,1},{sheep,1}});
                        break;
                    default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
                }

            }
            break;
        case -2:
            std::cout << "Unable to upgrade that to a city. Resources have been refunded." << std::endl;
            while (!choice) {
                std::cout << "Would you like to try again?\n1. yes\n2. no\n>>> ";
                choice = getIntFromUser();
                switch (choice) {
                    case 1: return 2;
                    case 2:
                        addResource({{wheat,3},{stone,2}});
                        break;
                    default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
                }
            }
            break;
        case -3:
            std::cout << "Invalid placement for a road. Resources have been refunded." << std::endl;
            while (!choice) {
                std::cout << "Would you like to try again?\n1. yes\n2. no\n>>> ";
                choice = getIntFromUser();
                switch (choice) {
                    case 1: return 3;
                    case 2:
                        addResource({{wood,1},{brick,1}});
                        break;

                    default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
                }
            }
            break;
        case 4:
            if (!largestArmy && checkLargestArmy(players)) {
                std::cout << "Congratulations! You have the largest army!" << std::endl;
            }
            break;
        default: break;
    }


    while (true) {
        std::cout << "Select an option to \n1. Show Resources\n2. Buy something\n3. Trade\n4. Play a dev card\n5. Show board\n6. Display stats\n7. End turn\n>>> ";
        choice = getIntFromUser();
        switch (choice) {
            case 1:
                std::cout << "You have: " << std::endl;
                showResources();
                break;
            case 2: {
                const int result = buyMenu();
                if (result > 0 && result < 4) {
                    return result;
                }
                if (result == 4) {
                    std::cout << devCards.draw(deck) << std::endl;
                }
                break;
            }
            case 3:
                choice = 0;
                while (!choice) {
                    std::cout << "Who would you like to trade with?\n1. The Bank/Ports\n2. Other Players";
                    choice = getIntFromUser();
                    switch (choice) {
                    case 1:
                    case 2:
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
                break;
            case 4:
                if (devCards.isEmpty()) {
                    std::cout << "You don't have any dev cards, you can buy some from the buy menu!" << std::endl;
                    break;
                }
                switch (devCards.play(&resources,&vp)) {
                case 1: army += 1; return 4;
                case 2: return 5;
                case 3: monopoly(players); break;
                default: break;
                }
                break;

            case 5:
                    return 6;

            case 6:
                for (const auto player : players) {
                    std::cout << player->name << ": "  << player->getVP() << " VP" << (player->hasLargestArmy()?"Largest Army: "+std::to_string(player->getArmy()):"") << std::endl;
                }
                break;

            case 7: return 0;
            default: std::cout << "Invalid choice" << std::endl; break;
        }
    }
}

void Player::showCollectedResources() {
    if (!collected.empty()) {
        auto iter = collected.begin();
        while (iter != collected.end()) {
            std::cout << to_string(*iter) << ((iter+1)!=collected.end()?" and ":"");
            ++iter;
        }
        std::cout << "!" << std::endl;
    }else {
        std::cout << "nothing!" <<std::endl;
    }
    collected.clear();
}

int Player::buyMenu() {
    //1 = road, -1 = road failure
    //2 = settlement, -2 = settlement failure
    //3 = city, -3 = city failure
    //4 = development card, -4 = dev card failure
    //5 = back


    char choice;
    while (!choice) {
        std::cout << "Select an option to buy\n- road\n- settlement\n- city\n- development card";
        std::cout << std::endl << "Or press b to go back" << std::endl;
        std::cin >> choice;
        checkCin(&choice);
        switch (choice){
            case 'r': case 'R':
                                //std::cout << (road.buy()?"Success":"Insufficient resources") << std::endl;
                if (resources[brick] < 1 || resources[wood] < 1) {
                    std::cout << "Insufficient resources!" << std::endl;
                    return -1;
                }

                removeResource(Resource(wood, 1));
                removeResource(Resource(brick, 1));
                return 1;
                                break;
            case 's': case 'S':
                                // std::cout << (settlement.buy()?"Success":"Insufficient resources") << std::endl;
                if (resources[sheep] < 1 || resources[wheat] < 1 || resources[wood] < 1 || resources[brick] < 1) {
                    std::cout << "Insufficient resources!" << std::endl;
                    return -2;
                }

                removeResource(Resource(wood, 1));
                removeResource(Resource(brick, 1));
                removeResource(Resource(wheat, 1));
                removeResource(Resource(sheep, 1));
                return 2;
                                break;
            case 'c': case 'C':
                if (resources[stone] < 2 || resources[wheat] < 3) {
                    std::cout << "Insufficient resources!" << std::endl;
                    return -3;
                }

                removeResource(Resource(stone, 3));
                removeResource(Resource(wheat, 2));
                return 3;
                                // std::cout << (city.buy()?"Success":"Insufficient resources") << std::endl;
                                break;
            case 'd': case 'D':
                if (resources[wheat] < 1 || resources[stone] < 1 || resources[sheep] < 1) {
                    std::cout << "Insufficient resources!" << std::endl;
                    return -4;
                }

                removeResource(Resource(sheep, 1));
                removeResource(Resource(stone, 1));
                removeResource(Resource(wheat, 1));
                return 4;

            case 'b': case 'B': return 5;

            default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
        }
    }
}


void Player::monopoly(const std::vector<Player*>& players) {
    int choice;
    std::cout << "Select an option from the list below" << std::endl;
    std::cout << "1. Wood" << std::endl;
    std::cout << "2. Stone" << std::endl;
    std::cout << "3. Brick" << std::endl;
    std::cout << "4. Sheep" << std::endl;
    std::cout << "5. Wheat" << std::endl;
    choice = getIntFromUser();
    while (choice == -1 || choice == 0 || choice > 5) {
        std::cout << "Invalid input. Please enter a number between 1 and 5: ";
        choice = getIntFromUser();
    }
    std::vector<Resource> resourcesStolen;
    int totalResource = 0;
    switch (choice) {
        case 1:
            int numberOfWood;
            for (Player* player : players) {
                numberOfWood = (player->getResources())[wood];
                totalResource += numberOfWood;
                resourcesStolen.push_back(Resource(wood, numberOfWood));
                player->removeResource(Resource(wood, numberOfWood));
            }
            addResource(resourcesStolen);
            std::cout << "You stole " << std::to_string(totalResource) << " wood." << std::endl;
            break;
        case 2:
            int numberOfStone;
            for (Player* player : players) {
                numberOfStone = (player->getResources())[stone];
                totalResource += numberOfStone;
                resourcesStolen.push_back(Resource(stone, numberOfStone));
                player->removeResource(Resource(stone, numberOfStone));
            }
            addResource(resourcesStolen);
            std::cout << "You stole " << std::to_string(totalResource) << " stone." << std::endl;
            break;
        case 3:
            int numberOfBrick;
            for (Player* player : players) {
                numberOfBrick = (player->getResources())[brick];
                totalResource += numberOfBrick;
                resourcesStolen.push_back(Resource(brick, numberOfBrick));
                player->removeResource(Resource(brick, numberOfBrick));
            }
            addResource(resourcesStolen);
            std::cout << "You stole " << std::to_string(totalResource) << " brick." << std::endl;
            break;
        case 4:
            int numberOfSheep;
            for (Player* player : players) {
                numberOfSheep = (player->getResources())[sheep];
                totalResource += numberOfSheep;
                resourcesStolen.push_back(Resource(sheep, numberOfSheep));
                player->removeResource(Resource(sheep, numberOfSheep));
            }
            addResource(resourcesStolen);
            std::cout << "You stole " << std::to_string(totalResource) << " sheep." << std::endl;
            break;
        case 5:
            std::cout << "How much wheat do you want: ";
            int numberOfWheat;
            for (Player* player : players) {
                numberOfWheat = player->getResources()[wheat];
                totalResource += numberOfWheat;
                resourcesStolen.push_back(Resource(wheat, numberOfWheat));
                player->removeResource(Resource(wheat, numberOfWheat));
            }
            addResource(resourcesStolen);
            std::cout << "You stole " << std::to_string(totalResource) << " wheat." << std::endl;
            break;
    }

}

//returns true if that puts the player over 10
bool Player::addVP(int pVP) {
    vp += pVP;
    return hasWon();
}

int Player::getVP() const {
    return vp;
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

void Player::addTrade(const Trade &t) {
    if (std::count(allowedTrades.begin(),allowedTrades.end(),t) != null) {
        allowedTrades.push_back(t);
    }
}

bool Player::trade(std::vector<Resource> get, std::vector<Resource> give) {
    char choice = static_cast<char>(NULL);
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
    int choice = 0;

    while (!choice) {
        std::cout << "What would you like to offer? (Select finish when done or quit to go back)\n1. wood\n2. sheep\n3. brick\n4. stone\n5. wheat\n6. finish\n. quit\n>>> ";
        choice = getIntFromUser();
        switch (choice) {
            case wood+1: choice = 0;
                std::cout << "How much wood do you want to trade? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[wood]) {
                    std::cout << "You don't have enough wood for that trade!" << std::endl;
                    break;
                }
                offer.push_back(Resource(wood, numResource));
                break;
            case sheep+1: choice = 0;
                std::cout << "How many sheep do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[sheep]) {
                    std::cout << "You don't have enough sheep for that trade!" << std::endl;
                    break;
                }
                offer.push_back(Resource(sheep, numResource));
                break;
            case stone+1: choice = 0;
                std::cout << "How many stones do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[stone]) {
                    std::cout << "You don't have enough stone for that trade!" << std::endl;
                    break;
                }
                offer.push_back(Resource(stone, numResource));
                break;
            case brick+1: choice = 0;
                std::cout << "How many bricks do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[brick]) {
                    std::cout << "You don't have enough brick for that trade!" << std::endl;
                    break;
                }
                offer.push_back(Resource(brick, numResource));
                break;
            case wheat+1: choice = 0;
                std::cout << "How much wheat do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                if (numResource > resources[wheat]) {
                    std::cout << "You don't have enough wheat for that trade!" << std::endl;
                    break;
                }
                offer.push_back(Resource(wheat, numResource));
                break;
            case 6: choice = 1; break;
            case 7:
                return false;
            default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
        }
    }

    choice = 0;
    while (!choice) {
        std::cout << "What would you like to get? (Select finish when done or quit to go back)\n1. wood\n2. sheep\n3. brick\n4. stone\n5. wheat\n6. finish\n. quit\n>>> ";
        choice = getIntFromUser();
        switch (choice) {
            case wood+1: choice = 0;
                std::cout << "How much wood do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(wood, numResource));
                break;
            case sheep+1: choice = 0;
                std::cout << "How many sheep do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(sheep, numResource));
                break;
            case brick+1: choice = 0;
                std::cout << "How many bricks do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(brick, numResource));
                break;
            case stone+1: choice = 0;
                std::cout << "How many stones do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(stone, numResource));
                break;
            case wheat+1: choice = 0;
                std::cout << "How much wheat do you want? Minimum 0: ";
                numResource = getIntFromUser();
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(wheat, numResource));
                break;
            case 6: choice = 6; break;
            case 7:
                return false;
            default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
        }
    }

    bool traded = false;
    for (Player* player : players) {
        if (player != this && player->trade(offer, want)) {
            traded = true;
            break;
        }
    }
    if (!traded) {
        return false;
    }
    removeResource(offer);
    for (const Resource resource : want) {
        addResource(resource);
    }
    return true;
}

bool Player::tradeBank() {
    int choice = 0;
    auto trade = allowedTrades.begin();
    while (choice < 1 || choice > allowedTrades.size()) {

        std::cout << "Please select an option from the list below: " << std::endl;
        for (int i = 1; i <= allowedTrades.size(); i++) {
            std::cout << i << ". " << to_string(trade->give) << " for " << to_string(trade->receive) << std::endl;
            ++trade;
        }
        std::cout << allowedTrades.size()+1 << ". cancel\n>>> ";
        choice = getIntFromUser();
        trade = allowedTrades.begin();
    }
    if (choice == allowedTrades.size()+1) {
        return false;
    }
    trade += choice;
    choice = 0;
    while (!choice) {
        if (trade->give.num > 2) {
            std::cout << "What would you like to trade?\n1. wood\n2. sheep\n3. brick\n4. stone\n5. wheat\n6. quit: ";
            choice = getIntFromUser();
        }else {
            choice = trade->give.type + 1;
        }

        switch (choice) {
            case wood+1:
                if (!removeResource(Resource(wood, trade->give.num))) {
                    std::cout << "Insufficient resources!" << std::endl;
                    choice = 0;
                }
                break;
            case sheep+1:
                if (!removeResource(Resource(sheep, trade->give.num))) {
                    std::cout << "Insufficient resources!" << std::endl;
                    choice = 0;
                }
                break;
            case brick+1:
                if (!removeResource(Resource(brick, trade->give.num))) {
                    std::cout << "Insufficient resources!" << std::endl;
                    choice = 0;
                }
                break;
            case stone+1:
                if (!removeResource(Resource(stone, trade->give.num))) {
                    std::cout << "Insufficient resources!" << std::endl;
                    choice = 0;
                }
                break;
            case wheat+1:
                if (!removeResource(Resource(wheat, trade->give.num))) {
                    std::cout << "Insufficient resources!" << std::endl;
                    choice = 0;
                }
                break;
            case 6: return false;
            default: choice = 0; std::cout << "Invalid choice" << std::endl;
                break;
        }
    }

    choice = 0;
    while (!choice) {
        std::cout << "What would you like to receive?\n1. wood\n2. sheep\n3. brick\n4. stone\5. wheat\n>>> ";
        choice = getIntFromUser();
        switch (choice) {
            case wood+1:
                addResource(Resource(wood, 1));
                break;
            case sheep+1:
                addResource(Resource(sheep, 1));
                break;
            case brick+1:
                addResource(Resource(brick, 1));
                break;
            case stone+1:
                addResource(Resource(stone, 1));
                break;
            case wheat+1:
                addResource(Resource(wheat, 1));
                break;
            default: choice = 0; std::cout << "Invalid choice" << std::endl;
                break;
        }
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
        std::cout << "Would you like to get rid of wood, sheep, brick, stone wheat: ";
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
    //Do the **** with actually moving the robber
    int choice = static_cast<int>(NULL);
    resourceType gained;
    if (!stuffToSteal.empty()) {
        bool canStealFrom = false;
        while (!canStealFrom) {
            std::cout << "Who would you like to steal from?" << std::endl;
            for (int i = 0; i < stuffToSteal.size(); i++) {
                std::cout << "(" << std::to_string(i+1) << ") " << get<0>(stuffToSteal[i]) << std::endl;
            }
            std::cout << "(" << std::to_string(stuffToSteal.size()+1) << ")  quit" << std::endl;

            choice = getIntFromUser();
            //Validates that the input is a valid choice
            while (choice < 0 || choice > stuffToSteal.size()+1) {
                std::cout << "Invalid input. Please enter a number > 0 and < " << std::to_string(stuffToSteal.size()+2) << ": " << std::endl;
                choice = getIntFromUser();
            }
            if (choice == stuffToSteal.size()+1) {
                return "";
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

std::string Player::getColor() const {
    switch (color) {
        case blue: return "b";
        case green: return "g";
        case red: return "r";
        case white: return "w";
        default: return "";
    }
}

int Player::getArmy() const {
    return army;
}

