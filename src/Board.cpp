//
// Created by tvito on 9/16/2025.
//

#include "Board.h"

Board::Board() {
    // generate vertices
    // generate edges
    // assign vertices and edges to tiles
    // std::vector<Vertex> vertices;
    // int rowsizes[] = {3,5,7,5,3};
    // for (int row = 0; row < 5; row++) {
    //     int rowsize = rowsizes[row] + 2;
    //     for (int i = 0; i <= rowsize - 1; i++) {
    //         vertices.emplace_back(row + i * 5, row);
    //     }
    // }
    // for (int row = 0; row < 5; row++) {
    //     int rowsize = rowsizes[row] + 2;
    //     for (int i = 0; i <= rowsize - 1; i++) {
    //         for (int j = 0; j <= 6; j++) {
    //             tiles[row*rowsize + i]->setVertex(j,vertices[]);
    //         }
    //     }
    // }
    // }


}

Board::~Board() = default;


Board Board::generateBoard() {
    return {};
}

Board Board::generateBoard(int seed) {
    return {};
}

void Board::printBoard() {
    for (auto tile : tiles) {
        tile->printTile();
    }
}

void Board::collectResources(int roll) {

}


