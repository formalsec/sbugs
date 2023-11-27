#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj2.h"
/* Maximo de caracteres do nome de equipa = 1023 + '\0' */
#define MAX_CAR_EQUIPA 1024
#define M 127



/* Inicio da lista das equipas */
equipa inicio_equipas = NULL;
/* Inicio da tabela dos jogos */
static jogo *inicio_jogos;
/* Valor do numero de equipas */
int ordem_equipa;
/* Numero da linha de comandos do terminal */
int linha_comando;
/* Numero de jogos introduzidos */
int numero_jogos_total;


/****************************************************************************/
/*************** TABELA DE DISPERSAO DOS JOGOS E RESPETIVO INDICE **********/
/***************************************************************************/

/* Tabela de dispersao para guardar os jogos */
int procura_indice_tabela_dispersao(char *v) {
	int h = 0, a = 127;
	for (; *v != '\0'; v++)
		h = (a*h + *v) % M;
	return h;
}


void inicializa_tabla_dispersao() {
	int i;
	inicio_jogos = (jogo*) malloc(M*sizeof(jogo));
	for (i = 0; i < M; i++)
		inicio_jogos[i] = NULL;
}

/****************************************************************************/
/************************** FUNCOES AUXILIARES ******************************/
/****************************************************************************/

/* Esta funcao auxiliar aloca memoria para um jogo novo */
jogo criar_jogo(char *nomejogo, char *nome_equipa1, char *nome_equipa2, int pontos1, int pontos2) {
	jogo novo_jogo = (jogo) malloc(sizeof(struct fila));
	novo_jogo -> nome_jogo = (char *) malloc(sizeof(char)*(MAX_CAR_EQUIPA));
	strcpy(novo_jogo -> nome_jogo, nomejogo);

	novo_jogo -> equipa1 = (char *) malloc(sizeof(char)*(MAX_CAR_EQUIPA));
	strcpy(novo_jogo -> equipa1, nome_equipa1);
	novo_jogo -> equipa2 = (char *) malloc(sizeof(char)*(MAX_CAR_EQUIPA));
	strcpy(novo_jogo -> equipa2, nome_equipa2);
	novo_jogo -> pontos_1 = pontos1;
	novo_jogo -> pontos_2 = pontos2;
	novo_jogo -> proximo = NULL;
	numero_jogos_total++;
	novo_jogo -> ordem_entrada_jogo = numero_jogos_total;
	return novo_jogo;
}

/* Esta funcao insere um jogo no inicio de uma lista da tabela de dispersao */
jogo insere_jogo_lista(jogo *inicio_jogos, int i, char *nomejogo, char *nome_equipa1, char *nome_equipa2, int pontos1, int pontos2) {
	 jogo p;
	 jogo j = criar_jogo(nomejogo, nome_equipa1, nome_equipa2, pontos1, pontos2);
	 p = inicio_jogos[i];
	 j -> proximo = p;
	 inicio_jogos[i] = j;
	 return inicio_jogos[i];
}


/* Esta funcao auxiliar cria uma equipa para depois em adiciona_equipa() ser colocada na lista */
equipa criar_equipa(char *nome) {
	equipa nova_equipa = (equipa) malloc(sizeof(struct lista));
	ordem_equipa++;
	nova_equipa -> ordem_entrada = ordem_equipa;
	nova_equipa -> nome_equipa = (char *) malloc(sizeof(char)*(MAX_CAR_EQUIPA));
	strcpy(nova_equipa -> nome_equipa, nome);
	nova_equipa -> numero_jogos_ganhos = 0;
	nova_equipa -> proximo = NULL;
	return nova_equipa;
}


