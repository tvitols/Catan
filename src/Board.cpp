//
// Created by tvito on 9/16/2025.
//

#include "Board.h"

#include <random>
#include <vector>

#include "Edge.h"
#include "Port.h"
#include "Vertex.h"

Board::Board() {
    this->robber = robber;
    generateTiles(std::mt19937(std::random_device()()));
};

Board::Board(const int seed) {
    this-> robber = robber;
    generateTiles(std::mt19937(seed));
    for (std::vector<Tile*> tileVector : tiles) {
        for (Tile *tile : tileVector) {
            if (tile->getResourceType() == null) {
                robber->setCurrentTile(tile);
            }
        }
    }
}


void Board::generateTiles(std::mt19937 twist) {
    std::vector<Edge*> e;
    for (int i = 0; i < 30; i++) {
        e.push_back(new Edge());
    }
    std::vector<Vertex*> v;
    for (int i = 0; i < 30; i++) {
        v.push_back(new Vertex());
    }

    std::vector<int> ports = {};

    for (auto p : ports) {
        v[p] = reinterpret_cast<std::vector<Vertex *>::value_type>(new Port(*v[p]));
    }

    std::vector keys = {2,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,12};

    std::vector types = {wood,wood,wood,wood,sheep,sheep,sheep,sheep,wheat,wheat,wheat,wheat,brick,brick,brick,stone,stone,stone,null};

    shuffle(keys.begin(), keys.end(), twist);
    shuffle(types.begin(),types.end(), twist);

    //Lila: starting from top and going clockwise
    tiles =
            {std::vector<Tile*>() = {new Tile({e[0],e[1],e[2],e[3],e[4],e[5]},{v[0],v[1],v[2],v[3],v[4],v[5]}, keys[0],types[0]), new Tile({e[1],e[6],e[7],e[8],e[9],e[10]},{v[1],v[2],v[6],v[7],v[8],v[9]},keys[1],types[1]), new Tile({e[8],e[11],e[12],e[13],e[14],e[15]},{v[7],v[8],v[10],v[11],v[12],v[13]},keys[2],types[2])},
        std::vector<Tile*>() = {new Tile({e[3], e[16], e[17], e[18], e[19], e[20]},{v[4], v[3], v[14], v[15], v[16], v[17]},keys[3],types[3]), new Tile({e[2],e[6],e[21],e[22],e[23],e[16]},{v[2],v[3],v[6],v[18],v[19],v[14]},keys[4],types[4]), new Tile({e[11], e[24], e[25], e[26], e[21], e[7]}, {v[7], v[10], v[20], v[21], v[18], v[6]},keys[5],types[5]), new Tile({e[27], e[28], e[29], e[30], e[24], e[12]}, {v[11], v[22], v[23], v[24], v[20], v[10]},keys[6],types[6])},
    std::vector<Tile*>() = {new Tile({e[18], e[31], e[32], e[33], e[34], e[35]}, {v[16], v[15], v[25], v[26], v[27], v[28]},keys[7],types[7]), new Tile({e[23], e[36], e[37], e[38], e[31], e[17]}, {v[14], v[19], v[29], v[30], v[25], v[15]},keys[8],types[8]), new Tile({e[26], e[39], e[40], e[41], e[36], e[22]}, {v[18], v[21], v[31], v[32], v[29], v[19]},keys[9],types[9]), new Tile({e[30], e[42], e[43], e[44], e[39], e[25]}, {v[20], v[24], v[33], v[34], v[31], v[21]},keys[10],types[10]), new Tile({e[45], e[46], e[47], e[48], e[42], e[29]}, {v[23], v[35], v[36], v[37], v[33], v[24]},keys[11],types[11])},
        std::vector<Tile*>() = {new Tile({e[38], e[49], e[50], e[51], e[52], e[32]}, {v[25], v[30], v[38], v[39], v[40], v[26]},keys[12],types[12]), new Tile({e[41], e[53], e[54], e[55], e[49], e[37]}, {v[29], v[32], v[41], v[42], v[38], v[30]},keys[13],types[13]), new Tile({e[44], e[56], e[57], e[58], e[53], e[40]}, {v[31], v[34], v[43], v[44], v[41], v[32]},keys[14],types[14]), new Tile({e[48], e[59], e[60], e[61], e[56], e[43]}, {v[33], v[37], v[45], v[46], v[43], v[34]},keys[15],types[15])},
            std::vector<Tile*>() = {new Tile({e[55], e[62], e[63], e[64], e[65], e[50]}, {v[38], v[42], v[47], v[48], v[49], v[39]},keys[16],types[16]), new Tile({e[58], e[66], e[67], e[68], e[62], e[54]}, {v[41], v[44], v[50], v[51], v[47], v[42]},keys[17],types[17]), new Tile({e[61], e[69], e[70], e[71], e[66], e[57]}, {v[43], v[46], v[52], v[53], v[50], v[44]},keys[18],types[18])},};
}

Board::~Board() = default;


Board Board::generateBoard() {
    return {};
}

Board Board::generateBoard(Robber *robber) {
    Board board{};
    board.addRobber(robber);
    return board;
}

Board Board::generateBoard(const int seed) {
    return Board(seed);
}

void Board::printBoard() const {
    for (const auto& row : tiles) {
        for (const auto tile : row) {
            tile->printTile();
        }
    }
}

void Board::collectResources(int roll) const {
    for (const auto& row : tiles) {
        for (const auto tile : row) {
            tile->collectResources(roll);
        }
    }
}

void Board::addRobber(Robber* robber) {
    this->robber = robber;
}


