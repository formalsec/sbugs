#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "func.h"
#include "struc.h"


#define WORDSIZE 1023
#define HASHSIZE 2027
#define G_AUX 2000	


/* #################################################################################################################################################*/

/* Hash Table */

/* #################################################################################################################################################*/

/* #################################################################################################################################################*/
	/* Encontra e pode comecar uma lista_equipa da hash table */
/* #################################################################################################################################################*/
int hash_key_e(char *name, lista_equipas *Hash_table[]){


	int key = 0, a = 127, M = HASHSIZE;

	for(;*name != '\0'; name++){
		key = (a*key + *name) % M;
		/* Calcula a chave Correspondente */
	}

	if(!Hash_table[key]){
		/* Se n existe comeca uma nova */
		Hash_table[key] = can_fail_malloc(sizeof(lista_equipas));
		/* Inicializa os ponteiros como nulos */
		Hash_table[key]->head = NULL;
		Hash_table[key]->last = NULL;
	}
	return key;
}


/* #################################################################################################################################################*/
	/* Semelhante a hash_key_e so que para jogos */
/* #################################################################################################################################################*/


int hash_key_p(char *name, lista_jogos *Hash_table[]){


	int key = 0, a = 127, M = HASHSIZE;

	for(;*name != '\0'; name++){
		key = (a*key + *name) % M;
	}

	if(!Hash_table[key]){
		Hash_table[key] = can_fail_malloc(sizeof(lista_jogos));
		Hash_table[key]->head = NULL;
		Hash_table[key]->last = NULL;
	}
	return key;
}


/* #################################################################################################################################################*/
	/* Dando um nome char (jogo) e uma lista_jogos, precorre a lista_jogos dada ate encontrar o jg pedido */
	/* Se encontrado devolve 0, senao 1; */
/* #################################################################################################################################################*/

int find_game(lista_jogos *l, char jogo[]){

	int logico = 1;
	node_jogos *search;
	/* Cria um node point para a procura */

	for(search = l->head; search != NULL ;search = search->next){
		if(strcmp(jogo, search->jogo) == 0){ /* Iguais */
			logico = 0;
			break;
		}

	}
	return logico;

}


/* #################################################################################################################################################*/
	/* Dando um nome char (jogo) e uma lista_equipas, precorre a lista_jogos dada ate encontrar o jg pedido */
	/* Se encontrado devolve 1, senao 0 (contrario ao anterior) */ 		
/* #################################################################################################################################################*/

int find_team(lista_equipas *l, char equipa[]){

	int logico = 0;
	node_equipas *search;

	for(search = l->head; search != NULL ;search = search->next){
		if(strcmp(equipa, search->name) == 0){ /* Iguais */
			logico = 1;
			break;
		}

	}
	return logico;


}

/* #################################################################################################################################################*/
	/* atualiza as vitorias de uma dada equipa , aumentado-a em +1; se a equipa nao estiver na lista dada n faz nada*/
/* #################################################################################################################################################*/


void atualiza_v(lista_equipas *l, char equipa[]){

	node_equipas *search;
	/* Nomes iguais -> mesmo jogo */
	for(search = l->head; search != NULL ;search = search->next){
		if(strcmp(equipa, search->name) == 0){ /*Iguais?*/
			search->Jogos_ganhos += 1;
			break;
		}
	}

}

/* #################################################################################################################################################*/
	/* atualiza as vitorias de uma dada equipa , diminuindo em 1; se a equipa nao estiver na lista dada n faz nada*/
/* #################################################################################################################################################*/

void retira_v(lista_equipas *l, char equipa[]){

	node_equipas *search;

	for(search = l->head; search != NULL ;search = search->next){
		if(strcmp(equipa, search->name) == 0){ /*Iguais*/
			search->Jogos_ganhos -= 1;
			break;
		}

	}

}

/* #################################################################################################################################################*/
	/* Da um node e a lista de jogos onde o mesmo esta presente; Remove-o da lista ligada */
/* #################################################################################################################################################*/


