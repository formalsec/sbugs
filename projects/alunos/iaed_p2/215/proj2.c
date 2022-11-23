#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_descricao 1050
#define MAX_instr 80000
#define tamanho_hash 26
#define tamanho_hash_lista 25


int id_output = 1;  /*contador do numero da linha do comando de input que originou esse output */

typedef struct Jogo {

	char nome[MAX_descricao];
	struct Equipa *equipa_1;
	struct Equipa *equipa_2;
	int score_1;
	int score_2; 
	struct Jogo *next;
	struct Jogo *prox_cron;
} Jogo;


typedef struct HashJ{
	struct Jogo *head;
} HashJ;


typedef struct Equipa {
	char nome[MAX_descricao];
	int num_vitorias;
	struct Equipa *next;
} Equipa;


typedef struct HashE{
	struct Equipa *head;
} HashE;

HashJ jogos[tamanho_hash];    /*hastable pata jogos*/
HashE equipas[tamanho_hash];  /*hastable pata equipas*/

Jogo *head_cron;
Jogo *tail_cron; 


int getchave(char argv[]){    /*encontra o pointer dependendo do argumento*/

	char letra = argv[0];

	return letra%tamanho_hash;
}


Equipa* procura_equipa(char argv[]){   /*percorre a hash que se obtem atraves da funcao anterior e verifica se o argumento com o nome da equipa existe ou nao*/

	int hash = getchave(argv);
	Equipa* x = equipas[hash].head;

	for(; x != NULL;x = x->next){
		if(!strcmp(x->nome, argv)){ 
			return x;
		}
	}
	return NULL;
}


Jogo* procura_jogo(char argv[]){      /*percorre a hash que se obtem atraves da funcao anterior e verifica se o argumento com o nome do jogo existe ou nao*/

	int hash = getchave(argv);
	Jogo* x = jogos[hash].head;

	for(; x != NULL; x = x->next){
		if(!strcmp(x->nome, argv)){ 
			return x;
		}
	}
	return NULL;
}


void adiciona_jogo(char argv[]){
	char delimt[2] = ":";	/*delimitador para o input*/

	char name[MAX_descricao];   
	Equipa* eqp_1;
	Equipa* eqp_2;
	char eqp_1_2[MAX_descricao];
	char eqp_2_2[MAX_descricao];
	char scr_1[MAX_descricao];
	char scr_2[MAX_descricao];
	int scr_1_2;
	int scr_2_2;

	Jogo* x;

	int hash;
	hash = getchave(argv);      /*encontra a hash em que a palavra se encontra*/

	x = jogos[hash].head; 

	strcpy(name ,strtok(argv, delimt));		/*repartir os diferentes dados do produto pelas variaveis atraves do delimitador*/
	strcpy(eqp_1_2 ,strtok(NULL, delimt));
	strcpy(eqp_2_2 ,strtok(NULL, delimt));
	strcpy(scr_1 ,strtok(NULL, delimt));
	strcpy(scr_2 ,strtok(NULL, delimt));

	scr_1_2 = strtol(scr_1, NULL, 10);		 /*passar o pointer para inteiro*/
	scr_2_2 = strtol(scr_2, NULL, 10);		
	
	eqp_1 = procura_equipa(eqp_1_2);          /*encontra o pointer*/
	eqp_2 = procura_equipa(eqp_2_2);

	if(!!procura_jogo(name)){  /*caso ja exista um jogo com o mesmo nome*/
		printf("%d %s\n", id_output, "Jogo existente.");
		id_output++;
		return;
	}

	if(!eqp_1){  /*caso a equipa 1 nao exista*/
		printf("%d %s\n", id_output, "Equipa inexistente."); 
		id_output++;
		return;
	}
	if(!eqp_2){  /*caso a equipa 2 nao exista*/
		printf("%d %s\n", id_output, "Equipa inexistente.");
		id_output++;
		return;
	}

    jogos[hash].head = can_fail_malloc(sizeof(struct Jogo));  /*aloca espaco para o novo membro*/
    jogos[hash].head->prox_cron = NULL;
    strcpy(jogos[hash].head->nome, name);
    jogos[hash].head->equipa_1 = eqp_1;
    jogos[hash].head->equipa_2 = eqp_2;
    jogos[hash].head->score_1 = scr_1_2;
    jogos[hash].head->score_2 = scr_2_2;
    jogos[hash].head->next = x;

    if(scr_1_2 > scr_2_2){     /*adiciona uma vitoria a equipa 1*/
        jogos[hash].head->equipa_1->num_vitorias++;      
    }
    else if(scr_1_2 < scr_2_2){      /*adiciona uma vitoria a equipa 2*/
        jogos[hash].head->equipa_2->num_vitorias++;
    }

    if(!head_cron){              /*caso nao exista head_cron cria um no inicio*/
        head_cron = jogos[hash].head;
        tail_cron = jogos[hash].head;
    }
    else{                       /*caso exista atualiza os pointers*/
        tail_cron->prox_cron = jogos[hash].head;
        tail_cron = jogos[hash].head;
    }
	
	id_output++;
}


