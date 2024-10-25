#ifndef VERIF_H
#define VERIF_H

#include "generation.h"
#include "lst_co.h"
#include "pathfinding.h"
#include "tab.h"
#include "tools.h"

#define V(condition, show_msg)                      \
    do                                              \
    {                                               \
        if (!(condition))                           \
        {                                           \
            fprintf(stderr, #condition " -> KO\n"); \
            exit(EXIT_FAILURE);                     \
        }                                           \
        if (show_msg)                               \
        {                                           \
            printf(#condition " -> OK\n");          \
        }                                           \
    } while (0)

int verif_tab(Tab tab);
int verif_path_continuity(Lst_co l);
int verif_path_start_end(Lst_co l, Tab tab);
int verif_size(int width, int height);
void test_smallmaze();
void test_bigmaze();
void test_maze(int width, int height, int show_msg, int display);

#endif