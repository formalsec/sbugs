#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "equipas.h"
#include "equipas_hashtable.h"
#include "jogos.h"
#include "jogos_hashtable.h"

#define MAXHASHTABLE 2003
#define MAXNOME 1024


/*		PROTOTIPOS		*/
void adiciona_jogo(int linha_input, jogo **ht_jogos, int *pt_max_ht_jogos, int *pt_num_elem_ht_jogos, 
				   lista_jogos *lst_jogos, equipa **ht_equipas, int *max_ht_equipas, int *max_vitorias);

void lista_jogos_ordem_intro(int linha_input, lista_jogos *lst_jogos);

void procura_jogo(int linha_input, jogo **ht_jogos, int *pt_max_ht_jogos);

void apaga_jogo(int linha_input, jogo **ht_jogos, int *pt_max_ht_jogos, int *pt_num_elem_ht_jogos, 
				lista_jogos *lst_jogos);

void altera_resultado(int linha_input, jogo **ht_jogos, int *pt_max_ht_jogos, int *pt_max_vitorias);

void adiciona_equipa(int linha_input, equipa **ht_equipas, int *max_ht_eqp, 
					int *num_elem_ht_equipas);

void procura_equipa(int linha_input, equipa **ht_equipas, int *max_ht_eqp);

void lista_equipas_mais_vitorias(int linha_input, equipa **ht_equipas, int max_ht_equipas, 
								 int num_elem_ht_equipas, int max_vitorias);

/*		FUNCOES AUXILIARES		*/
int compara_strings(const void *ptr_str_1, const void *ptr_str_2);




/*		FUNCAO INICIAL		*/
int main() {
	int max_ht_equipas = MAXHASHTABLE; /* dimensao (inicial) da hash table de equipas */
	int *pt_max_ht_equipas = &max_ht_equipas;
	int num_elem_ht_equipas;	/* numero de elementos na hash table (equipas) */
	int *pt_num_elem_ht_equipas = &num_elem_ht_equipas;
	equipa **ht_equipas = inicia_hashtable_equipas(pt_max_ht_equipas, pt_num_elem_ht_equipas);
	int max_vitorias = 0; /* guarda o numero maximo de vitorias atual */
	int *pt_max_vitorias = &max_vitorias;

	int max_ht_jogos = MAXHASHTABLE; /* dimensao (inicial) da hash table de jogos */
	int *pt_max_ht_jogos = &max_ht_jogos;
	int num_elem_ht_jogos;	/* numero de elementos na hash table (jogos) */
	int *pt_num_elem_ht_jogos = &num_elem_ht_jogos;
	jogo **ht_jogos = inicia_hashtable_jogos(pt_max_ht_jogos, pt_num_elem_ht_jogos);
	lista_jogos *lst_jogos = cria_lista_jogos();
	int linha_input = 1;
	while (1) { 
		char cmd;
		cmd = getchar();
		switch(cmd) {
			case 'a':
				adiciona_jogo(linha_input, ht_jogos, pt_max_ht_jogos, pt_num_elem_ht_jogos,
							  lst_jogos, ht_equipas,pt_max_ht_equipas, pt_max_vitorias);
				break;
			case 'l':
				lista_jogos_ordem_intro(linha_input, lst_jogos);
				break;
			case 'p':
				 procura_jogo(linha_input, ht_jogos, pt_max_ht_jogos);
				break;
			case 'r':
				apaga_jogo(linha_input, ht_jogos, pt_max_ht_jogos, pt_num_elem_ht_jogos, lst_jogos);
				break;
			case 's':
				altera_resultado(linha_input, ht_jogos, pt_max_ht_jogos, pt_max_vitorias);
				break;
			case 'A':
				adiciona_equipa(linha_input, ht_equipas, pt_max_ht_equipas, pt_num_elem_ht_equipas);
				break;
			case 'P':
				procura_equipa(linha_input, ht_equipas, pt_max_ht_equipas);
				break;
			case 'g':
				lista_equipas_mais_vitorias(linha_input, ht_equipas, max_ht_equipas, 
											num_elem_ht_equipas, max_vitorias);
				break;
			case 'x': /* termina o programa, liberta toda a memoria alocada dinamicamente */
				liberta_hashtable_equipas(ht_equipas, max_ht_equipas);
				liberta_hashtable_jogos(ht_jogos, max_ht_jogos);
				free(lst_jogos);
				return 0;	/* Termina o programa (sem erros) */	
			default:
				printf("Comando desconhecido\n");
		}
		getchar();	/* Retira o '\n' do stdin */
		linha_input++;
	}
	return -1;	/* Se chegou ate aqui, algo correu mal */
}         



/*		FUNCOES PRINCIPAIS		*/

/* adiciona um novo jogo ao sistema */
/* input: linha de input atual
		  ponteiro para a hash table de jogos
		  ponteiro para o tamanho da hash table de jogos
		  ponteiro para o numero de elementos guardados na hash table de jogos
		  ponteiro para a lista ligada de jogos
		  ponteiro para a hash table de equipas
		  ponteiro para o tamanho da hash table de equipas
		  ponteiro para o resultado (de um jogo) maximo atual */
