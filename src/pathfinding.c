#include "../deps/pathfinding.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Lst_co pathfinding_recursive(Tab *tab, Lst_co l) {
  int x = l->x;
  int y = l->y;
  if (tab->cells[y][x].type == end)
    return l;

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

  return pathfinding_recursive(tab, l);
}

Lst_co pathfinding_iteratif(Tab *tab, Lst_co l, int show_msg) {
  int x = l->x;
  int y = l->y;
  int i = 0;

  while (tab->cells[y][x].type != end) {
    i++;

    x = l->x;
    y = l->y;

    tab->cells[y][x].visited = 1;

    if (tab->cells[y][x].down && !tab->cells[y + 1][x].visited)
      l = adjt_co(l, x, y + 1);
    else if (tab->cells[y][x].right && !tab->cells[y][x + 1].visited)
      l = adjt_co(l, x + 1, y);
    else if (tab->cells[y][x].up && !tab->cells[y - 1][x].visited)
      l = adjt_co(l, x, y - 1);
    else if (tab->cells[y][x].left && !tab->cells[y][x - 1].visited)
      l = adjt_co(l, x - 1, y);
    else
      l = supt_co(l);
    x = l->x;
    y = l->y;
  };

  if (show_msg)
    printf("Number of iterations : %d\n", i);

  return l;
}

// ---------------------- Start :  a star finding section ------------------
Cost calculate_cost(Pos start, Pos end, Pos actual) {
  Cost result;

  int xDistance =
      abs(actual.x - end.x); // the formula is current.x - start.x but we
                             // start from end, so in this case start == end
  int yDistance =
      abs(actual.y - end.y); // the formula is current.x - start.x but we
                             // start from end, so in this case start == end
  result.gCost = xDistance + yDistance;

  xDistance =
      abs(actual.x - start.x); // the formula is current.x - start.x but we
                               // start from end, so in this case start == end
  yDistance =
      abs(actual.y - start.y); // the formula is current.x - start.x but we
                               // start from end, so in this case start == end
  result.hCost = xDistance + yDistance;

  result.fCost = result.gCost + result.hCost;

  return result;
}

struct as_ll *init_ll_pos(int x, int y) {
  struct as_ll *result = malloc(sizeof(struct as_ll));
  Pos *p = malloc(sizeof(Pos));
  p->x = x;
  p->y = y;
  result->data = p;
  result->next = NULL;

  return result;
}

struct as_ll *init_ll_cpos(int x, int y, int parent_x, int parent_y) {
  struct as_ll *result = malloc(sizeof(struct as_ll));
  CouplePos *p = malloc(sizeof(CouplePos));
  p->actual.x = x;
  p->actual.y = y;
  p->parentPos.x = x;
  p->parentPos.y = y;
  result->data = p;
  result->next = NULL;

  return result;
}

struct as_ll *add_ll(struct as_ll *head, struct as_ll *new) {
  if (head == NULL) {
    return new;
  }

  struct as_ll *tmp = head;
  while (tmp->next != NULL) {
    tmp = tmp->next;
  }

  tmp->next = new;

  return head;
}

void free_ll(struct as_ll *remove) {
  remove->next = NULL;
  free(remove->data);
  free(remove);
}

struct as_ll *remove_ll(struct as_ll *head, void *data,
                        bool (*compare)(void *, void *)) {
  if (compare(head->data, data)) {
    struct as_ll *next = head->next;
    free_ll(head);
    return next;
  }

  struct as_ll *tmp = head;
  while (!(compare(head->next->data, data))) {
    tmp = tmp->next;
  }

  struct as_ll *del = tmp->next;
  struct as_ll *next = del->next;
  tmp->next = next;
  free_ll(del);

  return head;
}

void openPos(Pos current, struct as_ll *parentPos, struct as_ll *posOpened) {}

bool comparePos(void *d1, void *d2) {
  Pos *p1 = d1;
  Pos *p2 = d2;

  if (p1->x == p2->x && p1->y == p2->y) {
    return true;
  }

  return false;
}

Lst_co a_star_finding(Tab *tab, Lst_co l) {
  Pos end = {tab->width - 1, tab->height - 1};
  Pos current = end;
  Pos start = tab->start;
  struct as_ll *posOpened = init_ll_pos(current.x, current.y);
  struct as_ll *posChecked = (struct as_ll *)NULL;
  struct as_ll *parentPos = init_ll_cpos(current.x, current.y, NULL, NULL);
  bool destReached = false;

  while (destReached == false) {
    int x = current.x;
    int y = current.y;

    struct as_ll *new = malloc(sizeof(struct as_ll));
    // TODO : improve add_ll

    posChecked = remove_ll(posChecked, &current, comparePos);
  }
}

// ---------------------- End : a star finding section ------------------

void trace_path(Tab tab, Lst_co l) {
  while (l != NULL) {
    if (tab.cells[l->y][l->x].type != start &&
        tab.cells[l->y][l->x].type != end)
      tab.cells[l->y][l->x].type = path;
    l = l->suiv;
  }
}
