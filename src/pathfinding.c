#include "../deps/pathfinding.h"

Lst_co pathfinding_recursive(Tab *tab, Lst_co l)
{
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

Lst_co pathfinding_iteratif(Tab *tab, Lst_co l, int show_msg)
{
  int x = l->x;
  int y = l->y;
  int i = 0;

  while (tab->cells[y][x].type != end)
  {
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
Cost calculate_cost(Pos start_pos, Pos end_pos, Pos *actual)
{
  Cost result;

  int xDistance = abs(
      actual->x - start_pos.x); // the formula is current.x - start.x but we
                                // start from end, so in this case start == end
  int yDistance = abs(
      actual->y - start_pos.y); // the formula is current.x - start.x but we
                                // start from end, so in this case start == end
  result.gCost = xDistance + yDistance;

  xDistance = abs(actual->x -
                  end_pos.x); // the formula is current.x - start.x but we
                              // start from end, so in this case start == end
  yDistance = abs(actual->y -
                  end_pos.y); // the formula is current.x - start.x but we
                              // start from end, so in this case start == end
  result.hCost = xDistance + yDistance;

  result.fCost = result.gCost + result.hCost;

  return result;
}

struct as_ll *init_ll_pos(void *a)
{
  Pos *arg = (Pos *)a;
  struct as_ll *result = malloc(sizeof(struct as_ll));
  Pos *p = malloc(sizeof(Pos));
  p->x = arg->x;
  p->y = arg->y;
  result->data = p;
  result->next = NULL;

  return result;
}

struct as_ll *init_ll_cpos(void *a)
{
  CouplePos *arg = (CouplePos *)a;
  struct as_ll *result = malloc(sizeof(struct as_ll));
  CouplePos *p = malloc(sizeof(CouplePos));
  p->actual.x = arg->actual.x;
  p->actual.y = arg->actual.y;
  p->parentPos.x = arg->parentPos.x;
  p->parentPos.y = arg->parentPos.y;
  result->data = p;
  result->next = NULL;

  return result;
}

struct as_ll *add_ll(struct as_ll *head, void *data,
                     struct as_ll *create(void *))
{
  struct as_ll *new = create(data);

  if (head == NULL)
  {
    return new;
  }

  struct as_ll *tmp = head;
  while (tmp->next != NULL)
  {
    tmp = tmp->next;
  }

  tmp->next = new;

  return head;
}

void free_ll(struct as_ll *remove)
{
  remove->next = NULL;
  free(remove->data);
  free(remove);
}

struct as_ll *remove_ll(struct as_ll *head, void *data,
                        bool (*compare)(void *, void *))
{
  if (compare(head->data, data))
  {
    struct as_ll *next = head->next;
    free_ll(head);
    return next;
  }

  struct as_ll *tmp = head;
  while (!(compare(head->next->data, data)))
  {
    tmp = tmp->next;
  }

  struct as_ll *del = tmp->next;
  struct as_ll *next = del->next;
  tmp->next = next;
  free_ll(del);

  return head;
}

int size_ll(struct as_ll *head)
{
  int result = 0;
  struct as_ll *tmp = head;
  while (tmp != NULL)
  {
    result++;
    tmp = tmp->next;
  }

  return result;
}

void *get_ll(struct as_ll *head, int pos)
{
  int i = 0;
  struct as_ll *tmp = head;
  while (tmp != NULL)
  {
    if (i == pos)
      return tmp->data;

    tmp = tmp->next;
    i++;
  }

  return NULL;
}

Pos find_parent_pos(struct as_ll *parentPos, Pos current)
{
  bool reached = false;
  struct as_ll *tmp = parentPos;
  while (!reached)
  {
    CouplePos *couple = (CouplePos *)tmp->data;
    if (couple->actual.x == current.x && couple->actual.y == current.y)
      reached = true;

    tmp = tmp->next;
  }

  CouplePos *final_couple = (CouplePos *)tmp->data;
  Pos final_pos = final_couple->parentPos;

  return final_pos;
}

Lst_co get_path(struct as_ll *parentPos, Pos start_pos, Pos end_pos)
{
  Pos current = {end_pos.x, end_pos.y};
  Lst_co result = new_lst_co(end_pos.x, end_pos.y);

  while (current.x != start_pos.x || current.y != start_pos.y)
  {
    Pos parent = find_parent_pos(parentPos, current);
    result = adjt_co(result, parent.x, parent.y);
    current = parent;
  }

  return result;
}

bool comparePos(void *d1, void *d2)
{
  Pos *p1 = d1;
  Pos *p2 = d2;

  if (p1->x == p2->x && p1->y == p2->y)
  {
    return true;
  }

  return false;
}

bool contains_pos(struct as_ll *lst, Pos p)
{
  struct as_ll *tmp = lst;

  while (tmp != NULL)
  {
    Pos *actual = (Pos *)tmp->data;
    if (actual->x == p.x && actual->y == p.y)
      return true;

    tmp = tmp->next;
  }

  return false;
}

Lst_co a_star_finding(Tab *tab)
{
  Pos end_pos = {tab->width - 1, tab->height - 1};
  Pos current = end_pos;
  Pos start_pos = tab->start;
  struct as_ll *posOpened = init_ll_pos(&current);
  struct as_ll *posChecked = (struct as_ll *)NULL;
  CouplePos couple_current = {current, current};
  struct as_ll *parentPos = init_ll_cpos(&couple_current);
  bool destReached = false;

  while (destReached == false)
  {
    int x = current.x;
    int y = current.y;

    posChecked = add_ll(posChecked, &current, init_ll_pos);

    posOpened = remove_ll(posOpened, &current, comparePos);

    if (tab->cells[y][x].up)
    {
      Pos up = {x, y - 1};
      CouplePos couple_pos = {up, current};

      if (!(contains_pos(posOpened, up) || contains_pos(posChecked, up)))
      {
        posOpened = add_ll(posOpened, &up, init_ll_pos);
        parentPos = add_ll(parentPos, &couple_pos, init_ll_cpos);
      }
    }

    if (tab->cells[y][x].down)
    {
      Pos down = {x, y + 1};
      CouplePos couple_pos = {down, current};
      if (!(contains_pos(posOpened, down) || contains_pos(posChecked, down)))
      {
        posOpened = add_ll(posOpened, &down, init_ll_pos);
        parentPos = add_ll(parentPos, &couple_pos, init_ll_cpos);
      }
    }

    if (tab->cells[y][x].left)
    {
      Pos left = {x - 1, y};
      CouplePos couple_pos = {left, current};
      if (!(contains_pos(posOpened, left) || contains_pos(posChecked, left)))
      {
        posOpened = add_ll(posOpened, &left, init_ll_pos);
        parentPos = add_ll(parentPos, &couple_pos, init_ll_cpos);
      }
    }

    if (tab->cells[y][x].right)
    {
      Pos right = {x + 1, y};
      CouplePos couple_pos = {right, current};
      if (!(contains_pos(posOpened, right) ||
            contains_pos(posChecked, right)))
      {
        posOpened = add_ll(posOpened, &right, init_ll_pos);
        parentPos = add_ll(parentPos, &couple_pos, init_ll_cpos);
      }
    }

    int best_node_index = 0;
    int best_node_fcost = INT_MAX;
    int best_node_gcost = INT_MAX;

    struct as_ll *tmp = posOpened;
    int size_posOpened = size_ll(posOpened);
    for (int i = 0; i < size_posOpened; i++)
    {
      Pos *pos = (Pos *)tmp->data;
      Cost cost = calculate_cost(end_pos, start_pos, pos);

      if (cost.fCost < best_node_fcost)
      {
        best_node_fcost = cost.fCost;
        best_node_gcost = cost.gCost;
        best_node_index = i;
      }
      else if (cost.fCost == best_node_fcost)
      {
        if (cost.gCost < best_node_gcost)
        {
          best_node_gcost = cost.gCost;
          best_node_index = i;
        }
      }
    }

    current = *((Pos *)get_ll(posOpened, best_node_index));

    if (current.x == start_pos.x && current.y == start_pos.y)
    {
      destReached = true;
    }
  }

  Lst_co result_path = get_path(parentPos, end_pos, start_pos);

  return result_path;
}

// ---------------------- End : a star finding section ------------------

void trace_path(Tab tab, Lst_co l)
{
  while (l != NULL)
  {
    if (tab.cells[l->y][l->x].type != start &&
        tab.cells[l->y][l->x].type != end)
      tab.cells[l->y][l->x].type = path;
    l = l->suiv;
  }
}
