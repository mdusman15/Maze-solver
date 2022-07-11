#ifndef COSC_ASS_ONE_PATH_PLANNING
#define COSC_ASS_ONE_PATH_PLANNING

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathPlanner {
public:
  /*                                           */
  /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
  /*                                           */

  PathPlanner(Env env, int rows, int cols);
  ~PathPlanner();

   // Set The initial position
   void initialPosition(int row, int col);

  // Execute forward search algorithm
  // To be implemented for Milestone 2
  void milestone2Search(Env env);

   // Return a DEEP COPY of the NodeList of all node's
   //    that the robot can reach with distances
  NodeList* getReachableNodes();

  void setRow(int row);
  void setCol(int col);

  // Execute backtracking and Get a DEEP COPY of the path the 
  // robot should travel
  // To be implemented for Milestone 3
  NodeList* getPath(Env env);

  /*                                           */
  /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
  /*                                           */
  inline int getRow() const { return _row;}
  inline int getCol() const { return _col;}
  inline NodeList * getOpen() const {return _open;}

private:

  Node* getLowestDist(Node*, Node*);
  /*                                           */
  /* DO NOT MOFIFY THESE VARIABLES             */
  /*                                           */

  /*                                           */
  /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
  /*                                           */

  int _row;
  int _col;
  // open list for search algorithm
  NodeList* _open;
  //closed list for search algorithm
  NodeList* _close;

  Node* getValidNode(Node* currentNode, Env env);
  void checkForNode(int row, int col, NodeList *listOfDoneNodes, Node **currentNode, bool checkDistance, int idx, Node* thisNode);
};

#endif // COSC_ASS_ONE_PATH_PLANNING