void adiciona_equipa(char argv[]){

	Equipa* x;

	int hash;
	hash = getchave(argv);

	x = equipas[hash].head;

	if(procura_equipa(argv) != NULL){         /*caso ja exista uma equipa com o mesmo nome*/
		printf("%d %s\n", id_output, "Equipa existente.");
		id_output++;
	}

	else{
		if(!x){      /*caso inicial*/                          
			equipas[hash].head = can_fail_malloc(sizeof(struct Equipa));    /*aloca espaco para a nova equipa*/
			strcpy(equipas[hash].head->nome, argv);
			equipas[hash].head->num_vitorias = 0;
			equipas[hash].head->next = NULL;

			id_output++;

			return;
		}

		else{         /*casos restantes*/                
			x = can_fail_malloc(sizeof(struct Equipa));     /*aloca espaco para a nova equipa*/
			x->next = equipas[hash].head;
			equipas[hash].head = x;
			strcpy(x->nome, argv);
			x->num_vitorias = 0;

			id_output++;
		}
	}
}


void lista_jogos(){
	
	Jogo* temp;
	temp = head_cron;

	while (temp) {    /*percorre a ordem cronologica das equipas criadas ate ao momento*/
		printf("%d %s %s %s %d %d\n", id_output, temp->nome, temp->equipa_1->nome, temp->equipa_2->nome, temp->score_1, temp->score_2);
		temp = temp->prox_cron;
	}

	id_output++;
}

void procura_jogos(char argv[]){  

	char* name; 
	char eqp_1[MAX_descricao];
	char eqp_2[MAX_descricao];
	int scr_1;
	int scr_2;  

	Jogo* x;

	name = argv;

	x = procura_jogo(argv);

	if(!x){
		printf("%d %s\n", id_output, "Jogo inexistente.");   /*caso ainda nao exista um jogo com o mesmo nome*/
		id_output++;
	}

	else{                              
		strcpy(eqp_1, x->equipa_1->nome);
		strcpy(eqp_2, x->equipa_2->nome);
		scr_1 = x->score_1;
		scr_2 = x->score_2;
		printf("%d %s %s %s %d %d\n", id_output, name, eqp_1, eqp_2, scr_1, scr_2);

		id_output++;
	}
}


void procura_equipas(char argv[]){

	int num_jogos_ganhos;

	Equipa* x; 

	x = procura_equipa(argv);

	if(!x){
		printf("%d %s\n", id_output, "Equipa inexistente.");   /*caso a equipa nao exista*/
		id_output++;
	}
	else{

		num_jogos_ganhos = x->num_vitorias;

		printf("%d %s %d\n", id_output, argv, num_jogos_ganhos);

		id_output++;
	}
}


void apaga_jogo(char argv[]){

	Jogo* x;
	Jogo* prev_cron = NULL;
	Jogo* prev = NULL; 

	int hash;
	hash = getchave(argv);

	x = jogos[hash].head;

	for(; x ; ){
		if(!strcmp(x->nome, argv)){ 
			break;
		}
		prev = x;
		x = x->next;
	}

	for(x = head_cron; x != NULL; ){
		if(!strcmp(x->nome, argv)){ 
			break;
		}
		prev_cron = x;
		x = x->prox_cron;
	}	

	if(!x){
		printf("%d %s\n", id_output, "Jogo inexistente.");  /*caso ainda nao exista um jogo com o mesmo nome*/
		id_output++;
	}

	else{
		if(x->score_1 > x->score_2){
			x->equipa_1->num_vitorias--;
		}
		else if(x->score_1 < x->score_2){
			x->equipa_2->num_vitorias--;
		}
		
		if(head_cron == x){
			head_cron = x->next;
		}
		else{
			prev_cron->prox_cron = x->prox_cron;
		}

        if (tail_cron == x) {
            if (head_cron == x) {
                tail_cron = NULL;
            } else {
                tail_cron = prev_cron;
            }
        }
		
		if(jogos[hash].head == x){
			jogos[hash].head = x->next;
		}
		else{
			prev->next = x->next;
		}


		free(x);

		id_output++;
	}	
}


