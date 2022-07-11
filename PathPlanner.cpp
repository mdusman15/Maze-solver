#include "PathPlanner.h"
#include <iostream>

#define internal static

internal Node* getPositionForKey(Env env, char keyCode, int row, int col) {

  Node* p = nullptr;
  for (int x = 0; x < row; x++) {
    for (int y = 0; y < col; y++) {
      if (env[x][y] == keyCode) p = new Node(x, y, 0);
    }
  }
  return p;
}

PathPlanner::PathPlanner(Env env, int row, int col) :
  _row(row), _col(col){
  _close = new NodeList();
  _open = new NodeList();

}

PathPlanner::~PathPlanner(){
  delete _open;
}


// setters 
void PathPlanner::setRow(int row) {
  this->_row = row;
}

void PathPlanner::setCol(int col) {
  this->_col = col;
}


void PathPlanner::initialPosition(int row, int col)
{
  _row = row;
  _col = col;
}

void PathPlanner::milestone2Search(Env env){

// Goal node
  Node* endNode = getPositionForKey(env, SYMBOL_GOAL, _row, _col);  
// Start Node
  Node* startNode = getPositionForKey(env, SYMBOL_START, _row, _col);


  // add start node to list
  _open->addBack(startNode);

  while (!startNode->equals(endNode)) { 
    startNode = getLowestDist(startNode, endNode);
    startNode->checkValid(this, env);

    // Add to closed list
    _close->addBack(startNode);
  }

  delete startNode;
  delete endNode;  
}


bool isCloser(Node *A, Node *B, Node* GoalNode){

  return (A->goalDist(GoalNode)>= B->goalDist(GoalNode));
}

Node* PathPlanner::getLowestDist(Node* thisNode, Node* nodeGoal) {
  for (int i = 0; i < _open->getLength() - 1; ++i) {

    Node* p = _open->get(i + 1);

    bool closerThanThis = isCloser(thisNode, p, nodeGoal);

    if ((((_close)->containsNode(thisNode)) || (closerThanThis)) && 
                (!(_close)->containsNode(p))) {
    
        thisNode = p;
    } 
  }
  
  return thisNode;
}



NodeList* PathPlanner::getReachableNodes(){

  //get a copy of the closed list
  // closed list is the list of the already explored nodes
  return new NodeList(*(_close));
}

void PathPlanner::checkForNode(int row, int col, 
NodeList *listOfDoneNodes, Node **currentNode, 
bool checkDistance, int idx, Node* thisNode)
{
  if (row == thisNode->getRow() 
            && col == thisNode->getCol()) {
            if (checkDistance) {
              *currentNode = _close->get(idx);
              listOfDoneNodes->addBack(*currentNode);
            }
          }
}
NodeList* PathPlanner::getPath(Env env){

  NodeList* listOfDoneNodes = new NodeList();

  Node* currentNode = _close->
      get(_close->getLength() - 1);

  // getting the first element of the closed list
  Node* goalNode = _close->get(0);

// put the first node 
  listOfDoneNodes->addBack(currentNode);


  while (!currentNode->equals(goalNode)) {

      for (int i = 0; i < _close->getLength(); ++i) {
        
        Node* thisNode = _close->get(i);

        // check each node to see if its 1 less
        bool checkDistance = (thisNode->getDistance() == currentNode->getDistance() - 1);

        

        // process adjacent nodes
        // -1 0
        checkForNode(currentNode->getRow() - 1, currentNode->getCol(),
        listOfDoneNodes, &currentNode, checkDistance, i, thisNode);

        // 0 1
        checkForNode(currentNode->getRow(), currentNode->getCol() + 1,
        listOfDoneNodes, &currentNode, checkDistance, i, thisNode);

        // 0 -1
        checkForNode(currentNode->getRow(), currentNode->getCol() - 1,
        listOfDoneNodes, &currentNode, checkDistance, i, thisNode);
        
        // 1 0
        checkForNode(currentNode->getRow() + 1, currentNode->getCol(),
        listOfDoneNodes, &currentNode, checkDistance, i, thisNode);

    }
  }

  delete currentNode;

  NodeList* reservedList = new NodeList();

  for (int i = 0; i < listOfDoneNodes->getLength(); ++i) {
    // add back element to top of new list
    reservedList->addBack(listOfDoneNodes->get((listOfDoneNodes->getLength() - 1) - i));
  }

  // delete listOfDoneNodes;
  return reservedList;  
   

}

