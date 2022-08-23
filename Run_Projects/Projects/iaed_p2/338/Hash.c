#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
#include "LinkedList.h"
#include "Hash.h"

/*Esta funcao recebe uma key que e embaralhada e devolve um valor correspondente a essa key*/
int hash(char *nome, int M) /*recebe a key e o table size*/
{
	int h, a = 31415, b = 27183;
	for (h = 0; *nome != '\0'; nome++, a = a*b % (M-1))
	h = (a*h + *nome) % M;
	return abs(h);
}

/*Esta funcao cria a hashtable responsavel por guardar os jogos*/
void ht_creat_jogo(int tblsz, jogo *st){
	int i;
	for(i = 0;i < tblsz;i++){
		st[i] = NULL; /* Inicializar a hash com tudo a NULL*/
	}
}

/*Esta funcao cria a hashtable responsavel por guardar as equipas*/
void ht_creat_eq(int tblsz, equipa *eq){
	int i;
	for(i = 0;i < tblsz;i++)
		eq[i] = NULL;
}

void expand_jogo(int tblsz_jogo, jogo *st, int M);
void expand_equipa(int tblsz_equipa,equipa *eq, int N);

/*Esta funcao insere a equipa na hashtable das equipas*/
void insert_equipa(char *key,equipa value,int tblsz, equipa *eq,int N){
	int index;
	index = hash(key,tblsz);
	while(eq[index] != NULL)
		index = index + 1 % tblsz;
	eq[index] = malloc(sizeof(struct equipas));
	eq[index]->nome_equipa = malloc(sizeof(char)*(strlen(value->nome_equipa)+1));
	strcpy(eq[index]->nome_equipa, value->nome_equipa);
	eq[index]->vitorias = value->vitorias;
	if(N > tblsz/2){
		expand_equipa(tblsz,eq,N);
	}
}

/*Esta funcao aumenta o tamanho da hashtable sempre que a hashtable fica metade preenchida*/
void expand_equipa(int tblsz_equipa, equipa *eq, int N){
	int i;
	equipa *t = eq;
	eq = realloc(eq,2*tblsz_equipa*sizeof(equipa));
	ht_creat_eq(tblsz_equipa+tblsz_equipa,eq);
	for(i = 0;i<tblsz_equipa/2; i++){
		if(t[i] != NULL){
			insert_equipa(t[i]->nome_equipa, t[i],tblsz_equipa+tblsz_equipa, eq,N);
		}
	}
	free(t);
}

/*Esta funcao insere o jogo na hashtable dos jogos*/
void insert_jogo(char *key, jogo value,int tblsz, jogo *st ,int M){
	int index;
	index = hash(key,tblsz);
	while(st[index] != NULL){
		/*printf("%s\n", st[index]->nome);*/
		index = index + 1 % tblsz;
	}
		st[index] = malloc(sizeof(struct jogos));
		st[index]->nome = malloc(sizeof(char)*(strlen(value->nome)+1));
		strcpy(st[index]->nome,value->nome);
		st[index]->equipa1 = malloc(sizeof(char)*(strlen(value->equipa1)+1));
		strcpy(st[index]->equipa1,value->equipa1);
		st[index]->equipa2 = malloc(sizeof(char)*(strlen(value->equipa2)+1));
		strcpy(st[index]->equipa2,value->equipa2);
		st[index]->score1 = value->score1;
		st[index]->score2 = value->score2;
		if(M > tblsz/2){
			expand_jogo(tblsz,st,M);
		}
		
}

/*Esta funcao aumenta o tamanho da hashtable sempre que a hashtable fica metade preenchida*/
void expand_jogo(int tblsz_jogo, jogo *st, int M){
	int i;
	jogo *t = st;
	st = realloc(st,2*tblsz_jogo*sizeof(jogo));
	ht_creat_jogo(tblsz_jogo+tblsz_jogo, st);
	for(i = 0;i<tblsz_jogo/2; i++){
		if(t[i] != NULL){
			insert_jogo(t[i]->nome, t[i],tblsz_jogo+tblsz_jogo, st, M);
		}
	}
	free(t);
}

/*Esta funcao procura uma equipa dado o nome e, se essa equipa existir, devolve-a*/
equipa search_equipa(char *key, int tblsz, equipa *eq){
	int index;
	index = hash(key, tblsz);
	while(eq[index] != NULL){
		if((strcmp(eq[index]->nome_equipa, key)) == 0){
			return eq[index];
		}
		else
			index = (index+1)%tblsz;
	}
	return NULL;
}

