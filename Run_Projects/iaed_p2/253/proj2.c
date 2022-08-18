#include "TABELA_HASH_E.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char comando=' '; 							  /* Inicializacao da variavel que le o comando */
	int contador=0;

	listE *lista_equipas = cria_listE();		  /* Linked lists */
	listJogos *lista_jogos = cria_listJogos();
	Tabela_hash *tabela = cria_tabela_hash();	  /* Tabela das equipas */
	Tabela_hash *calendario = cria_tabela_hash(); /* Calendario remete para o 
													calendario de jogos (jogos que decorreram)*/

	while(comando != EOF && comando != 'x')
	{
		scanf("%c", &comando);
		switch(comando)
		{	
			case 'a':
			adiciona_jogo(lista_jogos, calendario, tabela, ++contador);
			break;

			case 'l':
			lista_todos_jogos(lista_jogos, ++contador);
			break;

			case 'p':
			procura_jogo(calendario, ++contador);
			break;

			case 'r':
			apaga_jogo(calendario,tabela, lista_jogos, ++contador);
			break;

			case 's':
			altera_resultado(calendario, tabela, ++contador);
			break;

			case 'A':
			adiciona_equipa(lista_equipas, tabela, ++contador);
			break;

			case 'P':
			procura_equipa(tabela, ++contador);
			break;

			case 'g':
			vencedores(lista_equipas, ++contador);
			break;
		}
	}
	/* Liberta toda a memoria alocada */
	free_list(lista_equipas);			
	free_listJ(lista_jogos);
	free_tabela_hash(tabela);
	free_tabela_hash(calendario);

	return 0;
}
