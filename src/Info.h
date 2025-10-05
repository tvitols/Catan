//
// Created by tvito on 9/10/2025.
//

#ifndef INFO_H
#define INFO_H

#include <filesystem>


class Info {
private:
    //filepath to rules.txt
    static const std::filesystem::path rulesPath;
    //filepath to info.txt
    static const std::filesystem::path infoPath;

public:
    /**
     * prints the contents of rules.txt
     */
    static void print_rules();
    /**
     * prints the contents of info.txt
     */
    static void print_info();
};


#endif //INFO_H
