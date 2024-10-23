#include <stdio.h>
#include <stdlib.h>
#include "tab.h"

/**
 * @brief Creates a new Tab struct with the given width and height.
 *
 * The top-left cell is at coordinates (0,0) and the bottom-right cell is at
 * coordinates (width-1,height-1). The bottom-right cell is designated as the
 * end cell.
 *
 * @param width the number of columns in the tab
 * @param height the number of rows in the tab
 *
 * @return a Tab struct with the given width and height
 */
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

/**
 * @brief Frees the memory allocated for the given Tab struct
 *
 * This function releases all the memory allocated for the given Tab struct.
 * It is the user's responsibility to call this function once they are done
 * using a Tab struct to avoid memory leaks.
 *
 * @param tab the Tab struct whose memory should be freed
 */
void free_tab(Tab tab)
{
    for (int i = 0; i < tab.height; i++)
    {
        free(tab.cells[i]);
    }
    free(tab.cells);
}

/**
 * @brief Prints the given Tab struct in the console
 *
 * This function prints the given Tab struct in the console in the following
 * format:
 * up down left right
 *
 * Note that the start_x and start_y fields of the Tab struct are taken into
 * account when printing the tab.
 */
void print_tab(Tab tab)
{
    for (int i = tab.start_y; i < tab.height; i++)
    {
        for (int j = tab.start_x; j < tab.width; j++)
            printf("%d %d %d %d   ", tab.cells[i][j].up, tab.cells[i][j].down, tab.cells[i][j].left, tab.cells[i][j].right);
        printf("\n");
    }
}

/**
 * @brief Prints the given Tab struct as a maze in the console
 *
 * This function prints the given Tab struct as a maze in the console.
 * The maze is printed as a grid of characters, with '+' characters at the
 * corners, '-' characters for the north and south walls, and '|' characters
 * for the west and east walls. The type of each cell is represented by a
 * single character: ' ' for normal cells, 'S' for the start cell, and 'E'
 * for the end cell.
 *
 * @param t the Tab struct to print
 *
 * The start_x and start_y fields of the Tab struct are taken into account
 * when printing the maze.
 */
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

            printf("%s", type_to_str(t.cells[i][j].type)); // espace pour la cellule
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

char *type_to_str(type_cell type)
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
