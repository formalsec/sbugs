#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1023
#define NUM 1073
#define MIN 1


typedef struct valores {
	int n;
	int NL;
	int e;
} saved;
saved value[MIN];   /* Tabela de variaveis*/


typedef struct jogos {
	char nome[MAX];
	char equipa1[MAX];
	char equipa2[MAX];
	int score1;
	int score2;
	int deleted;
} info;
info jogo[NUM];   /* Tabela de jogos */


typedef struct equipas {
	char nome[MAX];
	int vitorias;
} lista;
lista equipa[NUM];    /* Tabela das equipas */


/*
Verifica se existe um jogo dado um nome.
*/

int nao_existe_jogo(info jogo[NUM], char in_nome[MAX], saved value[MIN])
{
	int c = 0;
	while(c < value[0].n){
		if(strcmp(jogo[c].nome, in_nome) == 0 && jogo[c].deleted != 1){
			return 0;
		}
		c++;
	}
	return 1;
}

/*
Verifica se existe uma equipa dado um nome.
*/

int nao_existe_equipa(lista equipa[NUM], char in_nome[MAX], saved value[MIN])
{
	int c = 0;
	while(c < value[0].e){
		if(strcmp(equipa[c].nome, in_nome) == 0){
			return 0;
		}
		c++;
	}
	return 1;
}

/*
Adiciona um novo jogo.
*/

void a(info jogo[NUM], lista equipa[NUM], saved value[MIN])
{
	int c = 0;
	char in_nome[MAX], equipa1[MAX], equipa2[MAX], equipa_vencedora[MAX];
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]", in_nome, equipa1, equipa2);
	if(!nao_existe_jogo(jogo, in_nome, value)){
		printf("%d Jogo existente\n", value[0].NL);
		value[0].NL++;
	}
	else if(nao_existe_equipa(equipa, equipa1, value) || nao_existe_equipa(equipa, equipa2, value)){
		printf("%d Equipa inexistente\n", value[0].NL);
		value[0].NL++;
	}
	else{
	scanf(":%d:%d", &jogo[value[0].n].score1, &jogo[value[0].n].score2);
	if(jogo[value[0].n].score1 > jogo[value[0].n].score2){
		strcpy(equipa_vencedora, equipa1);
	}
	if(jogo[value[0].n].score1 < jogo[value[0].n].score2){
		strcpy(equipa_vencedora, equipa2);
	}
	if(jogo[value[0].n].score1 != jogo[value[0].n].score2){
		while(strcmp(equipa[c].nome, equipa_vencedora) != 0){
			c++;
		}
		equipa[c].vitorias++;
	}
	strcpy(jogo[value[0].n].nome, in_nome);
	strcpy(jogo[value[0].n].equipa1, equipa1);
	strcpy(jogo[value[0].n].equipa2, equipa2);
	value[0].n++;
	}
}

/*
Lista todos os jogos introduzidos.
*/

void l(info jogo[NUM], saved value[MIN])
{
	int c = 0;
	while(c < value[0].n){
		if(jogo[c].deleted != 1){
			printf("%d %s %s %s %d %d\n", value[0].NL, jogo[c].nome, jogo[c].equipa1, jogo[c].equipa2, jogo[c].score1, jogo[c].score2);
			value[0].NL++;
		}
		c++;
	}
}

/*
Proucura um jogo com o nome dado.
*/

void p(info jogo[NUM], saved value[MIN])
{
	int c = 0;
	char in_nome[MAX];
	scanf("%s", in_nome);
	if(nao_existe_jogo(jogo, in_nome, value)){
		printf("%d Jogo inexistente\n", value[0].NL);
		value[0].NL++;
	}
	else{
		while(strcmp(jogo[c].nome, in_nome) != 0){
			c++;
		}
		printf("%d %s %s %s %d %d\n", value[0].NL, jogo[c].nome, jogo[c].equipa1, jogo[c].equipa2, jogo[c].score1, jogo[c].score2);
		value[0].NL++;
	}
}

