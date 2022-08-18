#include "hashtable.h"

/*Funcao de hash adaptada das funcoes 
apresentadas em aula*/
size_t hash(char *v, size_t M){
	size_t h = 0, a = 127;
	for (; *v != '\0'; v++){
		h = (a*h + *v) % M;
		
	}
	return h;
}
/******************************************************************************
 *
 * Parte das Equipas
 *
 *****************************************************************************/

/*Funcao que serve para inicializar a 
hashtable das equipas*/
Hequipas *init_hashE(){
	Hequipas *nova_hashequipas;
	nova_hashequipas = malloc(sizeof(Hequipas)); /*Aloca memoria para a hashtable*/
	nova_hashequipas->cabecas = calloc(MAX_TABLE, sizeof(NodeE*)); /*Coloca tudo a NULL*/
	nova_hashequipas->capacidade = MAX_TABLE; /*Declara a dimensao da hashtable*/
	return nova_hashequipas;	
}


Equipa *hash_insertE(Hequipas *h_eq, Equipa *e, char *buffer){
	Equipa *eq_add = malloc(sizeof(Equipa)); /*Cria e aloca memoria para um ponteiro do tipo eq_add*/
	NodeE *aux = malloc(sizeof(NodeE)); /*Cria e aloca memoria para um ponteiro do tipo NodeE*/
	size_t index = hash(buffer, h_eq->capacidade); /*Obtem o index que ira corresponder a uma posicao da hashtable*/
	eq_add->nome = malloc(strlen(buffer) + 1);/*Aloca memoria para o nome da equipa*/
	strcpy(eq_add->nome, buffer);
	eq_add->proximo = e;
	eq_add->vitorias = 0;/*Introduz a equipa com os dados fornecidos*/
	aux->proximo = h_eq->cabecas[index];
	aux->aponta_equipa = eq_add;
	e = eq_add;
	h_eq->cabecas[index] = aux;/*Poe a equipa na hashtable na posicao fornecida*/
	return e;
}

/*Liberta toda a memoria alocada para a Hashtable das
equipas(Funcao adaptada de uma funcao mostrada em aula)*/
void free_Hequipas(Hequipas *t){
	NodeE *aux;
	size_t i;
	for(i = 0; i < t->capacidade; i++){
		while(t->cabecas[i]){
			aux = t->cabecas[i];
			t->cabecas[i] = t->cabecas[i]->proximo;
			free(aux);
		}
	}
	free(t->cabecas);
	free(t);
}

/*Liberta a lista que contem todas as equipas*/
void free_listaE(Equipa *c){
	Equipa *aux;
	while(c != NULL){
		aux = c;
		c = c->proximo;
		free(aux->nome);
		free(aux);
	}
}

/*Procura uma equipa na hashtable
pelo seu hashcode e retorna verdadeiro(1), caso exista
ou falso(0) caso contrario*/
int procuraE(Hequipas *h_eq, char *nome){
	int index;
	NodeE *tmp;
	index = hash(nome, h_eq->capacidade);
	tmp = h_eq->cabecas[index];
	while(tmp != NULL){
		if(strcmp(tmp->aponta_equipa->nome, nome) == 0){
			return 1;
		}
		tmp = tmp -> proximo;
		
	}
	return 0;
}

/******************************************************************************
 *
 * Parte dos jogos
 *
 *****************************************************************************/
/*Inicializa a Hashtable dos jogos*/
Hjogos *init_hashJ(){
	Hjogos *nova_hashjogos;
	nova_hashjogos = malloc(sizeof(Hjogos));
	nova_hashjogos->cabecas = calloc(MAX_TABLE, sizeof(NodeJ*));
	nova_hashjogos->capacidade = MAX_TABLE;
	return nova_hashjogos;	
}

/*Funcao que insere um jogo na hashtable e numa lista que ira conter todos os jogos*/
void hash_insertJ(Hjogos *h_j, Cabeca_cauda *extremos_lista_jogos, char *buffer, char *equipa1_aux, char *equipa2_aux, int pontos1, int pontos2){
	Jogo *j_add = malloc(sizeof(Jogo));
	NodeJ *aux = malloc(sizeof(NodeJ));
	size_t index = hash(buffer, h_j->capacidade);
	j_add->nome = malloc(strlen(buffer) + 1);
	strcpy(j_add->nome, buffer);
	j_add->equipa1 = malloc(strlen(equipa1_aux) + 1);
	strcpy(j_add->equipa1, equipa1_aux);
	j_add->equipa2 = malloc(strlen(equipa2_aux) + 1);
	strcpy(j_add->equipa2, equipa2_aux);/*formacao de um jogo com toda a informacao fornecida*/
	j_add->proximo = NULL;
	j_add->anterior = extremos_lista_jogos->cauda;
	j_add->pontos1 = pontos1;
	j_add->pontos2 = pontos2;
	if(extremos_lista_jogos->cauda != NULL){
		extremos_lista_jogos->cauda->proximo = j_add; 
	}
	else{
		extremos_lista_jogos->cabeca = j_add;
	}
	extremos_lista_jogos->cauda = j_add;/*Processo que adiciona este jogo a uma lista
	duplamente ligada*/
	aux->proximo = h_j->cabecas[index];
	if(h_j->cabecas[index]){
		h_j->cabecas[index]->anterior = aux;
	}
	aux->anterior = NULL;
	aux->aponta_jogo = j_add;
	h_j->cabecas[index] = aux;/*Adiciona a Hashtable dos jogos*/
}

/*Liberta toda a memoria alocada na Hashtable dos jogos
(Funcao adaptada de uma funcao mostrada em aula)*/
void free_Hjogos(Hjogos *t){
	NodeJ *aux;
	size_t i;
	for(i = 0; i < t->capacidade; i++){
		while(t->cabecas[i]){
			aux = t->cabecas[i];
			t->cabecas[i] = t->cabecas[i]->proximo;
			free(aux);
		}
	}
	free(t->cabecas);
	free(t);
}

/*Liberta toda a memoria alocada para a lista de jogos*/
void free_listaJ(Cabeca_cauda *c){
	Jogo *aux;
	while(c->cabeca != NULL){
		aux = c->cabeca;
		c->cabeca = c->cabeca->proximo;
		free(aux->nome);
		free(aux->equipa1);
		free(aux->equipa2);
		free(aux);
	}
	free(c);
}

/*Procura um jogo na hashtable
pelo seu hashcode e retorna verdadeiro(1), caso exista
ou falso(0) caso contrario*/
int procuraJ(Hjogos *h_j, char *nome){
	int index;
	NodeJ *tmp;
	index = hash(nome, h_j->capacidade);
	tmp = h_j->cabecas[index];
	while(tmp != NULL){
		if(strcmp(tmp->aponta_jogo->nome, nome) == 0){
			return 1;
		}
		tmp = tmp->proximo;
		
	}
	return 0;
}