#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "lst_co.h"
#include "tab.h"

typedef struct cost {
  int gCost;
  int hCost;
  int fCost;
} Cost;

typedef struct cpos {
  Pos actual;
  Pos parentPos;
} CouplePos;

struct as_ll {
  void *data;
  struct as_ll *next;
};

/**
 * @brief Iterative pathfinding algorithm to find the shortest path to the exit.
 *
 * The algorithm visits each cell in the maze and marks each cell as visited.
 * It then checks if there is an unvisited cell adjacent to the current cell.
 * If there is, it adds the adjacent cell to the list of coordinates.
 * If there is not, it removes the current cell from the list of coordinates.
 * The algorithm stops when it reaches the end of the maze.
 *
 * The end of the maze is designated as the bottom-right cell so it try to
 visits
 * the bottom and then the right before the up and left neighbor.
 *
 * @param tab the Tab struct containing the maze
 * @param l the Lst_co struct containing the current position
 * @param show_msg whether to display messages

 * @return the list of coordinates representing the shortest path to the exit
 */
Lst_co pathfinding_iteratif(Tab *tab, Lst_co l, int show_msg);

/**
 * !DEPRECATED : use pathfinding_iteratif instead to avoid segmentation fault
 * (for big maze) due to recursion
 * @brief Pathfinding algorithm to find the shortest path to the exit.
 *
 * @param tab the Tab struct containing the maze
 * @param l the Lst_co struct containing the current position
 *
 * The algorithm visits each cell in the maze and marks each cell as visited.
 * It then checks if there is an unvisited cell adjacent to the current cell.
 * If there is, it adds the adjacent cell to the list of coordinates and
 * recursively calls itself. If there is not, it removes the current cell from
 * the list of coordinates and recursively calls itself.
 *
 * @return the list of coordinates representing the shortest path to the exit
 */
Lst_co pathfinding_recursive(Tab *tab, Lst_co l);

/**
 * @brief Traces the path from the start to the end of the maze
 *
 * This function takes a Tab struct and a Lst_co struct containing the path
 * and marks each cell in the path as 'path' type.
 *
 * The function iterates over each element of the list of coordinates and
 * changes the type of the corresponding cell in the Tab struct to 'path'.
 * It does not change the type of the start or end cells.
 */
void trace_path(Tab tab, Lst_co l);

Lst_co a_star_finding(Tab *tab);
#endif
