#include <stdlib.h>
#include "proj2.h"

#define MAXNAME 1023 /*numero maximo caracteres do jogo e equipa*/
#define SIZE 2997 /*numero primo*/



   /*FUNCOES AUXLIARES*/

/*#################################################################################################################################################
inicializa_l_jogos: Ambas funcoes sao funcoes auxiliares que incializao as listas ligadas, alocando espaco na memoria. (visto que so iremos usar as listas para ser 
mais facil de implementar a funcao l - onde temos de imprimir pela ordem que foram introduzidos)
#################################################################################################################################################*/
Jogoslist* inicializa_l_jogos(){	
	Jogoslist* lista = (Jogoslist*)malloc(sizeof(Jogoslist)); /*aloca memoria*/
	lista->head = NULL; /*inicializa ambos ponteiros a NULL*/
	lista->root = NULL; 
	return lista;
}


/*#################################################################################################################################################
inicializa_jogo s & inicializa_equipa

Ambas funcoes sao funcoes auxiliares que incializao as Hash Tables, incializando-as a NULL
#################################################################################################################################################*/
void inicializa_jogo(Nodo_jogo **table){
	int i;
	for(i = 0; i<SIZE;i++)
		table[i]= NULL;

	return;
}

void inicializa_equipa(Nodo_equipa** table){
	int i;
	for(i = 0; i<SIZE;i++)
		table[i]= NULL;

	return;
}

/*#################################################################################################################################################
hash: Esta funcao auxiliar recebe um nome e encontra a sua posicao(index) na Hash Table, para que seja mais facil de procurar
#################################################################################################################################################*/
unsigned long hash(char* nome) {
    unsigned long i = 0;
    int j;
    for (j=0; nome[j]; j++)
        i += nome[j];
    return i % SIZE;
}


/*#################################################################################################################################################
alocar_jogos: 
Esta funcao auxiliar ira receber as variavies para a funcao "a", e ira alocar a respetiva memoria para cada componente. 
Inicializando tambem os ponteiros next e prev a NULL.

alocar_equipas_nome: 
Esta funcao auxiliar ira receber a variavel nome, e ira alocar a respetiva memoria para cada componente. 
Inicializando tambem os ponteiros next e prev a NULL.
#################################################################################################################################################*/
Jogos* alocar_jogos(){
	char arg1[MAXNAME], arg2[MAXNAME], arg3[MAXNAME]; 
	int arg4, arg5;
	Jogos* novo_jogo; 
	novo_jogo = malloc(sizeof(Jogos)); 
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", arg1, arg2, arg3, &arg4, &arg5); /*informacao recebida na funcao*/
	novo_jogo->next = NULL; 
	novo_jogo->prev = NULL; 
	novo_jogo->nome = malloc(sizeof(char*)*(strlen(arg1)+1)); /*aloca espaco na memoria*/
	novo_jogo->equipa1 = malloc(sizeof(char*)*(strlen(arg2)+1));
	novo_jogo->equipa2 = malloc(sizeof(char*)*(strlen(arg2)+1));
	
	novo_jogo->nome = strcpy(novo_jogo->nome, arg1); /*copia os argumentos*/
	novo_jogo->equipa1 = strcpy(novo_jogo->equipa1, arg2); 
	novo_jogo->equipa2 = strcpy(novo_jogo->equipa2, arg3); 
	novo_jogo->score1 = arg4; 
	novo_jogo->score2 = arg5; 
	return novo_jogo; /*visto que e do tipo Jogos, tera de retornar uam variavel do tipo Jogos*/
}


Equipas* alocar_equipas_nome(){
	char arg1[MAXNAME]; 
	Equipas* nova_equipa; 
	nova_equipa = malloc(sizeof(Equipas)); 
	scanf(" %[^:\n]", arg1);
	nova_equipa->next_e = NULL; 
	nova_equipa->prev_e = NULL; 
	nova_equipa->nome = malloc(sizeof(char*)*(strlen(arg1)+1)); /*aloca espaco na memoria*/
	
	nova_equipa->nome = strcpy(nova_equipa->nome, arg1); /*copia os argumentos*/
	nova_equipa->finalscore = 0;
	return nova_equipa; 
}

void malloc_array(char **array, int k){/*funcao para alocar espaco na memoria para o array com as equipas (usado na funcao g)*/
	int i;
	for(i = 0; i<k;i++){
		array[i] = malloc(MAXNAME*sizeof(char));
	}
}