/*
Altera o score de um jogo dado o nome.
*/

void s(info jogo[NUM], saved value[MIN])
{
	int c = 0;
	int in_score1, in_score2;
	char in_nome[MAX];
	scanf(" %[^:\n]:%d:%d", in_nome, &in_score1, &in_score2);
	if(nao_existe_jogo(jogo, in_nome, value)){
		printf("%d Jogo inexistente\n", value[0].NL);
		value[0].NL++;
	}
	else{
		while(strcmp(jogo[c].nome, in_nome) != 0){
			c++;
		}
		jogo[c].score1 = in_score1;
		jogo[c].score2 = in_score2;
	}
}

/*
Apaga um jogo dado um nome.
*/

void r(info jogo[NUM], saved value[MIN])
{
	char in_nome[MAX];
	int c = 0;
	scanf("%s", in_nome);
	if(nao_existe_jogo(jogo, in_nome, value)){
		printf("%d Jogo inexistente\n", value[0].NL);
		value[0].NL++;
	}
	else{
		while(strcmp(jogo[c].nome, in_nome) != 0){
			c++;
		}
	jogo[c].deleted = 1;
	}
}

/*
Adiciona uma nova equipa.
*/

void A(lista equipa[NUM], saved value[MIN])
{
	char in_nome[MAX];
	scanf("%s", in_nome);
	if(!nao_existe_equipa(equipa, in_nome, value)){
		printf("%d Equipa existente\n", value[0].NL);
		value[0].NL++;
	}
	else{
		strcpy(equipa[value[0].e].nome, in_nome);
		value[0].e++;
	}
}

/*
Adiciona um novo jogo.
*/

void P(lista equipa[NUM], saved value[MIN])
{
	char in_nome[MAX];
	int c = 0;
	scanf("%s", in_nome);
	if(nao_existe_equipa(equipa, in_nome, value)){
		printf("%d Equipa inexistente\n", value[0].NL);
		value[0].NL++;
	}
	else{
		while(strcmp(equipa[c].nome, in_nome) != 0){
			c++;	
		}
		printf("%d %s %d\n", value[0].NL, in_nome, equipa[c].vitorias);
		value[0].NL++;
	}
}


void g(lista equipa[NUM], saved value[MIN])
{
	int total_vitorias = 0;
	int c1 = 0;
	int c2 = 0;
	int c3 = 0;
	int c4 = 0;
	int c5 = 1;
	int c6 = 1;
	char str[NUM][MAX];
	char temp[MAX];
	if(value[0].e > 0){
		while(c1 < value[0].e){
			total_vitorias += equipa[c1].vitorias;
			c1++;
		}
		printf("%d Melhores %d\n", value[0].NL, total_vitorias);
		value[0].NL++;
		while(c2 < value[0].e){
			if(equipa[c2].vitorias > 0){
				strcpy(str[c3], equipa[c2].nome);
				c3++;
			}
			c2++;
		}
		while(c4 < value[0].e){
			while(c5 < value[0].e){
				if(strcmp(str[c4], str[c5]) > 0){
					strcpy(temp, str[c4]);
					strcpy(str[c4], str[c5]);
					strcpy(str[c5], temp);
				}
				c5++;
			}
			c4++;
		}
		c6 = value[0].e -1;
		while(c6 > 0){
			printf("%d * %s\n", value[0].NL, str[c6]);
			value[0].NL++;			
			c6--;
		}
	}
}


int main()
{
	char letra;
	while(letra != 'x'){
		scanf("%c", &letra);
		if(letra == 'a'){
			a(jogo, equipa, value);
		}
		if(letra == 'l'){
			l(jogo, value);
		}
		if(letra == 'p'){
			p(jogo, value);
		}
		if(letra == 's'){
			s(jogo, value);
		}
		if(letra == 'r'){
			r(jogo, value);
		}
		if(letra == 'A'){
			A(equipa, value);
		}
		if(letra == 'P'){
			P(equipa, value);
		}
		if(letra == 'g'){
			g(equipa, value);
		}
	}
	return 0;
}