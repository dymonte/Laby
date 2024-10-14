#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lst_co.h"
#include "tab.h"
#include "generation.h"
#include "pathfinding.h"

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
    int largeur = 20;
    int hauteur = 50;

    // Génère un labyrinthe de taille (largeur x hauteur)
    Tab generated_tab = generate(tab_start(largeur, hauteur), 0, 1, 0);

    // Position aléatoire de départ pour le pathfinding
    Lst_co co_start = init_start(generated_tab);

    // Appel de l'algorithme de pathfinding à partir de la position de départ
    Lst_co path = pathfinding(&generated_tab, co_start);

    // Affiche les coordonnées du chemin trouvé
    show_co(path);

    // Trace le chemin trouvé dans le labyrinthe
    trace_path(generated_tab, path);

    // Affiche le labyrinthe avec le chemin tracé
    maze_show(generated_tab);

    // Libère la mémoire allouée pour la liste et le labyrinthe
    free_lst_co(path);
    free_tab(generated_tab);

    return 0;
}
