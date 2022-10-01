/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct corner
{
  int type;
  int *corners;
  int *flow;
  int visited;
  int arrivedFrom;
  int h;
  int e;
} Corner;
typedef struct coord
{
  int x;
  int y;
} Coord;
typedef struct vertex
{
  int index;
  int realIndex;
  struct vertex *next;
} OverflowingVertex;
int V;
int avenues;
int streets;
int nMarkets;
OverflowingVertex *head;
int order[2][6] = {{6, 2, 1, 4, 3, 5}, {0, 2, 1, 4, 3, 6}};
int way[2][6] = {{1, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 0}};
void newOverflowingList()
{
  head = 0;
}

void freeVertex(OverflowingVertex *vertex)
{
  OverflowingVertex *destroy;
  destroy = head;
  head = head->next;
  free(destroy);
}

void freeOverflowingList()
{
  while (head != 0)
  {
    freeVertex(head);
  }

}

void addVertex(int index)
{
  OverflowingVertex *temp;
  OverflowingVertex *newVertex = malloc(sizeof(OverflowingVertex));
  newVertex->index = index;
  index = index % (V - 1);
  newVertex->realIndex = index;
  if ((head == 0) || (head->realIndex > index))
  {
    newVertex->next = head;
    head = newVertex;
  }
  else
  {
    temp = head;
    while ((temp->next != 0) && (temp->next->realIndex < index))
    {
      temp = temp->next;
    }

    newVertex->next = temp->next;
    temp->next = newVertex;
  }

}

int popVertex()
{
  if (head == 0)
  {
    return -1;
  }
  else
  {
    
  }

  int index = head->index;
  freeVertex(head);
  return index;
}

void printList()
{
  OverflowingVertex *printing = head;
  while (printing != 0)
  {
    printf("Index: %d\n", printing->index);
    printing = printing->next;
  }

}

int neighbour(int index, int direction, int way)
{
  int neighbour;
  neighbour = index % (V - 1);
  switch (direction)
  {
    case 1:
      neighbour -= avenues;
      break;

    case 2:
      neighbour -= 1;
      break;

    case 3:
      neighbour += avenues;
      break;

    case 4:
      neighbour += 1;
      break;

    case 5:
      return 0;
      break;

    case 6:
      return ((index + V) - 1) % ((V * 2) - 2);
      break;

    default:
      return V - 1;
      break;

  }

  if (way == 0)
  {
    neighbour += V - 1;
  }
  else
  {
    
  }

  return neighbour;
}

int oppositeDirection(int direction)
{
  if (direction == 6)
  {
    return 6;
  }
  else
  {
    
  }

  direction--;
  return ((direction + 2) % 4) + 1;
}

int cornerID(int avenue, int street)
{
  street--;
  return (street * avenues) + avenue;
}

Coord *cornerCoord(int index, int avenues)
{
  Coord *coord = malloc(sizeof(Coord));
  index--;
  coord->x = (index % avenues) + 1;
  coord->y = (index / avenues) + 1;
  return coord;
}

int firstOverflowingVertex(Corner *map)
{
  return popVertex();
}

int isHigher(Corner *map, int index, int neighbourI)
{
  return map[index].h > map[neighbourI].h;
}

int canGoThere(Corner *map, int candidate, int direction, int way, int place)
{
  if (way == 1)
  {
    return (map[candidate].flow[direction] == 0) && (map[place].visited != (-1));
  }
  else
  {
    return map[candidate].flow[direction] == (-1);
  }

}

void relabel(Corner *map, int index, int lowestNeighbour)
{
  map[index].h = map[lowestNeighbour].h + 1;
}

