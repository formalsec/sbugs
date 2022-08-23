#include <stdio.h>    	/*Bibliotecas de funcoes*/
#include <string.h>
#include <stdlib.h>

#define SIZE 1997  	/*Numero primo, tamanho das hash tables*/
#define MAX_NOME 1023 	/*Tamanho maximo dos inputs*/


/*###################################ESTRUTURAS#####################################################
Estrutura Jogo - Criei esta estrutura com os diversos componentes de um jogo que o utilizador
ira utilizar nos inputs, nomeadamente o nome do jogo, o nome das equipas e o numero de golos de 
cada equipa.
Estrutura Equipa - Criei esta estrutura com os diversos componentes de uma equipa, nomeadamente o 
nome que o utilizador ira utilizar nos inputs. A estrutura tem tambem o numero de vitorias de cada
equipa com o intuito de facilitar a atualizacao das vitorias das equipas.
Estrutura linked_list_game - Criei esta estrutura com um pointer que apontara sempre para um jogo,
e um pointer que apontara para o proximo elemento de uma linked list desta estrutura. O facto de
usar um pointer para um jogo da hashtable que guardara os jogos, e eficiente na quantidade de 
memoria alocada para a criacao desta lista, quando comparada com a alocacao de memoria necessaria
para a criacao de uma lista em que em vez de ter um pointer a apontar para um jogo da hashtable, 
tivesse um jogo, onde seria preciso alocar memoria para o mesmo jogo 2 vezes,
desnecessariamente.
##################################################################################################*/
typedef struct jogo{
	char *nome;
	char *equipa1;
	char *equipa2;
	int golos1;
	int golos2;
	struct jogo *next; /*vai apontar para o proximo node(jogo)*/
}*jogo;

typedef struct equipa{
	char *nome;
	int wins;
	struct equipa *next; /*vai apontar para o proximo node(equipa)*/
}*equipa;

typedef struct linked_list_jogo{
	struct jogo *ptr;
	struct  linked_list_jogo *next;
}*linked_list_jogo;

/*Variavel Global*/
int NL = 1, existe_equipas = 0; /*NL serve para contar as linhas dos inputs e o existe_equipas e 
								uma variavel de estado que passa a um caso haja equipas no sistema*/

/*##########################FUNCOES_SECUNDARIAS###################################################*/

/*##################################################################################################
liberta_equipas - e uma funcao auxiliar que tem como objetivo libertar a memoria que esta associada 
a uma hashtable, incluindo todas as suas equipas.

liberta_equipas1 - e uma funcao auxiliar que tem como objetivo libertar a memoria que esta associada 
a uma hashtable de um so indice, usada na funcao g, criada com o objetivo de armazenar as melhores 
equipas.

liberta_jogos - e uma funcao auxiliar que tem como objetivo libertar a memoria que esta associada 
a uma hashtable, incluindo todos os seus jogos.

liberta_jogos1 - e uma funcao auxiliar que tem como objetivo libertar a memoria que esta associada 
a uma hashtable de um unico indice, usada na funcao lista_jogos_existentes, criada com o 
objetivo de obter todos os jogos por ordem de entrada no sistema.
##################################################################################################*/
void liberta_equipas(equipa *h){
    int i;
    equipa aux;
    for (i = 0; i < SIZE; i++){
        while(h[i] != NULL){
            aux = h[i]->next;
            free(h[i]->nome);
            free(h[i]);
            h[i] = aux;
        }
    }
    free(h);
}

void liberta_equipas1(equipa *h){
    int i;
    equipa aux;
    for (i = 0; i < 1; i++){
        while(h[i] != NULL){
            aux = h[i]->next;
            free(h[i]->nome);
            free(h[i]);
            h[i] = aux;
        }
    }
    free(h);
}
void liberta_jogos(jogo *h){
    int i;
    jogo aux;
    for (i = 0; i < SIZE; i++){
        while(h[i] != NULL){
            aux = h[i]->next;
            free(h[i]->nome);
            free(h[i]->equipa1);
            free(h[i]->equipa2);
            free(h[i]);
            h[i] = aux;
        }
    }
    free(h);
}

