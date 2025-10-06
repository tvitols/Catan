//
// Created by tvito on 9/16/2025.
//

#include "Player.h"

#include <functional>
#include <iostream>
#include <vector>
#include <string>

#define WINNING_VP 5

Player::Player(const std::string *pname, playerColor pColor) {
    name = *pname;
    color = pColor;
    //automatically can do a 4:1 trade
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
    //Validates that user has enough Resources to remove
    for (Resource resource : r) {
        if (resource.num > resources[resource.type]) {
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
    //printing out number of each resource the user has
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
    //army needs to be greater than 3 to count
    if (army < 3) {
        return false;
    }
    Player *max = nullptr;
    //Checks if user has a larger army than other players
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
    //decrements other player vp by 2 as they just lost Largest Army
    if (max != nullptr) {
        max->removeVP(2);
    }
    largestArmy = true;
    //Largest Army gets you 2 VP
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
            //all devCards that were purchased in the previous turn are now active
            devCards.makeActive();
            break;
        case -1:
            //Invalid placement of settlement
            std::cout << "Invalid Placement for a settlement. Resources have been refunded." << std::endl << std::endl;
            while (!choice) {
                std::cout << "Would you like to try again?\n1. yes\n2. no\n>>> ";
                //Validating input
                choice = getIntFromUser();
                switch (choice) {
                    //Trying to place a settlement again
                    case 1: return 1;
                    case 2:
                        //refunding the resource
                        addResource({{wood,1},{brick,1},{wheat,1},{sheep,1}});
                        break;
                    default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
                }

            }
            break;
        case -2:
            //Invalid city placement
            std::cout << "Unable to upgrade that to a city. Resources have been refunded." << std::endl;
            while (!choice) {
                std::cout << "Would you like to try again?\n1. yes\n2. no\n>>> ";
                //Validating input
                choice = getIntFromUser();
                switch (choice) {
                    //Trying to place a city again
                    case 1: return 2;
                    case 2:
                        //refunding the resources
                        addResource({{wheat,3},{stone,2}});
                        break;
                    default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
                }
            }
            break;
        case -3:
            //Invalid road placement
            std::cout << "Invalid placement for a road. Resources have been refunded." << std::endl;
            while (!choice) {
                std::cout << "Would you like to try again?\n1. yes\n2. no\n>>> ";
                //Validating input
                choice = getIntFromUser();
                switch (choice) {
                    //Trying to place another road
                    case 1: return 3;
                    case 2:
                        //Refunding resources
                        addResource({{wood,1},{brick,1}});
                        break;

                    default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
                }
            }
            break;
        case 4:
            //purchased a KnightCard which adds to Army
            if (!largestArmy && checkLargestArmy(players)) {
                std::cout << "Congratulations! You have the largest army!" << std::endl;
            }
            break;
        default: break;
    }


    while (true) {
        std::cout << std::endl << std::endl << "Select an option to \n1. Show Resources\n2. Buy something\n3. Trade\n4. Play a dev card\n5. Show board\n6. Display stats\n7. End turn\n>>> ";
        choice = getIntFromUser();
        switch (choice) {
            case 1: {
                //Printing resources
                std::cout << "You have: " << std::endl;
                showResources();
                break;
}
            case 2: {
                const int result = buyMenu();
                //Returning number associated with each type of Structure
                if (result > 0 && result < 4) {
                    return result;
                }
                //Buying a DevCard
                if (result == 4) {
                    std::cout << devCards.draw(deck) << std::endl;
                }
                break;
            }
            case 3:
                choice = 0;
                while (!choice) {
                    //Trading
                    std::cout << "Who would you like to trade with?\n1. The Bank/Ports\n2. Other Players";
                    //Validating input
                    choice = getIntFromUser();
                    switch (choice) {
                    case 1:
                            //Trading with the Bank and returning whether that Trade was completed
                            if (tradeBank()) {
                                std::cout << name + ": Trade Completed!" << std::endl << std::endl;
                            }
                            else {
                                std::cout << name + ": Trade Failed!" << std::endl << std::endl;
                            }
                            break;
                    case 2:
                        //Trading with Players and returning whether that Trade was completed
                        if (initiateTrade(players)) {
                            std::cout << name + ": Trade Completed!" << std::endl << std::endl;
                        }
                        else {
                            std::cout << name + ": Trade Failed!" << std::endl << std::endl;
                        }
                        break;
                    default: choice = 0; std::cout << "Invalid choice" << std::endl <<  std::endl; break;
                    }

                }
                break;
            case 4:
                //Playing DevCard
                if (devCards.isEmpty()) {
                    std::cout << "You don't have any dev cards, you can buy some from the buy menu!" << std::endl << std::endl;
                    break;
                }
                //Obtains key from devCards play() function
                switch (devCards.play(&resources,&vp)) {
                //Knight
                case 1: army += 1; return 4;
                //RoadBuilding
                case 2: return 5;
                //Monopoly
                case 3: monopoly(players); break;
                default: break;
                }
                break;

            case 5:
                //Shows Board
                    return 6;

            case 6: {
                //Prints the victory points of each player
                std::cout << std::endl;
                for (const auto player : players) {
                    std::cout << player->name << ": "  << player->getVP() << " VP" << (player->hasLargestArmy()?"Largest Army: "+std::to_string(player->getArmy()):"") << std::endl;
                }
                break;
}
            //Quits
            case 7: return 0;
            default: std::cout << "Invalid choice" << std::endl; break;
        }
    }
}

void Player::showCollectedResources() {
    //Prints the resources you collected on other people's turns
    if (!collected.empty()) {
        auto iter = collected.begin();
        //Iterates through vector and prints resourceType
        while (iter != collected.end()) {
            std::cout << to_string(*iter) << ((iter+1)!=collected.end()?" and ":"");
            ++iter;
        }
        std::cout << "!" << std::endl;
    }else {
        std::cout << "nothing!" <<std::endl;
    }
    //Clears collected
    collected.clear();
}

int Player::buyMenu() {
    int choice = 0;
    while (true) {
        std::cout <<std::endl << std::endl << "Select an option to buy\n1. road\n2. settlement\n3. city\n4. development card\n5. Go Back\n>>> ";
        choice = getIntFromUser();
        switch (choice){
            case 1:
                //Validates resources of road
                if (resources[brick] < 1 || resources[wood] < 1) {
                    std::cout << "Insufficient resources!" << std::endl << std::endl;
                    return -3;
                }
                //Removed resources
                removeResource(Resource(wood, 1));
                removeResource(Resource(brick, 1));
                return 3;
                                break;
            case 2:
                //Validates resources of settlement
                if (resources[sheep] < 1 || resources[wheat] < 1 || resources[wood] < 1 || resources[brick] < 1) {
                    std::cout << "Insufficient resources!" << std::endl << std::endl;
                    return -1;
                }
                //Removes resources
                removeResource(Resource(wood, 1));
                removeResource(Resource(brick, 1));
                removeResource(Resource(wheat, 1));
                removeResource(Resource(sheep, 1));
                return 1;

            case 3:
                //Validates resources of City
                if (resources[stone] < 2 || resources[wheat] < 3) {
                    std::cout << "Insufficient resources!" << std::endl << std::endl;
                    return -2;
                }
                //Removes resources
                removeResource(Resource(stone, 3));
                removeResource(Resource(wheat, 2));
                return 2;
                                break;
            case 4:
                //Validates resources of DevCard
                if (resources[wheat] < 1 || resources[stone] < 1 || resources[sheep] < 1) {
                    std::cout << "Insufficient resources!" << std::endl << std::endl;
                    return -4;
                }
                //Removes resources
                removeResource(Resource(sheep, 1));
                removeResource(Resource(stone, 1));
                removeResource(Resource(wheat, 1));
                return 4;

            case 5: return 5;

            default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
        }
    }
}


void Player::monopoly(const std::vector<Player*>& players) {
    int choice = 0;
    //Chooses resource to obtain
    std::cout << std::endl << std::endl;
    std::cout << "Select an option from the list below" << std::endl;
    std::cout << "1. Wood" << std::endl;
    std::cout << "2. Stone" << std::endl;
    std::cout << "3. Brick" << std::endl;
    std::cout << "4. Sheep" << std::endl;
    std::cout << "5. Wheat\n>>> ";
    choice = getIntFromUser();
    //Validates input
    while (choice == -1 || choice == 0 || choice > 5) {
        std::cout << "Invalid input. Please enter a number between 1 and 5: ";
        choice = getIntFromUser();
    }
    std::vector<Resource> resourcesStolen;
    int totalResource = 0;
    //Removes all of that resourceType from every other player
    //Adds number of resources stolen to user
    switch (choice) {
        case 1: {
            int numberOfWood = 0;
            for (Player* player : players) {
                numberOfWood = (player->getResources())[wood];
                totalResource += numberOfWood;
                resourcesStolen.push_back(Resource(wood, numberOfWood));
                player->removeResource(Resource(wood, numberOfWood));
            }
            addResource(resourcesStolen);
            std::cout << "You stole " << std::to_string(totalResource) << " wood." << std::endl << std::endl;
            break;
        }
        case 2: {
            int numberOfStone = 0;
            for (Player* player : players) {
                numberOfStone = (player->getResources())[stone];
                totalResource += numberOfStone;
                resourcesStolen.push_back(Resource(stone, numberOfStone));
                player->removeResource(Resource(stone, numberOfStone));
            }
            addResource(resourcesStolen);
            std::cout << "You stole " << std::to_string(totalResource) << " stone." << std::endl << std::endl;
            break;
        }
        case 3: {
            int numberOfBrick = 0;
            for (Player* player : players) {
                numberOfBrick = (player->getResources())[brick];
                totalResource += numberOfBrick;
                resourcesStolen.push_back(Resource(brick, numberOfBrick));
                player->removeResource(Resource(brick, numberOfBrick));
            }
            addResource(resourcesStolen);
            std::cout << "You stole " << std::to_string(totalResource) << " brick." << std::endl << std::endl;
            break;
        }
        case 4: {
            int numberOfSheep = 0;
            for (Player* player : players) {
                numberOfSheep = (player->getResources())[sheep];
                totalResource += numberOfSheep;
                resourcesStolen.push_back(Resource(sheep, numberOfSheep));
                player->removeResource(Resource(sheep, numberOfSheep));
            }
            addResource(resourcesStolen);
            std::cout << "You stole " << std::to_string(totalResource) << " sheep." << std::endl << std::endl;
            break;
        }
        case 5: {
            int numberOfWheat = 0;
            for (Player* player : players) {
                numberOfWheat = player->getResources()[wheat];
                totalResource += numberOfWheat;
                resourcesStolen.push_back(Resource(wheat, numberOfWheat));
                player->removeResource(Resource(wheat, numberOfWheat));
            }
            addResource(resourcesStolen);
            std::cout << "You stole " << std::to_string(totalResource) << " wheat." << std::endl << std::endl;
            break;
        }
    }

}

bool Player::addVP(int pVP) {
    vp += pVP;
    //returns true if that puts the player over 10
    if (hasWon()) {
        std::cout << "Congratulations! You have reached 10 VP, other players will now get one final turn once yuo end yours." << std::endl;
    }
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
    return vp>=WINNING_VP;
}

bool operator==(const Player &lhs, const Player &rhs) {
    //compares names
    const std::string lhsName = lhs.getName();
    const std::string rhsName = rhs.getName();
    return lhsName == rhsName;

}

bool operator!=(const Player &lhs, const Player &rhs) {
    return !(lhs == rhs);
}

void Player::addTrade(const Trade &t) {
    //Adds Trade given by Port to allowedTrades
    //Confirms that it is not a duplicate Trade
    if (std::count(allowedTrades.begin(),allowedTrades.end(),t) != null) {
        allowedTrades.push_back(t);
    }
}

bool Player::trade(const std::vector<Resource>& get, const std::vector<Resource> &give) {
    int choice = 0;
    std::cout << "\n" + name + ": Trade Offered! \nYou recieve: " << std::endl;
    //Resources offered to you
    for (Resource resourceGet : get) {
        std::cout << std::to_string(resourceGet.num) << " " << static_cast<resourceType>(resourceGet.type) << std::endl;
    }
    std::cout << std::endl;
    std::cout << "\nYou give: " << std::endl;
    //Resources would you be losing
    for (Resource resourceGive : give) {
        std::cout << std::to_string(resourceGive.num) << " " << static_cast<resourceType>(resourceGive.type) << std::endl;
    }
    std::cout << std::endl;
    while (!choice) {
        std::cout << "Would you like to proceed?\n1. yes\n2. no\n>>> ";
        choice = getIntFromUser();
        //Validating input
        switch (choice) {
            case 1:
                //Removing resources
                if (removeResource(give)) {
                    std::cout << "Trade done!" << std::endl << std::endl;
                }
                //Validating that you have enough resources for the Trade
                else {
                    std::cout << "Trade failed! You don't have enough resources!" << std::endl << std::endl;
                    return false;
                }
                //Adding the resources offered
                for (const Resource resource : get) {
                    addResource(resource);
                }
                return true;
            //Refusing Trade
            case 2:
                std::cout << "Trade rejected!" << std::endl << std::endl;
                return false;
            default: choice = 0; std::cout << "Invalid choice" << std::endl << std::endl; break;
        }
    }
    return false;
}

bool Player::initiateTrade(std::vector<Player*> players) {
    std::vector<Resource> want;
    std::vector<Resource> offer;
    int numResource;
    int choice = 0;

    std::vector<int> tradeNums = {0,0,0,0,0};

    while (!choice) {
        //Creating vector of Resources they would offer in the Trade
        std::cout << "What would you like to offer? (Select finish when done or quit to go back)\n1. wood\n2. sheep\n3. brick\n4. stone\n5. wheat\n6. finish\n7. quit\n>>> ";
        choice = getIntFromUser();
        switch (choice) {
            case 1: choice = 0;
                std::cout << "How much wood do you want to trade? Minimum 0: ";
                numResource = getIntFromUser();
                //Validating input
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                //Validating input
                if (tradeNums[wood] + numResource > resources[wood]) {
                    std::cout << "You don't have enough wood for that trade!" << std::endl;
                    break;
                }
                tradeNums[wood] += numResource;
                offer.push_back(Resource(wood, numResource));
                break;
            case 2: choice = 0;
                std::cout << "How many sheep do you want to trade? Minimum 0: ";
                numResource = getIntFromUser();
                //Validating input
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                //Validating input
                if (tradeNums[sheep] + numResource > resources[sheep]) {
                    std::cout << "You don't have enough sheep for that trade!" << std::endl;
                    break;
                }
                tradeNums[sheep] += numResource;
                offer.push_back(Resource(sheep, numResource));
                break;
            case 4: choice = 0;
                std::cout << "How many stones do you want to trade? Minimum 0: ";
                numResource = getIntFromUser();
                //Validating input
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                //Validating input
                if (tradeNums[stone] + numResource > resources[stone]) {
                    std::cout << "You don't have enough stone for that trade!" << std::endl;
                    break;
                }
                tradeNums[stone] += numResource;
                offer.push_back(Resource(stone, numResource));
                break;
            case 3: choice = 0;
                std::cout << "How many bricks do you want to trade? Minimum 0: ";
                numResource = getIntFromUser();
                //Validating input
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                //Validating input
                if (tradeNums[brick] + numResource > resources[brick]) {
                    std::cout << "You don't have enough brick for that trade!" << std::endl;
                    break;
                }
                tradeNums[brick] += numResource;
                offer.push_back(Resource(brick, numResource));
                break;
            case 5: choice = 0;
                std::cout << "How much wheat do you want to trade? Minimum 0: ";
                numResource = getIntFromUser();
                //Validating input
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                //Validating input
                if (tradeNums[wheat] + numResource > resources[wheat]) {
                    std::cout << "You don't have enough wheat for that trade!" << std::endl;
                    break;
                }
                tradeNums[wheat] += numResource;
                offer.push_back(Resource(wheat, numResource));
                break;
            case 6: choice = 1; break;
            case 7:
                return false;
            default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
        }
    }

    choice = 0;
    //Creating a vector of Resources you would like to recieve
    while (!choice) {
        std::cout << "What would you like to get? (Select finish when done or quit to go back)\n1. wood\n2. sheep\n3. brick\n4. stone\n5. wheat\n6. finish\n7. quit\n>>> ";
        choice = getIntFromUser();
        switch (choice) {
            case 1: choice = 0;
                std::cout << "How much wood do you want? Minimum 0: ";
                numResource = getIntFromUser();
                //Validating input
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(wood, numResource));
                break;
            case 2: choice = 0;
                std::cout << "How many sheep do you want? Minimum 0: ";
                numResource = getIntFromUser();
                //Validating input
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(sheep, numResource));
                break;
            case 3: choice = 0;
                std::cout << "How many bricks do you want? Minimum 0: ";
                numResource = getIntFromUser();
                //Validating input
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(brick, numResource));
                break;
            case 4: choice = 0;
                std::cout << "How many stones do you want? Minimum 0: ";
                numResource = getIntFromUser();
                //Validating input
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                want.push_back(Resource(stone, numResource));
                break;
            case 5: choice = 0;
                std::cout << "How much wheat do you want? Minimum 0: ";
                numResource = getIntFromUser();
                //Validating input
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
    //Offers the Trade to all other players
    for (Player* player : players) {
        if (player != this && player->trade(offer, want)) {
            traded = true;
            break;
        }
    }
    if (!traded) {
        return false;
    }
    //Removes resources offered
    removeResource(offer);
    addResource(want);
    return true;
}

