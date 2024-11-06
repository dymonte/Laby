#include <stdlib.h>
#include "generation.h"

Tab tab_start(int w, int h)
{
    Tab t = new_tab(w, h);

    for (int i = t.start_y; i < h; i++)
    {
        t.cells[i][t.start_x].left = 0;
        t.cells[i][t.start_x + w - 1].right = 0;
    }

    for (int i = t.start_x; i < w; i++)
    {
        t.cells[t.start_y][i].up = 0;
        t.cells[t.start_y + h - 1][i].down = 0;
    }

    t.cells[t.height - 1][t.width - 1].type = end;
    return t;
}

Tab generate(Tab tab, int orientation, int random_wall, int random_orientation)
{
    if (tab.height == 1 || tab.width == 1)
        return tab;

    Tab t1 = tab;
    Tab t2 = tab;
    if (orientation == 0)
    {
        int w = random_wall ? rand() % (tab.width - 1) + 1 : (int)(tab.width / 2);
        int w_wall = w + tab.start_x;
        int pos_ouverture = rand() % tab.height;

        for (int i = tab.start_y; i < tab.start_y + tab.height; i++)
        {
            if (i == tab.start_y + pos_ouverture)
            {
                tab.cells[i][w_wall - 1].right = 1;
                tab.cells[i][w_wall].left = 1;
            }
            else
            {
                tab.cells[i][w_wall - 1].right = 0;
                tab.cells[i][w_wall].left = 0;
            }
        }

        t1.width = w;
        t2.width = tab.width - w;
        t2.start_x += w;
    }
    else
    {
        int h = random_wall ? rand() % (tab.height - 1) + 1 : (int)(tab.height / 2);
        int h_wall = h + tab.start_y;
        int pos_ouverture = rand() % tab.width;

        for (int i = tab.start_x; i < tab.start_x + tab.width; i++)
        {
            if (i == tab.start_x + pos_ouverture)
            {
                tab.cells[h_wall - 1][i].down = 1;
                tab.cells[h_wall][i].up = 1;
            }
            else
            {
                tab.cells[h_wall - 1][i].down = 0;
                tab.cells[h_wall][i].up = 0;
            }
        }

        t1.height = h;
        t2.height = tab.height - h;
        t2.start_y += h;
    }

    if (random_orientation)
    {
        generate(t1, rand() % 2, random_wall, random_orientation);
        generate(t2, rand() % 2, random_wall, random_orientation);
    }
    else
    {
        generate(t1, (orientation + 1) % 2, random_wall, random_orientation);
        generate(t2, (orientation + 1) % 2, random_wall, random_orientation);
    }
    return tab;
}