/*#################################################################################################################################################
free_item: Esta funcao tem como objetivo libertar a memoria que esta associado a um certo jogo, bem como a todos os seus componentes.  

free_item_e: Esta funcao tem como objetivo libertar a memoria que esta associado a uma certa equipa, bem como a todos os seus componentes.  

clean_array: Esta funcao tem como objetivo limpar o array com o nome das equipas
#################################################################################################################################################*/
void free_item(Jogos* item) { 
    free(item->nome);
    free(item->equipa1);
    free(item->equipa2);
    free(item);
}


void free_item_e(Equipas* item) {
    free(item->nome);
    free(item);
}

void clean_array(char **array, int k){ /*funcao para limpar o array com as equipas (usado na funcao g)*/
	int i;
	for(i = 0; i<k;i++){
		strcpy(array[i],"\0"); /*visto que e um array de caraceteres quando apagamos colocamos "0\"*/
	}
}


void libertajogohash(Nodo_jogo *c){
  free(c);
}

void libertaequipahash(Nodo_equipa *c){
  free(c);
}


/*#################################################################################################################################################
insert: Esta funcao tem como objetivo adicionar a Hash Table dos jogos um certo jogo recebido.  

insert_e: Esta funcao tem como objetivo adicionar a Hash Table das equipas uma certa equipa recebido.  

inserir_score: Esta funcao tem como objetivo inserir a pontuacao de um jogo na Hash Table. Caso a pontuacao de uma das equipas seja maior que a outra, 
entao incrementa o finalscore da equipa, caso as pontuacoes sejam iguais, nao e adicionado nem retirado pontuacao dessa equipa.
#################################################################################################################################################*/
int insert(Nodo_jogo **table, Jogos* novojogo){
	int index = hash(novojogo->nome);
	Nodo_jogo* new_node = (Nodo_jogo*)malloc(sizeof(Nodo_jogo));
	Nodo_jogo* node_aux = table[index]; /*sao criadas um node_aux auxiliar para nao retirar a posicao da head na Hash Table*/

	new_node->jogo = novojogo;
	new_node->next = NULL;

	if(table[index]==NULL) /*caso a Hash Table ainda nao tenha nenhum valor, sera colocado o primeiro valor*/
	{
		table[index]=new_node;
		table[index]->jogo = novojogo;
		table[index]->next = NULL; /*o proximo e colocado a NULL*/

		return 1;
	} 
	while(node_aux->next != NULL){/*procura um espaco livre bem como compara o nome recebido para o mesmo jogo nao ser colocado mais do que uma vez*/
		node_aux = node_aux->next; /*caso nao encontre, passa para a proxima posicao*/
	}
	/*aqui aux tem ultimo elemento onde se pode colocar um jogo*/
		node_aux->next = new_node;
		return 1;
	
	return 0;
}


int insert_e(Nodo_equipa **table, Equipas* novaequipa){
	int index = hash(novaequipa->nome);
	Nodo_equipa* new_node_e = (Nodo_equipa*)malloc(sizeof(Nodo_equipa));
	Nodo_equipa* node_aux_e = table[index];

	new_node_e->equipa = novaequipa;
	new_node_e->next_e = NULL;

	if(table[index]==NULL){/*caso a Hash Table ainda nao tenha nenhum valor, sera colocado o primeiro valor*/
		table[index] = new_node_e;
		table[index]->equipa = novaequipa;
		table[index]->next_e = NULL; /*o proximo e colocado a NULL*/
		return 1;
	}
	while(node_aux_e->next_e != NULL){/*procura um espaco livre recebido para o mesmo jogo nao ser colocado mais do que uma vez*/
		node_aux_e = node_aux_e->next_e;
	}
	/*aqui aux tem ultimo elemento onde se pode colocar a equipa*/
		node_aux_e->next_e = new_node_e;
		return 1; 
	
	return 0;
}