/* erros: 1: se ja existir um jogo com esse nome no sistema
		  2: no caso de uma das equipas ou ambas nao existirem no sistema */
void adiciona_jogo(int linha_input, jogo **ht_jogos, int *pt_max_ht_jogos, 
				   int *pt_num_elem_ht_jogos, lista_jogos *lst_jogos, equipa **ht_equipas, 
				   int *pt_max_ht_equipas, int *max_vitorias) {
	char jogo_input[MAXNOME], equipa_1_input[MAXNOME], equipa_2_input[MAXNOME];
	int reslt_1, reslt_2;
	equipa *equipa_1, *equipa_2;
	scanf(" %1023[^:\n]:%1023[^:]:%1023[^:]:%d:%d", jogo_input, equipa_1_input, 
			equipa_2_input, &reslt_1, &reslt_2);
	if ((procura_jogo_ht(ht_jogos, jogo_input, *pt_max_ht_jogos)) != NULL) { 
		printf("%d Jogo existente.\n", linha_input);/* se procura_jogo_ht() devolve algo diferente */
		return; 				/* de NULL, entao o jogo ja esta na hash table, e assinala o erro */
	}
	if(((equipa_1 = procura_equipa_ht(ht_equipas, equipa_1_input, *pt_max_ht_equipas)) == NULL) 
	  	|| ((equipa_2 = procura_equipa_ht(ht_equipas, equipa_2_input, *pt_max_ht_equipas)) == NULL)) {
		printf("%d Equipa inexistente.\n", linha_input); /* se as equipas nao existirem no sistema, */
		return; 										 /* procura_equipa_ht() retorna NULL */
	}
	insere_jogo(novo_jogo(jogo_input, equipa_1, equipa_2, reslt_1, reslt_2), pt_max_ht_jogos, 
				ht_jogos, pt_num_elem_ht_jogos, lst_jogos); 
	if (reslt_1 > reslt_2) { /* atualiza numero de vitorias das equipas participantes no jogo */
		if ((++equipa_1->num_vitorias) > *max_vitorias) {
			*max_vitorias = equipa_1->num_vitorias;
		}
	}
	else if (reslt_2 > reslt_1) {
		if ((++equipa_2->num_vitorias) > *max_vitorias) {
			*max_vitorias = equipa_2->num_vitorias;
		}
	}
}


/* lista todos os jogos introduzidos, pela ordem em que foram indroduzidos no sistema, caso nao 
exista nenhum jogo no sistema, nao imprime nada */
/* input: linha de input atual
		  ponteiro para a lista ligada de jogos */
void lista_jogos_ordem_intro(int linha_input, lista_jogos *lst_jogos) {
	jogo *jogo_aux;
	if (lst_jogos->jogo_inicial == NULL) { /* nao existem jogos no sistema */
		return;
	}
	else {
		for (jogo_aux = lst_jogos->jogo_inicial; jogo_aux != NULL; jogo_aux = jogo_aux->seguinte) {
			printf("%d %s %s %s %d %d\n", linha_input, jogo_aux->nome, jogo_aux->equipa_1->nome,
									  jogo_aux->equipa_2->nome, jogo_aux->resultado_1,
									  jogo_aux->resultado_2);
		}
	}
}


/* procura um jogo dado um nome */
/* input: linha de input atual
		  ponteiro para a hash table de jogos
		  ponteiro para o tamanho da hash table */
/* erros: 1: se nao exister nenhum jogo com esse nome no sistema */
void procura_jogo(int linha_input, jogo **ht_jogos, int *pt_max_ht_jogos) {
	char jogo_input[MAXNOME];
	jogo *jogo_procurar;
	scanf(" %1023[^\n]", jogo_input);
	if ((jogo_procurar = procura_jogo_ht(ht_jogos, jogo_input, *pt_max_ht_jogos)) == NULL) {
		printf("%d Jogo inexistente.\n", linha_input);
	}
	else {
		printf("%d %s %s %s %d %d\n", linha_input, jogo_procurar->nome, jogo_procurar->equipa_1->nome,
									  jogo_procurar->equipa_2->nome, jogo_procurar->resultado_1,
									  jogo_procurar->resultado_2);
	}
}


/* apaga um jogo dado um nome */
/* input: linha de input atual
		  ponteiro para a hash table de jogos
		  ponteiro para o tamanho da hash table de jogos
		  ponteiro para o numero de elementos guardados na hash table de jogos
		  ponteiro para a lista ligada de jogos */
/* erros: 1: se nao existir nenhum jogo com esse nome no sistema */
void apaga_jogo(int linha_input, jogo **ht_jogos, int *pt_max_ht_jogos, int *pt_num_elem_ht_jogos, 
				lista_jogos *lst_jogos) {
	char jogo_input[MAXNOME];
	scanf(" %1023[^\n]", jogo_input);
	if (remove_jogo_ht(jogo_input, ht_jogos, pt_max_ht_jogos, pt_num_elem_ht_jogos, lst_jogos) != 0) { 
		printf("%d Jogo inexistente.\n", linha_input); /* se falhar na remocao (jogo nao esta na */
	}							   /* hash table), remove_jogo() retorna -1, e assinala-se o erro*/
}


