/*
//////////////////////////////////////////
Grupo 136, Alameda, Rafael Pereira, 83554
//////////////////////////////////////////
*/

#include <stdio.h>
#include <stdlib.h>

int min(int a, int b){
    return(a<b?a:b);
}
int max(int a, int b){
    return(a>b?a:b);
}


/* variaveis globais*/
int numero_subredes_R, numero_routers_vulneraveis_C, ID_sub, id, contador_numero_vertixes, contador_numero_vertixes_aux;
int *List_ID, *Lista_routers_vulneraveis;


/* No de uma lista de adjacencias */
typedef struct Node{
	struct Node* next; /*ponteiro paea o peoximo no*/
    int vertice; /* Representa a aresta do current no */
} *Node;

/* Lista de adjacencias com referencia para o primeiro no*/
typedef struct List {
    Node head;
} *List;

/* Grafo com o numero de vertices e todas as listas de adjacencias*/
typedef struct Graph{
	List List;
    int num_vertices;
} *Graph ;

/* Inicializacao de Funcoes*/
Node createNode(int destino);
Graph createGraph(int num_vertices);
void addEdge(Graph grafo, int fonte, int destino);
int cmpfunc (const void * a, const void * b);
int* sort(int* List_ID, int numero_subredes_R);
void sort_print(int* List_ID, int numero_subredes_R);
/*void AP(Graph grafo);
void AP2(Graph grafo);
void apAUX(Graph grafo, int node, int* isVisited, int* des, int* parent, int* low, int* ap);
void apAUX2(Graph grafo, int node, int* isVisited);*/

/* Funcao que cria os nos*/
Node createNode(int src){
    Node new_Node = (Node) malloc(sizeof(Node*));
    new_Node->vertice = src;
    new_Node->next = NULL;
    return new_Node;
}

/* Funcao que cria grafos*/
Graph createGraph(int num_vertices){
	Graph new_graph = (Graph)malloc(sizeof(Graph*));
    new_graph->num_vertices = num_vertices;
    int i;
    for(i = 0; i<num_vertices; i++){
    	new_graph->List = (List) malloc(num_vertices * sizeof(List*));
    }
    /*inicializa a lista a vazio*/
    for (i = 0; i < num_vertices; i++){
    	new_graph->List[i].head = NULL;
    }
    return new_graph;
}

/* Funcao que cria as arestas em ambas as direcoes*/
void addEdge(Graph graph, int src, int dest){
	dest--;
	src--;
	Node new_node = createNode(dest);
    new_node->next = graph->List[src].head;
    graph->List[src].head = new_node;    

    Node new_node_2 = createNode(src);
    new_node_2->next = graph->List[dest].head;
    graph->List[dest].head = new_node_2;  
}

/* Funcao auxiliar da ap*/
void apAUX(Graph grafo, int node, int* isVisited, int* des, int* parent, int* low, int* ap){
    
	Node current_node = NULL;
    static int time = 0;
    time++;
    des[node]=low[node] = time;
    ID_sub = max(ID_sub, node);
    int children = 0;
    isVisited[node] = 1;
    current_node = grafo->List[node].head;
    int vertice;
    
    while(current_node!=NULL){
    	vertice = current_node->vertice;
       	if(!isVisited[vertice]){
            /*printf("new visit %d\n", vertice+1);  */   
          	children++;
          	parent[vertice] = node;
          	/* o id da sub vai ser o maior vertice presente nesta, logo sera o max entre o id ja existente e o 
          	// tempo de descoberta do vertice atual (e assim sucessivamente correndo os vertices todos)
          	*/
          	apAUX(grafo, current_node->vertice, isVisited, des, parent, low, ap);
        	low[node] = min(low[node], low[current_node->vertice]);
        	/* caso tenha mais de um filho e um ponto vulneravel*/
          	if(parent[node]==-1 && children>1 && ap[node] == 0){
            	if(ap[node] == 0){
            		numero_routers_vulneraveis_C++;
            		ap[node] = 1;
            	}
            }
            /*se nao tiver mais de um filho e se o tempo de descoberta do vertice for maior que o low de algum do filho entao e ponto vulneravel*/
      		if(parent[node]!=-1 && des[node]<=low[current_node->vertice]){
            	if(ap[node] == 0){
            		numero_routers_vulneraveis_C++;
            		ap[node] = 1;
            	}
            }
        }
        else if(current_node->vertice != parent[node]){
            low[node] = min(low[node],des[current_node->vertice]);
        }
        /*printf("valor dentro: %d\n", ID_sub);*/
       	current_node = current_node->next;
    }
    /*printf("valor fora: %d\n", id);*/
    /*id = max(id, ID_sub);*/
    /*printf("valor maximo: %d\n", id);*/
    /*List_ID[numero_subredes_R] = ID_sub;*/
}

