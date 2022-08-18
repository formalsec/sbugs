#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "teamHTable.h"
#include<assert.h>

#define Key(a) (a->name)/*macro para a chave de um ponteiro*/

/*funcao auxiliar que termina o programa e reporta erro*/
void err(const char *msg){
	printf("ERR: %s\n", msg);
	exit(EXIT_FAILURE);
}

/*funcao auxiliar que le uma string e aloca memoria necessaria*/
char *my_strdup(char *in){	
	char *str;
    char *p;
    int len = 0;

    while (in[len])
        len++;
    str = malloc(len + 1);
    p = str;
    while (*in)
        *p++ = *in++;
    *p = '\0';
    return str;
}

/*hash transforma o input num indice*/
int hash(char * v) {
	int h=0, a=31415, b=27183;
	/*printf("hash de %s\n", v);*/
	for(h=0; *v != '\0'; v++, a = a*b%((SIZE*2)-1))
		h = (a*h + *v)% SIZE;
	return h;
}

/*hashtwo transforma o input num indice*/
int hashtwo(char * v) {
	int h = 0, a = 7879, b= 4513;
	for(h = 0; *v != '\0'; v++, a = a*b%((SIZE*2)-1))
		h = (a*h + *v) % SIZE;
	return h;

}

/*inicializa a hashtable de equipas*/
tlink ** init_HTteams(int number){
	int i;
	tlink ** HTteams = malloc((number*2)*sizeof(tlink*));
	for(i=0; i<(number*2); i++){
		HTteams[i] = NULL;
	}
	return HTteams;
}

/*duplica o tamanho da hashtable HTteams se esta chega a metade da sua capacidade*/
tlink ** texpand(tlink ** HTteams, int number){
	int i;
	tlink ** t = HTteams;
	tlink ** newHTteam;
	newHTteam = init_HTteams(number*4);
	for(i = 0; i <number*2; i++){
		if(Key(t[i]->t) != NULL)
			tsimplyInsert(t[i], newHTteam);
	}
	free(t);
	return newHTteam;
}

/*insere o jogo na hashtable dado o ponteiro para este*/
tlink * tsimplyInsert(tlink * new, tlink ** HTteams){
	int i, k;
	i = hash(Key(new->t));
	k = hashtwo(Key(new->t));
	printf("volto a inserir %s\n", Key(new->t));
	while(HTteams[i] != NULL)
		i = (i+k) % SIZE;
	HTteams[i] = new;
	return new;
}

/*inicializa o array de equipas - tamanho consoante o numero de equipas no sistema*/
pTeam ** team_array(int counter){
	int i;
	pTeam** lista = malloc((counter)*sizeof(pTeam*));
	for(i=0; i<(counter); i++){
		lista[i] = NULL;
	}
	return lista;
}

/*cria a equipa, dado o nome*/
pTeam * create_team(char * buffer0){
	pTeam * equipa = malloc(sizeof(struct team));
	equipa = malloc(sizeof(struct team));
	equipa->wins = 0;
	/*aloca memoria necessaria para o nome da equipa*/
	equipa->name = my_strdup(buffer0);
	/*retorna o ponteiro para a equipa criada*/
	return equipa;
}

/*cria o ponteiro para a equipa, depois de criada, e insere na hashtable HTteams*/
tlink * tLinkInsert(char * buffer0, tlink * link, tlink ** HTteams){
	int i, k;
	/*se ja existe equipa com este nome, retorna NULL*/
	if(search_team(HTteams, buffer0) != NULL) return NULL;
	else{
		link->t = create_team(buffer0);
		i = hash(Key(link->t));
		k = hashtwo(Key(link->t));
		while(HTteams[i] != NULL)
			i = (i + k) % (SIZE*2);
		HTteams[i] = link;/*insere na hashtable*/
		return link;
	}
}

/*procura uma equipa na hashtable dado o nome*/
tlink * search_team(tlink ** HTteams, char *nome){
	int i, k;
	tlink * link;
	i = hash(nome);
	k = hashtwo(nome);
	link = HTteams[i];
	while(HTteams[i]!= NULL){
		link = HTteams[i];
		if(strcmp(nome, Key(link->t)) == 0) return HTteams[i];
		else
			i = (i + k) % (SIZE*2);
	}
	return NULL;
}

/*dada a hashtable das equipas no sistema, procura elementos nao nulo
retorna o array de equipas existentes na hashtable*/
pTeam ** search_el(pTeam ** aux, tlink ** HTteams, int count){
	int i, j=0;
	pTeam ** equipa = team_array(count);
	pTeam * taux;
	for (i = 0; i < count; i++){
		if(equipa[i] != NULL)
			equipa[i] = aux[i];
	}
	while(j < count){
		for(i=0; i<(SIZE*2); i++){
			if(HTteams[i] != NULL){
				taux = HTteams[i]->t; /*equipa presente na htable*/
				if(equipa[j] != taux){/*se tiver guardado um elemento diferente do atual*/
					equipa[j] = taux;/*copia o atual para o array*/
				}j++;
			}
		}
	}
	return equipa;/*equipa contem todas as equipas presentes encontradas na hashtable*/
}

/*configura as equipas em STteams por ordem lexicografica*/
pTeam ** abc_winners(pTeam ** STteams, int counter){
	
	int i,j;
	pTeam ** equipa = team_array(counter);

	for (i = 0; i < counter; i++){
		equipa[i] = STteams[i];
	}
	for(i = 0; i < (counter-1); i++){
		for(j = i+1; j < (counter); j++){
			/*se o seguinte for maior que o atual, 
			troco as posicoes no vetor*/
				if(strcmp(Key(STteams[i]), Key(STteams[j])) > 0){
					equipa[i] = STteams[i];
					STteams[i] = STteams[j];
					STteams[j] = equipa[i];
				}
		}
	}
	return STteams;/*retorna STteams ordenada*/
}

/*dada a Hashtable e o nome da equipa, incrementa/decrementa as vitorias
dependendo de var, equipa assume papel WINNER ou LOOSER*/
tlink * change_win_team(tlink **HTteams, char*nome, int var){
	int i, k;
	tlink * link;
	i = hash(nome);
	k = hashtwo(nome);
	while(HTteams[i]!= NULL){
		link = HTteams[i];
		if(strcmp(nome, Key(link->t)) == 0){/*encontra a equipa na hashtable*/
			if(var == WINNER)
				link->t->wins += 1;/*incremente as vitorias*/
			else if(var == LOOSER)
				link->t->wins -= 1;/*decrementa as vitorias*/
			return link;
		}
		else i = (i + k) % SIZE;
	}
	return NULL;
}

/*return true se a hashtable de jogos esta vazia, false caso contrario*/
bool teamisEmpty(tlink ** HTteams){
	int i;
	for(i=0; i<(SIZE*2); i++){
		if (HTteams[i] != NULL)
			return false;
	}
	return true;
}

/*liberta memoria equipa*/
void teamFree(pTeam * t){
	free(t->name);
	free(t);
}

/*liberta memoria tabela de equipas*/
void free_tTable(tlink * ttable){
	int i;
	pTeam * t;
	for(i = 0; i <= SIZE; i++){
		t = &ttable->t[i];
		if(t != NULL){
			teamFree(t);
		}
	}

	free(ttable->t);
	free(ttable);
}
