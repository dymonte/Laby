#ifndef VERIF_H
#define VERIF_H

#include "generation.h"
#include "lst_co.h"
#include "pathfinding.h"
#include "tab.h"
#include "tools.h"

#define V(condition, show_msg)                      \
    do                                              \
    {                                               \
        if (!(condition))                           \
        {                                           \
            fprintf(stderr, #condition " -> KO\n"); \
            exit(EXIT_FAILURE);                     \
        }                                           \
        if (show_msg)                               \
        {                                           \
            printf(#condition " -> OK\n");          \
        }                                           \
    } while (0)

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
int verif_tab(Tab tab);

/**
 * @brief Checks if the path represented by the list of coordinates is valid
 *
 * The function checks two things to validate the path:
 * - That the path is continuous (i.e. two adjacent cells in the path are
 *   adjacent in the maze)
 * - That the path starts at the start of the maze and ends at the end of
 *   the maze
 *
 * @param tab the Tab struct containing the maze
 * @param l the list of coordinates representing the path
 *
 * @return 1 if the path is valid, 0 otherwise
 */
int verif_path(Tab tab, Lst_co l);

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
int verif_path_continuity(Lst_co l);

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
int verif_path_start_end(Lst_co l, Tab tab);

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
int verif_size(int width, int height);



/**
 * @brief Test the continuity in the path 
 * 
 * @param tab the Tab struct containing the maze in whuch we found a path
 * @param path the list of coordinates representing the path 
 * 
 * @return 1 if the path is continuous, 0 if there is a gap in the path
 */
int verif_gaps(Tab tab, Lst_co path);

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
void test_maze(int width, int height, int show_msg, int display);

#endif