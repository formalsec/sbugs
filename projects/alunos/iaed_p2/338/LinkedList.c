#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Hash.h"
#include "structs.h"
#include "LinkedList.h"

/*Esta funcao adiciona um nome a uma Linked List*/
node append(char game[],node Head){
	struct nodes *temp;
	struct nodes *p;
	temp = (struct nodes*)can_fail_malloc(sizeof(struct nodes));
	temp->link = NULL;
	temp->nome_jogo = can_fail_malloc(sizeof(char)*(strlen(game)+1));
	strcpy(temp->nome_jogo,game);
	if(Head == NULL){ /*Lista esta vazia*/
		return temp;
	}
	else{
		p = Head;
		while(p->link != NULL){
			p = p->link;
		}
		p->link = temp;
	}
	return Head;
}

/*Esta funcao faz print ao conteudo da lista dos jogos*/
void display(int contalinhas,int tblsz_jogo,node Head, jogo*st){
	struct nodes *temp;
	struct jogos *display_jogo;
	temp = Head;
	if(temp == NULL){
		return;
	}
	else{
		while(temp != NULL){
			display_jogo = search_jogo(temp->nome_jogo, tblsz_jogo,st);
			printf("%d %s %s %s %d %d\n", contalinhas, display_jogo->nome, display_jogo->equipa1,
			 display_jogo->equipa2, display_jogo->score1, display_jogo->score2);
			temp = temp->link;
		}
	}
}

/*Esta funcao faz print ao conteudo da lista das equipas*/
void display2(int contalinhas,int tblsz_jogo,node Head, equipa *eq){
	struct nodes *temp;
	struct equipas *display_jogo;
	temp = Head;
	if(temp == NULL){
		return;
	}
	else{
		while(temp != NULL){
			display_jogo = search_equipa(temp->nome_jogo, tblsz_jogo,eq);
			printf("%d %s %d\n", contalinhas, display_jogo->nome_equipa, display_jogo->vitorias);
			temp = temp->link;
		}
	}
}

/*Esta funcao um par com o numero maximo de vitorias
 e com a quantidade de equipas com esse numero de vitorias*/
tuplio get_max_vit(node Head,int tblsz, equipa *eq, tuplio tuplo){
	int m,conta_eq_c_max_vit = 0,max_vit = 0;
	struct nodes *temp;
	temp = Head;
	tuplo->max_vitorias = 0;
	tuplo->conta_eq_c_max_vit = 0;
	if(temp == NULL)
		return tuplo;
	else{
		while(temp != NULL){
			m = get_vitorias(temp->nome_jogo,tblsz,eq);
			if(max_vit < m){
				max_vit = m;
				conta_eq_c_max_vit = 1;
			}
			else{
				if(max_vit == m){
					conta_eq_c_max_vit += 1;
				}
			}
			temp = temp->link;

		}
		tuplo->max_vitorias = max_vit;
		tuplo->conta_eq_c_max_vit = conta_eq_c_max_vit;
		return tuplo;
	}
}

/*Esta funcao apaga um dado elemento de uma Linked List*/
node delete_node(char *nome, node Head){
	struct nodes *temp;
	struct nodes *p, *q;
		if (strcmp(nome,Head->nome_jogo) == 0){
			temp = Head;
			Head = temp->link;
			temp->link = NULL;
			free(temp->nome_jogo);
			free(temp);
		}
	else{
		q = Head;
		while(strcmp(q->nome_jogo,nome) != 0){
			p = q;
			q = q->link;
		}
		p->link = q->link;
		q->link = NULL;
		free(q->nome_jogo);
		free(q);
	}
	return Head;
}

/*Esta funcao obtem as equipas com o maximo de vitorias e guarda-as na variavel
equipa_c_vitorias*/
void obtem_equipas_com_max_vit(node Head, int max_vitorias, char**equipa_c_vitorias,int tblsz,
 equipa *eq){
	struct nodes *temp;
	int i, cont = 1;
	temp = Head;
	while(temp != NULL){
		if (get_vitorias(temp->nome_jogo, tblsz,eq) == max_vitorias){
			*equipa_c_vitorias = can_fail_malloc(sizeof(char)*(strlen(temp->nome_jogo)+1));
			strcpy((*equipa_c_vitorias),temp->nome_jogo);
			equipa_c_vitorias ++;
			cont++;
		}
		temp = temp->link;
	}
	/*Regressar na variavel para a primeira equipa*/
	for(i = 0; i < cont;i++){
		equipa_c_vitorias--;
	}
}