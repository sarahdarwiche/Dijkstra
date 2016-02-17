#include <queue> 
#include <iostream>
#include "graph.h"

using namespace std;

/*****************************************************************************************
 * priority queue
 ****************************************************************************************/

struct NodeCompare
{
  //tests whether n1 worse than n2
  bool operator()(const Node *n1, const Node *n2) const{
    return n1->dist > n2->dist;
  }
};


//changes the key of node in a priority queue
priority_queue<Node*,vector<Node*>,NodeCompare> change_key(priority_queue<Node*,vector<Node*>,NodeCompare> *old_queue, Node *n, int new_key) {

  priority_queue<Node*,vector<Node*>,NodeCompare> new_queue;
  
  while(!old_queue->empty()) {
  
     Node *k = old_queue->top();
     old_queue->pop();
     if(n == k) k->dist = new_key;
     new_queue.push(k); 
  }
  
  return new_queue;
}


void test_queue(){

  priority_queue<Node*,vector<Node*>,NodeCompare> node_queue;
    
  //create new nodes
  Node a(1,30);
  Node b(2,20);
  Node c(3,10);
  
  cout << "size of queue " << node_queue.size() << endl;
  
  node_queue.push(&a);
  cout << "size of queue " << node_queue.size() << endl;
  
  node_queue.push(&b);
  cout << "size of queue " << node_queue.size() << endl;
  
  node_queue.push(&c);
  cout << "size of queue " << node_queue.size() << endl;
  
  node_queue = change_key(&node_queue, &a, 4);
  
  Node *n = node_queue.top();
  cout << "popped from queue:" << endl;
  n->print();
  node_queue.pop();
  
  
  Node *m = node_queue.top();
  cout << "popped from queue:" << endl;
  m->print();
  node_queue.pop();
  
  Node *k = node_queue.top();
  cout << "popped from queue:" << endl;
  k->print();
  node_queue.pop();
  
}


/*****************************************************************************************
 * end
 ****************************************************************************************/

