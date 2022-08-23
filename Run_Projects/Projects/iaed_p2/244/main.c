#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equipa.h"
#include "jogos.h"

int main(){

	int nl = 1, pt1, pt2,temp_1, temp_2, max;
	char comando, buffer[MAX_STRING], nome1[MAX_STRING], nome2[MAX_STRING];
	char *nome_equipa, *nome_jogo, *nome_1, *nome_2;


	/*inicializa a hashtable das equipas*/
	htable_entrada_t **htable_equipas;

	/*inicializa a hashtable dos jogos*/
	htable_entrada_jogo_t **htable_jogos;


	lista_intruduzidos_t *cabeca = NULL;

    lista_equipas_intruduzidas_t *cabeca_remove = NULL;

	htable_entrada_jogo_t *t = malloc(sizeof(htable_entrada_jogo_t));

	htable_entrada_t *eq = malloc(sizeof(htable_entrada_t));


	htable_equipas = cria_hashtable();
	
	htable_jogos = cria_hashtable_jogo();


	comando = getchar();

	while (comando != 'x'){

		switch (comando){

		/* adiciona um jogo novo*/
		case 'a':

			scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", buffer, nome1 , nome2 ,&pt1, &pt2);

			nome_jogo = malloc(sizeof(char) * (strlen(buffer) + 1));
			nome_1 = malloc(sizeof(char) * (strlen(nome1) + 1));
			nome_2 = malloc(sizeof(char) * (strlen(nome2) + 1));

			strcpy(nome_jogo, buffer);
			strcpy(nome_1, nome1);
			strcpy(nome_2, nome2);

			
			if (encontra_jogo(htable_jogos, nome_jogo)!= NULL){

				printf("%d Jogo existente.\n", nl);

			}

			else if (encontra_equipa(htable_equipas, nome_1) == NULL || encontra_equipa(htable_equipas, nome_2) == NULL){

				printf("%d Equipa inexistente.\n", nl);
			}

			else{

				adiciona_jogo_a_hashtable(htable_jogos,&cabeca , nome_jogo, nome_1, nome_2, pt1, pt2);

				t->jogo = encontra_jogo(htable_jogos, nome_jogo);

				/* acerta o numero de jogos ganhos quando se adiciona um jogo*/
				if ((t->jogo->pts_1) > (t->jogo->pts_2)){

					eq->equipa = encontra_equipa(htable_equipas, t->jogo->eq1);
					eq->equipa->numero_de_jogos += 1;
				}
				else if ((t->jogo->pts_2) > (t->jogo->pts_1)){

					eq->equipa = encontra_equipa(htable_equipas, t->jogo->eq2);
					eq->equipa->numero_de_jogos += 1;
				}
				
			}

			
			nl+=1;
			

			free(nome_jogo);
			free(nome_1);
			free(nome_2);

			break;

		/* lista todos os jogos pela ordem em que foram introduzidos*/
		case 'l':

			imprime_lista(cabeca, nl);
			nl+=1;

			break;

		/* procura um jogo */
		case 'p':

			scanf(" %[^\n]", buffer);

			nome_jogo = malloc(sizeof(char) * (strlen(buffer) + 1));

			strcpy(nome_jogo, buffer);

			if (encontra_jogo(htable_jogos, nome_jogo) == NULL){

				printf("%d Jogo inexistente.\n", nl);

			}

			else{

				printf("%d %s", nl, nome_jogo);
				printf(" %s",(encontra_jogo(htable_jogos, nome_jogo))->eq1);
				printf(" %s",(encontra_jogo(htable_jogos, nome_jogo))->eq2);
				printf(" %d",(encontra_jogo(htable_jogos, nome_jogo))->pts_1);
				printf(" %d\n",(encontra_jogo(htable_jogos, nome_jogo))->pts_2);
				
			}

			nl+=1;
			free(nome_jogo);

			break;

		/* apaga um jogo */
		case 'r':

			scanf(" %[^\n]", buffer);

			nome_jogo = malloc(sizeof(char) * (strlen(buffer) + 1));

			strcpy(nome_jogo, buffer);


			if (encontra_jogo(htable_jogos, nome_jogo) == NULL){

				printf("%d Jogo inexistente.\n", nl);

			}

			else{

				/* ao remover um jogo, tem de se atualizar o numero de jogos ganhos das equipas*/
				if ( (encontra_jogo(htable_jogos, nome_jogo)->pts_1) > (encontra_jogo(htable_jogos, nome_jogo)->pts_2 )){


					(encontra_equipa(htable_equipas,(encontra_jogo(htable_jogos, nome_jogo)->eq1)))->numero_de_jogos-=1;

				}

				else if ( (encontra_jogo(htable_jogos, nome_jogo)->pts_1) < (encontra_jogo(htable_jogos, nome_jogo)->pts_2 )){


					(encontra_equipa(htable_equipas,(encontra_jogo(htable_jogos, nome_jogo)->eq2)))->numero_de_jogos-=1;

				}

				retira_da_lista(&cabeca, nome_jogo);

				remove_jogo(htable_jogos,nome_jogo);

			}
			nl+=1;
			free(nome_jogo);

			break;

		/* altera a pontucao (score) de um jogo */
		case 's':


			scanf(" %[^:\n]:%d:%d", buffer, &pt1, &pt2);

			nome_jogo = malloc(sizeof(char) * (strlen(buffer) + 1));

			strcpy(nome_jogo, buffer);

			if (encontra_jogo(htable_jogos, nome_jogo) == NULL){

				printf("%d Jogo inexistente.\n", nl);

			}

			else{

				temp_1 = encontra_jogo(htable_jogos,nome_jogo)->pts_1;
				temp_2 = encontra_jogo(htable_jogos,nome_jogo)->pts_2;

				t->jogo = encontra_jogo(htable_jogos,nome_jogo);
				t->jogo->pts_1 = pt1;
				t->jogo->pts_2 = pt2;


				if (pt1 > pt2 && temp_1 < temp_2){

					(encontra_equipa(htable_equipas,t->jogo->eq1))->numero_de_jogos+=1;
					(encontra_equipa(htable_equipas,t->jogo->eq2))->numero_de_jogos-=1;

				}


				if (pt1 > pt2 && temp_1 == temp_2){

					(encontra_equipa(htable_equipas,t->jogo->eq1))->numero_de_jogos+=1;

				}

	
				else if (pt1 < pt2 && temp_1 > temp_2){

					(encontra_equipa(htable_equipas,t->jogo->eq2))->numero_de_jogos+=1;
					(encontra_equipa(htable_equipas,t->jogo->eq1))->numero_de_jogos-=1;
						

				}
				else if (pt1 < pt2 && temp_1 == temp_2){

					(encontra_equipa(htable_equipas,t->jogo->eq2))->numero_de_jogos+=1;	

				}


				else if (pt1 == pt2 && temp_1 > temp_2){

					(encontra_equipa(htable_equipas,t->jogo->eq1))->numero_de_jogos-=1;

				}

				else if (pt1 == pt2 && temp_1 < temp_2){

					(encontra_equipa(htable_equipas,t->jogo->eq2))->numero_de_jogos-=1;

				}

			}

			nl+=1;
			free(nome_jogo);

			break;

		/* adiciona uma nova equipa */
		case 'A':

			scanf(" %[^\n]", buffer);

			nome_equipa = malloc(sizeof(char) * (strlen(buffer) + 1));

			strcpy(nome_equipa, buffer);

			if (encontra_equipa(htable_equipas, nome_equipa) != NULL){

				printf("%d Equipa existente.\n", nl);

			}

			else{

				adiciona_equipa_a_hashtable(htable_equipas,&cabeca_remove, nome_equipa);
			}
			nl+=1;


			free(nome_equipa);
			break;

		/* procura uma euipa */
		case 'P':

			scanf(" %[^\n]", buffer);
			nome_equipa = malloc(sizeof(char) * (strlen(buffer) + 1));
			strcpy(nome_equipa, buffer);

			if (encontra_equipa(htable_equipas, nome_equipa) == NULL){

				printf("%d Equipa inexistente.\n", nl);

			}

			else{

				printf("%d %s %d\n",nl, nome_equipa, (encontra_equipa(htable_equipas, nome_equipa))->numero_de_jogos);
				
			}

			nl+=1;

			free(nome_equipa);
			break;

		/* encontra as equipas que venceram mais jogos*/
		case 'g':

			max = max_jogos_ganhos(cabeca_remove);
			imprime_melhores_equipas(cabeca_remove, max, nl);
			nl +=1;

			break;

		}
	
		comando = getchar();	

	}
	
	
	free(t);
	free(eq);

	destroi_lista(cabeca);
	destroi_lista_equipas(cabeca_remove);

	destroi_hashtable(htable_equipas);
	destroi_hashtable_jogo(htable_jogos);
	
	
	
	return 0;
}