/*	Funcao que vai correr o grafo e verificar as ligacoes*/
void AP(Graph grafo){
    int i, auxiliar_index = 0;
    /*inicializa os atributos de todos os vertices a 'vazio'*/
    int* des = (int*)malloc(sizeof(int)*grafo->num_vertices);
    int* isVisited = (int*)malloc(sizeof(int)*grafo->num_vertices);
    int* parent = (int*)malloc(sizeof(int)*grafo->num_vertices);
    int* low = (int*)malloc(sizeof(int)*grafo->num_vertices);
    int* ap = (int*)malloc(sizeof(int)*grafo->num_vertices);
    /*inicializada com o numero de todos os vertices pois todos podem ser um no isolado*/
    List_ID = (int*)malloc(sizeof(int)*grafo->num_vertices);
    for(i=0; i < grafo->num_vertices-1 ;i++){
        isVisited[i] = 0;
        parent[i] = -1;
        ap[i] = 0;
    }
    /*itera todos os vertices e se ainda nao tiver sido visitado chama a funcao auxiliar*/
    for(i = 0; i<grafo->num_vertices; i++){
    	/*vertice ainda nao visitado, ao visita-lo vai visitar toda a sua sub rede, isto e faz uma DFS a este no*/
        if(isVisited[i]==0){
            /*printf("new subtree %d\n", i+1);*/
            apAUX(grafo, i, isVisited, des, parent, low, ap);
            List_ID[numero_subredes_R] = ID_sub+1;
            ID_sub = 0; 
            numero_subredes_R++;
        }
    }
    for(i = 0; i < grafo->num_vertices; i++){

    	/*
    	// printf("apis aqui %d\n", ap[i]);
       	// se o ap estiver a um ativamos a flag e sabemos que i e um articulation point, juntando a lista
        */
        if(ap[i] == 1){
        	Lista_routers_vulneraveis[auxiliar_index] = i;
        	/*printf("esta lista adiciona o: %d\n", Lista_routers_vulneraveis[auxuiliar_index -1]);*/
		auxiliar_index++;
		}
		
    }
    for (i = 0; i < 35; i++) {
    	/*printf("valores que a lista tem fim AP: %d\n", Lista_routers_vulneraveis[i]);*/
    }
}

/*funcao auxiliar da funcao ap2*/
void apAUX2(Graph grafo, int node, int* isVisited){
    contador_numero_vertixes_aux++;
	/*printf("valor aux inicio apaux2: %d\n", contador_numero_vertixes_aux);*/
	Node current_node = NULL;
    isVisited[node] = 1;
    int vertice;
    current_node = grafo->List[node].head;
    while(current_node != NULL){
    	vertice = current_node->vertice;
       	if(!isVisited[vertice] ){
            /*printf("new visit %d\n", vertice+1);*/
          	apAUX2(grafo, vertice, isVisited);
        }
        /*printf("valor dentro: %d\n", contador_numero_vertixes_aux);*/
       	current_node = current_node->next;
    }
    /*printf("valor fora: %d\n", contador_numero_vertixes);
    printf("valor do aux: %d\n", contador_numero_vertixes_aux);*/
    contador_numero_vertixes = max(contador_numero_vertixes, contador_numero_vertixes_aux);
    /*printf("valor maximo: %d\n", contador_numero_vertixes);*/
}

