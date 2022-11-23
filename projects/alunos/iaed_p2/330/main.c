#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "funcoes.h"

/******************************************************************************
 *
 * Comandos:
 * a - Adiciona um novo jogo.
 * A - Adiciona uma nova equipa.
 * l - Lista todos os jogos pela ordem em que foram introduzidos.
 * p - Procura um jogo.
 * P - Procura uma equipa.
 * r - Apaga um jogo.
 * s - Altera a pontuacao de um jogo.
 * g - Encontra as equipas que venceram mais jogos.
 * x - Termina o programa.
 *
 *****************************************************************************/

int main(){
	char comando = '0'; /*Cria uma variavel para servir de comando que comeca
	com algo que nunca vai ser chamado para nao dar origem a erros*/

	/*inicializacoes*/
	Equipa *cabeca_equipas = NULL; 
	Hequipas *TabEquipas = init_hashE();
	Cabeca_cauda *extremos_lista_jogos = can_fail_malloc(sizeof(Cabeca_cauda));
	Hjogos *TabJogos = init_hashJ();
	int *NL = can_fail_malloc(sizeof(int)); /*contador de numero de linhas dos comandos*/
	extremos_lista_jogos->cabeca = NULL;
	extremos_lista_jogos->cauda = NULL;
	*NL = 1;

	while (comando != 'x'){
		scanf("%c", &comando);
		if (comando == 'a'){
			a(TabEquipas, TabJogos, extremos_lista_jogos, NL);

		}
		if (comando == 'A'){
			cabeca_equipas = A(TabEquipas, cabeca_equipas, NL);

		}
		if (comando == 'l'){
			l(NL, extremos_lista_jogos);
		}
		if (comando == 'p'){
			p(TabJogos, NL);

		}
		if (comando == 'P'){
			P(TabEquipas, NL);

		}
		if (comando == 'r'){
			r(NL, TabJogos, TabEquipas, extremos_lista_jogos);
		}
		if (comando == 's'){
			s(TabEquipas, TabJogos, NL);

		}
		if (comando == 'g'){
			g(NL, cabeca_equipas);
		}
	}

	/*Liberta memoria de tudo o que tenha sido alocado*/
	free_Hequipas(TabEquipas);
	free_listaE(cabeca_equipas);
	free_Hjogos(TabJogos);
	free_listaJ(extremos_lista_jogos);
	free(NL);
	return 0;
}
