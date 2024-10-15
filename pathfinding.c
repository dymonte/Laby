#include "pathfinding.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Pathfinding algorithm to find the shortest path to the exit.
 *
 * @param tab the Tab struct containing the maze
 * @param l the Lst_co struct containing the current position
 *
 * The algorithm visits each cell in the maze and marks each cell as visited.
 * It then checks if there is an unvisited cell adjacent to the current cell.
 * If there is, it adds the adjacent cell to the list of coordinates and
 * recursively calls itself. If there is not, it removes the current cell from
 * the list of coordinates and recursively calls itself.
 *
 * @return the list of coordinates representing the shortest path to the exit
 */
Lst_co pathfinding(Tab *tab, Lst_co l)
{
    int x = l->x;
    int y = l->y;
    if (tab->cells[y][x].type == end)
        return l;

    tab->cells[y][x].visited = 1;

    if (tab->cells[y][x].up && !tab->cells[y - 1][x].visited)
        l = adjt_co(l, x, y - 1);
    else if (tab->cells[y][x].down && !tab->cells[y + 1][x].visited)
        l = adjt_co(l, x, y + 1);
    else if (tab->cells[y][x].left && !tab->cells[y][x - 1].visited)
        l = adjt_co(l, x - 1, y);
    else if (tab->cells[y][x].right && !tab->cells[y][x + 1].visited)
        l = adjt_co(l, x + 1, y);
    else
        l = supt_co(l);

    return pathfinding(tab, l);
}

/**
 * @brief Traces the path from the start to the end of the maze
 *
 * This function takes a Tab struct and a Lst_co struct containing the path
 * and marks each cell in the path as 'path' type.
 *
 * The function iterates over each element of the list of coordinates and
 * changes the type of the corresponding cell in the Tab struct to 'path'.
 * It does not change the type of the start or end cells.
 */
void trace_path(Tab tab, Lst_co l)
{
    while (l != NULL)
    {
        if (tab.cells[l->y][l->x].type != start && tab.cells[l->y][l->x].type != end)
            tab.cells[l->y][l->x].type = path;
        l = l->suiv;
    }
}
