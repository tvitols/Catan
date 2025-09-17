//
// Created by tvito on 9/10/2025.
//

#ifndef INFO_H
#define INFO_H

#include <filesystem>


class Info {
private:
    static const std::filesystem::path rulesPath;
    static const std::filesystem::path infoPath;

public:
    static void print_rules();
    static void print_info();
};


#endif //INFO_H