void inserir_score(Nodo_equipa **table_e, int score1, int score2, char *equipa1, char* equipa2){
	int index1 = hash(equipa1);
	int index2 = hash(equipa2);
	Nodo_equipa* aux1 =NULL; /*cria variaveis do tipo Node_equipa para procurar na Hash Table sem alterar a posicao da head da Hash Table*/
	Nodo_equipa* aux2 = NULL;
	aux1= table_e[index1];
	aux2 = table_e[index2];
	
	if(score1 > score2){ /*compara os valores, caso a pontuacao do jogo da primeira equipa seja maior que a pontuacao da segunda equipa no jogo, 
	na Hash Table das equipas altera o finalscore da equipa*/
		while(strcmp(aux1->equipa->nome,equipa1)!= 0) /*precorre todas as posicoes ate encontrar a equipa que queremos alterar*/
			aux1 = aux1->next_e;
		aux1->equipa->finalscore++;/*incrementa o numero de jogos ganho pela equipa*/
		return;
	}
	if(score2 > score1){/*compara os valores, caso a pontuacao do jogo da segunda equipa seja maior que a pontuacao da primeira equipa no jogo, 
	na Hash Table das equipas altera o finalscore da equipa*/
		while(strcmp(aux2->equipa->nome,equipa2)!= 0)
			aux2 = aux2->next_e;
		aux2->equipa->finalscore++;
		return;
		}

}


/*#################################################################################################################################################
search: Esta funcao tem como objetivo procurar um nome na Hash Table dos jogos, retornadno o index se existir, senao retorna -1.

search_e: Esta funcao tem como objetivo procurar um nome na Hash Table das equipas, retornadno o index se existir, senao retorna -1.
#################################################################################################################################################*/
int search(Nodo_jogo** table, char *nome){
	int result = -1;
	Nodo_jogo *node_aux = NULL; /*cria-se uma variavel que percorre a Hash Table sem alterar a cabeca de onde estamos a procurar*/
	int index = hash(nome);
	node_aux = table[index];
	
	while(node_aux != NULL){
		if (strcmp(node_aux->jogo->nome,nome) == 0){
			return index; 
		}
	node_aux = node_aux->next;/*caso o nome da equipa nao seja igual ao que estamos a procurar entao passamos ao proximo node*/		
	}
	free(node_aux);
	return result; 
}




int search_e(Nodo_equipa** table, char *name){
	int result = -1;
	Nodo_equipa *node_aux; /*cria-se uma variavel que percorre a Hash Table sem alterar a cabeca de onde estamos a procurar*/
	int index = hash(name);
	node_aux = table[index];
	while(node_aux != NULL){
		if (strcmp(node_aux->equipa->nome,name) == 0){
				return index; 
		}
	node_aux = node_aux->next_e;/*caso o nome da equipa nao seja igual ao que estamos a procurar entao passamos ao proximo node*/			
	}
	free(node_aux); /*liberta espaco na memoria do node_aux*/
	return result; 
}

/*#################################################################################################################################################
pop_node: Funcao auxiliar que tem como objetivo apagar da lista de jogos, desta forma, temos de analisar tres opcoes: 
	1 - caso a lista apenas tenha um elemento
	2 - caso a lista tenha mais do que um elemento e estamos a retirar o primeiro
	3 - caso a lista tenha mais elementos e estejamos a tirar do meio

apaga: Esta funcao tem como objetivo apagar um jogo da Hash Table dos jogos se o jogo e apagado entao teremos de 
retirar o valor desse jogo nas equipas (usando a funcao pop_node).
#################################################################################################################################################*/
void pop_node (Jogoslist *l, Jogos *n){

	Jogos* aux = l->head;
	Jogos* v = NULL;

	if(aux == NULL)
		return;

	if(aux->next == NULL && strcmp(aux->nome, n->nome) ==0){/*se queremos remover o primeiro elemento e nao ha mais elementos na lista*/
		l->head = NULL; /*como a lista vai ficar vazia, entao a cabeca e o root ficaram iguais*/
		l->root = NULL;
		free(aux);
		return; 
	}
	else if(aux!= NULL && strcmp(aux->nome, n->nome)==0){ /*se queremos removar o primeiro elemento e existem pelo menos dois jogos na lista*/
		l->head = l->head->next; /*a cabeca sera o proximo elemento visto que vamos retirar o primeiro*/
		free(aux);
		return;
	}
	/*caso a equipa que procuramos nao seja o primeiro elemento da lista*/
	while(aux->next!=NULL){
		if(strcmp(aux->next->nome,n->nome)== 0) /*procura o elemento na lista*/
			break;
		else
			aux = aux->next;
	} 
	v = aux->next;
	aux->next = aux->next->next;/*ao retirar do meio, conectamos o elemento anterior com o proximo*/
	free(v);
	return;
}



