#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "declaracoes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Inicializa a lista duplamente ligada*/
lista* cria_lista(){

	lista * l = can_fail_malloc(sizeof(lista));

	l->head = l->last = NULL;

	return l;
}

/*Adiciona um novo jogo a hashtable dos jogos*/
void adiciona_novo_jogo(lista * ls, link_j *heads_j, link_e *heads_e, int nl){

	char buffer_nome[MAXSTR],buffer_equipa1[MAXSTR],buffer_equipa2[MAXSTR];
	link_e equipa1;
	link_e equipa2;
	int p1, p2, i;

	getchar();/*le o espaco em branco entre o comando dado e o resto do standard input */
	scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d",buffer_nome,buffer_equipa1,buffer_equipa2, &p1, &p2);
	getchar();/*Le o \n final */

	/*Verifica o jogo existe*/
	if(!(pesquisa_jogo(heads_j, buffer_nome))){

		equipa1 = pesquisa_equipa(heads_e, buffer_equipa1);
		equipa2 = pesquisa_equipa(heads_e, buffer_equipa2);

		/*Verifica se a equipa existe*/
		if(equipa1 && equipa2){

			i = hash(buffer_nome, HASHTABLESIZE_J);
			heads_j[i] = insere_jogo_inicio(ls, heads_j[i], buffer_nome, buffer_equipa1, buffer_equipa2, p1, p2);

			if(maior(p1, p2)){
				(equipa1->e.vitorias)++;
			}
			else if (menor(p1, p2)){
				(equipa2->e.vitorias)++;
			}
		}
		else
			printf("%d Equipa inexistente.\n", nl);
	}
	else
		printf("%d Jogo existente.\n", nl);
}

/*Adiciona uma equipa a hashtable das equipas*/
void adiciona_nova_equipa(link_e *heads_e , int *contador_equipas, int nl){

	char buffer_nome[MAXSTR];
	int i;

	getchar();
	scanf("%[^:\n]",buffer_nome);
	getchar();

	if(!(pesquisa_equipa(heads_e, buffer_nome))){

		i = hash(buffer_nome, HASHTABLESIZE_E);
		heads_e[i] = insere_equipa_inicio(heads_e[i], buffer_nome);
		*(contador_equipas) = *(contador_equipas) + 1;
	}
	else
		printf("%d Equipa existente.\n", nl);
}

/*Lista todos os jogos por ordem cronologica, percorrendo a lista duplamente ligada*/
void lista_jogos(lista * ls, int nl){

	node_j * n;

	for(n = ls->head; n; n = n->next)
	printf("%d %s %s %s %d %d\n",nl, n->j->nome, n->j->equipa1, n->j->equipa2, n->j->p1, n->j->p2);
	getchar();
}

/*procura um jogo dado no standard input, caso exista*/
void proucura_jogo(link_j *heads_j, int nl){

	char buffer_nome[MAXSTR];
	link_j t;

	getchar();
	scanf("%[^:\n]",buffer_nome);
	getchar();

	t = pesquisa_jogo(heads_j, buffer_nome);

	if(t)

		printf("%d %s %s %s %d %d\n", nl, buffer_nome, t->j->equipa1, t->j->equipa2,t->j->p1, t->j->p2);
	else
		printf("%d Jogo inexistente.\n", nl);
}

/*Procura uma equipa dado o nome pelo standard input*/
void procura_equipa(link_e *heads_e, int nl){

	char buffer_nome[MAXSTR];
	link_e equipa;

	getchar();
	scanf("%[^:\n]",buffer_nome);
	getchar();

	equipa = pesquisa_equipa(heads_e, buffer_nome);

	if(equipa){

		printf("%d %s %d\n", nl, buffer_nome, equipa->e.vitorias);
	}
	else
		printf("%d Equipa inexistente.\n", nl);
}

/*Apaga um jogo da hashtable e da lista de jogos*/
void apaga_jogo(link_j* heads_j, link_e *heads_e, lista * ls, int nl){

	char buffer_nome[MAXSTR];
	link_j t;
	link_e equipa;
	int i;
	node_j * n;

	getchar();
	scanf("%[^:\n]", buffer_nome);
	getchar();

	t = pesquisa_jogo(heads_j, buffer_nome);

	if(t){

		if(maior(t->j->p1, t->j->p2)){
			equipa = pesquisa_equipa(heads_e, t->j->equipa1);
			(equipa->e.vitorias)--;
		}
		else if(menor(t->j->p1, t->j->p2)){
			equipa = pesquisa_equipa(heads_e, t->j->equipa2);
			(equipa->e.vitorias)--;
		}

		for(n = ls->head; n; n = n->next)
				if(compara(n->j->nome, buffer_nome) == 0){
					remove_node(ls, n);
					break;
				}

		i = hash(buffer_nome, HASHTABLESIZE_J);

		heads_j[i] = apaga_node_jogo(heads_j[i], buffer_nome);
	}
	else
		printf("%d Jogo inexistente.\n", nl);
}

