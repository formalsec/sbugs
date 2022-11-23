#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "HashTable.h"

/*---------------------------------------------------------------------------------------
*	hash
*	Gera um index, o qual e utilizado para determinar a gaveta da hashtable.
*--------------------------------------------------------------------------------------*/
int hash(char *v){
	int h = 0, a = 127;

	for (; *v != '\0'; v++)
		h = (a*h + *v) % HASH_LEN;
	return h;
}

/*---------------------------------------------------------------------------------------
*	hash_init_JOGOS
*	Inicializa a hashtable dos Jogos.
*--------------------------------------------------------------------------------------*/
Hash_Jogo* hash_init_JOGOS(){
	Hash_Jogo* HTJ = can_fail_malloc(sizeof(Hash_Jogo));
	HTJ -> gaveta_JOGO = can_fail_calloc(HASH_LEN, sizeof(cabeca_JOGO*));
	return HTJ;
}

/*---------------------------------------------------------------------------------------
*	hash_init_EQUIPAS
*	Inicializa a hashtable das Equipas.
*--------------------------------------------------------------------------------------*/
Hash_Equipa* hash_init_EQUIPAS(){
	Hash_Equipa* HTE = can_fail_malloc(sizeof(Hash_Equipa));
	HTE -> gaveta_EQUIPA = can_fail_calloc(HASH_LEN, sizeof(cabeca_EQUIPA*));
	return HTE;
}

/*---------------------------------------------------------------------------------------
*	hash_insercao_JOGOS
*	Insere jogos novos na hashtable das Jogos.
*--------------------------------------------------------------------------------------*/
void hash_insercao_JOGOS(Hash_Jogo* HTJ, int Chave, Jogo* CJ){
	cabeca_JOGO* CJ_aux = can_fail_malloc(sizeof(cabeca_JOGO));
	CJ_aux -> ptrJOGO = CJ;
	CJ_aux -> proximo = HTJ -> gaveta_JOGO[Chave];
	CJ_aux -> anterior = NULL;
	if (HTJ -> gaveta_JOGO[Chave])
		HTJ -> gaveta_JOGO[Chave] -> anterior = CJ_aux;
	HTJ -> gaveta_JOGO[Chave] = CJ_aux;
}

/*---------------------------------------------------------------------------------------
*	hash_insercao_EQUIPAS
*	Insere equipas novas na hashtable das Equipas.
*--------------------------------------------------------------------------------------*/
void hash_insercao_EQUIPAS(Hash_Equipa* HTE, int Chave, Equipas* CE){
	cabeca_EQUIPA* CE_aux = can_fail_malloc(sizeof(cabeca_EQUIPA));
	CE_aux -> ptrEQUIPA = CE;
	CE_aux -> proximo = HTE -> gaveta_EQUIPA[Chave];
	HTE -> gaveta_EQUIPA[Chave] = CE_aux;
}

/*---------------------------------------------------------------------------------------
*	hash_procura_Jogo
*	Procura jogos na hashtable dos Jogos.
*--------------------------------------------------------------------------------------*/
Jogo* hash_procura_Jogo(Hash_Jogo* HTJ, char* nome){
	int index = hash(nome);
	cabeca_JOGO* aux = HTJ -> gaveta_JOGO[index];
	for (; aux != NULL; aux = aux -> proximo){
		if (strcmp(aux -> ptrJOGO -> nome, nome) == 0)
			return aux -> ptrJOGO;
	}
	return NULL;
}

/*---------------------------------------------------------------------------------------
*	hash_procura_Equipa
*	Procura Equipas na hashtable das Equipas.
*--------------------------------------------------------------------------------------*/
Equipas* hash_procura_Equipa(Hash_Equipa* HTE, char* nome){
	int index = hash(nome);
	cabeca_EQUIPA* aux = HTE -> gaveta_EQUIPA[index];
	for (; aux != NULL; aux = aux -> proximo){
		if (strcmp(aux -> ptrEQUIPA -> nome, nome) == 0)
			return aux -> ptrEQUIPA;
	}
	return NULL;
}

/*---------------------------------------------------------------------------------------
*	cria_lista_Equipas
*	Inicializa a lista principal das Equipas
*--------------------------------------------------------------------------------------*/
Lista_Equipas* cria_lista_Equipas(){
	Lista_Equipas* lista_aux = can_fail_malloc(sizeof(Lista_Equipas));
	lista_aux -> topo = NULL;
	return lista_aux;
}

/*---------------------------------------------------------------------------------------
*	cria_lista_Jogos
*	Inicializa a lista principal das Jogos
*--------------------------------------------------------------------------------------*/
Lista_Jogos* cria_lista_Jogos(){
	Lista_Jogos* lista_aux = can_fail_malloc(sizeof(Lista_Jogos));
	lista_aux -> topo = NULL;
	lista_aux -> fim = NULL;
	return lista_aux;
}

/*---------------------------------------------------------------------------------------
*	Liberta_HTJ
*	Liberta a hashtable dos Jogos.
*--------------------------------------------------------------------------------------*/
void Liberta_HTJ(Hash_Jogo* HTJ){
	cabeca_JOGO* CJ;
	size_t i;
	for (i = 0; i < HASH_LEN; i++){
		while(HTJ -> gaveta_JOGO[i]){
			CJ = HTJ -> gaveta_JOGO[i] -> proximo;
			free(HTJ -> gaveta_JOGO[i]);
			HTJ -> gaveta_JOGO[i] = CJ;
		}
	}
	free(HTJ -> gaveta_JOGO);
	free(HTJ);
}

/*---------------------------------------------------------------------------------------
*	Liberta_HTE
*	Liberta a hashtable das Equipas.
*--------------------------------------------------------------------------------------*/
void Liberta_HTE(Hash_Equipa* HTE){
	cabeca_EQUIPA* CE;
	size_t i;
	for (i = 0; i < HASH_LEN; i++){
		while(HTE -> gaveta_EQUIPA[i]){
			CE = HTE -> gaveta_EQUIPA[i] -> proximo;
			free(HTE -> gaveta_EQUIPA[i]);
			HTE -> gaveta_EQUIPA[i] = CE;
		}
	}
	free(HTE -> gaveta_EQUIPA);
	free(HTE);
}

/*---------------------------------------------------------------------------------------
*	Liberta_Lista_Jogo
*	Liberta a lista dos Jogos.
*--------------------------------------------------------------------------------------*/
void Liberta_Lista_Jogo(Lista_Jogos* CJ){
	Jogo* aux;
	while (CJ -> topo != NULL){
		aux = CJ -> topo;
		CJ -> topo = CJ -> topo -> proximo;
		free(aux -> equipa1);
		free(aux -> equipa2);
		free(aux -> nome);
		free(aux);
	}
	free(CJ);
}

/*---------------------------------------------------------------------------------------
*	Liberta_Lista_Jogo
*	Liberta a lista das Equipas.
*--------------------------------------------------------------------------------------*/
void Liberta_Lista_Equipas(Lista_Equipas* CE){
	Equipas* aux;
	while (CE -> topo != NULL){
		aux = CE -> topo;
		CE -> topo = CE -> topo -> proximo;
		free(aux -> nome);
		free(aux);
	}
	free(CE);
}