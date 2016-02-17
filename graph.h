#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

using namespace std;

//
//node interface
//
class Node {

public:
 
  int index; //index of node
  vector<Node*> neighbors; //adjacency list of node
  vector<int> weights; 
  
  //used by dijkstra's algorithm
  int dist; 
  Node* parent;
  bool known;
   
public:

  Node(int i);
  Node(int i, int d);
  void add_neighbor(Node* dest, int weight);
  void print() const;
   
};

//   
//graph interface
//
class Graph {

private:
  
  int node_count;
  vector<Node*> nodes;

public:

  Graph(int size);
  ~Graph();
  void print() const;
  int size() const;
  void add_edge(int source, int dest, int weight) const;
  void save_as_dot(string fname) const; //added by baba
  void dijkstra(int s);
  vector<int> get_shortest_path(int start, int end);
  void print_shortest_paths(int start);
  int get_edge_weight(int i, int j);
  
};

#endif