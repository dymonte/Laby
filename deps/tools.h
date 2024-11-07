#ifndef TOOLS_H
#define TOOLS_H

#include "lst_co.h"
#include "tab.h"
#include <stdio.h>

/**
 * @brief Initializes the start of the maze
 *
 * @param[in] tab the maze
 * @return a pointer to a linked list representing the start of the maze
 *
 * The start is chosen randomly within the maze, but never
 * on the last row or column to avoid breaking the exit.
 * The start cell is then set as type 'start'.
 */
Lst_co init_start(Tab tab, int random_start);

/**
 * @brief Prints a formatted title
 *
 * This function takes a string as input and prints it as a title
 * enclosed with dashes on either side, followed by two new lines.
 *
 * @param title the string to be printed as a title
 */
void print_title(char *title);

#endif