void liberta_jogos1(linked_list_jogo *h){
    int i;
    linked_list_jogo aux;
    for (i = 0; i < 1; i++){
        while(h[i] != NULL){
            aux = h[i]->next;
            free(h[i]);
            h[i] = aux;
        }
    }
    free(h);
}

/*##################################################################################################
ASCII e uma funcao auxiliar que transforma um dado nome em ASCII
##################################################################################################*/

int ASCII(char *name){/*uma vez que vai ser retribuido um numero, a funcao e do tipo int*/
  int s,i,x,ascii = 0;
  s = strlen(name);/*Numero de algarismos do nome*/
  x = 0;
  for (i = 0; i<s;i++){
    x = name[i];
    ascii += x;
  }
  return ascii;
}
/*##################################################################################################
Devolvekey e uma funcao auxiliar que calcula e devolve a key de um certo nome para uma hashtable.
##################################################################################################*/

int devolvekey(char *name){/*uma vez que vai ser retribuido um numero, a funcao e do tipo int*/
  int ascii, key;
  ascii = ASCII(name);/*recorrer a funcao ASCII*/
  key = ascii % SIZE;
  return key;
}

/*##################################################################################################
criar_hash_jogo - e uma funcao auxiliar que cria uma hashtable. Esta funcao vai ser usada pela 
funcao main, com o objetivo de criar uma hashtable para armazenar os jogos. 

criar_hash_lista_jogos - e uma funcao auxiliar que cria uma lista ligada. Esta funcao vai chamada
pela funcao main, com o objetivo de criar uma lista ligada para armazenar os jogos por ordem de 
entrada que sera usada na funcao lista_jogos_existentes.

criar_hash_equipa - e uma funcao auxiliar que cria uma hashtable. Esta funcao vai ser usada pela 
funcao main, com o objetivo de criar uma hashtable para armazenar as equipas do sistema. 

criar_hash_equipa1 - e uma funcao auxiliar que cria uma lista ligada. Esta funcao vai ser usada pela 
funcao encontra_equipa_wins, com o objetivo de criar uma hashtable para armazenar as melhores 
equipas do sistema. 
##################################################################################################*/

jogo *criar_hash_jogo(){
	int i;  /*Aloca o espaco para a hashtable que vai ser criada*/
	jogo *heads = malloc(SIZE * sizeof(struct jogo));
	for (i = 0; i < SIZE; i++)
		heads[i] = NULL;  /*Inicializa se todos os indices da hashtable a apontar para NULL*/
	return heads;
}

linked_list_jogo *criar_hash_lista_jogos(){
	linked_list_jogo *heads = malloc(sizeof(struct linked_list_jogo));
	heads[0] = NULL;
	return heads;
}

equipa *criar_hash_equipa(){
	int i;
	equipa *heads = malloc(SIZE* sizeof(struct equipa));
	for (i = 0; i < SIZE; i++)
		heads[i] = NULL;
	return heads;
}

equipa *criar_hash_equipa1(){
	equipa *heads = malloc(sizeof(struct equipa));
	heads[0] = NULL;
	return heads;
}

/*##################################################################################################
NEW_equipa - e uma funcao auxiliar que cria uma nova equipa que sera chamada pelas funcoes de
inserir equipas em listas ligadas, quando for necessario adicionar a equipa no inicio ou meio da 
lista.  
NEW_equipa1 - e uma funcao auxiliar que cria uma nova equipa que sera chamada pelas funcoes de 
inserir equipas em listas ligadas, quando for necessario adicionar a equipa no fim da lista.
NEW_jogo - e uma funcao auxiliar que cria uma nova equipa que sera chamada pelas funcoes de inserir
jogos em listas ligadas.
##################################################################################################*/

equipa NEW_equipa(char *text){
	/*Aloco espaco para a equipa que ira ser criada*/
	equipa x = malloc(sizeof(struct equipa));
	x->nome = malloc(sizeof(char)*(strlen(text)+1));
	strcpy(x->nome, text); /*Copio o nome do input para o nome da equipa*/
	x->wins = 0;
	return x;
}

equipa NEW_equipa1(char *text){
	/*Aloco espaco para a equipa que ira ser criada*/
	equipa x = malloc(sizeof(struct equipa));
	x->nome = malloc(sizeof(char)*(strlen(text)+1));
	strcpy(x->nome, text); /*Copio o nome do input para o nome da equipa*/
	x->wins = 0;
	x->next = NULL; /*O pointer next aponta para NULL pois esta equipa criada sera o fim da lista*/
	return x;
}

