#include <stdlib.h>
#include "generation.h"

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
