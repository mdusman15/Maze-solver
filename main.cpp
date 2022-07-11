#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"
#include <sstream>

/*DESCRIPTION
This assignment was started by dividing the bigger problem to smaller ones. The provided pseudocode was then used
to implement Milestone 2. All the methods in Node, NodeList and PathPlanner classes were thoroughly
studied before implementing. The most challenging milestones, milestone 2 and milestone 4 were the most time consuming
parts of this assignment. In milestone 2, the forward search algorithm was implemented according to the pseudocode
given for the getReachableNodes method. This approach involved adding node to the openLIst given that there isn't a wall symbol
in the process of traversal. After checking up, right, down and left, the nodes having the lowest distance were added to the
closed list. The most common error encountered in the code was the segmentation fault error which occured due to
attempting to access a memory location that it is not allowed to access, notifying the system of memory access violation.
In milestone 3, the getPath method of class PathPlanner and printPath method were implemented, this required going through the nodes
to determine the direction symbol (^,>,v,<) based on the previous node with the help of the calculated distance. This method finds the
path to the goal position from the starting position using the NodeList that was generated in your Milestone 2.
Milestone 4 was a challenging one as it involved using an unknown dimension of the maze unlike other milestones. For this, the previous
implementations were modified to accomodate the needs. The readEnvStdin was modified to take dynamically allocate memory for the arrays
which resulted in solving a maze of any dimension. The templates provided were helpful for this implementation. 
 */

// Helper test functions
// void testNode();
// void testNodeList();

// Read a environment from standard input.
Env readEnvStdin(Env env, PathPlanner* );
// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printPath(Env env, NodeList* ,  int row, int col);
Env makeEnv(const int rows, const int cols);
void delete_env(Env env, int rows, int cols);

int main(int argc, char** argv){
  // Load Environment 
  Env env;
  env = nullptr;
  
  // Setting default values to pathPlanner
  PathPlanner* pathplanner = new PathPlanner(env, 0, 0);
  // use pathPlanner to get env
  env = readEnvStdin(env, pathplanner); 
  // search the path  
  pathplanner->milestone2Search(env);
  // get path
  NodeList* solution = pathplanner->getPath(env);
  printPath(env, solution, pathplanner->getRow(), pathplanner->getCol());
  NodeList* reachablePositions = nullptr;
  reachablePositions = pathplanner->getReachableNodes();
  // cleanup
  delete_env(env, pathplanner->getRow(), pathplanner->getCol());
  delete reachablePositions;
  delete solution;
  delete pathplanner;
}

// read method
Env readEnvStdin(Env env, PathPlanner* pathplanner){
  int numRows = 1;
  int numCols = 1;
  bool isThere = false;
  std::string getLines("");

  // Read until end of file
  while (!std::cin.eof()) {  
    char c;
    std::cin.get(c);
    getLines.push_back(c); 
  }
  getLines.pop_back();
  
  for (std::string::size_type i = 0; i < getLines.size(); ++i) {
    if (getLines[i] != '\n' && !isThere) {
        numCols++;
    } 
    if (getLines[i] == '\n'){
        numRows++;
        isThere = true;
    }
  }

  // Using the setters in pathPlanner 
  pathplanner->setRow(numRows);
  pathplanner->setCol(numCols);
  // new memory for the environment
  Env newEnv = makeEnv(numRows, numCols);
  int streamChar = 0;
  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j < numCols; ++j) {
        newEnv[i][j] = getLines[streamChar];
        streamChar++;  
    }
  }
  // assign env with this new environment
  env = newEnv;
  return env;
}
// Make environment 
Env makeEnv(const int rows, const int cols) {
   Env env = nullptr;

   if (rows >= 0 && cols >= 0) {
      env = new char*[rows];
      for (int i = 0; i != rows; ++i) {
         env[i] = new char[cols];
      }
   }
   return env;
}

// delete environment
void delete_env(Env env, int rows, int cols) {
   if (rows >= 0 && cols >= 0) {
      for (int i = 0; i != rows; ++i) {
         delete env[i];
      }
      delete env;
   }
   return;
}

// mark the directions in the maze
void dirMarker(Env env, Node *thisNode, Node* next)
{
    int nextCol = next->getCol();
    int currCol = thisNode->getCol();
    int nextRow = next->getRow();
    int currRow = thisNode->getRow();
    if (nextCol - currCol == 1) 
    {
      env[currRow][currCol] = '>';
    } 
    else if (nextRow - currRow == 1) 
    {
        env[currRow][currCol] = 'v';
    } 
    else if (nextCol- currCol == -1) 
    {
        env[currRow][currCol] = '<';
    } 
    else if (nextRow - currRow == -1) 
    {
        env[currRow][currCol] = '^';
    }
}

// print the path 
void printPath(Env env, NodeList* solution, int row, int col) {
  for (int i = 1; i < solution->getLength() - 1; i++){
        Node* thisNode = solution->get(i);
        Node* next = solution->get(i + 1);
        dirMarker(env, thisNode, next);
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
         std::cout << env[i][j];                       
        }
    }
  }