void apaga(Jogoslist* lista, char name[MAXNAME], Nodo_jogo** table, Nodo_equipa** table_e){
	int score1_jogo = 0;
	char *nome_equipa1; char *nome_equipa2;
	int score2_jogo = 0;
	int index = hash(name); 
	Nodo_equipa* aux_1;
	Nodo_equipa* aux_2; /*sao usadas variaveis auxiliares para nao perder a cabeca da Hash Table*/
	Nodo_jogo* aux = table[index]; 
	Nodo_jogo* v = NULL;

	nome_equipa1 = table[index]->jogo->equipa1;
	nome_equipa2 = table[index]->jogo->equipa2;
	
	score1_jogo = hash(nome_equipa1);
	score2_jogo = hash(nome_equipa2); 

	aux_1 = table_e[score1_jogo];
	aux_2 = table_e[score2_jogo];

	if(table[index]->jogo->score1>table[index]->jogo->score2){ /*caso a primeira equipa tenha ganho, quando retiramos o jogo e necessario retirar tambem
		o retirar um ponto do finalscore*/
		aux_1->equipa->finalscore--;
		}
	else if(table[index]->jogo->score1<table[index]->jogo->score2){
		aux_2->equipa->finalscore--;
		}
	
	if(aux == NULL)/*nao existe jogo*/
		return; 
	if(aux != NULL && strcmp(aux->jogo->nome, name) == 0){ /*caso seja a cabeca da Hash Table, basta apagar*/
		pop_node(lista,table[index]->jogo); /*e ncessario retirar tambem na lista*/
		free(aux);
		table[index] = NULL;
		return; 
	}
	while(aux->next!= NULL){ /*caso nao seja a cabeca teremos de percorrer a Hash Table*/
		if(strcmp(aux->next->jogo->nome, name) == 0) break;
		else
			aux = aux->next;
	}
	v = aux->next; /*guarda se a variavel a apagar num NodeHash auxiliar*/
	aux->next = v->next;
	pop_node(lista,table[index]->jogo);
	free(v);
}



  /*FUNCOES PRINCIPAIS*/


/*#################################################################################################################################################
Adiciona um novo jogo

Na funcao main, ao ativar o comando a, esta sera a funcao utilizada.

Tem como objetivo adicionar um jogo.

Caracteristicas da funcao:

Formato de entrada: 'a nome:equipa1:equipa2:score1:score2'
Formato de saida: NADA (excepto erro)
Erros:
  - `Equipa inexistente.` caso uma das equipas (ou ambas) nao existir. Logo nao foi adicionado a lista das Equipas. 
  -'Jogo existente' no caso de o nome do jogo ja existir no sistema.
#################################################################################################################################################*/

void adiciona_jogo (int i, Jogoslist* lista,Nodo_jogo **hashtable_j, Nodo_equipa** hashtable_e){
	Jogos* novo_jogo;
	novo_jogo = alocar_jogos();
	
	if(search(hashtable_j, novo_jogo->nome)!= -1){/*caso o nome ja exista a funcao search ira retornar -1, logo o jogo nao e adicionado*/
		printf("%d Jogo existente.\n",i);
		free_item(novo_jogo); 
		return; 
	}
	
	if(search_e(hashtable_e, novo_jogo->equipa1) == -1 || search_e(hashtable_e, novo_jogo->equipa2) == -1){
		printf("%d Equipa inexistente.\n", i);
		free_item(novo_jogo); 
		return; 
	}
	else{
		if(lista->head == NULL) { /*caso esteja a colocar o primeiro elemento na lsita*/
			lista->head = novo_jogo; 
			lista->root = novo_jogo;
			novo_jogo->next=NULL;
			novo_jogo->prev=NULL;
			insert(hashtable_j, novo_jogo); /*importante inserir tambem na Hash Table*/
			inserir_score(hashtable_e, novo_jogo->score1, novo_jogo->score2, novo_jogo->equipa1, novo_jogo->equipa2); /*atualizar a pontuacao das 
			equipas*/
			return; 
		}
		else{
			novo_jogo->next = lista->head; /*caso estejammos a inserir, e nao seja o primeiro elemento da lista*/
			lista->head->prev = novo_jogo;
			lista->head = novo_jogo;
			insert(hashtable_j, novo_jogo);
			inserir_score(hashtable_e, novo_jogo->score1, novo_jogo->score2, novo_jogo->equipa1, novo_jogo->equipa2);
		}
    }
}


