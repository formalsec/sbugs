#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_CHAR 		1023

#define HASH_PRIMO		1709
#define	HASH_RANDOM_1	31415
#define	HASH_RANDOM_2	27183
#define HASH_RANDOM_3	3		

#define	EQUIPA1 		1
#define EQUIPA2 		2
#define EMPATE			3

#define	MAIS 			'+'
#define MENOS 			'-'

#define SIM				1
#define NAO 			0



/*	Estrutura "Equipa":
		- Nome da equipa;
		- Vitorias da equipa. */
typedef struct equipa {
	char *nome;
	int vitorias;
} Equipa;


/*	Estrutura "Nd_Eq" (Node Equipa):
		- Ponteiro para uma equipa numa lista ligada;
		- Ponteiro para a proxima equipa e equipa anterior da lista. */
typedef struct node_equipas {
	Equipa *equipa;
	struct node_equipas *next, *prev;
} Nd_Eq;


/*	Estrutura "Lst_Eqs" (lista duplamente ligada):
		- Ponteiros para o primeiro e ultimo jogo
	da lista de equipas. */
typedef struct {
	struct node_equipas *head, *last;
} Lst_Eqs;


/*	Estrutura "Hsh_Eq" (Equipa em Hash Table):
		- Ponteiro para uma equipa numa lista ordenada;
		- Ponteiros para a equipa posterior
		de igual indice numa tabela de dispersao. */
typedef struct hash_equipa {
	Nd_Eq *node_e;
	struct hash_equipa *next, *prev;
} Hsh_Eq;


/*	!Estrutura "Hsh_Lst_Eqs" (Lista de Equipas em Hash Table):
		- Ponteiro para a primeira e ultima equipa da lista
		de equipas numa hash table. 
typedef struct {
	struct hash_jogo *head, *last;
} Hsh_Lst_Eqs;
*/

/*	Estrutura "Jogo":
		- Nome do jogo e das equipas que participaram;
		- Golos marcados por cada equipa.	*/
typedef struct jogo {
	char *nome, *equipa1, *equipa2;
	int score1, score2;
} Jogo;


/*	Estrutura "Nd_Jg" (Node Jogo):
		- Ponteiro para um jogo;
		- Ponteiros para o jogo anterior e para o proximo jogo.	*/
typedef struct node_jogos {
	Jogo *jogo;
	struct node_jogos *next, *prev;
} Nd_Jg;

 
/*	Estrutura "Lst_Jgs" (lista duplamente ligada):
		- Ponteiros para o primeiro e ultimo jogo
		da lista de jogos. */
typedef struct {
	struct node_jogos *head, *last;
} Lst_Jgs;


/*	Estrutura "Hsh_Jg" (Jogo em lista de Hash Table):
		- Ponteiro para um node de jogo numa lista ligada;
		- Ponteiros para o proximo jogo e o jogo anterior de igual
		indice numa tabela de dispercao. */
typedef struct hash_jogo {
	Nd_Jg *node_j;
	struct hash_jogo *next, *prev;
} Hsh_Jg;


/*	!Estrutura "Hsh_Lst_Jgs" (Lista de Jogos em Hash Table):
		- Ponteiro para o primeiro e ultimo jogo da lista
		de jogos numa hash table. 
typedef struct {
	struct hash_jogo *head, *last;
} Hsh_Lst_Jgs;
*/


int hash(char *nome, int M);
Equipa* encontra_equipa(char *nome, Hsh_Eq **tabela);
Equipa* encontra_equipa_hash(char *nome, Hsh_Eq *indice);
Jogo* encontra_jogo(char *nome, Hsh_Jg **tabela);
Nd_Jg* encontra_jogo_node(char *nome, Hsh_Jg *indice);
Hsh_Jg* encontra_jogo_hash(char *nome, Hsh_Jg *indice);

void free_jogo(Jogo *j);
void free_equipa(Equipa *e);
void free_Nd_Eq(Nd_Eq *node_e);
void free_Nd_Jg(Nd_Jg *node_j);


Equipa* criar_equipa(char *nome_eq);
Lst_Eqs* criar_lst_equipas();
Hsh_Eq** criar_tabela_eq(int M);
Nd_Eq* push_equipa_node(Equipa *eq, Lst_Eqs *l);
void push_equipa_hash(Nd_Eq *node, Hsh_Eq **tabela);

