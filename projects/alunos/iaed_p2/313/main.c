#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include "func.h"
#include "struc.h"

/* #################################################################################################### */

#define WORDSIZE 1023
#define HASHSIZE 2027
#define G_AUX 2000	

/* #################################################################################################### */


/* #################################################################################################### */
/* Defines */


/* #################################################################################################### */


int main(){


	/*-----------------------------*/
	/* SISTEMA DE VAR PARA O CICLO */
	/*-----------------------------*/
	int FIM = 0, Contador = 1,i ,j,k;
 	/* Numero da instrucao, debbug, (i,j,k) indices de tabelas */
	char X;
	/*-----------------------------*/
	/* 		LEITURA DE DADOS	   */
	/*-----------------------------*/
	int l1, l2;
	char r1[WORDSIZE], r2[WORDSIZE], 
	r3[WORDSIZE];
	/*-----------------------------*/

	lista_equipas *Hash_table[HASHSIZE];

	lista_jogos *Hash_table_j[HASHSIZE];
	
	lista_jogos *l_jogos = can_fail_malloc(sizeof(lista_jogos));

	l_jogos->head = NULL ; l_jogos->last = NULL;

	for(i = 0; i < HASHSIZE; i++){
		Hash_table[i] = NULL;
	}

	for(i = 0; i < HASHSIZE; i++){
		Hash_table_j[i] = NULL;
	}

	scanf("%c", &X);
	/* Ler primeiro comando */

	while (FIM == 0){
		switch(X){

			case 'a':
				scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d\n",r1, r2, r3, &l1, &l2);
				i = hash_key_e(r2, Hash_table);
				j = hash_key_e(r3, Hash_table);
				k = hash_key_p(r1, Hash_table_j);
				if(find_game(Hash_table_j[k], r1)){
					if(find_team(Hash_table[i],r2) && find_team(Hash_table[j],r3)){
						a(r1,r2,r3,l1,l2,l_jogos, Hash_table,i ,j);
						a__2(r1,r2,r3,l1,l2,Hash_table_j[k]);
					}
					else{
						printf("%d Equipa inexistente.\n", Contador);
					}
				}
				else{
					printf("%d Jogo existente.\n", Contador);
				}
				
				Contador ++;
				break;

			case 'l':
				l(l_jogos, Contador);
				Contador ++;
				scanf("\n");
				break;

			case 'p':
				scanf(" %s\n",r1);
				i = hash_key_p(r1, Hash_table_j);
				p(Hash_table_j[i], r1, Contador);

				Contador ++;
				break;

			case 'r':
				scanf(" %s\n",r1);
				i = hash_key_p(r1, Hash_table_j);
				r(l_jogos,r1, Contador, Hash_table);
				r__2(Hash_table_j[i], r1);
				Contador ++;
				break;

			case 's':
				scanf(" %[^:\n]:%d:%d\n", r1, &l1, &l2);
				i = hash_key_p(r1, Hash_table_j);
				s(r1, l1, l2, l_jogos, Contador, Hash_table);
				s__2(r1,l1,l2,Hash_table_j[i]);
				Contador ++;
				break;
			case 'A':
				scanf(" %[^:\n]",r1);
				i = hash_key_e(r1, Hash_table);
				if(find_team(Hash_table[i], r1) == 0){
					A(r1, Hash_table[i]);
				}
				else{
					printf("%d Equipa existente.\n", Contador);
				}
				Contador ++;
				break;
			case 'P':
				scanf(" %[^:\n]",r1);
				i = hash_key_e(r1,Hash_table);
				if(find_team(Hash_table[i], r1)){
					P(l_jogos, r1, Contador);
				}
				else{
					printf("%d Equipa inexistente.\n", Contador);
				}

				Contador ++;
				break;
			case 'g':
				g(Hash_table, Contador);
				Contador ++;
				break;

			case 'x':
				FIM = 1;
				/* Acaba o ciclo e o programa*/
				break;

		}
	scanf("%c", &X);
	/* Proximo comando */
	}
	
	free_lista_jogos(l_jogos);
	free_hash(Hash_table);
	free_hash_j(Hash_table_j);

	/* Free all */


	return 0;
}