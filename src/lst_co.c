#include <stdio.h>
#include <stdlib.h>
#include "lst_co.h"

Lst_co new_lst_co(int x, int y)
{
    Lst_co l = (Lst_co)malloc(sizeof(struct lst_co));
    l->x = x;
    l->y = y;
    l->suiv = NULL;
    return l;
}

Lst_co supt_co(Lst_co l)
{
    Lst_co ret = l->suiv;
    free(l);
    return ret;
}

void free_lst_co(Lst_co l)
{
    while (l != NULL)
    {
        l = supt_co(l);
    }
}

Lst_co adjt_co(Lst_co l, int x, int y)
{
    Lst_co lnouv = new_lst_co(x, y);
    lnouv->suiv = l;
    return lnouv;
}

void show_co(Lst_co l)
{
    while (l != NULL)
    {
        printf("x : %d, y : %d\n", l->x, l->y);
        l = l->suiv;
    }
}

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