/* altera o resultado de um jogo dado o nome */
/* input: linha de input atual
		  ponteiro para a hash table de jogos
		  ponteiro para o tamanho da hash table de jogos
		  ponteiro para o resultado (de um jogo) maximo atual */
/* erros: 1: se nao existir nenhum jogo com esse nome no sistema */
void altera_resultado(int linha_input, jogo **ht_jogos, int *pt_max_ht_jogos, int *pt_max_vitorias) {
	char jogo_input[MAXNOME];
	int novo_reslt_1, novo_reslt_2;
	jogo *jogo_alterar;
	scanf(" %1023[^:\n]:%d:%d", jogo_input, &novo_reslt_1, &novo_reslt_2);
	if ((jogo_alterar = procura_jogo_ht(ht_jogos, jogo_input, *pt_max_ht_jogos)) == NULL) {
		printf("%d Jogo inexistente.\n", linha_input);;
	}
	else {
		altera_resultados_jogo(jogo_alterar, novo_reslt_1, novo_reslt_2);
		if (jogo_alterar->equipa_1->num_vitorias > *pt_max_vitorias) {
			*pt_max_vitorias = jogo_alterar->equipa_1->num_vitorias;
		}
		else if (jogo_alterar->equipa_2->num_vitorias > *pt_max_vitorias) {
			*pt_max_vitorias = jogo_alterar->equipa_2->num_vitorias;
		}
	}
}


/* adiciona uma nova equipa ao sistema */
/* input: linha de input atual
		  ponteiro para a hash table de equipas
		  ponteiro para o tamanho da hash table de equipas
		  ponteiro para o numero de elementos guardados na hash table de equipas */
/* erros: 1: se ja exister uma equipa com esse nome no sistema*/
void adiciona_equipa(int linha_input, equipa **ht_equipas, int *pt_max_ht_eqp, 
					int *num_elem_ht_equipas) {
	char equipa_input[MAXNOME];
	equipa *n_equipa;
	scanf(" %1023[^\n]", equipa_input);
	n_equipa = nova_equipa(equipa_input);
	if (insere_equipa(n_equipa, pt_max_ht_eqp, ht_equipas, num_elem_ht_equipas) == NULL) { /* se falhar na */
		liberta_equipa(n_equipa); /* insercao, insere_equipa() retorna 0, liberta-se a memoria alocada */
		printf("%d Equipa existente.\n", linha_input); /* e assinala-se o erro */
	}
}


/* procura uma equipa dado um nome */
/* input: linha de input atual
		  ponteiro para a hash table de equipas
		  ponteiro para o tamanho da hash table de equipas */
/* erros: 1: se nao exister nenhuma equipa com esse nome no sistema */
void procura_equipa(int linha_input, equipa **ht_equipas, int *pt_max_ht_eqp) {
	char equipa_input[MAXNOME];
	equipa *equipa_procurar;
	scanf(" %1023[^\n]", equipa_input);
	if ((equipa_procurar = procura_equipa_ht(ht_equipas, equipa_input, *pt_max_ht_eqp)) == NULL) {
		printf("%d Equipa inexistente.\n", linha_input);
	}
	else {
		printf("%d %s %d\n", linha_input, equipa_procurar->nome, equipa_procurar->num_vitorias);
	}
}


/* encontra as euipas que ganharam mais jogos e lista por ordem lexicografica (do nome da equipa) */
/* input: linha de input atual
		  ponteiro para a hashtable de equipas
		  tamanho maximo da hash table de equipas
		  numero de elementos guardados na hash table de equipas
		  numero maximo de vitorias das equipas*/
void lista_equipas_mais_vitorias(int linha_input, equipa **ht_equipas, int max_ht_equipas, 
								 int num_elem_ht_equipas, int max_vitorias) {
	char **aux_equipas = malloc((sizeof(char*))*num_elem_ht_equipas); /* vetor de strings a ordenar */
	int i, j = 0;
	for (i = 0; i < max_ht_equipas; i++) {
		if (ht_equipas[i] == NULL) {
			continue;
		}
		else if (ht_equipas[i]->num_vitorias == max_vitorias) { /* procura equipas com o numero de */
			aux_equipas[j++] = ht_equipas[i]->nome; /* vitorias, igual ao maximo guardado */
		}
	}
	if (j != 0) { /* se nao encontrou nenhuma equipa, nao imprime nada (j nunca aumentou o seu valor) */
		qsort(aux_equipas, j, sizeof(char*), compara_strings); /* ordena as equipas por ordem lexicografrica */
		printf("%d Melhores %d\n", linha_input, max_vitorias);
		for (i = 0; i < j; i++) {
			printf("%d * %s\n", linha_input, aux_equipas[i]);
		}
	}
	free(aux_equipas);	
}


/* funcao auxiliar para ordenar um vetor de ponteiros para strings */
int compara_strings(const void *ptr_str_1, const void *ptr_str_2) {
	char *str_1 = *(char**)ptr_str_1;
	char *str_2 = *(char**)ptr_str_2;
	return strcmp(str_1, str_2);
}
