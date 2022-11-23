#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME 1024	/*tamanho maximo dos nomes*/
#define PRIMO 509


int hash(char *v, int M){

	int h, a = 31415, b = 27183;
	for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
		h = (a*h + *v) % M;
	return h;
}





/*---------------------------EQUIPAS-------------------(funciona tudo ate agora)*/
typedef struct EQUIPAS{
	char *nome;
	int score;
}equipa;


typedef struct LISTA_EQUIPAS{
	equipa *equipa;
	struct LISTA_EQUIPAS *next;
}hash_equipa;


void organiza_lexic(equipa *equipa, hash_equipa **equipas_lexic){
	hash_equipa *j, *ord, *anterior;

	j = can_fail_malloc(sizeof(hash_equipa));
	j->equipa = equipa;
	j->next = NULL;
	if (*equipas_lexic == NULL){
		*equipas_lexic = j;
	}

	else{

		for(ord = *equipas_lexic, anterior = NULL; ord != NULL; anterior = ord, ord = ord->next){
			if (strcmp(j->equipa->nome, ord->equipa->nome) < 0){

				if (ord == *equipas_lexic){
					j->next = *equipas_lexic;
					*equipas_lexic = j;
				}

				else{
					anterior->next = j;
					j->next = ord;
				}

			}

			else if(strcmp(j->equipa->nome, ord->equipa->nome) > 0 && ord->next == NULL){
				ord->next = j;
				j->next = NULL;
			}
		}
	}
}


equipa *procura_equipa(hash_equipa **hashtable_e, char *nome){
	hash_equipa *j;
	int indice;
	indice = hash(nome, PRIMO);

	for(j = hashtable_e[indice]; j != NULL; j = j->next){
		if(strcmp(j->equipa->nome, nome) == 0)
			return j->equipa;
	}
	return NULL;
}


equipa *cria_equipa(char *nome){
	equipa *e;
	e = can_fail_malloc(sizeof(equipa));
	e->nome = can_fail_malloc((strlen(nome)+1)*sizeof(char));
	e->score = 0;
	strcpy(e->nome, nome);
	return e;
}


void adiciona_equipa(hash_equipa **hashtable_e, int NL, hash_equipa **equipas_lexic){
	hash_equipa *j;
	int indice;
	char buffer[NOME];
	scanf(" %[^\n]", buffer);
	indice = hash(buffer, PRIMO);


	if (procura_equipa(hashtable_e, buffer) != NULL)
		printf("%d Equipa existente.\n", NL);

	else{
		j = can_fail_malloc(sizeof(hash_equipa));
		j->equipa = cria_equipa(buffer);
		j->next = hashtable_e[indice];
		hashtable_e[indice] = j;
		organiza_lexic(j->equipa, equipas_lexic);

	}

}


hash_equipa **cria_hashtable_equipa(int m){
	int i;
	hash_equipa **heads = can_fail_malloc(m*sizeof(hash_equipa));
	for (i = 0; i < m; ++i) heads[i] = NULL;
	return heads;
}


int procura_maximo(hash_equipa *equipas_lexic){
	int max;
	hash_equipa *j;
	max = 0;

	for(j = equipas_lexic; j != NULL; j = j->next){
		if (j->equipa->score > max)
			max = j->equipa->score;
	}
	return max;
}


void mais_jogos_ganhos(hash_equipa *equipas_lexic, int NL, int max){
	hash_equipa *j;

	if (equipas_lexic != NULL){
		printf("%d Melhores %d\n", NL, max);
		for (j = equipas_lexic; j != NULL; j = j->next){
			if (j->equipa->score == max)
				printf("%d * %s\n", NL, j->equipa->nome);
		}
	}
}

/*---------------------------JOGOS-----------------------*/
typedef struct JOGOS{
	char *nome;
	equipa *equipa1, *equipa2;
	int score1, score2;
}jogo;


typedef struct LISTA_JOGOS{
	jogo *jogo;
	struct LISTA_JOGOS *next;
}hash_jogo;


jogo *procura_jogo(hash_jogo **hashtable_j, char *nome){
	hash_jogo *i;
	int indice;
	indice = hash(nome, PRIMO);
	for(i = hashtable_j[indice]; i != NULL; i = i->next){
		if(strcmp(i->jogo->nome, nome) == 0)
			return i->jogo;
	}
	return NULL;
}


