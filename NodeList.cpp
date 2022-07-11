#include "NodeList.h"
#include <iostream>

#define INITIAL_LENGTH 0


NodeList::NodeList(){

  _length = INITIAL_LENGTH;
  _nodes = new Node* [NODE_LIST_ARRAY_MAX_SIZE];
}

NodeList::~NodeList(){

  for (int i = 0; i < _length; i++) {
      delete _nodes[i];
  }
  delete _nodes;
}

// DEEP COPY
NodeList::NodeList(NodeList& other)
{   

  _length = other._length;
  _nodes = new Node*[NODE_LIST_ARRAY_MAX_SIZE];

  // copy all elements from other node
  for (int i = 0; i < other.getLength(); ++i) {

    Node* node = other.get(i);
    Node* newNode = new Node(*node);

    _nodes[i] = newNode;

  }  
}

// getters 
int NodeList::getLength(){
  return _length;
}

void NodeList::addBack(Node* nodeToAdd){
  _nodes[_length++] = new Node(*nodeToAdd);
}

Node* NodeList::get(int i){

  return _nodes[i]; 
}

bool NodeList::containsNode(Node* node) {
  bool found = false;

  for (int i = 0; i < getLength(); ++i) {
    Node* currNode = get(i);
    if (currNode->equals(node)) {
      found = true;
    }
  }   
  return found;
}