void push(Corner *map, int index)
{
  int direction;
  int picker;
  int i;
  int j;
  int neighbourI;
  j = 0;
  if (index < (V - 1))
  {
    picker = 0;
  }
  else
  {
    picker = 1;
  }

  int chosenDirection = -1;
  int lowestNeighbour = -1;
  for (i = 0; i < 6; i++)
  {
    direction = order[picker][i];
    if (map[index].corners[direction] == 0)
    {
      continue;
    }
    else
    {
      
    }

    neighbourI = neighbour(index, direction, way[picker][i]);
    if (canGoThere(map, index, direction, way[picker][i], neighbourI))
    {
      if ((lowestNeighbour == (-1)) || (map[neighbourI].h < lowestNeighbour))
      {
        lowestNeighbour = map[neighbourI].h;
        j = i;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  chosenDirection = order[picker][j];
  neighbourI = neighbour(index, chosenDirection, way[picker][j]);
  if (!isHigher(map, index, neighbourI))
  {
    relabel(map, index, neighbourI);
  }
  else
  {
    
  }

  if ((chosenDirection == 5) || (chosenDirection == 0))
  {
    map[index].e--;
    map[neighbourI].e++;
    map[index].flow[chosenDirection]++;
  }
  else
  {
    map[index].e--;
    map[neighbourI].e++;
    addVertex(neighbourI);
    map[index].flow[chosenDirection]++;
    map[neighbourI].flow[oppositeDirection(chosenDirection)]--;
    if (chosenDirection != 6)
    {
      map[neighbour(index, 6, 0)].flow[chosenDirection]++;
      map[neighbour(neighbourI, 6, 0)].flow[oppositeDirection(chosenDirection)]--;
    }
    else
    {
      
    }

  }

}

int getMaxFlow(Corner *map)
{
  int u;
  while (((u = firstOverflowingVertex(map)) > 0) && (nMarkets > map[V - 1].e))
  {
    push(map, u);
  }

  return map[V - 1].e;
}

int main()
{
  int i;
  avenues = new_sym_var(sizeof(int) * 8);
  streets = new_sym_var(sizeof(int) * 8);
  V = (avenues * streets) + 2;
  Corner *map = malloc((sizeof(Corner)) * (V + (avenues * streets)));
  newOverflowingList();
  map[0].type = 5;
  map[0].h = V;
  map[V - 1].type = 0;
  map[V - 1].h = 0;
  map[V - 1].e = 0;
  for (i = 1; i < (V - 1); i++)
  {
    int twin = neighbour(i, 6, 1);
    map[i].type = 3;
    map[twin].type = 3;
    map[i].corners = malloc((sizeof(int)) * 7);
    map[twin].corners = malloc((sizeof(int)) * 7);
    map[i].flow = malloc((sizeof(int)) * 7);
    map[twin].flow = malloc((sizeof(int)) * 7);
    Coord *coord = cornerCoord(i, avenues);
    int x = coord->x;
    int y = coord->y;
    free(coord);
    map[i].corners[6] = 1;
    map[i].flow[6] = 0;
    map[twin].corners[6] = 1;
    map[twin].flow[6] = 0;
    if (x != 1)
    {
      map[i].corners[2] = 1;
      map[i].flow[2] = 0;
      map[twin].corners[2] = 1;
      map[twin].flow[2] = 0;
    }
    else
    {
      map[i].corners[2] = 0;
      map[twin].corners[2] = 0;
    }

    if (y != 1)
    {
      map[i].corners[1] = 1;
      map[i].flow[1] = 0;
      map[twin].corners[1] = 1;
      map[twin].flow[1] = 0;
    }
    else
    {
      map[i].corners[1] = 0;
      map[twin].corners[1] = 0;
    }

    if (x != avenues)
    {
      map[i].corners[4] = 1;
      map[i].flow[4] = 0;
      map[twin].corners[4] = 1;
      map[twin].flow[4] = 0;
    }
    else
    {
      map[i].corners[4] = 0;
      map[twin].corners[4] = 0;
    }

    if (y != streets)
    {
      map[i].corners[3] = 1;
      map[i].flow[3] = 0;
      map[twin].corners[3] = 1;
      map[twin].flow[3] = 0;
    }
    else
    {
      map[i].corners[3] = 0;
      map[twin].corners[3] = 0;
    }

    map[i].corners[5] = 0;
    map[i].corners[0] = 0;
    map[i].flow[5] = 0;
    map[i].flow[0] = 0;
    map[twin].corners[5] = 0;
    map[twin].corners[0] = 0;
    map[twin].flow[5] = 0;
    map[twin].flow[0] = 0;
    map[i].h = 0;
    map[i].e = 0;
    map[twin].h = 0;
    map[twin].e = 0;
  }

  int nHouses;
  nMarkets = new_sym_var(sizeof(int) * 8);
  nHouses = new_sym_var(sizeof(int) * 8);
  map[0].e = -nHouses;
  int direction;
  for (i = 0; i < nMarkets; i++)
  {
    int x;
    int y;
    x = new_sym_var(sizeof(int) * 8);
    y = new_sym_var(sizeof(int) * 8);
    int index = cornerID(x, y);
    int twin = neighbour(index, 6, 1);
    map[index].type = 1;
    for (direction = 1; direction < 5; direction++)
    {
      map[twin].corners[direction] = 0;
    }

    map[twin].corners[0] = 1;
  }

  for (i = 0; i < nHouses; i++)
  {
    int x;
    int y;
    x = new_sym_var(sizeof(int) * 8);
    y = new_sym_var(sizeof(int) * 8);
    int index = cornerID(x, y);
    if ((map[index].type == 1) && (map[index].visited == 0))
    {
      map[index].visited = -1;
      map[V - 1].e++;
    }
    else
    {
      if ((map[index].type != 1) && (map[index].visited == 0))
      {
        if (map[index].e == 0)
        {
          map[index].corners[5] = 1;
          for (direction = 1; direction < 5; direction++)
          {
            map[index].corners[direction] = 0;
          }

          map[index].flow[5] = -1;
          map[index].visited = -1;
          map[index].e = 1;
          addVertex(index);
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

  }

  int maxFlow = getMaxFlow(map);
  printf("%d\n", maxFlow);
  for (i = 0; i < ((V * 2) - 2); i++)
  {
    free(map[i].corners);
    free(map[i].flow);
  }

  freeOverflowingList();
  return 0;
}
