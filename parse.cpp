//program to parse input and fill adjacency matrix

using namespace std;
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stack> 
#include <queue>
#include <algorithm>  
#include "AVL.h"

int main (int argc, char* argv[])
 {
   AVL *adelson = new AVL();

   while(true){
    string line = "";
    string command = "";
    string num = "";
    string second_half = "bfs";
    bool after_space = false;
    int number_as_integer = 0;
          
     getline( cin, line );
     if(cin.eof()) return -1;
	      
     for(int i=0; i < line.length(); i++){
       
       if ( line[i] != ' ' && after_space == false ){
	 command = command + line[i];
       }
       else{
	 after_space = true;
       }
       if( line[i] != ' ' && after_space == true ) num = num + line[i];
     }
     if (num.compare(second_half) == 0) command = command + num;
     number_as_integer = atoi(num.c_str());
     
     //cout << command << endl;
     
     if(command == "insert") adelson->insert(number_as_integer); 
     if(command == "access") adelson->access(number_as_integer);
     if(command == "print")  adelson->print();
     if(command == "printbfs") adelson->breadth_first_print();
     if(command == "delete") adelson->delete_value(number_as_integer);
     
   }
   
   return 0;
   
 }