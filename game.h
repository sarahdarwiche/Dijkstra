#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "graph.h"

using namespace std;

class Game {

  public:
  
  int size;
  int snake_count;
  int ladder_count;
  
  vector<int> ladder_start; 
  vector<int> ladder_end; 
  vector<int> snake_start; 
  vector<int> snake_end; 
  
  Graph *graph;
  vector<int> solution;
   
  public:
  
  Game(string fname); 
  Game();
  ~Game();
  void read_from_file(string fname);
  void read_from_stdin();
  void print_to_stdout(); 
  void construct_graph();
  void solve();
  void print_solution();
   
};

#endif