//
// Created by tvito on 9/16/2025.
//

#ifndef PORT_H
#define PORT_H

#include "Vertex.h"


class Port : Vertex {

    public:
    Port() = default;

    explicit Port(const Vertex &pVert): Vertex(pVert) {};
    ~Port() = default;
};



#endif //PORT_H
