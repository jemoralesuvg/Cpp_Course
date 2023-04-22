#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

/******************************************************************************
Author: Jose Eduardo Morales
shortestPath.h
Date: march 22, 2023
*******************************************************************************/

#include "graph.h"
#include <vector>

class shortestPath{
    public:
        shortestPath();
        shortestPath(Graph g);  //contructor with input graph
        void calc(int x);       //calculates all distances and previous vertices
        bool connected(int y);  //check if x connects to y, must run calc first
        int dist(int y);        //returns the distance from x to y
        std::vector<int> path (int y);  //uses previous vertices to get path
        //int pathSize(int x, int y);
        void printPath();       // print path in format ex: n0->n3->n6
        void printAllPaths();   // print all info
        float avgDist();        // get average distance of paths to source
    private:
        Graph graph;
        int minDistanceIndex(std::vector<int> dist, std::vector<bool> checkDistance, int size);
        std::vector<int> distance;
        std::vector<bool> checkDistance;
        std::vector<int> route;
        std::vector<int> previousVertex;
        bool validPath;
        int source;
        int connectedVert = 0;
        int totalDist = 0;
        
};

#endif