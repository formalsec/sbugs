#include "estrutura.h"
#include "funcoesprincipais.h"

int main(){
	int x = 1, n_linha = 0;
	char c;
	/*declara a hash table dos jogos*/
	jogo * heads_jogos[M_jogos];
	/*declara a hash table das equipas*/
	equipa * heads_equipas[M_jogos];
	/*declara a lista dos jogos para o comando l*/
	lista_jogo * jogos_ordenados = NULL;
	jogos_ordenados  = inic_lista();
	inic_hash_j(heads_jogos);
	inic_hash_e(heads_equipas);
	while(x){
		c = getchar();
		switch(c){
			case 'a':
				getchar();
				n_linha ++;
				cmd_a(heads_jogos, heads_equipas, n_linha, jogos_ordenados);
				break;
			case 'A':
				getchar();
				n_linha ++;
				cmd_A(heads_equipas, n_linha);
				break;
			case 'l':
				getchar();
				n_linha ++;
				cmd_l(jogos_ordenados, n_linha);
				break;
			case 'p':
				getchar();
				n_linha ++;
				cmd_p(heads_jogos, n_linha);
				break;
			case 'P':
				getchar();
				n_linha ++;
				cmd_P(heads_equipas, n_linha);
				break;
			case 'r':
				getchar();
				n_linha ++;
				cmd_r(heads_jogos, jogos_ordenados, n_linha);
				break;
			case 's':
				getchar();
				n_linha ++;
				cmd_s(heads_jogos, n_linha);
				break;
			case 'g':
				getchar();
				n_linha ++;
				cmd_g(heads_equipas, n_linha);
				break;
			case 'x':
				/*sai do ciclo*/
				x = 0;
				break;
		}
	}
	/*libertacao de memoria*/
	free_lista(jogos_ordenados);
	free_hash_e(heads_equipas);
	free_hash_j(heads_jogos);
	return 0;
}



