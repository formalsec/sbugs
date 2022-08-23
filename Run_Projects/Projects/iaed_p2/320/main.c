#include <stdio.h>
#include "games.h"
#include "teams.h"

void comand_a(int nl, dlist_games ** hasht_g, dlist_teams ** hasht_t, dlist_games * dl_g);
void comand_A(int nl, dlist_teams ** hasht_t);
void comand_l(int nl, dlist_games * dl_g);
void comand_p(int nl, dlist_games ** hasht_g);
void comand_P(int nl, dlist_teams ** hasht_t);
void comand_r(int nl, dlist_games ** hasht_g, dlist_teams ** hasht_t, dlist_games * dl_g);
void comand_s(int nl, dlist_games ** hasht_g, dlist_teams ** hasht_t);
void comand_g(int nl, dlist_teams ** hasht_t);

/* le o input e executa o comando correspondente */
int main(){
	int nl = 0;						/* numero da linha que originou o output */
	char comand;					/* primeiro caracter do input */
	dlist_games ** hasht_g = NULL;	/* hashtable dos jogos */
	dlist_teams ** hasht_t = NULL;	/* hashtable das equipas */
	dlist_games * dl_g = NULL;		/* lista duplamente ligada ordenada dos jogos */
	hasht_g = init_hasht_games();	/* inicializa as estruturas declaradas anteriormente */
	hasht_t = init_hasht_teams();
 	dl_g = init_dlist_games();
	while(1){
		scanf("%c", &comand);
		if(comand != '\n'){
			nl++;
			switch(comand){
				case 'a':
					comand_a(nl, hasht_g, hasht_t, dl_g);
				break;
				case 'A':
					comand_A(nl, hasht_t);
				break;
				case 'l':
					comand_l(nl, dl_g);
				break;
				case 'p':
					comand_p(nl, hasht_g);
				break;
				case 'P':
					comand_P(nl, hasht_t);
				break;
				case 'r':
					comand_r(nl, hasht_g, hasht_t, dl_g);
				break;
				case 's':
					comand_s(nl, hasht_g, hasht_t);
				break;
				case 'g':
					comand_g(nl, hasht_t);
				break;
				case 'x':
					free_games(hasht_g, dl_g);	/* free hashtable e lista ordenada dos jogos */
					free_teams(hasht_t);		/* free hashtable das equipas */
					return 0;
			}
		}
	}
}