/* Esta funcao auxiliar aumenta o numero de jogos ganhos na respetiva equipa que ganhou o jogo */
int muda_numero_jogos_ganhos(char *nome_equipa1, char * nome_equipa2, int pontos1, int pontos2) {
	equipa p;
	if (pontos1 > pontos2) {
		for (p = inicio_equipas; p != NULL; p = p->proximo)
			if (strcmp(p -> nome_equipa, nome_equipa1) == 0)
				p -> numero_jogos_ganhos += 1;
	}
	else if (pontos1 < pontos2) {
		for (p = inicio_equipas; p != NULL; p = p->proximo)
			if (strcmp(p -> nome_equipa, nome_equipa2) == 0)
				p -> numero_jogos_ganhos += 1;
	}
	return 0;
}


/* Esta funcao auxiliar atualiza uma lista de jogos apos ser removido um jogo */
jogo remove_jogo_lista(int i, char *nome) {
	jogo curr, tmp, prev;
	equipa p;
	for (curr = inicio_jogos[i], prev = NULL; curr != NULL; ) {
		if (strcmp(curr -> nome_jogo, nome) == 0) {
			/* Se o jogo for o primeiro elemento da lista: */
			if (curr == inicio_jogos[i])
				inicio_jogos[i] = curr -> proximo;
			else
				prev -> proximo = curr -> proximo;

			/* Altera numero de jogos ganhos da equipa vencedora */
			if (curr -> pontos_1 > curr -> pontos_2) {
				for (p = inicio_equipas; p != NULL; p = p -> proximo)
					if (strcmp(curr -> equipa1, p -> nome_equipa) == 0)
						p -> numero_jogos_ganhos -= 1;
			}

			else if (curr -> pontos_1 < curr -> pontos_2) {
				for (p = inicio_equipas; p != NULL; p = p -> proximo)
					if (strcmp(curr -> equipa2, p -> nome_equipa) == 0)
						p -> numero_jogos_ganhos -= 1;
			}

			/* Liberta o espaco da memoria deste jogo */
      tmp = curr;
      curr = tmp->proximo;
			free(tmp->nome_jogo);
			free(tmp->equipa2);
			free(tmp->equipa1);
			free(tmp);
		} else {
      prev = curr; curr = curr->proximo;
    }
	}
	return inicio_jogos[i];
}

/* Esta funcao auxiliar cria uma lista para as equipas com mais jogos ganhos */
podio adiciona_podio(char *nome) {
	podio novo = (podio) malloc(sizeof(struct pilha));
	novo -> nome_equipa_podio = (char*) malloc(sizeof(char)*MAX_CAR_EQUIPA);
	strcpy(novo -> nome_equipa_podio, nome);
	novo -> proximo = NULL;
	return novo;
}


/****************************************************************************/
/************************** FUNCOES PRINCIPAIS ******************************/
/****************************************************************************/

/* adiciona_novo_jogo e a funcao que adiciona um novo jogo ao sistema */
void adiciona_novo_jogo() {
	char vector[MAX_CAR_EQUIPA];
	char *nomejogo = vector;
	int pontos1, pontos2;
	char vetor1[MAX_CAR_EQUIPA], vetor2[MAX_CAR_EQUIPA];
	char *nome_equipa1 = vetor1;
	char *nome_equipa2 = vetor2;
	int i;
	int controlo_existe_equipa1 = 0;
	int controlo_existe_equipa2 = 0;
	int existe_nome_jogo = 0;
	equipa p = inicio_equipas;
	jogo j;

	scanf(" %[^:]:%[^:]:%[^:]:%d:%d", nomejogo, nome_equipa1, nome_equipa2, &pontos1, &pontos2);
	i = procura_indice_tabela_dispersao(nomejogo);

	/* Verificacao da existencia de alguma equipa */
	if (p == NULL)
		printf("%d Equipa inexistente.\n", linha_comando);
	else {
		/* Verifica se existe algum jogo no sistema com o mesmo nome que o introduzido */
		for (j = inicio_jogos[i]; j != NULL; j = j -> proximo)
			if (strcmp(j -> nome_jogo, nomejogo) == 0)
				existe_nome_jogo++;
		if (existe_nome_jogo != 0)
			printf("%d Jogo existente.\n", linha_comando);
		else {
			/* Verifica se existem equipas no sistema com o mesmo nome das equipas introduzidas */
			for (p = inicio_equipas; p != NULL; p = p -> proximo) {
				if (strcmp(p -> nome_equipa, nome_equipa1) == 0)
					controlo_existe_equipa1++;
				else if (strcmp(p -> nome_equipa, nome_equipa2) == 0)
					controlo_existe_equipa2++;
			}
			if (controlo_existe_equipa1 == 0 || controlo_existe_equipa2 == 0)
				printf("%d Equipa inexistente.\n", linha_comando);

			/* No caso das condicoes anteriores serem respeitadas, o sistema cria um novo jogo */
			else {
				inicio_jogos[i] = insere_jogo_lista(inicio_jogos, i, nomejogo, nome_equipa1, nome_equipa2, pontos1, pontos2);
				muda_numero_jogos_ganhos(nome_equipa1, nome_equipa2, pontos1, pontos2);
			}
		}
	}
}

