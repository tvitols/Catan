cmake_minimum_required(VERSION 3.13)
project(Catan)

set(CMAKE_CXX_STANDARD 20)


# Set required C++ standard.
set( CPPGRAPHICS_CXX_STANDARD 17 )

# Absolute path to cppgraphics directory. Leave empty for console app.
set( CPPGRAPHICS_CPPGRAPHICS_PATH "cppgraphics")

###############################################################################
###############################################################################


# Just for possible debugging:
message("Using CMake ${CMAKE_VERSION}")

include(GNUInstallDirs)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (default Release)" FORCE)
endif()


foreach (DIR ${PREFIX_PATH_CHECK})
    if (NOT EXISTS "${DIR}")
        message(FATAL_ERROR "CMAKE_PREFIX_PATH element doesn't exist: ${DIR}")
    endif ()
endforeach ()
message("CMAKE_PREFIX_PATH:${CMAKE_PREFIX_PATH}")

execute_process(COMMAND "git submodule init")
execute_process(COMMAND "git submodule update")
execute_process(COMMAND "echo 'Git submodules updated'")



file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/rules.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/info.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


file(COPY src/static/ DESTINATION static/)


set(TARGET_NAME "Catan")
set(LIST_OF_FILES src/main.cpp
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
        src/Port.cpp
        src/Port.h
        src/CustomUtils.h
        src/Info.h
        src/Info.cpp
        src/Board.cpp
        src/Board.h
        src/Game.cpp
        src/Game.h
        src/AdjacencyGraph.cpp
        src/AdjacencyGraph.h
        cppgraphics/src/cppgraphics.hpp
        cppgraphics/src/cppgraphics.cpp
        src/VictoryPointCard.h
        src/VictoryPointCard.cpp
        src/YearOfPlentyCard.cpp
        src/YearOfPlentyCard.h
        src/KnightCard.cpp
        src/KnightCard.h
        src/RoadBuilding.cpp
        src/RoadBuilding.h
        src/MonopolyCard.cpp
        src/MonopolyCard.h)

add_executable(${TARGET_NAME} ${LIST_OF_FILES})

if (NOT "${CPPGRAPHICS_CPPGRAPHICS_PATH}" STREQUAL "" )
    # First add cppgraphics include directory.
    target_include_directories(${TARGET_NAME} PRIVATE "${CPPGRAPHICS_CPPGRAPHICS_PATH}/src/")

    # Find OpenGL
    set(OpenGL_GL_PREFERENCE "GLVND")
    find_package(OpenGL REQUIRED)
    target_include_directories(${TARGET_NAME} PRIVATE "${OPENGL_INCLUDE_DIR}")
    target_link_libraries(${TARGET_NAME} "${OPENGL_LIBRARIES}")
    message("OpenGL found: ${OPENGL_LIBRARIES}")

    # Build deps
    if (WIN32)
        execute_process(COMMAND "${CPPGRAPHICS_CPPGRAPHICS_PATH}/deps/build_deps.bat" ${CMAKE_GENERATOR} ${CMAKE_C_COMPILER} ${CMAKE_CXX_COMPILER} WORKING_DIRECTORY "${CPPGRAPHICS_CPPGRAPHICS_PATH}/deps/")
    else()
        execute_process(COMMAND "sh" "${CPPGRAPHICS_CPPGRAPHICS_PATH}/deps/build_deps.sh" ${CMAKE_GENERATOR} ${CMAKE_C_COMPILER} ${CMAKE_CXX_COMPILER} WORKING_DIRECTORY "${CPPGRAPHICS_CPPGRAPHICS_PATH}/deps/")
    endif()

    # Find SDL2
    find_package(SDL2 2 CONFIG REQUIRED)
    target_link_libraries(${TARGET_NAME} SDL2::SDL2 )


    if (WIN32)
        # Add SDL2 dependencies (needed because it is statically linked)
        target_link_libraries(${TARGET_NAME} winmm setupapi version imm32)
    endif()
endif()

# Tell MSVC we don't want its Release/Debug folders.
if (MSVC)
    set_target_properties( ${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build )
    set_target_properties( ${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build )
    set_target_properties( ${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build )
endif()



# Enforce required standard on the target.
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_${CPPGRAPHICS_CXX_STANDARD})



# On Linux, make sure that pthread is found.
if (UNIX AND NOT APPLE)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries( ${TARGET_NAME} Threads::Threads)
endif()

add_executable(Tests test/testing.cpp)
