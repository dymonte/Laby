#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "lst_co.h"
#include "tab.h"

Lst_co pathfinding_recursive(Tab *tab, Lst_co l);
Lst_co pathfinding_iteratif(Tab *tab, Lst_co l);
void trace_path(Tab tab, Lst_co l);

#endif
