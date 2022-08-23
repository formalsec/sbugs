/*
segundo projeto de ASA

nome:   Miguel Leonardo
numero: 92529
curso:  LEIC-A
*/
#include <stdio.h>
#include <stdlib.h>

int M, N;
int S, C;

/*estados possiveis dos vertices ou nodos*/
enum color{White, Gray, Black};

/*define o espaco maximo alocado ao vetor
parent (p)*/
int p[100000000];

/*define o espaco maximo alocado ao vetor color*/
enum color color[100000000];

typedef struct node *link;
typedef struct graph *Graph;
typedef struct queue* queue;

struct node {
    int v;
    link next;
};

struct graph {
    int V;
    int E;
    link *adj;
};

struct queue {
  int items[100000000];
  int front;
  int rear;
};

struct arrayofGrays {
    int array[100000000];
    int count;
};

/*vetor que guarda os vertices ja visitados*/
struct arrayofGrays visited;

/*funcao que inicializa uma Queue*/
queue createQueue();

/*funcao que adiciona um elemento a
uma Queue*/
void enqueue(queue q, int);

/*funcao que remove um elemento a
uma Queue*/
int dequeue(queue q);

/*funcao que retorn 1 se Queue a estiver vazia
e 0 se a Queue nao esta vazia*/
int isEmpty(queue q);

/*funcao que inicializa o grafo*/
Graph GRAPHinit(int V);

/*funcao que cria ligacoes entre os vertices
do grafo*/
void GRAPHcreate(Graph G);

/*funcao que insere um nodo/vertice no grafo*/
void insertE(link *head, int v);

/*funcao que insere um nodo/vertice 
do tipo (x,y) no grafo*/
void insertExy(link *head, int x, int y);

/*funcao que apaga um nodo/vertice no grafo*/
void deleteE(link *head, int v);

/*funcao que obtem o numero maximo de
cidadaos*/
void EdmondsKarp(Graph G);

/*funcao que obtem o caminho minimo disponivel
entre a source e o sink*/
int bfs(Graph G);

/*funcao que pinta os caminhos ja visitados
a cinzento (=Gray)*/
void paintGray();

/*funcao que recebe M e N*/
void getMN();

/*funcao que recebe S e C*/
void getSC();

/*funcao que recebe as posicoes dos S e
as posicoes dos C*/
void getSsCs(Graph G);

/*funcao  principal do programa*/
int main() {
    Graph G;
    getMN();
    getSC();
    G = GRAPHinit(M*N+2);
    GRAPHcreate(G);
    getSsCs(G);
    EdmondsKarp(G);
    return 0;
}

void EdmondsKarp(Graph G) {
    int i, f=0;
    /*procura de caminho minimos em cada
    iteracao entre a source e o sink*/
    while(bfs(G)==1) {
        i=G->V-1;
        /*procura no vetor dos pais de um 
        caminho desde o sink ate a source*/
        while(p[i]>=0) {
            if (i!=G->V-1) {
                /*apaga o caminho no sentido
                source - sink*/
                deleteE(&G->adj[p[i]], i);
                visited.array[visited.count]=i;
                visited.count++;
            }
            i=p[i];
        }
        f++;
    }
    printf("%d\n", f);
}

int bfs(Graph G) {
    int u=0, v=0;
    link a;
    struct queue* q = createQueue();
    for (u=1; u<G->V; u++) {
        color[u] = White; p[u]=-1;
    }
    /*pinta os caminhos ja visitados a cinzento*/
    paintGray();
    u=0;
    /*pinta o vertice de origem (source - s) 
    a cinzento*/
    color[0]=Gray; p[0]=-1;
    enqueue(q, 0);
    while (!isEmpty(q)) {
        u = dequeue(q);
        for (a = G->adj[u]; a != NULL; a = a->next) {
            v=a->v;
            if (color[v]==White) {
                color[v]=Gray; p[v]=u;
                enqueue(q, v);
            }
        }
        color[u]=Black;
    }
    /*retorna quando atinge o vertice de destino
    (sink - t)*/
    return color[M*N+1]==Black;
}

void paintGray() {
    int i;
    if (visited.count==0) return;
    if (visited.count!=0) {
        for (i=0; i<visited.count; i++)
            color[visited.array[i]]=Gray; 
    }
}

void getMN() {
    scanf("%d %d", &M, &N);
}

void getSC() {
    scanf("%d %d", &S, &C);
}


