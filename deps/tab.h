#ifndef TAB_H
#define TAB_H

#include <stdbool.h>

typedef enum
{
  normal,
  path,
  start,
  end
} type_cell;

typedef struct cell
{
  bool up : 1, down : 1, left : 1, right : 1;
  type_cell type : 2;
  bool visited : 1;
} Cell;

typedef struct pos
{
  int x;
  int y;
} Pos;

typedef struct tab
{
  int width;
  int height;
  int start_x; // used for generation
  int start_y; // used for generation
  Pos start;   // position of the start
  Cell **cells;
} Tab;

/**
 * @brief Creates a new Tab struct with the given width and height.
 *
 * The top-left cell is at coordinates (0,0) and the bottom-right cell is at
 * coordinates (width-1,height-1). The bottom-right cell is designated as the
 * end cell.
 *
 * @param width the number of columns in the tab
 * @param height the number of rows in the tab
 *
 * @return a Tab struct with the given width and height
 */
Tab new_tab(int width, int height);

/**
 * @brief Frees the memory allocated for the given Tab struct
 *
 * This function releases all the memory allocated for the given Tab struct.
 * It is the user's responsibility to call this function once they are done
 * using a Tab struct to avoid memory leaks.
 *
 * @param tab the Tab struct whose memory should be freed
 */
void free_tab(Tab tab);

/**
 * @brief Prints the given Tab struct in the console
 *
 * This function prints the given Tab struct in the console in the following
 * format:
 * up down left right
 *
 * Note that the start_x and start_y fields of the Tab struct are taken into
 * account when printing the tab.
 */
void print_tab(Tab tab);

/**
 * @brief Prints the given Tab struct as a maze in the console
 *
 * This function prints the given Tab struct as a maze in the console.
 * The maze is printed as a grid of characters, with '+' characters at the
 * corners, '-' characters for the north and south walls, and '|' characters
 * for the west and east walls. The type of each cell is represented by a
 * single character: ' ' for normal cells, 'S' for the start cell, and 'E'
 * for the end cell.
 *
 * @param t the Tab struct to print
 *
 * The start_x and start_y fields of the Tab struct are taken into account
 * when printing the maze.
 */
void maze_show(Tab tab);
char *type_to_str(type_cell type);

#endif
