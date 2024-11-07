#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

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
