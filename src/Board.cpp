//
// Created by tvito on 9/16/2025.
//

#include "Board.h"

#include <random>
#include <vector>

#include "Edge.h"
#include "Port.h"
#include "Vertex.h"
#include "customUtils.h"
#include "cppgraphics.hpp"

Board::Board() {
    robber = new Robber;
    generateTiles(std::mt19937(std::random_device()()));
    for (const std::vector<Tile *> &tileVector: tiles) {
        for (Tile *tile: tileVector) {
            if (tile->getResourceType() == null) {
                robber->setCurrentTile(tile);
            }
        }
    }
} ;

Board::Board(Robber *pRobber) {
    robber = pRobber;
    generateTiles(std::mt19937(std::random_device()()));
    for (const std::vector<Tile*>& tileVector : tiles) {
        for (Tile *tile : tileVector) {
            if (tile->getResourceType() == null) {
                robber->setCurrentTile(tile);
            }
        }
    }
}

Board::Board(const int seed) {
    robber = new Robber;
    generateTiles(std::mt19937(seed));
    for (const std::vector<Tile*>& tileVector : tiles) {
        for (Tile *tile : tileVector) {
            if (tile->getResourceType() == null) {
                robber->setCurrentTile(tile);
            }
        }
    }
}


void Board::generateTiles(std::mt19937 twist) {
    std::vector<Edge*> e;
    for (int i = 0; i < 72; i++) {
        e.push_back(new Edge());
    }

    // 0-0,1-0,2-1,3-1,4-2,5-2,6-3,7-3,8-4,9-4,10-5,11-5,12-6,13-6,14-7,15-7
    std::vector<Vertex*> v;
    std::vector<resourceType> randomResource = {wood,  wheat,  sheep, brick, stone, null, null, null, null};
    std::shuffle(randomResource.begin(), randomResource.end(), twist);
    const std::vector<int> portIndices = {0, 5, 11, 22, 35, 36, 45, 46, 50, 51, 48, 49, 40, 26, 16, 12};
    const std::vector<coords> shipCoords = {{255,115},{450,105},{600,205},{700,410},{590,615},{460,710},{255,710},{150,515},{150,350}};
    bool pushed = false;
    for (int i = 0; i < 54; i++) {
        pushed = false;
        for (int j = 0; j < portIndices.size(); j++) {
            if (portIndices[j] == i) {
                v.push_back(new Port({{randomResource[j/2],(randomResource[j/2]==null)?3:2},{null,1}},shipCoords[j/2]));
                pushed = true;
            }
        }
        if (!pushed){
            v.push_back(new Vertex());
        }
    }


    std::vector keys = {2,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11,12};
    std::vector types = {wood,wood,wood,wood,sheep,sheep,sheep,sheep,wheat,wheat,wheat,wheat,brick,brick,brick,stone,stone,stone,null};

    shuffle(keys.begin(), keys.end(), twist);
    shuffle(types.begin(),types.end(), twist);

    for (int i = 0; i < types.size(); i++) {
        if (types[i] == null ) {
            keys.insert(keys.begin() + i,{7});
        }
    }

    //Lila: starting from top and going clockwise
    tiles =
            {std::vector<Tile*>() = {new Tile({e[0],e[1],e[2],e[3],e[4],e[5]},{v[0],v[1],v[2],v[3],v[4],v[5]}, keys[0],types[0]), new Tile({e[9],e[8],e[7],e[6],e[1],e[10]},{v[9],v[8],v[7],v[6],v[2],v[1]},keys[1],types[1]), new Tile({e[14],e[13],e[12],e[11],e[8],e[15]},{v[13],v[12],v[11],v[10],v[7],v[8]},keys[2],types[2])},
        std::vector<Tile*>() = {new Tile({e[3], e[16], e[17], e[18], e[19], e[20]},{v[4], v[3], v[14], v[15], v[16], v[17]},keys[3],types[3]), new Tile({e[6],e[21],e[22],e[23],e[16],e[2]},{v[2],v[6],v[18],v[19],v[14],v[3]},keys[4],types[4]), new Tile({e[11], e[24], e[25], e[26], e[21], e[7]}, {v[7], v[10], v[20], v[21], v[18], v[6]},keys[5],types[5]), new Tile({e[27], e[28], e[29], e[30], e[24], e[12]}, {v[11], v[22], v[23], v[24], v[20], v[10]},keys[6],types[6])},
    std::vector<Tile*>() = {new Tile({e[18], e[31], e[32], e[33], e[34], e[35]}, {v[16], v[15], v[25], v[26], v[27], v[28]},keys[7],types[7]), new Tile({e[23], e[36], e[37], e[38], e[31], e[17]}, {v[14], v[19], v[29], v[30], v[25], v[15]},keys[8],types[8]), new Tile({e[26], e[39], e[40], e[41], e[36], e[22]}, {v[18], v[21], v[31], v[32], v[29], v[19]},keys[9],types[9]), new Tile({e[30], e[42], e[43], e[44], e[39], e[25]}, {v[20], v[24], v[33], v[34], v[31], v[21]},keys[10],types[10]), new Tile({e[45], e[46], e[47], e[48], e[42], e[29]}, {v[23], v[35], v[36], v[37], v[33], v[24]},keys[11],types[11])},
        std::vector<Tile*>() = {new Tile({e[38], e[49], e[50], e[51], e[52], e[32]}, {v[25], v[30], v[38], v[39], v[40], v[26]},keys[12],types[12]), new Tile({e[41], e[53], e[54], e[55], e[49], e[37]}, {v[29], v[32], v[41], v[42], v[38], v[30]},keys[13],types[13]), new Tile({e[44], e[56], e[57], e[58], e[53], e[40]}, {v[31], v[34], v[43], v[44], v[41], v[32]},keys[14],types[14]), new Tile({e[48], e[59], e[60], e[61], e[56], e[43]}, {v[33], v[37], v[45], v[46], v[43], v[34]},keys[15],types[15])},
            std::vector<Tile*>() = {new Tile({e[55], e[62], e[63], e[64], e[65], e[50]}, {v[38], v[42], v[47], v[48], v[49], v[39]},keys[16],types[16]), new Tile({e[58], e[66], e[67], e[68], e[62], e[54]}, {v[41], v[44], v[50], v[51], v[47], v[42]},keys[17],types[17]), new Tile({e[61], e[69], e[70], e[71], e[66], e[57]}, {v[43], v[46], v[52], v[53], v[50], v[44]},keys[18],types[18])},};

    const std::vector<int> offset ={300,250,200,250,300};
    for (int i = 0; i < tiles.size(); i++) {
        for (int j = 0; j < tiles[i].size(); j++) {
            if (tiles[i][j]->getKey() == 7) {
                tiles[i][j]->rob(true);
            }
            tiles[i][j]->setCoordinates(offset[i]+(j*100), 217+(i*100));
            tiles[i][j]->setVerticeCoords();
            tiles[i][j]->setEdgeCoords();
        }
    }

}

