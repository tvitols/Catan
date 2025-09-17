//
// Created by tvito on 9/16/2025.
//

#ifndef BOARD_H
#define BOARD_H



class Board {

    Board();

public:
    ~Board();

    static Board generateBoard();
    static Board generateBoard(int seed);

};



#endif //BOARD_H
