#ifndef GRAPH_H
#define GRAPH_H
/******************************************************************************
Author: Jose Eduardo Morales
graph.h
Date: march 22, 2023
*******************************************************************************/
#include <list>

class Graph {

    private:
        int m_size;
        int ** graph;
        template <typename T>
        void printGraph(T** graph, int rows, int cols) ;
        
    public:
        Graph ();
        Graph (int size);
        ~Graph();
        void print();
        int V();                        //return the # of vertices in the Graph
        int E();                        //return the # of edges in the Graph
        bool adjacent(int x, int y);    //test if there is an edge from x to y
        std::list<int> neighbors(int x); // list all nodes y from x
        void add(int x, int y, int value); //add the edge from x to y
        void remove(int x, int y);      //removes edge from x to y
        int getEdge(int x, int y);
        float getDensity();
        /*
        int get_node_value(int x);
        void set_node_value(int x, char a);
        void set_edge_value(int x, int y, int value);*/
    
};
#endif