#include "verif.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**                                                                          \
 * @brief Checks if the given Tab struct is correct                          \
 *                                                                           \
 * This function checks the given Tab struct by iterating over each cell and \
 * verifying if the walls are consistent with the adjacent cells.            \
 *                                                                           \
 * @param tab the Tab struct to be checked                                   \
 *                                                                           \
 * @return 1 if the Tab struct is correct, 0 otherwise                       \
 */
int verif_tab(Tab tab)
{
  for (int y = tab.start_y; y < tab.start_x + tab.height; y++)
  {
    for (int x = tab.start_x; x < tab.start_x + tab.width; x++)
    {
      if (tab.cells[y][x].up == 1 && tab.cells[y - 1][x].down != 1)
        return 0;

      if (tab.cells[y][x].down == 1 && tab.cells[y + 1][x].up != 1)
        return 0;

      if (tab.cells[y][x].left == 1 && tab.cells[y][x - 1].right != 1)
        return 0;

      if (tab.cells[y][x].right == 1 && tab.cells[y][x + 1].left != 1)
        return 0;
    }
  }

  return 1;
}

/**
 * @brief Verifies if the path represented by the list of coordinates is valid
 *
 * The function checks if the path is valid by iterating over each element of
 * the list and verifying if the adjacent coordinates are within a distance
 * of 1.
 *
 * @param l the list of coordinates representing the path
 *
 * @return 1 if the path is valid, 0 otherwise
 */
int verif_path_continuity(Lst_co l)
{
  if (l == NULL)
    return 0;
  while (l->suiv != NULL)
  {
    if (abs(l->x - l->suiv->x) > 1 || abs(l->y - l->suiv->y) > 1)
    {
      return 0;
    }
    l = l->suiv;
  }
  return 1;
}

/**
 * @brief Checks if the path represented by the list of coordinates starts at the
 * start of the maze and ends at the end of the maze
 *
 * The function checks if the first element of the list is the start of the
 * maze and the last element is the end of the maze.
 *
 * @param l the list of coordinates representing the path
 * @param tab the Tab struct containing the maze
 *
 * @return 1 if the path starts at the start and ends at the end, 0 otherwise
 */
int verif_path_start_end(Lst_co l, Tab tab)
{
  Lst_co st = l;

  while (l->suiv != NULL)
  {
    l = l->suiv;
  }
  return tab.cells[l->y][l->x].type == end && tab.cells[st->y][st->x].type == start;
}

/**
 * @brief Checks if the given width and height are valid
 *
 * @param width the width of the maze
 * @param height the height of the maze
 *
 * @return 1 if the width and height are valid, 0 otherwise
 *
 * A valid width and height are positive integers.
 */
int verif_size(int width, int height)
{
  return width > 0 && height > 0 && (width > 1 || height > 1);
}

/**
 * @brief Runs a test on a small maze
 *
 * This function tests the generation and pathfinding of a small maze
 * with dimensions 2x2. It displays the maze and prints messages
 * indicating the success or failure of the operations.
 */
void test_smallmaze()
{
  test_maze(2, 2, 1, 1);
}

/**
 * @brief Runs a test on a large maze
 *
 * This function tests the generation and pathfinding of a large maze
 * with dimensions 1000x1000. It does not display the maze, but it
 * prints messages indicating the success or failure of the operations.
 */
void test_bigmaze()
{
  test_maze(1000, 1000, 1, 0);
}

/**
 * @brief Test the generation of a maze and the pathfinding algorithm
 *
 * This function takes four parameters:
 * - `width`: the width of the maze
 * - `height`: the height of the maze
 * - `show_msg`: a boolean indicating if the function should print messages
 * - `display`: a boolean indicating if the function should display the maze
 *
 * The function tests the generation of a maze of size (width x height) and
 * the pathfinding algorithm by generating a maze, calling the pathfinding
 * algorithm from a random starting position, testing the validity of the
 * path, tracing the path in the maze and displaying the maze if requested.
 *
 * The function also measures the time taken to generate the maze and to
 * find the path.
 *
 * @param width the width of the maze
 * @param height the height of the maze
 * @param show_msg a boolean indicating if the function should print messages
 * @param display a boolean indicating if the function should display the maze
 */
void test_maze(int width, int height, int show_msg, int display)
{
  // Initialize the random number generator

  if (show_msg)
    printf("-- Start --\n\n");

  srand(time(NULL));

  if (show_msg)
    printf("Verif size (%d x %d) : ", width, height);
  V(verif_size(width, height), show_msg);

  time_t t = time(&t);

  if (show_msg)
    printf("\n-- Generating maze --\n\n");
  Tab maze = tab_start(width, height);

  // Generate a maze of size (width x height)
  generate(maze, 0, 1, 0);

  // print_tab(maze);

  // Random starting position for pathfinding
  Lst_co co_start = init_start(maze, 1);
  if (show_msg)
    printf("Start : (%d, %d)\n", co_start->x, co_start->y);

  // Test the validity of the maze
  if (show_msg)
    printf("Verif integrity of maze : ");
  V(verif_tab(maze), show_msg);

  double diff_time = difftime(time(NULL), t);
  if (show_msg)
    printf("Time to create the maze : %.2f secondes\n", diff_time);
  time(&t);

  printf("\n-- Path finding--\n\n");

  // Call the pathfinding algorithm from the starting position
  Lst_co p = pathfinding_iteratif(&maze, co_start);

  diff_time = difftime(time(NULL), t);
  if (show_msg)
    printf("Time to find the path : %.2f secondes\n", diff_time);

  // Test the validity of the path
  if (show_msg)
    printf("Verif integrity of path : ");
  V(verif_path_continuity(p), show_msg);

  if (show_msg)
    printf("Length of the path : %d\n", len_co(p));

  // Display the coordinates of the found path
  // show_co(path);

  // Trace the found path in the maze
  trace_path(maze, p);

  // Display the maze with the traced path
  if (display)
  {
    printf("\n-- Display --\n\n");

    maze_show(maze);
  }

  // Free the allocated memory for the list and the maze
  free_lst_co(p);
  free_tab(maze);
}