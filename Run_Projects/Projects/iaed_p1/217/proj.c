#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(){

	char command;
	int preco, peso, qtd, idp, ide;
	char desc[MAX_DESC];

	while(1){
		command = getchar();
		

		switch(command) {
			
			case 'a':
				getchar();				
				scanf("%[^:]:%d:%d:%d", desc, &preco, &peso, &qtd);
				a(desc, preco, peso, qtd);
			break;
			case 'q':
				getchar();
				scanf("%d:%d", &idp, &qtd);
				q(idp, qtd);
			break;
			case 'N':
				getchar();
				N();
			break;
			case 'A':
				getchar();
				scanf("%d:%d:%d", &ide, &idp, &qtd);
				A(ide, idp, qtd);
			break;
			case 'r':			
				getchar();
				scanf("%d:%d", &idp, &qtd);
				r(idp, qtd);
			break;
			case 'R':
				getchar();
				scanf("%d:%d", &ide, &idp);
				R(ide, idp);
			break;
			case 'C':
				getchar();
				scanf("%d", &ide);
				C(ide);
			break;
			case 'p':
				getchar();
				scanf("%d:%d", &idp, &preco);
				p(idp, preco);
			break;
			case 'E':
				getchar();
				scanf("%d:%d", &ide, &idp);
				E(ide, idp);
			break;
			case 'm':
				getchar();
				scanf("%d", &idp);
				m(idp);
			break;
			case 'l':
				getchar();
				l();	
			break;
			case 'L':
				getchar();
				scanf("%d", &ide);
				L(ide);
			break;
			case 'x':
				return EXIT_SUCCESS; 
		}
	}
	return EXIT_FAILURE;
}