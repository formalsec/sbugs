#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equipas.h"
#include "hashtable_equipas.h"
#include "jogos.h"
#include "hashtable_jogos.h"
#include "lista_ligada_nomes.h"

/* NUmero maximo de caracteres dos nomes das equipas/jogos. */
#define N_LEN 1024
/* Tamanho da(s) hashtable(s). */
#define SIZE_HASH 1439




void adiciona_equipa(table_e **heads, int M, int linha){

	/*----------------------
	ADICIONA UMA NOVA EQUIPA
	----------------------*/

	Equipa *x;
	char nome[N_LEN];
	int key;

	scanf(" %[^\n]", nome);
	key = hash(nome, M);

	/* Mensagem de erro caso a equipa nao exista. */
	if ( (heads[key]!= NULL) && ((x=encontra(equipas_hash(heads[key]), nome))  != NULL) )
		printf("%d Equipa existente.\n", linha);
	else{
		/* Cria equipa. */
		x = cria_equipa(nome);
		/* Adiciona equipa a hashtable de equipas. */
		adiciona_e(heads, x, M);
	}
}



void procura_e(table_e **heads, int M, int linha){

	/*-----------------------------
	PROCURA UMA EQUIPA DADO UM NOME
	-----------------------------*/

	Equipa *x;
	char nome[N_LEN];

	scanf(" %[^\n]", nome);

	/* Mensagem de erro caso a equipa nao exista. */
	if ((x = procura_equipa_hash(heads, nome, M)) == NULL)
		printf("%d Equipa inexistente.\n", linha);
	else
		printf("%d %s %d\n", linha, nome_e(x), jogos_ganhos(x));
}




void adiciona_jogo(table_e **head_e, table_j **heads, Lista **ultimo_jogo, int M, int linha, Lista **lista){

	/*-------------------
	ADICIONA UM NOVO JOGO
	-------------------*/

	Jogo *x;
	Lista *jogo;
	char nome_j[N_LEN], equipa1[N_LEN], equipa2[N_LEN];
	int key, score1, score2;

	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome_j, equipa1, equipa2, &score1, &score2);
	key = hash(nome_j, M);

	/* Mensagem de erro caso o jogo nao exista. */
	if ( (heads[key]!= NULL) && ((x=encontra_j(jogos_hash(heads[key]), nome_j))  != NULL) )
		printf("%d Jogo existente.\n", linha);

	/* Mensagem de erro caso equipa nao exista. */
	else if ( (procura_equipa_hash(head_e, equipa1, M) == NULL) || (procura_equipa_hash(head_e, equipa2, M) == NULL) )
		printf("%d Equipa inexistente.\n", linha);

	else{
		/* cria elemento para lista de nomes de jogos. */
		jogo = cria_elemento(nome_j);
		/* adiciona nome do jogo a lista de nome de jogos ordenados. */
		adiciona_elemento(lista, jogo, ultimo_jogo);
		/* cria estrutura de jogo. */
		x = cria_jogo(nome_j, equipa1, equipa2, score1, score2);
		/* adiciona o jogo a hashtable dos jogos. */
		adiciona_j(heads, x, M);
		/* Altera os jogos ganhos das equipas consoante o score do jogo. */
		if (score1 != score2){
			(score1>score2) ? altera_ganhos(procura_equipa_hash(head_e, equipa1, M), 1) : altera_ganhos(procura_equipa_hash(head_e, equipa2, M), 1);
		}
	}
}





void procura_j(table_j **heads, int M, int linha){

	/*-----------------------------
	PROCURA UM JOGO COM O NOME DADO
	-----------------------------*/

	Jogo *x;
	char nome[N_LEN];

	scanf(" %[^\n]", nome);

	/* Mensagem de erro caso jogo nao exista. */
	if ((x = procura_jogo_hash(heads, nome, M)) == NULL)
		printf("%d Jogo inexistente.\n", linha);
	else
		printf("%d %s %s %s %d %d\n", linha, nome_jogo(x), equipa1_j(x), equipa2_j(x), score1_j(x), score2_j(x));
}





void lista_jogos(table_j **head, Lista *jogos, int M, int linha){

	/*-------------------------------
	LISTA TODOS OS JOGOS INTRODUZIDOS
	-------------------------------*/

	Jogo *x;

	/* Percorre a lista "jogos" dos jogos ordenados pela ordem de intruducao,
	procura-os na hashtable e faz print. */
	for (; jogos != NULL ; jogos = proximo_elemento(jogos)){
		x = procura_jogo_hash(head, nome_lista(jogos), M);
		printf("%d %s %s %s %d %d\n", linha, nome_jogo(x), equipa1_j(x), equipa2_j(x), score1_j(x), score2_j(x));

	}
}






