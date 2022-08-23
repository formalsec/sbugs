/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


struct cl
{
  int nodenum;
  struct cl *next;
};
struct mainvalue
{
  int val;
  struct cl *prop;
} mainvalue;
void update(int nodenum, int val, struct mainvalue *mainlist)
{
  struct cl *it;
  if (mainlist[nodenum].val < val)
  {
    mainlist[nodenum].val = val;
    if (mainlist[nodenum].prop != 0)
    {
      for (it = mainlist[nodenum].prop; it != 0; it = it->next)
      {
        update(it->nodenum, val, mainlist);
      }

    }
    else
    {
      
    }

  }
  else
  {
    
  }

}

int main()
{
  int nodecount;
  int concount;
  int readval;
  int readval2;
  int i;
  struct mainvalue *mainlist;
  struct cl *connect;
  struct cl *it;
  struct cl *last;
  nodecount = new_sym_var(sizeof(int) * 8);
  concount = new_sym_var(sizeof(int) * 8);
  mainlist = malloc(nodecount * (sizeof(struct mainvalue)));
  for (i = 0; i < nodecount; ++i)
  {
    readval = new_sym_var(sizeof(int) * 8);
    mainlist[i].val = readval;
    mainlist[i].prop = 0;
  }

  for (i = 0; i < concount; ++i)
  {
    readval = new_sym_var(sizeof(int) * 8);
    readval2 = new_sym_var(sizeof(int) * 8);
    readval--;
    readval2--;
    connect = malloc(sizeof(struct cl));
    connect->nodenum = readval;
    if (mainlist[readval2].prop == 0)
    {
      mainlist[readval2].prop = connect;
    }
    else
    {
      for (last = 0, it = mainlist[readval2].prop; it != 0; last = it, it = it->next)
      {
      }

      last->next = connect;
    }

  }

  for (i = 0; i < nodecount; ++i)
  {
    for (it = mainlist[i].prop; it != 0; it = it->next)
    {
      update(it->nodenum, mainlist[i].val, mainlist);
    }

  }

  for (i = 0; i < nodecount; ++i)
    printf("%d\n", mainlist[i].val);

  for (i = 0; i < nodecount; ++i)
  {
    if (mainlist[i].prop != 0)
    {
      for (last = 0, it = mainlist[i].prop; it != 0; last = it, it = it->next)
      {
        free(last);
      }

    }
    else
    {
      
    }

  }

  free(mainlist);
  exit(0);
}

