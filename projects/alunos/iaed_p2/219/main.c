#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "main.h"

int cont = 0;														/*contador das linhas de input para debug*/

int main(){
	lista_equipas *l_equipas = cria_lista_equipas();				/*inicializa a lista de equipas*/
	lista_jogos *l_jogos = cria_lista_jogos();				     	/*inicializa a lista de jogos*/
	char comando;
	Initequipa();													/*inicializa a hashtable das equipas*/
	Initjogo();														/*inicializa a hashtable dos jogos*/
	do{
		comando = le_comandos(l_equipas, l_jogos);
	}
	while(comando != 'x');

	free_equipas(l_equipas);							/*liberta a memoria da lista de equipas*/
	free_jogos(l_jogos);								/*liberta a memoria da lista de jogos*/
	ApagaHashEquipa();									/*liberta a memoria da hashtable das equipas*/
	ApagaHashJogo();                                   /*liberta a memoria da hashtable dos jogos*/
	return 0;
}

char le_comandos(lista_equipas *l_equipas, lista_jogos *l_jogos){

	char comando;
	char res[5][MAXINPUT];

	char *arg1;
	char *arg2;
	char *arg3;
	char *arg4;
	char *arg5;

	scanf("%c", &comando);	

	switch(comando){
		case 'a':
			cont++;
			scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%[^:\n]:%[^:\n]", res[0], res[1], res[2], res[3], res[4]);
		   	arg1 = res[0];
           	arg2 = res[1];
           	arg3 = res[2];
           	arg4 = res[3];
           	arg5 = res[4];
            comando_a(l_jogos, arg1, arg2, arg3, arg4, arg5);
            break;

		case 'A':
			cont++;
			scanf(" %[^:\n]:", res[0]);
		   	arg1 = res[0];
            comando_A(l_equipas, arg1);
            break;

		case 'l':
			cont++;
            comando_l(l_jogos);
            break;

		case 'p':
			cont++;
			scanf(" %[^:\n]:", res[0]);
		   	arg1 = res[0];
			comando_p(arg1);
			break;

		case 's':
			cont++;
			scanf(" %[^:\n]:%[^:\n]:%[^:\n]:", res[0], res[1], res[2]);
		   	arg1 = res[0];
			arg2 = res[1];
			arg3 = res[2];
            comando_s(arg1, arg2, arg3);
            break;

		case 'r':
			cont++;
			scanf(" %[^:\n]:", res[0]);
		   	arg1 = res[0];
			comando_r(l_jogos, arg1);
			break;

		case 'P':
			cont++;
			scanf(" %[^:\n]:", res[0]);
		   	arg1 = res[0];
			comando_P(arg1);
			break;
		case 'g':
			cont++;
			comando_g(l_equipas);
			break;
		case 'x':				
		
		default:	
			break;	
	}
	
	return comando;
}

void comando_a(lista_jogos *listaj, char *nome, char *equipa1, char *equipa2, char *score1, char *score2){
	int s1, s2;
	equipa *auxequipa;
	jogo *novo_jogo = cria_jogo();
	if (STsearchJogo(nome) == NULL){  
		if(STsearchEquipa(equipa1) !=NULL && STsearchEquipa(equipa2) != NULL){ 
			preenche_jogo(novo_jogo, nome, equipa1, equipa2, score1, score2);
			adiciona_jogo(novo_jogo, listaj);
			STinsertJogo(novo_jogo);
			sscanf(novo_jogo -> score1, "%d", &s1); 
			sscanf(novo_jogo -> score2, "%d", &s2); 
			if(s1 > s2){              /* score1 > score2, incrementamos o n de jogos ganhos da equipa1*/
				auxequipa = STsearchEquipa(equipa1);
				auxequipa -> ganhos++;  
			}
			else if(s2 > s1){         /* score2 > score1, incrementamos o n de jogos ganhos da equipa2*/
				auxequipa = STsearchEquipa(equipa2);
				auxequipa -> ganhos++;
			}
		}
		else {
			printf("%d Equipa inexistente.\n", cont);
		}
	}else{
		printf("%d Jogo existente.\n", cont);
		free(novo_jogo);
	}
}

void comando_A(lista_equipas *listae, char *nome){
	equipa *novo_equipa = cria_equipa();
	if (STsearchEquipa(nome) == NULL){  
			preenche_equipa(novo_equipa, nome);
			adiciona_equipa(novo_equipa, listae);
			STinsertEquipa(novo_equipa);
	}else{
		printf("%d Equipa existente.\n", cont);
		free(novo_equipa);
	}
}

void comando_l(lista_jogos *listaj){
	jogo *auxjogo = listaj -> last;
	while(auxjogo != NULL){
		printf("%d %s %s %s %s %s\n", cont, auxjogo -> nome, auxjogo -> equipa1, auxjogo -> equipa2, auxjogo -> score1, auxjogo -> score2);
		auxjogo = auxjogo -> jogo_anterior;
	}
}

