//
// Created by tvito on 10/2/2025.
//

#include <set>

#include "AdjacencyGraph.h"


AdjacencyGraph::AdjacencyGraph(Board* pBoard) {

    for (const auto& tiles : pBoard->getTiles()) {
        for (const auto tile : tiles) {
            for (int i = 0; i < 6; i++) {
                edgeKeyedAdjacencyList[tile->getEdge(i)].push_back(tile->getVertex(i));
                edgeKeyedAdjacencyList[tile->getEdge(i)].push_back(tile->getVertex((i+1)%6));
                vertexKeyedAdjacencyList[tile->getVertex(i)].push_back(tile->getEdge(i));
                vertexKeyedAdjacencyList[tile->getVertex(i)].push_back(tile->getEdge(i-1));
            }
        }
    }
}

bool AdjacencyGraph::isAdjacent( Edge* &edge1,  Edge* &edge2)  {
    for (auto vertex : edgeKeyedAdjacencyList[edge1]) {
        if (std::count(vertexKeyedAdjacencyList[vertex].begin(),vertexKeyedAdjacencyList[vertex].end(),edge2) != 0) {
            return true;
        }
    }
    return false;
}

bool AdjacencyGraph::isAdjacent( Edge *&edge,  Vertex* &vertex)  {
    if (std::count(vertexKeyedAdjacencyList[vertex].begin(),vertexKeyedAdjacencyList[vertex].end(),edge) != 0) {
        return true;
    }
    return false;
}

bool AdjacencyGraph::isAdjacent( Vertex* &vertex1,  Vertex *&vertex2)  {
    for (auto edge : vertexKeyedAdjacencyList[vertex1]) {
        if (std::count(edgeKeyedAdjacencyList[edge].begin(),edgeKeyedAdjacencyList[edge].end(),vertex2) != 0) {
            return true;
        }
    }
    return false;
}

std::vector<Vertex *> AdjacencyGraph::getAdjacentVertices( Edge *&edge)  {
    return edgeKeyedAdjacencyList[edge];
}

std::vector<Vertex *> AdjacencyGraph::getAdjacentVertices(Vertex* &vertex){
    std::set<Vertex *> adjacentVertices;
    for ( auto edge : vertexKeyedAdjacencyList[vertex]) {
        std::vector<Vertex *> v = edgeKeyedAdjacencyList[edge];
        if (v.size() != 0) {
            adjacentVertices.insert(v.begin(), v.end());
        }
    }
    return std::vector<Vertex *>(adjacentVertices.begin(),adjacentVertices.end());
}

std::vector<Edge *> AdjacencyGraph::getAdjacentEdges(Edge *&edge) {
    std::set<Edge *> adjacentEdges;
    for ( auto vertex : edgeKeyedAdjacencyList[edge]) {
        std::vector<Edge*> e = vertexKeyedAdjacencyList[vertex];
        if (e.size() != 0) {
            adjacentEdges.insert(e.begin(), e.end());
        }
    }
    return std::vector<Edge *>(adjacentEdges.begin(),adjacentEdges.end());
}

std::vector<Edge *> AdjacencyGraph::getAdjacentEdges( Vertex *&vertex)  {
    return vertexKeyedAdjacencyList[vertex];
}

bool AdjacencyGraph::checkEdge(Edge *&pEdge, Player *&player) {
    const std::vector<Vertex *> v = getAdjacentVertices(pEdge);
    for (const auto vertex : v) {
        if (vertex->isOccupied() && (vertex->getBuilding()->getOwner() == player)) {
            return true;
        }
    }
    const std::vector<Edge *> edges = getAdjacentEdges(pEdge);
    for (const auto edge : edges) {
        if (edge != pEdge && edge->isOccupied() && edge->getRoad()->getOwner() == player) {
            return true;
        }
    }
    return false;
}

bool AdjacencyGraph::checkVertex( Vertex *&pVertex,  Player *&player,  bool setup)  {
    const std::vector<Vertex *> adjacentVertices = getAdjacentVertices(pVertex);
    for ( auto vertex : adjacentVertices) {
        if (vertex->isOccupied()) {
            return false;
        }
        const std::vector<Vertex *> secondaryVertices = getAdjacentVertices(vertex);
        for (const auto v : secondaryVertices) {
            if (v == nullptr || v == pVertex) {
                continue;
            }
            if (v->isOccupied()) {
                return false;
            }
        }
    }
    if (!setup) {
        const std::vector<Edge *> adjacentEdges = getAdjacentEdges(pVertex);
        for (const auto edge : adjacentEdges) {
            if (edge->isOccupied() && edge->getRoad()->getOwner() == player) {
                return true;
            }
        }
        return false;
    }

    return true;
}

