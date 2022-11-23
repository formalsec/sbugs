#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JOGO.h"  /* Ficheiro que contem as funcoes que gerem os jogos */


/* Funcao main, funciona como selecionador de operacoes utilizando 
um switch case para todas as funcoes pedidas no enunciado. */

int main()
{
	char buffer[MAX];
	char funcao;
	int running = 1, n = 1;
	list* lista;
	equipaHash** equipaTable;
	lista = mk_list();
	equipaTable = criaEquipaHash();

	while (running == 1) {
		funcao = getchar();
		switch(funcao) {
			case 'a':
				getchar();
				fgets(buffer, MAX, stdin);
				lista = adicionaJogo(lista, equipaTable, buffer, n);
				n += 1;
				break;
			case 'A':
				getchar();
				fgets(buffer, MAX, stdin);
				adicionaEquipa(equipaTable, buffer, n);
				n += 1;
				break;
			case 'l':
				listaJogos(lista, n);
				n += 1;
				break;
			case 'p':
				getchar();
				fgets(buffer, MAX, stdin);
				procuraJogo(lista, buffer, n);
				n += 1;
				break;
			case 'P':
				getchar();
				fgets(buffer, MAX, stdin);
				procuraEquipa(equipaTable, buffer, n);
				n += 1;
				break;
			case 'r':
				getchar();
				fgets(buffer, MAX, stdin);
				lista = apagarJogo(lista, equipaTable, buffer, n);
				n += 1;
				break;
			case 's':
				getchar();
				fgets(buffer, MAX, stdin);
				lista = alteraResultado(lista, equipaTable, buffer, n);
				n += 1;
				break;
			case 'g':
				melhoresEquipas(equipaTable, n);
				n += 1;
				break;
			case 'x':
				running = 0;
				freeLista(lista);
				freeEquipaHash(equipaTable);
				break;
		}
	}
	return 0;
}

