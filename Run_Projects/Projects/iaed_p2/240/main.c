#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"




/**********************/
/*                    */
/* inicio do programa */
/*                    */
/**********************/


int main(){
	char c;
	int NL = 0;
	node_htable_equipas ** hash_equipas = init_hash_equipas();
	node_htable_jogos ** hash_jogos = init_hash_jogos();
	lista_ligada_jogos * lista_ligada_j = init_lista_ligada_j();
	lista_ligada_equipas * lista_ligada_e = init_lista_ligada_e();

	while (1){
		switch (c = getchar()){
			case 'a':	/* cria um novo jogo */
				NL++;
				adiciona_jogo(NL, hash_jogos, &lista_ligada_j, hash_equipas);
				break;
			case 'A':	/* cria uma nova equipa */
				NL++;
				adiciona_equipa(NL, hash_equipas, &lista_ligada_e);
				break;
			case 'l':	/* lista todos os jogos */
				NL++;
				lista_jogos(NL, lista_ligada_j);
				break;
			case 'p':	/* procura um jogo atraves do seu nome */
				NL++;
				procura_jogo(NL, hash_jogos);
				break;
			case 'P':	/* procura uma equipa atraves do seu nome devolvendo o 
						numero de jogos ganhos*/
				NL++;
				procura_equipa(NL, hash_equipas);
				break;
			case 'r':	/* apaga um jogo do sistema */
				NL++;
				apaga_jogo(NL, hash_jogos, &lista_ligada_j);
				break;
			case 's':	/* altera o score de um jogo */
				NL++;
				altera_score(NL, hash_jogos);
				break;
			case 'g':	/* lista as equipas com mais vitorias */
				NL++;
				lista_melhores_equipas(NL, &lista_ligada_e);
				break;
			case 'x':	/* Termina o programa */
				destroi_equipas(hash_equipas);
				destroi_jogos(hash_jogos);
				return 0;
				break;
		}
	}
}



/* adiciona o jogo a todas as estruturas necessarias usando funcoes auxiliares */

void adiciona_jogo(int NL, node_htable_jogos **entrada_hash_jogos,
lista_ligada_jogos ** lista_ligada, node_htable_equipas **entrada_hash_equipas){

	char equipa1[CHARMAX], equipa2[CHARMAX], nome_jogo[CHARMAX];
	int score1, score2;
	jogo *jogo_new;
	long hash_index;

	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome_jogo, equipa1, equipa2, &score1, &score2);

	if (procura_jogo_aux(nome_jogo, entrada_hash_jogos)){
		printf("%d Jogo existente.\n", NL);
		return;
	}

	if (!(procura_equipa_aux(equipa1, entrada_hash_equipas)) || !(procura_equipa_aux(equipa2, 
	entrada_hash_equipas))){
		printf("%d Equipa inexistente.\n", NL);
		return;
	}

	hash_index = hash(nome_jogo);

	jogo_new = cria_jogo(nome_jogo, equipa1, equipa2, score1, score2, entrada_hash_equipas);
	entrada_hash_jogos[hash_index] = adiciona_ao_node_jogos(entrada_hash_jogos[hash_index],
	jogo_new);

	lista_ligada = adiciona_a_lista_ligada_j(jogo_new, lista_ligada);
}



/* Adiciona a equipa a todas as estruturas necessarias */

void adiciona_equipa(int NL, node_htable_equipas **entrada_hash, 
lista_ligada_equipas ** lista_ligada){
	char nome_equipa[CHARMAX];
	long hash_index;
	equipa *equipa;

	scanf(" %[^\n]", nome_equipa);

	if (procura_equipa_aux(nome_equipa, entrada_hash))
	{
		printf("%d Equipa existente.\n", NL);
		return;
	}

	hash_index = hash(nome_equipa);
	

	equipa = cria_equipa(nome_equipa);
	entrada_hash[hash_index] = adiciona_a_lista_equipas(entrada_hash[hash_index], equipa);
	lista_ligada = adiciona_a_lista_ligada_e(equipa, lista_ligada);
}



/* lista os jogos pela ordem que foram introduzidos */

void lista_jogos(int NL, lista_ligada_jogos * lista_ligada){

	if(lista_ligada == NULL)
		return;

	lista_jogos(NL, lista_ligada->next);
	printf("%d %s %s %s %d %d\n", NL, lista_ligada->jogo->nome_jogo, 
		lista_ligada->jogo->equipa1->nome_equipa,
		lista_ligada->jogo->equipa2->nome_equipa, lista_ligada->jogo->score1, 
		lista_ligada->jogo->score2);
}



/* procura um jogo */

void procura_jogo(int NL, node_htable_jogos **entrada_hash){
	jogo * pt_jogo;
	char nome_jogo[CHARMAX];
	scanf(" %[^\n]", nome_jogo);

	pt_jogo = procura_jogo_aux(nome_jogo, entrada_hash);
	if(pt_jogo)
		printf("%d %s %s %s %d %d\n", NL, pt_jogo->nome_jogo, pt_jogo->equipa1->nome_equipa,
			pt_jogo->equipa2->nome_equipa, pt_jogo->score1,
			 pt_jogo->score2);
	else
		printf("%d Jogo inexistente.\n", NL);

}