void remove_jogo(table_j **heads_j, table_e **heads_e,  Lista **listas, Lista **ultimo_jogo, int M, int linha_input){

	/*------------------------------------
	REMOVE UM JOGO DO SISTEMA DADO UM NOME
	------------------------------------*/

	char nome[N_LEN];
	Jogo *jogo;
	Equipa *equipa;

	scanf(" %[^\n]", nome);

	/* Mensagem de erro caso jogo nao exista. */
	if ((jogo = procura_jogo_hash(heads_j, nome, M)) == NULL)
		printf("%d Jogo inexistente.\n", linha_input);

	else{
		/* Altera o score das equipas consoante os scores do jogo que serao eliminados. **/
		if ( score1_j(jogo) > score2_j(jogo) ){
			equipa = procura_equipa_hash(heads_e, equipa1_j(jogo), M);
			altera_ganhos(equipa, 0);
		}
		else if ( score1_j(jogo) < score2_j(jogo) ){
			equipa = procura_equipa_hash(heads_e, equipa2_j(jogo), M);
			altera_ganhos(equipa, 0);
		}

		/* Remove o jogo da hastable. */ 
		remove_j(heads_j, nome, M);
		/* Remove o nome do jogo da lista ordenada de jogos. */
		ultimo_jogo = remove_el(listas, ultimo_jogo, nome);

	}
}






void altera_score(table_j **jogos, table_e **equipas, int M, int linha_input){

	/*-----------------------------------
	ALTERA O SCORE DE UM JOGO DADO O NOME
	-----------------------------------*/

	Jogo *x;
	Equipa *e1, *e2;
	char nome[N_LEN];
	int s1, s2;

	scanf(" %[^:]:%d:%d", nome, &s1, &s2);

	/* Guarda em x o jogo "nome" da hashtable. */
	x = procura_jogo_hash(jogos, nome, M);

	if (x != NULL){

		/* Guarda as equipas 1 e 2 do jogo em e1 e e2 respetivamente. */
		e1 = procura_equipa_hash(equipas, equipa1_j(x), M);
		e2 = procura_equipa_hash(equipas, equipa2_j(x), M);

		/* Altera o numero de jogos ganhos de cada uma das equipas consoante o novo resultado. */
		if ( ( (score1_j(x) < score2_j(x)) || (score1_j(x) == score2_j(x)) ) && (s1 > s2) ){
			altera_ganhos(e1, 1);
		}
		else if ( (score1_j(x) > score2_j(x)) && ((s2>s1) || (s2 == s1)) ){
			altera_ganhos(e1, 0);
		}

		if ( (score1_j(x) < score2_j(x)) && ((s1 > s2) || (s1 == s2)) ){
			altera_ganhos(e2, 0);
		}
		else if ( ( (score1_j(x) > score2_j(x)) || (score1_j(x)==score2_j(x)) ) && (s1 < s2) ){
			altera_ganhos(e2, 1);
		}


		/* Altera o score do jogo. */
		score1_j(x) = s1;
		score2_j(x) = s2;
	}
	/* Mensagem de erro. */
	else{
		printf("%d Jogo inexistente.\n", linha_input);
	}
}






void swap(char **arr, int i, int l){

	/*-----------------------------------
	FUNCAO AUXILAR - TROCA DOIS ELEMENTOS
	-----------------------------------*/

	char aux[1024];
	strcpy(aux, arr[i]), strcpy(arr[i],arr[l]), strcpy(arr[l],aux);
}


void heapify(char **arr, int n, int i) { 

	/*------------------------
	FUNCAO SECUNDARIA HEAPSORT
	------------------------*/

    int largest = i; /* Inicializa largest como raiz. */
    int l = 2*i + 1;
    int r = 2*i + 2;
  
    /* Se a crianca esquerda > raiz. */
    if (l < n && strcmp(arr[l], arr[largest]) < 0) 
        largest = l; 
  
    /* Se a crianca direita > raiz */
    if (r < n && strcmp(arr[r], arr[largest]) < 0) 
        largest = r; 
  
    /* Se largest nao e raiz*/
    if (largest != i) 
    { 
        swap(arr, i, largest); 
  
        /* Recursivamente "heapifica" a sub-arvore. */ 
        heapify(arr, n, largest); 
    } 
} 
  