void remove_jogo(node_jogos *element, lista_jogos *l){



	if(!element->previous){
	/*Se nao tiver um elemento a antes e o primeiro*/
		l->head = element->next;
		/* head sera o proximo agora, (se next for nulo so havia um elmento na lista)*/
	}
	else{
		element->previous->next = element->next;
		/* Senao o elemento anterior passa ao next (P -> E -> N) --> (P-> N) */
	}

	/* Mesmo passo mas para o elemnto a seguir */

	if(!element->next){
		l->last = element->previous;
	}
	else{
		element->next->previous = element->previous;
	}
	/* Free jogo */
	free(element->jogo);
	free(element->equipa1);
	free(element->equipa2);
	free(element);

}


/* #################################################################################################################################################*/
	/* Tal e qual remove_jogo mas com uma outra classe*/
/* #################################################################################################################################################*/

void remove_equipa(node_equipas *element, lista_equipas *l){



	if(!element->previous){
	/*Se for um ponteiro, se existir*/
		l->head = element->next;
	}
	else{
		element->previous->next = element->next;
	}

	if(!element->next){
		l->last = element->previous;
	}
	else{
		element->next->previous = element->previous;
	}
	free(element->name);
	free(element);


}


/* #################################################################################################################################################*/
	/* Precorre a lista dada e remove todos os elementos, liberta a lista depois. NOTA : remove_jogo da free */
/* #################################################################################################################################################*/
void free_lista_jogos(lista_jogos *l){

	node_jogos *search;

	while(l->head){		/* Head vai se movendo para a frente ate ja n houver ponteiros (fim da lista) */
		search = l->head->next;
		remove_jogo(l->head,l);
		l->head = search;
	}
	free(l);

}

/* #################################################################################################################################################*/
	/*	Tal e qual free_lista_jogos mas com classes diferentes */
/* #################################################################################################################################################*/
void free_lista_equipas(lista_equipas *l){

	node_equipas *search;

	while(l->head){
		search = l->head->next;
		remove_equipa(l->head,l);
		l->head = search;
	}
	free(l);

}


/* #################################################################################################################################################*/
	/* Precorre todos os ponteiros lista_equipas e faz free_lista_equipas, isto liberta a memoria alocada */
/* #################################################################################################################################################*/

void free_hash(lista_equipas *Hash_table[]){

	int k;

	for(k = 0; k < HASHSIZE; k++){
		if(Hash_table[k]){
			free_lista_equipas(Hash_table[k]);
		}
	}
}

/* #################################################################################################################################################*/
	/* Igual a free_hash mas para jogos */
/* #################################################################################################################################################*/

void free_hash_j(lista_jogos *Hash_table[]){

	int k;

	for(k = 0; k < HASHSIZE; k++){
		if(Hash_table[k]){
			free_lista_jogos(Hash_table[k]);
		}
	}
}


/* #################################################################################################################################################*/
/* #################################################################################################################################################*/


/* #################################################################################################################################################*/
	/* Recebe os elemntos do scanf q correspondem ao (jogo, equipa1 e 2, e os respectivos resultados), uma lista_jogos e
	a hash table das equipas para atualizar uma vitoria caso exista	(int i e j sao indices pre calculados da hash_table para as equipas
	 1 e 2 respectivamente)*/
/* #################################################################################################################################################*/


void a(char jogo[], char equipa1[], char equipa2[], int score1, int score2, lista_jogos *l, lista_equipas *Hash_table[], int i, int j){


	node_jogos *new_node = can_fail_malloc(sizeof(node_jogos));
	/* Aloca memoria para o novo node */
	new_node->previous = l->last;
	/* Ligar o novo node ao fim da lista */
	new_node->next = NULL;
	/* O proximo ainda n existe */

	/* "Da" os componentes ao novo no */
	/*----------------------------------------------------*/
	new_node->jogo = can_fail_malloc(sizeof(char)*(strlen(jogo)+1));
	strcpy(new_node->jogo, jogo);
	new_node->equipa1 = can_fail_malloc(sizeof(char)*(strlen(equipa1)+1));
	strcpy(new_node->equipa1, equipa1);
	new_node->equipa2 = can_fail_malloc(sizeof(char)*(strlen(equipa2)+1));
	strcpy(new_node->equipa2, equipa2);
	new_node->valor1 = score1;
	new_node->valor2 = score2;
	/*----------------------------------------------------*/
	/* Se o ultimo elemento da lista existe, entao o seu proximo e o novo */
	if(l->last)
		l->last->next = new_node;
	else{
		/* Se nao existe ultimo entao a lista e vazia logo atualiza a head */
		l->head = new_node;
	}
	/* Ha um novo elemento entao e garantido q haja um ultimo */
	l->last = new_node;

	/* Se a equipa 1 ganhou a equipa 2 atualiza jgs ganhos de 1*/
	if(score1 > score2){
		atualiza_v(Hash_table[i], equipa1);
	}
	/* Se a equipa 2 ganhou a equipa 1 atualiza jgs ganhos de 2*/
	if(score1 < score2){
		atualiza_v(Hash_table[j], equipa2);
	}	


}

