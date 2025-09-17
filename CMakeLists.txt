cmake_minimum_required(VERSION 3.8)
project(Catan)

set(CMAKE_CXX_STANDARD 17)

ADD_EXECUTABLE(Catan src/main.cpp
        src/Player.cpp
        src/Player.h
        src/Structure.cpp
        src/Structure.h
        src/Tile.cpp
        src/Tile.h
        src/Vertex.cpp
        src/Vertex.h
        src/Edge.cpp
        src/Edge.h
        src/Card.cpp
        src/Card.h
        src/Resource.cpp
        src/Resource.h
        src/Robber.cpp
        src/Robber.h
        src/Deck.cpp
        src/Deck.h
        src/CardStack.cpp
        src/CardStack.h
        src/Road.cpp
        src/Road.h
        src/Building.cpp
        src/Building.h
        src/Settlement.cpp
        src/Settlement.h
        src/City.cpp
        src/City.h
        src/Port.cpp
        src/Port.h
)
add_executable(Tests test/testing.cpp)