Jogo* criar_jogo(char* nome, char* e1, char* e2, int s1, int s2);
Lst_Jgs* criar_lst_jogos();
Hsh_Jg** criar_tabela_jogos(int M);
Nd_Jg* push_jogo_node(Jogo *j, Lst_Jgs *l);
void push_jogo_hash(Nd_Jg *node, Hsh_Jg **tabela_jg);

int vencedor(Jogo *j);
void alterar_vitorias(char operacao, char* nome_eq, Hsh_Eq **tabela);

void print_lst_eq(Lst_Eqs *l);
void print_lst_jg(Lst_Jgs *l);
void print_hash_eq(Hsh_Eq **tabela, int i);
void print_hash_jg(Hsh_Jg **tabela, int i);

void NovaEquipa_aux(Hsh_Eq **tabela_eq, Lst_Eqs *lst_eqs, char *nome);
void A_NovaEquipa(int *NL, Hsh_Eq **tabela_eq, Lst_Eqs *lst_eqs);

void NovoJogo_aux(char *nome_j, char *nome_e1, char *nome_e2, int s1, int s2, Hsh_Eq **tabela_e, Hsh_Jg **tabela_j, Lst_Jgs *lst_j);
void a_NovoJogo(int *NL, Hsh_Eq **tabela_e, Hsh_Jg **tabela_j, Lst_Jgs *lst_j);

void l_JogosPorData(int *NL, Lst_Jgs *l);
void p_ProcuraJogo(int *NL, Hsh_Jg **tabela_j);
void P_ProcuraEquipa(int *NL, Hsh_Eq **tabela_eq);



/*	FUNCOES DE PROCURA */


/* hash:
	- Devolve o indice h de uma estrutura numa tabela de dispersao
	de tamanho M, de acordo com o seu nome. */
int hash(char *nome, int M) {
	int h, a = HASH_RANDOM_1, b = HASH_RANDOM_2;

	for (h = 0; *nome != '\0'; nome++, a = a*b % (M-1))
		h = (a*h + *nome) % M;

	return h;
}


/*	PROCURA - EQUIPAS */


/*	encontra_equipa:
		Encontra o ponteiro para a equipa de nome "nome" 
	na tabela de dispersao "tabela" (devolve NULL se nao existir). */
Equipa* encontra_equipa(char *nome, Hsh_Eq **tabela) {
	int i = hash(nome, HASH_PRIMO);

	return encontra_equipa_hash(nome, tabela[i]);
}


/*	encontra_equipa_hash:
		Encontra a equipa de nome "nome" na lista da tabela de
	dispersao de indice "indice". */
Equipa* encontra_equipa_hash(char *nome, Hsh_Eq *indice){
	Hsh_Eq *aux;

	for (aux = indice; aux != NULL; aux = aux->next)
		if (strcmp(aux->node_e->equipa->nome, nome) == 0)
			return aux->node_e->equipa;

	return NULL;
}


/*	PROCURA - JOGOS */


/*	encontra_jogo:
		Encontra o ponteiro para o jogo de nome "nome" 
	na tabela de dispersao "tabela" (devolve NULL se nao existir). */
Jogo* encontra_jogo(char *nome, Hsh_Jg **tabela) {
	int i = hash(nome, HASH_PRIMO);
	Nd_Jg *node_j;

	node_j = encontra_jogo_node(nome, tabela[i]);

	if (node_j != NULL)
		return node_j->jogo;
	
	return NULL;
}

Nd_Jg* encontra_jogo_node(char *nome, Hsh_Jg *indice) {
	Hsh_Jg *aux;

	aux = encontra_jogo_hash(nome, indice);

	if (aux != NULL)
		return aux->node_j;

	return NULL;
}

Hsh_Jg* encontra_jogo_hash(char *nome, Hsh_Jg *indice) {
	Hsh_Jg *aux;
	
	for (aux = indice; aux != NULL; aux = aux->next)
		if (strcmp(aux->node_j->jogo->nome, nome) == 0)
			return aux;

	return NULL;
}



/*	FUNCOES FREE */

void free_jogo(Jogo *j) {
	free(j->nome);
	free(j->equipa1);
	free(j->equipa2);
	free(j);
	return;
}

void free_equipa(Equipa *e) {
	free(e->nome);
	free(e);
	return;
}

void free_Nd_Eq(Nd_Eq *node_e) {
	free_equipa(node_e->equipa);
	free(node_e);
	return;
}

void free_Nd_Jg(Nd_Jg *node_j) {
	free_jogo(node_j->jogo);
	free(node_j);
	return;
}


