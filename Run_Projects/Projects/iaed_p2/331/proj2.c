#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comandos.h"
#define M_HASH 1931  /*tamanho das hash tables*/
#define MAX_CAR 1024 /*tamanho maximo de uma string com o nome de um jogo/equipa */


int main(){
	char comando, str1[MAX_CAR], str2[MAX_CAR], str3[MAX_CAR];
	int int1, int2, NL = 1;
	/*lista duplamente ligada com os nomes dos jogos introduzidos, pela ordem que o foram*/
	List_Names * jogos_introduzidos; 
	ht_games hash_t_jogos; /*hash table com os jogos*/
	ht_teams hash_t_eq; /*hash table com as equipas*/
	jogos_introduzidos = init_list_n();
	hash_t_jogos = init_ht_g(M_HASH);
	hash_t_eq = init_ht_t(M_HASH);
	scanf("%c", &comando); 
	/*o programa termina quando o comando for igual 'x'*/
	while (comando != 'x'){
		switch(comando){
			/*adicionar um novo jogo*/
			case 'a':
				scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", str1, str2, str3, &int1, &int2);
				cmd_a(NL, str1, str2, str3, int1, int2, hash_t_jogos, hash_t_eq, jogos_introduzidos);
				NL++;
				break;
			/*listar todos os jogos pela ordem em que foram introduzidos*/
			case 'l':
				cmd_l(NL, jogos_introduzidos, hash_t_jogos);
				NL ++;
				break;
			/*procurar um jogo*/
			case 'p':
				scanf(" %[^:\n]", str1);
				cmd_p(NL, str1, hash_t_jogos);
				NL++;
				break;
			/*apagar um jogo*/
			case 'r':
				scanf(" %[^:\n]", str1);
				cmd_r(NL, str1, hash_t_jogos, jogos_introduzidos, hash_t_eq);
				NL++;
				break;
			/*alterar a pontuacao de um jogo*/
			case 's':
				scanf(" %[^:\n]:%d:%d", str1, &int1, &int2);
				cmd_s(NL, str1, int1, int2, hash_t_jogos, hash_t_eq);
				NL++;
				break;
			/*adicionar uma nova equipa*/
			case 'A':
				scanf(" %[^:\n]", str1);
				cmd_A(NL, str1, hash_t_eq);
				NL++;
				break;
			/*procurar uma equipa*/
			case 'P':
				scanf(" %[^:\n]", str1);
				cmd_P(NL, str1, hash_t_eq);
				NL++;
				break;
			/*encontrar as equipas que venceram mais jogos*/
			case 'g':
				cmd_g(NL, hash_t_eq);
				NL++;
				break;
		}
		scanf("\n %c", &comando); 
	}
	free_all_names(jogos_introduzidos);
	destroy_ht_g(hash_t_jogos);
	destroy_ht_t(hash_t_eq);
	return 0;
}