/* #################################################################################################################################################*/
	/* Igual a a mas sem atualizar os jgs ganhos da equipa*/
/* #################################################################################################################################################*/

void a__2(char jogo[], char equipa1[], char equipa2[], int score1, int score2, lista_jogos *l){


	node_jogos *new_node = can_fail_malloc(sizeof(node_jogos));
	new_node->previous = l->last;
	new_node->next = NULL;
	new_node->jogo = can_fail_malloc(sizeof(char)*(strlen(jogo)+1));
	strcpy(new_node->jogo, jogo);
	new_node->equipa1 = can_fail_malloc(sizeof(char)*(strlen(equipa1)+1));
	strcpy(new_node->equipa1, equipa1);
	new_node->equipa2 = can_fail_malloc(sizeof(char)*(strlen(equipa2)+1));
	strcpy(new_node->equipa2, equipa2);
	new_node->valor1 = score1;
	new_node->valor2 = score2;

	if(l->last)
		l->last->next = new_node;
	else{
		l->head = new_node;
	}
	l->last = new_node;


}

/* #################################################################################################################################################*/
	/* Precorre uma lista e da print de cada elemento*/
/* #################################################################################################################################################*/


void l(lista_jogos *l, int Contador){


	node_jogos *search;

	for(search = l->head; search != NULL ; search = search->next){
		printf("%d %s %s %s %d %d\n", Contador,search->jogo, search->equipa1,search->equipa2,
			search->valor1, search->valor2);
	}

}


/* #################################################################################################################################################*/
	/* Percorre a lista e devolve o jogo correspondente ao char jogo, senao encontra print q n existe*/
/* #################################################################################################################################################*/


void p(lista_jogos *l, char jogo[], int Contador){


	node_jogos *search;

	for(search = l->head; search != NULL ; search = search->next){
		if(strcmp(jogo, search->jogo) == 0){ /* Iguais */
			printf("%d %s %s %s %d %d\n", Contador, search->jogo, search->equipa1, search->equipa2,
				search->valor1, search->valor2);
			return;
		}
	}
	printf("%d Jogo inexistente.\n", Contador);


}


/* #################################################################################################################################################*/
	/* Remove um dado jogo usando a remove_jogo , atualiza caso uma equipa tenha vencido nesse jg*/
/* #################################################################################################################################################*/




void r(lista_jogos *l, char jogo[], int Contador, lista_equipas *Hash_table[]){

	node_jogos *search;
	int i; /* Futura key */


	for(search = l->head; search != NULL ; search = search->next){
		if(strcmp(jogo, search->jogo) == 0){ /* Iguais */

		/* (Se equipa x ganhou neste jogo retira uma vitora a equipa x) */
			if(search->valor1 > search->valor2){
				i = hash_key_e(search->equipa1, Hash_table);
				retira_v(Hash_table[i], search->equipa1);
			}
			if(search->valor1 < search->valor2){
				i = hash_key_e(search->equipa2, Hash_table);
				retira_v(Hash_table[i], search->equipa2);
			}
			remove_jogo(search,l);
			return;
		}
	}
	/* Senao existe , print */
	printf("%d Jogo inexistente.\n", Contador);

}

/* #################################################################################################################################################*/
	/* Remove um dado jogo usando a remove_jogo , sem a atualizacao */
/* #################################################################################################################################################*/