void heapSort(char **arr, int n){

	/*-----------------------
	FUNCAO PRINCIPAL HEAPSORT
	-----------------------*/

	int i; 
    /* Constroi heap */
    for (i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    /* Extrai um elemnto de cada vez */
    for (i=n-1; i>0; i--) 
    { 
        /* Move raiz para o fim */
        swap(arr, 0, i); 
  
        /* chama heapify no heap ja reduzido */
        heapify(arr, i, 0); 
    } 
} 



void mais_ganhos_g(table_e **heads, int M, int linha_input){

	/*-----------------------------------------------------------------------
	PRINTA AS EQUIPAS COM O MAIOR NUMERO DE JOGOS GANHOS POR ORDEM ALFABETICA
	-----------------------------------------------------------------------*/

	int Max, i, count = 0, i2;
	Equipa *x;
	char **nomes;

	/* Guarda em Max o maior valor de jogos ganhos, 
	e em count o numero de equipas com <Max> jogos ganhos. */
	Max = mais_ganhos(heads, M, &count);


	if (count > 0){

		/* Aloca memoria para as equipas com mais jogos ganhos. */
		nomes = can_fail_malloc(sizeof(char*)*count);
		for (i=0 ; i < count ; i++){
			nomes[i] = can_fail_malloc(sizeof(char)*1024);
		}


		for (i = 0, i2 = 0 ; i < M ; i++){
			/*printf("%d\n", i);*/
			if (heads[i] != NULL){
				for ( x = equipas_hash(heads[i]) ; x != NULL ; x = proxima_e(x)){
					if (jogos_ganhos(x) == Max){
						strcpy(nomes[i2], nome_e(x));
						i2++;
					}
				}
			}
		}

		/* Ordena alfabeticamente as equipas (esta funcao foi usada tambem no 1 projeto). */
		heapSort(nomes, i2);

		/* Faz os prints. */
		printf("%d Melhores %d\n", linha_input, Max);
		for (i2 = i2-1; i2 >= 0 ; i2-- ){
			printf("%d * %s\n",linha_input, nomes[i2]);
		}

		/* Liberta toda a memoria alocada para a lista dos nomes ordenados. */
		for (count = count-1; count >= 0 ; count--){
			free(nomes[count]);
		}
		free(nomes);
	}


}





void free_lista(Lista **heads){

	/*-----------------------------------------------------------------------
	LIBERTA TODA A MEMORIA ALOCADA REFERENTE AS LISTAS ORDENADAS DE NOMES DAS 
	EQUIPAS E JOGOS
	------------------------------------------------------------------------*/

	Lista *x, *head;
	/* Percorre os ponteiros das listas das e equipas e jogos (indice 0-1). */
	head = heads[0];
	/* Caso ponteiro nao seja NULL, liberta memoria de cada nome. */
	for (x = head; head != NULL ; ){
		head = proximo_elemento(head);
		free_el(x);
		x = head;
	}
	free(heads);
}






int main(){
	/* estrutura hash equipas. */
	table_e **heads = NULL;
	/* estrutura hash jogos. */
	table_j **heads_j = NULL;
	/* lista de nomes de equipas e jogos. */
	Lista **listas = NULL, **ultimo_jogo = can_fail_malloc(sizeof(Lista));
	int size_hash = SIZE_HASH, linha_input = 0;
	char c;
	/* Inicializa hashtable equipas. */ 
	heads = inicializa_e(heads, size_hash);
	/* inicializa hashtable jogos. */
	heads_j = inicializa_j(heads_j, size_hash); 
	/* inicializa listas de nomes de jogos e quipas. */
	listas = inicializa_lista(listas);
	while(1){
		/*scan da letra do comando. */
		scanf(" %c", &c);
		if (c == 'a'){
			linha_input++;
			adiciona_jogo(heads, heads_j, ultimo_jogo, size_hash, linha_input, listas);
		}
		if (c == 'A'){
			linha_input++;
			adiciona_equipa(heads, size_hash, linha_input);
		}
		else if (c == 'P'){
			linha_input++;
			procura_e(heads, size_hash, linha_input);
		}
		else if (c == 'l'){
			linha_input++;
			lista_jogos(heads_j, lista_nomes_jogos(listas), size_hash, linha_input);
		}
		else if (c == 'r'){
			linha_input++;
			remove_jogo(heads_j, heads, listas, ultimo_jogo, size_hash, linha_input);
		}
		else if (c == 'p'){
			linha_input++;
			procura_j(heads_j, size_hash, linha_input);
		}
		else if (c == 's'){
			linha_input++;
			altera_score(heads_j, heads, size_hash, linha_input);
		}
		else if (c == 'g'){
			linha_input++;
			mais_ganhos_g(heads, size_hash, linha_input);
		}

		else if (c == 'x')
			break;
		
	}

	/* liberta toda a memoria alocada */
	free_hash_equipas(heads, size_hash);
	free_hash_jogos(heads_j, size_hash);
	free_lista(listas);
	free(ultimo_jogo);

	return 0;
}

