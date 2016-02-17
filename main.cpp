#include "graph.h"
#include "game.h"

#include <iostream>
#include <string>


int main (int argc, char* argv[]) {
  
  int game_count;
  cin >> game_count; //read number of games
  
  int i;
  for(i = 1; i <= game_count; i++) { //iterate over games
    
    //create game object
    Game mygame;
  
    //reading game details from standard input  
    mygame.read_from_stdin();
  
    //converting game to weighted directed graph
    mygame.construct_graph();
  
    //solving game using shortest path algorithm
    mygame.solve();
  
    //printing solution of game
    cout << "Board Game #" << i << ":" << endl;
    mygame.print_solution();
    
  }
  
  return 0;
 
}