jogo NEW_jogo(char *text, char *equipa1_input, char *equipa2_input, int golos1_input, 
	int golos2_input){
	/*Aloco espaco para o jogo que ira ser criada*/
	jogo x = malloc(sizeof(struct jogo));
	x->nome = malloc(sizeof(char)*(strlen(text)+1));
	x->equipa1 = malloc(sizeof(char)*(strlen(equipa1_input)+1));
	x->equipa2 = malloc(sizeof(char)*(strlen(equipa2_input)+1));
	strcpy(x->nome, text); 			   /*Copio o nome do input para o nome do jogo*/
	strcpy(x->equipa1, equipa1_input); /*Copio a equipa1 do input para a equipa1 do jogo*/
	strcpy(x->equipa2, equipa2_input); /*Copio a equipa2 do input para a equipa2 do jogo*/
	x->golos1 = golos1_input;
	x->golos2 = golos2_input;
	return x;
}

/*##################################################################################################
insertbegin_equipa - e uma funcao auxiliar criada com o objetivo de inserir uma equipa numa lista
ligada no inicio da lista.
insertbegin_lista_jogos - e uma funcao auxiliar criada com o objetivo de inserir um jogo numa 
lista ligada no inicio da lista.
insert_ordem_alfabetica - e uma funcao auxiliar criada com o objetivo de inserir um jogo numa lista
ligada por ordem alfabetica do nome dos jogos. 
##################################################################################################*/

equipa insertbegin_equipa(equipa head, char *text){
	equipa x = NEW_equipa(text); /*Cria um pointer x que apontara para uma equipa nova*/
	x->next = head;       /*O pointer_next da equipa x aponta para o inicio da lista*/
	head = x;             /*O inicio da lista e atualizado e apontara para a nova equipa*/
	return head;
}

jogo insertbegin_jogo_lista_jogos(jogo head, linked_list_jogo *lista_jogos,char *text, 
	char *equipa1_input, char *equipa2_input, int golos1_input, int golos2_input){
	/*Cria um pointer x que apontara para um jogo novo*/
	jogo x = NEW_jogo(text, equipa1_input, equipa2_input, golos1_input, golos2_input);
    /*Cria um pointer y que apontara para um linked_list_jogo novo*/
    linked_list_jogo y = malloc(sizeof(struct linked_list_jogo));
	x->next = head;  /*Coloca se o novo jogo, no inicio da lista ligada(hashtable_jogos[key])*/
	head = x;
	
	y->ptr = x;      /*Coloca se o novo jogo, no inicio da lista ligada*/
	y->next = lista_jogos[0];
	lista_jogos[0] = y; 
	
	return head;
}

equipa insert_ordem_alfabetica(equipa head, char *text){
	/*Cria um pointer t que apontara para uma nova equipa*/
	equipa x, t;
	/*Aloco memoria para a nova equipa*/
	t = malloc(sizeof(struct equipa));
	t->nome = malloc(sizeof(char)*(strlen(text)+1));
	strcpy(t->nome, text);
	t->wins = 0;
	
	if (head == NULL || strcmp(head->nome, text) > 0){
		t->next = head; /*Se a lista ligada for vazia ou a string do nome da nova equipa for menor*/
		head = t;       /*que a string do nome da primeira equipa da lista, a nova equipa e*/
		return head;    /*inserida no inicio da lista*/
	}
	/*Corre se a lista ate ao final e se houver alguma equipa na lista ligada que a sua*/
	/*String do nome da equipa seja maior que a da nova equipa, a nova equipa e inserida*/
	/*nessa posicao da lista ligada*/
	for (x = head; x->next != NULL; x = x->next){ 
		if(strcmp(x->next->nome, t->nome) > 0){
			t->next = x->next;
			x->next = t;
			return head;
		} 
	}
	free(t->nome); /*da se free da equipa criada*/
	free(t);

	x->next = NEW_equipa1(text); /*adiciona se uma nova equipa no fim da lista ligada*/
	return head;
}