/*#################################################################################################################################################
Adiciona uma nova equipa

Na funcao main, ao ativar o comando A, esta sera a funcao utilizada.

Tem como objetivo adicionar uma nova equipa na Hash Table das equipas.

Caracteristicas da funcao:

Formato de entrada: 'A nome'
Formato de saida: NADA (excepto erro)
Erros:
  - `Equipa existente.` no caso de o nome da Equipa ja existir no sistema.
#################################################################################################################################################*/

void adiciona_equipa (int i, Nodo_equipa **hashtable_e, int *teams){
	Equipas* nova_equipa = NULL;
	nova_equipa = alocar_equipas_nome();

	if(search_e(hashtable_e, nova_equipa->nome)!= -1){ /*caso a equipa ja exista a funcao search ira retornar != -1, logo o jogo nao e adicionado*/
		printf("%d Equipa existente.\n",i);
		free_item_e(nova_equipa); 
		return;
	}
	insert_e(hashtable_e, nova_equipa); /*insere na Hash Table das equipas*/
	*teams = *teams +1; /*variavel que sera usada na funcao g que contem o numero de equipas que sa adicionadas*/
}


/*#################################################################################################################################################
Lista todos os jogos introduzidos

Na funcao main, ao ativar o comando l, esta sera a funcao utilizada.

Tem como objetivo imprimir todos os jogos introduzidos.

Caracteristicas da funcao:

Formato de entrada: 'l'
Formato de saida: nome-jogo nome-equipa1 nome-equipa2 score1 score2
#################################################################################################################################################*/
void lista(int i, Jogos*l){
	if(l==NULL) /*enqunto nao tiver percorrido todos os jogos, ele continua a entrar no loop, ate chegar ao fim*/
		return;
	lista(i,l->next); /*faz uma procura recursiva visto que a funcao A adiciona no inicio*/

	printf("%d %s %s %s %d %d\n", i,l->nome, l->equipa1, l->equipa2, l->score1, l->score2);
}


/*#################################################################################################################################################
Procura um jogo com o nome dado

Na funcao main, ao ativar o comando p, esta sera a funcao utilizada.

Tem como objetivo procurar um determinado jogo

Caracteristicas da funcao:

Formato de entrada: 'p nome'
Formato de saida: nome-jogo 
Erros: 
- 'Jogo inexistente' no caso de nao existir nenhum jogo com esse nome no sistema.
#################################################################################################################################################*/

void procurajogo(int i,Nodo_jogo**table){
	int index;
	char arg1[MAXNAME]; 
	char frase;
	Nodo_jogo *aux;
	scanf("%c", &frase);
	scanf("%[^:\n]", arg1);

	index = hash(arg1); /*procura a posicao do nome na Hash Table*/
	aux = table[index];
	
	while(aux!=NULL){
			if(strcmp(aux->jogo->nome,arg1)==0){ /*compara o nome na hashtable, naquela posicao, 
				com o nome que queremos procurar*/
				printf("%d %s %s %s %d %d\n",i, aux->jogo->nome, aux->jogo->equipa1, 
		aux->jogo->equipa2, aux->jogo->score1, aux->jogo->score2); /*caso o nome seja igual chegamos a posicao desejada*/
				return;
			}

			aux=aux->next; /*caso nao tenhamos chegado a posicao correta, ele ve o */
		}
		

	printf("%d Jogo inexistente.\n",i);
	}
	
/*#################################################################################################################################################
Procura uma equipa com o nome dado

Na funcao main, ao ativar o comando P, esta sera a funcao utilizada.

Tem como objetivo procurar uma determinada equipa

Caracteristicas da funcao:

Formato de entrada: 'P nome'
Formato de saida: nome numero-de-jogos-ganhos
Erros: 
- 'Equipa inexistente' no caso de nao existir nenhuma equipa com esse nome no sistema.
#################################################################################################################################################*/

void procuraequipa(int i,Nodo_equipa**table){
	int index;
	char arg1[MAXNAME]; 
	char frase;
	Nodo_equipa *aux;
	scanf("%c", &frase);
	scanf("%[^:\n]", arg1);

	index = hash(arg1); /*procura a posicao do nome na Hash Table*/
	aux = table[index];

		while(aux!=NULL){
			if(strcmp(aux->equipa->nome,arg1)==0){
				printf("%d %s %d\n", i,aux->equipa->nome, aux->equipa->finalscore);
				return;
			}
			aux=aux->next_e;
		}	
		printf("%d Equipa inexistente.\n",i);
	}