jogo *cria_jogo(hash_equipa **hashtable_e, char *nome, char *equipa1, char *equipa2, int score1, int score2){
	
	jogo *j;
	j = can_fail_malloc(sizeof(jogo));
	j->nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
	strcpy(j->nome, nome);
	j->equipa1 = procura_equipa(hashtable_e, equipa1);
	j->equipa2 = procura_equipa(hashtable_e, equipa2);
	j->score1 = score1;
	j->score2 = score2;
	return j;
}


void adiciona_jogo(hash_jogo **hashtable_j, hash_equipa **hashtable_e, int NL, hash_jogo **jogos_ordem){
	hash_jogo *j, *ord;
	int indice, score1, score2;
	char jogo[NOME], equipa1[NOME], equipa2[NOME];
	scanf(" %[^:]", jogo);
	scanf(":%[^:]", equipa1);
	scanf(":%[^:]", equipa2);
	scanf(":%d", &score1);
	scanf(":%d", &score2);
	indice = hash(jogo, PRIMO);

	if (procura_jogo(hashtable_j, jogo) != NULL)
		printf("%d Jogo Existente.\n", NL);

	else if (procura_equipa(hashtable_e, equipa1) == NULL || procura_equipa(hashtable_e, equipa2) == NULL)
		printf("%d Equipa inexistente.\n", NL);

	else{
		j = can_fail_malloc(sizeof(hash_jogo));
		j->jogo = cria_jogo(hashtable_e, jogo, equipa1, equipa2, score1, score2);

		ord = can_fail_malloc(sizeof(hash_jogo));
		ord->jogo = j->jogo;

		if (score1 > score2)
			j->jogo->equipa1->score += 1;
		else if (score1 < score2)
			j->jogo->equipa2->score += 1;

		j->next = hashtable_j[indice];
		hashtable_j[indice] = j;

		ord->next = *jogos_ordem;
		*jogos_ordem = ord;


	}
}


void compara_scores(int a, int b, equipa *equipa1, equipa *equipa2){
	if (a > 0 && b == 0)
		equipa1->score -= 1;

	else if (a < 0 && b == 0)
		equipa2->score -= 1;

	else if (a == 0 && b > 0)
		equipa1->score += 1;

	else if (a == 0 && b < 0)
		equipa2->score += 1;
	
	else if (a < 0 && b > 0){
		equipa1->score += 1;
		equipa2->score -= 1;
	}

	else if (a > 0 && b < 0){
		equipa1->score -= 1;
		equipa2->score += 1;
	}
}


void altera_pontuacao(hash_jogo **hashtable_j, int NL){
		
	jogo *j;
	char jogo[NOME];
	int score1, score2;

	scanf(" %[^:]", jogo);
	scanf(":%d", &score1);
	scanf(":%d", &score2);

	if (procura_jogo(hashtable_j, jogo) == NULL)
		printf("%d Jogo inexistente.\n", NL);
	
	else{
		j = procura_jogo(hashtable_j, jogo);
		compara_scores(j->score1 - j->score2, score1 - score2, j->equipa1, j->equipa2);
		j->score1 = score1;
		j->score2 = score2;
	}
}


void apaga_jogo_ordenado(hash_jogo **jogos_ordem, char *jogo){
	hash_jogo *j, *anterior;

	for(j = *jogos_ordem, anterior = NULL; j != NULL; anterior = j, j = j->next){
		if (strcmp(j->jogo->nome, jogo) == 0){
			if (j == *jogos_ordem)
				*jogos_ordem = j->next;

			else{
				anterior->next = j->next;
				free(j);
				break;
			}
		}
	}
}


void apaga_jogo_main(hash_jogo **hashtable_j, int NL, hash_jogo **jogos_ordem){
	hash_jogo *j, *anterior;
	char jogo[NOME];
	int indice;
	scanf(" %[^\n]", jogo);

	if (procura_jogo(hashtable_j, jogo) == NULL)
		printf("%d Jogo inexistente.\n", NL);

	else{
		indice = hash(jogo, PRIMO);
		for (j = hashtable_j[indice], anterior = NULL; j != NULL; anterior = j, j = j->next){
			if (strcmp(j->jogo->nome, jogo) == 0){

				if (j == hashtable_j[indice])
					hashtable_j[indice] = j->next;

				else
					anterior->next = j->next;
			
				compara_scores(j->jogo->score1 - j->jogo->score2, 0, j->jogo->equipa1, j->jogo->equipa2);
				apaga_jogo_ordenado(jogos_ordem, jogo);

				free(j->jogo->nome);
				free(j->jogo);
				free(j);

				break;
			}
		}
	}
}



