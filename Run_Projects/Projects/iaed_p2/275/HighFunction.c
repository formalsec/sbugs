#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HighFunction.h"

/*Funcao recebe a hashtable dos jogos e verifica se esse jogo existe.Caso exista nao adiciona esse novo jogo.Verifica tambem se as equipas que fazem parte desse jogo existem.
Se cumprir todos os requisitos adiciona esse jogo*/

void addJogo(TableJogos * table_jogos, linkJogo jogo,char *nome_jogo, char *nome_equipa1, char *nome_equipa2, int golos_equipa1,int golos_equipa2){
	if(strcmp(jogo->nome, nome_jogo) == 0){
		printf("Jogo existente.\n");
	}
	else if (strcmp(jogo->equipa1, nome_equipa1) != 0 || strcmp(jogo->equipa2, nome_equipa2) != 0){
		printf("Equipa inexistente.\n");
	}
	else{
		STinsertJogo(table_jogos,nome_jogo, nome_equipa1, nome_equipa2,  golos_equipa1,  golos_equipa2);
	}
}

/*Funcao que recebe a hashtable das equipas e verifica se essa equipa existe.Caso exista, nao adiciona a equipa.Caso contrario,
se nao for encontrada essa equipa, entao e porque nao existe e adiciona ao sistema.*/

void addEquipa(TableEquipas * table_equipas, linkEquipa equipa, char nome_equipa[SIZE_CHAR]){
	if(strcmp(equipa->nome, nome_equipa) == 0){
		printf("Equipa existente.\n");
	}
	else {
		STinsertEquipa(nome_equipa, table_equipas);
	}
}

/*Funcao que recebe a hashtable dos jogos e percorre essa tabela ate encontrar o jogo pretendido*/

void findJogo(TableJogos* table_jogos, linkJogo jogo){
	if(STsearchJogo(jogo->nome, table_jogos) == NULL){
		printf("Jogo inexistente.\n");
	}
	else
		printf("%s",jogo->nome);
}

/*Funcao que recebe a hashtable das equipas e percorre essa hashtable ate encontrar a equipa desejada.*/

void findEquipa(TableEquipas* table_equipas, linkEquipa equipa){
	if(STsearchEquipa(equipa->nome, table_equipas) == NULL){
		printf("Equipa inexistente.\n");
	}
	else
		printEquipa(equipa);
}

/*Funcao que recebe a hashtable dos jogos e procura um certo jogo.Caso o encontre apaga esse jogo e torna o score a 0*/

void removeJogo(TableJogos* table_jogos, linkJogo jogo){
	if(STsearchJogo(jogo->nome, table_jogos) == NULL){
		printf("Jogo inexistente.\n");
	}
	else
		jogo->score1 = 0;
	    jogo->score2 = 0;
		STdeleteJogo(jogo, table_jogos);
		free(jogo);
}

/*Funcao que recebe a hashtable dos jogos e procura um certo jogo.Caso o encontre troca o resultado desse jogo */

void changeScore(TableJogos* table_jogos, linkJogo jogo, int score1_aux , int score2_aux){
	if(STsearchJogo(jogo->nome, table_jogos) == NULL){
		printf("Jogo inexistente.\n");
	}
	else
		jogo->score1 = score1_aux;
	    jogo->score2 = score2_aux;
}

