#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNOME 1023 
#define MAX_COMANDO 4098
#define HASH_SIZE 503


/* estruturas*/
typedef struct equipaHash{
	struct Equipa *dados;
}equipaHash;


typedef struct Equipa{
	char name[MAXNOME];
	int jogosGanhos;
    struct Equipa *next;
}Equipa;



typedef struct jogoHash{
	struct jogo *jogoH;
}jogoHash;


typedef struct jogo{
	char nome[MAXNOME];
	struct Equipa *equipa1;
	struct Equipa *equipa2;
	int result1;
	int result2;
	struct jogo *next;
}jogo;

/*inicializacao das hastables*/
equipaHash teams[HASH_SIZE];
jogoHash games[HASH_SIZE];
jogoHash ordenados[1];
/*NL*/
int NL;

void init(){
	/*inicializacao das linked lists em cada indice da hashtable*/
	int i;
	for(i = 0 ; i < HASH_SIZE; i++){
		teams[i].dados = NULL;
		games[i].jogoH = NULL;
	}
	ordenados[0].jogoH = NULL;
}

int hashKey(char key) {
	/*funcao que retorna o indice da hastable*/
   return key % HASH_SIZE;
}

Equipa* findPointerEquipa(char args[]){
	/*funcao que returna o ponteiro para uma equipa*/
	int key;
	Equipa *temp;

	key = hashKey(args[0]);
	temp = teams[key].dados;

	/*loop que percorre todos os elementos*/
	while(temp != NULL){
		if(!strcmp(temp->name, args)){
			return temp;
		}
		temp = temp->next;
	}
	return 	NULL;
}

