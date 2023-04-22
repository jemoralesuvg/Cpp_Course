/******************************************************************************
Hex game
Author: Jose Eduardo Morales
Date: april 11, 2023

*******************************************************************************/
#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>  //fill cout number fill
#include <stdlib.h>
#include <list>     // graph.h
#include <string>
#include <iterator> //shortestPath
#include <limits.h> //shortestPath
#include <chrono>
#include <thread>
#include <cmath>

using namespace std;


enum class PlayerColor {Blank, Red, Blue};
vector <vector <PlayerColor>> board;
int board_size;

ostream& operator << (ostream &out, const PlayerColor &ob)
{
    if(ob==PlayerColor::Blue)
        out<<"x";
    else if(ob==PlayerColor::Red)
        out<<"o";
    else out<< ".";

    return out;
}

template <typename T>
ostream& operator << (ostream & out, const vector< vector<T> > &matrix)
{
    out  << " " ;
    for (int x = 0; x < matrix.size(); ++x)
            out  << " " <<  static_cast<char>(x+65) ;
    out << endl;
    for(int i = 0 ; i < matrix.size(); i++)
    {
        out << string(i, ' ');
        out << setw(2) << setfill('0') << i + 1 << " ";
        for (int j = 0; j < matrix.at(i).size(); j++)
        {
            out<<  matrix[i][j]<<" ";
        }
        out << setw(2) << setfill('0') << i + 1 << endl;
    }
    out << string(matrix.size()+2, ' ');
    //for (int x = 0; x < matrix.size()+1; ++x) out << " " ;  
    for (int x = 0; x < matrix.size(); ++x)
            out  << " " << static_cast<char>(x+65) ;
    out << endl;
    return out;
}
void clear_screen(){
    #ifdef _WIN32
        system("cls");
    #elif _WIN64
        system("cls");
    #elif __linux__
        system("clear"); 
    #endif
}

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
        void add(int x, int y);
        void remove(int x, int y);      //removes edge from x to y
        int getEdge(int x, int y);
    
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
void Graph::add(int x, int y){ //add the edge from x to y
    graph[x][y] = 1;
    graph[y][x] = 1;    // make bidirectional edge
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

Graph board_connections;
int north, south, east, west;

class shortestPath{
    public:
        shortestPath();
        shortestPath(Graph g);  //contructor with input graph
        void calc(int x);       //calculates all distances and previous vertices
        void calc(int x, vector<bool> checkDistance);
        void calc(int x, vector<bool> my_moves, vector<bool> op_moves);
        bool connected(int y);  //check if x connects to y, must run calc first
        int dist(int y);        //returns the distance from x to y
        std::vector<int> path (int y);  //uses previous vertices to get path
        //int pathSize(int x, int y);
        void printPath();       // print path in format ex: n0->n3->n6
        void printAllPaths();   // print all info
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


template<typename T>
void printVector(const T& t) {
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, " -> "));
}

shortestPath::shortestPath(){
    
}

shortestPath::shortestPath(Graph g):graph(g){
    // get graph
    int size = graph.V();
    validPath = false;
    distance = std::vector<int> (size, INT_MAX) ; //init vector with max dist
    checkDistance = std::vector<bool> (size,true);//init vector with true 
}

