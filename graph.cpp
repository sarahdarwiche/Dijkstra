#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
 
#include "graph.h"
#include "priority_queue.cpp"

using namespace std;


/*****************************************************************************************
 * node class
 ****************************************************************************************/
//
//node implementation
//

//i: node index
Node::Node(int i){
  index = i;
  
  //initialize dijkstra's distance to infinity (actually, largest integer)
  dist  = numeric_limits<int>::max();
  parent = NULL;
  known = false;
}

//i: node index
//d: initial dijkstra's distance
Node::Node(int i, int d){
  index = i;
  
  //initialize dijkstra's distance to infinity (actually, largest integer)
  dist  = d;
  known = false;
  parent = NULL;
}

//adds dest as a neighbor to node
void Node::add_neighbor(Node* dest, int weight){
  neighbors.push_back(dest);
  weights.push_back(weight);
}

//prints the node and its neighbors
void Node::print() const {
  cout << "Node " << index;
  cout << ":";
  int i;
  for(i = 0; i< neighbors.size(); i++){
  	 cout  << " " << neighbors[i]->index;
  	 cout  << "(" << weights[i] << ")";
  }
  cout << endl;
}  	   

/*****************************************************************************************
 * graph class
 ****************************************************************************************/
//
//graph implementation
//

Graph::Graph(int size) { 
  node_count = size; 
  int i;
  for(i = 0; i < size; i++) {
    Node *n = new Node(i+1);
    nodes.push_back(n);
  }
}

Graph::~Graph() {
  int i;
  for(i = 0; i < nodes.size(); i++) {
    delete nodes[i];
  }
}

//prints the graphs in the adjacency list format
void Graph::print() const {
  int i;
  for(i = 0; i < node_count; i++) nodes[i]->print();
}

//returns number of nodes in graph
int Graph::size() const { 
  return node_count; 
}

//adds an edge source -> destination
void Graph::add_edge(int source, int dest, int weight) const {
  Node *s = nodes[source-1];
  Node *d = nodes[dest-1];
  s->add_neighbor(d, weight);
}

//returns the weight of edge i-->j
int Graph::get_edge_weight(int i, int j) {
  Node *source = nodes[i - 1];
  Node *dest   = nodes[j - 1];
  
  int k;
  for(k = 0; k < source->neighbors.size(); k++) {
    if(source->neighbors[k] == dest) return source->weights[k];
  }
  
  return -1; //edge i-->j does not exist
}

//saves the graph to file in dot format 
//file can be visualized using the graphviz software on a mac
//saves edges costs, and dijkstra's distances as well
void Graph::save_as_dot(string fname) const {
  ofstream file;
  file.open(fname);
  
  //header
  file << "digraph {" << endl;
  file << "overlap=false" << endl;
  
  //write edges
  int i;
  for(i = 0; i < node_count; i++) { //iterate over nodes of graph
    Node *source = nodes[i];
    file << endl << source->index << " [label=\"" << source->index << ": " << source->dist << "\"];" << endl;
    
    vector<Node*> neighbors = source->neighbors;
    vector<int> weights     = source->weights;
    int j;
    for(j = 0; j < neighbors.size(); j++) { //iterate over neighbors of source
      Node *dest = neighbors[j];
      int weight = weights[j];
      file << source->index << "->" << dest->index;
      file << " [label=" << weight << "];" << endl;
    }
  } 
  
  //footer
  file << endl << "}" << endl;
  file.close();
}


/*****************************************************************************************
 * dijkstra implementation
 ****************************************************************************************/
 
