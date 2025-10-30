//
// Created by tvito on 9/11/2025.
//

#ifndef CUSTOMUTILS_H
#define CUSTOMUTILS_H

#include <chrono>
#include <random>
#include <iostream>
#include <string>

// Get start time of the program to seed randomness
static int start_time = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).
    time_since_epoch()).count());

//The generator that we will use for most randomness
static std::default_random_engine generator_(start_time);

//The distribution to use for dice
static auto distribution_ = std::uniform_int_distribution<int>(1,6);

//Lamda function to allow rolling a dice as dice()
static auto dice = []{ return distribution_(generator_); };

//Lamda function to allow shifting the robber token as shift()
static auto shift = []{ return std::uniform_int_distribution<int>(-20,20)(generator_); };

/** Enumerated type for different resources. null can be used as empty (for dessert) or as a wildcard (for trades)
 *
 * @brief Values: wood, sheep, brick, stone, wheat, null
 *
 */
enum resourceType : int {wood = 0, sheep = 1, brick = 2, stone = 3, wheat = 4, null = 7};


/**A struct that holds a type and quantity of a resource
 *
 * @param resourceType type -  The type of the resource
 * @param int num - The quantity of the resources
 *
 */
struct Resource {
    resourceType type;
    int num;
};

/** Enumerated type for tilts of tile edges. Left and right denote tilt of top
 *
 * @brief Values: right, left, upright
 *
 */
enum tilt {
    right,
    left,
    upright
};

/**A struct that holds different types of trades. Mostly used for trading with the bank/ports
 *
 * @param Resource give - What the player who initiated the trade is giving
 * @param Resource receive - What the player who initiated the trade is getting
 *
 */
struct Trade {
    Resource give;
    Resource receive;
};

/** Compares two Trades
 *
 * @param lhs The left hand side Trade
 * @param rhs The right hand side Trade
 * @return True if and only if both type and num are equal. False otherwise
 */
inline bool operator==(const Trade& lhs, const Trade& rhs) {
    return lhs.give.type == rhs.give.type && lhs.give.num == rhs.give.num;
}

/** Compares two Trades
 *
 * @param lhs The left hand side Trade
 * @param rhs The right hand side Trade
 * @return Inverse of above
 */
inline bool operator!=(const Trade& lhs, const Trade& rhs) {
    return !(lhs == rhs);
}

inline std::ostream& operator<<(std::ostream& os, Resource const &rhs) {
    os << rhs.num << " " << rhs.type;
    return os;
}

/**Converts a Resource into a std::string representation
 *
 * @param rhs The resource to convert
 * @return A string representation in the form "num type"
 */
inline std::string to_string(Resource const &rhs) {
    std::string res = std::to_string(rhs.num);
    res += " ";
    switch (rhs.type) {
        case wood: res += ("wood"); break;
        case sheep: res += ("sheep"); break;
        case brick: res += "brick"; break;
        case stone: res += ("stone"); break;
        case wheat: res += ("wheat"); break;
        case null: res += ("anything"); break;
    }
    return res;
}

inline std::ostream& operator<<(std::ostream& os, resourceType const &rhs){
    switch (rhs) {
        case wood: os << "wood"; break;
        case sheep: os << "sheep"; break;
        case brick: os << "brick"; break;
        case stone: os << "stone"; break;
        case wheat: os << "wheat"; break;
        case null: os << "null"; break;
        default: os << "unknown"; break;
    }
    return os;
}


inline std::stringstream& operator<<(std::stringstream& os, resourceType const &rhs){
    switch (rhs) {
        case wood: os << "wood"; break;
        case sheep: os << "sheep"; break;
        case brick: os << "brick"; break;
        case stone: os << "stone"; break;
        case wheat: os << "wheat"; break;
        case null: os << "desert"; break;
        default: os << "unknown"; break;
    }
    return os;
}

/**Returns the path to the image for a given resource tile
 *
 * @param rtype the resource type of the tile
 * @return the path to the image for a given resource type
 */
inline std::string getRTypeFile(const resourceType rtype) {
    std::stringstream ss;
    std::string file = "static/";
    std::string type;
    ss << rtype;
    ss >> type;
    file += type;
    file += ".png";
    return file;
}

/**Returns the path to the image for a given number tile
 *
 * @param num The number
 * @return the path
 */
inline std::string getNumImgFile(const int num){
    if (num == 7 || num < 2 || num > 12) return "";
    std::string file = "static/";
    file += std::to_string(num);
    file += ".png";
    return file;
}


// A struct for holding and working with x,y coordinates
struct coords {
    double x;
    double y;
};


/** Handles inout validation of getting a valid int from a user.
 *
 * Range validation of the int must be done separately
 *
 * @return A valid integer
 */
inline int getIntFromUser() {
    //Create stringstream
    std::stringstream ss;
    //Obtain user input
    int number;
    std::string input;
    std::string left_in_ss = "";
    getline(std::cin, input);
    ss << input;
    std::cout << left_in_ss << std::endl;
    bool is_int = !(ss >> number);
    getline(ss, left_in_ss);
    //Validate input: will return false if unable to convert to an int
    if (is_int || !left_in_ss.empty()) {
        return -1;
    }
    if (number < 0) {
        return -1;
    }
    //Return validated integer
    return number;
}


#endif //CUSTOMUTILS_H
