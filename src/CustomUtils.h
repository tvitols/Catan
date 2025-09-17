//
// Created by tvito on 9/11/2025.
//

#ifndef CUSTOMUTILS_H
#define CUSTOMUTILS_H

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
#endif //CUSTOMUTILS_H
