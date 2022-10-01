/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
  int x;
  int y;
  struct node *next;
  struct node *previous;
  struct node *nearest;
  float bestDistance;
  struct node *nextInColumn;
  int populated;
  int store;
  int usedInPath;
  int connecting;
} Node;
Node **map;
int M = 0;
int N = 0;
int S = 0;
int C = 0;
void addNodeToMap(Node *node)
{
  int x = node->x;
  Node *currentNode;
  if (map[x] == 0)
  {
    map[x] = node;
    return;
  }
  else
  {
    currentNode = map[x];
    while (currentNode->nextInColumn != 0)
      currentNode = currentNode->nextInColumn;

    currentNode->nextInColumn = node;
  }

}

Node *newNode(int posX, int posY)
{
  Node *new = (Node *) malloc(sizeof(Node));
  new->x = posX;
  new->y = posY;
  new->next = 0;
  new->previous = 0;
  new->nearest = 0;
  new->bestDistance = -1;
  new->nextInColumn = 0;
  new->populated = 0;
  new->store = 0;
  new->usedInPath = 0;
  new->connecting = 0;
  return new;
}

int nodeUsed(Node *node)
{
  return (node->next != 0) || (node->previous != 0);
}

Node *getNode(int x, int y)
{
  if ((((x < 0) || (x >= M)) || (y < 0)) || (y >= N))
  {
    return 0;
  }
  else
  {
    
  }

  Node *currentNode = map[x];
  while ((currentNode != 0) && (currentNode->y != y))
    currentNode = currentNode->nextInColumn;

  if (currentNode == 0)
  {
    Node *new = newNode(x, y);
    addNodeToMap(new);
    currentNode = new;
  }
  else
  {
    
  }

  return currentNode;
}

typedef struct queueElement
{
  Node *node;
  struct queueElement *next;
} QueueElement;
void printQueue(QueueElement *head)
{
  QueueElement *current = head->next;
  printf("\nQUEUE-----------------------\n");
  while (current != 0)
  {
    printf("(%d,%d)\n", current->node->x, current->node->y);
    current = current->next;
  }

  printf("END QUEUE-----------------------\n\n");
}

QueueElement *newQueueElement(Node *node)
{
  QueueElement *newEl = malloc(sizeof(QueueElement));
  newEl->node = node;
  newEl->next = 0;
  return newEl;
}

void push(Node *node, QueueElement *head)
{
  QueueElement *newEl = newQueueElement(node);
  QueueElement *temp = head;
  while (temp->next != 0)
    temp = temp->next;

  temp->next = newEl;
}

QueueElement *popLast(QueueElement *head)
{
  QueueElement *temp = head;
  QueueElement *prev = 0;
  while (temp->next != 0)
  {
    prev = temp;
    temp = temp->next;
  }

  prev->next = 0;
  return temp;
}

QueueElement *popFirst(QueueElement *head)
{
  QueueElement *first = head->next;
  if (first != 0)
  {
    head->next = first->next;
  }
  else
  {
    
  }

  return first;
}

QueueElement *startQueue()
{
  QueueElement *head = newQueueElement(0);
  return head;
}

int queueEmtpy(QueueElement *head)
{
  return head->next == 0;
}

float distanceBetweenNodes(Node *a, Node *b)
{
  float dX = a->x - b->x;
  float dY = a->y - b->y;
  return dX + dY;
}

void sortClosest(int *closest, int size)
{
  int lowest = 0;
  int temp = 0;
  int i = 0;
  int j = 0;
  for (i = 0; i < size; i++)
  {
    lowest = i;
    for (j = i; j < size; j++)
    {
      if (closest[j] < closest[lowest])
      {
        lowest = j;
      }
      else
      {
        
      }

    }

    if (lowest != i)
    {
      temp = closest[i];
      closest[i] = closest[lowest];
      closest[lowest] = temp;
    }
    else
    {
      
    }

  }

}

void sortConnecting(Node **connecting, int size)
{
  Node *temp;
  int lowest = 0;
  int l = 0;
  ;
  int i = 0;
  int j = 0;
  for (i = 0; i < size; i++)
  {
    lowest = connecting[i]->connecting;
    l = i;
    for (j = i; j < size; j++)
    {
      if (connecting[j]->connecting < lowest)
      {
        lowest = connecting[j]->connecting;
        l = j;
      }
      else
      {
        
      }

    }

    if (l != i)
    {
      temp = connecting[i];
      connecting[i] = connecting[l];
      connecting[l] = temp;
    }
    else
    {
      
    }

  }

}

void pushNeighbour(Node *start, Node *origin, int d_x, int d_y, QueueElement *head)
{
  Node *neighbour = getNode(origin->x + d_x, origin->y + d_y);
  if ((((neighbour == 0) || nodeUsed(neighbour)) || (neighbour->store && start->store)) || (neighbour->populated && start->populated))
  {
    return;
  }
  else
  {
    
  }

  neighbour->previous = origin;
  push(neighbour, head);
}

void visitNode(Node *start, Node *node, QueueElement *head)
{
  pushNeighbour(start, node, 1, 0, head);
  pushNeighbour(start, node, 0, 1, head);
  pushNeighbour(start, node, -1, 0, head);
  pushNeighbour(start, node, 0, -1, head);
}

