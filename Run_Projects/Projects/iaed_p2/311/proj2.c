#include "hash.h"
#include "equipa.h"
#include "jogo.h"
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char c; /* identifica o comando pedido */
	int contador = 0; /* o que e descrito no enunciado por NL, a linha do comando pedido */

	int max_wins = 0, flag;	/* max_wins regista o as vitorias maximas da(s) equipa(s) vencedora(s),
	flag da informacao para alterar a lista vencedores (os estados estao definidos em "funcoes.h")*/

	Equipa new_winner; /* em caso da flag ADD ou NOVO e guardado nesta 
	variavel a equipa que provocou a alteracao */

	link_J lista_jogos = NULL; /* lista que mantem os jogos em ordem, para ser usada no comando l*/
	link_E vencedores = NULL; /* lista que regista as equipas com mais vitorias */
	hashJ jogos = inicia_hash_jogo(TAM_HASH); /* hashtable que contem todos os jogos */
	hashE equipas = inicia_hash_equipa(TAM_HASH); /* hashtable que contem todas as equipas */

	while((c = getchar()) != 'x'){

		flag = NADA;

		switch(c){
			case 'a':
				addJ(jogos, equipas, &lista_jogos, ++contador, &max_wins, &flag, &new_winner);
				break;
			case 'l':
				print_lista_jogos(lista_jogos, ++contador);
				break;
			case 'p':
				procura_jogo(jogos, ++contador);
				break;
			case 'r':
				apaga_jogo(jogos, equipas, &lista_jogos, &vencedores, ++contador, &flag);
				break;
			case 's':
				alt_score(jogos, equipas, &vencedores, &new_winner, ++contador, &flag, &max_wins);
				break;
			case 'A':
				add_equipa(equipas, &new_winner, max_wins, &flag, ++contador);
				break;
			case 'P':
				procura_equipa(equipas, ++contador);
				break;
			case 'g':
				champions(vencedores, max_wins, ++contador);
				break;


			/*debug*/
			case 'L':
				print_hash_equipas(equipas, max_wins);
				break;
			case 'K':
				print_hash_jogos(jogos);
				break;
		}

		atualiza_winner(equipas, &vencedores, new_winner, flag, &max_wins);
	}

	free_listaJ(lista_jogos);
	free_hashJ(jogos, TAM_HASH);
	free_nodesE(vencedores);
	free_hashE(equipas, TAM_HASH);

	return 0;
}