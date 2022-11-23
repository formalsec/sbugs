#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proj2.h"
#define MAX_NOME 1024
#define MAX_INPUT 1605
#define MAX_RESULT 3

char input[MAX_NOME];
int i = 0;
int j = 0;
int a = 0;
int contador=0;

/*Prototipos*/

void AdicionaJogo();
void AdicionaEquipa();
void ListaJogos();
int  ProcuraJogo();
int ProcuraEquipa();
void ApagaJogo();
void AlteraPontuacao();
void EncontraVencedor();
Equipa lookup(Equipa equipa, char* nome );
Jogo lookup_jogo(Jogo jogo, char* nome );
Equipa verifica(Equipa equipa, char* nome );
int isEmpty( Equipa equipa );
void ListaEquipas();
Equipa troca(Equipa equipa1, Equipa equipa2);
Equipa Ordena(Equipa equipa);
Equipa libertaequipas();
Jogo libertajogos();
Jogo verifica_jogos(Jogo jogo, char* nome);


/*Funcao main*/

int main(){
	char comando;

	while(1)
	{
		scanf("%c",&comando);

		switch (comando){
			case 'a':
				contador++;
				AdicionaJogo();
				break;
			case 'A':
				contador++;
				AdicionaEquipa();
				break;
			case 'l':
				contador++;
				ListaJogos();
				break;
			case 'p':
				contador++;	
				ProcuraJogo();
				break;
			case 'P':
				contador++;
				ProcuraEquipa();
				break;
			case 'r':
				contador++;
				ApagaJogo();
				break;
			case 's':
				contador++;
				AlteraPontuacao();
				break;
			case 'g':
				contador++;
				EncontraVencedor();
				break;
			case 'L':
				contador++;
				ListaEquipas();
				break;	
			case 'x':
			libertajogos();
			libertaequipas();		
				return 0;
		}
	}

	return 0;
}

/* Comando a*/
/*Funcao que adiciona um jogo a lista ligada de jogos, caso nao existam jogos com o mesmo nome e ambas as equipas estejam presentes na lista das equipas*/
void AdicionaJogo(){

	char novo_nome[MAX_NOME];
	char nova_equipa1[MAX_NOME];
	char nova_equipa2[MAX_NOME];
	char novo_score1[3];
	char novo_score2[4];
	int nscore1;
	int nscore2;
	char* token;
	getchar();
	fgets(input,MAX_INPUT,stdin);

	token = strtok(input,":");
	strcpy(novo_nome,token);


	lookup_jogo(jogo,novo_nome);
	if(i==1){
		i=0;
		return;
	}
	
	token = strtok(NULL,":");
	strcpy(nova_equipa1,token);


	if(isEmpty(equipa)!=0){
		verifica(equipa,nova_equipa1);
		if(j!=2){
			printf("%d Equipa inexistente.\n",contador);
			return;
		}
		else{
			j=0;
		}
	}
	else{
		printf("%d Equipa inexistente.\n",contador);
		return;
	}

		

	token = strtok(NULL,":");
	strcpy(nova_equipa2,token);
/*	printf("%s\n",nova_equipa2);*/

	verifica(equipa,nova_equipa2);
	if(j!=2){
		printf("%d Equipa inexistente.\n",contador);
		return;
	}
	else{
		j=0;
	}

	

	token = strtok(NULL,":");
	strcpy(novo_score1,token);


	token = strtok(NULL,":");
	strcpy(novo_score2,token);


	


	novojogo = (Jogo)can_fail_malloc(sizeof(struct node_jogos));

	if (jogo == NULL){
		jogo = jogoatual = novojogo;
	}
	else
	{
		jogoatual = jogo;
		while (jogoatual->next != NULL)
		{
			jogoatual = jogoatual->next;	
		}
		jogoatual->next = novojogo;
		jogoatual = novojogo;
	}


    strcpy(novojogo->nome,novo_nome);



	strcpy(novojogo->equipa1,nova_equipa1);



	strcpy(novojogo->equipa2,nova_equipa2);



	strcpy(novojogo->score1,novo_score1);
	nscore1 = atoi(novojogo->score1);




	strcpy(novojogo->score2,novo_score2);
	nscore2 = atoi(novojogo->score2);





	if (nscore1>nscore2)
	{
		equipaatual = equipa;
		while (equipaatual != NULL)
		{
			if (strcmp(equipaatual->nome,novojogo->equipa1) == 0){
				equipaatual->vitorias+=1;
				break;
			}
			else
			{
			equipaatual = equipaatual -> next;
			}		
		}	
	}
	else if(nscore2>nscore1)
	{
		equipaatual = equipa;
		while (equipaatual != NULL)
		{
			if (strcmp(equipaatual->nome,novojogo->equipa2) == 0){
				equipaatual->vitorias+=1;
				break;
			}
			else
			{	
			equipaatual = equipaatual -> next;
			}		
		}	
	}


	jogoatual->next = NULL;
}

