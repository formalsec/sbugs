#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "jogo.h"
#include "equipa.h"
#include "hash.h"
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addJ(hashJ hash, hashE teams, link_J *jogos, int count, int *wins, int *flag, Equipa *new){
	Jogo x;
	link_E node1, node2;
	Equipa equipa = NULL;
	char nome[TAM_STR], equipa1[TAM_STR], equipa2[TAM_STR];
	int score1, score2;
	
	scanf(" %[^:]:%[^:]:%[^:]:%d:%d", nome, equipa1, equipa2, &score1, &score2);


	if(procura_hash_jogo(hash, nome, TAM_HASH) != NULL){
		printf("%d Jogo existente.\n", count);
		return;
	}

	node1 = procura_hash_equipa(teams, equipa1, TAM_HASH);
	node2 = procura_hash_equipa(teams, equipa2, TAM_HASH);

	if(node1 == NULL || node2 == NULL){
		printf("%d Equipa inexistente.\n", count);
		return;
	}

	if(score1 > score2){
		equipa = node1->equipa;
	}
	else if (score2 > score1){
		equipa = node2->equipa;
	}

	/* se a equipa vencedora do jogo tiver mais vitorias do que a(s) equipa(s) vencedora(s),
	e ativada a respetiva flag "NOVO", caso o numero de vitorias seja o mesmo, ativa-se a flag
	"ADD", sendo guardada a equipa em ambos os casos para proceder a alteracao depois */
	if(equipa != NULL){
		if(++equipa->wins > *wins){
			(*wins)++;
			*flag = NOVO;
			*new = equipa;
		}
		else if(equipa->wins == *wins){
			*flag = ADD;
			*new = equipa;
		}
	}

	x = inicializa_jogo(nome, equipa1, equipa2, score1, score2);

	hash = insere_hash_jogo(hash, x, TAM_HASH);
	*jogos = insertBeginJ(*jogos, x); /* inserir no inicio e mais rapido do que no fim */
	return;
}

void print_lista_jogos(link_J head, int contador){
	/* os jogos foram inseridos ao contrario, pois assim nao se tem de percorrer a lista
	para inserir o jogo no fim, e esta funcao recursiva resolve o problema de imprimir a lista
	ao contrario */
	print_inverso(head, contador);
	return;
}

void procura_jogo(hashJ jogos, int contador) {
	char nome[TAM_STR];
	link_J jogo;

	scanf(" %[^\n]", nome);

	jogo = procura_hash_jogo(jogos, nome, TAM_HASH);

	if(jogo == NULL)
		printf("%d Jogo inexistente.\n", contador);
	else{
		printf("%d ", contador);
		printNodeJ(jogo);
	}

	return;
}

void apaga_jogo(hashJ jogos, hashE equipas, link_J *lista, link_E *winners, int contador, int *flag){
	link_J node;
	Equipa equipa = NULL;
	char nome[TAM_STR];

	scanf(" %[^\n]", nome);

	node = procura_hash_jogo(jogos, nome, TAM_HASH);

	if(node == NULL){
		printf("%d Jogo inexistente.\n", contador);
		return;
	}

	/* encontra a equipa que estava a vencer neste jogo */
	if(node->jogo->score1 > node->jogo->score2){
		equipa = procura_hash_equipa(equipas, node->jogo->equipa1, TAM_HASH)->equipa;
	}
	else if(node->jogo->score2 > node->jogo->score1){
		equipa = procura_hash_equipa(equipas, node->jogo->equipa2, TAM_HASH)->equipa;
	}

	/* apaga a equipa encontrada dos vencedores */
	if(equipa != NULL){
		*winners = deleteE(*winners, equipa->nome);
		equipa->wins--;
	}

	if(*winners == NULL)
		*flag = REFAZER;

	jogos = retira_hash_jogo(jogos, nome, TAM_HASH);
	*lista = deleteJ(*lista);
	return;
}

