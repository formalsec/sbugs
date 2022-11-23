#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*
 * ********************************************
 * Grupo 119, Alameda.
 * Andre Ferreira, 92423
 * Tiago Semide, 92563
 * ********************************************
 */

#include <stdio.h>
#include <stdlib.h>

/* utilizado na funcao min */
#define INF 100000000

/*
   Estrutura para vertices

   Estados da flag:
   0 - fornecedores
   1 - Abastecimento original
   2 - Abastecimento clone

   Estados de visited
   0 - Vertice nao visitado
   1 - Vertice visitado
*/
typedef struct vertex {
    int height;
    int flow;
    int flag;
    int visited;
}Vertex;

typedef struct aresta {
    int flow;
    int max_flow;
}Aresta;

static Aresta **matriz;
static Vertex *lista;
static int vertices;

static int *op_list;
static int counter;

/* Inicializacao . */
int *stack;
int top = -1;

/* Lista atualizada com os vertices vizinhos de um certo vertice. */
static int * lista_vizinhos;
/* Lista onde sao guardados os vertices que fazem parte da divisao do hipermercado
   do corte minimo mais proximo deste, se um vertice pertencer a esta divisao
   o seu respetivo indice sera 1 caso contrario sera 0. */
static int * lista_resultado;
/* Lista onde sao guardados os armazens cujo aumento implicaria um aumento
   na capacidade maxima. */
static int * lista_armazens;
/* Lista onde sao guardados as ligacoes cujo aumento implicaria um aumento
   na capacidade maxima. */
static int * lista_ligacoes;

/* Capacidade maxima equivale ao fluxo que chegou ao hipermercado. */
int capacidade_maxima() {
    return(lista[1].flow);
}

/* Verifica se a stack esta vazia retornando 1 e 0 caso contrario. */
int stack_isempty() {

   if(top == -1)
      return 1;
   else
      return 0;
}

/* Retorna o valor do topo da stack e remove-o. */
int stack_pop() {
    int data;
    data = stack[top];
    top = top - 1;
    return data;
}

/* Recebe um valor e coloca-o no topo da stack. */
void stack_push(int data) {
    top = top + 1;
    stack[top] = data;
}

/* Coloca o valor do indice recebido no inicio da lista de operacoes. */
void swap(int index) {
    int i,data;
    data = op_list[index];
    for ( i=index; i>0; i--) {
        op_list[i] = op_list[i-1];
    }
    op_list[0] = data;
}

/* Funcao auxiliar que retorna o minimo de dois valores recebidos. */
int min(int a, int b){
  if (a<b) return a;
  return b;
}

/* Empurra o fluxo do vertice u para o vertice v respeitando o fluxo maximo da aresta. */
void push(int u, int v){
    int d = min( lista[u].flow, matriz[u][v].max_flow - matriz[u][v].flow);
    matriz[u][v].flow += d;
    matriz[v][u].flow -= d;
    lista[u].flow -= d;
    lista[v].flow += d;
}

/* Aumenta a altura do vertice a para o minimo possivel de modo a poder enviar
   fluxo para um dos seus vizinhos. */
void relabel(int a) {
  int j,m=INF;
  for( j=1; j<=vertices; j++){
    if( (matriz[a][j].max_flow - matriz[a][j].flow) != 0)
      m = min( m, lista[j].height);
  }
  lista[a].height=m+1;
}

/* Operacao de Discharge do Push-Rellabel, aplica pushes e 
   rellabels ate o vertice u ficar com 0 de excesso */
void discharge(int u) {
    int v,seen=0;
    while( lista[u].flow > 0) {
        if (seen <= vertices) {
            v = seen;
            if ((matriz[u][v].max_flow - matriz[u][v].flow > 0) && (lista[u].height > lista[v].height ))
                push(u,v);
            else
                seen +=1;
        }
        else {
            relabel(u);
            seen = 0;
        }
    }
}

/* Liberta a memoria alocada para a matriz */
void free_matrix(){
    int i;
    for(i=0;i<=vertices;i++)
        free(matriz[i]);
    free(matriz);
}

/* recebe index de um vertice e devolve vizinhos com caminho nao cheios */
void descobre_vizinhos(int s) {
    int i,j;
    /* inicializa  lista_vizinhos */
    for( i = 0; i<= vertices; i++) {
        lista_vizinhos[i] = -1;
    }
    for( i = 1, j = 0; i <= vertices; i++) {
        if(matriz[i][s].max_flow - matriz[i][s].flow != 0) {
            lista_vizinhos[j] = i;
            j++;
        }
    }
}