/*Comando A*/
/*Funcao que adiciona uma equipa a lista ligada de equipas apos verificar se essa equipa ja existe ou nao na lista*/
void AdicionaEquipa(){
	char novo_nome[MAX_NOME];
	char* token;
	getchar();
	fgets(input,MAX_INPUT,stdin);
	token = strtok(input,("\n"));
	strcpy(novo_nome,token);

	lookup(equipa,novo_nome);
	if(i==3){
		i=0;
		return;
	}
	else{

	novaequipa = (Equipa)can_fail_malloc(sizeof(struct node_equipas));

	if (equipa == NULL){
		equipa = equipaatual = novaequipa;
	}
	else
	{
		equipaatual = equipa;
		while (equipaatual->next != NULL)
		{
			equipaatual = equipaatual->next;	
		}
		equipaatual->next = novaequipa;
		equipaatual = novaequipa;
	}

	

	strcpy(novaequipa->nome,novo_nome);
	novaequipa->vitorias = 0;


	equipaatual->next = NULL;
	}

}

/*Comando L*/
/*Funcao que tem como objetivo listar todos os jogos disputados*/
void ListaJogos(){
	int nscore1;
	int nscore2;

	if (jogo != NULL) {  
		jogoatual = jogo;
		
		do {
			nscore1=atoi(jogoatual -> score1);
			nscore2=atoi(jogoatual -> score2);
			/*printf("%d %s %s %s %s %s\n",contador, jogoatual -> nome, jogoatual -> equipa1, jogoatual -> equipa2 ,jogoatual -> score1, jogoatual -> score2);*/
			printf("%d %s %s %s %d %d\n",contador, jogoatual -> nome,jogoatual -> equipa1, jogoatual -> equipa2,nscore1, nscore2);
		}
		while((jogoatual = jogoatual -> next) != NULL);
	}
}

/*Comando p*/
/*Funcao que dado um nome de um jogo, procura esse jogo e lista o, bem como os nomes das equipas participantes e resultado*/
int ProcuraJogo(){
	char novo_nome[MAX_NOME];
	char *token;


	getchar();
	fgets(input,MAX_INPUT,stdin);
	token = strtok(input,("\n"));
	strcpy(novo_nome,token);

	jogoatual = jogo;
	while (jogoatual != NULL)
	{
		if (strcmp(jogoatual->nome,novo_nome) == 0)
		{
			printf("%d %s %s %s %s %s\n",contador, jogoatual -> nome, jogoatual -> equipa1, jogoatual -> equipa2 ,jogoatual -> score1, jogoatual -> score2);
			return 0;
		}
		else
		{
			jogoatual = jogoatual -> next;
		}
	}
	printf("%d Jogo inexistente.\n",contador);
	return 1;


}

