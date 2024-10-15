#include <stdio.h>
#include <stdlib.h>
#include "verif.h"
#include <math.h>

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
 * The function checks if the path is valid by iterating over each element of the
 * list and verifying if the adjacent coordinates are within a distance of 1.
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
 * @brief Exits the program with a status of 0 if the given boolean is false
 *
 * @param b the boolean value to check
 *
 * This function can be used to verify if a condition is true and exit the
 * program if it is false.
 */
void verif_exit(int b)
{
    if (b == 0)
        exit(EXIT_FAILURE);
}