#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

struct vertex{
  int x;
  int y;
};

struct edge{
    struct edge* next;
    struct edge* previus;
    struct vertex destination;
    struct vertex origin;
};


struct vertice{
  struct edge* head;
  struct vertice* nextqueue;
  struct vertex vertex;
  struct vertex father;
  int color;
};

struct graph{
  struct vertice*** matrix;
  struct vertice* headqueue;
  struct vertice* tailqueue;
  int m;
  int n;
  int s;
  int c;
};


struct edge* createEdge(int destx, int desty, int origx, int origy){
  struct edge* newEdge = malloc(sizeof(struct edge));
  newEdge->destination.x = destx;
  newEdge->destination.y = desty;
  newEdge->origin.x = origx;
  newEdge->origin.y = origy;
  newEdge->next = NULL;
  newEdge->previus = NULL;
  return newEdge;
}

void addEdge(struct graph* G, int destx, int desty, int origx, int origy){
  struct edge* newEdge = createEdge(destx, desty, origx, origy);
  if (G->matrix[origx][origy]->head != NULL){
    G->matrix[origx][origy]->head->previus = newEdge;
    newEdge->next = G->matrix[origx][origy]->head;
  }
  G->matrix[origx][origy]->head = newEdge;
}

void removeEdge(struct graph* G, int destx, int desty, int origx, int origy){
  struct edge* auxEdge = G->matrix[origx][origy]->head;
  while (auxEdge->destination.x != destx || auxEdge->destination.y != desty){
    auxEdge = auxEdge->next;
  }
  if (auxEdge == G->matrix[origx][origy]->head){
    G->matrix[origx][origy]->head = auxEdge->next;
    if(auxEdge->next != NULL){
      auxEdge->next->previus = auxEdge->previus;
    }
  } else if (auxEdge->next == NULL){
    auxEdge->previus->next = auxEdge->next;
  } else {
    auxEdge->next->previus = auxEdge->previus;
    auxEdge->previus->next = auxEdge->next;
  }
  free(auxEdge);
}

struct vertice* createVertice(int x, int y){
  struct vertice* newVertice = malloc(sizeof(struct vertice));
  newVertice->vertex.x = x;
  newVertice->vertex.y = y;
  newVertice->father.x = -1;
  newVertice->father.y = -1;
  newVertice->color = WHITE;
  newVertice->nextqueue = NULL;
  newVertice->head = NULL;
  return newVertice;
}

void initMatrix(struct graph* G){
  int i, j;
  for(i=1; i <= G->m *2 ; i++){
    for(j=1; j <= G->n; j++){
      G->matrix[i][j] = createVertice(i, j);
    }
  }
  G->matrix[0][0] = createVertice(0, 0);
  G->matrix[0][1] = createVertice(0, 1);
  for(i=1 ; i <= G->m ; i++){
    for(j=1; j <= G->n; j++){
      if(i-1 >= 1){
        addEdge(G, i, j, i-1 + G->m, j);
      }
      if(i+1 <= G->m){
        addEdge(G, i, j, i+1 + G->m, j);
      }
      if(j-1 >= 1){
        addEdge(G, i, j, i + G->m, j-1);
      }
      if(j + 1 <= G->n){
        addEdge(G, i, j, i + G->m, j+1);
      }
    }
  }
  for(; i <= G->m *2 ; i++){
    for(j=1; j <= G->n; j++){
      addEdge(G, i, j, i - G->m, j);
    }
  }
}


void createSS(struct graph* G){
  int x, y, i;
  char* string = malloc(sizeof(char*));
  for(i=0; i < G->s; i++){
    fgets(string,100, stdin);
    x = atoi(strtok(string," "));
    y = atoi(strtok(NULL,""));
    addEdge(G, 0, 1, x + G->m, y);
  }
  for(i=0; i < G->c; i++){
    fgets(string,100, stdin);
    x = atoi(strtok(string," "));
    y = atoi(strtok(NULL,""));
    addEdge(G, x, y, 0, 0);
  }
  free(string);
}


