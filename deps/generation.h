#ifndef GENERATION_H
#define GENERATION_H

#include "tab.h"

/**
 * @brief Initializes a Tab struct with the given width and height and sets
 * the border cells walls to 0.
 *
 * The top-left cell is at coordinates (0,0) and the bottom-right cell is at
 * coordinates (width-1,height-1). The bottom-right cell is designated as the
 * end cell.
 *
 * @param w the number of columns in the tab
 * @param h the number of rows in the tab
 *
 * @return a Tab struct with the given width and height
 */
Tab tab_start(int l, int h);

/**
 * @brief Generates a maze recursively by dividing the given Tab struct into
 * two smaller Tab structs and connecting them with a wall.
 *
 * The given Tab struct is divided into two smaller Tab structs, t1 and t2,
 * by a wall of width 1. The wall is then opened at a random position.
 *
 * If the given Tab struct has a height of 1 or a width of 1, the function
 * simply returns the given Tab struct.
 *
 * The orientation parameter determines the orientation of the wall. If
 * orientation is 0, the wall is horizontal, and if orientation is 1, the wall
 * is vertical.
 *
 * If random_wall is 1, the wall is placed at a random position, and if
 * random_wall is 0, the wall is placed in the middle of the given Tab struct.
 *
 * If random_orientation is 1, the orientation of the wall is chosen randomly,
 * and if random_orientation is 0, the orientation of the wall is chosen
 * deterministically.
 *
 * @param tab the Tab struct to be divided
 * @param orientation the orientation of the wall (0 for horizontal, 1 for vertical)
 * @param random_wall if 1, the wall is placed at a random position, and if 0,
 * the wall is placed in the middle of the given Tab struct
 * @param random_orientation if 1, the orientation of the wall is chosen
 * randomly, and if 0, the orientation of the wall is chosen deterministically
 *
 * @return the divided Tab struct
 */
void generate(Tab tab, int orientation, int random_wall, int random_orientation);

#endif