/* procura_jogo e a funcao que procura um jogo especifico, no caso de existir */
void procura_jogo() {
	char vetor[MAX_CAR_EQUIPA];
	char *nome = vetor;
	int i;
	int existe_nome_jogo = 0;
	jogo j;
	scanf(" %[^:\n]", nome);
	/* Determina a posicao que o jogo ocupa na tabela de dispersao dos jogos */
	i = procura_indice_tabela_dispersao(nome);
	/* Se nao existirem jogos nesta lista da tabela, levanta erro */
	if (inicio_jogos[i] == NULL)
		printf("%d Jogo inexistente.\n", linha_comando);
	else {
		for (j = inicio_jogos[i]; j != NULL; j = j->proximo)
			if (strcmp(j -> nome_jogo, nome) == 0) {
				printf("%d %s %s %s %d %d\n", linha_comando, j->nome_jogo, j->equipa1, j->equipa2, j->pontos_1, j->pontos_2);
				existe_nome_jogo++;
			}
		if (existe_nome_jogo == 0)
			printf("%d Jogo inexistente.\n", linha_comando);
	}

}


/* altera_resultado_jogo e a funcao que altera o valor das pontuacoes das equipas de um jogo */
void altera_resultado_jogo() {
	char vetor[MAX_CAR_EQUIPA];
	char *nome = vetor;
	int pontos1, pontos2, i;
	int existe_nome_jogo = 0;
	jogo j;
	equipa p;
	scanf(" %[^:\n]:%d:%d", nome, &pontos1, &pontos2);
	/* Determina a posicao que o jogo ocupa na tabela de dispersao dos jogos */
	i = procura_indice_tabela_dispersao(nome);
	if (inicio_jogos[i] == NULL)
		printf("%d Jogo inexistente.\n", linha_comando);
	else {
		for (j = inicio_jogos[i]; j != NULL; j = j -> proximo)
			if (strcmp(j->nome_jogo, nome) == 0) {
				existe_nome_jogo++;

				/* Muda o numero de jogos ganhos destas equipas */
				if (j -> pontos_1 < j -> pontos_2) {
					/* A equipa 1 passa a ter mais um jogo ganho e a equipa 2 menos 1 */
					if (pontos1 > pontos2)
						for (p = inicio_equipas; p != NULL; p = p -> proximo) {
							if (strcmp(p -> nome_equipa, j -> equipa1) == 0)
								p -> numero_jogos_ganhos += 1;
							else if (strcmp(p -> nome_equipa, j -> equipa2) == 0)
								p -> numero_jogos_ganhos -= 1;
						}
					else if (pontos1 == pontos2)
						for (p = inicio_equipas; p != NULL; p = p -> proximo)
							if (strcmp(p -> nome_equipa, j -> equipa2) == 0)
								p -> numero_jogos_ganhos -= 1;
				}
				else if (j -> pontos_1 > j -> pontos_2) {
					/* Se a equipa 1 deixou de vencer perde um jogo ganho */
					if (pontos1 < pontos2)
						for (p = inicio_equipas; p != NULL; p = p -> proximo) {
							if (strcmp(p -> nome_equipa, j -> equipa1) == 0)
								p -> numero_jogos_ganhos -= 1;
							else if (strcmp(p -> nome_equipa, j -> equipa2) == 0)
								p -> numero_jogos_ganhos += 1;
						}
					else if (pontos1 == pontos2)
						for (p = inicio_equipas; p != NULL; p = p -> proximo)
							if (strcmp(p -> nome_equipa, j -> equipa1) == 0)
								p -> numero_jogos_ganhos -= 1;
				}
				/* Altera a pontuacao das equipas no jogo */
				j -> pontos_1 = pontos1;
				j -> pontos_2 = pontos2;
			}
		if (existe_nome_jogo == 0)
			printf("%d Jogo inexistente.\n", linha_comando);
	}
}


