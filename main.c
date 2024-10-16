#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lst_co.h"
#include "tab.h"
#include "generation.h"
#include "pathfinding.h"
#include "verif.h"

/**
 * @brief Initialise le depart du labyrinthe
 *
 * @param[in] tab le labyrinthe
 * @return un pointeur vers une liste chainee representant le depart du labyrinthe
 *
 * Le depart est choisi aleatoirement dans le labyrinthe, mais jamais
 * a la derniere ligne ou colonne pour eviter de casser la sortie.
 * La case de depart est alors affectee comme type 'start'.
 */
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

int main(int argc, char const *argv[])
{
    // Initialisation du générateur de nombres aléatoires
    srand(time(0));

    // Crée et génère le labyrinthe avec les paramètres donnés
    int largeur = 100;
    int hauteur = 100;

    Tab maze = tab_start(largeur, hauteur);

    // Génère un labyrinthe de taille (largeur x hauteur)
    generate(maze, 0, 1, 1);

    // print_tab(maze);

    // Test de la validité du labyrinthe
    verif_exit(verif_tab(maze));

    // Position aléatoire de départ pour le pathfinding
    Lst_co co_start = init_start(maze);

    // Appel de l'algorithme de pathfinding à partir de la position de départ
    Lst_co path = pathfinding_iteratif(&maze, co_start);

    // Test de la validité du chemin
    verif_exit(verif_path(path));

    // Affiche les coordonnées du chemin trouvé
    // show_co(path);

    // Trace le chemin trouvé dans le labyrinthe
    trace_path(maze, path);

    // Affiche le labyrinthe avec le chemin tracé
    maze_show(maze);

    // Libère la mémoire allouée pour la liste et le labyrinthe
    free_lst_co(path);
    free_tab(maze);

    return 0;
}
