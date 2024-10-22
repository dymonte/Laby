#ifndef VERIF_H
#define VERIF_H

#include "generation.h"
#include "lst_co.h"
#include "pathfinding.h"
#include "tab.h"
#include "tools.h"

int verif_tab(Tab tab);
int verif_path(Lst_co l);
int verif_size(int width, int height);
void verif_exit(int b, int show_msg);
int test_smallmaze();
int test_bigmaze();
int test_maze(int width, int height, int show_msg, int display);

#endif