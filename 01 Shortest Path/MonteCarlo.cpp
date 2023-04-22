#include "MonteCarlo.h"
#include <random>
#include <limits>

/******************************************************************************
Author: Jose Eduardo Morales
MonteCarlo.cpp
Date: march 22, 2023
*******************************************************************************/
MonteCarlo::MonteCarlo()
{
    srand(time(0));
}

Graph MonteCarlo::randomGraph(int edges, float density, int maxDistance){
    Graph graph(edges);
    int row = 0;
    for(int i = 0; i < edges; i++){
        for (int j = 0; j < edges; j++){
            if ((j > row) && (rand()%100 < density * 100)){
                graph.add(i, j, 1 + rand()%maxDistance);
            }
        }
        row++;
        
    }
    return graph;
}