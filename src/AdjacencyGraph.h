//
// Created by tvito on 10/2/2025.
//

#ifndef CATAN_ADJACENCYGRAPH_H
#define CATAN_ADJACENCYGRAPH_H
#include <map>
#include "Board.h"
#include "Edge.h"
#include "Vertex.h"

class AdjacencyGraph {

    std::map< Edge*,std::vector<Vertex*>> edgeKeyedAdjacencyList;
    std::map< Vertex*,std::vector<Edge*>> vertexKeyedAdjacencyList;

    public:

    AdjacencyGraph() = default;
    explicit AdjacencyGraph(Board* pBoard);

    ~AdjacencyGraph() = default;

    bool isAdjacent( Edge* &edge1,  Edge* &edge2) ;
    bool isAdjacent( Edge* &edge,  Vertex* &vertex) ;
    bool isAdjacent( Vertex* &vertex1,  Vertex* &vertex2) ;

    std::vector<Vertex*> getAdjacentVertices( Edge* &edge) ;
    std::vector<Vertex*> getAdjacentVertices( Vertex* &vertex) const;
    std::vector<Edge*> getAdjacentEdges( Edge* &edge) const;
    std::vector<Edge*> getAdjacentEdges( Vertex* &vertex) ;

    bool checkEdge( Edge* &pEdge,  Player* &player) ;
    bool checkVertex( Vertex* &pVertex,  Player* &player,  bool setup = false) ;

    // std::vector<Vertex*> getValidVertices( Player* &player) ;
    // std::vector<Edge*> getValidEdges( Player* &player) ;

};


#endif //CATAN_ADJACENCYGRAPH_H