void lista_jogos(hash_jogo *jogos_ordem, int NL){
	if(jogos_ordem == NULL)
		return;
	lista_jogos(jogos_ordem->next, NL);

	printf("%d %s %s ", NL, jogos_ordem->jogo->nome, jogos_ordem->jogo->equipa1->nome);
	printf("%s %d %d\n", jogos_ordem->jogo->equipa2->nome, jogos_ordem->jogo->score1, jogos_ordem->jogo->score2);
}



hash_jogo **cria_hashtable_jogo(int m){
	int i;
	hash_jogo **heads = can_fail_malloc(m*sizeof(hash_jogo));
	for (i = 0; i < m; ++i) heads[i] = NULL;
	return heads;
}



/*------------------------------MAIN-------------------------*/

void liberta(hash_equipa **hashtable_e, hash_jogo **hashtable_j,hash_equipa **equipas_lexic, hash_jogo **jogos_ordem){
	int indice;
	hash_jogo *j, *q;
	hash_equipa *i, *k;



	for (indice = 0; indice < PRIMO; ++indice){
		for(j = hashtable_j[indice]; j != NULL; j = q){
			q = j->next;
			free(j->jogo->nome);
			free(j->jogo);
			free(j);
		}
	}
	free(hashtable_j);


	for (j = *jogos_ordem; j != NULL; j = q){
		q = j->next;
		free(j);
	}

	for (i = *equipas_lexic; i != NULL; i = k){
		k = i->next;
		free(i);
	}

	for (indice = 0; indice < PRIMO; ++indice){
		for (i = hashtable_e[indice]; i != NULL; i = k){
			k = i->next;
			free(i->equipa->nome);
			free(i->equipa);
			free(i);
		}
	}
	free(hashtable_e);


}


int main(){
	hash_equipa **hashtable_e, *equipas_lexic;
	hash_jogo **hashtable_j, *jogos_ordem;
	equipa *equipa;
	jogo *jogo;
	char cmnd, buffer[NOME];
	int NL, max;
	hashtable_e = cria_hashtable_equipa(PRIMO);
	hashtable_j = cria_hashtable_jogo(PRIMO);
	NL = 0;
	max = 0;
	jogos_ordem = NULL;
	equipas_lexic = NULL;
	while (scanf("%c", &cmnd) != 'x'){
		++NL;
		switch (cmnd){
			case('a'):
			adiciona_jogo(hashtable_j, hashtable_e, NL, &jogos_ordem);
			break;

			case 'A':
			adiciona_equipa(hashtable_e, NL, &equipas_lexic);
			break;
			
			case 'l':
			lista_jogos(jogos_ordem, NL);
			break;
			
			case 'P':
			scanf(" %[^\n]", buffer);
			equipa = procura_equipa(hashtable_e, buffer);
			if (equipa != NULL)
				printf("%d %s %d\n", NL, equipa->nome, equipa->score);
			else
				printf("%d Equipa inexistente.\n", NL);
			break;

			case 'p':
			scanf(" %[^\n]", buffer);
			jogo = procura_jogo(hashtable_j, buffer);
			if (jogo != NULL)
				printf("%d %s %s %s %d %d\n", NL, jogo->nome, jogo->equipa1->nome, jogo->equipa2->nome, jogo->score1, jogo->score2);
			else
				printf("%d Jogo inexistente.\n", NL);
			break;

			case 's':
			altera_pontuacao(hashtable_j, NL);
			break;

			case 'r':
			apaga_jogo_main(hashtable_j, NL, &jogos_ordem);
			break;

			case('g'):
			max = procura_maximo(equipas_lexic);
			mais_jogos_ganhos(equipas_lexic, NL, max);
			break;

			case 'x':
			liberta(hashtable_e, hashtable_j,&equipas_lexic, &jogos_ordem);
				return 0;
			break;
		}	

		getchar(); /* o character '\n' estava a estragar-me a vida, por isso eliminei-o*/

	}	
	return 0;
}