int shortestPath::minDistanceIndex(std::vector<int> dist, std::vector<bool> checkDistance, int size){
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

void shortestPath::calc(int x){
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

void shortestPath::calc(int x, vector<bool> checkDistance){
    //init variables
    validPath = false;
    int size = graph.V();
    distance.clear();
    //checkDistance.clear();
    previousVertex.clear();
    route.clear();
    distance = std::vector<int> (size, INT_MAX) ;
    //checkDistance = std::vector<bool> (size,true);
    previousVertex = std::vector<int> (size, -1);
    source = x;
    
    int count_available = 0;
    for (int i = 0; i< checkDistance.size() ; ++i){
        if (checkDistance[i] == true){
            count_available++;
        }
    }
    //set source distance to zero
    distance.at(x) = 0;
    for(int j = 0; j < count_available; j++){ //checks once per vertex
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

void shortestPath::calc(int x, vector<bool> my_moves, vector<bool> op_moves){
    //init variables
    validPath = false;
    int size = graph.V();
    distance.clear();
    checkDistance.clear();
    previousVertex.clear();
    route.clear();
    distance = std::vector<int> (size, INT_MAX) ;
    checkDistance = std::vector<bool> (size, false);
    previousVertex = std::vector<int> (size, -1);
    source = x;
    
    //cout << "op moves size" << op_moves.size()<< endl;
    //cout << "check dist size" << checkDistance.size() << endl;
        //checkDistance = ~op_moves;
    //vector <bool> checkDistance (my_moves.size());
    int count_available = 0;
    for (int i = 0; i< op_moves.size() ; ++i){
        //cout << "i = " << i << endl;
        if (op_moves[i] == false){
            count_available++;
            checkDistance[i] = true;
        }
        
        //count_available++;
        //checkDistance[i] = !op_moves[i];
        //cout << "check dist " << checkDistance[i] << endl;
    }
    
    //set source distance to zero
    distance.at(x) = 0;
    for(int j = 0; j < count_available; j++){ //checks once per vertex
        //choose vertex K = minimun distance
        int k = minDistanceIndex(distance, checkDistance, size); 
        //cout << "K " << k << endl;
        checkDistance.at(k) = false; //processed
        for (int i = 0; i < size; i++){ //check all nodes connecter to k
            //checks if node is a valid minimun connetion
            if(distance.at(k) != INT_MAX &&  checkDistance.at(i) &&
            distance.at(k) + (graph.getEdge(k,i)*(my_moves[k]?1:10)) < distance.at(i) &&
            graph.getEdge(k,i) != 0){
                //update minimun distance
                distance.at(i) = distance.at(k) + (graph.getEdge(k,i)*(my_moves[k]?1:10));
                //save previous vertex to later recreate shortest path
                previousVertex.at(i) = k;
            }
        }
        
    }
    return;
}
bool shortestPath::connected(int y){
    return (distance.at(y) < INT_MAX);
}


int shortestPath::dist(int y){
    if (connected(y))
        return distance.at(y);
    else
        return -1;
}

std::vector<int> shortestPath::path (int y){
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

void shortestPath::printPath() {
    if (validPath){
        for (int i : route){
            if (i == graph.V()-4)
                std::cout << "north -> ";
            else if (i == graph.V()-3)
                std::cout << "south -> ";
            else if (i == graph.V()-2)
                std::cout << "east -> ";
            else if (i == graph.V()-1)
                std::cout << "west -> ";
            else {
                int val = sqrt(graph.V()-4);
                std::cout << static_cast<char>(i/val + 'A') << i%val +1<< " -> ";
            }
        }
        std::cout << "\b\b\b   " ; // delete last ->
    }
    /*
    else{
        std::cout << "no valid path ";// << std::endl;
    }*/
}
      
void shortestPath::printAllPaths() {
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


vector<bool> blue_spaces;
vector<bool> red_spaces;

void create_board(){
    int graph_size = board_size*board_size+4;
    red_spaces = vector<bool> (graph_size, false);
    blue_spaces = vector<bool> (graph_size, false);
    //for(int i = graph_size-4; i < graph_size; ++i){
      red_spaces[graph_size-4] = true; //connect to N
      red_spaces[graph_size-3] = true; //connect to S
      blue_spaces[graph_size-2] = true; //connect to W
      blue_spaces[graph_size-1] = true; //connect to E
    //} 
    
    board_connections = Graph(graph_size);  
    board = vector< vector <PlayerColor>> (board_size, vector<PlayerColor> (board_size, PlayerColor::Blank));
    
    int size = board_size;//rename for shorter access
    north = size*size;
    south = north + 1;
    east = south + 1;
    west = east + 1;
    //populate connections graph
    for(int i=0;i<size;++i)
    {
        for(int j=0;j<size;++j)
        {
            if (j==0){
                board_connections.add(i*size+j, i*size + j +1);
                if ((i+1)*size + j + 1< graph_size)
                    board_connections.add(i*size+j, (i+1)*size + j );
            }
            else if(j < size - 1)
            {
                board_connections.add(i*size+j, i*size + j + 1);
                if ((i+1)*size + j -1< graph_size)
                    board_connections.add(i*size+j, (i+1)*size + j - 1);
                if ((i+1)*size + j < graph_size)
                    board_connections.add(i*size+j, (i+1)*size + j );
                
            }
            else{
                if ((i+1)*size + j -1< graph_size)
                    board_connections.add(i*size+j, (i+1)*size + j -1);
                if ((i+1)*size + j < graph_size)
                    board_connections.add(i*size+j, (i+1)*size + j );
            }
            
           
        }
    }
    for(int i=0; i<size*size+4;++i) //remove additional connections
    {
        for(int j=0;j<size*size+4;++j){
            if(j >= size*size || i >= size*size)
                board_connections.remove(i,j);
        }
    }
    //connect north south east west
    for (int i = 0; i < size; ++i){
            board_connections.add(north, i*size);
            board_connections.add(south, (i+1)*size - 1);
            board_connections.add(east, i+(size*(size-1)));
            board_connections.add(west, i);
    }
    //board_connections.print();
}

void get_board_size(){
    cout<<"Enter the board size (4 - 11)";
    cin>>board_size;
    while (board_size > 11 || board_size < 4) {
        cout << "try other number (4 - 11)";
        cin>>board_size;
    } 
    create_board();
}

void get_input(PlayerColor Color){
    if (Color == PlayerColor::Blue){
        cout << "Player Blue - " << PlayerColor::Blue << endl;
        cout << "West - East " << endl;
        cout << " ---> " << endl;
    }
    else{
        cout << "\\Player 2 - " << PlayerColor::Red << endl;
        cout << " \\ North - South " << endl;
        cout << "  \\" << endl;
        cout << "   *" << endl;
    }
    string input;
    cout << "Make your move (ie A1): ";
    cin >> input;
    
    char letter = input[0];
    
    int col = input[0] - 'A';
    int row = stoi(input.substr(1)) - 1;
    
    while (board[row][col] != PlayerColor::Blank || row > board_size || col > board_size){
        cout << "Invalid move - ";
        cout << "Make another move (ie A1): ";
        cin >> input;
        
        letter = input[0];
        
        col = input[0] - 'A';
        row = stoi(input.substr(1)) - 1;
    }
    
    board[row][col] = Color;  
    if(Color == PlayerColor::Red)
        red_spaces[col*board_size + row] = true;
    else
        blue_spaces[col*board_size + row] = true;
    
    
   
}
void ai_first_move(){
    int pos = board_size/2;
    board[pos][pos] = PlayerColor::Red;  
    red_spaces[pos*board_size + pos] = true;
    cout << "AI first move" << endl;
}
void ai_move(){
    cout << "AI thinking" << flush;
    cout << endl;
    /*
    for (auto i : blue_spaces){
        cout << "space blue" << i << endl; // " = " << red_spaces[i] << endl;
    }*/
    //cout << red_spaces << endl;
    
    this_thread::sleep_for(chrono::milliseconds(600));
    cout << "."<< flush;
    this_thread::sleep_for(chrono::milliseconds(600));
    cout << "."<< flush;
    this_thread::sleep_for(chrono::milliseconds(600));
    cout << "."<< flush;
    this_thread::sleep_for(chrono::milliseconds(600));
    cout << endl;
    
    
    shortestPath sp(board_connections);
    sp.calc(north, red_spaces, blue_spaces);
    vector<int> path_temp = sp.path (south);
    sp.printPath();
    
    //cout << "here 2" << endl;
    vector<int> path (path_temp.size());
    int n = path.size()/2;
    int count = 0;
    int middle =path.size()/2;
    for (int offset = 0; offset <= middle; offset++) {
        if (offset == 0) {
            path[count] = path_temp[ middle];
            count++;
        } else {
            if (count < path.size())
                path[count] = path_temp[(middle + offset)%path.size()];
            count++;
            if (count < path.size())
                path[count] = path_temp[(middle - offset)%path.size()];
            count++;
        }
    }
    for(auto i : path)
        cout << i << endl;
    /*
    int count = 0;
    for(int i = n-1; i >= -n+1; --i) {
        count++;
        int j = n - std::abs(i);
        path[count] = path_temp[j % path.size()];
    }*/
    //int displace = path.size()*3/4; 
    //for(int i = 0; i < path.size() ; i++)
    //    path[ (i + displace )%path.size()] = path_temp[i];
    
    //board_connections.print();
    for (int i : path){
        if ( i < board_size*board_size ){
            // << "board size " << board_size << endl;
            cout << "Posible AI move: " << i << " " << static_cast<char>(i/board_size + 'A') << i%board_size +1 << endl;
            if (board[i%board_size][i/board_size] == PlayerColor::Blank ){
                board[i%board_size][i/board_size]= PlayerColor::Red;
                red_spaces[i] = true;
                cout << "AI move: " << static_cast<char>(i/board_size + 'A') << i%board_size +1 << endl;
                break;
            }
        }
    }
    
}

int main()
{
    cout<<"HEX GAME" << endl;
    get_board_size();
    //clear_screen();
    
    cout << board;
    
    ai_first_move();
    cout << board;
    while (1) {
        
        
        get_input(PlayerColor::Blue);
        cout << board;
        
        shortestPath sp_blue(board_connections);
        sp_blue.calc(east, blue_spaces);
        sp_blue.path(west);
        sp_blue.printPath();
        if (sp_blue.connected(west)){
            cout << "Player wins" << endl;
            break;
        }
        
        
        ai_move();
        cout << board;
        
        shortestPath sp_red(board_connections);
        sp_red.calc(north, red_spaces);
        if (sp_red.connected(south)){
            cout << "AI  wins" << endl;
            break;
        }
    }
    
    //clear_screen();
    //cout << board;
    //cout<<"Hi " << endl << static_cast<char>(01) ;
    //cout << "jose" << endl;
    //cout<<'\b';  //Cursor moves 1 position backwards
    //cout<<" ";   //Overwrites letter 'i' with space
    
    //clear_screen();
    return 0;
}


