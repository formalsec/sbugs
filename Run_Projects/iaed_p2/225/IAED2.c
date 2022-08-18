#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Valores maximos de um nome (jogo e equipas) e tamanho maximo de um jogo,
ou seja o tamanho da hashtable dos jogos*/
#define MAX_NAME  1025
#define SIZE_GAME 30011

/****************ESTRUTURAS E VARIAVEIS GLOBAIS****************/

/*Tratamento de equipas*/
/*estrutura para uma equipa*/
typedef struct
{
	char *tName;
	int wins;
} Team;

/*estrutura para a lista ligada*/
typedef struct nodeT nodeT;
typedef struct nodeT* linkT;
struct nodeT{
	Team *team;
	nodeT *next;
};
/*hashtable das equipas*/
linkT teams[SIZE_GAME*2];
static linkT topT = NULL;
static linkT bottomT = NULL;

/*tratamento de jogos*/

/*estrutura para um jogo*/
typedef struct
{
	char *gName;
	linkT team1, team2;
	int score1, score2, winTeam;
} Game;

typedef struct nodeG nodeG;
typedef struct nodeG* linkG;
struct nodeG{
	Game *game;
	nodeG *next;
};
linkG hashT_game[SIZE_GAME];
static linkG top = NULL;
static linkG bottom = NULL;

/*counter das linhas de comando*/
int commands=1;


/****************FUNCOES AUXILIARES****************/

/*
	funcao (int) hash:
	-Argumentos: char *name- nome que sera utilizado para calcular a hash key
				 int M- tamanho da hashtable
	-Realiza uma conta especifica para calcular o hash key
	-Retorna o indice em que se ira inserir o nome numa dada hashtable 
*/
int hash(char *name, int M)
{
	int h=0, a=127;

	for(; *name !='\0';name++)
		h = (a*h + *name) % M;
	return h;
}

/*
	funcao (void) init_hashT:
	-Coloca todos os elementos da hashtable de equipas a NULL
*/
void init_hashT()
{
	int i; 
	for(i=0; i < SIZE_GAME*2; i++)
		teams[i] = NULL;
}

/*
	funcao (void) init_hashG:
	-Coloca todos os elementos da hashtable de jogos a NULL
*/
void init_hashG()
{
	int i;
	for(i=0; i < SIZE_GAME; i++)
		hashT_game[i] = NULL;
}

/*
	funcao (linkG) new_nodeG:
	-Argumentos: Game *g- ponteiro para um jogo a querer inserir
	-Dado o ponteiro para um jogo, cria um no com a infromacao desse ponteiro
	-Retorna o no criado
*/
linkG new_nodeG(Game *g)
{
	linkG x = malloc(sizeof(nodeG));
	x->game = g;
	x->next = NULL;
	return x; 
}

/*
	funcao (linkT) new_nodeT:
	-Argumentos: Team *t- ponteiro para uma equipa a querer inserir
	-Dado o ponteiro para uma equipa, cria um no com a infromacao desse ponteiro
	-Retorna o no criado
*/
linkT new_nodeT(Team *t)
{
	linkT x = malloc(sizeof(nodeT));
	x->team = t;
	x->next = NULL;
	return x;
}

/*
	funcao (void) gameInsert:
	-Argumentos: Game *g- ponteiro para um jogo que se quer inserir na hashtable
				 linkG hashT[]- hashtable de listas ligadas
	-Descoberta a hashkey e liga o ponteiro para o jogo a hashtable
*/
void gameInsert(Game *g, linkG hashT[]){
	linkG i;
	int k = hash(g->gName, SIZE_GAME);
	i = new_nodeG(g);
	i->next = hashT[k];
	hashT[k] = i;
}

