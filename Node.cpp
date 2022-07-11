#include "Node.h"
#include <iostream>
#include "PathPlanner.h"


Node::Node(int row, int column, int distance) :_row(row), _column(column), _distance(distance) {}

Node::Node(Node& other) :_row(other._row), _column(other._column), _distance(other._distance) {}

Node::~Node(){
}

int Node::goalDist(Node* goal){
  return sqrt((this->getCol() - goal->getCol()) * (this->getCol() - goal->getCol()) +
        (this->getRow() - goal->getRow()) * (this->getRow() - goal->getRow()));;
}

bool Node::equals(Node* node) {
  return  this->_row == node->_row && 
        this->_column == node->_column;
}
    
void Node::checkNode(PathPlanner* planner, int row, int col, Env env) {
  
  int endRow = (getRow()) + row;
  int endCol = (getCol()) + col;

  if (env[endRow][endCol] == SYMBOL_EMPTY || env[endRow][endCol] == SYMBOL_GOAL) {


    Node* node = new Node(endRow, endCol, (getDistance()) + 1);

    if (!planner->getOpen()->containsNode(node)) {
        planner->getOpen()->addBack(node);
    }

    delete node;

  }
}

void Node::checkValid(PathPlanner* planner, Env env) {

  checkNode(planner, -1, 0, env);
  checkNode(planner, 0, 1, env);
  checkNode(planner, 1, 0, env); 
  checkNode(planner, 0, -1, env);

}