/*Comando P*/
/*Funcao que dado um nome de uma equipa lista essa equipa e o seu numero de vitorias */
int ProcuraEquipa(){
	char novo_nome[MAX_NOME];
	char *token;


	getchar();
	fgets(input,MAX_INPUT,stdin);
	token = strtok(input,("\n"));
	strcpy(novo_nome,token);

	equipaatual = equipa;

	while (equipaatual != NULL)
	{
		if (strcmp(equipaatual->nome,novo_nome) == 0)
		{
			printf("%d %s %d\n",contador, equipaatual -> nome, equipaatual->vitorias);
			return 0;/*ADICIONAR NUMERO DE VITORIAS*/
		}
		else
		{
			equipaatual = equipaatual -> next;
		}
	}
	printf("%d Equipa inexistente.\n",contador);
	return 1;

}
/*Comando r*/
/*Funcao que dado um nome de um jogo, procura se existe e caso exista apaga o jogo da lista ligada de jogos*/
void ApagaJogo(){
	char novo_nome[MAX_NOME];
	char *token;
	int oldscore1;
	int oldscore2;


	getchar();
	fgets(input,MAX_INPUT,stdin);
	token = strtok(input,("\n"));
	strcpy(novo_nome,token);

	jogoatual = jogo;
	jogoanterior = jogo;
	equipaatual = equipa;
	verifica_jogos(jogoatual,novo_nome);
	 if(a!=2)
	 {
			printf("%d Jogo inexistente.\n",contador);
			return;
	}
	else
	{
		a=0;
	}

	while (jogoatual != NULL)
	{
		if (strcmp(jogoatual->nome,novo_nome) == 0)
		{
			oldscore1 = atoi(jogoatual->score1);
			oldscore2 = atoi(jogoatual->score2);

			if(oldscore1>oldscore2){
		 		while(equipaatual!=NULL){
		 			if(strcmp(jogoatual->equipa1,equipaatual->nome)==0){
		 				equipaatual->vitorias-=1;
		 				break;
		 			}
		 			else{
		 				equipaatual = equipaatual->next;
		 			}		
		 		}
		 	}
		 	else if(oldscore2>oldscore1){
		 		while(equipaatual!=NULL){
		 			if(strcmp(jogoatual->equipa2,equipaatual->nome)==0){
		 				equipaatual->vitorias-=1;
		 				break;
		 			}
		 			else{
		 				equipaatual = equipaatual->next;
		 			}		
		 		}
		 	}

			if(jogoatual != jogo){
				jogoanterior->next = jogoatual->next;
				
			} else {
				jogo = jogo->next;
				
			}
			break;
		}
		else
		{
			jogoanterior = jogoatual;
			jogoatual = jogoatual -> next;
		}		
	}
	if(jogoatual == NULL){
		printf("%d Jogo inexistente.\n",contador);
	}
}

/*Funcao que dado o nome de um jogo e um par de inteiros, verifica se esse jogo existe e altera o resultado desse jogo*/
void AlteraPontuacao(){
	char novo_nome[MAX_NOME];
	char novo_score1[3];
	char novo_score2[4];
	char *token;
	int nscore1;
	int nscore2;
	int oldscore1;
	int oldscore2;

    getchar();
	fgets(input,MAX_INPUT,stdin);

	token = strtok(input,":");	
	strcpy(novo_nome,token);
		
  	

	token = strtok(NULL,":");
	strcpy(novo_score1,token);
/*	printf("novo_email = %s", novo_email);*/

	token = strtok(NULL,":");
	strcpy(novo_score2,token);

	 jogoatual = jogo;

	 verifica_jogos(jogoatual,novo_nome);
	 if(a!=2)
	 {
			printf("%d Jogo inexistente.\n",contador);
			return;
	}
	else
	{
		a=0;
	}
    
   	 while (jogoatual != NULL)		      
	 {

		 if (strcmp(jogoatual->nome,novo_nome) == 0)
		 {
		 	equipaatual = equipa;
		 	oldscore1 = atoi(jogoatual->score1);
		 	oldscore2 = atoi(jogoatual->score2);

		 	if(oldscore1>oldscore2){
		 		while(equipaatual!=NULL){
		 			if(strcmp(jogoatual->equipa1,equipaatual->nome)==0){
		 				equipaatual->vitorias-=1;
		 				break;
		 			}
		 			else{
		 				equipaatual = equipaatual->next;
		 			}		
		 		}
		 	}
		 	else if(oldscore2>oldscore1){
		 		while(equipaatual!=NULL){
		 			if(strcmp(jogoatual->equipa2,equipaatual->nome)==0){
		 				equipaatual->vitorias-=1;
		 				break;
		 			}
		 			else{
		 				equipaatual = equipaatual->next;
		 			}		
		 		}
		 	}

			strcpy(jogoatual->score1,novo_score1);
			strcpy(jogoatual->score2,novo_score2);
			nscore1 = atoi(jogoatual->score1);
			nscore2 = atoi(jogoatual->score2);

			if (nscore1>nscore2)
			{
				equipaatual = equipa;
				while (equipaatual != NULL)
				{
					if (strcmp(equipaatual->nome,novojogo->equipa1) == 0){
					equipaatual->vitorias+=1;
					break;
					}
					else
					{
						equipaatual = equipaatual -> next;
					}		
				}	
			}
			else if(nscore2>nscore1)
			{
				equipaatual = equipa;
				while (equipaatual != NULL)
				{
					if (strcmp(equipaatual->nome,novojogo->equipa2) == 0){
					equipaatual->vitorias+=1;
					break;
					}
					else
					{	
						equipaatual = equipaatual -> next;
					}		
				}	
			}
			break;
		 }
		 else
		 {			 
			 jogoatual = jogoatual->next;
		 }
	 }
	 if(jogoatual == NULL)
 	 {
	 	printf("%d Jogo inexistente.\n",contador);
	 }
	 
}