/*
	funcao (void) teamInsert:
	-Argumentos: Team *t- ponteiro para uma equipa que se quer inserir na hashtable
				 linkT hashT[]- hashtable de listas ligadas
	-Descoberta a hashkey e liga o ponteiro para a equipa a hashtable
*/
void teamInsert(Team *t, linkT hashT[])
{
	linkT i;
	int k = hash(t->tName, SIZE_GAME*2);
	i = new_nodeT(t);
	i->next = hashT[k];
	hashT[k] = i;
}

/*
	funcao (linkT) searchT:
	-Argumentos: char *name- nome que se quer procurar na hashtable de equipas
	-Dado um certo nome itera-se pelo indice correspondente a esse nome na hashtable
	-Retorna NULL caso nao encontre nenhuma equipa com esse nome, caso encontre
	retorna o node correspondente a essa equipa 
*/
linkT searchT(char *name)
{
	linkT t;
	int i = hash(name, SIZE_GAME*2);
	for(t= teams[i]; t!=NULL; t = t->next)
		if(!strcmp(t->team->tName, name))
			return t;
	return NULL;
}

/*
	funcao (linkG) searchG:
	-Argumentos: char *name- nome que se quer procurar na hashtable de jogs
	-Dado um certo nome itera-se pelo indice correspondente a esse nome na hashtable
	-Retorna NULL caso nao encontre nenhum jogo com esse nome, caso encontre
	retorna o node correspondente a esse jogo 
*/
linkG searchG(char *name)
{
	linkG g;
	int i = hash(name, SIZE_GAME);
	for(g= hashT_game[i]; g!=NULL; g = g->next)
		if(!strcmp(g->game->gName, name))
			return g;
	return NULL;
}

/*
	funcao (void) freeMemoryLlistT:
	-Argumentos: linkT head- node que se tenciona apagar
				 int mode- flag que decide se se apaga a equipa ligada a lista
	-liberta toda a memoria alocada pela lista, caso mode seja 1 apaga a equipa
	ligada a lista. Tambem libertando a memoria alocada pelo no e caso mode seja 
	1 apaga a euipa ligada a esse node. Assim libertando toda a memoria alocada 
	para essa dada equipa.
*/
void freeMemoryLlistT(linkT head, int mode)
{  	
	linkT i = head;
	linkT next;

   while (i != NULL){
    	next = i->next;	
    	if (mode)
    	{
			free(i->team->tName);
			free(i->team);
		}
		free(i);
    	i = next;
    }
}


/*
	funcao (void) free_node:
	-Argumentos: linkG node- node que se tenciona apagar
				 int mode- flag que decide se se apaga o jogo ligado ao no
	-Liberta a memoria alocada pelo no e caso mode seja 1 apaga o jogo ligado a esse node.
*/
void free_node(linkG node, int mode)
{
	if (mode){
		free(node->game->gName);
		node->game->team1=NULL;
		node->game->team2=NULL;
		free(node->game);
	}
	free(node);
}

/*
	funcao (void) free_node:
	-Argumentos: linkG node- node que se tenciona apagar
				 int mode- flag que decide se se apaga o jogo ligado a lista
	-Liberta a memoria alocada pela lista e caso mode seja 1 apaga o jogo ligado a essa lista.
*/
void free_memory_list(linkG head, int mode)
{  	
	linkG i = head;
	linkG next;

   while (i != NULL){
    	next = i->next;	
    	free_node(i, mode);
    	i = next;
    }
}

/*
	funcao (void) freeMemory:
	-Liberta toda a memoria alocada pelo porgrama. Apaga a lista principal (tanto de equipas
	como de jogos) e tambem todas as equipas e jogos criados. Liberta tambem a memoria 
	alocada pelos nos das hastables
*/
void free_memory(){
	int i;
	free_memory_list(top, 1);
	for (i = 0; i < SIZE_GAME; i++){
		free_memory_list(hashT_game[i], 0);
	}
	freeMemoryLlistT(topT, 1);
	for (i = 0; i < SIZE_GAME*2; i++){
		freeMemoryLlistT(teams[i], 0);
	}
}

