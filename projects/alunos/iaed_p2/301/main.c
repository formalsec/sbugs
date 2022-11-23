#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "structs.h"
#include <string.h>
#include <stdio.h>

/* Funcao principal do programa que inicializa todas as tabelas e listas, 
chama a funcao dos comandos e por fim liberta a memoria ocoupada*/

int main(){
	/*inicializacao das tabelas*/
	Hash_table *jogos = init_table(SIZE_TABLE_J);
	Hash_tableEq *equipas_t = init_tableEq(SIZE_TABLE_E);
	/*inicializacao das listas*/
	Node *head;
	NodeEq *headEq;
	head = NULL;
	headEq = NULL;
	/*funcao que controla os comandos recebidos*/
	comandos(head, jogos, equipas_t, headEq);
	/*liberta toda a memoria ocupada pelas tabelas*/
	destroyTable(jogos);
	destroyTableEq(equipas_t);
	return 0;
}