/*##################################################################################################
delete - e uma funcao auxiliar criada com o objetivo de apagar um jogo de um indice da
hashtable e da lista ligada onde os jogos estao por ordem de entrada.
##################################################################################################*/

jogo delete(jogo head, linked_list_jogo *lista_jogos,char *text){
	jogo x, prev;
	linked_list_jogo x1, prev1;
	/*Apago o jogo da hashtable correndo a lista ligada desse indice e comparando os nomes dos jogos
	da lista ligada desse indice(key do nome do jogo), e quando encontrar um nome igual ao do jogo
	que quero apagar, retiro esse jogo da lista ligada. O mesmo para a lista ligada onde os jogos
	estao por ordem*/
    /*Hashtable[Key]*/
	for (x1 = lista_jogos[0], prev1 = NULL; x1 != NULL; prev1 = x1, x1 = x1->next){
		if (strcmp(x1->ptr->nome, text) == 0){
			if (x1 == lista_jogos[0])
				lista_jogos[0] = x1->next;
			else 
				prev1->next = x1->next;
			free(x1);
			break;
		}
	}
	/*Lista ligada - Lista_jogos*/
	for (x = head, prev = NULL; x != NULL; prev = x, x = x->next){
		if (strcmp(x->nome, text) == 0){
			if (x == head)
				head = x->next;
			else
				prev->next = x->next;
			free(x->nome);
			free(x->equipa1);
			free(x->equipa2);
			free(x);
			break;
		}
	}
	return head;
}
/*##################################################################################################
verifica_equipa_existente - funcao auxiliar com o objetivo de verificar se existe no sistema 
a equipa que quero procurar. retorna 0 se existir, retorna 1 se nao existir
verifica_jogo_existente - funcao auxiliar com o objetivo de verificar se existe no sistema 
o jogo que quero procurar. retorna 0 se existir, retorna 1 se nao existir
##################################################################################################*/

int verifica_equipa_existente(equipa head, char *equipa_x){
	equipa x;
	x = head;
	for (; x != NULL; x = x->next){
		if (strcmp(x->nome, equipa_x) == 0)
			return 0;
	}
	return 1;
}

int verifica_jogo_existente(jogo head, char *text){
	jogo x;
	x = head;
	for (; x != NULL; x = x->next){
		if (strcmp(x->nome, text) == 0)
			return 0;
	}
	return 1;
}
/*##################################################################################################
adiciona_win - funcao auxiliar que tem como objetivo adicionar uma vitoria a uma determinada equipa
diminui_win - funcao auxiliar que tem como objetivo retirar uma vitoria a uma determinada equipa
##################################################################################################*/
void adiciona_win(equipa head, char *text){
	equipa x;
	x = head;
	for (; x != NULL; x = x->next){
		if(strcmp(x->nome, text) == 0){
			x->wins = x->wins +1;
			return;   
		} 
	}
}

void dimimui_win(equipa head, char *text){
	equipa x;
	x = head;
	for (; x != NULL; x = x->next){
		if(strcmp(x->nome, text) == 0){
			x->wins = x->wins - 1;
			return;   
		} 
	}
}
/*##################################################################################################
encontra_max_wins - funcao auxiliar que tem como objetivo percorrer a hashtable onde estao
armazenadas todas as equipas e encontrar o maior numero de vitorias.
##################################################################################################*/
int encontra_max_wins(equipa *hash_table_equipa){
	int i, max_wins = 0;
	equipa x;
	for (i = 0; i < SIZE; i++){
		x = hash_table_equipa[i];
		for (; x != NULL; x = x->next){
			if (x->wins > max_wins)
				max_wins = x->wins;
		}
	}
	return max_wins;
}

