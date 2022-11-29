#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "declaracoes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

link_j *heads_j;
link_e *heads_e;
lista * ls;
int cmd, nl = 0, bol = 1;
int contador_equipa = 0;

	/*Inicializa as hashtables a NULL*/
	heads_j = can_fail_calloc(HASHTABLESIZE_J,sizeof(link_j)); 
	heads_e = can_fail_calloc(HASHTABLESIZE_E,sizeof(link_e));
	
	/*Inicializa a lista duplamente ligada a NULL*/
	ls = cria_lista();

	while(bol){

		cmd = getchar();
		nl++;

		switch(cmd){
			case 'a':		
				adiciona_novo_jogo(ls, heads_j, heads_e, nl);
				break;
			case 'A':				
				adiciona_nova_equipa(heads_e , &contador_equipa, nl);
				break;
			case 'l':				
				lista_jogos(ls, nl);
				break;
			case 'p':			
				proucura_jogo(heads_j, nl);
				break;
			case 'P':				
				procura_equipa(heads_e, nl);
				break;
			case 'r':			
				apaga_jogo(heads_j, heads_e, ls, nl);
				break;
			case 's':				
				altera_score(heads_j, heads_e, nl);
				break;
			case 'g':
				equipa_vitorias(heads_e, &contador_equipa, nl);
				break;
			case 'x':
				bol = 0;
				break;
			default:
				le_lixo();
				break;			
		}
	}

	limpa_ht_jogos(heads_j);/*Limpa a hashtable dos jogos*/
	limpa_ht_equipas(heads_e);/*Limpa a hashtable das equipas*/
	limpa_lista_ligada(ls); /*Limpa a lista dupamente ligada*/

	return 0;
}


