#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
#include "Hash.h"
#include "LinkedList.h"
#define Char_Max 1024

/*Funcoes auxiliares*/

/*Esta funcao e responsavel por verificar se um jogo ainda nao existe*/
int jogo_inexistente(char nome[],int tblsz_jogo, int contalinhas, jogo printado, jogo *st){
	char *aponta;
	aponta = malloc(sizeof(char)*(strlen(nome)+1));
	strcpy(aponta,nome);
	printado = search_jogo(aponta, tblsz_jogo,st);
	if (printado == NULL){
		printf("%d Jogo inexistente.\n", contalinhas);
		free(aponta);
		return 1;
	}
	free(aponta);
	return 0;
}

/*Esta funcao e responsavel por verificar se um jogo ja existe*/
int jogo_existente(char nome[],int tblsz_jogo, int contalinhas, jogo procura_jogo, jogo *st){
	char *aponta;
	aponta = malloc(sizeof(char)*(strlen(nome)+1));
	strcpy(aponta,nome);
	procura_jogo = search_jogo(aponta, tblsz_jogo, st);
	if (procura_jogo != NULL){
		printf("%d Jogo existente.\n", contalinhas);
		free(aponta);
		return 1;
	}
	free(aponta);
	return 0;
}

/*Esta funcao e responsavel por verificar se uma equipa ainda nao existe*/
int equipa_inexistente(char nome[],int tblsz_equipa,int contalinhas,equipa procura_equipa,
 equipa *eq){
	char *aponta;
	aponta = malloc(sizeof(char)*(strlen(nome)+1));
	strcpy(aponta,nome);
	procura_equipa = search_equipa(aponta,tblsz_equipa, eq);
	if(procura_equipa == NULL){
		printf("%d Equipa inexistente.\n", contalinhas);
		free(aponta);
		return 1;
	}
	free(aponta);
	return 0;
}

/*Esta funcao e responsavel por determinar se uma dada equipa ja existe*/
int equipa_existente(char nome[],int tblsz_equipa, int contalinhas, equipa procura_equipa,
 equipa *eq){
	char *aponta;
	aponta = malloc(sizeof(char)*(strlen(nome)+1));
	strcpy(aponta,nome);
	procura_equipa = search_equipa(aponta,tblsz_equipa,eq);
	if(procura_equipa != NULL){
		printf("%d Equipa existente.\n", contalinhas);
		free(aponta);
		return 1;
	}
	free(aponta);
	return 0;

}

int cmp_str(const void * a, const void * b)
{
    char **palavra1 = (char**) a;
    char **palavra2 = (char**) b;
    return strcmp(*palavra1, *palavra2);
}

/*Esta funcao realiza os free da hashtable das equipas*/
void free_hash_eq(equipa * eq, int tblsz_equipa){
	int i;
	for(i = 0;i<tblsz_equipa;i++){
		if (eq[i]!= NULL){
			free(eq[i]->nome_equipa);
			free(eq[i]);
		}
	}
	free(eq);
}

/*Esta funcao realiza os free da hashtable dos jogos*/
void free_hash_st(jogo *st, int tblsz_jogo){
	int i;
	for(i = 0;i < tblsz_jogo;i++){
		if(st[i] != NULL){
			free(st[i]->nome);
			free(st[i]->equipa1);
			free(st[i]->equipa2);
			free(st[i]);
		}
	}
	free(st);
}

/*Esta funcao realiza os free da lista com os jogos*/
void free_list_jogo(node Head){
	struct nodes *temp;
	struct nodes *help;
	temp = Head;
	while(temp != NULL){
		help = temp->link;
		free(temp->nome_jogo);
		free(temp);
		temp = help;
	}
}

/*Esta funcao realiza os free da lista com as equipas*/
void free_list_equipa(node Head_equipas){
	struct nodes *temp;
	struct nodes *help;
	temp = Head_equipas;
	while(temp != NULL){
		help = temp->link;
		free(temp->nome_jogo);
		free(temp);
		temp = help;
	}
}

/*Esta funcao verifica quem ganhou o jogo anterior, verifica quem ganhou o proximo jogo,
 e realiza as devidas alteracoes aos resultados e as vitorias*/
