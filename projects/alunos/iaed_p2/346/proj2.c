#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAMANHO 1024
#define TAMANHO_INICIAL 16


/*Listas jogo e equipas*/
/*
struct jogo {
	char *jogo;
	char *equipa1[MAX_TAMANHO];
	char *equipa2[MAX_TAMANHO];
	char *score1;
	char *score2;
};
struct jogo *jogos;
jogos = (struct jogo *)can_fail_malloc(TAMANHO_INICIAL * sizeof(struct jogo));


typedef struct equipa {
	char *equipa;
	int *wins;
};
struct equipa *equipas;
equipas = (struct equipa *)can_fail_malloc(TAMANHO_INICIAL * sizeof(struct equipa));
*/

int tamanhojogo = TAMANHO_INICIAL;
int tamanhoequipa = TAMANHO_INICIAL;
int NL = 0;

struct jogo {
	char jogo[MAX_TAMANHO];
	char equipa1[MAX_TAMANHO];
	char equipa2[MAX_TAMANHO];
	int score1;
	int score2;
};
struct jogo jogo[TAMANHO_INICIAL];

struct equipas {
	char equipa[MAX_TAMANHO];
	int wins;
	
};
struct equipas equipas[TAMANHO_INICIAL];

/*adiciona um jogo novo*/
void run_a(char nome[], char equipa1[], char equipa2[], int score1, int score2) {
	int i, idx;
	char nogame[] = "";

	/*verifica se o nome introduzido ja existe*/
	for (i = 0; i < tamanhojogo; i++) {
		if (strcmp(jogo[i].jogo, nome) == 0) {
			printf("%d Jogo existente.\n", NL);
			return;
		}
	}

	/*verifica se alguma das ja existe*/
	for (i = 0; i < tamanhoequipa; i++) {
		if(strcmp(equipas[i].equipa, equipa1) == 0) {
			break;
		}

		if (i == tamanhoequipa-1 && strcmp(equipas[i].equipa, equipa1) != 0) {
			printf("%d Equipa inexistente.\n", NL);
			return;
		}
	}
	for (i = 0; i < tamanhoequipa; i++) {
		if(strcmp(equipas[i].equipa, equipa2) == 0) {
			break;
		}

		if (i == tamanhoequipa-1 && strcmp(equipas[i].equipa, equipa2) != 0) {
			printf("%d Equipa inexistente.\n", NL);
			return;
		}
	}

	/*verifica qual a proxima posicao vazia para introduzir os dados fornecidos*/
	for (i = 0; i < tamanhojogo; i++) {
		if (strcmp(jogo[i].jogo, nogame) == 0) {
			strcpy(jogo[i].jogo, nome);
			strcpy(jogo[i].equipa1, equipa1);
			strcpy(jogo[i].equipa2, equipa2);
			jogo[i].score1 = score1;
			jogo[i].score2 = score2;

			/*verifica qual das equipas ganhou o jogo*/
			if(score1 > score2) {
				for (idx = 0; idx < tamanhoequipa; idx++) {
					if (strcmp(equipas[idx].equipa, equipa1) == 0) {
						equipas[idx].wins++;
						break;
					}
				}
			}
			
			if(score1 < score2) {
				for (idx = 0; idx < tamanhoequipa; idx++) {
					if (strcmp(equipas[idx].equipa, equipa2) == 0) {
						equipas[idx].wins++;
						break;
					}
				}
			}

			return;
		}
	}
}

/*lista os jogos introduzidos*/
void run_l() {
	int i;
	char nogame[] = "";

	/*faz print dos dados dos jogos existentes*/
	for(i = 0; i < tamanhojogo; i++) {
		if (strcmp(jogo[i].jogo, nogame) == 0) {
			return;
		}

		printf("%d %s %s %s %d %d\n", NL, jogo[i].jogo, jogo[i].equipa1, jogo[i].equipa2, jogo[i].score1, jogo[i].score2);
	}
}

