/******************************************************************************
Author: Jose Eduardo Morales
main.cpp
Shortest route implemented with digikstras algorithm using matrices
Date: march 20, 2023
*******************************************************************************/

#include <iostream>
#include <list>
#include "graph.h"
#include "MonteCarlo.h"
#include "shortestPath.h"

using namespace std;

int main() {
    Graph g;    // create empty graph
    MonteCarlo sim; //create a random graph
    
    // 50 vertices, 20% density, 10 max distance
    const int vertices = 50;
    float density = 0.20;
    const int maxDistance = 10;
    g = sim.randomGraph(vertices, density, maxDistance);
    cout << "new random graph created" << endl;
    //g.print();
    const int src = 0;  //shortest path source Vertex
    shortestPath sp(g); //send graph
    sp.calc(src);       //calculate distances to src
    sp.printAllPaths(); //print all distances and paths
    //print density and avg distance
    cout << "Avg. Density = " << g.getDensity() << "%" << endl;
    cout << "Avg. Distance= " << sp.avgDist() << endl; 
    
    
    // 50 vertices, 40% density, 10 max distance
    density = 0.40;
    g = sim.randomGraph(vertices, density, maxDistance);
    cout << "new random graph created" << endl;
    //g.print();
    sp = shortestPath(g);
    sp.calc(src);       //calculate distances to src
    sp.printAllPaths(); //print all distances and paths
    cout << "Avg. Density = " << g.getDensity() << "%" << endl;
    cout << "Avg. Distance= " << sp.avgDist() << endl; 
    
    return 0;
}