/* apaga_jogo e a funcao que dado um nome de um jogo, o retira do sistema */
void apaga_jogo() {
	char vetor[MAX_CAR_EQUIPA];
	char *nome = vetor;
	int i;
	int existe_nome_jogo = 0;
	jogo j;
	scanf(" %[^:\n]", nome);
	i = procura_indice_tabela_dispersao(nome);
	/* No caso de nao existirem jogos nesta lista i da tabela */
	if (inicio_jogos[i] == NULL)
		printf("%d Jogo inexistente.\n", linha_comando);

	else {
		for (j = inicio_jogos[i]; j != NULL; j = j -> proximo)
			if (strcmp(j -> nome_jogo, nome) == 0)
				existe_nome_jogo ++;
		/* Se o jogo existe vai ser removido */
		if (existe_nome_jogo != 0) {
			inicio_jogos[i] = remove_jogo_lista(i, nome);
		}

		else
			printf("%d Jogo inexistente.\n", linha_comando);
	}
}


/* podio_equipas e a funcao que mostra as equipas com mais jogos ganhos */
void podio_equipas() {
	int max_jogos_ganhos = 0;
	char vetor[MAX_CAR_EQUIPA];
	char *nome = vetor;
	int numero_elementos = 0;
	/* Primeira variavel da lista do podio */
	equipa p;
	podio l;
	/* Variavel que guarda a primeira equipa do podio */
	podio lista_podio = NULL;

	for (p = inicio_equipas; p != NULL; p = p -> proximo)
		if ( p -> numero_jogos_ganhos > max_jogos_ganhos)
			max_jogos_ganhos = p -> numero_jogos_ganhos;
	if (max_jogos_ganhos >= 0) {
		for (p = inicio_equipas; p != NULL; p = p -> proximo)
			if (p -> numero_jogos_ganhos == max_jogos_ganhos) {
				strcpy(nome, p->nome_equipa);
				/* No caso de ainda nao haver nenhuma equipa no podio */
				if (lista_podio == NULL) {
					lista_podio = adiciona_podio(nome);
					numero_elementos++;
				}
				/* Se ja houver equipas no podio */
				else {
					l = lista_podio;
					while (l -> proximo != NULL)
						l = l -> proximo;
					l -> proximo = adiciona_podio(nome);
					numero_elementos++;

				}
			}

		/* Libertar memoria do podio */
		printf("%d Melhores %d\n", linha_comando, max_jogos_ganhos);
		for (l = lista_podio; l != NULL; l = l -> proximo) {
			printf("%d * %s\n", linha_comando,l -> nome_equipa_podio);
		}
	}
}


