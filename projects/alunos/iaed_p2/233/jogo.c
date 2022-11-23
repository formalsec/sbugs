#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "struct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*head -> primeira estrutura da lista inicializada a NULL*/
jogo *head = NULL;

/*adiciona um jogo a linked list*/
int a(){
	char nome[MAXINPUT], equipa1[MAXINPUT], equipa2[MAXINPUT];
	int score1, score2, aux1, aux2;
	jogo *aux;
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);
	/*se a equipa nao existe a procuraEquipa devolve -1*/
	aux1 = procuraEquipa(equipa1);
	aux2 = procuraEquipa(equipa2);
	/*se a cabeca for nula acrescenta na primeira posicao(head)*/
	if(head == NULL){
		if(aux1 == -1 || aux2 == -1){
			printf("%d Equipa inexistente.\n", NL);
			return 0;
		}
		head = can_fail_malloc(sizeof(jogo));
		head->nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
		strcpy(head->nome, nome);
		head->equipa1 = hash_e[aux1];
		head->equipa2 = hash_e[aux2];
		head->score1 = score1;
		head->score2 = score2;
		head->next = NULL;
		head->ant = NULL;
		/*acrescenta um jogo ganho a equipa que ganhou*/
		if(score1 > score2){
			hash_e[aux1]->ganhos++;
		}
		if(score2 > score1){
			hash_e[aux2]->ganhos++;
		}
	}
	else{
		aux = head;
		while(aux->next != NULL){
			if(strcmp(aux->nome, nome) == 0){
				printf("%d Jogo existente.\n", NL);
				return 0;
			}
			aux = aux->next;
		}
		/*verifica na ultima posicao da lista*/
		if(strcmp(aux->nome, nome) == 0){
			printf("%d Jogo existente.\n", NL);
			return 0;
		}
		if(aux1 == -1 || aux2 == -1){
			printf("%d Equipa inexistente.\n", NL);
			return 0;
		}
		/*cria um jogo na posicao a seguir a ultima*/
		aux->next = can_fail_malloc(sizeof(jogo));
		aux->next->nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
		strcpy(aux->next->nome, nome);
		aux->next->equipa1 = hash_e[aux1];
		aux->next->equipa2 = hash_e[aux2];
		aux->next->score1 = score1;
		aux->next->score2 = score2;
		aux->next->next = NULL;
		aux->next->ant = aux;
		/*acrescenta um jogo ganho a equipa que ganhou*/
		if(score1 > score2){
			hash_e[aux1]->ganhos++;
		}
		if(score2 > score1){
			hash_e[aux2]->ganhos++;
		}
	}
	return 1;
}

/*free da lista e estrutura jogo*/
void destroyJogos(){
	jogo *aux;
	aux = head;
	while(aux != NULL){
		aux = aux->next;
		free(head->nome);
		free(head);
		head = aux;
	}
}

/*funcao que lista todos os jogos pela a ordem que foram introduzidos*/
void l(){
	jogo *aux;
	aux = head;
	while(aux != NULL){
		printf("%d %s %s %s %d %d\n", NL, aux->nome, aux->equipa1->nome, aux->equipa2->nome, aux->score1, aux->score2);
		aux = aux->next;
	}
}

/*funcao que procura um jogo pelo nome e devolve o jogo*/
/*se o jogo nao existir devolve NULL*/
jogo* procurarJogo(char *nome){
	jogo *aux = head;
	while(aux != NULL){
		if(strcmp(aux->nome, nome) == 0){
			return aux;
		}
		aux = aux->next;
	}
	return NULL;
}

/*funcao que apaga um jogo da lista*/
void r(){
	char nome[MAXINPUT];
	jogo *aux;
	scanf(" %[^:\n]", nome);
	aux = procurarJogo(nome);
	if(aux != NULL){
		/*remove uma vitoria a equipa que ganhou o jogo*/
		if(aux->score1 > aux->score2){
			aux->equipa1->ganhos--;
		}
		if(aux->score2 > aux->score1){
			aux->equipa2->ganhos--;
		}
		/*se for a cabeca da lista mete NULL e da free dele*/
		if(aux->ant == NULL){
			head = aux->next;
			/*se existir mais um mete o ant a NULL pois passa a ser a cabeca da lista*/
			if(aux->next != NULL){
				aux->next->ant = NULL;
			}
			free(aux->nome);
			free(aux);
		}
		/*se for o ultimo da lista*/
		else if(aux->next == NULL){
			aux->ant->next = NULL;
			free(aux->nome);
			free(aux);
		}
		/*se for um jogo entre a cabeca da lista e o ultimo*/
		else{
			aux->ant->next = aux->next;
			aux->next->ant = aux->ant;
			free(aux->nome);
			free(aux);
		}
	}
	else{
		printf("%d Jogo inexistente.\n", NL);
	}
}

/*Procura um jogo*/
void p(){
	char nome[MAXINPUT];
	jogo *aux;
	scanf(" %[^:\n]", nome);
	aux = procurarJogo(nome);
	if(aux != NULL){
		printf("%d %s %s %s %d %d\n", NL, aux->nome, aux->equipa1->nome, aux->equipa2->nome, aux->score1, aux->score2);
	}
	else{
		printf("%d Jogo inexistente.\n", NL);
	}
}

/*funcao que altera a pontuacao de um jogo*/
void s(){
	char nome[MAXINPUT];
	int score1, score2;
	jogo *aux;
	scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);
	aux = procurarJogo(nome);
	if(aux != NULL){
		/*se a equipa1 ganhou*/
		if(aux->score1 > aux->score2){
			if(score2 > score1){
				aux->equipa1->ganhos--;
				aux->equipa2->ganhos++;
			}
			else if(score1 == score2){
				aux->equipa1->ganhos--;
			}
		}
		/*se a equipa2 ganhou*/
		else if(aux->score1 < aux->score2){
			if(score1 > score2){
				aux->equipa1->ganhos++;
				aux->equipa2->ganhos--;
			}
			else if(score1 == score2){
				aux->equipa2->ganhos--;
			}
		}
		else{
			/*se as equipas empataram*/
			if(score1 > score2){
				aux->equipa1->ganhos++;
			}
			if(score2 > score1){
				aux->equipa2->ganhos++;
			}
		}
		/*muda o score*/
		aux->score1 = score1;
		aux->score2 = score2;
	}
	else{
		printf("%d Jogo inexistente.\n", NL);
	}
}