void r__2(lista_jogos *l, char jogo[]){

	node_jogos *search;

	for(search = l->head; search != NULL ; search = search->next){
		if(strcmp(jogo, search->jogo) == 0){ /* Iguais */
			remove_jogo(search,l);
			return;
		}
	}

}


/* #################################################################################################################################################*/
	/* Encontra um jogo e altera-o , assim como a vitoria de cada equipa */
/* #################################################################################################################################################*/



void s(char jogo[], int score1, int score2, lista_jogos *l, int Contador, lista_equipas *Hash_table[]){

	node_jogos *search;
	int i;

	for(search = l->head; search != NULL ; search = search->next){
		if(strcmp(jogo, search->jogo) == 0){ /* Iguais */

		/* Semalhante a tds os anteriores */
			if(search->valor1 > search->valor2){
				i = hash_key_e(search->equipa1, Hash_table);
				retira_v(Hash_table[i], search->equipa1);
			}
			if(search->valor1 < search->valor2){
				i = hash_key_e(search->equipa2, Hash_table);
				retira_v(Hash_table[i], search->equipa2);
			}
			search->valor1 = score1;
			search->valor2 = score2;

			if(search->valor1 > search->valor2){
				i = hash_key_e(search->equipa1, Hash_table);
				atualiza_v(Hash_table[i], search->equipa1);
			}
			if(search->valor1 < search->valor2){
				i = hash_key_e(search->equipa2, Hash_table);
				atualiza_v(Hash_table[i], search->equipa2);
			}

			return;
		}
	}


	printf("%d Jogo inexistente.\n", Contador);


}

/* #################################################################################################################################################*/
	/* Encontra um jogo e altera-o , sem alterar */
/* #################################################################################################################################################*/

void s__2(char jogo[], int score1, int score2, lista_jogos *l){

	node_jogos *search;

	for(search = l->head; search != NULL ; search = search->next){
		if(strcmp(jogo, search->jogo) == 0){ /* Iguais */
			search->valor1 = score1;
			search->valor2 = score2;
			return;
		}
	}
}


/* #################################################################################################################################################*/
	/* Cria uma nova equipa na lista dada para o efeito */
/* #################################################################################################################################################*/


void A(char equipa[], lista_equipas *l){

	/* Semalhante a (a) */

	node_equipas *new_node = can_fail_malloc(sizeof(node_equipas));

	new_node->previous = l->last;
	new_node -> next = NULL;
	new_node->name = can_fail_malloc(sizeof(char)*(strlen(equipa)+1));
	strcpy(new_node->name, equipa);
	new_node->Jogos_ganhos = 0;

	if(l->last){
		l->last->next = new_node;
	}
	else{
		l->head = new_node;
	}

	l->last = new_node;

}


/* #################################################################################################################################################*/
	/* Encontra uma dada equipa pela string dada e printa-a */
/* #################################################################################################################################################*/

void P(lista_jogos *l, char equipa[], int Contador){


	node_jogos *search;
	int vitorias = 0;

	for(search = l->head; search != NULL; search = search->next){
		if(strcmp(search->equipa1, equipa) == 0 && search->valor1 > search->valor2){
			vitorias += 1;
		}
		if(strcmp(search->equipa2, equipa) == 0 && search->valor1 < search->valor2){
			vitorias += 1;
		}
	}

	printf("%d %s %d\n", Contador, equipa, vitorias);


}


/*####################################################################################################################################################*/
/*			Funcao auxiliar de merge2.									  				  				 	 									  	  */
/*			Recebe: Duas listas de caracteres.																		  			  					  */		
/*			Funcionamento: Determinar qual das listas (A, B) vem primeiro em ordem alfabetica. Se for A , return 0. Se for B, return 1.	  			  */										
/*####################################################################################################################################################*/

int Alphabetic(char *A, char *B){

	char New_A[WORDSIZE], New_B[WORDSIZE];
	strcpy(New_A, A);	
	strcpy(New_B, B);
	
	if(strcmp(New_A,New_B) < 0){
		return 0;
	}
	else{
		return 1;
	}

}

/*####################################################################################################################################################*/
/*			Funcao auxiliar de mergesort.									  				  				 	 									  */
/*			Recebe: A lista a ordenar, inicio, meio, fim, lista P.																		  			  */		
/*			Funcionamento: Ordena a lista basiando no seu posicionamento alfabetico 							  									  */								
/*####################################################################################################################################################*/


