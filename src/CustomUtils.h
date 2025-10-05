//
// Created by tvito on 9/11/2025.
//

#ifndef CUSTOMUTILS_H
#define CUSTOMUTILS_H

#include <chrono>
#include <random>
#include <iostream>
#include <string>

static int start_time = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).
    time_since_epoch()).count());

// Function modified from https://stackoverflow.com/a/16388610
constexpr unsigned int str2int(const char* str, const int h = 0){
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

 void checkCin(auto *checkVar) {
    if (std::cin.peek() != '\n') {
       *checkVar = 0;
    }
    std::cin.clear();
    std::string junk;
    std::getline(std::cin,junk);
}

static std::default_random_engine generator_(start_time);
static auto distribution_ = std::uniform_int_distribution<int>(1,6);
static auto shiftDist_ = std::uniform_int_distribution<int>(-20,20);

static auto dice = []{ return distribution_(generator_); };
static auto shift = []{ return shiftDist_(generator_); };

enum resourceType : int {wood = 0, sheep = 1, brick = 2, stone = 3, wheat = 4, null = 7};

struct Resource {
    resourceType type;
    int num;
};

enum tilt {
    right,
    left,
    upright
};

struct Trade {
    Resource give;
    Resource receive;
};

inline bool operator<(const Trade& lhs, const Trade& rhs)
{
    return lhs.receive.num > rhs.receive.num;
}

inline bool operator==(const Trade& lhs, const Trade& rhs) {
    return lhs.give.type == rhs.give.type && lhs.give.num == rhs.give.num;
}

inline std::ostream& operator<<(std::ostream& os, Resource const &rhs) {
    os << rhs.num << " " << rhs.type;
    return os;
}

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

inline std::string getNumImgFile(const int num){
    if (num == 7 || num < 2 || num > 12) return "";
    std::string file = "static/";
    file += std::to_string(num);
    file += ".png";
    return file;
}

struct coords {
    double x;
    double y;
};

inline std::ostream& operator<<(std::ostream& os, coords const &rhs) {
    os << "(" << rhs.x << ", " << rhs.y << ")";
    return os;
}

inline void pushFunction(std::vector<void (*)()> &vector, void (*func)()) {
    vector.push_back(func);
}

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
