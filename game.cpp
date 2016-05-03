#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
#include "Game.h"


/*****************************************************************************************
 * constructors
 ****************************************************************************************/
 
//constructor
Game::Game(string filename) {
  this->read_from_file(filename);
}

Game::Game() {
}

Game::~Game() {
  delete graph;
}

/*****************************************************************************************
 * input / output
 ****************************************************************************************/
 
//reading game from file
void Game::read_from_file(string filename) {

  ifstream myfile;
  
  myfile.open(filename);
  
  myfile >> size; 
  myfile >> ladder_count; 
  myfile >> snake_count;
  
  int i, number;
  
  i = ladder_count;
  while(i--) {
    myfile >> number;
    ladder_start.push_back(number);
    myfile >> number;
    ladder_end.push_back(number);
  }
  
  i = snake_count;
  while(i--) {
    myfile >> number;
    snake_start.push_back(number);
    myfile >> number;
    snake_end.push_back(number);
  }
  
  myfile.close();
  
}

//reading game from standard input
void Game::read_from_stdin() {

  cin >> size; 
  cin >> ladder_count; 
  cin >> snake_count;
  
  int i, number;
  
  i = ladder_count;
  while(i--) {
    cin >> number;
    ladder_start.push_back(number);
    cin >> number;
    ladder_end.push_back(number);
  }
  
  i = snake_count;
  while(i--) {
    cin >> number;
    snake_start.push_back(number);
    cin >> number;
    snake_end.push_back(number);
  }
  
}


void Game::print_to_stdout() {

  //first line
  cout << size << " " << ladder_count << " " << snake_count << endl;
  
  //second line (ladders)
  int i;
  for(i = 0; i < ladder_count; i++) {
    cout << ladder_start[i] << " " << ladder_end[i] << " ";
  }
  cout << endl;
  
  //third line (snakes)
  for(i = 0; i < snake_count; i++) {
    cout << snake_start[i] << " " << snake_end[i] << " ";
  }
  cout << endl;
   
}

/*****************************************************************************************
 * converting game to graph
 ****************************************************************************************/
 
void Game::construct_graph() {

  //number of nodes in graph
  int n = size * size;
  
  //construct graph
  graph = new Graph(n);
  
  //add graph edges
  int i;
  
  //add ladders
  for(i = 0; i < ladder_count; i++) {
    graph->add_edge(ladder_start[i], ladder_end[i], 1);
  }
    
  //add snakes 
  for(i = 0; i < snake_count; i++) {
    graph->add_edge(snake_start[i], snake_end[i], 1);
  }
    
  //add possible die rolls 
  for(i = 1; i < n; i++) {
    int j;
    for(j = 1; j < 7; j++) {
      if(i+j <= n) graph->add_edge(i, i+j, 2);
    }
  }
    
}

//solve the game by finding shortest path from cell 1 to cell n
void Game::solve() {

  //call dijkstra
  graph->dijkstra(1);
  
  //get path and save solution
  int n = size * size; //last cell on board
  solution = graph->get_shortest_path(1,n);
  graph->save_as_dot("visual.gv");
  
}


void Game::print_solution() {
  
  //find number of moves
  int i;
  int move_count = solution.size() - 1;
  for(i = solution.size()-1; i > 0; i--) { //skipping ladder moves
    if(graph->get_edge_weight(solution[i], solution[i-1]) == 1) move_count--;
  }
  
  cout << move_count << endl;
  
  //path was saved in reverse order
  for(i = solution.size()-1; i > 0; i--) {
    cout << solution[i];
    if(graph->get_edge_weight(solution[i], solution[i-1]) == 1) cout << "+";
    else cout << " ";
  }
  
  cout << solution[0]; //last cell on board  
  cout << endl;
 
}

/*****************************************************************************************
 * end
 ****************************************************************************************/
  

