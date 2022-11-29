#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LowFunction.h"

/*Esta funcao e responsavel pela alocacao de memoria de tudo o que e necessario para um novo no de uma equipa*/
linkEquipa NEWequipa(char* new_equipa){
	linkEquipa equipa = can_fail_malloc(sizeof(struct node));
	equipa->nome = can_fail_malloc(sizeof(char)*(strlen(new_equipa)+1));
	equipa->wins = 0;
	strcpy(equipa->nome, new_equipa);
	equipa->next = NULL;
	return equipa;
}

/*Esta funcao e responsavel pela alocacao de memoria de tudo o que e necessario para um novo no de um jogo*/
linkJogo NEWjogo(char* new_jogo, char* new_equipa1, char* new_equipa2, int new_score1, int new_score2){
	linkJogo jogo = can_fail_malloc(sizeof(struct nodejogo));
	jogo->nome = can_fail_malloc(sizeof(char)*(strlen(new_jogo)+1));
	jogo->equipa1 = can_fail_malloc(sizeof(char)*strlen(new_equipa1)+1);
	jogo->equipa2 = can_fail_malloc(sizeof(char)*strlen(new_equipa2)+1);
	jogo->score1 = new_score1;
	jogo->score2 = new_score2;
	strcpy(jogo->nome, new_jogo);
	strcpy(jogo->equipa1, new_equipa1);
	strcpy(jogo->equipa2, new_equipa2);
	jogo->next = NULL;
	return jogo;
}

/*Esta funcao insere uma nova equipa no inicio da lista*/
linkEquipa insertBeginListEquipa(linkEquipa head, char* name){
	linkEquipa equipa = NEWequipa(name);
	equipa->next = head;
	return equipa;
}

/*Esta funcao insere um novo jogo no inicio da lista*/
linkJogo insertBeginListJogo(linkJogo head, char *jogo_nome, char *equipa1_nome, char *equipa2_nome, int resultado1, int resultado2){
	linkJogo jogo = NEWjogo(jogo_nome, equipa1_nome, equipa2_nome, resultado1, resultado2);
	jogo->next = head;
	return jogo;
}

/*Esta funcao recebe uma equipa e procura essa equipa na lista, caso ela exista*/
linkEquipa searchListEquipa(linkEquipa head, char* name){
	linkEquipa equipa;
	for(equipa = head; equipa != NULL; equipa = equipa->next){
		if(strcmp(equipa->nome, name) == 0){
			return equipa;
		}
	}
	return NULL;
}

/*Esta funcao recebe um jogo e procura esse jogo na lista, caso ele exista*/
linkJogo searchListJogo(linkJogo head, char* name){
	linkJogo jogo;
	for(jogo = head; jogo != NULL; jogo = jogo->next){
		if(strcmp(jogo->nome, name) == 0){
			return jogo;
		}
	}
	return NULL;
}

/*Esta funcao recebe uma equipa e quando essa equipa for encontrada na lista e removida*/
linkEquipa removeFromListEquipa(linkEquipa head, char* name){
	linkEquipa equipa, prev;
	for(equipa = head, prev = NULL; equipa != NULL;
		prev = equipa, equipa = equipa->next){
		if(strcmp(equipa->nome, name) == 0){
			if(equipa == head){
				head = equipa->next;
			}
			else{
				prev->next = equipa->next;
			}

			free(equipa->next);
			free(equipa);
		}
	}
	return head;
}

/*Esta funcao recebe um jogo e quando esse jogo for encontrado na lista e removido*/
linkJogo removeFromListJogo(linkJogo head, char* name){
	linkJogo jogo, prev;
	for(jogo = head, prev = NULL; jogo != NULL;
		prev = jogo, jogo = jogo->next){
		if(strcmp(jogo->nome, name) == 0){
			if(jogo == head){
				head = jogo->next;
			}
			else{
				prev->next = jogo->next;
			}

			free(jogo->next);
			free(jogo);
		}
	}
	return head;
}

/*Esta funcao adiciona um jogo ao final da lista*/
linkJogo insertEnd(linkJogo head, char *jogo_nome, char *equipa1_nome, char *equipa2_nome, int resultado1, int resultado2){
	linkJogo jogo;
	if(head == NULL){
		return NEWjogo(jogo_nome, equipa1_nome, equipa2_nome, resultado1, resultado2);
	}
	for(jogo = head; jogo->next != NULL; jogo = jogo->next){
		;
	}
	jogo->next = NEWjogo(jogo_nome, equipa1_nome, equipa2_nome, resultado1, resultado2);
	return head;
}


