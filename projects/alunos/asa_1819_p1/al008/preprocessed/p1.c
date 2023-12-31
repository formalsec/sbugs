#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct element
{
  int el;
  int d;
  int low;
  int parent;
  int subDiv;
  int visited;
  int isAP;
} *ElementLink;
typedef struct list
{
  ElementLink element;
  struct list *prev;
  struct list *next;
} *ListLink;
int parseArgs(ElementLink *fListEl, ListLink **fListAdj);
void insertElement(ListLink *listAdj, int a, int b, ElementLink listEl);
void updateRegionAdj(ListLink *listAdj, int region, int current);
int comparator(const void *a, const void *b);
void getDivisions(ListLink *listAdj, ElementLink listEl, int size, int *countAP);
void getDivisionsAP(ListLink *listAdj, ElementLink listEl, int size, int *countAP);
void getAP(ListLink *listAdj, ElementLink listEl, int size, int start, int depth, int *countAP);
int main(int argc, char **argv)
{
  int size = 0;
  int countAP = 0;
  ElementLink listEl;
  ListLink *listAdj;
  size = parseArgs(&listEl, &listAdj);
  getDivisions(listAdj, listEl, size, &countAP);
  printf("%d\n", countAP);
  getDivisionsAP(listAdj, listEl, size, &countAP);
  return 0;
}

int parseArgs(ElementLink *fListEl, ListLink **fListAdj)
{
  int i = 0;
  int secondArg;
  int size = 0;
  size = new_sym_var(sizeof(int) * 8);
  ElementLink listEl = (ElementLink) malloc((sizeof(struct element)) * size);
  ListLink *listAdj = (ListLink *) malloc((sizeof(ListLink)) * size);
  for (i = 0; i < size; i++)
  {
    ElementLink newEl = &listEl[i];
    newEl->el = i + 1;
    newEl->d = -1;
    newEl->low = -1;
    newEl->parent = -1;
    newEl->subDiv = -1;
    newEl->visited = 0;
    newEl->isAP = 0;
    listAdj[i] = 0;
  }

  secondArg = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < secondArg; i++)
  {
    int fNum = 0;
    int sNum = 0;
    fNum = new_sym_var(sizeof(int) * 8);
    sNum = new_sym_var(sizeof(int) * 8);
    insertElement(listAdj, fNum, sNum, listEl);
    insertElement(listAdj, sNum, fNum, listEl);
  }

  *fListAdj = listAdj;
  *fListEl = listEl;
  return size;
}

void insertElement(ListLink *listAdj, int a, int b, ElementLink listEl)
{
  ListLink new = (ListLink) malloc(sizeof(struct list));
  ListLink head = listAdj[a - 1];
  new->prev = 0;
  new->element = &listEl[b - 1];
  if (head == 0)
  {
    listAdj[a - 1] = new;
    new->next = 0;
  }
  else
  {
    new->next = head;
    head->prev = new;
    listAdj[a - 1] = new;
  }

}

void updateRegionAdj(ListLink *listAdj, int region, int current)
{
  ListLink head = listAdj[current];
  while (head != 0)
  {
    ElementLink el = head->element;
    if ((el->subDiv == (-1)) && (!el->isAP))
    {
      el->subDiv = region;
      updateRegionAdj(listAdj, region, el->el - 1);
    }
    else
    {
      
    }

    head = head->next;
  }

}

void getDivisions(ListLink *listAdj, ElementLink listEl, int size, int *countAP)
{
  int i;
  int subConj = 0;
  int *output = (int *) malloc((sizeof(int)) * size);
  for (i = size - 1; i >= 0; i--)
  {
    if (listEl[i].subDiv == (-1))
    {
      listEl[i].subDiv = ++subConj;
      updateRegionAdj(listAdj, subConj, i);
      output[listEl[i].subDiv - 1] = i + 1;
    }
    else
    {
      
    }

  }

  printf("%d\n", subConj);
  for (i = subConj - 1; i >= 0; i--)
  {
    if (i == (subConj - 1))
    {
      printf("%d", output[i]);
    }
    else
    {
      printf(" %d", output[i]);
    }

    getAP(listAdj, listEl, size, output[i], 0, countAP);
  }

  if (subConj > 0)
  {
    printf("\n");
  }
  else
  {
    
  }

}

void getDivisionsAP(ListLink *listAdj, ElementLink listEl, int size, int *countAP)
{
  int i;
  int subConj = 0;
  int *count = (int *) malloc((sizeof(int)) * size);
  for (i = 0; i < size; i++)
  {
    count[i] = 0;
  }

  for (i = 0; i < size; i++)
  {
    if ((listEl[i].subDiv == (-1)) && (listEl[i].isAP == 0))
    {
      listEl[i].subDiv = ++subConj;
      updateRegionAdj(listAdj, subConj, i);
    }
    else
    {
      
    }

    count[listEl[i].subDiv - 1]++;
  }

  int max = 0;
  int j;
  for (j = 0; j < subConj; j++)
  {
    if (count[j] > max)
    {
      max = count[j];
    }
    else
    {
      
    }

  }

  printf("%d\n", max);
}

void getAP(ListLink *listAdj, ElementLink listEl, int size, int start, int depth, int *countAP)
{
  ElementLink cur = &listEl[start - 1];
  cur->visited = 1;
  cur->d = depth;
  cur->low = depth;
  cur->subDiv = -1;
  int childCount = 0;
  int isArticulation = 0;
  ListLink next = listAdj[start - 1];
  while (next != 0)
  {
    ElementLink el = next->element;
    if (next->element->visited == 0)
    {
      el->parent = start;
      getAP(listAdj, listEl, size, el->el, depth + 1, countAP);
      childCount++;
      if (el->low >= cur->d)
      {
        isArticulation = 1;
      }
      else
      {
        
      }

      if (el->low < cur->low)
      {
        cur->low = el->low;
      }
      else
      {
        
      }

    }
    else
    {
      if ((el->el != cur->parent) && (el->d < cur->low))
      {
        cur->low = el->d;
      }
      else
      {
        
      }

    }

    next = next->next;
  }

  if (((cur->parent != (-1)) && isArticulation) || ((cur->parent == (-1)) && (childCount > 1)))
  {
    cur->isAP = 1;
    (*countAP)++;
  }
  else
  {
    
  }

}

