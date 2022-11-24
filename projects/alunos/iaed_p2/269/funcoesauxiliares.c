#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "estrutura.h"

/* Funcao auxiliar que cria uma hashtable para os jogos onde no futuro lhe vao ser adicionados
de alguma forma e inicializa-se cada indica da hashtable a NULL pois ainda nao tem nada e 
porque vao ser inseridas em cada um uma linked list para evitar as colisoes entre elementos 
com o mesmo indice.*/
jogos *criar_hashtablejogos()
{
	jogos *hashtable_jogos = can_fail_malloc(MAX_TAMANHO_TABELA * sizeof(struct jogo)); 
	/* Aloca espaco a memoria */
	int p;
	for (p = 0; p < MAX_TAMANHO_TABELA; p++)
	{
		hashtable_jogos[p] = NULL; /* Inicializa cada indice a NULL */
	}
	return hashtable_jogos;
}

/* Funcao auxiliar que basicamente tem a mesma funcao que a hashtable dos jogos mas neste caso
no futuro vao ser adicionadas equipas a tabela e para evitar colisoes cada indice vai ter uma 
linked list tambem em que se o indice originado pela funcao hash for igual adiciona se no 
iniciio da linked list*/
equipas *criar_hashtableequipas()
{
	equipas *hashtable_equipas = can_fail_malloc(MAX_TAMANHO_TABELA * sizeof(struct equipa)); 
	/* Aloca espaco a memoria */
	int p;
	for (p = 0; p < MAX_TAMANHO_TABELA; p++)
	{
		hashtable_equipas[p] = NULL; /* Inicializa cada indice a NULL */
	}
	return hashtable_equipas;
}

 /* Funcao auxiliar diretamente relacionada com as hashtables porque recebendo um uma string 
 origina um valor aleatorio para o indice da hashtable consoante o seu tamanho mas por vezes
 pode criar o mesmo numero e por isso origina colisoes nas hashtables e por isso e que e 
 usado listas ligadas para cada indice */ 
int hash(char *v)
{
	int h, a = 31415, b = 27183;
	for (h = 0; *v != '\0'; v++, a = a * b % (MAX_TAMANHO_TABELA - 1))
		h = (a * h + *v) % MAX_TAMANHO_TABELA;
	return h;
}

/* A funcao NEWJOGO cria um novo jogo atraves do uso de um ponteiro auxiliar*/
jogos NEWJOGO(char* nome, char* equipa1, char* equipa2, int score1, int score2, int num_jogos)
{
	jogos x = can_fail_malloc(sizeof(struct jogo)); 
	/* Aloca espaco livre a memoria com tamanho possivel para guardar a estrutura do jogo */
	x->nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
	/* Aloca espaco a memoria para um string com tamanho do nome mais 1 por causa do \0
	e o mesmo para as equipas */
	x->equipa1 = can_fail_malloc(sizeof(char) * (strlen(equipa1) + 1));
	x->equipa2 = can_fail_malloc(sizeof(char) * (strlen(equipa2) + 1)); 
	x->score1 = score1; 
	x->score2 = score2;
	x->num_jogos = num_jogos;
	strcpy(x->nome, nome); 
	/* O ponteiro aponta para um nome da estrutura e esse e copiado para a variavel nome
	tal como se faz a seguir para as equipas*/
	strcpy(x->equipa1, equipa1); 
	strcpy(x->equipa2, equipa2); 
	x->next = NULL; 
	/* O proximo jogo e NULL pois anda nao existe mas sempre que se cria um novo o ultimo 
	tem que ficar a NULL */
	return x;
}

/* A funcao NEWEQUIPA tem a mesma funcao que a NEWJOGO so que nas circunstancias da equipa */
equipas NEWEQUIPA(char* nome_equipa)
{
	equipas x = can_fail_malloc(sizeof(struct equipa));
	x->nome_equipa = can_fail_malloc(sizeof(char) * (strlen(nome_equipa) + 1));
	x->vitorias = 0; 
	/* As vitorias sao inicializadas a 0 porque o seu valor so aumenta quando uma equipa
	ganha o jogo */
	strcpy(x->nome_equipa, nome_equipa);
	x->next = NULL; /* O ultimo node da lista que esta no indice da hashtable tem que ser NULL*/
	return x;
}