void altera_score(char argv[]){

	char delimt[2] = ":";	/*delimitador para o input*/

	char name[MAX_descricao];   
	char scr_1[MAX_descricao];
	char scr_2[MAX_descricao];
	int scr_1_2;
	int scr_2_2;

	Jogo* x;

	int hash;
	hash = getchave(argv);

	x = jogos[hash].head;

	strcpy(name ,strtok(argv, delimt));		/*repartir os diferentes dados do produto pelas variaveis atraves do delimitador*/
	strcpy(scr_1 ,strtok(NULL, delimt));
	strcpy(scr_2 ,strtok(NULL, delimt));

	scr_1_2 = strtol(scr_1, NULL, 10);		 /*passar o pointer para inteiro*/
	scr_2_2 = strtol(scr_2, NULL, 10);	

	x = procura_jogo(name);

	if(!x){
		printf("%d %s\n", id_output, "Jogo inexistente.");   /*caso ainda nao exista um jogo com o mesmo nome*/
		id_output++;
	}	

	else{
		if(x->score_1 > x->score_2){       /*verifica se vai haver alguma alteracao nos resultados*/
			if(scr_2_2 > scr_1_2){
				x->equipa_1->num_vitorias--;
				x->equipa_2->num_vitorias++;
			}
		}
		else if(x->score_1 < x->score_2){   /*verifica se vai haver alguma alteracao nos resultados*/
			if(scr_1_2 > scr_2_2){
				x->equipa_1->num_vitorias++;
				x->equipa_2->num_vitorias--;
			}
		}
		x->score_1 = scr_1_2;
		x->score_2 = scr_2_2;

		id_output++;
	}
}

int maximo_vitorias() {   /*verifica qual o numero maximo de vitorias que uma equipa obteve*/
	int max = 0;      
	Equipa* x;
	int i;
	for (i = 0; i < tamanho_hash_lista; i++) {      
		if (!equipas[i].head) {
			continue;
		}
		for (x = equipas[i].head; x; x = x->next) {
			if (x->num_vitorias > max) {
				max = x->num_vitorias;
			}
		}
	}
	return max;
}

void encontra_mais_vitorias(){     

	int num_max_vitorias = maximo_vitorias();

	int i, j, n;

	Equipa* x;
	Equipa* temp;

	Equipa* equipas_mais_vitorias[MAX_instr];

	j = 0;

	for(i = 0; i < tamanho_hash_lista; i++){        /*encontra todas as equipas com o numero de vitorias igual ao maximo possivel e coloca_as num array do tipo Equipas */
		if(!equipas[i].head){
			continue;
		}
			for(x = equipas[i].head; x; x = x->next){
				if(x->num_vitorias == num_max_vitorias){
					equipas_mais_vitorias[j] = x;
					j++;
				}
			}
	}
	n = j;

	for(i = 0; i < n-1; i++){    /*bubble sort - organiza o array */   
    	for (j = 0; j < n-i-1; j++){  
    		if(strcmp(equipas_mais_vitorias[j]->nome, equipas_mais_vitorias[j+1]->nome) > 0){  
            	temp = equipas_mais_vitorias[j];
            	equipas_mais_vitorias[j] = equipas_mais_vitorias[j+1];
            	equipas_mais_vitorias[j+1] = temp;
            }
        }
    }

    if(n>0){

	    printf("%d %s %d\n", id_output, "Melhores", num_max_vitorias);
	    
	    for(i = 0; i<n; i++){
	    	printf("%d %s %s\n", id_output, "*", equipas_mais_vitorias[i]->nome);
	    }
	} 

    id_output++;
}



int main(){

	int i;

	Jogo* x;
	Jogo* temp_J;
	Equipa* y; 
	Equipa* temp_E;

	char instruction[MAX_instr];
	char cmd = ' ';	
	head_cron = NULL;

	while(cmd != 'x'){

		cmd = getchar();
		

		switch (cmd){

			case 'a':
				getchar();
				scanf("%[^\n]s", instruction);
				adiciona_jogo(instruction);
				break;	

			case 'A':
				getchar();
				scanf("%[^\n]s", instruction);
				adiciona_equipa(instruction);
				break;	

			case 'l':
				lista_jogos(instruction);
				break;

			case 'p':
				getchar();
				scanf("%[^\n]s", instruction);
				procura_jogos(instruction);
				break;

			case 'P':
				getchar();
				scanf("%[^\n]s", instruction);
				procura_equipas(instruction);
				break;

			case 'r':
				getchar();
				scanf("%[^\n]s", instruction);
				apaga_jogo(instruction);
				break;

			case 's':
				getchar();
				scanf("%[^\n]s", instruction);
				altera_score(instruction);
				break;

			case 'g':
				encontra_mais_vitorias(instruction);
				break;
		}
	}

	for(i = 0; i < tamanho_hash_lista; i++){     /*liberta todo o espaco alocado para jogos*/
		if(jogos[i].head){
			for(x = jogos[i].head; x;){
				temp_J = x;
				x = x->next;
				free(temp_J);
			}
		}
		
	}

	for(i = 0; i < tamanho_hash_lista; i++){    /*liberta todo o espaco alocado para equipas*/
		if(equipas[i].head){
			for(y = equipas[i].head; y;){
				temp_E = y;
				y = y->next;
				free(temp_E);
			}
		}
	}
	
	return 0;
}