/*#################################################################################################################################################
Altera um valor na pontuacao de um jogo

Na funcao main, ao ativar o comando s, esta sera a funcao utilizada.

Caracteristicas da funcao:

Formato de entrada: 's nome:score1:score2'
Formato de saida: NADA
Erros: 
- 'Jogo inexistente' no caso de nao existir nenhum jogo com esse nome no sistema.
#################################################################################################################################################*/
void altera_pontos(int i,Nodo_jogo**table, Nodo_equipa**table_e){
	int arg2, arg3; 
	char arg1[MAXNAME];
	char espaco;
	int index,indexs1, indexs2;
	Nodo_jogo *novo_jogo;
	Nodo_equipa *nova_equipa1;
	Nodo_equipa *nova_equipa2;
	
	scanf("%c", &espaco); 
	scanf(" %[^:\n]:%d:%d", arg1, &arg2, &arg3);

	if(search(table, arg1)==-1){ 
		printf("%d Jogo inexistente.\n",i);
		return;
	}
	
	/*procura posicao na Hash Table*/
	index = hash(arg1); 
	indexs1 = hash(table[index]->jogo->equipa1);
	indexs2 = hash(table[index]->jogo->equipa2);
	
	novo_jogo = table[index]; /*usado para procurar na Hash Table dos jogos, e para nao perder a sua cabeca e criada uma variavel*/
	nova_equipa1 = table_e[indexs1]; /*usado para procurar na Hash Table das equipas, e para nao perder a sua cabeca e criada uma variavel*/
	nova_equipa2 = table_e[indexs2];/*usado para procurar na Hash Table das equipas, e para nao perder a sua cabeca e criada uma variavel*/

	while(novo_jogo->next !=NULL){ /*procura o jogo na Hash Table dos jogos*/
		if(strcmp(novo_jogo->jogo->nome,arg1)==0)
			break;
		novo_jogo=novo_jogo->next;
	}


	while(nova_equipa1->next_e !=NULL){ /*procura o jogo na Hash Table das equipas*/
		if(strcmp(nova_equipa1->equipa->nome,novo_jogo->jogo->equipa1)==0)
			break;
		nova_equipa1=nova_equipa1->next_e;
	}

	while(nova_equipa2->next_e !=NULL){ /*procura o jogo na Hash Table das equipas*/
		if(strcmp(nova_equipa2->equipa->nome,novo_jogo->jogo->equipa2)==0)
			break;
		nova_equipa2=nova_equipa2->next_e;
	}


	if((arg2 > arg3 && novo_jogo->jogo->score1 > novo_jogo->jogo->score2) || (arg2==arg3 && novo_jogo->jogo->score1 == novo_jogo->jogo->score2)){ 
		/*caso o primeiro score a ser alterado seja maior que o segundo, e caso o jogo (antes de ser alterado) tinha o primeiro valor maior que o segundo
		ou caso seja um empate, o valor do finalscore das equipas nao e alterado, mas o score do jogo sim*/

		novo_jogo->jogo->score1 = arg2;
  		novo_jogo->jogo->score2 = arg3;
  		return;
  	}

	if(arg2 > arg3 && novo_jogo->jogo->score1 < novo_jogo->jogo->score2){
		/*caso o primeiro score a ser alterado seja maior que o segundo, e caso o jogo (antes de ser alterado) tinha o primeiro valor menor que o segundo
		logo, no valor do finalscore da primeira equipa adiciona-se 1, e no valor do finalscore da segunda equipa retira-se 1*/
		nova_equipa1->equipa->finalscore++;
		nova_equipa2->equipa->finalscore--;
		novo_jogo->jogo->score1 = arg2;
  		novo_jogo->jogo->score2 = arg3;
  		return;
	}
	
	if(arg2 > arg3 && novo_jogo->jogo->score1 == novo_jogo->jogo->score2){
		/*caso o primeiro score a ser alterado seja menor que o segundo, e caso o jogo (antes de ser alterado) tinha o primeiro valor igual que o segundo
		logo, no valor do finalscore da primeira equipa adiciona-se 1*/
		nova_equipa1->equipa->finalscore++;
		novo_jogo->jogo->score1 = arg2;
  		novo_jogo->jogo->score2 = arg3;
  		return;
	}

	if(arg2 < arg3 && novo_jogo->jogo->score1 == novo_jogo->jogo->score2){
		/*caso o primeiro score a ser alterado seja menor que o segundo, e caso o jogo (antes de ser alterado) tinha o primeiro valor igual que o segundo
		logo, no valor do finalscore da segunda equipa adiciona-se 1*/
		nova_equipa2->equipa->finalscore++;
		novo_jogo->jogo->score1 = arg2;
  		novo_jogo->jogo->score2 = arg3;
  		return;
	}

	if(arg2 < arg3 && novo_jogo->jogo->score1 > novo_jogo->jogo->score2){
		/*caso o primeiro score a ser alterado seja menor que o segundo, e caso o jogo (antes de ser alterado) tinha o primeiro valor maior que o segundo
		logo, no valor do finalscore da primeira equipa retira-se 1, e no valor do finalscore da segunda equipa adiciona-se 1*/
		nova_equipa1->equipa->finalscore--;
		nova_equipa2->equipa->finalscore++;
		novo_jogo->jogo->score1 = arg2;
  		novo_jogo->jogo->score2 = arg3;
  		return;
	}
	if(arg2 == arg3 && novo_jogo->jogo->score1 > novo_jogo->jogo->score2){
		/*caso o primeiro score a ser alterado seja igual que o segundo, e caso o jogo (antes de ser alterado) tinha o primeiro valor maior que o segundo
		logo, no valor do finalscore da primeira equipa retira-se 1*/
		nova_equipa1->equipa->finalscore--;
		novo_jogo->jogo->score1 = arg2;
  		novo_jogo->jogo->score2 = arg3;
  		return;
	}

	if(arg2 == arg3 && novo_jogo->jogo->score1 < novo_jogo->jogo->score2){
		/*caso o primeiro score a ser alterado seja igual que o segundo, e caso o jogo (antes de ser alterado) tinha o primeiro valor menor que o segundo
		logo, no valor do finalscore da segunda equipa retira-se 1*/
		nova_equipa2->equipa->finalscore--;
		novo_jogo->jogo->score1 = arg2;
  		novo_jogo->jogo->score2 = arg3;
  		return;
	}

	if(arg2 < arg3 && novo_jogo->jogo->score1 < novo_jogo->jogo->score2){
		/*caso o primeiro score a ser alterado seja menor que o segundo, e caso o jogo (antes de ser alterado) tinha o primeiro valor menor que o segundo,
		 o valor do finalscore das equipas nao e alterado, mas o score do jogo sim*/
		novo_jogo->jogo->score1 = arg2;
  		novo_jogo->jogo->score2 = arg3;
  		return;
  	}
}


