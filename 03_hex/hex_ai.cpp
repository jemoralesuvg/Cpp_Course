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
#include <random> //ai move

using namespace std;

enum class PlayerColor {Blank, Red, Blue};  //player color class
vector <vector <PlayerColor>> board;        //board matrix
int board_size;                             //board size
int north, south, east, west;
vector<bool> blue_spaces;
vector<bool> red_spaces;
Graph board_connections;
default_random_engine  e(time(nullptr));
uniform_int_distribution <char> distribution(0, 1);

ostream& operator << (ostream &out, const PlayerColor &ob){
    if(ob==PlayerColor::Blue)
        out<<"x";
    else if(ob==PlayerColor::Red)
        out<<"o";
    else out<< ".";

    return out;
}

//template <typename T>       //Print board matrix 
//ostream& operator << (ostream & out, const vector< vector<T> > &matrix)
ostream& operator << (ostream & out, const vector< vector<PlayerColor> > &matrix){
    out  << "\n " ;
    for (int x = 0; x < matrix.size(); ++x)
            out  << " " <<  static_cast<char>(x+65) ;
    out << endl;
    for(int i = 0 ; i < matrix.size(); i++){
        out << string(i, ' ');
        out << setw(2) << setfill('0') << i + 1 << " ";
        for (int j = 0; j < matrix.at(i).size(); j++)
            out<<  matrix[i][j]<<" ";
        out << setw(2) << setfill('0') << i + 1 << endl;
    }
    out << string(matrix.size()+2, ' ') ; 
    for (int x = 0; x < matrix.size(); ++x)
            out  << " " << static_cast<char>(x+'A') ;
    out << endl;
    return out;
}
void clear_screen(){ //clear screen function for windows and linux
    #ifdef _WIN32
        system("cls");
    #elif _WIN64
        system("cls");
    #elif __linux__
        system("clear"); 
    #endif
}
//------------------------------------------------------------------------------
class Graph {
    protected:
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
        void add(int x, int y, int value); //add the edge from x to y
        void remove(int x, int y);      //removes edge from x to y
        int getEdge(int x, int y);
};

Graph::Graph(){};
//construct that creates an empty graph with size as a parameter

