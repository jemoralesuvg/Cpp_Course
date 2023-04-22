/******************************************************************************
Shortest route implemented with digikstras algorithm using matrices
Author: Jose Eduardo Morales
Date: march 20, 2023
*******************************************************************************/

#include <iostream>
#include <list>
#include <random>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>
#include <sstream>
#include <numeric>

using namespace std;

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

Graph::Graph(){};
//construct that creates an empty graph with size as a parameter

Graph::Graph (int size):m_size(size) { //constructor

    if (m_size == 0){
        std::cout << "error initializing graph at 0" << std::endl;
    }
        
    graph = new int*[m_size]; 
    for (int i = 0; i < m_size; i++)
        graph[i] = new int[m_size];
        
    //std::cout << "graph created" << std::endl;
    
}
Graph::~Graph(){ // destructor
    //std::cout << "destroying graph" << std::endl;
}

template <typename T>
void Graph::printGraph(T** graph, int rows, int cols) {
    //print titles
    std::cout << "\t";
    for(int i = 0; i < cols; ++i)
    {
        std::cout << "n" << i << "\t" ;
    }
    //print content
    std::cout << std::endl;
    for(int i = 0; i < rows; ++i) {
        std::cout << "n" << i << "\t";
        for(int j = 0; j < cols; ++j) {
            std::cout << graph[i][j] << " \t";
        }
        std::cout << std::endl;
    }
}
// public print
void Graph::print(){
    printGraph(graph, m_size, m_size);
    
}

int Graph::V(){       //return the # of vertices in the Graph
    return m_size;
}

int Graph::E(){       //return the # of edges in the Graph
    int count_E = 0;
    for(int i = 0; i < m_size; ++i) {
        for(int j = 0; j < m_size; ++j) {
            if ( graph[i][j] > 0)
                count_E ++;
        }
    }
    return count_E;
}

bool Graph::adjacent(int x, int y){ //test if there is an edge from x to y
    return (graph[x][y] > 0);
}

std::list<int> Graph::neighbors(int x){ // list all nodes y with edges to x
    std::list<int> neigbhborsToX = {};
    
    for(int i = 0; i < m_size; ++i) {
        if ( graph[x][i] > 0)
            neigbhborsToX.push_back(i);
    }
    return neigbhborsToX;
}

void Graph::add(int x, int y, int value){ //add the edge from x to y
    graph[x][y] = value;
    graph[y][x] = value;    // make bidirectional edge
}

void Graph::remove(int x, int y){ //removes edge from x to y
    graph[x][y] = 0;
    graph[y][x] = 0;        // bidirectional edge
}

int Graph::getEdge(int x, int y){
    return graph[x][y];
}

float Graph::getDensity(){
    return static_cast<float>(E())*100.0/(V()*(V()-1));
}

class graphReader{
    public:
    graphReader();
    Graph readGraph(string fname);
    
    private:
};
graphReader::graphReader(){ // constructor
    
}
Graph graphReader::readGraph(string fname){
    int graphSize = 0;
    string line;
    ifstream myfile;
    myfile.open(fname);
    Graph g;
    if(myfile.is_open()){
        cout << "graph opened \nsize: ";
        getline(myfile, line);
        graphSize = stoi(line);
        if (graphSize>0)
            g = Graph(graphSize);
        else
            return g;
        cout << graphSize << endl;
        string token;
        vector<int> tokens;
        while (myfile){
            getline(myfile, line);
            istringstream iss(line);
            while (iss >> token){
                tokens.push_back(stoi(token));
            }
            if (tokens.size() == 3)
                g.add(tokens.at(0), tokens.at(1), tokens.at(2));
            else
                return g;
            tokens.clear();
            
            //cout << line << endl;
        }
        return g;
    }
    else{
        cout << "couldn't open file";
    }
    return g;
}


class GraphProc{
    public:
        GraphProc();
        GraphProc(Graph g);  //contructor with input graph
        void calc(int x);       //calculates all distances and previous vertices
        bool connected(int y);  //check if x connects to y, must run calc first
        int dist(int y);        //returns the distance from x to y
        std::vector<int> path (int y);  //uses previous vertices to get path
        void printPath();       // print path in format ex: n0->n3->n6
        void printAllPaths();   // print all info
        float avgDist();        // get average distance of paths to source
        void printMST();
        void primMST();
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
        std::vector<int> parent;
        
};


template<typename T>
void printVector(const T& t) {
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, " -> "));
}

// print the parrent vector with it's distances and total sum
void GraphProc::printMST()
{
    cout << "\nPrim's MST: " << endl;
    int sum = 0;
    cout << "Edge \tWeight\n";
    for (int i = 1; i < graph.V(); i++){
        cout << i << "\t - \t" << parent.at(i) << " \t"
             << graph.getEdge(i,parent.at(i)) << " \n";
        sum += graph.getEdge(i,parent.at(i)); //get sum
    }
    
    cout << "\nTotal distance: " << sum <<endl;
}