/*#################################################################################################################################################
Retira um jogo da Hash Table

Na funcao main, ao ativar o comando r, esta sera a funcao utilizada.

Caracteristicas da funcao:

Formato de entrada: 'r nome'
Formato de saida: NADA
Erros: 
- 'Jogo inexistente.' no caso de nao existir nenhum jogo com esse nome no sistema.
###################################m##############################################################################################################*/
void remover(int i,Jogoslist* nova, Nodo_jogo** table, Nodo_equipa** table_e){
	char arg1[MAXNAME]; 
	char frase;
	scanf("%c", &frase);
	scanf("%[^:\n]", arg1);
	

	if(search(table, arg1)==-1){ /*procura se o jogo existe*/
		printf("%d Jogo inexistente.\n",i);
		return; 
	}
	else{
		apaga(nova, arg1, table, table_e);
		return;
	}
}


/*#################################################################################################################################################
Ordenar pela ordem de entrada

Na funcao main, ao ativar o comando r, esta sera a funcao utilizada.

Caracteristicas da funcao:

Formato de entrada: 'r nome'
Formato de saida: NADA
Erros: 
- 'Jogo inexistente.' no caso de nao existir nenhum jogo com esse nome no sistema.
###################################m##############################################################################################################*/
void ordena(int i, int *teams, Nodo_equipa** table){
	Nodo_equipa* aux = NULL;
	int num_equipas = *teams;
	char **array = malloc(num_equipas*sizeof(char*)); /*double pointer porque e uma array de arrays de strings*/
	char temp[MAXNAME];
	int k = 0;
	int j = 0;
	int max_score=0; /*guarda o valor maximo de pontuacao*/
	malloc_array(array, num_equipas);

	if(num_equipas==0){ /*se nao houver equipas nao imprime nada e liberta-se espaco na memoria*/
		for(j= 0; j<num_equipas; j++){
			free(array[j]);
	}
	free(array);
	return;
	}

	for(j = 0; j<SIZE;j++){ /*vai procurar pela Hash Table das equipas*/
		aux = table[j];
		while(aux!=NULL){
			if(aux->equipa->finalscore == max_score){ /*caso tenha encontrado uma pontuacao igual ao mas_score, entao adiciona-se o nome da equipa
				no array e incrementa a posicao*/
				strcpy(array[k],aux->equipa->nome);
				k++;
			}
			if(aux->equipa->finalscore > max_score){ /*caso tenha encontrado uma pontuacao de equipa maior que o max_score, entao retira-se tudo o 
				que foi colocado nos arrays e coloca-se na primeira posicao o novo nome da equipa*/
				max_score = aux->equipa->finalscore;
				clean_array(array, num_equipas);
				strcpy(array[0],aux->equipa->nome);
				k=1;
			}

		aux = aux -> next_e;
		}
	}
	printf("%d Melhores %d\n",i, max_score);/*apenas faz este printf caso o array tenho algo dentro*/

	/*funcao para ordenar o nome das equipas do array*/
	for(k=0;k<num_equipas;k++){
    	for(j=k+1;j<num_equipas;j++){
        	if(strcmp(array[j],"\0")!=0 && strcmp(array[k],"\0")!=0){
	         	if(strcmp(array[k],array[j])>0){
	            	strcpy(temp,array[k]);
	            	strcpy(array[k],array[j]);
	           		strcpy(array[j],temp);
	         	}
	        }
	    }
	}

	/*funcao para imprimir as equipas*/
	for(j=0; j<num_equipas; j++){
		if(strcmp(array[j],"\0")== 0)
			break;
		printf("%d * %s\n", i, array[j]);
	}
	/*apos ter impresso tudo, liberta espaco na memoria*/
	for(j= 0; j<num_equipas; j++){
		free(array[j]);
	}
	free(array);
}


