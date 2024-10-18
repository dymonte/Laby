#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * !DEPRECATED : use pathfinding_iteratif instead to avoid segmentation fault
 * (for big maze) due to recursion
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
Lst_co pathfinding_recursive(Tab *tab, Lst_co l)
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

	return pathfinding_recursive(tab, l);
}

/**
 * @brief Iterative pathfinding algorithm to find the shortest path to the exit.
 *
 * The algorithm visits each cell in the maze and marks each cell as visited.
 * It then checks if there is an unvisited cell adjacent to the current cell.
 * If there is, it adds the adjacent cell to the list of coordinates.
 * If there is not, it removes the current cell from the list of coordinates.
 * The algorithm stops when it reaches the end of the maze.
 *
 * The end of the maze is designated as the bottom-right cell so it try to
 visits
 * the bottom and then the right before the up and left neighbor.
 *
 * @param tab the Tab struct containing the maze
 * @param l the Lst_co struct containing the current position

 * @return the list of coordinates representing the shortest path to the exit
 */
Lst_co pathfinding_iteratif(Tab *tab, Lst_co l)
{
	int x = l->x;
	int y = l->y;
	int i = 0;

	while (tab->cells[y][x].type != end)
	{
		i++;

		x = l->x;
		y = l->y;

		tab->cells[y][x].visited = 1;

		if (tab->cells[y][x].down && !tab->cells[y + 1][x].visited)
			l = adjt_co(l, x, y + 1);
		else if (tab->cells[y][x].right && !tab->cells[y][x + 1].visited)
			l = adjt_co(l, x + 1, y);
		else if (tab->cells[y][x].up && !tab->cells[y - 1][x].visited)
			l = adjt_co(l, x, y - 1);
		else if (tab->cells[y][x].left && !tab->cells[y][x - 1].visited)
			l = adjt_co(l, x - 1, y);
		else
			l = supt_co(l);
		x = l->x;
		y = l->y;
	};

	printf("Number of iterations : %d\n", i);

	return l;
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
		if (tab.cells[l->y][l->x].type != start &&
			tab.cells[l->y][l->x].type != end)
			tab.cells[l->y][l->x].type = path;
		l = l->suiv;
	}
}
