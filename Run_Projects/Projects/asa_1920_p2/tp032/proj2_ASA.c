/* Projeto 2 ASA 
   ist193734     Beatriz Venceslau
   ist193694     Carolina Ramos
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#define WHITE 0                 /* ainda nao foi acedido */
#define GRAY 1                  /* foi acedido */
#define BLACK 2                 /* foi guardado */
#define MAX_NODES 10000

struct vertice {
    int vIn;          /* numero do vertice*/
    int capacity;     /* quantos cidadaos podem passar no vertice*/
    int flow;         /* quantos cidadaos passam pelo vertice*/
    int vOut[5];      /* lista de vizinhos do vertice*/
};

int n, avenidas, numRuas, cidadaos;  /* n -> numero de vertices do grafo (avinas x numRuas)*/
int indVizinho = -1;
int color[MAX_NODES]; /* array com informacao se vertice ja foi acedido*/               
int pred[MAX_NODES];  /* array dos precedentes no caminho*/
int head,tail;
int q[MAX_NODES+2];

void enqueue (int x) {
    q[tail] = x;
    tail++;
    color[x] = GRAY;
}

int dequeue () {
    int x = q[head];
    head++;
    color[x] = BLACK;
    return x;
}

void condicao(int viz, struct vertice lista[n+2]) {
    int i, preced;
    preced = pred[lista[indVizinho].vOut[viz]];
    for (i=0; lista[preced].vOut[i] != 0; i++);  /*verifica quantos vizinhos tem*/
    if(i >= 2) {                                 /*se so tiver 2 muda o que nao for precedente para WHITE*/
        color[lista[indVizinho].vOut[viz]] = WHITE;
        pred[lista[indVizinho].vOut[viz]] = indVizinho;
    }
}

int bfs (int start, int target, struct vertice lista[n+2]){
    int u,v;
    for (u=0; u<=n+1; u++) {
	    color[u] = WHITE;
    }   
    head = tail = 0;
    enqueue(start);
    pred[start] = -1;
    while (head!=tail) {
        u = dequeue();
        /* Procura todos os vertices vizinhos brancos. Se o flow for 0 guarda na fila de processamento. */
        if( u == 0) {
            for (v=0; v<cidadaos; v++) {
                indVizinho = lista[u].vOut[v];
                if (color[indVizinho]==WHITE && lista[indVizinho].capacity - lista[indVizinho].flow > 0) {
                    enqueue(indVizinho);
                    pred[indVizinho] = u;
                }
            }
        }
        else{
            for (v=0; v<5; v++) {
                indVizinho = lista[u].vOut[v];
                /* Se for o fim do caminho guarda o seu precedente e acaba.*/
                if(indVizinho == n+1 && lista[indVizinho].capacity - lista[indVizinho].flow > 0) {
                    pred[indVizinho] = u;
                    return 1;
                }
                else if (color[indVizinho]==WHITE && lista[indVizinho].capacity - lista[indVizinho].flow > 0) {
                    enqueue(indVizinho);
                    pred[indVizinho] = u;
                    /*se so tiver dois vizinhos (o seu predecedente e um vizinho ja acedido)*/
                    if(lista[indVizinho].vOut[2] == 0) {
                        /*ve qual dos seus vizinhos nao e o seu predecedente*/
                        if(lista[indVizinho].vOut[0] != u){
                            condicao(0, lista); /*coloca esse vizinho como nao acedido (WHITE)*/
                        }
                        else if(lista[indVizinho].vOut[1] != u){
                            condicao(1, lista); /*coloca esse vizinho como nao acedido (WHITE)*/
                        }
                    }
                }
            }
        }
    }
    return color[target]==BLACK;
}

int max_flow (int source, int sink, struct vertice lista[n+2]) {
    int u;
    
    /* Enquanto existe o caminho possivel, aplica o algoritmo. */

    while(bfs(source,sink,lista)) {
        /* Incrementa a flow dos vertices que constituem um caminho. */
        for (u=n+1; u >=0; u=pred[u]) {
            lista[u].flow += 1; 
        }
    }
    /* Retorna quantos supermercados foram acedidos*/
    return lista[sink].flow;
}

int calculaVertice(int avenida, int rua, int numRuas) {
    return rua + (avenida - 1) * numRuas;  /*retorna o numero do vertice nas coordenadas dadas*/
}

void buildGraph(struct vertice lista[n+2]) {
    int i,j, d;
    int supermercados;
    int avenida, rua;
    int vert;

    scanf("%d %d", &supermercados, &cidadaos);

    /* inicializa cada vertice do grafo */
    for (i=0; i <= n+1; i++) {
	    lista[i].vIn = i;
        lista[i].flow = 0;
        lista[i].capacity = 1;
        for(j=0; j<5;j++) {
            lista[i].vOut[j] = 0;
        }
    }
    lista[n+1].vIn = n+1;
    
    /* le a capacidade das arestas dos supermercados */
    lista[n+1].capacity = supermercados;
    for (i=0; i<supermercados; i++) {
	    scanf("%d %d",&avenida,&rua);
        vert= calculaVertice(avenida, rua, numRuas);
	    lista[vert].vOut[0] = n + 1;                            /* coloca o supermercado como vizinho do vertice */
    }
    /* le a capacidade das arestas dos cidadaos */
    lista[0] .capacity = cidadaos;
    for (i=0; i<cidadaos; i++) {
	    scanf("%d %d",&avenida,&rua);
        vert = calculaVertice(avenida, rua, numRuas);
        lista[0].vOut[i] = vert;                                /* coloca os cidadaos como vizinhos dos vertices */
    }
    
    /*calcula os vizinhos de cada vertice do grafo*/
    for(i = 1; i <=n ; i++) {
        if(i % numRuas != 1) {             /*tem vizinho para cima*/
            d = i - 1;
            for(j=0; lista[i].vOut[j] != 0; j++);
            lista[i].vOut[j] = d;
        }
        if(i > numRuas) {                     /*tem vizinho a esquerda*/
            d = i - numRuas;
            for(j=0; lista[i].vOut[j] != 0; j++);
            lista[i].vOut[j] = d;
        }
        if(i <= n - numRuas) {                /*tem vizinho a direita*/
            d = i + numRuas;
            for(j=0; lista[i].vOut[j] != 0; j++);
            lista[i].vOut[j] = d;
        }
        if(i % numRuas != 0) {                 /*tem vizinho para baixo*/
            d = i + 1;
            for(j=0; lista[i].vOut[j] != 0; j++);
            lista[i].vOut[j] = d;
        }        
    }
}

int main () {
    scanf("%d %d", &avenidas, &numRuas);
    n = avenidas*numRuas;                   /*calcula numero de vertices do grafo*/
    struct vertice lista[n+2];              /* lista de vertices do grafo */
    buildGraph(lista);
    int s=0,t=n+1;                          /* s -> source; t-> fim do caminho */
    printf("%d\n",max_flow(s,t, lista));     /* chama algoritmo que procura numero maximo de caminhos possiveis*/
    return 0;
}