/*
	funcao (void) delete:
	-Argumentos: linkG head- topo da lista do node que se tenciona apagar
				 const char *name- nome do jogo a ser apagado
				 int mode- flag que decide se se apaga o jogo ligado ao no
	-Apaga um node da lista. Se a lista recebida for o topo, verifica-se caso
	seja o ultimo elemento, verificando-se altera-se o bottom para o node anterior
*/
linkG delete(linkG head, const char* name, int mode){	
	linkG t, prev;
	for(t = head, prev = NULL; t != NULL;
		prev = t, t = t->next){
		if (strcmp(t->game->gName, name) == 0){
			if (t == head){	
				head = t->next;
			}
			else{
				if (head == top)	
					if (t->next == NULL)												
						bottom = prev;
				prev->next = t->next;
			}
			free_node(t, mode);
			return head;
		}
	}
	return head;
}



/****************FUNCOES PRINCIPAIS****************/

/*
	funcao (void) a:
	-Argumentos: char *gName- nome do jogo;
				 char *team1- nome da equipa 1;
				 char *team2- nome da equipa 2;
				 int score1- pontuacao da equipa 1;
				 int score2- pontuacao da equipa 2.
	-Dados um nome para o jogo, das equipas e as suas pontuacoes, cria um jogo,
	alocando a memoria necessaria para o mesmo.
	-Retorna erro se:
		-ja existir um jogo com esse nome;
		-nao existir uma equipa com o nome dado.
*/
void a(char *gName, char *team1, char *team2, int score1, int score2)
{

	Game *newG;
	linkG i = searchG(gName);
	int p=0;

	linkT t1 = searchT(team1);
	linkT t2 = searchT(team2);
	
	newG = (Game*)malloc(sizeof(Game));

	
	if(i != NULL)
	{
		printf("%d Jogo existente.\n", commands);
		free(newG);
	}
	else if(t1 == NULL || t2==NULL)
	{
		printf("%d Equipa inexistente.\n", commands);
		free(newG);
	}

	else
	{
		
		while (gName[p] != '\0') p++;
		
		newG->gName = (char*)malloc(sizeof(char) * (p+1));

		strcpy(newG->gName, gName);





		newG->team1 = t1;
		newG->team2 = t2;

		newG->score1 = score1;
		newG->score2 = score2;

		if(newG->score1 > newG->score2)
		{
			t1->team->wins++;
			newG->winTeam =1;
		}
		else if(newG->score2 > newG->score1)
		{
			t2->team->wins++;
			newG->winTeam =2;
		}

		else
			newG->winTeam =0;



		if (top == NULL){	
		top = new_nodeG(newG);
		bottom = top;
		}
		else{
			bottom->next = new_nodeG(newG);
			bottom = bottom->next;

		}

		

		gameInsert(newG, hashT_game);
		
	}		
	
}

/*
	funcao (void) l:
	-Lista todos os jogos e as informacoes respetivas a cada um por ordem de insercao
	-Retorna para o standard output uma lista com o numero do comando, nome do jogo,
	nome das equipas e os respetivos scores.
*/
void l()
{
	linkG i = top;
	while(i != NULL){
			printf("%d %s %s %s %d %d\n",commands, i->game->gName,
								  i->game->team1->team->tName,
								  i->game->team2->team->tName,
								  i->game->score1,
								  i->game->score2);

		i = i->next;
	}	
}

/*
	funcao (void) p:
	-Argumentos: char *name- nome do jogo a ser procurado.
	-Dado um nome dum jogo, caso esse exista, lista as informacoes do mesmo
	-Retorna para o standar output o nunmero do comando, nome do jogo e das equipas
	e o score atual com que estas se encontram.
	-Retorna erro se:
		-nao existir um jogo com esse nome.
*/
void p(char *name)
{
	linkG i = searchG(name);
	if(i==NULL)
		printf("%d Jogo inexistente.\n", commands);
	else
		printf("%d %s %s %s %d %d\n",commands, i->game->gName,
								  i->game->team1->team->tName,
								  i->game->team2->team->tName,
								  i->game->score1,
								  i->game->score2);
}

