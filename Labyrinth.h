#pragma once
#include "Queue.h"
#include "Stack.h"

#include <iostream>
using std::string;

// Legend: X=0, *=1, R=10, Edge=5;
class Labyrinth {
private:
    char* labyrinth;
    int rows;
    int cols;
    int robotPosition;

public:
    Labyrinth(const string& fileName = "beispiel.txt");

    ~Labyrinth();

    // a
    bool pathExistenceCheck();

    // b & c
    void shortestPath();

    void printLabyrinth();

};