void merge(char * a[], int l, int m, int r){

	int i, j, k;
	char *aux[G_AUX]; /* Cria aux*/

	for(i = 0; i < G_AUX; i++){
		aux[i] = NULL;
	}
	/* Inicializa tudo a nulo */

	for (i = m+1; i > l; i --){
		aux[i-1] = can_fail_malloc(sizeof(char)*(strlen(a[i-1])+1));
		strcpy(aux[i-1],a[i-1]);
		/* Coloca a string anterior em aux */
	}
	for (j = m; j < r; j ++){
		aux[r+m-j] = can_fail_malloc(sizeof(char)*(strlen(a[j+1])+1));
		strcpy(aux[r+m-j],a[j+1]);
		/* Coloca a string anterior em aux */

	}
	for(k = l; k <= r; k++){
		if(Alphabetic(aux[j],aux[i]) == 0){ 
		/* Funcao entre A e B string para ver quem e o "maior" alfabeticamente */
			if(a[k]){free(a[k]);} /* free para atualizar*/
			a[k] = can_fail_malloc(sizeof(char)*(strlen(aux[j])+1));
			strcpy(a[k], aux[j]);
			j -= 1;
		}
		else{
			if(a[k]){free(a[k]);}/* free para se poder atualizar */
			a[k] = can_fail_malloc(sizeof(char)*(strlen(aux[i])+1));
			strcpy(a[k], aux[i]);
			i += 1;
		}
	}	

	/* NOTA : Apenas passo idp e qtd pois e o necessario para printar */
	for(i = 0; i < G_AUX; i++){
		if(aux[i]){
			free(aux[i]);
		}
	}
	/*free aux*/
}


/*####################################################################################################################################################*/
/*			Funcao auxiliar de l.									  				  				 	 									  		  */
/*			Recebe: A lista a ordenar, inicio, fim, lista P.																		  			   	  */		
/*			Funcionamento: Divide a lista, para esta ser organizada pela sua aux.		  															  */										
/*####################################################################################################################################################*/


void mergesort(char * a[], int l, int r){

	int m = (r+l)/2;

	if(r <= l)
		return;
	mergesort(a, l, m);
	mergesort(a, m+1, r);
	merge(a, l, m ,r);

}


/*####################################################################################################################################################*/
	/* Print as equipas por ordem alfabeitca com maior numero de jgs*/
/*####################################################################################################################################################*/



void g(lista_equipas *Hash_table[], int Contador){

	int melhor = 0, i = 0,j, k;
	node_equipas *search;
	char *nomes_equipas[G_AUX];

	nomes_equipas[0] = NULL;
	/* Inicializo este , pois e necessario para ver se a lista dos nomes e vazia*/

	/* Percorre hash table e encontra o maior numero de vitorias */
	for(k = 0; k < HASHSIZE; k++){
		if(Hash_table[k]){
			for(search = Hash_table[k]->head; search != NULL; search = search->next){
				if(search->Jogos_ganhos > melhor){
					melhor = search->Jogos_ganhos;
				}		
			}
		}
	}
	/* Percorre hash table e encontra todos as equipas com o numero max de jgs vencidos e fica com as suas strings*/
	for(k = 0; k < HASHSIZE; k++){
		if(Hash_table[k]){
			for(search = Hash_table[k]->head; search != NULL; search = search->next){
				if(search->Jogos_ganhos == melhor){
					nomes_equipas[i] = can_fail_malloc(sizeof(char)*strlen(search->name)+1);
					strcpy(nomes_equipas[i], search->name);
					i ++;
				}		
			}
		}
	}

	/* senao existir acaba*/
	if(!nomes_equipas[0]){return;}

	printf("%d Melhores %d\n", Contador, melhor);

	j = i;

	/*organiza*/
	mergesort(nomes_equipas, 0, j-1);

	/*print e free*/
	for(i = 0; i < j; i++){
		printf("%d * %s\n", Contador,nomes_equipas[i]);
		free(nomes_equipas[i]);	
	}


}

/* #################################################################################################### */