bool Player::tradeBank() {
    int choice = 0;
    auto trade = allowedTrades.begin();
    while (choice < 1 || choice > allowedTrades.size() + 1) {
        //Printing out available Trades
        std::cout << "Please select an option from the list below: " << std::endl;
        for (int i = 1; i <= allowedTrades.size(); i++) {
            std::cout << i << ". " << to_string(trade->give) << " for " << to_string(trade->receive) << std::endl;
            ++trade;
        }
        std::cout << allowedTrades.size()+1 << ". cancel\n>>> ";
        choice = getIntFromUser();
        trade = allowedTrades.begin();
    }
    //Validating inout
    if (choice == allowedTrades.size()+1) {
        return false;
    }
    trade += choice-1;
    choice = 0;

    while (!choice) {
        //Trading with the Bank or 3:1 Port
        if (trade->give.num > 2) {
            std::cout << "What would you like to trade?\n1. wood\n2. sheep\n3. brick\n4. stone\n5. wheat\n6. quit: ";
            choice = getIntFromUser();
        }else { // Trading with a 2:1 port
            choice = trade->give.type + 1;
        }
        //Offering a type of Resource
        switch (choice) {
            case wood+1:
                //Validating input
                if (!removeResource(Resource(wood, trade->give.num))) {
                    std::cout << "Insufficient resources!" << std::endl;
                    if (trade->give.num == 2) return false;
                    choice = 0;
                }
                break;
            case sheep+1:
                //Validating input
                if (!removeResource(Resource(sheep, trade->give.num))) {
                    std::cout << "Insufficient resources!" << std::endl;
                    if (trade->give.num == 2) return false;
                    choice = 0;
                }
                break;
            case brick+1:
                //Validating input
                if (!removeResource(Resource(brick, trade->give.num))) {
                    std::cout << "Insufficient resources!" << std::endl;
                    if (trade->give.num == 2) return false;
                    choice = 0;
                }
                break;
            case stone+1:
                //Validating input
                if (!removeResource(Resource(stone, trade->give.num))) {
                    std::cout << "Insufficient resources!" << std::endl;
                    if (trade->give.num == 2) return false;
                    choice = 0;
                }
                break;
            case wheat+1:
                //Validating input
                if (!removeResource(Resource(wheat, trade->give.num))) {
                    std::cout << "Insufficient resources!" << std::endl;
                    if (trade->give.num == 2) return false;
                    choice = 0;
                }
                break;
            case 6: return false;
            default: choice = 0; std::cout << "Invalid choice" << std::endl;
                break;
        }
    }

    //Receive resources
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
    //Checking if you have 7 or more resources
    int numberOfResources = 0;
    for (int num : resources) {
        numberOfResources += num;
    }
    if (numberOfResources < 7) {
        return false;
    }
    return true;
}

