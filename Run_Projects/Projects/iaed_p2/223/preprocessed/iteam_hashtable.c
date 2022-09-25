/*File generated by PreProcessor.py*/


#include "iteam_hashtable.h"


static tlink *itheads;
static int L;
int hashint(int n, int m)
{
  int h;
  h = n % m;
  return h;
}

void iTinit(int l)
{
  int i;
  L = l;
  itheads = malloc(L * (sizeof(tlink)));
  for (i = 0; i < L; i++)
  {
    itheads[i] = 0;
  }

}

void iTinsert(Equipa equipa)
{
  int i = hashint(equipa->vitorias, L);
  itheads[i] = TinsertEnd(itheads[i], equipa);
}

void iTdelete(Equipa equipa)
{
  int i = hashint(equipa->vitorias, L);
  itheads[i] = TremoveItem(itheads[i], equipa, 0);
}

tlink iLastList()
{
  int i;
  tlink t;
  for (i = 0; i < L; i++)
  {
    if (itheads[i] != 0)
    {
      t = itheads[i];
    }
    else
    {
      
    }

  }

  return t;
}

int equipasVazioQ()
{
  int i;
  for (i = 0; i < L; i++)
  {
    if (itheads[i] != 0)
    {
      return 0;
    }
    else
    {
      
    }

  }

  return 1;
}

void iTclear()
{
  int i;
  tlink t;
  tlink tmp;
  for (i = 0; i < L; i++)
  {
    if (itheads[i] != 0)
    {
      t = itheads[i];
      while (t != 0)
      {
        tmp = t;
        t = t->next;
        free(tmp);
      }

    }
    else
    {
      
    }

  }

  free(itheads);
}