/* procura uma equipa */

void procura_equipa(int NL, node_htable_equipas **entrada_hash){
	equipa *pt_equipa;
	char nome_equipa[CHARMAX];
	scanf(" %[^\n]", nome_equipa);

	pt_equipa = procura_equipa_aux(nome_equipa, entrada_hash);
	if(pt_equipa)
		printf("%d %s %d\n", NL, pt_equipa->nome_equipa, pt_equipa->jogos_ganhos);
	else
		printf("%d Equipa inexistente.\n", NL);
}



/* apaga um jogo de todas as esntruturas */

void apaga_jogo(int NL, node_htable_jogos ** entrada_hash_jogos, 
lista_ligada_jogos ** lista_ligada){
	char nome_jogo[CHARMAX];
	jogo * pt_jogo;
	scanf(" %[^\n]", nome_jogo);

	if (!(pt_jogo = procura_jogo_aux(nome_jogo, entrada_hash_jogos))){
		printf("%d Jogo inexistente.\n", NL);
		return;
	}
	if (pt_jogo->score1 > pt_jogo->score2){
		pt_jogo->equipa1->jogos_ganhos--;
	}
	if (pt_jogo->score1 < pt_jogo->score2){
		pt_jogo->equipa2->jogos_ganhos--;
	}

	apaga_jogo_lista_ligada(nome_jogo, lista_ligada);
	apaga_jogo_hashtable(nome_jogo, entrada_hash_jogos);

}



/* altera a pontuacao de um jogo */

void altera_score(int NL, node_htable_jogos ** entrada_hash_jogos){
	char nome_jogo[CHARMAX];
	int score1, score2, score_antes1, score_antes2;
	jogo * pt_jogo;

	scanf(" %[^:]:%d:%d", nome_jogo, &score1, &score2);
	if (!(procura_jogo_aux(nome_jogo, entrada_hash_jogos))){
		printf("%d Jogo inexistente.\n", NL);
		return;
	}
	pt_jogo = procura_jogo_aux(nome_jogo, entrada_hash_jogos);
	score_antes1 = pt_jogo->score1;
	score_antes2 = pt_jogo->score2;
	if(score_antes1 > score_antes2 && score1 < score2){
		pt_jogo->equipa1->jogos_ganhos--;
		pt_jogo->equipa2->jogos_ganhos++;
	}
	if(score_antes1 < score_antes2 && score1 > score2){
		pt_jogo->equipa1->jogos_ganhos++;
		pt_jogo->equipa2->jogos_ganhos--;
	}
	if(score_antes1 == score_antes2 && score1 < score2){
		pt_jogo->equipa2->jogos_ganhos++;
	}
	if(score_antes1 == score_antes2 && score1 > score2){
		pt_jogo->equipa1->jogos_ganhos++;
	}
	if(score_antes1 < score_antes2 && score1 == score2){
		pt_jogo->equipa2->jogos_ganhos--;
	}
	if(score_antes1 > score_antes2 && score1 == score2){
		pt_jogo->equipa1->jogos_ganhos--;
	}

	pt_jogo->score1 = score1;
	pt_jogo->score2 = score2;
}



/* lista as equipas com mais vitorias por ordem alfabetica */

void lista_melhores_equipas(int NL, lista_ligada_equipas ** lista_ligada){
	int max_vitorias = 0;
	lista_ligada_equipas * node = *lista_ligada;

	if(*lista_ligada == NULL)
		return;

	while(node != NULL){
		if (node->equipa->jogos_ganhos > max_vitorias){
			max_vitorias = node->equipa->jogos_ganhos;
		}
		node = node->next;
	}
	printf("%d Melhores %d\n", NL, max_vitorias);
	node = *lista_ligada;
	while(node != NULL){
		if (node->equipa->jogos_ganhos == max_vitorias){
			printf("%d * %s\n", NL, node->equipa->nome_equipa);
		}
		node = node->next;
	}
}



/* destroi todos os jogos */

void destroi_jogos(node_htable_jogos ** entrada_hash_jogos){
	int i;
	node_htable_jogos * node_hash;
	node_htable_jogos * node_aux_hash;
	for (i = 0; i < TAMANHO_MAX_HASH; i++){
		node_hash = entrada_hash_jogos[i];
		while(node_hash != NULL){
			node_aux_hash = node_hash;
			node_hash = node_hash->next;
			free(node_aux_hash->jogo->nome_jogo);
			free(node_aux_hash->jogo);
			free(node_aux_hash);
		}
	}
}



/* destroi todas as equipas */

void destroi_equipas(node_htable_equipas ** entrada_hash_equipas){
	int i;
	node_htable_equipas * node;
	node_htable_equipas * node_aux;
	for (i = 0; i < TAMANHO_MAX_HASH; i++){
		node = entrada_hash_equipas[i];
		while(node != NULL){
			node_aux = node;
			node = node->next;
			free(node_aux->equipa->nome_equipa);
			free(node_aux);
		}
	}
}


/* Fim Projeto */
