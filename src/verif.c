#include "../deps/verif.h"

#define CLOCK_REALTIME 0

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

int verif_path(Tab tab, Lst_co l)
{
  if (verif_path_continuity(l) && verif_path_start_end(l, tab) && verif_gaps(tab, l))
    return 1;
  else
    return 0;
}

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

int verif_path_start_end(Lst_co l, Tab tab)
{
  Lst_co st = l;

  while (st->suiv != NULL)
  {
    st = st->suiv;
  }

  return tab.cells[l->y][l->x].type == end &&
         tab.cells[st->y][st->x].type == start;
}

int verif_size(int width, int height)
{
  return width > 0 && height > 0 && (width > 1 || height > 1);
}

/**
 * @brief Writes the given time difference to a file
 *
 * This function takes a time difference in microseconds and writes it
 * as a string to the specified file.
 *
 * @param diff_time the time difference to be written, in microseconds
 * @param f the file pointer to which the time difference will be written
 */
void write_time(unsigned int diff_time, FILE *f)
{
  char str_diff_time[32];
  sprintf(str_diff_time, "%d", diff_time);
  fwrite(str_diff_time, strlen(str_diff_time), 1, f);
}

/**
 * @brief Computes the difference in time between two timespec structures in microseconds
 *
 * @param time1 the first timespec structure
 * @param time2 the second timespec structure
 *
 * @return the difference in time between the two timespec structures in microseconds
 */
unsigned int get_difftime(struct timespec time1, struct timespec time2)
{
  return (time2.tv_sec - time1.tv_sec) * 1000000 + (time2.tv_nsec - time1.tv_nsec) / 1000;
}

/**
 * @brief Writes the time taken to generate a maze and to find the path in a maze to csv files
 *
 * The function takes two parameters:
 * - `diff_time_gen`: the time taken to generate the maze in microseconds
 * - `diff_time_path`: the time taken to find the path in the maze in microseconds
 *
 * The function appends the times to the end of the files "stats/result_gen.csv" and "stats/result_path.csv"
 *
 * @param diff_time_gen the time taken to generate the maze in microseconds
 * @param diff_time_path the time taken to find the path in the maze in microseconds
 */
void generate_stats(unsigned int diff_time_gen, unsigned int diff_time_path)
{
  FILE *gen = fopen("stats/result_gen.csv", "a");
  FILE *solve = fopen("stats/result_path.csv", "a");
  write_time(diff_time_gen, gen);
  write_time(diff_time_path, solve);
  fclose(gen);
  fclose(solve);
}

int verif_gaps(Tab tab, Lst_co p)
{
  Lst_co current = p;

  int x, y, next_x, next_y;

  while (current != NULL && current->suiv != NULL)
  {
    x = current->x;
    y = current->y;
    next_x = current->suiv->x;
    next_y = current->suiv->y;

    // Check if the next cell in the path is a valid neighbor

    if (!(next_y == y + 1 && tab.cells[y][x].down) &&
        !(next_y == y - 1 && tab.cells[y][x].up) &&
        !(next_x == x + 1 && tab.cells[y][x].right) &&
        !(next_x == x - 1 && tab.cells[y][x].left))
    {
      // If none of the valid side match, there's a gap
      printf("Gap detected between (%d, %d) and (%d, %d)\n", x, y, next_x, next_y);
      return 0; // Path has a gap
    }
    current = current->suiv;
  }

  return 1; // Path is continuous if no gaps were found
}

void test_maze(int width, int height, int show_msg, int display, int get_stats)
{
  // Initialize the random number generator
  srand(time(NULL));

  if (show_msg)
    print_title("Start");

  if (show_msg)
    printf("Verif size (%d x %d) : ", width, height);
  V(verif_size(width, height), show_msg);

  struct timespec time1, time2, time3;

  clock_gettime(CLOCK_REALTIME, &time1);

  if (show_msg)
    print_title("Generation of maze");
  Tab maze = tab_start(width, height);

  // Generate a maze of size (width x height)
  generate(maze, 0, 1, 0);

  // Random starting position for pathfinding
  Lst_co co_start = init_start(maze, 1);
  if (show_msg)
    printf("Start : (%d, %d)\n", co_start->x, co_start->y);

  // Measure the time taken to generate the maze
  clock_gettime(CLOCK_REALTIME, &time2);

  unsigned int diff_time_gen = get_difftime(time1, time2);

  if (show_msg)
    printf("Time to create the maze : %dms\n", diff_time_gen);

  // Test the validity of the maze
  if (show_msg)
    printf("Verif integrity of maze : ");
  V(verif_tab(maze), show_msg);

  if (show_msg)
    print_title("Pathfinding");

  // Call the pathfinding algorithm from the starting position
  Lst_co p = pathfinding_iteratif(&maze, co_start, show_msg);
  // Lst_co p = a_star_finding(&maze);

  // Measure the time taken to find the path
  clock_gettime(CLOCK_REALTIME, &time3);
  unsigned int diff_time_path = get_difftime(time2, time3);

  if (show_msg)
    printf("Time to find the path : %dms\n", diff_time_gen);

  // Test the validity of the path
  if (show_msg)
    printf("Verif integrity of path : ");

  V(verif_path(maze, p), show_msg);

  if (show_msg)
    printf("Length of the path : %d\n", len_co(p));

  // Display the coordinates of the found path
  // show_co(path);

  // Trace the found path in the maze
  trace_path(maze, p);

  // Display the maze with the traced path
  if (display)
  {
    print_title("Display");
    maze_show(maze);
  }

  // Generate statistics
  if (get_stats)
    generate_stats(diff_time_gen, diff_time_path);

  // Free the allocated memory for the list and the maze
  free_lst_co(p);
  free_tab(maze);
}