Graph::Graph (int size):m_size(size) { //constructor
    if (m_size == 0)
        std::cout << "error initializing graph at 0" << std::endl;
        
    graph = new int*[m_size]; 
    for (int i = 0; i < m_size; i++)
        graph[i] = new int[m_size];
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

void Graph::add(int x, int y, int value = 1){ //add the edge from x to y
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

//------------------------------------------------------------------------------
class shortestPath{
    public:
        shortestPath();
        shortestPath(Graph g);  //contructor with input graph
        void calc(int x);       //calculates all distances and previous vertices
        void calc(int x, vector<bool> checkDistance);
        bool connected(int y);  //check if x connects to y, must run calc first
        int dist(int y);        //returns the distance from x to y
        std::vector<int> path (int y);  //uses previous vertices to get path
        void printPath();       // print path in format ex: n0->n3->n6
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
        if (dist[i] <= min && checkDistance[i]){
            min = dist[i];
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
    
    // get the number of vertices to check
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
        checkDistance[k] = false; //processed
        for (int i = 0; i < size; i++){ //check all nodes connecter to k
            //checks if node is a valid minimun connetion
            if(graph.getEdge(k,i) && distance[k] != INT_MAX &&  checkDistance[i]){
                int sum = distance[k] + 1;
                if( sum < distance[i] ){
                    //update minimun distance
                    distance[i] = sum ;//graph.getEdge(k,i); //only edges = 1 for now
                    //save previous vertex to later recreate shortest path
                    previousVertex[i] = k;
                }
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

//------------------------------------------------------------------------------

void create_board(){ //setup board, connections and moves
    int graph_size = board_size*board_size+4;
    int size = board_size;//rename for shorter access
    board_connections = Graph(graph_size);  
    board = vector< vector <PlayerColor>> (board_size, vector<PlayerColor> (board_size, PlayerColor::Blank));
    
    //vector of player moves to use in shortest path valid edges
    red_spaces = vector<bool> (graph_size, false); 
    blue_spaces = vector<bool> (graph_size, false);
    red_spaces[graph_size-4] = true; //connect to N
    red_spaces[graph_size-3] = true; //connect to S
    blue_spaces[graph_size-2] = true; //connect to W
    blue_spaces[graph_size-1] = true; //connect to E
    
    // set positions of north, south, east and west edges on graph
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
    for(int i=0; i<size*size+4;++i) //remove posible additional connections
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
int starting_player = 0;
void get_board_size(){ //ask the user for the desired board size
    cout<<"Enter the board size (4 - 11)";
    cin>>board_size;
    while (board_size > 11 || board_size < 4) {
        cout << "try other number (4 - 11)";
        cin>>board_size;
    } 
    create_board();
}
void get_starting_player(){
    while(1){
        cout << "Who will start (1/2)\n\t1. Player \n\t2. AI" << endl;   
        string input;
        cin >> input;
        try{
            starting_player = static_cast<int>(input[0]) - '0';
            if (starting_player == 1 || starting_player == 2)
                return;
            else
                cout << "enter a number between 1 and 2" << endl;
        }
        catch (...) {
            cout << "not a valid input" << endl;
        }
    }
}

void get_input(PlayerColor Color){ //get player move
    //print the corresponding direction of the player
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
    
    //get player input
    cout << "Make your move (ie A1): ";
    cin >> input;
    
    char letter = input[0];
    
    //validate input
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
    
    // record player move
    board[row][col] = Color;  
    if(Color == PlayerColor::Red)
        red_spaces[col*board_size + row] = true;
    else
        blue_spaces[col*board_size + row] = true;
}

void ai_move(){
    cout << "AI thinking" << flush;
    cout << endl;
    int lineal_size = board_size*board_size;
    int attemps = 400;
    vector <int> total_wins = vector <int> (lineal_size, 0);
    int max_wins_pos = 0;
    for (int pos = 0; pos < lineal_size; pos++){
        if(!red_spaces[pos]&&!blue_spaces[pos]){
            for (int k = 0; k < attemps; k++){
                vector<bool> sim_red_moves = red_spaces;
                vector<bool> sim_blue_moves = blue_spaces;
                sim_red_moves[pos] = true;
                for (int i = 0; i < sim_red_moves.size(); i++){
                    if ( !sim_red_moves[i] && !sim_blue_moves[i]){
                        sim_red_moves[i] = static_cast<bool> (distribution(e));
                        sim_blue_moves[i] = !sim_red_moves[i];
                    }
                }
                
                shortestPath sp_red(board_connections);
                sp_red.calc(north, sim_red_moves);
                if (sp_red.connected(south)){ 
                    total_wins[pos]++;
                }
            }
        }
        if (total_wins[max_wins_pos] < total_wins[pos])
            max_wins_pos = pos;
    }
    
    int i = max_wins_pos;
    cout << "AI move best: " << static_cast<char>(i/board_size + 'A') << i%board_size +1 << endl;
    cout << "Estimated win %: " << static_cast<float>(total_wins[max_wins_pos])/attemps * 100<< endl;
    board[i%board_size][i/board_size]= PlayerColor::Red;
    red_spaces[i] = true;
}

int main()
{
    cout<<"HEX GAME" << endl;
    get_board_size();
    get_starting_player();
    clear_screen();
    
    cout << "HEX GAME" << endl;
    cout << board;
    
    if (starting_player == 2) {
        cout << "AI is starting" << endl; 
        ai_move();
        cout << board;
    }
    
    while (1) {
         //player move
        get_input(PlayerColor::Blue);
        cout << board;
        
        //test if player 1 wins
        shortestPath sp_blue(board_connections);
        sp_blue.calc(east, blue_spaces);
        sp_blue.path(west);
        sp_blue.printPath();
        if (sp_blue.connected(west)){
            cout << "Player wins" << endl;
            break;
        }
        
        //AI move
        ai_move();
        cout << board;
        
        //test if AI wins
        shortestPath sp_red(board_connections);
        sp_red.calc(north, red_spaces);
        if (sp_red.connected(south)){
            cout << "AI  wins" << endl;
            break;
        }
    }
    return 0;
}