void getSsCs(Graph G) {
    int i, v, x, y;
    for(i=0;i<S;i++) {
        scanf("%d %d", &x, &y);   
        /*calculo do valor do vertice*/
        v = (x-1)*N+y;
        /*adicao do vertice ao grafo
        (ligacao a source)*/
        insertE(&G->adj[v], M*N+1);

    }
    for(i=0;i<C;i++) {
        scanf("%d %d", &x, &y);
        /*calculo do valor do vertice*/
        v = (x-1)*N+y;
        /*adicao do vertice ao grafo
        (ligacao ao sink)*/
        insertE(&G->adj[0], v);
    }
}

Graph GRAPHinit(int V) {
    int v;
    Graph G = malloc(sizeof(struct graph));
    G->V = V;
    G->E = 0;
    G->adj = malloc(V * sizeof(link));
    for (v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}

void GRAPHcreate(Graph G) {
    int i=0, x=0, y=0;
    for (i=0; i<M*N+2; i++) insertE(&G->adj[i], i);
    /*establecimento de todas as ligacoes
    entre os vertices do grafo*/
    i=1;
    for (x=1; x<=M; x++)
        for (y=1; y<=N; y++) {
            if (x==1) {
                if (y==1) {
                    /*canto superior esquerdo*/
                    insertExy(&G->adj[i], x, y+1);
                    insertExy(&G->adj[i], x+1, y);
                }
                if (y!=1 && y!=N) {
                    /*limites superiores*/
                    insertExy(&G->adj[i], x, y-1);
                    insertExy(&G->adj[i], x, y+1);
                    insertExy(&G->adj[i], x+1, y);
                }
                if (y==N) {
                    /*canto superior direito*/
                    insertExy(&G->adj[i], x, y-1);
                    insertExy(&G->adj[i], x+1, y);
                }
            }
            if (x!=1 && x!=M) {
                if (y==1) {
                    /*lateral esquerda*/
                    insertExy(&G->adj[i], x-1, y);
                    insertExy(&G->adj[i], x, y+1);
                    insertExy(&G->adj[i], x+1, y);
                }
                if (y!=1 && y!=N) {
                    /*interior*/
                    insertExy(&G->adj[i], x-1, y);
                    insertExy(&G->adj[i], x, y-1);
                    insertExy(&G->adj[i], x, y+1);                    
                    insertExy(&G->adj[i], x+1, y);
                }
                if(y==N) {
                    /*lateral direita*/
                    insertExy(&G->adj[i], x-1, y);
                    insertExy(&G->adj[i], x, y-1);
                    insertExy(&G->adj[i], x+1, y);
                }
            } 
            if (x==M) {
                if (y==1) {
                    /*canto inferior esquerdo*/
                    insertExy(&G->adj[i], x-1, y);
                    insertExy(&G->adj[i], x, y+1);
                }
                if (y!=1 && y!=N) {
                    /*limites inferiores*/
                    insertExy(&G->adj[i], x-1, y);
                    insertExy(&G->adj[i], x, y-1);
                    insertExy(&G->adj[i], x, y+1);
                }
                if (y==N) {
                    /*canto inferior direito*/
                    insertExy(&G->adj[i], x-1, y);
                    insertExy(&G->adj[i], x, y-1);
                }
            }
            i++;
        }
}

void insertE(link *head, int v) {
    link  a = (link)malloc(sizeof(struct node));
    link last = *head;
    a->v = v;
    a->next = NULL;
    if (*head == NULL) {
       *head = a;
       return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = a;
    return;
}

void insertExy(link *head, int x, int y) {
    int v;
    link  a = (link)malloc(sizeof(struct node));
    link last = *head;
    /*calculo do valor do vertice*/
    v = (x-1)*N+y;
    a->v = v;
    a->next = NULL;
    if (*head == NULL) {
       *head = a;
       return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = a;
    return;
}

void deleteE(struct node **head, int v) { 
    struct node *temp = *head, *prev;
    if (temp != NULL && temp->v == v) { 
        *head = temp->next;
        free(temp);
        return; 
    } 
    while (temp != NULL && temp->v != v) { 
        prev = temp;
        temp = temp->next; 
    } 
    if (temp == NULL) return; 
    prev->next = temp->next; 
    free(temp);
}

struct queue* createQueue() {
  struct queue* q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

int isEmpty(struct queue* q) {
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

void enqueue(struct queue* q, int value) {
  if (q->rear == 10000000 - 1)
    return;
  else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

int dequeue(struct queue* q) {
  int item;
  if (isEmpty(q)) {
    item = -1;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
      q->front = q->rear = -1;
    }
  }
  return item;
}