int connectNode(Node *start)
{
  int result = 0;
  QueueElement *head = startQueue();
  QueueElement *trash = startQueue();
  push(start, head);
  QueueElement *current = 0;
  while (!queueEmtpy(head))
  {
    current = popFirst(head);
    if (((current->node->store && start->populated) || (current->node->populated && start->store)) && (current->node->usedInPath != 1))
    {
      Node *node = current->node;
      Node *prev = node->previous;
      while ((prev != 0) && (prev->next == 0))
      {
        node->usedInPath = 1;
        prev->next = node;
        node = prev;
        prev = node->previous;
      }

      result = 1;
      start->usedInPath = 1;
      free(current);
      break;
    }
    else
    {
      
    }

    push(current->node, trash);
    visitNode(start, current->node, head);
    free(current);
  }

  while (!queueEmtpy(head))
  {
    current = popFirst(head);
    current->node->previous = 0;
    free(current);
  }

  while (!queueEmtpy(trash))
  {
    current = popFirst(trash);
    if (current->node->usedInPath != 1)
    {
      current->node->previous = 0;
    }
    else
    {
      
    }

    free(current);
  }

  free(head);
  free(trash);
  return result;
}

int countConnections(Node *start)
{
  QueueElement *head = startQueue();
  QueueElement *trash = startQueue();
  push(start, head);
  QueueElement *current = 0;
  int found = 0;
  while (!queueEmtpy(head))
  {
    current = popFirst(head);
    if ((current->node->store && start->populated) || (current->node->populated && start->store))
    {
      start->nearest = current->node;
      found++;
    }
    else
    {
      visitNode(start, current->node, head);
    }

    push(current->node, trash);
    free(current);
  }

  if (found == 1)
  {
    Node *node = start->nearest;
    Node *prev = node->previous;
    while ((prev != 0) && (prev->next == 0))
    {
      node->usedInPath = 1;
      prev->next = node;
      node = prev;
      prev = node->previous;
    }

    start->usedInPath = 1;
  }
  else
  {
    
  }

  while (!queueEmtpy(head))
  {
    current = popFirst(head);
    current->node->previous = 0;
    free(current);
  }

  while (!queueEmtpy(trash))
  {
    current = popFirst(trash);
    if (current->node->usedInPath != 1)
    {
      current->node->previous = 0;
    }
    else
    {
      
    }

    free(current);
  }

  free(head);
  free(trash);
  start->connecting = found;
  return found;
}

int main()
{
  int x = 0;
  int y = 0;
  int i = 0;
  Node **citizens;
  Node **supermarkets;
  int *closest;
  if (2 <= 0)
  {
    return -1;
  }
  else
  {
    M = new_sym_var(sizeof(int) * 8);
    N = new_sym_var(sizeof(int) * 8);
    
  }

  if (2 <= 0)
  {
    return -1;
  }
  else
  {
    S = new_sym_var(sizeof(int) * 8);
    C = new_sym_var(sizeof(int) * 8);
    
  }

  map = malloc(M * (sizeof(Node *)));
  for (i = 0; i < M; i++)
    map[i] = 0;

  supermarkets = malloc(S * (sizeof(Node *)));
  for (i = 0; i < S; i++)
  {
    if (2 <= 0)
    {
      return -1;
    }
    else
    {
      x = new_sym_var(sizeof(int) * 8);
      y = new_sym_var(sizeof(int) * 8);
      
    }

    supermarkets[i] = newNode(x - 1, y - 1);
    supermarkets[i]->store = 1;
    addNodeToMap(supermarkets[i]);
  }

  citizens = malloc(C * (sizeof(Node *)));
  closest = malloc((sizeof(int)) * C);
  for (i = 0; i < C; i++)
  {
    if (2 <= 0)
    {
      return -1;
    }
    else
    {
      x = new_sym_var(sizeof(int) * 8);
      y = new_sym_var(sizeof(int) * 8);
      
    }

    citizens[i] = newNode(x - 1, y - 1);
    citizens[i]->populated = 1;
    addNodeToMap(citizens[i]);
    closest[i] = i;
  }

  int changed = 1;
  int k = 0;
  int *countSup = malloc(S * (sizeof(int)));
  int *countCit = malloc(C * (sizeof(int)));
  while (changed != 0)
  {
    changed = 0;
    for (i = 0; i < S; i++)
    {
      if (supermarkets[i]->usedInPath)
      {
        continue;
      }
      else
      {
        
      }

      countSup[i] = countConnections(supermarkets[i]);
      if (countSup[i] == 1)
      {
        changed = 1;
      }
      else
      {
        
      }

    }

    for (i = 0; i < C; i++)
    {
      if (citizens[i]->usedInPath)
      {
        continue;
      }
      else
      {
        
      }

      countCit[i] = countConnections(citizens[i]);
      if (countCit[i] == 1)
      {
        changed = 1;
      }
      else
      {
        
      }

    }

  }

  sortConnecting(citizens, C);
  for (i = 0; i < C; i++)
  {
    if (!citizens[i]->usedInPath)
    {
      k = connectNode(citizens[i]);
      sortConnecting(citizens, C);
    }
    else
    {
      
    }

  }

  k++;
  int numberOfConnections = 0;
  for (i = 0; i < S; i++)
  {
    if (supermarkets[i]->usedInPath == 1)
    {
      numberOfConnections++;
    }
    else
    {
      
    }

  }

  printf("%d\n", numberOfConnections);
  for (i = 0; i < M; i++)
  {
    Node *current = map[i];
    Node *next = 0;
    while (current->nextInColumn != 0)
    {
      next = current->nextInColumn;
      free(current);
      current = next;
    }

  }

  free(countSup);
  free(countCit);
  free(map);
  free(supermarkets);
  free(citizens);
  free(closest);
  return 0;
}