void alt_score(hashJ jogos, hashE equipas, link_E *winners, 
				Equipa *new, int count, int *flag, int *wins){

	int score1, score2;
	char nome[TAM_STR];
	link_J node;
	Equipa equipa1, equipa2;


	scanf(" %[^:]:%d:%d", nome, &score1, &score2);

	node = procura_hash_jogo(jogos, nome, TAM_HASH);

	if(node == NULL){
		printf("%d Jogo inexistente.\n", count);
		return;
	}
	else{
		equipa1 = procura_hash_equipa(equipas, node->jogo->equipa1, TAM_HASH)->equipa;
		equipa2 = procura_hash_equipa(equipas, node->jogo->equipa2, TAM_HASH)->equipa;

		/* se a equipa nao estava a ganhar mas agora esta, 
		altera-se wins e adiciona a vencedores se necessario */
		if(score1 > score2 && node->jogo->score1 <= node->jogo->score2){
			if(node->jogo->score1 < node->jogo->score2){
				equipa2->wins--;
				*winners = deleteE(*winners, equipa2->nome);
			}
			if(++equipa1->wins > *wins){
				(*wins)++;
				*flag = NOVO;
				*new = equipa1;
			}
			else if(equipa1->wins == *wins){
				*flag = ADD;
				*new = equipa1;
			}
		}
		else if(score2 > score1 && node->jogo->score2 <= node->jogo->score1){
			if(node->jogo->score2 < node->jogo->score1){
				*winners = deleteE(*winners, equipa1->nome);
				equipa1->wins--;
			}
			if(++equipa2->wins > *wins){
				(*wins)++;
				*flag = NOVO;
				*new = equipa2;
			}
			else if(equipa2->wins == *wins){
				*flag = ADD;
				*new = equipa2;
			}
		}

		/* se a equipa estava a ganhar e agora e empate, tira-se dos vencedores e desce as wins */
		else if(score1 == score2){
			if(node->jogo->score1 > node->jogo->score2){
				*winners = deleteE(*winners, equipa1->nome);
				equipa1->wins--;
			}
			else if(node->jogo->score2 > node->jogo->score1){
				*winners = deleteE(*winners, equipa2->nome);
				equipa2->wins--;
			}
		}

		node->jogo->score1 = score1;
		node->jogo->score2 = score2;

		/* se ficar sem vencedores, refaz */
		if(*winners == NULL && *flag == NADA)
			*flag = REFAZER;
	}

	return;
}

void add_equipa(hashE equipas, Equipa *new_winner, int wins, int *flag, int contador){
	Equipa x;
	char nome[TAM_STR];

	scanf(" %[^\n]", nome);

	if(procura_hash_equipa(equipas, nome, TAM_HASH) != NULL){
		printf("%d Equipa existente.\n", contador);
		return;
	}

	x = can_fail_malloc(sizeof(struct equipa));
	x->nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));

	strcpy(x->nome, nome);
	x->wins = 0;

	if(wins == 0){
		*flag = ADD;
		*new_winner = x;
	}

	equipas = insere_hash_equipa(equipas, x, TAM_HASH);
	return;
}

void procura_equipa(hashE equipas, int contador) {
	char nome[TAM_STR];
	link_E equipa;

	scanf(" %[^\n]", nome);

	equipa = procura_hash_equipa(equipas, nome, TAM_HASH);

	if(equipa == NULL)
		printf("%d Equipa inexistente.\n", contador);
	else{
		printf("%d ", contador);
		printNodeE(equipa);
	}

	return;
}

void champions(link_E equipas, int wins, int contador){
	int n, i;
	char **array;
	link_E temp;

	n = lengthE(equipas);

	/* cria e copia os nomes para um array*/
	array = can_fail_malloc(sizeof(char*)*n);
	temp = equipas;
	for(i = 0; i < n; i++){
		array[i] = can_fail_malloc(sizeof(char)*(strlen(temp->equipa->nome) + 1));
		strcpy(array[i], temp->equipa->nome);
		temp = temp->next;
	}

	qsort(array, n, sizeof(char*), compara);

	/* se existirem equipas */
	if(n != 0)
		printf("%d Melhores %d\n", contador, wins);
	for(i = 0; i < n; i++)
		printf("%d * %s\n", contador, array[i]);

	for(i = 0; i < n; i++)
		free(array[i]);

	free(array);
	
	return;
}

/* auxiliar */
void atualiza_winner(hashE equipas, link_E *winners, Equipa winner, int flag, int *wins){
	int i, max = 0;
	link_E head, temp;

	if(flag != NADA){
		if(flag == ADD){
			*winners = insertBeginE(*winners, winner);
		}
		else if(flag == NOVO){
			/* apaga-se a lista e adiciona-se o unico vencedor */
			free_nodesE(*winners);
			*winners = NULL;
			*winners = insertBeginE(*winners, winner);
		}
		else if(flag == REFAZER){
			/* neste caso e feito uma procura linear pela hashtable e encontra-se uma nova lista */
			(*wins)--;
			for(i = 0; i < TAM_HASH; i++){
				head = equipas[i];
				while(head != NULL){
					if(head->equipa->wins == max){
						*winners = insertBeginE(*winners, head->equipa);
					}
					else if(head->equipa->wins > max){
						max = head->equipa->wins;
						while(*winners != NULL){
							temp = *winners;
							*winners = (*winners)->next;
							free(temp);
						}
						*winners = insertBeginE(*winners, head->equipa);
					}
				head = head->next;
				}
			}
		}
	}
}

/*debug*/

void print_hash_equipas(hashE equipas, int wins){
	link_E head;
	int i;

	printf("%d\n", wins);

	for(i = 0; i < TAM_HASH; i++){
		for(head = equipas[i] ; head != NULL; head = head->next){
			printf("%d ", i);
			printNodeE(head);
		}
	}
	return;
}

void print_hash_jogos(hashJ jogos){
	link_J head;
	int i;

	for(i = 0; i < TAM_HASH; i++){
		for(head = jogos[i] ; head != NULL; head = head->next){
			printf("%d ", i);
			printNodeJ(head);
		}
	}
	return;
}