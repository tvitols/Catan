//
// Created by tvito on 9/10/2025.
//

#include "Info.h"
#include <iostream>
#include <fstream>

const std::filesystem::path Info::rulesPath = std::filesystem::current_path() / "rules.txt";
const std::filesystem::path Info::infoPath = std::filesystem::current_path() / "info.txt";

void Info::print_rules() {
    std::ifstream rules;
    rules.open(rulesPath);
    //Validation
    if (!rules.is_open()) {
        std::cout << "Error in opening file " << rulesPath << std::endl;
    }
    std::string rule;
    //Printing out rules.txt
    while (getline(rules,rule)) {
        std::cout << rule << std::endl;
    }
    std:: cout << std::endl << std::endl << std::endl;
}

void Info::print_info() {
    std::ifstream info;
    info.open(infoPath);
    //Validation
    if (!info.is_open()) {
        std::cout << "Error in opening file " << infoPath << std::endl;
    }
    std::string infoString;
    //Printing out info.txt
    while (getline(info,infoString)) {
        std::cout << infoString << std::endl;
    }
    std:: cout << std::endl << std::endl << std::endl;
}