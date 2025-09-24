//
// Created by tvito on 9/11/2025.
//

#ifndef CUSTOMUTILS_H
#define CUSTOMUTILS_H

#include <chrono>
#include <random>
#include <iostream>

static int start_time = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).
    time_since_epoch()).count());

// Function modified from https://stackoverflow.com/a/16388610
constexpr unsigned int str2int(const char* str, const int h = 0){
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}


inline void checkCin(auto *checkVar) {
    if (std::cin.peek() != '\n') {
       *checkVar = 0;
    }
    std::cin.clear();
    std::string junk;
    std::getline(std::cin,junk);
}

static std::default_random_engine generator_(start_time);
static std::uniform_int_distribution<int> distribution_ = std::uniform_int_distribution<int>(1,6);

static auto dice = [] { return distribution_(generator_); };


enum resourceType : int {wood = 0, sheep = 1, brick = 2, stone = 3, wheat = 4};

struct Resource {
    resourceType type;
    int num;
};

inline std::ostream& operator<<(std::ostream& os, Resource const &rhs) {
    os << rhs.num << " " << rhs.type;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, resourceType const &rhs){
    switch (rhs) {
        case wood: os << "wood"; break;
        case sheep: os << "sheep"; break;
        case brick: os << "brick"; break;
        case stone: os << "stone"; break;
        case wheat: os << "wheat"; break;
        default: os << "unknown"; break;
    }
    return os;
}


#endif //CUSTOMUTILS_H
