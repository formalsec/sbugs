#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "teams.h"


void del_team(void *t)
{
  free(((team *) t)->name);
  free(t);
  return;
}

int cmp_team_str(void *str, void *t)
{
  return strcmp((char *) str, ((team *) t)->name);
}

int cmp_teams_nme(void *a, void *b)
{
  return strcmp(((team *) a)->name, ((team *) b)->name);
}

int cmp_teams_vct(void *a, void *b)
{
  if (((team *) a)->victs != ((team *) b)->victs)
  {
    return ((team *) a)->victs - ((team *) b)->victs;
  }
  else
  {
    
  }

  return strcmp(((team *) a)->name, ((team *) b)->name);
}

void print_team(team *t, int in_line)
{
  printf("%d %s %d\n", in_line, t->name, t->victs);
  return;
}

t_node *change_victs(t_node *root, team *t, int dif)
{
  root = tree_remove(root, cmp_teams_vct, t);
  t->victs += dif;
  return tree_insert(root, cmp_teams_vct, t);
}

