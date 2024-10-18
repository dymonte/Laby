#include "tools.h"
#include "stdlib.h"

/**
 * @brief Initializes the start of the maze
 *
 * @param[in] tab the maze
 * @return a pointer to a linked list representing the start of the maze
 *
 * The start is chosen randomly within the maze, but never
 * on the last row or column to avoid breaking the exit.
 * The start cell is then set as type 'start'.
 */
Lst_co init_start(Tab tab, int random_start)
{
  if (!random_start)
  {
    Lst_co l = new_lst_co(0, 0);

    tab.cells[0][0].type = start;

    return l;
  }

  int w = tab.width;
  int random_y = rand() % (tab.height - (w == 1 ? 1 : 0));
  if (random_y == tab.height - 1 &&
      w > 1) // eviter que l'entree ecrase la sortie, si la largeur est
             // inferieure a 1, division par 0
    w--;
  int random_x = rand() % (w);
  Lst_co l = new_lst_co(random_x, random_y);

  tab.cells[random_y][random_x].type = start;
  return l;
}