/*Esta funcao recebe uma string e calcula o bucket adequado para a mesma dentro da hashtable*/
int hash(char *v){
	int h = 0, a = 31415, b = 27183, size = SIZE_HASH;

	for(h = 0; *v != '\0'; v++, a = a*b % (size-1)){
		h = (a*h + *v) % size;
	}
	return h;
}

/*Esta funcao recebe uma equipa e liberta toda a memoria anteriormente alocada para esta.*/ 
void freeEquipa(linkEquipa equipa){
	free(equipa->nome);
	free(equipa);
}

/*Esta funcao recebe um jogo e liberta toda a memoria anteriormente alocada para este.*/
void freeJogo(linkJogo jogo){
	free(jogo->nome);
	free(jogo->equipa1);
	free(jogo->equipa2);
	free(jogo);
}

/*Esta funcao recebe uma equipa e devolve todas as suas caracteristicas*/
void printEquipa(linkEquipa equipa){
	printf("%s %d\n",equipa->nome, equipa->wins);
}

/*Esta funcao recebe um jogo e devolve todas as suas caracteristicas*/
void printJogo(linkJogo jogo){
	printf("%s %s %s %d %d\n", jogo->nome, jogo->equipa1, jogo->equipa2, jogo->score1, jogo->score2);
}


/*Esta funcao recebe a hashtable das equipas e inicia essa a NULL*/
TableEquipas*  STinitEquipa(){
	int i;
	TableEquipas* table_equipas = can_fail_malloc(sizeof(TableEquipas));
	table_equipas->M = SIZE_HASH;
	table_equipas->headsEquipa = can_fail_malloc(table_equipas->M*sizeof(linkEquipa));
	for(i = 0; i < table_equipas->M; i++)
		table_equipas->headsEquipa[i] = NULL;
	return table_equipas;
}

/*Esta funcao recebe a hashtable dos jogos e inicia essa a NULL*/
TableJogos*  STinitJogo(){
	int i;
	TableJogos* table_jogos = can_fail_malloc(sizeof(TableJogos));
	table_jogos->M = SIZE_HASH;
	table_jogos->headsJogo = can_fail_malloc(table_jogos->M*sizeof(linkJogo));
	for(i = 0; i < table_jogos->M ; i++)
		table_jogos->headsJogo[i] = NULL;
	return table_jogos;

}

/*Esta funcao recebe a hashtable referente a uma equipa e calcula em que bucket adicionar essa equipa*/
void STinsertEquipa(char *nome, TableEquipas* table_equipas){ 
	int i = hash(nome);
	table_equipas->headsEquipa[i] = insertBeginListEquipa(table_equipas->headsEquipa[i], nome);
}

/*Esta funcao recebe a hashtable referente a um jogo e calcula em que bucket adicionar esse jogo*/
void STinsertJogo(TableJogos* table_jogos, char *jogo_nome, char *equipa1_nome, char *equipa2_nome, int resultado1, int resultado2){
	int i = hash(jogo_nome);
	table_jogos->headsJogo[i] = insertBeginListJogo(table_jogos->headsJogo[i], jogo_nome, equipa1_nome, equipa2_nome, resultado1, resultado2);
}

/*Esta funcao recebe a hashtable referente a uma equipa e calcula em que bucket remover essa equipa*/
void STdeleteEquipa(linkEquipa equipa, TableEquipas* table_equipas){
	int i = hash(equipa->nome);
	table_equipas->headsEquipa[i] = removeFromListEquipa(table_equipas->headsEquipa[i], equipa->nome);
}

/*Esta funcao recebe a hashtable referente a um jogo e calcula em que bucket remover esse jogo*/
void STdeleteJogo(linkJogo jogo, TableJogos* table_jogos){
	int i = hash(jogo->nome);
	table_jogos->headsJogo[i] = removeFromListJogo(table_jogos->headsJogo[i], jogo->nome);
}

/*Esta funcao recebe uma hashtable referente a uma equipa e procura o bucket atraves da chave que recebe*/
linkEquipa STsearchEquipa(Key v, TableEquipas* table_equipas){
	int i = hash(v);
	return searchListEquipa(table_equipas->headsEquipa[i], v);
}

/*Esta funcao recebe uma hashtable referente a um jogo e procura o bucket atraves da chave que recebe*/
linkJogo STsearchJogo(Key v, TableJogos* table_jogos){
	int i = hash(v);
	return searchListJogo(table_jogos->headsJogo[i], v);
}
 
