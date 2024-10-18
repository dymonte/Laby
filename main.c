#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lst_co.h"
#include "tab.h"
#include "generation.h"
#include "pathfinding.h"
#include "verif.h"

/**
 * @brief Initializes the start of the maze
 *
 * @param[in] tab the maze
 * @return a pointer to a linked list representing the start of the maze
 *
 * The start is chosen randomly within the maze, but never
 * on the last row or column to avoid breaking the exit.
 * The start cell is then set as type 'start'.
 */
Lst_co init_start(Tab tab, int random_start)
{
    if (!random_start)
    {
        Lst_co l = new_lst_co(0, 0);

        tab.cells[0][0].type = start;

        return l;
    }

    int w = tab.width;
    int random_y = rand() % (tab.height - (w == 1 ? 1 : 0));
    if (random_y == tab.height - 1 && w > 1) // eviter que l'entree ecrase la sortie, si la largeur est inferieure a 1, division par 0
        w--;
    int random_x = rand() % (w);
    Lst_co l = new_lst_co(random_x, random_y);

    tab.cells[random_y][random_x].type = start;
    return l;
}

/**
 * @brief Entry point for the maze generation and pathfinding program
 *
 * This function initializes the random number generator and creates a maze.
 * It generates the maze and verifies its validity.
 * A random starting position is chosen for pathfinding, and the iterative pathfinding
 * algorithm is executed to find a path through the maze. The validity of the
 * path is verified, and the path is traced in the maze, which is then displayed.
 * Finally, the allocated memory for the path and maze structures is freed.
 *
 * @param argc The number of command line arguments
 * @param argv The array of command line arguments
 *
 * @return Returns 0 upon successful execution
 */
int main(int argc, char const *argv[])
{
    if (argc != 6)
    {
        fprintf(stderr, "Usage: %s <width> <height> <random_start> <show_verif> <display>\n", argv[0]);
        return 1;
    }

    int show_msg = atoi(argv[4]); // to show messages

    int display = atoi(argv[5]); // to display the maze

    // Initialize the random number generator
    srand(time(NULL));

    // Create and generate the maze with given parameters
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);

    if (show_msg)
        printf("Verif size (%d x %d) : ", width, height);
    verif_exit(verif_size(width, height), show_msg);

    time_t t = time(&t);

    Tab maze = tab_start(width, height);

    // Generate a maze of size (width x height)
    generate(maze, 0, 1, 0);

    // print_tab(maze);

    // Test the validity of the maze
    if (show_msg)
        printf("Verif integrity of maze : ");
    verif_exit(verif_tab(maze), show_msg);

    // Random starting position for pathfinding
    Lst_co co_start = init_start(maze, atoi(argv[3]));
    if (show_msg)
        printf("Start : (%d, %d)\n", co_start->x, co_start->y);

    double diff_time = difftime(time(NULL), t);
    if (show_msg)
        printf("Time to create the maze : %.2f secondes\n", diff_time);
    time(&t);

    // Call the pathfinding algorithm from the starting position
    Lst_co path = pathfinding_iteratif(&maze, co_start);

    diff_time = difftime(time(NULL), t);
    if (show_msg)
        printf("Time to find the path : %.2f secondes\n", diff_time);

    // Test the validity of the path
    if (show_msg)
        printf("Verif integrity of path : ");
    verif_exit(verif_path(path), show_msg);

    if (show_msg)
        printf("Length of the path : %d\n", len_co(path));

    // Display the coordinates of the found path
    // show_co(path);

    // Trace the found path in the maze
    trace_path(maze, path);

    // Display the maze with the traced path
    if (display)
        maze_show(maze);

    // Free the allocated memory for the list and the maze
    free_lst_co(path);
    free_tab(maze);

    return 0;
}
