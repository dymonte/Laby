#include <stdio.h>
#include <stdlib.h>
#include "verif.h"
#include <math.h>

/**
 * @brief Checks if the given Tab struct is correct
 *
 * This function checks the given Tab struct by iterating over each cell and
 * verifying if the walls are consistent with the adjacent cells.
 *
 * @param tab the Tab struct to be checked
 *
 * @return 1 if the Tab struct is correct, 0 otherwise
 */
int verif_tab(Tab tab)
{
    for (int y = tab.start_y; y < tab.start_x + tab.height; y++)
    {
        for (int x = tab.start_x; x < tab.start_x + tab.width; x++)
        {
            if (tab.cells[y][x].up == 1 && tab.cells[y - 1][x].down != 1)
                return 0;

            if (tab.cells[y][x].down == 1 && tab.cells[y + 1][x].up != 1)
                return 0;

            if (tab.cells[y][x].left == 1 && tab.cells[y][x - 1].right != 1)
                return 0;

            if (tab.cells[y][x].right == 1 && tab.cells[y][x + 1].left != 1)
                return 0;
        }
    }

    return 1;
}

//Check possible gaps between squares by checking next:(x,y) == (x+-1,y) || next(x,y)==(x,y+-1)

/**
 * @brief Verifies if the path represented by the list of coordinates is valid
 *
 * The function checks if the path is valid by iterating over each element of the
 * list and verifying if the adjacent coordinates are within a distance of 1.
 *
 * @param l the list of coordinates representing the path
 *
 * @return 1 if the path is valid, 0 otherwise
 */
int verif_path(Lst_co l)
{
    if (l == NULL)
        return 0;
    while (l->suiv != NULL)
    {
        if (abs(l->x - l->suiv->x) > 1 || abs(l->y - l->suiv->y) > 1)
        {
            return 0;
        }
        l = l->suiv;
    }
    return 1;
}

int verif_gaps(Tab *tab, Lst_co path) {
    Lst_co current = path;

    while (current != NULL && current->suiv != NULL) {
        int x = current->x;
        int y = current->y;
        int next_x = current->suiv->x;
        int next_y = current->suiv->y;

        // Check if the next cell in the path is a valid neighbor
        if (next_y == y + 1 && tab->cells[y][x].down) {
        } else if (next_y == y - 1 && tab->cells[y][x].up) {
        } else if (next_x == x + 1 && tab->cells[y][x].right) {
        } else if (next_x == x - 1 && tab->cells[y][x].left) {
        } else {
            // If none of the valid side match, there's a gap
            printf("Gap detected between (%d, %d) and (%d, %d)\n", x, y, next_x, next_y);
            return 0; // Path has a gap
        }
        current = current->suiv;
    }

    return 1; // Path is continuous if no gaps were found
}



/**
 * @brief Checks if the given width and height are valid
 *
 * @param width the width of the maze
 * @param height the height of the maze
 *
 * @return 1 if the width and height are valid, 0 otherwise
 *
 * A valid width and height are positive integers.
 */
int verif_size(int width, int height)
{
    return width > 0 && height > 0 && (width > 1 || height > 1);
}

/**
 * @brief Exits the program with a status of 0 if the given boolean is false
 *
 * @param b the boolean value to check
 *
 * This function can be used to verify if a condition is true and exit the
 * program if it is false.
 */
void verif_exit(int b, int show_msg)
{
    if (show_msg)
        printf("OK\n");
    if (b == 0)
    {
        fprintf(stderr, "KO\n");
        exit(EXIT_FAILURE);
    }
}



/**
 * @brief Tests the supt_co function by verifying list structure after deletion.
 *
 * This function creates a linked list with three elements, removes the first
 * element using supt_co, and checks if the resulting list's new head is correct.
 * If the test passes, the result will be printed as a success. If the test
 * fails, the program will exit with a failure status. It is used to ensure
 * that supt_co behaves correctly when removing elements from the list.
 */


void test_supt_co() {
    //printf("d");
    Lst_co l1 = new_lst_co(1, 1);
    Lst_co l2 = adjt_co(l1, 2, 2);
    Lst_co l3 = adjt_co(l2, 3, 3);

    Lst_co new_head = supt_co(l3);  
    int passed = (new_head->x == l2->x && new_head->x == 2 && new_head->y == 2);


    free_lst_co(new_head);

    if(passed){
        printf(" test_supt_co OK");
    }
    else{
        fprintf(stderr, " test_supt_co KO\n");
        exit(EXIT_FAILURE);
    }
}