/*funcao que corre o grafo pela segunda vez sem visitar os pontos vulneraveis*/
void AP2(Graph grafo){
	contador_numero_vertixes = 0;
    int i, counter=0;
    /*inicializa os atributos de todos os vertices a 'vazio'*/
    int* isVisited = (int*)malloc(sizeof(int)*grafo->num_vertices);
    /*inicializada com o numero de todos os vertices pois todos podem ser um no isolado*/
    for(i=0; i < grafo->num_vertices ;i++){
    	/*caso o router a que estamos a aceder seja um router isolado marcamos como visitado de forma a nao lhe aceder*/
    	if(Lista_routers_vulneraveis[counter] == i){
    		/*printf("lista que tem: %d\n", Lista_routers_vulneraveis[counter] );*/
    		isVisited[i] = 1;
    		counter++;
    	} 
    	else{
	        isVisited[i] = 0;
    	}
    	/*printf("numero de cenas removidas %d\n", counter);*/
    }
    /*itera todos os vertices e se ainda nao tiver sido visitado chama a funcao auxiliar*/
    for(i=0; i<grafo->num_vertices; i++){
    	/*vertice ainda nao visitado, ao visita-lo vai visitar toda a sua sub rede*/
        if(isVisited[i]==0){
        	/*printf("new subtree %d\n", i+1);*/
			/*printf("node: %d\n", i+1);*/
            apAUX2(grafo, i, isVisited);
            contador_numero_vertixes_aux = 0;
            /*for ( z = 0; z < grafo->num_vertices; z++)
            printf("#vertices %d\n", contador_numero_vertixes);*/
        }
    }
}

int cmpfunc (const void * a, const void * b) {
      return ( *(int*)a - *(int*)b );
}

int* sort(int* Lista_sort, int numero_subredes_R){
	qsort(Lista_sort, numero_subredes_R, sizeof(int), cmpfunc);
	return Lista_sort;

}
void sort_print(int* Lista_sort, int numero_subredes_R){
	int i;
	qsort(Lista_sort, numero_subredes_R, sizeof(int), cmpfunc);
	for(i = 0 ; i < numero_subredes_R - 1; i++ ) {   
		printf("%d ", Lista_sort[i]);
   	}
   	printf("%d\n", Lista_sort[i]);
}

/*
//////////////////////////////////////////////////////////////////////////////////
//						FUNCOES EM DESENVOLVIMENTO EM CIMA
//									Funcao MAIN
////////////////////////////////////////////////////////////////////////////////
*/

int main(int argc, const char * argv[]) {
    int vertices, arestas; 

    int ign = scanf("%d", &vertices);
    ign = scanf("%d", &arestas);

    numero_subredes_R = 0 * ign;
    numero_routers_vulneraveis_C = 0;
    ID_sub = 0;
    Lista_routers_vulneraveis = (int*)malloc(sizeof(int)*vertices);
    Graph grafo = createGraph(vertices);
     
    int ligacoes[arestas][2], i;
    for (i = 0; i < arestas; i++) {
    	ign = scanf("%d %d", &ligacoes[i][0], &ligacoes[i][1]);
        addEdge(grafo, ligacoes[i][0], ligacoes[i][1]); 
    }
    
    AP(grafo);
    /*printf("numero subredes\n");*/
    printf("%d\n", numero_subredes_R);
    /*printf("identificadores subredes\n");*/
    sort_print(List_ID, numero_subredes_R);
    /*printf("routers vulneraveis\n");*/
    printf("%d\n", numero_routers_vulneraveis_C);

    sort(Lista_routers_vulneraveis, numero_routers_vulneraveis_C);
    /*for (i = 0; i < vertices; i++) {
    	printf("valores que a lista tem after sort: %d\n", Lista_routers_vulneraveis[i]);
    }*/

    AP2(grafo);
    /*printf("numero de routers na maior subredes sem os routers vulneraveis\n");*/
    printf("%d\n", contador_numero_vertixes);
    free(grafo);
    return 0;
}