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

    //contains a vector of all Vertices adjacent to each Edge
    std::map< Edge*,std::vector<Vertex*>> edgeKeyedAdjacencyList;
    //contains a vector of all Edges adjacent to each Vertex
    std::map< Vertex*,std::vector<Edge*>> vertexKeyedAdjacencyList;

    public:

    /**
     * Initializes variables by iterating through the Board
     */
    AdjacencyGraph() = default;

    /**
     * Initializes variables by iterating through the Board
     * @param pBoard a specific Board to create the AdjacencyGraph for
     */
    explicit AdjacencyGraph(Board* pBoard);

    /**
     * Destroys the AdjacencyGraph
     */
    ~AdjacencyGraph() = default;

    /**
     *
     * @param edge1 Edge on Board
     * @param edge2 Edge on Board
     * @return true if the two Edges are adjacent and distict, false otherwise
     */
    bool isAdjacent( Edge* &edge1,  Edge* &edge2) ;
    /**
     *
     * @param edge Edge on Board
     * @param vertex Vertex on Board
     * @return true if the Edge and Vertex are adjacent, false otherwise
     */
    bool isAdjacent( Edge* &edge,  Vertex* &vertex) ;
    /**
     *
     * @param vertex1 Vertex on Board
     * @param vertex2 Vertex on Board
     * @return true if those Vertices are adjacent and distinct, false otherwise
     */
    bool isAdjacent( Vertex* &vertex1,  Vertex* &vertex2) ;

    /**
     *
     * @param edge Edge that user wants to check
     * @return vector of all adjacent Vertices to that Edge
     */
    std::vector<Vertex*> getAdjacentVertices( Edge* &edge) ;
    /**
     *
     * @param vertex Vertex that user wants to check
     * @return vector of all adjacent vertices to that Vertex
     */
    std::vector<Vertex*> getAdjacentVertices(Vertex* &vertex);
    /**
     *
     * @param edge Edge user wants to check
     * @return vector of all adjacent Edges to that Edge
     */
    std::vector<Edge*> getAdjacentEdges(Edge* &edge);
    /**
     *
     * @param vertex Vertex user wants to check
     * @return a vector of all adjacent edges to that Vertex
     */
    std::vector<Edge*> getAdjacentEdges( Vertex* &vertex) ;

    /**
     * checks if any adjacent vertices and edges have structures belonging to player
     * @param pEdge edge a player wants to check
     * @param player player who wants to place the Road
     * @return true if there is an adjacent settlement or road belonging to player, false otherwise
     */
    bool checkEdge( Edge* &pEdge,  Player* &player) ;
    /**
     *
     * @param pVertex a Vertex to check
     * @param player player attempting to place something on that Vertex
     * @param setup allows user to check adjacent edges
     * @return true if the Vertex is not occupied and also has a Road leading to it
     */
    bool checkVertex( Vertex* &pVertex,  Player* &player,  bool setup = false) ;

    // std::vector<Vertex*> getValidVertices( Player* &player) ;
    // std::vector<Edge*> getValidEdges( Player* &player) ;

};


#endif //CATAN_ADJACENCYGRAPH_H