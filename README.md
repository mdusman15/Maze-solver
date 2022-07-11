# Maze-solver

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
 
