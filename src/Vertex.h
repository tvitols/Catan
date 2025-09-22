//
// Created by tvito on 9/16/2025.
//

#ifndef VERTEX_H
#define VERTEX_H



class Vertex {

    int x;
    int y;
    bool occupied = false;

    public:
    Vertex();
    ~Vertex();
    Vertex(int x, int y) : x(x), y(y) {};

};



#endif //VERTEX_H