void Graph::dijkstra(int s) {

  Node *source = nodes[s-1];
 
  priority_queue<Node*,vector<Node*>,NodeCompare> node_queue;
  
  //add all graph nodes to priority queue after initialization
  int i;
  for(i = 0; i < node_count; i++) {
    Node *n = nodes[i];
    //initialize node fields
    n->dist   = n==source? 0: numeric_limits<int>::max();
    n->parent = NULL;
    n-> known = false;
    //add not to priority queue
    node_queue.push(n);
  }
   
  while(!node_queue.empty()) {
    Node *k = node_queue.top();
    node_queue.pop();
    
    k->known = true;
     
    int i;
    for(i = 0; i < k->neighbors.size(); i++) {
      Node *child = k->neighbors[i];
      int weight  = k->weights[i];
      if(child->known == false) { //if it is unknown
        int new_dist = k->dist + weight;
        if(new_dist < child->dist) {
          node_queue = change_key(&node_queue, child, new_dist);
          child->parent = k;
        }
      } 
    }
  }
 
}

// returns shortest path from start to end
vector<int> Graph::get_shortest_path(int start, int end) {
  
  Node *s = nodes[start - 1];
  Node *e = nodes[end - 1];
  
  vector<int> path;
  
  while(e != s) {
    path.push_back(e->index);
    e = e->parent;
  }
  
  path.push_back(s->index);
  
  return path;

}

void print_path(vector<int> &path) {
  cout << "path: ";
  int i;
  for(i = path.size()-1; i >= 0; i--) {
    cout <<  path[i] << " ";
  }
  cout << endl;
}

void Graph::print_shortest_paths(int start) {
  int end;
  for(end = 1; end <= node_count; end++) {
    vector<int> path = get_shortest_path(start,end);
    print_path(path);
  } 
}



/*****************************************************************************************
 * testing utilities
 ****************************************************************************************/

void test_graph() {

//  Graph *x = new Graph(5);
//  x->print_graph();
//  delete x;
  
  Graph x(5);
  x.add_edge(1,2,1);
  x.add_edge(2,3,2);
  x.add_edge(2,5,6);
  x.add_edge(4,5,3);
  x.print();
  string fname = "/Users/SarahDarwiche/Desktop/cs130a/project3/graph.gv";
  x.save_as_dot(fname);
  
}

void test_dijkstra_one() {
  Graph x(6);
  x.add_edge(1,2,3); 
  x.add_edge(1,3,4);
  x.add_edge(1,4,1);
  x.add_edge(4,3,2);
  x.add_edge(4,2,3);
  x.add_edge(4,5,2);
  x.add_edge(4,6,5);
  x.dijkstra(1);
  x.print();
  string fname = "/Users/SarahDarwiche/Desktop/cs130a/project3/graph.gv";
  x.save_as_dot(fname);
  
}

void test_dijkstra_two() {
  Graph x(7);
  x.add_edge(1,2,3);
  x.add_edge(1,4,1);
  x.add_edge(2,4,3);
  x.add_edge(2,5,10);
  x.add_edge(3,6,5);
  x.add_edge(3,1,4);
  x.add_edge(4,3,2);
  x.add_edge(4,5,2);
  x.add_edge(4,6,8);
  x.add_edge(4,7,4);
  x.add_edge(5,7,6);
  x.add_edge(7,6,1);
  
  x.dijkstra(1);
  x.print_shortest_paths(1);
  
  x.print();
  string fname = "/Users/SarahDarwiche/Desktop/cs130a/project3/graph.gv";
  x.save_as_dot(fname);
  
  
}

void test_dijkstra_three() {
  Graph x(5);
  x.add_edge(1,2,10);
  x.add_edge(1,5,5);
  x.add_edge(2,3,1);
  x.add_edge(2,5,2);
  x.add_edge(3,4,4);
  x.add_edge(4,3,6);
  x.add_edge(4,1,7);
  x.add_edge(5,2,3);
  x.add_edge(5,3,9);
  x.add_edge(5,4,2);
  x.dijkstra(1);
  x.print();
  string fname = "/Users/SarahDarwiche/Desktop/cs130a/project3/graph.gv";
  x.save_as_dot(fname);
  
}
  
/*****************************************************************************************
 * end
 ****************************************************************************************/