/*#################################################################################################################################################
main

Esta e a funcao principal do programa.
E nesta funcao que todos os comandos sao selecionados. O programa termina quando se utiliza o comando x
#################################################################################################################################################*/

int main(){
	char frase = '\0';
	int i=0,team_counter=0;
	Jogos *aux = NULL;
	Jogoslist* newgamelist = NULL;
	int *teams = NULL;
	Nodo_jogo** hashtable_j; 
	Nodo_equipa** hashtable_e;
	
	newgamelist = inicializa_l_jogos(); /*incializa a lista dos jogos*/
	hashtable_j = (Nodo_jogo**)malloc(SIZE*sizeof(Nodo_jogo));/*aloca espaco na memoria para a Hash Table dos jogos*/
	inicializa_jogo(hashtable_j);/*incializa a Hash Table dos jogos*/
	hashtable_e = (Nodo_equipa**)malloc(SIZE*sizeof(Nodo_equipa));/*aloca espaco na memoria para a Hash Table das equipas*/
	inicializa_equipa(hashtable_e);/*incializa a Hash Table das equipas*/
	teams = &team_counter; /*variavel usada para contar o numero de equipas*/

	while (frase != 'x'){
		scanf("%c", &frase);
		switch(frase){
			case 'a':
			i++;
			adiciona_jogo(i,newgamelist,hashtable_j,hashtable_e);
			break;

			case 'A':
			i++;
			adiciona_equipa(i,hashtable_e,teams);
			break;

			case 'l':
			i++;
			aux = newgamelist->head;
			lista(i,aux);
			break;

			case 'p':
			i++;
			procurajogo(i,hashtable_j); 
			break; 

			case'P': 
			i++;
			procuraequipa(i,hashtable_e);
			break; 

			case 's':
			i++;
			altera_pontos(i,hashtable_j, hashtable_e); 
			break;

			case 'r': 
			i++;
			remover(i,newgamelist, hashtable_j, hashtable_e); 
			break; 

			case 'g':
			i++; 
			ordena(i, teams, hashtable_e); 
			break;
			
		}
	}
	return 0;
}