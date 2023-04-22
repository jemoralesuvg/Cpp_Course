#ifndef MONTECARLO_H
#define MONTECARLO_H

/******************************************************************************
Author: Jose Eduardo Morales
MonteCarlo.h
Date: march 22, 2023
*******************************************************************************/

#include "graph.h"

class MonteCarlo{
    public:
        MonteCarlo(); //constructor creates random seed
        Graph randomGraph(int edges, float density, int maxDistance);
        //void shortestPath();
};

#endif