/*Altera o score de um jogo*/
void altera_score(link_j* heads_j, link_e *heads_e, int nl){

	char buffer_nome[MAXSTR];
	int p1, p2;
	link_e equipa1;
	link_e equipa2;
	link_j t;

	getchar();
	scanf("%[^:\n]:%d:%d",buffer_nome, &p1, &p2);
	getchar();

	t = pesquisa_jogo(heads_j, buffer_nome);

	if(t){

		equipa1 = pesquisa_equipa(heads_e, t->j->equipa1);
		equipa2 = pesquisa_equipa(heads_e, t->j->equipa2);

		if(maior(t->j->p1, t->j->p2) && maior(p2, p1)){

			(equipa1->e.vitorias)--;
			(equipa2->e.vitorias)++;
		}
		else if(menor(t->j->p1, t->j->p2) && menor(p2, p1)){
			
			(equipa1->e.vitorias)++;
			(equipa2->e.vitorias)--;
		}
		else if(p1 == p2){

			if(maior(t->j->p1, t->j->p2))
				(equipa1->e.vitorias)--;
			else if(menor(t->j->p1, t->j->p2))
				(equipa2->e.vitorias)--;

		}
		else if(t->j->p1 == t->j->p2){

			if(menor(p1, p2))
				(equipa2->e.vitorias)++;
			else if(maior(p1, p2))
				(equipa1->e.vitorias)++;
		}
		
		t->j->p1 = p1;
		t->j->p2 = p2;
	}
	else
		printf("%d Jogo inexistente.\n", nl);
}

/*Lista as equipas com o maior numero de vitorias por ordem alfabetica, usando o mergesort e passando para um vetor essas equipas.
E usada uma lista simplesmente ligada onde sao colocados os nomes das equipas com mais vitorias*/
void equipa_vitorias(link_e *heads_e, int *contador_equipas, int nl){

	int i, max = 0, contador, conta_equipas = 0;
	link_e equipa;
	char* arr[TAM];

	getchar();

/*Ciclo realizado para encontrar o numero de vitorias*/
	for(i = 0; i < HASHTABLESIZE_E; i++){

		for (equipa = heads_e[i]; equipa; equipa = equipa->next){

			contador = equipa->e.vitorias;

			if(contador > max)
				max = contador;
		}
	}
	for(i = 0; i < HASHTABLESIZE_E; i++){

		for (equipa = heads_e[i]; equipa; equipa = equipa->next){
		 
			if(equipa->e.vitorias == max){

				arr[conta_equipas] = equipa->e.nome;
				conta_equipas++;
			}
		}
	}
	qsort(arr, conta_equipas, sizeof(char*), comparador);

	if(*(contador_equipas))/*Se existirem equipas e realizado o print da frase pretendida*/

		printf("%d Melhores %d\n", nl, max);

    for(i = 0;i < conta_equipas; i++)

    	printf("%d * %s\n",nl, arr[i]);

}

/*Funcao responsavel por ler tudo o que nao e um comando valido*/
void le_lixo(){

	char buffer_nome[MAXSTR];

	scanf("%[^:\n]",buffer_nome);
	getchar();

}

/*liberta a memoria alocada pelos jogos e os seus constituintes*/
void limpa_ht_jogos(link_j *heads_j){

	int i;
	link_j limpa_aux;

	for(i = 0; i < HASHTABLESIZE_J; i++){ 

		while(heads_j[i]){

			limpa_aux = heads_j[i];
			heads_j[i] = heads_j[i]->next;

			apaga(limpa_aux->j->nome);
			apaga(limpa_aux->j->equipa1);
			apaga(limpa_aux->j->equipa2);
			apaga(limpa_aux->j);
			apaga(limpa_aux);
		}
	}
	apaga(heads_j);
}

/*liberta a memoria alocada pelas e todas as suas componentes*/
void limpa_ht_equipas(link_e *heads_e){

	int i;
	link_e liberta_aux;

	for(i = 0; i < HASHTABLESIZE_E; i++){

		while(heads_e[i]){

			liberta_aux = heads_e[i];
			heads_e[i] = heads_e[i]->next;

			apaga(liberta_aux->e.nome);
			apaga(liberta_aux);
		}
	}
	apaga(heads_e);
}

/*Limpa a lista duplamente ligada*/
void limpa_lista_ligada(lista * l){

	while(l->head){
		node_j * aux = l->head->next;
		apaga(l->head);
		l->head = aux;
	}
	apaga(l);
}