#include "verif.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Checks if the given Tab struct is correct
 *
 * This function checks the given Tab struct by iterating over each cell and
 * verifying if the walls are consistent with the adjacent cells.
 *
 * @param tab the Tab struct to be checked
 *
 * @return 1 if the Tab struct is correct, 0 otherwise
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
int verif_path(Lst_co l)
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
 * @brief Exits the program with a status of 0 if the given boolean is false
 *
 * @param b the boolean value to check
 *
 * This function can be used to verify if a condition is true and exit the
 * program if it is false.
 */
void verif_exit(int b, int show_msg)
{
  if (show_msg)
    printf("OK\n");
  if (b == 0)
  {
    fprintf(stderr, "KO\n");
    exit(EXIT_FAILURE);
  }
}

int test_verysmall()
{
  // Initialize the random number generator
  int show_msg = 1; // to show messages

  int display = 1; // to display the maze

  // Initialize the random number generator
  srand(time(NULL));

  // Create and generate the maze with given parameters
  int width = 2;
  int height = 2;

  if (show_msg)
    printf("Verif size (%d x %d) : ", width, height);
  verif_exit(verif_size(width, height), show_msg);

  time_t t = time(&t);

  Tab maze = tab_start(width, height);

  // Generate a maze of size (width x height)
  generate(maze, 0, 1, 0);

  // print_tab(maze);

  // Test the validity of the maze
  if (show_msg)
    printf("Verif integrity of maze : ");
  verif_exit(verif_tab(maze), show_msg);

  // Random starting position for pathfinding
  Lst_co co_start = init_start(maze, 1);
  if (show_msg)
    printf("Start : (%d, %d)\n", co_start->x, co_start->y);

  double diff_time = difftime(time(NULL), t);
  if (show_msg)
    printf("Time to create the maze : %.2f secondes\n", diff_time);
  time(&t);

  // Call the pathfinding algorithm from the starting position
  Lst_co p = pathfinding_iteratif(&maze, co_start);

  diff_time = difftime(time(NULL), t);
  if (show_msg)
    printf("Time to find the path : %.2f secondes\n", diff_time);

  // Test the validity of the path
  if (show_msg)
    printf("Verif integrity of path : ");
  verif_exit(verif_path(p), show_msg);

  if (show_msg)
    printf("Length of the path : %d\n", len_co(p));

  // Display the coordinates of the found path
  // show_co(path);

  // Trace the found path in the maze
  trace_path(maze, p);

  // Display the maze with the traced path
  if (display)
    maze_show(maze);

  // Free the allocated memory for the list and the maze
  free_lst_co(p);
  free_tab(maze);

  return 0;
}

int test_bigmaze()
{
  // Initialize the random number generator
  int show_msg = 1; // to show messages

  int display = 1; // to display the maze

  // Initialize the random number generator
  srand(time(NULL));

  // Create and generate the maze with given parameters
  int width = 1000;
  int height = 1000;

  if (show_msg)
    printf("Verif size (%d x %d) : ", width, height);
  verif_exit(verif_size(width, height), show_msg);

  time_t t = time(&t);

  Tab maze = tab_start(width, height);

  // Generate a maze of size (width x height)
  generate(maze, 0, 1, 0);

  // print_tab(maze);

  // Test the validity of the maze
  if (show_msg)
    printf("Verif integrity of maze : ");
  verif_exit(verif_tab(maze), show_msg);

  // Random starting position for pathfinding
  Lst_co co_start = init_start(maze, 1);
  if (show_msg)
    printf("Start : (%d, %d)\n", co_start->x, co_start->y);

  double diff_time = difftime(time(NULL), t);
  if (show_msg)
    printf("Time to create the maze : %.2f secondes\n", diff_time);
  time(&t);

  // Call the pathfinding algorithm from the starting position
  Lst_co p = pathfinding_iteratif(&maze, co_start);

  diff_time = difftime(time(NULL), t);
  if (show_msg)
    printf("Time to find the path : %.2f secondes\n", diff_time);

  // Test the validity of the path
  if (show_msg)
    printf("Verif integrity of path : ");
  verif_exit(verif_path(p), show_msg);

  if (show_msg)
    printf("Length of the path : %d\n", len_co(p));

  // Display the coordinates of the found path
  // show_co(path);

  // Trace the found path in the maze
  trace_path(maze, p);
  // Display the maze with the traced path
  if (display)
    maze_show(maze);

  // Free the allocated memory for the list and the maze
  free_lst_co(p);
  free_tab(maze);

  return 0;
}