/*Funcao auxiliar com funcao de dar free aos can_fail_mallocs ou seja libertar a memoria que foi 
utilizada para fazer a hashtable dos jogos e os seus constituintes*/
void freehashtable_jogos(jogos *hashtable_jogos)
{
	int i;
	jogos x, next;
	for (i = 0; i < MAX_TAMANHO_TABELA; i++) /* percorre a tabela */
	{
		for (x = hashtable_jogos[i]; x != NULL; x = next) 
		{
			next = x->next;
			free(x->nome); /* Liberta a memoria utilizada pelas strings*/
			free(x->equipa1);
			free(x->equipa2);
			free(x);
		}
	}
	free(hashtable_jogos);
}

/*Funcao auxiliar com a funcao de dar free aos can_fail_mallocs usados para criar a hashtable com
equipas que foram os que foram utilizados na NEWEQUIPA e na de criar a propria hashtable */
void freehashtable_equipas(equipas *hashtable_equipas)
{
	int i;
	equipas x, next;
	for (i = 0; i < MAX_TAMANHO_TABELA; i++)
	{
		for (x = hashtable_equipas[i]; x != NULL; x = next)
		{
			next = x->next;
			free(x->nome_equipa); /* liberta a memoria usada pela string do nome da equipa*/
			free(x);
		}
	}
	free(hashtable_equipas);
}

/*Funcao auxiliar com a funcao de adicionar um jogo ao inicio de uma linked list e 
utilizada pois cada indice da hashtable tem uma linked list*/
jogos insertBeginjogos(jogos head_jogo, char* nome, char *equipa1, char *equipa2, int score1, 
	int score2, int num_jogos)
{
	jogos x = NEWJOGO(nome, equipa1, equipa2, score1, score2, num_jogos); 
	/* Adiciona se a tabela */
	x->next = head_jogo; /* Anda se o valor da cabeca para a direita */
	head_jogo = x; /* Atualiza se o valor da cabeca */
	return x;
}



/* FUncao auxiliar com a funcao de adicionar a equipa no inicio da linked list dos indices da
hashtable das equipas tal como funciona a insertbegin dos jogos*/
equipas insertBeginequipas(equipas head, char* nome_equipa)
{
	equipas x = NEWEQUIPA(nome_equipa); 
	x->next = head;	
	head = x;  
	return x;
}

/*Funcao auxiliar com o objetivo de procurar o jogo na funcao da hashtable e muito
inmportante pois e utilizada para verificar a existencia do jogo e para aceder a
um jogo que esta na tabela basta char esta funcao*/
jogos lookupjogo(jogos *hashtable_jogos, char *nome)
{
	int id = hash(nome); /* obtem se o indice da hashtable onde o jogo esta inserido*/
	jogos x = hashtable_jogos[id]; /*Cria se uma variavel auxiliar que aponta para a estrutura
	do jogo e iguala se ao indice da hashtable dos jogos */
	for (; x != NULL; x = x->next) /* Como em cada indice podem existir varios jogos percorre se
	a linked list a procura do node onde esta inserido*/
	{
		if (strcmp(x->nome, nome) == 0) /* se o auxiliar que aponta para o parametro da 
		estrutura do jogo for igual ao jogo que recebe no input de uma funcao o jogo existe */
			return x;
	}
	return NULL;
}

/*Funcao auxiliar com o objetivo de procurar uma equipa na hashtable das equipas e
basicamente faz se o mesmo que na hashtable de jogos so que neste caso faz se para as equipas*/
equipas lookupequipa(equipas *hashtable_equipas, char *nome_equipa)
{
	int id = hash(nome_equipa);
	equipas x = hashtable_equipas[id];
	for (; x != NULL; x = x->next)
	{
		if (strcmp(x->nome_equipa, nome_equipa) == 0)
		{
			return x;
		}
	}
	return NULL;
}