/*	FUNCOES DE CRIACAO E ADICAO */


/*	criar_equipa:
		Devolve o ponteiro para uma equipa de nome "nome_eq",
	inicializada a 0 vitorias. */
Equipa* criar_equipa(char *nome_eq) {
	Equipa *eq = can_fail_malloc(sizeof(Equipa));

	eq->nome = can_fail_malloc((strlen(nome_eq) + 1) * sizeof(char));
	strcpy(eq->nome, nome_eq);
	eq->vitorias = 0;

	return eq;
}

/*	criar_lst_equipas:
		Devolve o ponteiro para uma estrura Lst_Eqs, vazia. */
Lst_Eqs* criar_lst_equipas() {
	Lst_Eqs* l = can_fail_malloc(sizeof(Lst_Eqs));
	l->head = l->last = NULL;
	return l;
}

/*	criar_tabela_eq:
		Devolve uma tabela de dispersao de ponteiros
	para equipas, vazia, de tamanho M. */
Hsh_Eq** criar_tabela_eq(int M) {
	Hsh_Eq **tabela = can_fail_malloc(M * sizeof(Hsh_Eq*));
	int i;

	for (i = 0; i < M; i++)
		tabela[i] = NULL;

	return tabela;
}

/* 	push_equipa_node:
		Devolve o ponteiro para um node-equipa "new" numa lista
	ligada, que sera a nova "head" da mesma. */
Nd_Eq* push_equipa_node(Equipa *eq, Lst_Eqs *l) {
	Nd_Eq *new = can_fail_malloc(sizeof(Nd_Eq));

	new->equipa = eq;
	new->prev = l->last;
	new->next = NULL;

	if (l->last)
		l->last->next = new;
	else
		l->head = new;

	l->last = new;
	return new;
}


/*	push_equipa_hash:
		Adiciona uma equipa a uma lista ligada
	de uma tabela de dispersao. */
void push_equipa_hash(Nd_Eq *node, Hsh_Eq **tabela) {
	Hsh_Eq *hash_e = can_fail_malloc(sizeof(Hsh_Eq));
	int i = hash(node->equipa->nome, HASH_PRIMO);

	hash_e->node_e = node;
	hash_e->next = tabela[i];
	hash_e->prev = NULL;

	tabela[i] = hash_e;

	return;
}



Jogo* criar_jogo(char* nome, char* e1, char* e2, int s1, int s2) {
	Jogo* j = can_fail_malloc(sizeof(Jogo));

	j->nome = can_fail_malloc((strlen(nome) + 1) * sizeof(char));
	j->equipa1 = can_fail_malloc((strlen(e1) +1) * sizeof(char));
	j->equipa2 = can_fail_malloc((strlen(e2) + 1) * sizeof(char));

	strcpy(j->nome, nome);
	strcpy(j->equipa1, e1);
	strcpy(j->equipa2, e2); 
	j->score1 = s1;
	j->score2 = s2;

	return j;
}


/*	criar_lst_jogos:
		Devolve o ponteiro para uma estrura Lst_Jgs, vazia. */
Lst_Jgs* criar_lst_jogos() {
	Lst_Jgs *l = can_fail_malloc(sizeof(Lst_Jgs));
	l->head = l->last = NULL;
	return l;
}


/*	criar_tabela_jogos:
		Devolve uma tabela de dispersao de ponteiros
	para jogos, vazia, de tamanho M.*/
Hsh_Jg** criar_tabela_jogos(int M) {
	Hsh_Jg **tabela = can_fail_malloc(M * sizeof(Hsh_Jg*));
	int i;

	for (i = 0; i < M; i++)
		tabela[i] = NULL;

	return tabela;
}



/*	push_jogo_node:
		Adiciona o jogo "j" a lista de jogos "l", na ultima
	posicao da lista, devolvendo o node correspondente. */
Nd_Jg* push_jogo_node(Jogo *j, Lst_Jgs *l) {
	Nd_Jg *new = can_fail_malloc(sizeof(Nd_Jg));

	new->jogo = j;
	new->prev = l->last;
	new->next = NULL;

	if (l->last)
		l->last->next = new;
	else
		l->head = new;

	l->last = new;

	return new;
}


