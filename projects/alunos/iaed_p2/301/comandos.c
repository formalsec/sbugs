#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "structs.h"
#include <stdio.h>

/*funcao que invoca as funcoes respetivas dos comandos*/
void comandos(Node *head, Hash_table *jogosT, Hash_tableEq *equipasT, NodeEq *headEq){
	/* nl - contador de linhas
	*/
	int nl = 0;
	Node *next;
	NodeEq *nextEq;
	while(1){
		/*menu de comandos da gestao de jogos e equipas*/
		char c;
		switch(c=getchar()){
			/*adiciona novo jogo*/
			case 'a':
				nl++;
				head = adicionaJogo(head, jogosT, equipasT, nl);
				break;
			/*lista jogos*/
			case 'l':
				nl++;
				listaJogos(head, nl);
				break;
			/*procura um jogo*/
			case 'p':
				nl++;
				procuraJogo(jogosT, nl);
				break;
			/*remove um jogo*/
			case 'r':
				nl++;
				head = removeJogo(jogosT, equipasT, head, nl);
				break;
			/*altera o score de um jogo*/
			case 's':
				nl++;
				alteraScore(jogosT, equipasT, nl);
				break;
			/*adiciona uma nova equipa*/
			case 'A':
				nl++;
				headEq = adicionaEquipas(headEq, equipasT, nl);
				break;
			/*procura uma equipa*/
			case 'P':
				nl++;
				procuraEquipa(equipasT, nl);
				break;
			/*mostra uma tabela com os vencedores*/
			case 'g':
				nl++;
				listaVencedores(equipasT, nl);
				break;
			/*imprime tabela de jogos*/
			case 't':
				printTable(jogosT);
				break;
			/*imprime tabela de equipas*/
			case 'e':
				printTableEq(equipasT);
				break;
			/*lista as equipas com as suas vitorias*/
			case 'c':
				listaEquipas(headEq);
				break;
			/*termina o programa*/
			case 'x':
			/*liberta a memoria ocupada pelas listas ligadas*/
				while(head != NULL){
					if(head->nome){
						free(head->nome);
						free(head->equipa1);
						free(head->equipa2);
					}
					next = head->next;
					free(head);
					head = next;
				}
				while(headEq != NULL){
					free(headEq->nome);
					nextEq = headEq->next;
					free(headEq);
					headEq = nextEq;
				}
				return;
			case '\n':
				break;
			default:
				nl++;
				printf("Este comando nao existe.\n");
				break;
		}
	}
}