/* lista_todos_jogos e a funcao que mostra todos os jogos por ordem de introducao no sistema */
void lista_todos_jogos() {
	int inicio = 1;
	int i;
	int nao_existe = 0;
	jogo j;
	/* So lista se houver jogos */
	if (numero_jogos_total > 0) {
		while (inicio <= numero_jogos_total) {
			for (i = 0; i < 127; i++)
				for (j = inicio_jogos[i]; j != NULL; j = j -> proximo)
					if (j -> ordem_entrada_jogo == inicio) {
						printf("%d %s %s %s %d %d\n", linha_comando, j -> nome_jogo, j -> equipa1, j -> equipa2, j -> pontos_1, j -> pontos_2);
						inicio++;
						nao_existe = 0;
					}
					else
						nao_existe = 1;
			if (nao_existe == 1)
				inicio++;
		}
	}
}


/* adiciona_equipa e a funcao que adiciona uma nova equipa ao sistema */
void adiciona_equipa() {
	int existe_equipa = 0;
	char vetor[MAX_CAR_EQUIPA];
	char *nome = vetor;
	equipa p = inicio_equipas;

	scanf(" %[^:\n]", nome);
	/* No caso da lista estar vazia adiciona-se o primeiro elemento */
	if (inicio_equipas == NULL)
		inicio_equipas = criar_equipa(nome);

	/* No caso de ja existir uma equipa no inicio da lista */
	else {
		p = inicio_equipas;
		/* Verifica se a primeira equipa no sistema tem o nome da nova equipa */
		if (strcmp(p -> nome_equipa, nome) == 0)
			existe_equipa++;
		/* Verifica se os restantes elementos da lista tem o mesmo nome da nova equipa */
		else {
			while (p -> proximo != NULL) {
				if (strcmp(p -> nome_equipa, nome) == 0)
					existe_equipa++;
				p = p -> proximo;
				if (strcmp(p -> nome_equipa, nome) == 0)
					existe_equipa++;
			}
		}
		if (existe_equipa == 0)
			p -> proximo = criar_equipa(nome);
		/* No caso de ja existir uma equipa com esse nome, levanta erro */
		else
			printf("%d Equipa existente.\n", linha_comando);
	}
}

/* procura_equipa e a funcao que no caso de existir, mostra o numero de jogos ganhos */
void procura_equipa() {
	char vetor[MAX_CAR_EQUIPA];
	char *nome = vetor;
	int controlo = 0;
	equipa p;

	scanf(" %[^:\n]", nome);
	for (p = inicio_equipas; p != NULL; p = p -> proximo)
		if (strcmp(p -> nome_equipa, nome) == 0) {
			printf("%d %s %d\n", linha_comando, p -> nome_equipa, p -> numero_jogos_ganhos);
			controlo++;
		}
	if (controlo == 0)
		printf("%d Equipa inexistente.\n", linha_comando);
}




/* A funcao principal recebe um comando, e decide qual a operacao/funcao a executar */
int main(){
	char comando;
	/* Aloca memoria para os jogos no sistema */
	inicializa_tabla_dispersao();
	while ((comando = getchar()) != 'x'){
		/* O comando 'x' termina o programa */
		switch(comando){
			case 'a':
				/* Adiciona um novo jogo */
				linha_comando++;
				adiciona_novo_jogo();
				break;
			case 'A':
				/* Adiciona uma nova equipa */
				linha_comando++;
				adiciona_equipa();
				break;
			case 'l':
				/* Lista todos os jogos pela ordem em que foram introduzidos no sistema */
				linha_comando++;
				lista_todos_jogos();
				break;
			case 'p':
				/* Procura um jogo */
				linha_comando++;
				procura_jogo();
				break;
			case 'P':
				/* Procura uma equipa */
				linha_comando++;
				procura_equipa();
				break;
			case 'r':
				/* Apaga um jogo */
				linha_comando++;
				apaga_jogo();
				break;
			case 's':
				/* Altera a pontuacao de um jogo */
				linha_comando++;
				altera_resultado_jogo();
				break;
			case 'g':
				/* Encontra as equipas que venceram mais jogos */
				linha_comando++;
				podio_equipas();
				break;
		}
	}
	return 0;
}