void push_jogo_hash(Nd_Jg *node, Hsh_Jg **tabela_jg) {
	Hsh_Jg *hash_jg = can_fail_malloc(sizeof(Hsh_Jg));
	int i = hash(node->jogo->nome, HASH_PRIMO);

	hash_jg->node_j = node;
	hash_jg->prev = NULL;
	hash_jg->next = tabela_jg[i];
	tabela_jg[i] = hash_jg;

	return;
}

/*	CONSEQUENCIAS DE ADICAO , REMOCAO, E ALTERACAO DE JOGOS*/

int vencedor(Jogo *j) {

	if (j->score1 > j->score2)
		return EQUIPA1;
	else if (j->score2 > j->score1)
		return EQUIPA2;
	else
		return EMPATE;
}

void alterar_vitorias(char operacao, char* nome_eq, Hsh_Eq **tabela) {
	Equipa *e = encontra_equipa(nome_eq, tabela);

	if (operacao == MAIS)
		e->vitorias++;

	else if (operacao == MENOS)
		e->vitorias--;

	return;
}


/* FUNCOES PRINCIPAIS */

void NovaEquipa_aux(Hsh_Eq **tabela_eq, Lst_Eqs *lst_eqs, char *nome) {
	Equipa *e;
	Nd_Eq *node_e;

	e = criar_equipa(nome);
	node_e = push_equipa_node(e, lst_eqs);
	push_equipa_hash(node_e, tabela_eq);

	return;
}

/* Adiciona uma nova equipa ao sistema */
void A_NovaEquipa(int *NL, Hsh_Eq **tabela_eq, Lst_Eqs *lst_eqs) {
	char *nome_eq = can_fail_malloc((MAX_CHAR+1) * sizeof(char));

	scanf(" %[^:\n]", nome_eq);

	if (encontra_equipa(nome_eq, tabela_eq) != NULL)
		printf("%d Equipa existente.\n", *NL);
	else
		NovaEquipa_aux(tabela_eq, lst_eqs, nome_eq);

	free(nome_eq);
	return;
}


 
void NovoJogo_aux(char *nome_j, char *nome_e1, char *nome_e2, int s1, int s2, Hsh_Eq **tabela_e, Hsh_Jg **tabela_j, Lst_Jgs *lst_j) {
	Jogo *j;
	Nd_Jg *node_j;
	int venceu;

	j = criar_jogo(nome_j, nome_e1, nome_e2, s1, s2);
	node_j = push_jogo_node(j, lst_j);
	push_jogo_hash(node_j, tabela_j);

	venceu = vencedor(j);
	if (venceu == EQUIPA1)
		alterar_vitorias(MAIS, nome_e1, tabela_e);
	else if (venceu == EQUIPA2)
		alterar_vitorias(MAIS, nome_e2, tabela_e);

	return;

}

/* Adiciona um novo jogo ao sistema */
void a_NovoJogo(int *NL, Hsh_Eq **tabela_e, Hsh_Jg **tabela_j, Lst_Jgs *lst_j){
	char *nome_j = can_fail_malloc((MAX_CHAR+1) * sizeof(char));
	char *nome_e1 = can_fail_malloc((MAX_CHAR+1) * sizeof(char));	
	char *nome_e2 = can_fail_malloc((MAX_CHAR+1) * sizeof(char));
	int s1, s2;

	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",
		nome_j,
		nome_e1,
		nome_e2,
		&s1,
		&s2);

	if (encontra_jogo(nome_j, tabela_j) != NULL)
		printf("%d Jogo existente.\n", *NL);
	else if ((encontra_equipa(nome_e1, tabela_e) == NULL) || (encontra_equipa(nome_e2, tabela_e) == NULL))
		printf("%d Equipa inexistente.\n", *NL);
	else
	{
		NovoJogo_aux(nome_j, nome_e1, nome_e2, s1, s2, tabela_e, tabela_j, lst_j);
	}

	free(nome_j);
	free(nome_e1);
	free(nome_e2);
	return;
}

/* Lista os jogos existentes cronologicamente */
void l_JogosPorData(int *NL, Lst_Jgs *l) {
	Nd_Jg *aux;

	for (aux = l->head; aux != NULL; aux = aux->next)
		printf("%d %s %s %s %d %d\n",
			*NL,
			aux->jogo->nome,
			aux->jogo->equipa1,
			aux->jogo->equipa2,
			aux->jogo->score1,
			aux->jogo->score2);

	return;
}

