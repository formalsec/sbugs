/*************************************************************
1º Projeto Analise e Sintese de Algoritmos 
2º Semestre 2018/2019
* 
AUTORES:    Diogo Costa, nº 86971
GRUPO:		83
* 
DATA: 17/03/2019
***************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*Definicao de estruturas de dados:
- Routers => Nos
- Rede => Grafo
*/
struct router{
	int id;
	struct router* next;
};

struct Rede{
	int numRouters;
	int tempo_atual;
	int subredes;
	int* visitado;
    int* predecessor;
    int* tempo;
    int* low;
    int* ponto_artic;
	struct router** lista_adj;
};

/*Definicao de funcoues utilizadas*/
struct router* criarRouter(int);
struct Rede* criarRede(int);
int* criarVetor(int);
void addArco(struct Rede*, int, int);
int percorrerRede(struct Rede*);
int contarRouters(struct Rede*, int, int);
void DFS(struct Rede*);
void DFS_Visitar(struct Rede*, int i);
void libertarMemoria(struct Rede*);
int min(int,int);

int main()
{	
	/*Declaracao e inicializacao de variaveis*/
	int i=0, router_x=0, router_y=0, V = 0, E = 0, nponto_artic = 0, a=0;
	/*leitura do numero de routers e ligacoes*/
	if(!scanf("%d %d", &V, &E)) exit(1);
	/*Criacao de rede de acordo com o numero de routers*/
    struct Rede* rede = criarRede(V);
    
    /*Criar lista de adjacencias => leitura de E arcos entre os vertices*/
	for(i = 0; i<E; i++){
		if(!scanf("%d %d", &router_x, &router_y)) exit(1);
		addArco(rede,router_x-1, router_y-1);
	}
	
	/*Aplicacao do algoritmo de Tarjan*/
	DFS(rede);
	
	printf("%d\n", rede->subredes);
	for(i = 0; i<V; i++){
		/*Impressao das raizes de cada uma das subredes => vertice sem predecessor*/
		if(rede->predecessor[i] == -1){
			if(a == 0){
				printf("%d", i+1);
				a++;
			}
			else printf(" %d", i+1);
		}
		/*Contagem dos pontos de articulacao*/
		if(rede->ponto_artic[i] == 1)
			nponto_artic++;
	}		
	printf("\n");
	printf("%d\n", nponto_artic);
	/*Percorrer rede, excluindo os pontos de articulacao de forma a encontrar o maior
	numero de routers ligados que nao sao pontos de articulacao*/
	printf("%d\n", percorrerRede(rede));

	/*Libertacao de toda a memoria utilizada*/
	libertarMemoria(rede);

    return EXIT_SUCCESS;
}

/*Alocacao de memora para vertices/routers*/
struct router* criarRouter(int id){
	struct router* novoRouter = malloc(sizeof(struct router));
	novoRouter->id = id;
	novoRouter->next = NULL;
	return novoRouter;
}

/*Alocacao de memoria para vetores utilizados na rede inicializados com os valores a -1*/
int* criarVetor(int vertices){
	int* novoVetor = malloc(vertices*sizeof(int));
	int i;
	for(i = 0; i<vertices; i++) novoVetor[i] = -1;
	return novoVetor;
}

/*Alocacao de memoria para a rede, seus dados e respetiva lista de adjacencias 
utilizada para identificar as ligacoes entre os routers inicializada a NULL*/
struct Rede* criarRede(int vertices){
	struct Rede* novaRede = malloc(sizeof(struct Rede));
	novaRede->numRouters = vertices;
	novaRede->lista_adj = malloc(vertices * sizeof(struct router*));
	novaRede->visitado = criarVetor(vertices);
    novaRede->predecessor = criarVetor(vertices);
    novaRede->tempo = criarVetor(vertices);
    novaRede->low = criarVetor(vertices);
    novaRede->ponto_artic = criarVetor(vertices);
    
	int i;
	for(i = 0; i<vertices; i++) novaRede->lista_adj[i] = NULL;
	
	return novaRede;
}

