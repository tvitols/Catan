//
// Created by tvito on 9/16/2025.
//

#ifndef PLAYER_H
#define PLAYER_H


#include <string>
#include <vector>

#include "Deck.h"
#include "CardStack.h"
#include "customUtils.h"

enum playerColor : int {red = 0, white = 1, blue = 2, green = 3};

inline std::ostream& operator<<(std::ostream& os, const playerColor& pC) {
    switch (pC) {
        case red:
            os << "Red";
            break;
        case white:
            os << "White";
            break;
        case blue:
            os << "Blue";
            break;
        case green:
            os << "Green";
            break;
        default:
            os << "UNKNOWN";
            break;
    }
    return os;
}

class Player {

    std::string name;
    int vp = 0;
                            //    w,s,b,s,wh
    std::vector<int> resources = {0,0,0,0,0};
    std::vector<Resource> collected = {};
    CardStack devCards;
    playerColor color;
    std::vector<Trade> allowedTrades;
    bool largestArmy = false;
    int army = 0;

    public:

    /**
     * constructor
     * @param pname name of player
     * @param pColor color of Structures
     */
    Player(const std::string *pname, playerColor pColor);

    /**
     * increments resource[r.type] by r.num
     * @param r Resource to add
     */
    void addResource(const Resource r);
    /**
     * calls addResource for every Resource in r
     * @param r vector of Resources
     */
    void addResource(const std::vector<Resource> &r);

    /**
     * validates that user has enough resources to remove
     * decrements resources[r.type] by r.number
     * @param r Resource to remove
     * @return true if player has enough resources to remove, false otherwise
     */
    bool removeResource(const Resource r);

    /**
     * validates that user has enough of each resource to remove
     * calls removeResource(r) on all Resources in vector
     * @param r vector of Resources to remove
     * @return true if player has enough resources to remove, false otherwise
     */
    bool removeResource(const std::vector<Resource> &r);

    /**
     * prints out all resources
     */
    void showResources();


    /**
     * validates if |KnightCards| > 3
     * compares number of KnightCards to all other players
     * if > a player who hasLargestArmy, sets that player's hasLargestArmy to false and remove 2 vp
     * @param vector vector of all Players in Game
     * @return true if they have the largest number of KnightCards and have more than three, false otherwise
     */
    bool checkLargestArmy(const std::vector<Player *> & vector);

    /**
     * @return hasLargestArmy
     */
    bool hasLargestArmy() const;

    /**
     * validates previous action done by Player
     * if a failed action, asks if they want to try again
     * prompts player for action
     * preforms action through switch statement
     * @param players vector of all Players in Game
     * @param action action already completed passed by Game
     * @param deck deck of Cards
     * @return
     */
    int takeTurn(const std::vector<Player*>& players, int action, Deck* &deck);

    /**
     *prints list of resources obtained in other players turns
     */
    void showCollectedResources();

    /**
     * displays options to buy things
     * prompts user to choose option
     * validates that user has enough resources to purchase object
     * removes those resources
     * @return number corresponding to purchase
     */
    int buyMenu();

    /**
     * plays the monopoly card
     * asks user to choose a type of Resource
     * steals all of that Resource from other players
     * @param players vector of all Players in the Game
     */
    void monopoly(const std::vector<Player*>& players);


    /**
     * adds pVP to vp
     * @param pVP number of victory points to add
     * @return hasWon()
     */
    bool addVP(int pVP);

    /**
     *
     * @return vp
     */
    int getVP() const;

    /**
     * removes pVP from vp
     * @param pVP number of victory points to remove
     */
    void removeVP(int pVP);

    /**
     *
     * @return name
     */
    std::string getName() const;

    /**
     *
     * @return if victory points is greater than 10
     */
    bool hasWon();

    friend bool operator==(const Player &lhs, const Player &rhs);
    friend bool operator!=(const Player &lhs, const Player &rhs);

    /**
     * checks to make sure the trade isn't a duplicate
     * adds Trade to allowedTrades
     * @param t Trade to add
     */
    void addTrade(const Trade &t);

    /**
     * offers a trade and asks if they accept
     * validates that user has enough resources
     * @param get vector of Resources to gain
     * @param give vector of Resources to
     * @return if accepted trade, false otherwise
     */
    bool trade(std::vector<Resource>get, std::vector<Resource>give);

    /**
     * Asks user to input how many Resources they want to offer and obtain
     * validates that user has enough Resources
     * calls trade(offer, obtain) on all other Players in players
     * adds Resources obtained if someone accepts the trade
     * @param players list of players in game
     * @return true if trade occurred, false otherwise
     */
    bool initiateTrade(std::vector<Player*> players);

    /**
     * prints all Trades a player contains and asks player to choose one
     * removes Resources given, adds Resources gained from trade
     * validates that user has enough Resources to trade
     * @return true if trade occurred, false otherwise
     */
    bool tradeBank();

    /**
     *
     * @return true if player has > 7 resources, false otherwise
     */
    bool rolledASeven();

    /**
     * if player has 7 or more resources, removes half of their resources
     * player can choose which resources, and how many of each
     * validates that player has enough resources to remove
     */
    void loseHalfOfCards();

    /**
     * asks player who they would like to steal resources from (if vector is not empty)
     * validates that the person to rob has resources
     * @param stuffToSteal vector of names and resources of all players (other than you) on Tile
     * @return name of player to steal from, or ""
     */
    std::string moveRobber(std::vector<std::tuple<std::string, std::vector<int>>> stuffToSteal);

    /**
     *
     * @return resources
     */
    std::vector<int> getResources();

    /**
     *
     * @return name
     */
    std::string getName();

    /**
     *
     * @return char corresponding to color
     */
    std::string getColor() const;

    /**
     *
     * @return army
     */
    int getArmy() const;
};



#endif //PLAYER_H