/* Procura um jogo */
void p_ProcuraJogo(int *NL, Hsh_Jg **tabela_j) {
	Jogo *j;
	char *nome = can_fail_malloc((MAX_CHAR+1) *sizeof(char));

	scanf(" %[^:\n]", nome);
	j = encontra_jogo(nome, tabela_j);

	if (j == NULL)
		printf("%d Jogo inexistente.\n", *NL);
	else
		printf("%d %s %s %s %d %d\n",
			*NL,
			j->nome,
			j->equipa1,
			j->equipa2,
			j->score1,
			j->score2);

	free(nome);
	return;
}

/* Procura uma equipa */
void P_ProcuraEquipa(int *NL, Hsh_Eq **tabela_eq) {
	Equipa *e;
	char *nome = can_fail_malloc((MAX_CHAR+1) * sizeof(char));

	scanf(" %[^:\n]", nome);
	e = encontra_equipa(nome, tabela_eq);

	if (e == NULL)
		printf("%d Equipa inexistente.\n", *NL);
	else
		printf("%d %s %d\n",
			*NL,
			e->nome,
			e->vitorias);

	return;

	free(nome);
}


int nr_vitorias(Nd_Eq *nd_e) {
	return nd_e->equipa->vitorias;
}

/* Altera o resultado de um jogo */
void s_AlteraScore(int *NL, Hsh_Jg **tabela_j, Hsh_Eq **tabela_e) {
	char *nome = can_fail_malloc((MAX_CHAR+1) * sizeof(char));
	Jogo *j;
	int s1, s2;
	int venceu_antes, venceu_agora;

	scanf(" %[^:\n]:%d:%d",
		nome,
		&s1,
		&s2);

	j = encontra_jogo(nome, tabela_j);

	if (j == NULL)
		printf("%d Jogo inexistente.\n", *NL);
	else
	{
		venceu_antes = vencedor(j);

		j->score1 = s1;
		j->score2 = s2;
		venceu_agora = vencedor(j);

		if (venceu_antes == EMPATE)
		{
			if (venceu_agora == EQUIPA1)
				alterar_vitorias(MAIS, j->equipa1, tabela_e);
			else if (venceu_agora == EQUIPA2)
				alterar_vitorias(MAIS, j->equipa2, tabela_e);
		}

		else if (venceu_antes == EQUIPA1)
		{
			if (venceu_agora == EQUIPA2)
			{
				alterar_vitorias(MENOS, j->equipa1, tabela_e);
				alterar_vitorias(MAIS, j->equipa2, tabela_e);
			}
			else if (venceu_agora == EMPATE)
				alterar_vitorias(MENOS, j->equipa1, tabela_e);
		}

		else if (venceu_antes == EQUIPA2)
		{
			if (venceu_agora == EQUIPA1)
			{
				alterar_vitorias(MAIS, j->equipa1, tabela_e);
				alterar_vitorias(MENOS, j->equipa2, tabela_e);
			}
			else if (venceu_agora == EMPATE)
				alterar_vitorias(MENOS, j->equipa2, tabela_e);
		}
	}

	free(nome);
	return;
}

int peso_nome(char *nome) {
	int p, a = HASH_RANDOM_3;

	for (p = 0; *nome != '\0'; nome++)
		p = (a*p + *nome);

	return p;
}

int less(char *nome1, char *nome2) {
	return peso_nome(nome1) <= peso_nome(nome2);
}

void trocar(char *nome1, char *nome2) {
	char *aux;

	aux = nome1;
	nome1 = nome2;
	nome2 = aux;

	return;
}

int partition(char **lst, int l, int r) {
	int i = l-1;
	int j = r;

	char *nome_eq = lst[r];

	while (i < j)
	{
		while(less(lst[++i], nome_eq));

		while (less(nome_eq, lst[--j]))
			if (j == l)
				break;
		if (i < j)
			trocar(lst[i], lst[j]);


	}

	trocar(lst[i], lst[r]);
	return i;
}

/* Ordena uma lista de palavras por ordem alfabetica */
void quicksort(char **lst, int l, int r) {
	int i;

	if (r <= l) return;

	i = partition(lst, l, r);
	quicksort(lst, l, i-1);
	quicksort(lst, i+1, r); 
}