void compara_resultados(int who_won_int, int score1, int score2, char nome[], int tblsz_jogo,
 jogo*st, int tblsz_equipa, equipa*eq, char team2[], char*aponta_nome_equipa, char team1[]){
	if(who_won_int == 1){
		if(score1 > score2){
			altera_score(nome,tblsz_jogo,score1,score2,st);
		}
		else if(score2 > score1){
			altera_vitorias(quem_ganhou(nome,tblsz_jogo,st),tblsz_equipa,-1,eq);
			strcpy(team2,obtem_equipa2(nome,tblsz_jogo,st));
			altera_vitorias(team2,tblsz_equipa,1,eq);
			altera_score(nome,tblsz_jogo,score1,score2,st);
			free(aponta_nome_equipa);
			return;
			/*Mudar o score do jogo, retirar vitoria a equipa 1 e adicionar a equipa 2*/
		}
		else if(score2 == score1){
			altera_vitorias(quem_ganhou(nome,tblsz_jogo,st),tblsz_equipa,-1,eq);
			altera_score(nome,tblsz_jogo,score1,score2,st);
			/*Mudar o resultado do jogo e remover vitoria da equipa 1*/
		}
		free(aponta_nome_equipa);
	}
	else if(who_won_int == 2){
		if(score1 > score2){
			altera_vitorias(quem_ganhou(nome,tblsz_jogo,st),tblsz_equipa,-1,eq);
			strcpy(team1,obtem_equipa1(nome,tblsz_jogo,st));
			altera_vitorias(team1,tblsz_equipa,1,eq);
			altera_score(nome,tblsz_jogo,score1,score2,st);
			/*Mudar o score do jogo, remover vitoria da equipa2 e adicionar vitoria a equipa 1*/
		}
		else if(score2 > score1){
			altera_score(nome,tblsz_jogo,score1,score2,st);
			/*Mudar o score do jogo*/
		}
		else if(score2 == score1){
			altera_vitorias(quem_ganhou(nome,tblsz_jogo,st),tblsz_equipa,-1,eq);
			altera_score(nome,tblsz_jogo,score1,score2,st);
			/*Mudar score do jogo e remover vitoria da equipa 2*/
		}
		free(aponta_nome_equipa);
	}
	else if(who_won_int == 0){
		if(score1 >score2){
			altera_score(nome,tblsz_jogo,score1,score2,st);
			strcpy(team1,obtem_equipa1(nome,tblsz_jogo,st));
			altera_vitorias(team1,tblsz_equipa,1,eq);
			/*Mudar score e adicionar vitoria a equipa 1*/
		}
		else if(score2>score1){
			altera_score(nome,tblsz_jogo,score1,score2,st);
			strcpy(team2,obtem_equipa2(nome,tblsz_jogo,st));
			altera_vitorias(team2,tblsz_equipa,1,eq);
			/*Mudar score e adicionar vitoria a equipa 2*/
		}
		else if(score2 == score1){
			altera_score(nome,tblsz_jogo,score1,score2,st);
			/*Mudar o score*/
		}
	}
}

/*Funcao responsavel por verificar os erros possiveis do case a*/
int erros_a(int stop, jogo game, char equipa1[], int tblsz_equipa, int contalinhas, 
 equipa procura_equipa, equipa*eq, char equipa2[], 
 int tblsz_jogo, jogo *st, jogo procura_jogo){
	stop = jogo_existente(game->nome,tblsz_jogo,contalinhas,procura_jogo,st);
	if(stop == 1){
		free(game->equipa2);
		free(game->equipa1);
		free(game->nome);
		return 1;
	}
	stop = equipa_inexistente(equipa1,tblsz_equipa,contalinhas,procura_equipa,eq);
	if (stop == 1){
		free(game->equipa2);
		free(game->equipa1);
		free(game->nome);
		return 1;
	}
	stop = equipa_inexistente(equipa2,tblsz_equipa,contalinhas,procura_equipa,eq);
	if(stop == 1){
		free(game->equipa2);
		free(game->equipa1);
		free(game->nome);
		return 1;
	}
	return 0;
}

