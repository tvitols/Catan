//
// Created by tvito on 9/16/2025.
//

#include "Board.h"

#include <vector>

#include "Edge.h"
#include "Vertex.h"

Board::Board() {

    std::vector<Edge*> e;
    for (int i = 0; i < 30; i++) {
        e.push_back(new Edge());
    }
    std::vector<Vertex*> v;
    for (int i = 0; i < 30; i++) {
        v.push_back(new Vertex());
    }

    tiles =
            {std::vector<Tile*>() = {new Tile({e[0],e[1],e[2],e[3],e[4],e[5]},{v[0],v[1],v[2],v[3],v[4],v[5]}), new Tile({e[1],e[6],e[7],e[8],e[9],e[10]},{v[1],v[2],v[6],v[7],v[8],v[9]}), new Tile({e[8],e[11],e[12],e[13],e[14],e[15]},{v[7],v[8],v[10],v[11],v[12],v[13]})},
        std::vector<Tile*>() = {new Tile({e[3], e[16], e[17], e[18], e[19], e[20]},{v[4], v[3], v[14], v[15], v[16], v[17]}), new Tile({e[2],e[6],e[21],e[22],e[23],e[16]},{v[2],v[3],v[6],v[18],v[19],v[14]}), new Tile(), new Tile()},
    std::vector<Tile*>() = {new Tile(), new Tile(), new Tile(), new Tile(), new Tile()},
        std::vector<Tile*>() = {new Tile(), new Tile(), new Tile(), new Tile()},
            std::vector<Tile*>() = {new Tile(), new Tile(), new Tile()},};


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