/* Lista as melhores equipas por ordem alfabetica */
void g_MelhoresEquipas(int *NL, Lst_Eqs *lst_e) {
	int size_tabela = 5, size_nome_eq;
	int nr_melhores_equipas = 0;
	int max_vitorias = 0;
	int i;
	Nd_Eq *aux;
	char *nome_eq = NULL;
	char **a_ordenar = can_fail_malloc(size_tabela * sizeof(char*));

	if (lst_e->head == NULL)
		return;

	for (aux = lst_e->head; aux != NULL; aux = aux->next)
	{
		if (nr_vitorias(aux) > max_vitorias)
		{
			max_vitorias = nr_vitorias(aux);
			nr_melhores_equipas = 0;
		}

		if (nr_vitorias(aux) == max_vitorias)
		{
			size_nome_eq = strlen(aux->equipa->nome);
			nome_eq = can_fail_malloc((size_nome_eq+1) * sizeof(char));
			strcpy(nome_eq, aux->equipa->nome);
			a_ordenar[nr_melhores_equipas] = nome_eq;

			nr_melhores_equipas++;
		}

		if (nr_melhores_equipas == size_tabela)
		{
			size_tabela = size_tabela * 2;
			a_ordenar = (char**) can_fail_realloc(a_ordenar, size_tabela * sizeof(char*));
		}
	}

	a_ordenar = (char**) can_fail_realloc(a_ordenar, nr_melhores_equipas * sizeof(char*));

	quicksort(a_ordenar, 0, nr_melhores_equipas-1);

	printf("%d Melhores %d\n", *NL, max_vitorias);
	
	for (i = 0; i < nr_melhores_equipas; i++)
		printf("%d * %s\n", *NL, a_ordenar[i]);

	return;
}

/* Apaga um jogo */
void r_ApagaJogo(int *NL, Hsh_Jg **tabela_j, Lst_Jgs *lst_j, Hsh_Eq **tabela_e) {
	int i;
	int venceu_antes = 0;
	char *nome = can_fail_malloc((MAX_CHAR+1) * sizeof(char));
	Jogo *j = NULL;
	Nd_Jg *node_j = NULL;
	Hsh_Jg *hash_j = NULL;

	scanf(" %[^:\n]", nome);

	j = encontra_jogo(nome, tabela_j);

	if (j == NULL)
		printf("%d Jogo inexistente.\n", *NL);
	else
	{
		venceu_antes = vencedor(j);

		if (venceu_antes == EQUIPA1)
			alterar_vitorias(MENOS, j->equipa1, tabela_e);
		else if (venceu_antes == EQUIPA2)
			alterar_vitorias(MENOS, j->equipa2, tabela_e);

		i = hash(nome, HASH_PRIMO);
		hash_j = encontra_jogo_hash(nome, tabela_j[i]);
		node_j = hash_j->node_j;
		

		if (node_j->prev == NULL)
			lst_j->head = node_j->next;
		else
			node_j->prev->next = node_j->next;

		if (node_j->next == NULL)
			lst_j->last = node_j->prev;
		else
			node_j->next->prev = node_j->prev;

		free_Nd_Jg(node_j);

		if (hash_j->prev == NULL)
			tabela_j[i] = hash_j->next;
		else
			hash_j->prev->next = hash_j->next;

		if (hash_j->next != NULL)
			hash_j->next->prev = hash_j->prev;

		free(hash_j);
	}	

	return;

}

int main() {
	char comando;
	int *NL;
	int linha = 1;

	Hsh_Jg **tabela_j = criar_tabela_jogos(HASH_PRIMO);
	Hsh_Eq **tabela_e = criar_tabela_eq(HASH_PRIMO);
	Lst_Jgs *lst_jgs = criar_lst_jogos();
	Lst_Eqs *lst_eqs = criar_lst_equipas();

	NL = &linha;

	scanf("%c", &comando);

	while (comando != 'x')
	{
		switch (comando)
		{
			case 'a':
				a_NovoJogo(NL, tabela_e, tabela_j, lst_jgs);
				break;

			case 'A':
				A_NovaEquipa(NL, tabela_e, lst_eqs);
				break;

			case 'l':
				l_JogosPorData(NL, lst_jgs);
				break;

			case 'p':
				p_ProcuraJogo(NL, tabela_j);
				break;

			case 'P':
				P_ProcuraEquipa(NL, tabela_e);
				break;

			case 'r':
				r_ApagaJogo(NL, tabela_j, lst_jgs ,tabela_e);
				break;

			case 's':
				s_AlteraScore(NL, tabela_j, tabela_e);
				break;

			case 'g':
				g_MelhoresEquipas(NL, lst_eqs);
				break;
		}
		scanf("\n%c", &comando);
		(*NL)++;
	}

	return 0;
}