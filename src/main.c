#include "../deps/verif.h"
#include <stdio.h>
#include <stdlib.h>

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
  if (argc != 5) // nb of arguments incorrect
  {
    fprintf(stderr, "Usage : ./main <width> <height> <show_msg> <display>\n");
    return EXIT_FAILURE;
  }

  int width = atoi(argv[1]);
  int height = atoi(argv[2]);
  int show_msg = atoi(argv[3]);
  int display = atoi(argv[4]);

  test_maze(width, height, show_msg, display);

  return EXIT_SUCCESS;
}