void initGraph(struct graph* G, int m, int n, int s, int c){
  int i;
  G->m = m;
  G->n = n;
  G->s = s;
  G->c = c;
  G->headqueue = NULL;
  G->tailqueue = NULL;
  G->matrix = malloc((m*2 + 1) * sizeof(struct vertice**));
  G->matrix[0] = malloc(2 * sizeof(struct vertice*));
  for(i = 1; i <= m * 2; i++){
    G->matrix[i] = malloc((n + 1) * sizeof(struct vertice*));
  }
}

void parser(struct graph* G){
  int n=0,m=0,s=0,c=0;
  char* string = malloc(sizeof(char*));
  fgets(string,100, stdin);
  m = atoi(strtok(string," "));
  n = atoi(strtok(NULL,""));
  fgets(string,100, stdin);
  s = atoi(strtok(string," "));
  c = atoi(strtok(NULL,""));
  initGraph(G,m,n,s,c);
  initMatrix(G);
  createSS(G);
  free(string);
  return ;
}


void enqueue(struct graph* G, struct vertice* vertice, struct vertex father) {
  if (G->headqueue == NULL) {
    G->headqueue = G->matrix[vertice->vertex.x][vertice->vertex.y];
    G->tailqueue = G->matrix[vertice->vertex.x][vertice->vertex.y];
  } else {
    G->tailqueue->nextqueue = vertice;
    G->tailqueue = vertice;
  }
  vertice->father.x = father.x;
  vertice->father.y = father.y;
  vertice->color = GRAY;
}

struct vertice* dequeue(struct graph* G){
  struct vertice* vertice = G->headqueue;
  G->headqueue->color = BLACK;
  G->headqueue = G->headqueue->nextqueue;
  return vertice;
}

void initverticetoqueue(struct vertice* vertice) {
  vertice->nextqueue = NULL;
  vertice->father.x = -1;
  vertice->father.y = -1;
  vertice->color = WHITE;
}

void initqueue(struct graph* G) {
  int i, j;
  G->headqueue = G->matrix[0][0];
  G->tailqueue = G->matrix[0][0];
  initverticetoqueue(G->matrix[0][0]);
  initverticetoqueue(G->matrix[0][1]);
  for(i=1; i<= G->m *2; i++){
    for(j=1; j<= G->n;j++){
      initverticetoqueue(G->matrix[i][j]);
    }
  }
}

void foundPath(struct graph* G) {
  struct vertice* u = G->matrix[0][1];
  for (;u->father.x != -1; u = G->matrix[u->father.x][u->father.y]){
    addEdge(G, u->father.x, u->father.y, u->vertex.x, u->vertex.y);
    removeEdge(G, u->vertex.x, u->vertex.y, u->father.x, u->father.y);
  }
}


void printQueue(struct graph* G){
  struct vertice* aux = G->headqueue;
  printf("queue ");
  for(; aux!=NULL;aux = aux->nextqueue){
    printf("| (%d,%d) |", aux->vertex.x,aux->vertex.y);
  }
  printf("\n");
}



int bfs(struct graph* G){
  struct vertice* u;
  struct edge* adj;
  initqueue(G);
  while(G->headqueue != NULL){
    u = dequeue(G);
    for(adj = u->head; adj != NULL; adj = adj->next){
      if (G->matrix[adj->destination.x][adj->destination.y]->color == WHITE){
        enqueue(G, G->matrix[adj->destination.x][adj->destination.y], adj->origin);
      }
      if(adj->destination.x == 0 && adj->destination.y == 1){
        foundPath(G);
        return 1;
      }
    }
  }
  return 0;
}

void algorithm(struct graph* G){
  int contador = 0;
  while(bfs(G)){
    contador++;
  }
  printf("%d\n",contador);
}


void printVertex(struct edge* node){
  printf("(%d,%d)",node->destination.x, node->destination.y);
}

void printGraph(struct graph* G){
  int i, j;
  struct edge* x;
  x = G->matrix[0][0]->head;
  while(x != NULL){
    printVertex(x);
    printf(" -> ");
    x = x->next;
  }
  printf("\n");
  for(i=1; i<=G->m*2; i++){
    for(j=1; j<=G->n; j++){
      x = G->matrix[i][j]->head;
      while(x != NULL){
        printVertex(x);
        printf(" -> ");
        x = x->next;
      }
      printf("\n");
    }
  }

}


int main(){
  struct graph* G = malloc(sizeof(struct graph));
  parser(G);
  algorithm(G);
  return 0;
}