/*procura um jogo definido pelo utilizador*/
void run_p(char nome[]) {
	int i;

	/*verifica a existencia do jogo*/
	for (i = 0; i < tamanhojogo; i++) {
		if (strcmp(jogo[i].jogo, nome) == 0) {
			printf("%d %s %s %s %d %d\n", NL, jogo[i].jogo, jogo[i].equipa1, jogo[i].equipa2, jogo[i].score1, jogo[i].score2);
			return;
		}

		if (i == tamanhojogo-1 && strcmp(jogo[i].jogo, nome) != 0) {
			printf("%d Jogo inexistente.\n", NL);
		}
	}
}

/*remove um jogo definido pelo utilizador*/
void run_r(char nome[]) {
	int i, idx;
	char empty[] = "";

	/*verifica a posicao do jogo*/
	for (i = 0; i < tamanhojogo; i++) {
		if (strcmp(jogo[i].jogo, nome) == 0) {			
			
			/*remove a vitoria da equipa que ganhou o jogo*/
			if(jogo[i].score1 > jogo[i].score2) {
				for(idx = 0; idx < tamanhoequipa; idx++) {
					if (strcmp(equipas[idx].equipa, jogo[i].equipa1) == 0) {
						equipas[idx].wins--;
						break;
					}
				}
			}
			if(jogo[i].score1 < jogo[i].score2) {
				for(idx = 0; idx < tamanhoequipa; idx++) {
					if (strcmp(equipas[idx].equipa, jogo[i].equipa2) == 0) {
						equipas[idx].wins--;
						break;
					}
				}
			}

			/*apaga os dados da posicao do jogo*/
			strcpy(jogo[i].jogo, empty);
			strcpy(jogo[i].equipa1, empty);
			strcpy(jogo[i].equipa2, empty);
			jogo[i].score1 = 0;
			jogo[i].score2 = 0;

			/*altera a posicao dos restantes jogos para nao deixar espaco entre as posicoes*/
			for (idx = i+1; idx < tamanhojogo; idx++) {
				if (strcmp(jogo[idx].jogo, empty) != 0) {
					strcpy(jogo[idx-1].jogo, jogo[idx].jogo);
					strcpy(jogo[idx-1].equipa1, jogo[idx].equipa1);
					strcpy(jogo[idx-1].equipa2, jogo[idx].equipa2);
					jogo[idx-1].score1 = jogo[idx].score1;
					jogo[idx-1].score2 = jogo[idx].score2;

					strcpy(jogo[idx].jogo, empty);
					strcpy(jogo[idx].equipa1, empty);
					strcpy(jogo[idx].equipa2, empty);
					jogo[idx].score1 = 0;
					jogo[idx].score2 = 0;
				}
			}

			return;
		}
	}

	printf("%d Jogo inexistente.\n", NL);
}

/*altera o resultado de um jogo introduzido pelo utilizador*/
void run_s(char nome[], int score1, int score2) {
	int i, idx;

	/*verifica a posicao do jogo*/
	for (i = 0; i < tamanhojogo; i++) {
		if(strcmp(jogo[i].jogo, nome) == 0) {

			/*remove a vitoria da equipa que ganhou o jogo antes da alteracao do resultado*/
			if(jogo[i].score1 > jogo[i].score2) {
				for(idx = 0; idx < tamanhoequipa; idx++) {
					if (strcmp(equipas[idx].equipa, jogo[i].equipa1) == 0) {
						equipas[idx].wins--;
						break;
					}
				}
			}
			if(jogo[i].score1 < jogo[i].score2) {
				for(idx = 0; idx < tamanhoequipa; idx++) {
					if (strcmp(equipas[idx].equipa, jogo[i].equipa2) == 0) {
						equipas[idx].wins--;
						break;
					}
				}
			}
		
			/*altera o resultado do jogo*/
			jogo[i].score1 = score1;
			jogo[i].score2 = score2;

			/*adiciona uma vitoria a equipa que ganhou o jogo com o novo resultado*/
			if(score1 > score2) {
				for (idx = 0; idx < tamanhoequipa; idx++) {
					if (strcmp(equipas[idx].equipa, jogo[i].equipa1) == 0) {
						equipas[idx].wins++;
						break;
					}
				}
			}			
			if(score1 < score2) {
				for (idx = 0; idx < tamanhoequipa; idx++) {
					if (strcmp(equipas[idx].equipa, jogo[i].equipa2) == 0) {
						equipas[idx].wins++;
						break;
					}
				}
			}
		
		return;
		}	
	}

	printf("%d Jogo inexistente.\n", NL);
}

