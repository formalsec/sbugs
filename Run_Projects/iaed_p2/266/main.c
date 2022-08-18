#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h" /* Ficheiro que contem as funcoes que geram os jogos e as equipas */

int main() {
	listajogos* list = NovaListaJogos(); /* Inicializa todos os ponteiros da lista de jogos a NULL */
	listaequipas* list1 = NovaListaEquipas(); /* Inicializa todos os ponteiros da lista de equipas a NULL */
	int run = 1, score1recebido, score2recebido, comando = 0;
	char decisao, nomejogo[NOME], equipa1nome[EQUIPAS], equipa2nome[EQUIPAS], equipanome[EQUIPAS];
	
	while (run == 1) {
		scanf("%c", &decisao); /* Seleciona qual o comando a realizar */
		switch(decisao) {
			case 'a':
				comando++;
				getchar();
				scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nomejogo, equipa1nome, equipa2nome, &score1recebido, &score2recebido);
				AdicionaJogo(list, list1, nomejogo, equipa1nome, equipa2nome, score1recebido, score2recebido, comando);
				break;
			case 'A':
				comando++;
				getchar();
				scanf("%[^:\n]", equipanome);
				AdicionaEquipa(list1, equipanome, comando);
				break;
			case 'l':
				comando++;
				ListaJogos(list, comando);
				break;
			case 'p':
				comando++;
				getchar();
				scanf("%[^:\n]", nomejogo);
				ProcuraJogo(list, nomejogo, comando);
				break;
			case 'P':
				comando++;
				getchar();
				scanf("%[^:\n]", equipanome);
				ProcuraEquipa(list1, equipanome, comando);
				break;
			case 'r':
				comando++;
				getchar();
				scanf("%[^:\n]", nomejogo);
				ApagaJogo(list, list1, nomejogo, comando);
				break;
			case 's':
				comando++;
				getchar();
				scanf("%[^:\n]:%d:%d", nomejogo, &score1recebido, &score2recebido);
				AlteraScore(list, list1, nomejogo, score1recebido, score2recebido, comando);
				break;
			case 'g':
				OrdenaEquipas(list1, comando);
				break;
			case 'x':
				return 0;
				break;			
		}
	}
	return 0;
}