/*##########################FUNCOES_PRINCIPAIS####################################################*/
/*##################################################################################################
adiciona_jogo - funcao que tem como objetivo adicionar um jogo ao programa. Adicionando esse jogo
a hashtable que armazena os jogos e a lista ligada que tem os jogos por ordem. Verifica se 
as equipas envolvidas no jogo existem no sistema e se o nome do jogo esta disponivel. Devolve um 
erro caso alguma desta condicoes seja falsa. 
##################################################################################################*/
void adiciona_jogo(jogo *hash_table_jogo, equipa *hash_table_equipa, linked_list_jogo *lista_jogos, 
	char *jogo_input, char *equipa1_input, char *equipa2_input, int golos1_input, int golos2_input){
	int key = devolvekey(jogo_input); /*Calcula as keys do nome do jogo e das equipas*/
	int key_equipa1 = devolvekey(equipa1_input);
	int key_equipa2 = devolvekey(equipa2_input); 
	if (verifica_jogo_existente(hash_table_jogo[key], jogo_input) == 0){
		printf("%d Jogo existente.\n", NL);
	}
	else{
		if((verifica_equipa_existente(hash_table_equipa[key_equipa1], equipa1_input)) || 
			(verifica_equipa_existente(hash_table_equipa[key_equipa2],equipa2_input))){
			printf("%d Equipa inexistente.\n", NL);
			return;
		}
		else{
			/*Adiciona o jogo a hashtable e a lista ligada*/
			hash_table_jogo[key] = insertbegin_jogo_lista_jogos(hash_table_jogo[key], 
				lista_jogos,jogo_input, equipa1_input, equipa2_input, golos1_input, golos2_input);
			/*Compara o numero de golos de cada equipa da partida e adiciona vitoria a equipa 
			vencedora ou nao caso exista um empates*/
			if (golos1_input > golos2_input){  
				adiciona_win(hash_table_equipa[key_equipa1], equipa1_input);
			}
			else if (golos2_input > golos1_input){
				adiciona_win(hash_table_equipa[key_equipa2], equipa2_input);
			}
		}
	}
}
/*##################################################################################################
adiciona_equipa - funcao que tem como objetivo adicionar uma equipa ao programa. Adicionando essa
equipa a hashtable que armazena as equipas. Verifica se a equipa ja existe. Devolve um erro caso 
esta condicao seja verdadeira
##################################################################################################*/
void adiciona_equipa(char *equipa1_input, equipa *hash_table_equipa){
	int key = devolvekey(equipa1_input); /*Calcula a key do nome da equipa*/
	if (verifica_equipa_existente(hash_table_equipa[key], equipa1_input)){
		/*Adiciona a equipa a hashtable*/
		hash_table_equipa[key] = insertbegin_equipa(hash_table_equipa[key], equipa1_input);
		existe_equipas = 1;
	}
	else{ /*Da print do erro*/
		printf("%d Equipa existente.\n", NL);
	}
}
/*##################################################################################################
procura_equipa - funcao que tem como objetivo procurar uma equipa no sistema. Se existir deve dar 
print do nome da equipa e o numero de vitorias. Caso nao exista da print de um erro.
##################################################################################################*/
void procura_equipa(equipa *hash_table_equipa, char *equipa1_input){
	equipa x;
	int key = devolvekey(equipa1_input);
	x = hash_table_equipa[key];
	for (; x != NULL; x = x->next){
		if (strcmp(x->nome, equipa1_input) == 0){
			printf("%d %s %d\n", NL, x->nome, x->wins);
			return;
		}
	}
	printf("%d Equipa inexistente.\n", NL);
}
/*##################################################################################################
procura_jogo - funcao que tem como objetivo procurar um jogo no sistema. Se existir deve dar 
print do nome do jogo do nome das equipas e do resultado. Caso nao exista da print de um erro.
##################################################################################################*/
void procura_jogo(jogo *hash_table_jogo, char *jogo_input){
	jogo x;
	int key = devolvekey(jogo_input);
	x = hash_table_jogo[key];
	for (; x != NULL; x = x->next){
		if (strcmp(x->nome, jogo_input) == 0){
			printf("%d %s %s %s %d %d\n", NL, x->nome, x->equipa1, x->equipa2, x->golos1, x->golos2);
			return;
		}
	}
	printf("%d Jogo inexistente.\n", NL);
}
/*##################################################################################################
lista_jogos_existentes - funcao que tem como objetivo listar todos os jogos por ordem de entrada.
Como quando entra um novo jogo, o jogo e adicionado no inicio da lista ligada, faz se uma funcao
recursiva a comecar os prints dos jogos desde o final da lista ligada.
##################################################################################################*/
void lista_jogos_existentes(linked_list_jogo head){
		if (head != NULL){
		lista_jogos_existentes(head->next);
    	printf("%d %s %s %s %d %d\n", NL, head->ptr->nome, head->ptr->equipa1, head->ptr->equipa2, 
    		head->ptr->golos1, head->ptr->golos2);
    }
}
/*##################################################################################################
altera-score - funcao que tem como objetivo alterar o resultado de um jogo. Verifica se o jogo
existe no sistema, se nao existir da print de um erro.
##################################################################################################*/
void altera_score(jogo *hash_table_jogo, linked_list_jogo *lista_jogos ,equipa *hash_table_equipa ,
	char *jogo_input, int golos1_input, int golos2_input){
	jogo x;
	linked_list_jogo aux;
	int key = devolvekey(jogo_input); /*Calculo a key para o jogo*/
	int key_equipa;
	x = hash_table_jogo[key]; /*O x e o aux aponta para o primeiro elemento das listas ligadas*/
	aux = lista_jogos[0];     

	if (verifica_jogo_existente(hash_table_jogo[key], jogo_input) == 1){
		printf("%d Jogo inexistente.\n", NL); /*Verifica se existe equipa*/
	}
	else{
		for (; x != NULL; x = x->next){
			if ((strcmp(x->nome, jogo_input)) == 0){
				/*Se no resultado anterior a equipa 1 tiver ganho retiro a sua vitoria
				o mesmo para a equipa2.*/
				if (x->golos1 > x->golos2){
					key_equipa = devolvekey(x->equipa1);
					dimimui_win(hash_table_equipa[key_equipa], x->equipa1);
				}
				else if (x->golos1 < x->golos2){
					key_equipa = devolvekey(x->equipa2);
					dimimui_win(hash_table_equipa[key_equipa], x->equipa2);
				}
				x->golos1 = golos1_input; /*Atualizo o resultado*/
				x->golos2 = golos2_input;
				/*Se no novo resultado a equipa 1 tiver ganho adiciono uma vitoria a equipa1*/
				/*Se no novo resultado a equipa 2 tiver ganho adiciono uma vitoria a equipa2*/
				if (x->golos1 > x->golos2){
					key_equipa = devolvekey(x->equipa1);
					adiciona_win(hash_table_equipa[key_equipa], x->equipa1);
				}
				else if (x->golos1 < x->golos2){
					key_equipa = devolvekey(x->equipa2);
					adiciona_win(hash_table_equipa[key_equipa], x->equipa2);
				}
				break;
			}
		}
		/*Atualizo tambem o resultado na lista ligada*/
		for (; aux != NULL; aux = aux->next){
			if ((strcmp(aux->ptr->nome, jogo_input)) == 0){
				aux->ptr->golos1 = golos1_input;
				aux->ptr->golos2 = golos2_input;
				return;
			}
		}
	}
}
/*##################################################################################################
apaga_jogo - funcao que tem como objetivo apagar um jogo de um sistema. Verifica se o jogo existe.
Caso contrario faz print de um erro. 
##################################################################################################*/
void apaga_jogo(jogo *hash_table_jogo, linked_list_jogo *lista_jogos, equipa *hash_table_equipa ,
	char *jogo_input){
	jogo x;
	int key = devolvekey(jogo_input); /*Calcula a key do nome do jogo*/
	int key_equipa;
	x = hash_table_jogo[key]; /*O x aponta para o primeiro elemento da lista ligada*/

	if (verifica_jogo_existente(hash_table_jogo[key], jogo_input) == 1){
		printf("%d Jogo inexistente.\n", NL); /*Verifico o erro*/
	}
	else{
		for(; x != NULL; x = x->next){
			if((strcmp(x->nome, jogo_input)) == 0){
				/*Se a equipa 1 tivesse ganho o jogo, retiro uma vitoria a equipa1
				Se a equipa2 tivesse ganho o jogo, retiro uma vitoria a equipa2*/
				if (x->golos1 > x->golos2){
					key_equipa = devolvekey(x->equipa1);
					dimimui_win(hash_table_equipa[key_equipa], x->equipa1);
				}
				else if (x->golos1 < x->golos2){
					key_equipa = devolvekey(x->equipa2);
					dimimui_win(hash_table_equipa[key_equipa], x->equipa2);
				}
				/*Elimino os jogo da lista ligada e da hashtable*/
				hash_table_jogo[key] = delete(hash_table_jogo[key], lista_jogos,jogo_input);
				return;
			}
		}
	}
}
/*##################################################################################################
encontra_equipa_wins - funcao que tem como objetivo fazer print das equipas do sistema com mais 
vitorias.
##################################################################################################*/
void encontra_equipa_wins(equipa *hash_table_equipa){
	int i, max_wins = 0; 
	equipa x;
	equipa *lista_equipas = criar_hash_equipa1(); /*crio uma lista ligada para as melhores equipas*/
	max_wins = encontra_max_wins(hash_table_equipa); /*Encontra o max de vitorias.*/

	if (existe_equipas == 0){ /*Verifico a variavel de estado. Caso nao exista equipas liberta se*/ 											
		liberta_equipas1(lista_equipas); /*a lista ligada que foi criada e faz se return*/
		return;
	}

	/*Corre se a hashtable e encontra se as equipas com as vitorias igual ao maior numero de 
	vitorias. As equipas que tiverem esse numeros de vitorias sao adicionadas a lista
	ligada que foi criada nesta funcao*/
	for (i = 0; i < SIZE; i++){
		x = hash_table_equipa[i];
		for (; x != NULL; x = x->next){
			if (x->wins == max_wins)
				lista_equipas[0] = insert_ordem_alfabetica(lista_equipas[0], x->nome);
		}
	}

	printf("%d Melhores %d\n", NL, max_wins); /*Faz se o print*/
	x = lista_equipas[0];

	for(; x != NULL; x = x->next){
		printf("%d * %s\n", NL, x->nome);
	}
	liberta_equipas1(lista_equipas); /*Liberto a lista ligada que criei nesta funcao*/
}

