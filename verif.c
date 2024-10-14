#include <stdio.h>
#include <stdlib.h>
#include "tab.h"
#include "verif.h"

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
}

void verif_exit(int b)
{
    if (b == 0)
        exit(0);
}