void Player::loseHalfOfCards() {
    int numberOfResources = 0;
    for (int num : resources) {
        numberOfResources += num;
    }
    std::cout << name << ": you have over 7 cards! \nYou need to get rid of " << std::to_string(numberOfResources / 2) << " them" << std::endl;
    std::cout << "You have: " << std::endl;
    showResources();
    //Number of resources they have gottenRidOf
    int gottenRidOf = 0;
    int choice = -1;
    int numResource = 0;

    while (gottenRidOf < numberOfResources/2) {
        if (choice != -1) {
            std::cout << "You have gotten rid of " << std::to_string(gottenRidOf) << " resources. You still need to get rid of " << std::to_string((numberOfResources / 2)-gottenRidOf) << " more." << std::endl;
        }
        numResource = 0;
        std::cout << std::endl << "What would you like to get rid of?\n1. wood\n2. sheep\n3. brick\n4. stone\n5. wheat\n>>> ";
        choice = getIntFromUser();
        switch (choice) {
            case 1: choice = 0;
                std::cout << "How much wood would you like to get rid of? ";
                numResource = getIntFromUser();
                //Validating input
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                //Validating input
                if (!removeResource(Resource(wood, numResource))) {
                    std::cout << "You don't have enough wood!" << std::endl;
                    break;
                }
                //Adding number gotten rid of to gottenRidOf
                gottenRidOf += numResource;
                break;
            case 2: choice = 0;
                std::cout << "How many sheep would you like to get rid of? ";
                numResource = getIntFromUser();
                //Input validation
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                //Input validation
                if (!removeResource(Resource(sheep, numResource))) {
                    std::cout << "You don't have enough sheep!" << std::endl;
                    break;
                }
                //Increasing gottenRidOf
                gottenRidOf += numResource;
                break;
            case 4: choice = 0;
                std::cout << "How many stones do you want to get rid of? ";
                numResource = getIntFromUser();
                //Validating input
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                //Validating input
                if (!removeResource(Resource(stone, numResource))) {
                    std::cout << "You don't have enough stone!" << std::endl;
                    break;
                }
                //Increasing gottenRidOf
                gottenRidOf += numResource;
                break;
            case 3: choice = 0;
                std::cout << "How many bricks do you want to get rid of? ";
                numResource = getIntFromUser();
                //Validating input
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                //Validating input
                if (!removeResource(Resource(brick, numResource))) {
                    std::cout << "You don't have enough brick!" << std::endl;
                    break;
                }
                //Increasing gottenRidOf
                gottenRidOf += numResource;
                break;
            case 5: choice = 0;
                std::cout << "How much wheat do you want to get rid of? ";
                numResource = getIntFromUser();
                //Input validation
                while (numResource <= 0) {
                    std::cout << "Invalid input. Please enter a number > 0: ";
                    numResource = getIntFromUser();
                }
                //Input validation
                if (!removeResource(Resource(wheat, numResource))) {
                    std::cout << "You don't have enough wheat!" << std::endl;
                    break;
                }
                //Increasing gottenRidOf
                gottenRidOf += numResource;
                break;
            default: choice = 0; std::cout << "Invalid choice" << std::endl; break;
        }
    }
}