jogo* findPointerJogo(char args[]){
	/*funcao que percorre a hastable dos jogos e devolve um ponteiro para o jogo*/
	int key;
	jogo *temp;

	key = hashKey(args[0]);
	temp = games[key].jogoH;

	while(temp != NULL){
		if(!strcmp(temp->nome, args)){
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

void adicionaEquipa(char args[]){
	/*funcao que adiciona uma equipa*/
	char nome[MAXNOME];
	int key;
	Equipa *temp, *prev;
	strcpy(nome, args);
	
	key = hashKey(nome[0]);
	temp = teams[key].dados;
	/*se o primeiro elemento for null*/
	if(temp == NULL){
		teams[key].dados = can_fail_malloc(sizeof(Equipa));
		temp = teams[key].dados;
		strcpy(temp->name,nome);
		temp->next = NULL;
		temp->jogosGanhos = 0;
		NL+=1;
		return; 
	}
	/*enquanto nao se chegar ao ultimo elemento verificar se ja existe*/
	while(temp != NULL){
		if(!strcmp(temp->name, nome)){
			printf("%d Equipa existente.\n",NL);
			NL+=1;
			return;
		}
		/*prev guarda o ultimo elemento existente*/
		prev = temp;
		temp = temp->next;
	}
	prev->next = can_fail_malloc(sizeof(Equipa));
	strcpy(prev->next->name,nome);
	prev->next->jogosGanhos = 0; 
	prev->next->next = NULL;
	NL+=1;
	return;
}
void addOrdenados(char nome[MAXNOME],char equipa1[MAXNOME], char equipa2[MAXNOME],int res1,int res2 ){
	jogo *temp, *prev;
	Equipa *etemp1;
	Equipa *etemp2;
	

	etemp1 = findPointerEquipa(equipa1);
	etemp2 = findPointerEquipa(equipa2);

	temp = ordenados[0].jogoH;
	if (temp == NULL){
		ordenados[0].jogoH = can_fail_malloc(sizeof(jogo));
		temp = ordenados[0].jogoH;
		strcpy(temp->nome, nome);
		temp->equipa1 = etemp1;
		temp->equipa2 = etemp2;
		temp->result1 = res1;
		temp->result2 = res2;
		temp->next =NULL;
		return;
	}
	while(temp != NULL){
		prev = temp;
		temp = temp->next;
	}
	prev->next = can_fail_malloc(sizeof(jogo));
	strcpy(prev->next->nome, nome);
	prev->next->equipa1 = etemp1;
	prev->next->equipa2 = etemp2;
	prev->next->result1 = res1;
	prev->next->result2 = res2;
	prev->next->next = NULL;
	return;

}

void adicionaJogo(char args[]){
	char equipa1[MAXNOME], equipa2[MAXNOME], nome[MAXNOME], delim[2], *token;
	int res1, res2, key;
	jogo *temp, *prev;
	Equipa *etemp1;
	Equipa *etemp2;
	strcpy(delim,":");

	token = strtok(args, delim);
	strcpy(nome, token);
	token = strtok(NULL, delim);
	strcpy(equipa1, token);
	token = strtok(NULL, delim);
	strcpy(equipa2, token);
	res1 = atoi(strtok(NULL, delim));
	res2 = atoi(strtok(NULL, delim));

	

	key = hashKey(nome[0]);

	temp = games[key].jogoH;

	if(temp == NULL){
		etemp1 = findPointerEquipa(equipa1);
		etemp2 = findPointerEquipa(equipa2);

		if(etemp1 == NULL || etemp2 == NULL){
			printf("%d Equipa inexistente.\n",NL);
			NL+=1;
			return;
		}

		games[key].jogoH = can_fail_malloc(sizeof(jogo));
		temp = games[key].jogoH;
		strcpy(temp->nome, nome);
		temp->equipa1 = etemp1;
		temp->equipa2 = etemp2;
		temp->result1 = res1;
		temp->result2 = res2;
		temp->next =NULL;

		if (res1 > res2){
			etemp1->jogosGanhos +=1;
		}
		if (res2 > res1){
			etemp2->jogosGanhos +=1;
		}
		NL+=1;
		addOrdenados(nome, equipa1, equipa2, res1, res2);
		return;
	}

	while(temp != NULL){
		if(!strcmp(temp->nome, nome)){
			printf("%d Jogo existente.\n",NL);
			NL+=1;
			return;
		}
		prev = temp;
		temp = temp->next;
	}
	
	etemp1 = findPointerEquipa(equipa1);
	etemp2 = findPointerEquipa(equipa2);

	if(etemp1 == NULL || etemp2 == NULL){
		printf("%d Equipa inexistente.\n",NL);
		NL+=1;
		return;
	}

	prev->next = can_fail_malloc(sizeof(jogo));
	strcpy(prev->next->nome, nome);
	prev->next->equipa1 = etemp1;
	prev->next->equipa2 = etemp2;
	prev->next->result1 = res1;
	prev->next->result2 = res2;
	if (res1 > res2){
		etemp1->jogosGanhos +=1;
	}
	if (res2 > res1){
		etemp2->jogosGanhos +=1;
	}
	prev->next->next = NULL;
	NL+=1;
	addOrdenados(nome, equipa1, equipa2, res1, res2);
	return;
}
 
void procuraJogo(char args[]){
	int key;
	jogo *temp;

	key = hashKey(args[0]);
	temp = games[key].jogoH;

	while (temp != NULL){
		if (!strcmp(temp->nome, args)){
			printf("%d %s %s %s %d %d\n",NL ,temp->nome, temp->equipa1->name, temp->equipa2->name, temp->result1, temp->result2);
			NL+=1;
			return;
		}
		temp = temp->next;
	}
	printf("%d Jogo inexistente.\n",NL);
	NL+=1;
	return;
}


void procuraEquipa(char args[]){
	int key;
	Equipa *temp;

	key = hashKey(args[0]);
	temp = teams[key].dados;
	while (temp != NULL){
		if(!strcmp(temp->name, args)){
			printf("%d %s %d\n",NL, temp->name, temp->jogosGanhos);
			NL+=1;
			return;
		}
		temp = temp->next;
	}
	printf("%d Equipa inexistente.\n", NL);
	NL+=1;
	return;
}




void listaJogos(){
	jogo *temp;
	temp = ordenados[0].jogoH;
	while(temp != NULL){
		printf("%d %s %s %s %d %d\n", NL, temp->nome, temp->equipa1->name, temp->equipa2->name, temp->result1, temp->result2);
		temp = temp->next;
	}
	NL+=1;
	return;
}

void alteraScore(char args[]){
	char nome[MAXNOME], *token, delim[2];
	int res1, res2, oldRes1, oldRes2;
	jogo *temp;
	/*parsing dos argumentos*/
	strcpy(delim,":");
	token = strtok(args,delim);
	strcpy(nome, token);
	res1 = atoi(strtok(NULL,delim));
	res2 = atoi(strtok(NULL,delim));

	temp = findPointerJogo(nome);
	
	if(temp == NULL){
		printf("%d Jogo inexistente.\n", NL);
		NL+=1;
		return;
	}

	oldRes1 = temp->result1;
	oldRes2 = temp->result2;
	temp->result1= res1;
	temp->result2 = res2;
	/*verificar todas as condicoes para mudar as vitorias*/
	if(res1 > res2 && oldRes1<oldRes2){
		temp->equipa1->jogosGanhos +=1;
		temp->equipa2->jogosGanhos -=1;
	}	
	if( res1<res2 && oldRes1>oldRes2){
		temp->equipa2->jogosGanhos +=1; 
		temp->equipa1->jogosGanhos -=1;

	}
	if(res1 == res2 && oldRes1<oldRes2){
		temp->equipa2->jogosGanhos -=1;
	}
	if(res1 == res2 && oldRes1>oldRes2){
		temp->equipa1->jogosGanhos -=1;
	}
	if(res1 > res2 && oldRes1==oldRes2){
		temp->equipa1->jogosGanhos -=1;
	}	
	if( res1<res2 && oldRes1==oldRes2){
		temp->equipa2->jogosGanhos -=1; 
	}
	NL+=1;
	return;
}

void apagaJogo(char args[]){
	char nome[MAXNOME];
	jogo *temp;
	jogo *prev;
	int key;

	sscanf(args, "%s", nome);

	key = hashKey(nome[0]);
	temp = games[key].jogoH;
	prev = games[key].jogoH;

	if(temp == NULL){
		printf("%d Jogo inexistente.\n",NL);
		NL+=1;
		return;	
	}

	if(!strcmp(temp->nome, nome)){
		if(temp->result1 > temp->result2){
			temp->equipa1->jogosGanhos -=1;
		}
		if(temp->result1 < temp->result2){
			temp->equipa2->jogosGanhos -=1;
		}
		games[key].jogoH = temp->next;
		free(temp);
		NL+=1;
		return;
	}

	while(temp != NULL){
		if(!strcmp(temp->nome, nome)){
			if(temp->result1 > temp->result2){
				temp->equipa1->jogosGanhos -=1;
			}
			if(temp->result1 < temp->result2) {
				temp->equipa2->jogosGanhos -=1;
			}
			prev->next = temp->next;
			free(temp);
			NL+=1;
			return;
		}
		prev = temp;
		temp = temp->next;
	}
	printf("%d Jogo inexistente.\n",NL);
	NL+=1;
	return;
}


void maiorVictoria(){
	Equipa *temp;
	char **sort;
	char *tmp;
	int i, j, max, counter, permCounter;
	max = -1;
	counter = 0;
	for (i = 0 ;i < HASH_SIZE; i++){
		temp = teams[i].dados;
		while(temp != NULL){
			if(temp->jogosGanhos == max){
				counter +=1;
			}
			if(temp->jogosGanhos > max){
				max = temp->jogosGanhos;
				counter = 1;
			}
			temp = temp->next;
		}
	}
	sort= can_fail_malloc(counter * sizeof(char*));
	permCounter = counter;
	counter = 0;
	for (i=0; i < HASH_SIZE; i++){
		temp = teams[i].dados;
		while(temp != NULL){
			if(temp->jogosGanhos == max){
				sort[counter]= can_fail_malloc(MAXNOME* sizeof(char));
				strcpy(sort[counter], temp->name);
				counter +=1;
			}
			temp = temp->next;
		}
	}
	tmp = can_fail_malloc(MAXNOME);
	for(i = 0; i < permCounter -1 ; i++){
		for(j=i+1;j < permCounter; j++){
			if(strcmp(sort[i],sort[j])>0){
				strcpy(tmp, sort[i]);
				strcpy(sort[i], sort[j]);
				strcpy(sort[j], tmp);
			}
		}

	}
	free(tmp);
	printf("%d Melhores %d\n",NL, max);
	for(i=0; i < permCounter; i++){
		printf("%d * %s\n",NL ,sort[i]);
	}
	for(i=0; i<permCounter; i++){
		free(sort[i]);
	}
	free(sort);
	NL+=1;
	return;
}

void freeAll(){
	int i;
	Equipa *temp, *prev;
	jogo *tmp, *prv, *ordtemp, *ordprev;
	for (i = 0 ;i < HASH_SIZE; i++){
		temp = teams[i].dados;
		while(temp != NULL){
			prev = temp;
			temp = temp->next;
			free(prev);
		}
	}
	for (i = 0 ;i < HASH_SIZE; i++){
		tmp = games[i].jogoH;
		while(tmp != NULL){
			prv = tmp;
			tmp = tmp->next;
			free(prv);
		}
	}
	ordtemp = ordenados[0].jogoH;
	while(ordtemp != NULL){
		ordprev = ordtemp;
		ordtemp = ordtemp->next;
		free(ordprev);
	}
	return;
}



int main(){
	char cmd[MAX_COMANDO];
	char letra;
	char args[MAX_COMANDO - 2];
	NL = 1;

	init();
	while(1){
		/*dividir o comando entre i indicador de comando e os dados de entrada*/
		fgets(cmd, MAX_COMANDO, stdin);
		sscanf(cmd,"%c %[^\n]s", &letra, args);
		switch (letra){

			case 'a':
				adicionaJogo(args);
			break;

			case 'A':
				adicionaEquipa(args);
			break;

			case 'l':
				listaJogos();
			break;

			case 'p':
				procuraJogo(args);
			break;

			case 'P':
				procuraEquipa(args);
			break;

			case 'r':
				apagaJogo(args);
			break;

			case 's':
				alteraScore(args); 
			break;

			case 'g':
				maiorVictoria();
			break;

			case 'x':
				freeAll();
				return 0;
			break;

		}
	}
	return 0;
}