void comando_p(char *nome){
	jogo *auxjogo;
	if(STsearchJogo(nome) != NULL){
		auxjogo = STsearchJogo(nome);
		printf("%d %s %s %s %s %s\n", cont, auxjogo -> nome, auxjogo -> equipa1, auxjogo -> equipa2, auxjogo -> score1, auxjogo -> score2);
	}
	else{
		printf("%d Jogo inexistente.\n", cont);
	}
}

void comando_P(char *nome){
	equipa *auxequipa;
	if(STsearchEquipa(nome) !=NULL){
		auxequipa = STsearchEquipa(nome);
		printf("%d %s %d\n", cont, auxequipa -> nome, auxequipa -> ganhos);
	}
	else{
		printf("%d Equipa inexistente.\n", cont);
	}
}

void comando_s(char *nome, char *novo_s1, char *novo_s2){ 
	int ant1, ant2, novo1, novo2;
	jogo *auxjogo;
	equipa *auxequipa;
	sscanf(novo_s1, "%d", &novo1); /*score1 novo*/
	sscanf(novo_s2,"%d", &novo2);  /*score2 novo*/
	if(STsearchJogo(nome) != NULL){
		auxjogo = STsearchJogo(nome);
		sscanf(auxjogo -> score1, "%d", &ant1); /*score1 antigo*/
		sscanf(auxjogo -> score2, "%d", &ant2); /*score2 antigo*/
		/*recalcular o numero de jogos ganhos de cada equipa*/
		if(ant1 > ant2){  
			if(novo2 > novo1){
				auxequipa = STsearchEquipa(auxjogo->equipa1);
				auxequipa -> ganhos--;
				auxequipa = STsearchEquipa(auxjogo->equipa2);
				auxequipa -> ganhos++;
			}
			else if(novo2 == novo1){
				auxequipa = STsearchEquipa(auxjogo->equipa1);
				auxequipa -> ganhos--;
			}
		}
		else if(ant2 > ant1){
			if(novo1 > novo2){
				auxequipa = STsearchEquipa(auxjogo->equipa2);
				auxequipa -> ganhos--;
				auxequipa = STsearchEquipa(auxjogo->equipa1);
				auxequipa -> ganhos++;
			}
			else if(novo2 == novo1){
				auxequipa = STsearchEquipa(auxjogo->equipa2);
				auxequipa -> ganhos--;
			}
		}
		else if(ant1 == ant2){
			if(novo1 > novo2){
				auxequipa = STsearchEquipa(auxjogo->equipa1);
				auxequipa -> ganhos++;
			}
			else if(novo2 > novo1){
				auxequipa = STsearchEquipa(auxjogo->equipa2);
				auxequipa -> ganhos++;
			}
		}
		free(auxjogo -> score1);
		free(auxjogo -> score2);
		auxjogo -> score1 = can_fail_malloc(sizeof(char)*strlen(novo_s1)+1);
		auxjogo -> score2 = can_fail_malloc(sizeof(char)*strlen(novo_s2)+1);
		strcpy(auxjogo -> score1, novo_s1);
		strcpy(auxjogo -> score2, novo_s2);
	}
	else{
		printf("%d Jogo inexistente.\n", cont);
	}
}

void comando_r(lista_jogos *listaj, char *nome){
	jogo *auxjogo;
	equipa *auxequipa;
	int s1, s2;
	if(STsearchJogo(nome) != NULL){
		auxjogo = STsearchJogo(nome);
		sscanf(auxjogo -> score1, "%d", &s1); 
		sscanf(auxjogo -> score2, "%d", &s2);
		/*recalcular o numero de jogos ganhos de cada equipa*/
		if(s1>s2){
			auxequipa = STsearchEquipa(auxjogo -> equipa1);
			auxequipa -> ganhos--;
		}
		else if(s2<s1){
			auxequipa = STsearchEquipa(auxjogo -> equipa2);
			auxequipa -> ganhos--;
		}
		retira_jogo(listaj, auxjogo);
		STdelete(nome);
	}
	else{
		printf("%d Jogo inexistente.\n", cont);
	}
}

int comando_g(lista_equipas *listae){ 
	equipa *auxequipa = listae -> last;
	int ganhostotal = 0;
	while(auxequipa != NULL){
		if(auxequipa -> ganhos > ganhostotal){
			ganhostotal = auxequipa -> ganhos;
		}
		auxequipa = auxequipa -> equipa_anterior;
	}
	if(listae -> num_equipas==0){
		return -1;
	}
	else{
		printf("%d Melhores %d\n", cont, ganhostotal);
	}
	aux_g(listae, ganhostotal);
	return 0;
}

void aux_g(lista_equipas *listae, int ganhostotal){
	equipa *auxequipa = listae -> last;
	while (auxequipa != NULL){
		if(auxequipa -> ganhos == ganhostotal){
			printf("%d * %s\n", cont, auxequipa -> nome);
		}
		auxequipa = auxequipa -> equipa_anterior;
	}
}