std::string Player::moveRobber(std::vector<std::tuple<std::string, std::vector<int>>> stuffToSteal) {
    resourceType gained;
    //Checking that there were players on that Tile
    if (!stuffToSteal.empty()) {
        int choice = 0;
        bool canStealFrom = false;
        //Prompting User to steal from a Player, or quit
        while (!canStealFrom) {
            std::cout << "Who would you like to steal from?" << std::endl;
            for (int i = 0; i < stuffToSteal.size(); i++) {
                std::cout << std::to_string(i+1) << "1. " << get<0>(stuffToSteal[i]) << std::endl;
            }
            std::cout << std::to_string(stuffToSteal.size()+1) << ". quit\n>>> ";

            choice = getIntFromUser();
            //Validates that the input is a valid choice
            while (choice <= 0 || choice > stuffToSteal.size()+1) {
                std::cout << "Invalid input. Please enter a number > 0 and < " << std::to_string(stuffToSteal.size()+2) << ": " << std::endl;
                choice = getIntFromUser();
            }
            if (choice == stuffToSteal.size()+1) {
                stuffToSteal.clear();
                return "";
            }
            //Steals from the player if they have resources
            int numberOfResources = 0;
            for (int resource : get<1>(stuffToSteal[choice-1])) {
                numberOfResources += resource;
            }
            if (numberOfResources > 0) {
                canStealFrom = true;
                auto ret = get<0>(stuffToSteal[choice-1]);
                stuffToSteal.clear();
                return ret;
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