/*Criacao de arco entre dois routers
=> Implica adicionar Router2 a lista de adjacencias do Router1
e como o grafo nao e direcionado...
=> Implica adicionar Router1 a lista de adjacencias do Router2*/
void addArco(struct Rede* rede, int Router1, int Router2){
	struct router* novoRouter2 = criarRouter(Router2);
	novoRouter2->next = rede->lista_adj[Router1];
	rede->lista_adj[Router1] = novoRouter2;
	
	struct router* novoRouter1 = criarRouter(Router1);
	novoRouter1->next = rede->lista_adj[Router2];
	rede->lista_adj[Router2] = novoRouter1;
}

/*Inicializacao da contagem do "tempo" e das sub-redes*/
void DFS(struct Rede* rede){
	int i;
	rede->tempo_atual = 0;
	rede->subredes = 0;
	for(i = rede->numRouters-1; i>=0; i--){
		if(rede->visitado[i] == -1){
			rede->subredes++;
			DFS_Visitar(rede, i);
		}
	}
}

/*Funcao recursiva chamada em DFS para identificar pontos de articulacao
que sao os vertices/routers que:
(1) Nao sao raiz, nem folha e possuem tempo[x]<= low[y], sendo y um no filho no grafo
(2) Sao raiz, e possuem mais que 1 filho*/ 
void DFS_Visitar(struct Rede* rede, int i){
	int filhos = 0;
	rede->visitado[i] = 0;
	rede->tempo[i] = rede->tempo_atual;
	rede->low[i] = rede->tempo_atual;
	rede->tempo_atual++;
	
	struct router* temp = rede->lista_adj[i];
	while(temp){
		if(rede->visitado[temp->id] == -1){
			rede->predecessor[temp->id] = i;
			filhos++;
			DFS_Visitar(rede, temp->id);
			
			rede->low[i] = min(rede->low[i],rede->low[temp->id]);
			
			if((rede->predecessor[i] != -1 && rede->low[temp->id] >= rede->tempo[i])
				|| (rede->predecessor[i] == -1 && filhos > 1)){
				rede->ponto_artic[i] = 1;
			}
		}
		else if(temp->id != rede->predecessor[i]){
			rede->low[i] = min(rede->low[i], rede->tempo[temp->id]);
		}
		temp = temp->next;
	}
}

/*Percorrer a rede tal como em DFS mas apenas para contar o numero de Routers adjacentes
ignorando aqueles que sao pontos de articulacao*/
int percorrerRede(struct Rede* rede){
	int v, nRouters = 0, maxRouters = 0;
	for(v = 0; v<rede->numRouters; v++)
	{	
		if(rede->visitado[v] != 1 && rede->ponto_artic[v] == -1){
			rede->visitado[v] = 1;
			nRouters = 1;
			nRouters = contarRouters(rede, nRouters, v);
			if(nRouters > maxRouters)
				maxRouters = nRouters;
		}
	}
	return maxRouters;
}

/*Funcao recursiva que explora routers adjacentes ainda nao visitados que nao sao pontos de articulacao*/
int contarRouters(struct Rede* rede, int nRouters, int v){
	struct router* temp = rede->lista_adj[v];
	while(temp){
		if(rede->visitado[temp->id] != 1 && rede->ponto_artic[temp->id] == -1){
			rede->visitado[temp->id] = 1;
			nRouters++;
			nRouters = contarRouters(rede, nRouters, temp->id);
		}
		temp= temp->next;
	}
	return nRouters;
}

/*Libertacao da memoria utilizada para a execucao do algoritmo*/
void libertarMemoria(struct Rede* rede){
	int v;
	
	free(rede->visitado);
	free(rede->predecessor);
	free(rede->tempo);
    free(rede->low);
    free(rede->ponto_artic);

	for(v = 0; v<rede->numRouters; v++){
		struct router* temp = rede->lista_adj[v];
		while(temp){
			struct router* aux = temp;
			temp = temp->next;
			free(aux);
		}
	}
	
	free(rede->lista_adj);
	free(rede);
	
}

/*Funcao simples para facilitar a identificacao de um valor minimo sem repetir codigo*/
int min(int val1, int val2){
	if(val1<val2) return val1;
	else return val2;
}
