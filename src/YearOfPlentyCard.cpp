//
// Created by lilas on 10/4/2025.
//

#include "YearOfPlentyCard.h"
#include "CustomUtils.h"
#include <iostream>

#include "vector"

YearOfPlenty::YearOfPlenty() : Card("Year of Plenty", "Adds two resources of player's choice"){};

int YearOfPlenty::play(void* object) {
    int numberChosen = 0;
    int choice;
    std::vector<int>* resources = static_cast<std::vector<int>*>(object);\\
    //Prompts the user for a resourceType
    while (numberChosen != 2) {
        std::cout << "Select an option from the list below" << std::endl;
        std::cout << "1. Wood" << std::endl;
        std::cout << "2. Stone" << std::endl;
        std::cout << "3. Brick" << std::endl;
        std::cout << "4. Sheep" << std::endl;
        std::cout << "5. Wheat" << std::endl;
        choice = getIntFromUser();
        //Validates input
        while (choice == -1 || choice == 0 || choice > 5) {
            std::cout << "Invalid input. Please enter a number between 1 and 5: ";
            choice = getIntFromUser();
        }
        int numberOfResource;
        switch (choice) {
            case 1:
                std::cout << "How much wood do you want: ";
                numberOfResource = getIntFromUser();
                //Validates input
                while (numberOfResource == -1 || numberChosen + numberOfResource > 2) {
                    std::cout << "Invalid input. Please enter a number between 0 and " << std::to_string(2 - numberChosen) << ": ";
                    numberOfResource = getIntFromUser();
                }
                //Updates numberChosen
                numberChosen += numberOfResource;
                //Increases player wood resources
                (*resources)[wood] += numberOfResource;
                break;
            case 2:
                std::cout << "How much stone do you want: ";
                numberOfResource = getIntFromUser();
                //Validates input
                while (numberOfResource == -1 || numberChosen + numberOfResource > 2) {
                    std::cout << "Invalid input. Please enter a number between 0 and " << std::to_string(2 - numberChosen) << ": ";
                    numberOfResource = getIntFromUser();
                }
                //Updates numberChosen
                numberChosen += numberOfResource;
                //Increases player stone resources
                (*resources)[stone] += numberOfResource;
                break;
            case 3:
                std::cout << "How much brick do you want: ";
                numberOfResource = getIntFromUser();
                //Validates input
                while (numberOfResource == -1 || numberChosen + numberOfResource > 2) {
                    std::cout << "Invalid input. Please enter a number between 0 and " << std::to_string(2 - numberChosen) << ": ";
                    numberOfResource = getIntFromUser();
                }
                //Updates numberChosen
                numberChosen += numberOfResource;
                //Increases player brick resources
                (*resources)[brick] += numberOfResource;
                break;
            case 4:
                std::cout << "How much sheep do you want: ";
                numberOfResource = getIntFromUser();
                //Validates input
                while (numberOfResource == -1 || numberChosen + numberOfResource > 2) {
                    std::cout << "Invalid input. Please enter a number between 0 and " << std::to_string(2 - numberChosen) << ": ";
                    numberOfResource = getIntFromUser();
                }
                //Updates numberChosen
                numberChosen += numberOfResource;
                //Increases player sheep resources
                (*resources)[sheep] += numberOfResource;
                break;
            case 5:
                std::cout << "How much wheat do you want: ";
                numberOfResource = getIntFromUser();
                //Validates input
                while (numberOfResource == -1 || numberChosen + numberOfResource > 2) {
                    std::cout << "Invalid input. Please enter a number between 0 and " << std::to_string(2 - numberChosen) << ": ";
                    numberOfResource = getIntFromUser();
                }
                //Updates numberChosen
                numberChosen += numberOfResource;
                //Increases player wheat resources
                (*resources)[wheat] += numberOfResource;
                break;
        }
    }
    //returns the number corresponding to YearOfPlenty
    return 0;
}

int YearOfPlenty::getType() const {
    return type;
}