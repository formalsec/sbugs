/* Ana Valadares nr.83424 - AL018*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int numero_vertices;
int numero_estacoes;
int numero_fornecedores;


typedef struct _lista{
	struct _lista * next;
	struct _lista * last;
	int valor;
	int peso;
}lista;


typedef struct _ligas{
	struct _ligas * next;
	int origem;
	int destino;
}ligas;


lista * cria_lista ();
void inserir_inicio (lista * original, int inteiro, int peso);
void inserir_fim (lista * original, int inteiro, int peso);
ligas * cria_ligas ();
void inserir_ligas (ligas * original, int origem, int destino);
void Ford_Fulkerson(lista ** ligacoes);
lista * BFS(int root, lista ** ligacoes);
void update_weight(lista * original, int id , int update);
int get_weigth(lista * original, int id);
void Minimal_cut(lista ** ligacoes, int *isVisited);
int dfs(int root, lista ** ligacoes, int *isVisited);



lista * cria_lista (){
	lista * novo = (lista*)malloc(sizeof(lista));
	novo->next = NULL;
	novo->last = novo;
	novo->peso = -1;
	return novo;
}


void inserir_inicio (lista * original, int inteiro, int peso){
	lista * aux = original->next;
	lista * novo;
	novo = (lista*)malloc(sizeof(lista));
	novo->valor = inteiro;
	novo->next = aux;
	original->next = novo;
	if (original->peso == -1 || original->peso > peso) {
		original->peso = peso;
	}
	novo->peso = peso;
}


void inserir_fim (lista * original, int inteiro, int peso){
	lista * base = original->last;
	lista * novo;
	novo = (lista*)malloc(sizeof(lista));
	novo->valor = inteiro;
	novo->next = NULL;
	novo->last = NULL;
	base->next = novo;
	original->last = novo;
	novo->peso = peso;
}


ligas * cria_ligas(){
	ligas * novo = (ligas*)malloc(sizeof(ligas));
	novo->next = NULL;
	return novo;
}


void inserir_ligas (ligas * original, int origem, int destino){
	ligas * novo = (ligas*)malloc(sizeof(ligas));
	novo->origem = origem;
	novo->destino = destino;
	ligas * aux = original->next;
	ligas * before = original;
	while(aux != NULL){
		if(aux->origem > origem){
			before->next = novo;
			novo->next = aux;
			return;
		}
		if (aux->origem == origem && aux->destino > destino){
			before->next = novo;
			novo->next = aux;
			return;
		}
		before = aux;
		aux = aux->next;
	}
	before->next = novo;
	novo->next = aux;
}


void Ford_Fulkerson(lista ** ligacoes) {
	int augmenting = 1;
	int i;
	while(augmenting){
		lista * augmented = BFS(0,ligacoes);
		if (augmented->next == NULL || augmented->peso == 0){
			augmenting = 0;
		}
		else{
			lista * aux = augmented->next;
			while(aux!=NULL){
				lista * next = aux->next;
				if (next == NULL ) break;
				update_weight(ligacoes[aux->valor],next->valor,-augmented->peso);
				update_weight(ligacoes[next->valor],aux->valor, +augmented->peso);
				aux=next;
			}
		}
	}
	int max_flow=0;
	for(i=0;i<numero_vertices;i++){
		max_flow += get_weigth(ligacoes[1],i);
	}
	printf("%d\n",max_flow);

	int *isVisited =(int*)calloc(numero_vertices,sizeof(int));
	Minimal_cut(ligacoes, isVisited);
}


void update_weight(lista * original, int id , int update){
	lista * aux = original->next;
	while(aux != NULL){
		if (aux->valor == id){
			aux->peso += update;
			return;
		}
		aux = aux->next;
	}
	inserir_fim(original, id, update);
}


int get_weigth(lista * original, int id){
	lista * aux = original->next;
	while(aux != NULL){
		if (aux->valor == id){
			return aux->peso;
		}
		aux = aux->next;
	}
	return 0;
}


int not_in_lista(lista * original, int id){
	lista * aux = original->next;
	while(aux != NULL){
		if (aux->valor == id){
			return 0;
		}
		aux = aux->next;
	}
	return 1;
}


lista * BFS(int root, lista ** ligacoes){
	lista * queue = cria_lista();
	inserir_fim(queue, root, 0);
	int isVisited[numero_vertices];
	memset(isVisited, 0, sizeof(isVisited));
	int fatherOf[numero_vertices];
	memset(fatherOf, 0, sizeof(fatherOf));
	isVisited[root] = 1;
	int i;
	lista * aux = queue->next;
	int found_path = 0;
	while(aux != NULL){
		int id = aux ->valor;
		lista * auxiliar = ligacoes[id]->next;
		while(auxiliar!=NULL){
			int arco = auxiliar->peso ;
			i=auxiliar->valor;
			if (arco > 0 && !isVisited[i]){
				fatherOf[i] = id;
				isVisited[i] = 1;
				inserir_fim(queue, i, 0);
				if (i == 1){
					found_path=1;
					break;
				}
			}
			auxiliar = auxiliar->next;
		}
		aux = aux->next;
	}
	lista * augmenting_path = cria_lista();
	if (!found_path) {
		return augmenting_path;
	}
	i = 1;
	int next;
	inserir_inicio(augmenting_path,1,-1);
	while(i!=0){
		next = fatherOf[i];
		inserir_inicio(augmenting_path,next,get_weigth(ligacoes[next],i));
		i=next;
	}
	return augmenting_path;
}


void Minimal_cut(lista ** ligacoes, int *isVisited){
	int i;
	for (i=0;i<numero_vertices;i++){
		if (i!=1 && !isVisited[i]){
			dfs(i, ligacoes, isVisited);
		}
	}

	lista *estacoes = cria_lista();
	ligas *liga = cria_ligas();
	lista * aux;
	for (i=0;i<numero_vertices;i++){
		if (!isVisited[i]){
			aux = ligacoes[i]->next;
			while(aux!=NULL){
				int id = aux->valor;
				if (id && isVisited[id]){
					int i_aux = i;
					if (i > numero_fornecedores + 1 && id >numero_fornecedores + 1){
						i_aux = (i-numero_fornecedores-2)/2 + numero_fornecedores + 2;
						if (not_in_lista(estacoes,i_aux)){
							inserir_fim(estacoes, i_aux, 0);
						}
					}
					else{
						if (i > numero_fornecedores + 1){
							i_aux = (i-numero_fornecedores-2)/2 + numero_fornecedores + 2;
						}
						if(id >numero_fornecedores + 1){
							id = (id-numero_fornecedores-2)/2 + numero_fornecedores + 2;
						}
						inserir_ligas(liga, id, i_aux);
					}
				}
				aux=aux->next;
			}
		}
	}
	aux = estacoes->next;
	while(aux!=NULL){
		if (aux->next == NULL){
			printf("%d",aux->valor);
			break;
		}
		printf("%d ",aux->valor);
		aux = aux->next;
	}
	printf("\n");
	ligas * aux_2 = liga->next;
	while(aux_2!=NULL){
		printf("%d %d\n", aux_2->origem, aux_2->destino);
		aux_2 = aux_2->next;
	}

}


int dfs(int root, lista ** ligacoes, int *isVisited){
	int i;
	isVisited[root] = 1;
	lista * aux = cria_lista();
	inserir_fim(aux, root,0);
	lista * auxiliar = ligacoes[root]->next;
	while(auxiliar!=NULL){
		i = auxiliar->valor;
		if (auxiliar->peso && !isVisited[i]){
			if (i==1){
				aux = aux->next;
				while(aux != NULL){
					isVisited[aux->valor] = 0;
					aux = aux->next;
				}
				return 0;
			}
			inserir_fim(aux, i,0);
			isVisited[i] = 1;
			if (!dfs(i, ligacoes, isVisited)){
				aux = aux->next;
				while(aux != NULL){
					isVisited[aux->valor] = 0;
					aux = aux->next;
				}
				return 0;
			}
		}
		auxiliar = auxiliar->next;
	}
	return 1;
}



int main () {
	
	int numero_ligacoes, producao, capacidade_estacao, origem, destino, capacidade_ligacao, i;
	scanf ("%d %d %d", &numero_fornecedores, &numero_estacoes, &numero_ligacoes);
	numero_vertices = numero_fornecedores+(numero_estacoes*2)+2;

	lista **ligacoes = malloc(numero_vertices * sizeof(lista*));
	for (i=0; i< numero_vertices; i++){
		ligacoes[i] = cria_lista();
	}

	for (i=0; i<numero_fornecedores; i++){
		scanf ("%d", &producao);
		inserir_fim(ligacoes[0],i+2,producao);
		
	}
	for (i=0; i<numero_estacoes; i++){
		scanf ("%d", &capacidade_estacao);
		inserir_fim(ligacoes[(i*2)+2+numero_fornecedores],(i*2)+3+numero_fornecedores,capacidade_estacao);
		
	}

	for (i=0; i<numero_ligacoes; i++){
		scanf ("%d %d %d", &origem, &destino, &capacidade_ligacao);
		if (origem>numero_fornecedores+1){
			int diff = origem - numero_fornecedores - 2;
			origem = (diff*2) + numero_fornecedores + 3;
		}
		if (destino>numero_fornecedores+1){
			int diff = destino - numero_fornecedores - 2;
			destino = (diff*2) + numero_fornecedores + 2;
		}
		inserir_fim(ligacoes[origem],destino,capacidade_ligacao);		
	}
	Ford_Fulkerson(ligacoes);
	return 0;
}