/*Esta funcao compara os 2 scores e adiciona uma vitoria a equipa vencedora*/
void compara_score(int score1, int score2, int tblsz_equipa, equipa*eq, char equipa1[],
 char equipa2[]){
	if(score1 > score2){
		altera_vitorias(equipa1,tblsz_equipa,1,eq);
	}
	else
		if(score2 > score1){
			altera_vitorias(equipa2,tblsz_equipa,1,eq);
	}
}

/*Funcao principal*/

int main()
{
	char** equipas_c_vitorias; /*Variavel que vai guardar as equipas com o maximo de vitorias*/
	char c;
	char nome[Char_Max],equipa1[Char_Max],equipa2[Char_Max],team_name[Char_Max],
	who_won[Char_Max],team1[Char_Max],team2[Char_Max];
	char*aponta, *aponta_nome_equipa;
	int score1,score2,who_won_int, count;
	int contalinhas = 0, tblsz_jogo = 100000, tblsz_equipa = 100000,stop = 0,i = 0,
	 M = 0, N  = 0, erro_a = 0; /*Sempre que a variavel stop estiver a 1
	  significa que foi detetado um erro*/
	struct jogos *game = malloc(sizeof(struct jogos));
	struct jogos *procura_jogo = malloc(sizeof(struct jogos));
	jogo *printado = malloc(sizeof(jogo));
	struct equipas *add_equipa = malloc(sizeof(struct equipas));
	struct equipas *procura_equipa;
	struct nodes *Head = NULL;/*linked list com o nome dos jogos*/
	struct nodes *Head_equipas = NULL;/*Linked list com o nome das equipas*/
	struct tuple *tuplo;/*Par com o maior numero de vitorias
	 e com quantas equipas teem essas vitorias*/
	jogo *st;
	equipa *eq;
	tuplo = (struct tuple*)malloc(sizeof(struct tuple));
	st = malloc(tblsz_jogo*sizeof(jogo));
	eq = malloc(tblsz_equipa*sizeof(equipa));
	ht_creat_eq(tblsz_equipa, eq);
	ht_creat_jogo(tblsz_jogo, st);
	while((c=getchar()) != EOF){
		switch(c){
			case 'a':
				M++;
				contalinhas++;
				scanf(" %[^:]:%[^:]:%[^:]:%d:%d",nome,equipa1,equipa2,&score1,&score2);
				game->nome = malloc(sizeof(char)*(strlen(nome)+1));
				strcpy(game->nome,nome);
				game->equipa1 = malloc(sizeof(char)*(strlen(equipa1)+1));
				strcpy(game->equipa1,equipa1);
				game->equipa2 = malloc(sizeof(char)*(strlen(equipa2)+1));
				strcpy(game->equipa2,equipa2);
				game->score1 = score1;
				game->score2 = score2;
				erro_a = erros_a(stop, game, equipa1, tblsz_equipa, contalinhas, procura_equipa, eq, 
					equipa2, tblsz_jogo, st, procura_jogo);
				if(erro_a == 1)
					break;
				compara_score(score1, score2, tblsz_equipa, eq, equipa1, equipa2);
				Head = append(nome,Head);
				insert_jogo(game->nome, game, tblsz_jogo, st , M);
				free(game->equipa2);
				free(game->equipa1);
				free(game->nome);
				break;
			case 'l':
				contalinhas++;
				display(contalinhas,tblsz_jogo,Head,st);
				break;
			case 'A':
				N++;
				contalinhas++;
				scanf(" %[^\n]", team_name);
				getchar();
				aponta_nome_equipa = malloc(sizeof(char)*(strlen(team_name)+1));
				strcpy(aponta_nome_equipa,team_name);
				stop = equipa_existente(team_name,tblsz_equipa,contalinhas,procura_equipa,eq);
				if (stop == 1){
					free(aponta_nome_equipa);
					break;
				}
				add_equipa->nome_equipa = malloc(sizeof(char)*(strlen(team_name)+1));
				strcpy(add_equipa->nome_equipa,team_name);
				add_equipa->vitorias = 0;
				Head_equipas = append(team_name,Head_equipas);
				insert_equipa(aponta_nome_equipa,add_equipa,tblsz_equipa, eq, N);
				free(add_equipa->nome_equipa);
				free(aponta_nome_equipa);
				break;
			case 'p':
				contalinhas++;
				scanf(" %[^\n]", nome);
				stop = jogo_inexistente(nome,tblsz_jogo,contalinhas,(*printado),st);
				if(stop == 1)
					break;
				aponta = malloc(sizeof(char)*(strlen(nome)+1));
				strcpy(aponta,nome);
				(*printado) = search_jogo(aponta,tblsz_jogo,st);
				printf("%d %s %s %s %d %d\n",contalinhas, (*printado)->nome, (*printado)->equipa1,
				(*printado)->equipa2,(*printado)->score1,(*printado)->score2);
				free(aponta);
				break;

			case 'r':
				M--;
				contalinhas++;
				scanf(" %[^\n]", nome);
				stop = jogo_inexistente(nome,tblsz_jogo,contalinhas,(*printado),st);
				if(stop == 1)
					break;
				if(quem_ganhou(nome,tblsz_jogo,st) == NULL){
					delete_jogo(nome,tblsz_jogo,st,M);
					Head = delete_node(nome,Head);
					break;
				}
				strcpy(who_won,quem_ganhou(nome,tblsz_jogo,st));
				if(who_won != NULL){
					altera_vitorias(who_won,tblsz_equipa,-1,eq);
				}
				delete_jogo(nome,tblsz_jogo, st, M);
				Head = delete_node(nome,Head);
				break;
			case 'P':
				contalinhas++;
				scanf(" %[^\n]", nome);
				getchar();
				stop = equipa_inexistente(nome,tblsz_equipa,contalinhas,procura_equipa,eq);
				if(stop == 1)
					break;
				aponta = malloc(sizeof(char)*(strlen(nome)+1));
				strcpy(aponta,nome);
				procura_equipa = search_equipa(aponta,tblsz_equipa, eq);
				printf("%d %s %d\n", contalinhas, procura_equipa->nome_equipa,procura_equipa->vitorias);
				free(aponta);
				break;

			case 's':
				contalinhas++;
				scanf(" %[^:]:%d:%d",nome,&score1,&score2);
				stop = jogo_inexistente(nome,tblsz_jogo,contalinhas,(*printado),st);
				if(stop == 1){
					break;
				}
				if(quem_ganhou(nome,tblsz_jogo,st) != NULL){
					aponta_nome_equipa = malloc(sizeof(char)*(strlen(quem_ganhou(nome,tblsz_jogo,st))+1));
					strcpy(aponta_nome_equipa,quem_ganhou(nome,tblsz_jogo,st));
				}
				who_won_int = quem_ganhou_int(nome,tblsz_jogo,st);
				compara_resultados(who_won_int, score1, score2, nome, tblsz_jogo, st, tblsz_equipa, eq, team2,
				 aponta_nome_equipa, team1);
				break;
			case 'g':
				contalinhas++;
				count = 0;
				tuplo = get_max_vit(Head_equipas,tblsz_equipa,eq,tuplo);
				if(tuplo->conta_eq_c_max_vit != 0){
					printf("%d Melhores %d\n", contalinhas, tuplo->max_vitorias);
					equipas_c_vitorias = malloc(sizeof(char*)*(tuplo->conta_eq_c_max_vit+1));
					obtem_equipas_com_max_vit(Head_equipas, tuplo->max_vitorias, equipas_c_vitorias, tblsz_equipa,eq); /*Guarda as equipas com max vitorias em equipas_c_vitorias*/ 
					/*guardo os ponteiros para as equipas com maximo de vitorias*/
					qsort(equipas_c_vitorias,tuplo->conta_eq_c_max_vit,sizeof(char*),(cmp_str));
					for(i = 0;i < tuplo->conta_eq_c_max_vit;i++){
						count ++;
						printf("%d * %s\n", contalinhas,*equipas_c_vitorias);
						free(*equipas_c_vitorias);
						equipas_c_vitorias++;
					}
					equipas_c_vitorias -= count;
					free(equipas_c_vitorias);
				}
				break;
			case 'x':
				free(tuplo);
				free(printado);
				free_hash_eq(eq,tblsz_equipa);
				free_hash_st(st,tblsz_jogo);
				free_list_jogo(Head);
				free_list_equipa(Head_equipas);
				free(game);
				free(procura_jogo);
				free(add_equipa);
				break;
		}
	}
	return 0;
}