#ifndef GENERATION_H
#define GENERATION_H

#include "tab.h"

Tab tab_start(int l, int h);
Tab generate(Tab tab, int orientation, int random_wall, int random_orientation);

#endif
