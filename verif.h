#ifndef VERIF_H
#define VERIF_H

#include "tab.h"
#include "lst_co.h"

int verif_tab(Tab tab);
int verif_path(Lst_co l);
int verif_size(int width, int height);
void verif_exit(int b, int show_msg);
int verif_lst_length(Lst_co l, int expected_length);
void test_supt_co();

#endif