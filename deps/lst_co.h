#ifndef LST_CO_H
#define LST_CO_H

typedef struct lst_co
{
    int x;
    int y;
    struct lst_co *suiv;
} *Lst_co;

Lst_co new_lst_co(int x, int y);
Lst_co supt_co(Lst_co l);
void free_lst_co(Lst_co l);
Lst_co adjt_co(Lst_co l, int x, int y);
void show_co(Lst_co l);
int len_co(Lst_co l);

#endif