/* DFS que utiliza o hipermercado como vertice fonte. */
void DFS() {
    int i,s;
    /* Marca todos os vertices como nao visitados, exceto o hipermercado
    que e marcado como visitado e e colocado na stack */
    for(i = 2; i <= vertices; i++)
        lista[i].visited = 0;
    lista[1].visited = 1;
    stack_push(1);

    /* Inicializa a lista de resultados a zero. */
    for(i = 0; i <= vertices; i++)
        lista_resultado[i] = 0;
    lista_resultado[1] = 1;

    while(!stack_isempty()) {
        /* O vertice retirado da stack esta dentro da divisao
        do corte minimo mais proximos do hipermercado. */
        s = stack_pop();
        lista_resultado[s] = 1;

        /* Procura todos os vertices adjacentes do vertice s
        retirado da stack. Se um vertice adjacente ainda nao foi
        visitado, marca-o como visitado e coloca-o na stack. */
        descobre_vizinhos(s);
        for(i = 0; lista_vizinhos[i] != -1; i++) {
            if (lista[lista_vizinhos[i]].visited == 0) {
                lista[lista_vizinhos[i]].visited = 1;
                stack_push(lista_vizinhos[i]);
            }
        }
    }
}

/* Descobre o corte minimo mais perto do hipermercado */
void corte_minimo( int armazens) {
    int i,j,h = 0,k,min,aux1,aux2;

    DFS();

    /* inicializa as listas */
    for(i = 0; i<= vertices; i++)
        lista_armazens[i] = 0;

    for(i = 0; i<= vertices; i++)
        lista_ligacoes[i] = -1;

    for( i = 0; i <= vertices ; i++) {
        if (lista_resultado[i] == 1) {
            /* Caso armazem original ou hipermercado, testa todos os caminhos que chegam ate este vertice
               e verifica se estao cheios de modo a atribuir o corte a uma aresta */
            if((lista[i].flag == 1) || (lista[i].flag == 3)) {
                for(j = 1; j <= vertices; j++) {
                    if(((matriz[j][i].max_flow - matriz[j][i].flow) == 0) && (matriz[j][i].max_flow != 0) && (lista_resultado[j] == 0)) {
                        if (j > vertices - armazens)
                            lista_ligacoes[h] = j - armazens;
                        else
                            lista_ligacoes[h] = j;

                        lista_ligacoes[h+1] = i;
                        h += 2;

                    }
                }
            }
            /* Caso armazem clone, tem apenas um caminho (com origem no seu armazem original respetivo)
               e verifica se este caminho esta cheio ou nao de modo a atribuir o corte ao armazem original ou nao*/
            if((lista[i].flag == 2) && (lista_resultado[i-armazens] == 0)) {
                lista_armazens[i] = 1;
            }
        }
    }

    /* Da print a parte do resultado final dos armazens, por ordem crescente */
    for(i = 0, k = 0; i <= vertices ; i++)
        if ((k == 0) && (lista_armazens[i] != 0))
            {
            printf("%d", i - armazens);
            k = 1;
            }
        else if (lista_armazens[i] != 0)
            printf(" %d", i - armazens);

    printf("\n");

    /* Da print a parte do resultado final das ligacoes, por ordem crescente */
    for( k = 0 ; k < h/2; k++ ) {
      min = INF;
      aux2 = INF;
      aux1 = 0;
      for(i = 0; i < h; i += 2 ) {
        if (min == lista_ligacoes[i]) {
          if(aux2 > lista_ligacoes[1+i])
          {
            min = lista_ligacoes[i];
            aux2 = lista_ligacoes[i+1];
            aux1 = i;
          }
        }
        else if (min > lista_ligacoes[i])
        {
          min = lista_ligacoes[i];
          aux2 = lista_ligacoes[i+1];
          aux1 = i;
        }
      }
        printf("%d %d\n", min,aux2);
        lista_ligacoes[aux1] = INF;
        lista_ligacoes[aux1+1] = INF;
      }
}

