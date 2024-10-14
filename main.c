#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int a = 0;

typedef struct lst_co
{
    int x;
    int y;
    struct lst_co *suiv;
} *Lst_co;

typedef enum
{
    normal,
    path,
    start,
    end
} type_cell;

typedef struct cell
{
    unsigned int up : 1, down : 1, left : 1, right : 1; // 1 = not blocked, 0 = blocked
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

// --- fonctions pour les listes de coord ---
Lst_co new_lst_co(int x, int y)
{
    Lst_co l = (Lst_co)malloc(sizeof(struct lst_co));
    l->x = x;
    l->y = y;
    l->suiv = NULL;
    return l;
}

Lst_co supt_co(Lst_co l) // suffit pour detruire entierement une lst
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

// --- fonctions pour le tab ---

Tab new_tab(int width, int height)
{
    Tab tab;
    tab.width = width;
    tab.height = height;

    tab.start_x = 0;
    tab.start_y = 0;

    tab.cells = (Cell **)malloc(sizeof(Cell *) * height);
    for (int i = 0; i < height; i++)
    {
        tab.cells[i] = (Cell *)malloc(sizeof(Cell) * width);
        for (int j = 0; j < width; j++)
        {
            tab.cells[i][j].up = 1;
            tab.cells[i][j].down = 1;
            tab.cells[i][j].left = 1;
            tab.cells[i][j].right = 1;
            tab.cells[i][j].type = normal;
            tab.cells[i][j].visited = 0;
        }
    }
    tab.cells[height - 1][width - 1].type = end;
    return tab;
}

Lst_co init_start(Tab tab)
{
    int w = tab.width;
    int random_y = rand() % (tab.height - 1);
    if (random_y == tab.height - 1) // eviter que l'entree ecrase la sortie
        w -= 1;
    int random_x = rand() % (w - 1);
    Lst_co l = new_lst_co(random_x, random_y);

    tab.cells[random_y][random_x].type = start;
    return l;
}

void free_tab(Tab tab)
{
    for (int i = tab.start_y; i < tab.start_y + tab.height; i++)
    {
        free(tab.cells[i]);
    }
    free(tab.cells);
}

Tab tab_start(int l, int h)
{
    Tab t = new_tab(l, h);

    for (int i = t.start_y; i < h; i++)
    {
        t.cells[i][t.start_x].left = 0;
        t.cells[i][t.start_x + l - 1].right = 0;
    }

    for (int i = t.start_x; i < l; i++)
    {
        t.cells[t.start_y][i].up = 0;
        t.cells[t.start_y + h - 1][i].down = 0;
    }
    return t;
}

// --- fonctions pour afficher le lab ---
void print_tab(Tab tab)
{
    for (int i = tab.start_y; i < tab.height; i++)
    {
        for (int j = tab.start_x; j < tab.width; j++)
            printf("%d %d %d %d   ", tab.cells[i][j].up, tab.cells[i][j].down, tab.cells[i][j].left, tab.cells[i][j].right);
        printf("\n");
    }
}

char *typetostr(type_cell type)
{
    switch (type)
    {
    // case visited:
    //     return " * ";
    case start:
        return " S ";
    case end:
        return " E ";
    case path:
        return " * ";
    default:
        return "   ";
    }
}

void maze_show(Tab t)
{
    for (int i = t.start_y; i < t.height; i++)
    {
        // Imprimer les murs du haut pour chaque cellule
        for (int j = t.start_x; j < t.width; j++)
        {
            printf("+"); // coin supérieur gauche
            if (t.cells[i][j].up)
            {
                printf("   "); // mur nord ouvert
            }
            else
            {
                printf("---"); // mur nord fermé
            }
        }
        printf("+\n");

        // Imprimer les murs de gauche et de droite pour chaque cellule
        for (int j = t.start_x; j < t.width; j++)
        {
            if (t.cells[i][j].left)
            {
                printf(" "); // mur ouest ouvert
            }
            else
            {
                printf("|"); // mur ouest fermé
            }

            printf("%s", typetostr(t.cells[i][j].type)); // espace pour la cellule
        }
        printf("|\n"); // mur est pour la dernière cellule
    }

    // Imprimer les murs du bas pour la dernière rangée
    for (int j = t.start_x; j < t.width; j++)
    {
        printf("+");
        if (t.cells[t.height - 1][j].down)
        {
            printf("   "); // mur sud ouvert
        }
        else
        {
            printf("---"); // mur sud fermé
        }
    }
    printf("+\n");
}

Tab generate(Tab tab, int orientation, int random_wall, int random_orientation) // orientation = 0 : mur vertical
{
    /**
     * @param random_wall : si la position des murs doit etre aleatoire ou alors decouper chaque piece de au milieu
     * @param
     */

    if (tab.height == 1 || tab.width == 1) // codition de sortie
        return tab;

    Tab t1 = tab;
    Tab t2 = tab;
    if (orientation == 0) // si la piece doit etre coupee horizontalement ou verticalement
    {
        int w; // correspond a la pos du mur
        if (random_wall)
            w = rand() % (tab.width - 1) + 1;
        else
            w = (int)(tab.width / 2);

        int w_wall = w + tab.start_x;
        int pos_ouverture = rand() % tab.height;

        for (int i = tab.start_y; i < tab.start_y + tab.height; i++)
        {
            if (i == tab.start_y + pos_ouverture)
            {
                tab.cells[i][w_wall - 1].right = 1;
                tab.cells[i][w_wall].left = 1;
            }
            else
            {
                tab.cells[i][w_wall - 1].right = 0;
                tab.cells[i][w_wall].left = 0;
            }
        }

        t1.width = w;
        t2.width = tab.width - w;
        t2.start_x += w;
    }
    else
    {
        int h;
        if (random_wall)
            h = rand() % (tab.height - 1) + 1;
        else
            h = (int)(tab.height / 2);

        int h_wall = h + tab.start_y;
        int pos_ouverture = rand() % tab.width;
        for (int i = tab.start_x; i < tab.start_x + tab.width; i++)
        {
            if (i == tab.start_x + pos_ouverture)
            {
                tab.cells[h_wall - 1][i].down = 1;
                tab.cells[h_wall][i].up = 1;
            }
            else
            {
                tab.cells[h_wall - 1][i].down = 0;
                tab.cells[h_wall][i].up = 0;
            }
        }

        t1.height = h;
        t2.height = tab.height - h;
        t2.start_y += h;
    }
    if (random_orientation)

    {
        generate(t1, rand() % 2, random_wall, random_orientation);
        generate(t2, rand() % 2, random_wall, random_orientation);
    }
    else
    {
        generate(t1, (orientation + 1) % 2, random_wall, random_orientation);
        generate(t2, (orientation + 1) % 2, random_wall, random_orientation);
    }
    return tab;
}

Lst_co pathfinding(Tab *tab, Lst_co l)
{
    int x = l->x;
    int y = l->y;
    if (tab->cells[y][x].type == end)
    {
        return l;
    }
    tab->cells[y][x].visited = 1;

    if (tab->cells[y][x].up && !tab->cells[y - 1][x].visited)
        l = adjt_co(l, x, y - 1);
    else if (tab->cells[y][x].down && !tab->cells[y + 1][x].visited)
        l = adjt_co(l, x, y + 1);
    else if (tab->cells[y][x].left && !tab->cells[y][x - 1].visited)
        l = adjt_co(l, x - 1, y);
    else if (tab->cells[y][x].right && !tab->cells[y][x + 1].visited)
        l = adjt_co(l, x + 1, y);

    else
        l = supt_co(l);
    return pathfinding(tab, l);
}

void trace_path(Tab tab, Lst_co l)
{
    while (l != NULL)
    {
        if (tab.cells[l->y][l->x].type != start && tab.cells[l->y][l->x].type != end)
            tab.cells[l->y][l->x].type = path;
        l = supt_co(l);
    }
}

int main(int argc, char const *argv[])
{
    // init de random
    srand(time(0));

    // generation du labyrinthe
    Tab generated_tab = generate(tab_start(20, 50), 0, 1, 0);
    Lst_co co_start = init_start(generated_tab);

    Lst_co path = pathfinding(&generated_tab, co_start);
    show_co(path);
    trace_path(generated_tab, path);
    maze_show(generated_tab);

    return 0;
}