int main(){
	/*Cria se as variaveis para armazenar os inputs do utilizador*/
	int golos1_input, golos2_input;
	char jogo_input[MAX_NOME], equipa1_input[MAX_NOME], equipa2_input[MAX_NOME];
	char letra = 't';
	/*Cria se as hashtable*/
	linked_list_jogo *lista_jogos = criar_hash_lista_jogos();
	jogo *hash_table_jogo = criar_hash_jogo();
	equipa *hash_table_equipa = criar_hash_equipa();	
	while(letra != 'x'){
		scanf("%c", &letra);
		switch(letra){
			case'a':
			getchar();/*Tiro o segundo carater do input*/
			scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", jogo_input, equipa1_input, equipa2_input, 
				&golos1_input, &golos2_input);
			adiciona_jogo(hash_table_jogo, hash_table_equipa ,lista_jogos, jogo_input, 
				equipa1_input, equipa2_input, golos1_input, golos2_input);
			NL++;	
			break;

			case 'A':
			getchar();
			scanf("%[^:\n]", equipa1_input);
			adiciona_equipa(equipa1_input, hash_table_equipa);
			NL++;
			break;

			case 'l':
			lista_jogos_existentes(lista_jogos[0]);
			NL++;
			break;

			case 'p':
			getchar();
			scanf("%[^:\n]", jogo_input);
			procura_jogo(hash_table_jogo ,jogo_input);
			NL++;
			break;

			case 'P':
			getchar();
			scanf("%[^:\n]", equipa1_input);
			procura_equipa(hash_table_equipa ,equipa1_input);	
			NL++;
			break;

			case 'r':
			getchar();
			scanf("%[^:\n]", jogo_input);
			apaga_jogo(hash_table_jogo, lista_jogos, hash_table_equipa, jogo_input);
			NL++;
			break;

			case 's':
			getchar();
			scanf("%[^:\n]:%d:%d", jogo_input, &golos1_input, &golos2_input);
			altera_score(hash_table_jogo, lista_jogos ,hash_table_equipa ,jogo_input,
			 golos1_input, golos2_input);
			NL++;
			break;

			case 'g':
			encontra_equipa_wins(hash_table_equipa);
			NL++;
			break;

			case 'x':
			break;			
		}
	}
	/*Liberto as hashtables*/
	liberta_jogos1(lista_jogos);
	liberta_jogos(hash_table_jogo);
	liberta_equipas(hash_table_equipa);
	return 0;
}