int main() {
    int fornecedores, armazens, Ligacoes, i, j, flow, V_Inicial, V_Final, Valor;
    scanf("%d", &fornecedores);
    scanf("%d", &armazens);
    scanf("%d", &Ligacoes);
    vertices = fornecedores + 2 * armazens + 1;

    /* Lista que guarda os vertices */
    lista = (Vertex *)can_fail_malloc((vertices+1) * sizeof(Vertex));
    op_list = (int *)can_fail_malloc(((2 * armazens)+1) * sizeof(int));

    /* Matriz de arestas , Inicializa a matriz com tudo a zeros */
    matriz = (Aresta **)can_fail_malloc((vertices+1) * sizeof(Aresta*));

    for(i = 0; i <= vertices; i++) {
        matriz[i] = (Aresta *)can_fail_malloc((vertices+1) * sizeof(Aresta));
        for(j = 0; j <= vertices; j++) {
            matriz[i][j].flow = 0;
            matriz[i][j].max_flow = 0;
        }
    }
    /* Inicializacao do Hipermercado. */
    lista[1].flow = 0;
    lista[1].height = 0;
    lista[1].flag = 3;

    /* Recebe o input dos fornecedores e guarda-os na lista */
    for(i = 2; i <= fornecedores+1; i++) {
        scanf("%d", &flow);
        lista[i].flow = flow;
        lista[i].height = vertices;
        lista[i].flag = 0;
    }
    /* Recebe o input dos armazens e guarda-os na lista */
    counter = 0;
    for(i = fornecedores + 2; i <= fornecedores + armazens + 1; i++) {
        scanf("%d", &flow);

        lista[i].flow = 0;
        lista[i].height = 0;
        lista[i].flag = 1;

        op_list[counter] = i;
        counter++;

        matriz[i][i + armazens].flow = 0;
        matriz[i][i + armazens].max_flow = flow;

        lista[i + armazens].flow = 0;
        lista[i + armazens].height = 0;
        lista[i + armazens].flag = 2;

        op_list[counter] = i+armazens;
        counter++;
    }

    /* Recebe o input das arestas entre os varios vertices */
    for(i = 0; i < Ligacoes; i++) {
        scanf("%d", &V_Inicial);
        scanf("%d", &V_Final);
        scanf("%d", &Valor);
        if (lista[V_Inicial].flag == 1) {
          matriz[V_Inicial + armazens][V_Final].flow = 0;
          matriz[V_Inicial + armazens][V_Final].max_flow = Valor;
        }
        else {
        matriz[V_Inicial][V_Final].flow = 0;
        matriz[V_Inicial][V_Final].max_flow = Valor;
        }
    }

    /* Da Push a todos os fornecedores para os vertices adjacentes */
    for(i = 2; i < fornecedores + 2; i++) {
        for (j = 1; j <= vertices; j++) {
            if ( matriz[i][j].max_flow > 0 ) {
                push(i,j);
            }
        }
    }

    /* Aplica o algoritmo de Rellabel-To-Front */
    i = 0;
    while (i < counter) {
        int u = op_list[i];
        int old_height = lista[u].height;
        discharge(u);
        if (lista[u].height > old_height) {
            swap(i);
            i = 0;
        }
        else {
            i += 1;
        }
    }

    /* Liberta a memoria que foi alocada para aop_list e aloca a 
       memoria para as proximas listas que iremos utilizar */
    free(op_list);

    lista_armazens = (int*) can_fail_malloc((vertices+1) * sizeof(int));

    lista_ligacoes = (int*) can_fail_malloc((2*(Ligacoes+armazens)+1) * sizeof(int));

    lista_resultado = (int*) can_fail_malloc((vertices+1) * sizeof(int));

    lista_vizinhos = (int*) can_fail_malloc((vertices + 1) * sizeof(int));

    stack = can_fail_malloc(vertices * sizeof(int));

    /* Da print a parte do resultado da capacidade maxima */
    printf("%d\n",capacidade_maxima());

    /* Chama a funcao que da print a segunda parte do resultado, 
       os armazens e as ligacoes que deveriam ser aumentadas*/
    corte_minimo(armazens);

    /* Liberta toda a memoria que tinha sido alocado 
       no programa que ainda nao tinha sido libertada */
    free(lista);
    free_matrix();
    free(stack);
    free(lista_resultado);
    free(lista_vizinhos);
    free(lista_ligacoes);
    free(lista_armazens);

    return 0;
}