/*adiciona um equipa*/
void run_A(char nome[]) {
	int i;
	char noteam[] = "";

	/*verifica se a equipa ja existe*/
	for (i = 0; i < tamanhoequipa; i++) {
		if (strcmp(equipas[i].equipa, nome) == 0) {
			printf("%d Equipa existente.\n", NL);
			return;
		}
	}

	/*encontra uma posicao vazia para introduzir a nova equipa*/
	for(i = 0; i < tamanhoequipa; i++) {
		if (strcmp(equipas[i].equipa, noteam) == 0) {
			strcpy(equipas[i].equipa, nome);
			return;
		}
	}
}

/*procura uma equipa e imprime o seu nome com o numero de vitorias*/
void run_P(char nome[]) {
	int i;

	/*procura a posicao da equipa e imprime os dados necessarios*/
	for (i = 0; i < tamanhoequipa; i++) {
		if (strcmp(equipas[i].equipa, nome) == 0) {
			printf("%d %s %d\n", NL, nome, equipas[i].wins);
			return;
		}
	}
	printf("%d Equipa inexistente.\n", NL);
}

/*imprime as equipas com o maior numero de vitorias*/
void run_g() {
	int i, idx;
	char noteam[] = "";

	char equipaAux[MAX_TAMANHO] = "";
	int winsAux = 0;

	/*utilizacao de uma estrutura semelhante a das equipas para a ordenacao necessaria nesta funcao*/
	struct equipas ord[TAMANHO_INICIAL];
	int contAux = 0;

	/*procura pelo maior numero de vitorias*/
	for (i = 0; i < tamanhoequipa; i++) {
		if(equipas[i].wins > winsAux) {
			winsAux = equipas[i].wins;
		} 
	}

	/*introduz as equipas com o maior numero de vitorias na estrutura de ordenacao*/
	for (i = 0; i < tamanhoequipa; i++) {
		if(equipas[i].wins == winsAux && strcmp(equipas[i].equipa, noteam) != 0) {
			strcpy(ord[contAux].equipa, equipas[i].equipa);
			contAux++;
		}
	}

	/*se nao houver nenhuma equipa com vitorias a funcao termina*/
	if (contAux == 0) {
		return;
	}
	
	/*utiliza insertion sort para ordenar as equipas pela ordem necessaria*/
	for(i = 1; i < contAux; i++) {
		strcpy(equipaAux, ord[i].equipa);
		
		idx = i-1;
		while(idx >= 0 && strcmp(equipaAux, ord[idx].equipa) < 0) {
			strcpy(ord[idx+1].equipa, ord[idx].equipa);
			idx--;
		}
		strcpy(ord[idx+1].equipa, equipaAux);
	}

	printf("%d Melhores %d\n", NL, winsAux);

	for(i = 0; i < contAux; i++) {
		printf("%d * %s\n", NL, ord[i].equipa);
	}
}



int main() {

/*	loop infinito com os respetivos comandos*/

	/*inicializa as variaveis que serao alteradas de acordo com o input do utlizador*/
	char command;
	char nome[MAX_TAMANHO];
	char equipa1[MAX_TAMANHO];
	char equipa2[MAX_TAMANHO];
	int score1, score2;
	
	/*espera pela linha de comando com os respetivos parametros*/
	while (1) {
		command = getchar();
		switch (command) {
			case 'a':
				scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);
				NL++;
				run_a(nome, equipa1, equipa2, score1, score2);
				break;
			case 'l':
				NL++;
				run_l();
				break;
			case 'p':
				scanf(" %[^:\n]", nome);
				NL++;
				run_p(nome);
				break;
			case 'r':
				scanf(" %[^:\n]", nome);
				NL++;
				run_r(nome);
				break;
			case 's':
				scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);
				NL++;
				run_s(nome, score1, score2);
				break;
			case 'A':
				scanf(" %[^:\n]", nome);
				NL++;
				run_A(nome);
				break;
			case 'P':
				scanf(" %[^:\n]", nome);
				NL++;
				run_P(nome);
				break;
			case 'g':
				NL++;
				run_g();
				break;
			case 'x':
				return 0;
		}

	}

	return -1;
}