/*
	funcao (void) r:
	-Argumentos: char *name- nome do jogo a ser removido.
	-Dado um nome dum jogo, caso esse exista, esse sera apagado.
	-Retorna erro se:
		-nao existir um jogo com esse nome.
*/
void r(char *name)
{
	linkG i = searchG(name);
	int gN;
	if(i==NULL)
		printf("%d Jogo inexistente.\n", commands);
	else
	{
		gN = hash(name, SIZE_GAME);
		if(i->game->score1 > i->game->score2)
			i->game->team1->team->wins--;
		else if(i->game->score1 < i->game->score2)
			i->game->team2->team->wins--;

		hashT_game[gN] = delete(hashT_game[gN], name, 0);
		top = delete(top, name, 1);
	}	
}

/*
	funcao (void) s:
	-Argumentos: char *name- nome do jogo a ser procurado;
				 int score1- pontuacao da equipa 1 a ser alterada;
				 int score2- pontuacao da equipa 2 a ser alterada;
	-Dados um nome dum jogo, e duas pontuacoes, caso o jogo exista, altera as pontuacoes
	desse jogo para as fornecidas por argumento.
	-Retorna erro se:
		-nao existir um jogo com esse nome.
*/
void s(char *name, int score1, int score2)
{
	linkG i = searchG(name);
	if(i==NULL)
		printf("%d Jogo inexistente.\n", commands);
	else
	{
		if(i->game->winTeam==1)
			i->game->team1->team->wins--;
		else if(i->game->winTeam==2)
			i->game->team2->team->wins--;
		i->game->score1= score1;
		i->game->score2 = score2;
		if(score1 > score2)
		{
			i->game->team1->team->wins++;
			i->game->winTeam=1;
		}
		else if(score1 < score2)
		{
			i->game->team2->team->wins++;
			i->game->winTeam=2;
		}

		else
			i->game->winTeam = 0;
	}
}

/*
	funcao (void) A:
	-Argumentos: char *name- nome da equipa.
	-Dado um nome para a equipa, cria uma equipa alocando a memoria necessaria para a mesma.
	-Retorna erro se:
		-ja existir uma equipa com o nome dado.
*/
void A(char *name)
{
	Team *newT;
	linkT i = searchT(name);
	int p=0;

	
	newT = (Team*)malloc(sizeof(Team));

	
	if(i != NULL)
	{
		printf("%d Equipa existente.\n", commands);
		free(newT);
	}
	else
	{
		
		while (name[p] != '\0') p++;
		
		newT->tName = (char*)malloc(sizeof(char) * (p+1));

		strcpy(newT->tName, name);

		newT->wins = 0;

		if (topT == NULL){	/*binds newG to the main_list*/
		topT = new_nodeT(newT);
		bottomT = topT;
		}
		else{
			bottomT->next = new_nodeT(newT);
			bottomT = bottomT->next;
		}

		

		teamInsert(newT, teams);
		
	}
}

/*
	funcao (void) P:
	-Argumentos: char *name- nome da equipa.
	-Dado um nome para uma equipa, caso essa exista, lista-se o nome da mesma, 
	assim como o numero de jogos ganhos.
	-Retorna para o standard output o numero do comando, o nome da equipa e
	o numero de jogos ganhos.
	-Retorna erro se:
		-nao existir uma equipa com o nome dado.
*/
void P(char *name)
{
	linkT t = searchT(name);

	if(t==NULL)
		printf("%d Equipa inexistente.\n", commands);
	else
		printf("%d %s %d\n", commands, name, t->team->wins);
}