/*Esta funcao procura um jogo dado o nome e, se esse jogo existir devolve-o*/
jogo search_jogo(char *key, int tblsz, jogo *st){
	int index;
	index = hash(key,tblsz);
	while(st[index] != NULL){
		if ((strcmp(st[index]->nome, key)) == 0){
			return st[index];
		}
		else 
			index = (index+1)%tblsz;
	}
	return NULL;
}

/*Esta funcao apaga um jogo da hashtable, dado o nome desse jogo*/
void delete_jogo(char *key, int tblsz, jogo *st,int M){
	int index,j;
	index = hash(key,tblsz);
	/*Encontrar o indice onde esta a key*/
	while(st[index] != NULL){
		if ((strcmp(st[index]->nome, key)) == 0){
			break;
		}
		else
			index = (index + 1) % tblsz;
	}
	if(st[index] == NULL) {
		return;
	}
	free(st[index]->nome);
	free(st[index]->equipa1);
	free(st[index]->equipa2);
	free(st[index]);
	st[index]=NULL;
	for(j = (index+1) % tblsz; st[j] != NULL; j=(j+1)%tblsz){
		insert_jogo(st[j]->nome,st[j],tblsz,st,M);
		free(st[j]->nome);
		free(st[j]->equipa1);
		free(st[j]->equipa2);
		free(st[j]);
		st[j] = NULL;
	}	
}

/*Esta funcao devolve o numero de vitorias que uma equipa tem*/
int get_vitorias(char *key, int tblsz, equipa *eq){
	int index;
	index = hash(key,tblsz);
	while(eq[index] != NULL){
		if((strcmp(eq[index]->nome_equipa, key)) == 0){
			return eq[index]->vitorias;
		}
		else
			index = (index+1)%tblsz;
	}
	return 0;	
}

/*Esta funcao devolve o nome da equipa que ganhou um determinado jogo*/
char* quem_ganhou(char *key, int tblsz, jogo *st){ /* retorna o nome da equipa vencedora*/
	int index;
	index = hash(key, tblsz);
	while(st[index] != NULL){
		if ((strcmp(st[index]->nome, key)) == 0){
			if(st[index]->score1 > st[index]->score2){
				return st[index]->equipa1;
			}
			else
				if(st[index]->score1 < st[index]->score2){
					return st[index]->equipa2;
				}
				else return NULL;
		}
		else 
			index = (index+1)%tblsz;
	}
	return NULL;
}

/*Esta funcao devolve o numero da equipa que ganhou*/
int quem_ganhou_int(char *key, int tblsz,jogo *st){ /* retorna 1 se ganhar a equipa 1 retorna 2 se ganhar a equipa 2 retorna 0 se empatarem*/
	int index;
	index = hash(key, tblsz);
	while(st[index] != NULL){
		if ((strcmp(st[index]->nome, key)) == 0){
			if(st[index]->score1 > st[index]->score2){
				return 1;
			}
			else
				if(st[index]->score1 < st[index]->score2){
					return 2;
				}
				else return 0;
		}
		else 
			index = (index+1)%tblsz;
	}
	return 0;
}

/*Esta funcao altera o score de um dado jogo pelos valores indicados*/
void altera_score(char *key, int tblsz, int score1, int score2, jogo *st){
	int index;
	index = hash(key, tblsz);
	while(st[index] != NULL){
		if ((strcmp(st[index]->nome, key)) == 0){
			st[index]->score1 = score1;
			st[index]->score2 = score2;
			return;
		}
		else
			index = (index+1)%tblsz;
	}
}

/*Esta funcao adiciona um determinado numero de vitorias, normalmente 1 ou -1 
pois a equipa perde ou ganha*/
void altera_vitorias(char*key,int tblsz,int vit, equipa *eq){
	int index;
	index = hash(key,tblsz);
	while(eq[index] != NULL){
		if ((strcmp(eq[index]->nome_equipa, key)) == 0){
			eq[index]->vitorias += vit;
			return;
		}
		else
			index = (index+1)%tblsz;
	}
}

/*Esta funcao devolve o nome da equipa 1*/
char* obtem_equipa1(char *key,int tblsz, jogo*st){
	int index;
	index = hash(key, tblsz);
	while(st[index] != NULL){
		if ((strcmp(st[index]->nome, key)) == 0){
			return st[index]->equipa1;
		}
		else
			index = (index+1)%tblsz;
	}
	return NULL;
}

/*Esta funcao devolve o nome da equipa 2*/
char* obtem_equipa2(char *key,int tblsz, jogo *st){
	int index;
	index = hash(key, tblsz);
	while(st[index] != NULL){
		if ((strcmp(st[index]->nome, key)) == 0){
			return st[index]->equipa2;
		}
		else
			index = (index+1)%tblsz;
	}
	return NULL;
}