void GraphProc::primMST(){
    int size = graph.V();
    parent.clear();
    parent = std::vector<int> (size, -1);
    
    distance.clear();
    checkDistance.clear();
    previousVertex.clear();
    route.clear();
    distance = std::vector<int> (size, INT_MAX) ;
    checkDistance = std::vector<bool> (size,true);
    previousVertex = std::vector<int> (size, -1);
    source = 0;
    
    //set source distance to zero
    distance.at(0) = 0;
    for(int j = 0; j < size - 1; j++){ //checks once per vertex
        //choose vertex K = minimun distance
        int k = minDistanceIndex(distance, checkDistance, size); 
        checkDistance.at(k) = false; //processed
        for (int i = 0; i < size; i++){ //check all nodes connecter to k
            //checks if node is a valid minimun connetion
            if(graph.getEdge(k,i) && checkDistance.at(i) 
                &&  graph.getEdge(k,i) < distance.at(i) ){
                    parent.at(i) = k;
                    distance.at(i) = graph.getEdge(k,i);
                }
        }
        
    }
    printMST();
    //std::cout << std::end << << std:endl;
    return;
}

GraphProc::GraphProc(){
    
}

GraphProc::GraphProc(Graph g):graph(g){
    // get graph
    int size = graph.V();
    validPath = false;
    distance = std::vector<int> (size, INT_MAX) ; //init vector with max dist
    checkDistance = std::vector<bool> (size,true);//init vector with true 
}

int GraphProc::minDistanceIndex(std::vector<int> dist, std::vector<bool> checkDistance, int size){
    int min = INT_MAX; //start min value at infinite
    int index;
    //find the minimun distance
    for (int i = 0; i < size; i++){
        if (dist.at(i) <= min && checkDistance.at(i)){
            min = dist.at(i);
            index = i;
        }
    }
    return index;
}

void GraphProc::calc(int x){
    //init variables
    validPath = false;
    int size = graph.V();
    distance.clear();
    checkDistance.clear();
    previousVertex.clear();
    route.clear();
    distance = std::vector<int> (size, INT_MAX) ;
    checkDistance = std::vector<bool> (size,true);
    previousVertex = std::vector<int> (size, -1);
    source = x;
    
    //set source distance to zero
    distance.at(x) = 0;
    for(int j = 0; j < size - 1; j++){ //checks once per vertex
        //choose vertex K = minimun distance
        int k = minDistanceIndex(distance, checkDistance, size); 
        checkDistance.at(k) = false; //processed
        for (int i = 0; i < size; i++){ //check all nodes connecter to k
            //checks if node is a valid minimun connetion
            if(distance.at(k) != INT_MAX &&  checkDistance.at(i) &&
            distance.at(k) + graph.getEdge(k,i) < distance.at(i) &&
            graph.getEdge(k,i) != 0){
                //update minimun distance
                distance.at(i) = distance.at(k) + graph.getEdge(k,i);
                //save previous vertex to later recreate shortest path
                previousVertex.at(i) = k;
            }
        }
        
    }
    return;
}

bool GraphProc::connected(int y){
    return (distance.at(y) < INT_MAX);
}


int GraphProc::dist(int y){
    if (connected(y))
        return distance.at(y);
    else
        return -1;
}

std::vector<int> GraphProc::path (int y){
    validPath = false;
    route.clear();
    if (connected(y)){ //checks if vertex y is connected to source x
        int i = y;
        while (i != source){ //loop back from vertex y all the way to source
            route.push_back(i); // save route
            i = previousVertex.at(i);
        }
        route.push_back(source); //save source vertex
        std::reverse(route.begin(), route.end());   //reverse the order
        validPath = true;
        return route;
    }
    else{
        return std::vector<int> (0); 
    }
}

void GraphProc::printPath() {
    if (validPath){
        for (int i : route){
            std::cout << "n" << i << " -> ";
        }
        std::cout << "\b\b\b   " ; // delete last ->
    }
    else{
        std::cout << "no valid path ";// << std::endl;
    }
}
      
void GraphProc::printAllPaths() {
    connectedVert = 0;
    totalDist = 0;
    std::cout << "DISTANCES FROM n" << source << std::endl;
    std::cout << "Vertex \tDist \tPath" << std::endl;
    for (int i = 0; i < graph.V(); i++){
        std::cout << "n" << i << "\t";
        if (connected(i)){
            totalDist += dist(i);
            std::cout << dist(i) << "\t";
            std::vector<int> ipath = path(i);
            printPath();
            std::cout << std::endl;
            connectedVert++;
        }
        else{
            std::cout << "not connected" << std::endl;
        }
        
    }
}
float GraphProc::avgDist(){
    return static_cast<float>(totalDist) / connectedVert;
}

const char* txt0 = "Author: Jose Eduardo Morales \nMinimun Spanning Tree - main.cpp\nDate: march 27, 2023\n";

int main() {
    cout << txt0 << endl;
//    cout << txt1 << endl;
    
    graphReader reader;
    Graph g = reader.readGraph("graph_test.txt");
    g.print();
    
    GraphProc proc(g);
    proc.primMST();
    

    return 0;
}

