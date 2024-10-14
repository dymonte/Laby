#ifndef TAB_H
#define TAB_H

typedef enum
{
    normal,
    path,
    start,
    end
} type_cell;

typedef struct cell
{
    unsigned int up : 1, down : 1, left : 1, right : 1;
    type_cell type;
    int visited : 1;
} Cell;

typedef struct tab
{
    int width;
    int height;
    int start_x;
    int start_y;
    Cell **cells;
} Tab;

Tab new_tab(int width, int height);
void free_tab(Tab tab);
void print_tab(Tab tab);
void maze_show(Tab tab);
char *type_to_str(type_cell type);

#endif