/*Comando g*/
/*Funcao que verifica qual a equipa que venceu mais jogos*/
void EncontraVencedor(){
	equipaatual = equipa;

	if(equipaatual == NULL){
		return;
	}


	Ordena(equipaatual);
	printf("%d Melhores %d\n", contador,equipaatual->vitorias);
	while(equipaatual!=NULL){
		
		printf("%d * %s\n",contador, equipaatual->nome);
		equipaatual = equipaatual->next;
	}

	
}

/*Funcao auxiliar usada para verificar se uma dada equipa existe na lista ligada de equipas, que e usada na funcao para adicionar equipas*/
Equipa lookup(Equipa equipa, char* nome )
{
	Equipa t;
	for(t = equipa; t != NULL; t = t->next){
		if(strcmp(t->nome, nome) == 0){
			i=3;
			printf("%d Equipa existente.\n",contador);
		}
	}
	return NULL;
}
/*Funcao auxiliar usada para verificar se um dado jogo existe na lista ligada de jogos, que e usada na funcao para adicionar jogos*/
Jogo lookup_jogo(Jogo jogo, char* nome )
{

	Jogo t;
	for(t = jogo; t != NULL; t = t->next){
		if(strcmp(t->nome, nome) == 0){
			printf("%d Jogo existente.\n",contador);
			i=1;
		}
	}
	return NULL;
	
}

Jogo verifica_jogos(Jogo jogo, char* nome)
{
	Jogo t;
	for(t = jogo; t != NULL; t = t->next){
	
		if(strcmp(t->nome, nome) == 0){
			a=2;
		}
	}
	return NULL;

}
/*Funcao auxiliar usada para verificar se uma equipa existe*/
Equipa verifica(Equipa equipa, char* nome )
{
	Equipa t;

	for(t = equipa; t != NULL; t = t->next){
		if(strcmp(t->nome, nome) == 0){
			j=2;
		}
	}
	return NULL;

}
/*Funcao usada para verificar se a lista ligada tem algum elemento*/
int isEmpty( Equipa equipa )
 {
   if( equipa )
      return 1;
   return 0;
 }

void ListaEquipas(){
	if (equipa != NULL) {  
		equipaatual = equipa; 		
		do {
			printf("%s %d\n",equipaatual -> nome,equipaatual->vitorias);
		}
		while((equipaatual = equipaatual -> next) != NULL);
	}
}

Equipa troca(Equipa equipa1, Equipa equipa2){
	
	
	Equipa tmp = equipa1;
	equipa1 = equipa2;
	equipa2 = tmp;


	return NULL;
}

Equipa Ordena(Equipa equipa){
	
	int swapped; 
    Equipa ptr1; 
    Equipa lptr = NULL; 
  
 
    if (equipa == NULL) 
        return NULL; 
    do
    { 
        swapped = 0; 
        ptr1 = equipa; 
  
        while (ptr1->next != lptr) 
        { 
            if (ptr1->vitorias < ptr1->next->vitorias) 
            {  
                troca(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
    return NULL;
}

Equipa libertaequipas(){
	equipaatual = equipa;
	while(equipaatual!=NULL){
		free(equipaatual);
		equipaatual = equipaatual->next;
	}
	return NULL;
}

Jogo libertajogos(){
	jogoatual = jogo;
	while(jogoatual!=NULL){
		free(jogoatual);
		jogoatual = jogoatual->next;
	}
	return NULL;
}
