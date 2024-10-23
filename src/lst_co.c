#include <stdio.h>
#include <stdlib.h>
#include "lst_co.h"

/**
 * @brief Creates a new element in the list
 *
 * @param[in] x the abscissa of the new element
 * @param[in] y the ordinate of the new element
 * @return a pointer to the new element
 *
 * The new element is added at the beginning of the list and
 * contains the coordinates (x, y) in its fields x and y.
 * The pointer suiv of the new element is set to NULL.
 */
Lst_co new_lst_co(int x, int y)
{
    Lst_co l = (Lst_co)malloc(sizeof(struct lst_co));
    l->x = x;
    l->y = y;
    l->suiv = NULL;
    return l;
}

/**
 * @brief Deletes the first element of the list
 *
 * @param[in] l the list whose first element will be deleted
 * @return the new first element of the list
 *
 * The function deletes the first element of the list and
 * returns the new first element of the list.
 */
Lst_co supt_co(Lst_co l)
{
    Lst_co ret = l->suiv;
    free(l);
    return ret;
}

/**
 * @brief Deletes all elements of the list
 *
 * @param[in] l the list to be deleted
 *
 * The function deletes all elements of the list.
 */
void free_lst_co(Lst_co l)
{
    while (l != NULL)
    {
        l = supt_co(l);
    }
}

/**
 * @brief Adds a new element at the beginning of the list
 *
 * @param[in] l the list
 * @param[in] x the abscissa of the new element
 * @param[in] y the ordinate of the new element
 * @return the new first element of the list
 *
 * The new element is added at the beginning of the list and
 * contains the coordinates (x, y) in its fields x and y.
 * The pointer suiv of the new element points to the old first
 * element of the list.
 */
Lst_co adjt_co(Lst_co l, int x, int y)
{
    Lst_co lnouv = new_lst_co(x, y);
    lnouv->suiv = l;
    return lnouv;
}

/**
 * @brief Prints the coordinates of each element of the list
 *
 * @param[in] l the list of coordinates
 *
 * The function prints the coordinates of each element of the list.
 * The coordinates are printed in the format "x : <x>, y : <y>\n".
 */
void show_co(Lst_co l)
{
    while (l != NULL)
    {
        printf("x : %d, y : %d\n", l->x, l->y);
        l = l->suiv;
    }
}

/**
 * @brief Calculates the length of a list of coordinates
 *
 * @param[in] l the list of coordinates
 *
 * @return the length of the list
 *
 * The function iterates over the list and counts the number of elements.
 */
int len_co(Lst_co l)
{
    int i = 0;
    while (l != NULL)
    {
        i++;
        l = l->suiv;
    }
    return i;
}
