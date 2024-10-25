#include "verif.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief The main function of the program
 *
 * This function takes up to 4 arguments:
 * - `width`: the width of the maze
 * - `height`: the height of the maze
 * - `show_msg`: a boolean indicating if the program should print messages
 * - `display`: a boolean indicating if the program should display the maze
 *
 * If no arguments are given, the program runs two tests: one for a big maze,
 * and one for a small maze. If 4 arguments are given, the program runs one
 * test with the given parameters. Otherwise, the program prints an error
 * message.
 */
int main(int argc, char *argv[])
{
  if (argc == 5)
  {
    test_maze(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
  }
  else if (argc == 1)
  {
    test_bigmaze();
    printf(" \n-----------------------\n\n");
    test_smallmaze();
  }
  else
  {
    fprintf(stderr, "Usage : ./main <width> <height> <show_msg> <display>\n");
  }

  return EXIT_SUCCESS;
}