Board::~Board() = default;


Board Board::generateBoard() {
    return {};
}

Board Board::generateBoard(Robber *robber) {
    return Board(robber);
}

Board Board::generateBoard(const int seed) {
    return Board(seed);
}

coords Board::printBoard(const std::string &message, const bool wait){


    cg::create_window("Catan",800,800);
    cg::set_fill_color(cg::DarkBlue);
    cg::rectangle(0,0,800,800);
    cg::text(message, 10,10,780,50);
    cg::centered_image("static/top.png",350,125,325,400);
    cg::centered_image("static/top_left.png",160,310,325,400);
    cg::centered_image("static/bottom_left.png",205,595,325,400);
    cg::centered_image("static/bottom.png",435,715,325,400);
    cg::centered_image("static/bottom_right.png",640,500,325,400);
    cg::centered_image("static/top_right.png",600,210,325,400);
    for (auto ts : tiles) {
        for (const auto tile : ts) {
            const auto [tx, ty] = tile->getCoordinates();
            cg::centered_image(getRTypeFile(tile->getResourceType()),tx,ty,100,140);
            if (tile->getKey() != 7)
                cg::centered_image(getNumImgFile(tile->getKey()),tx,ty,50,50);
            for (int k = 0; k < 6; k++) {
                if (Edge * e = tile->getEdge(k); e->isOccupied()) {
                    const auto [ex, ey] = e->getCoordinates();
                    cg::centered_image(e->getOccupiedImg(),ex,ey,60,60);
                }
                Vertex* v = tile->getVertex(k);
                if (v->isOccupied()) {
                    const auto [vx, vy] = v->getCoordinates();
                    cg::centered_image(v->getOccupiedImg(),vx,vy,30,30);
                }
                if (v->isPort()) {
                    cg::centered_image(static_cast<Port *>(v)->getShipToken(), static_cast<Port *>(v)->getShipX(),static_cast<Port *>(v)->getShipY(),40,50);
                }
            }
        }
    }

    const auto [rx, ry] = robber->getCurrentTile()->getCoordinates();
    cg::centered_image("static/robber.png",rx+shift(),ry+shift(),25,50);


    while (cg::wait_until_mouse() != cg::MouseLeft) {}

    const coords xy = {cg::get_mouse_x(),cg::get_mouse_y()};
    cg::clear();
    cg::close_window();

    return xy;

}


void Board::collectResources(int roll) const {
    for (const auto& row : tiles) {
        for (const auto tile : row) {
            tile->collectResources(roll);
        }
    }
}

std::vector<std::tuple<std::string, std::vector<int>>> Board::otherPlayerResources(std::string name) {
    return robber->otherPlayerResources(name);
}

Edge * Board::getEdge(coords coordinates) {
    for (int i = 0; i < tiles.size(); i++) {
        for (int j = 0; j < tiles[i].size(); j++) {
            if (tiles[i][j]->getEdge(coordinates) != nullptr) {
                return tiles[i][j]->getEdge(coordinates);
            }
        }
    }
    return nullptr;
}

Vertex * Board::getVertex(coords coordinates) {
    for (int i = 0; i < tiles.size(); i++) {
        for (int j = 0; j < tiles[i].size(); j++) {
            if (tiles[i][j]->getVertice(coordinates) != nullptr) {
                return tiles[i][j]->getVertice(coordinates);
            }
        }
    }
    return nullptr;
}

Edge * Board::getEdge(const std::string &message) {
    coords xy = printBoard(message);
    std::cout << xy << std::endl;
    return getEdge(xy);
}

Vertex * Board::getVertex(const std::string &message) {
    return getVertex(printBoard(message));
}

Structure * Board::getStructure(double x, double y) {
}

Tile* Board::getTile(coords coordinates) {
    for (int i = 0; i < tiles.size(); i++) {
        for (int j = 0; j < tiles[i].size(); j++) {
            if (tiles[i][j]->getTile(coordinates)) {
                return tiles[i][j];
            }
        }
    }
    return nullptr;
}

std::vector<std::vector<Tile *>> Board::getTiles() {
    return tiles;
}

void Board::moveRobber(Tile* tile) {
    robber->move(tile);
}
