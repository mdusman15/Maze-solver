#ifndef COSC_ASS_ONE_NODE
#define COSC_ASS_ONE_NODE

#include "Types.h"

class PathPlanner;

class Node{
public:
  /*                                           */
  /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
  /*                                           */

  // Constructor/Desctructor
  Node(int row, int column, int distance);
  ~Node();


  inline int getRow() const { return _row;}
  inline int getCol() const { return _column;}
  inline int getDistance() const {return _distance;}


  int goalDist(Node* goal);
  void checkNode(PathPlanner*, int , int , Env );

  void checkValid(PathPlanner*, Env );

  /*                                           */
  /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
  /*                                           */

  bool equals(Node* node);

  Node(Node& other);

  private:
      /*                                           */
      /* DO NOT MOFIFY THESE VARIABLES             */
      /*                                           */

  int _row;
  int _column;
  int _distance;

  /*                                           */
  /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
  /*                                           */

};





#endif // COSC_ASS_ONE_NODE