/*
	funcao (void) g:
	-Encontra todas as equipas que venceram mais jogos e lista-as por ordem lexicografica. 
	-Retorna para o standard output uma lista contendo cada posicao o numero do comando, 
	o caracter "*" e o nome da equipa.
*/
void g()
{
	linkT i = topT;
	Team *t, *aux_x;
	char *aux_aux;
	char **t_aux;
	int k, j;
	int howMany =0;
	int most_wins=0;
	t = (Team*)calloc(1,sizeof(Team));

	while(i != NULL){
		if(i->team->wins > most_wins || (i->team->wins==0 && howMany==0))
		{

			t = (Team*)realloc(t, sizeof(Team));
			t[0] = *i->team;
			most_wins = i->team->wins;
			howMany = 1;
		}
		else if(i->team->wins == most_wins)
		{
			howMany++;
			aux_x = (Team*)realloc(t, sizeof(Team)*howMany);
			if(aux_x)
			{
				t = aux_x;
			}
			t[howMany-1] = *i->team;
		}
		i = i->next;
	}
	t_aux = (char**)malloc(sizeof(char*)*howMany);
	for(k=0; k < howMany; k++)
	{
		t_aux[k] = (char*)malloc(sizeof(char)*strlen((t+k)->tName)+1);
		strcpy(t_aux[k], (t+k)->tName);
	}
	for(k=0; k < howMany; k++)
	{
		for(j=k+1; j < howMany; j++)
		{

			aux_aux = (char*)malloc(sizeof(char)*strlen(t_aux[j])+1);
			if(strcmp(t_aux[k], t_aux[j])>0)
			{
				strcpy(aux_aux,t_aux[j]);
				t_aux[j] = (char*)realloc(t_aux[j], sizeof(char)*strlen(t_aux[k])+1);
				strcpy(t_aux[j],t_aux[k]);
				t_aux[k] = (char*)realloc(t_aux[k], sizeof(char)*strlen(aux_aux)+1);
				strcpy(t_aux[k], aux_aux);
			}
			free(aux_aux);
		}

	}
	if(howMany)
		printf("%d Melhores %d\n", commands, most_wins);
	for(k=0; k < howMany; k++)
	{
		printf("%d * %s\n", commands, t_aux[k]);
		free(t_aux[k]);
	}
	free(t_aux);
	free(t);

}


/****************CICLO MAIN****************/

/*
	-Sao feitas as inicializacoes das duas hashtables.
	-Faz alocacoes para tres variaveis, de tamanho variavel ao longo da 
	execucao do programa.
	-Faz as chamadas as diferentes funcoes principais, conforme indicado no comando fornecido.
	-liberta a memoria alocada para as tres variaveis alocadas no inicio do mesmo.
	-liberta toda a memoria utilizada ao longo do programa.
*/
int main()
{
	int score1, score2;
	char command, *name, *team1, *team2;




	init_hashT();
	init_hashG();

	name = (char*)malloc(sizeof(char)*MAX_NAME);
	team2 = (char*)malloc(sizeof(char)*MAX_NAME);
	team1 = (char*)malloc(sizeof(char)*MAX_NAME);
	


	while((command = getchar()) != 'x')
	{
		
			
			switch(command)
			{

				case 'a':

					getchar();

					scanf("%[^:]:%[^:]:%[^:]:%d:%d", name, team1, team2, &score1, &score2);
					a(name, team1, team2, score1, score2);
					commands++;
					break;
				case 'l':
					l();
					commands++;
					break;

				case 'p':
					getchar();
					scanf("%[^\n]", name);
					p(name);
					commands++;
					break;

				case 'r':
					getchar();
					scanf("%[^\n]", name);
					r(name);
					commands++;
					break;

				case 's':
					getchar();
					scanf("%[^:]:%d:%d", name, &score1, &score2);
					s(name, score1, score2);
					commands++;
					break;

				case 'A':
					getchar();
					scanf("%[^\n]", name);
					A(name);
					commands++;
					break;

				case 'P':
					getchar();
					scanf("%[^\n]", name);
					P(name);
					commands++;
					break;
				case 'g':
					g();
					commands++;
					break;
			}

	}
	free(name);
	free(team1);
	free(team2);
	free_memory();
	
	return 0;
}