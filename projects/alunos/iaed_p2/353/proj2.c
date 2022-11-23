#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include "comandos.h"


int main(){

	ht_equipas* ht_equipas = ht_init_equipas();
	ht_jogo *ht_jogos = ht_init();
	ll_jogos* linkedlist = NULL;

	int c,NL=1;
	
	while((c=getchar()) != 'x'){
		
		switch(c){
			
			default:
				break;

			case 'A':
				novaEquipa(ht_equipas, NL);
				NL++;
				break;

			case 'P':
				procuraEquipa(ht_equipas, NL);
				NL++;
				break;
			
			case 'a':
				novoJogo(ht_jogos, &linkedlist, ht_equipas, NL);
				NL++;
				break;
			
			case 'r':
				apagaJogo(ht_jogos, &linkedlist, ht_equipas, NL);
				NL++;
				break;

			case 's':
				alteraScore(ht_jogos, ht_equipas, NL);
				NL++;
				break;
			
			case 'p':
				procuraJogo(ht_jogos, NL);
				NL++;
				break;
			
			case 'l':
				listaJogos(linkedlist, NL);
				NL++;
				break;
			
			case 'g':
				tabScoresEquipas(ht_equipas, NL);
				NL++;
				break;
		}
	}
	/* liberta a memoria alocada da hashtable das equipas, jogos e da lista ligada dos jogos */
	free_hashtable_equipas(ht_equipas);
	free_hashtable(ht_jogos);
	deleteList(&linkedlist);
	return 0;
}


