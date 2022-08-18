#include "estrutura.h"

/*Funcao principal de adicionar uma equipa a hashtable das equipas e e importante porque sem
ela nao seria possivel nem queriar o jogo que e a funcao seguinte*/
void adicionaequipa(equipas *hashtable_equipas, char *nome_equipa, int NL)	/* COMANDO A */
{
	int id;
	if (lookupequipa(hashtable_equipas, nome_equipa) == NULL) /* Verifica se a equipa existia
	anteriormente e se nao existir da o erro pretendido */
	{
		id = hash(nome_equipa);
		hashtable_equipas[id] = insertBeginequipas(hashtable_equipas[id], nome_equipa);
		/*Atraves do id criado pela hashtable descobre se qual a linked list em que 
		temos de inserir a equipa e depois chama se a funcao que insere a equipa na 
		lista ligada*/
	}
	else
	{
		printf("%d Equipa existente.\n", NL);
	}
}

/*Funcao principal que cria um jogo e o adiciona a hashtable dos jogos onde cada jogo tem
um nome duas equipas e o resultado do jogo e aumenta o valor das vitorias das equipas se
esta ganahr ou seja se o seu score for maior que a da outra equipa*/
int adicionajogo(jogos *hashtable_jogos, equipas *hashtable_equipas, 
	char *nome, char *equipa1, char *equipa2, int score1, int score2, int num_jogos, int NL) 
	/* COMANDO a */
{
	int id = hash(nome); /*Calcula o id da tabela onde o jogo deve ficar*/
	equipas x = lookupequipa(hashtable_equipas, equipa1); 
	equipas y = lookupequipa(hashtable_equipas, equipa2);
	if (lookupjogo(hashtable_jogos, nome) == NULL) /* Verifica se o jogo existe */
	{
		if (lookupequipa(hashtable_equipas, equipa1) != NULL && 
			lookupequipa(hashtable_equipas, equipa2) != NULL) /* Verifica se as equipa existem*/
		{	
 			hashtable_jogos[id] = insertBeginjogos(hashtable_jogos[id], nome, equipa1, equipa2,
 				score1, score2, num_jogos); /* Insere o jogo na hashtable dos jogos mais 
 				especificamente nas linked list associada ao indice calculado pela hash */
 			if (score1 > score2)
 			{
 				x->vitorias++; 
 			}
 			if (score1 < score2)
 			{
 				y->vitorias++; 
 			}
 			return 1;
		}
		else
		{
			printf("%d Equipa inexistente.\n", NL);		
		}
	}
	else
	{
		printf("%d Jogo existente.\n", NL);
	}
	return 0;
}

/*Funcao principal com a funcao de listar os jogos pela ordem que foram introduzidos
e para o realizar foi criada um parametro na estrutura que foi o num_jogos que e 
um contador para os jogos que ja foram introduzidos e que e incrementado sempre
que a funcao de adicionar o jogo ocorre e assim percorre se esse contador e
a tabela dos jogos em cada indice percorrendo assim a linked list e se
o nome encontrado nessa linked list for igual ao que foi inserido na posicao
igual a do contador da se print e assim lista tudo por ordem
O num jogos funciona tambem como indice de cada vez que se adiciona jogo 0
0 e o num jogos */
void listaordemjogos(jogos *hashtable_jogos, int num_jogos, int NL) /* COMANDO l*/
{
	int i, e;
	jogos x;
	for (e = 0; e < num_jogos; e++) /*Percorre o contador*/
	{
		for (i = 0; i < MAX_TAMANHO_TABELA; i++) /*Percorre a tabela*/
		{
			for (x = hashtable_jogos[i]; x != NULL ; x = x->next) /*Percorre a linked list*/
			{
				if (x->num_jogos == e) /*Se o nome com o indice num jogo for igual a e
				da se print*/
				{
					printf("%d %s %s %s %d %d\n", NL, x->nome, x->equipa1, x->equipa2, 
						x->score1, x->score2);
				}
			}
		}
	}
}


/* Funcao principal que procura um jogo que esteja na hashtable e se nao houver da erro
e faz isto a partir do uso da funcao lookup que faz exatamente isso */
void procurajogo(jogos *hashtable_jogos, char* nome, int NL) /* COMANDO p */
{
	jogos x = lookupjogo(hashtable_jogos, nome); /* cria ponteiro auxiliar que aponta para
	a estrutura do jogo em questao */
	if (x != NULL) 
	{
		printf("%d %s %s %s %d %d\n", NL, x->nome, x->equipa1, x->equipa2, x->score1, x->score2);
	}
	else
	{
		printf("%d Jogo inexistente.\n", NL);
	}
}


/*Funcao principal que apaga o jogo tambem atraves do uso da lookup tambem e a partir do 
momento que se apaga um constituinte da lista ligada liga se o ponteiro anterior
ao next pois removeu se um expaco no meio deles mas em primeiro lugar tem que ir buscar o
resultado do jogo que se vai apagar para ver qual a equipa que ganhou e desta forma diminuir
o valor das suas vitorias na estrutura da equipa*/
jogos apagajogo(jogos *hashtable_jogos, equipas *hashtable_equipas, char *nome, int NL)
/* COMANDO r */
{
	int id = hash(nome);
	jogos x = hashtable_jogos[id];
	jogos anterior;
	equipas y;
	equipas z;
	if (lookupjogo(hashtable_jogos, nome) != NULL) /* se o jogo nao existir da print*/
	{
		y = lookupequipa(hashtable_equipas, x->equipa1);
		z = lookupequipa(hashtable_equipas, x->equipa2);
		if (x->score1 > x->score2)
		{
			y->vitorias--; /*se no jogo que se vai apagar a equipa1 ganhou diminui se o 
			numero de vitorias dessa equipa na estrutura da equipa*/
		}
		else if (x->score1 < x->score2)
		{
			z->vitorias--; /*diminui o valor das vitorias da equipa que ganhou*/
		}
		for (x = hashtable_jogos[id], anterior = NULL; x != NULL; anterior = x, x = x->next)
			/*Percorre a linked list atualizando o anterior e o next para quando se apagar
			nao deixar espacos livres no meior ou 'buracos*/
		{
			if (strcmp(x->nome, nome) == 0)
			{	
				if (x == hashtable_jogos[id]) 
				{
					hashtable_jogos[id] = x->next;
				}
				else
				{
					anterior->next = x->next;
				}
				free(x->nome); /*Da free de todas as strings a que foi necessario 
				alocar memoria*/
				free(x->equipa1);
				free(x->equipa2);
				free(x);
				return hashtable_jogos[id];
			}
		}
	}
	else
	{
		printf("%d Jogo inexistente.\n", NL);
	}
	return hashtable_jogos[id];
}


/* Funcao principal que procura uma equipa na hashtable das equipas atraves da fucncao
lookup tambem e da print dos seus constituintes tal como foi feito na funcao procurajogo*/
void procuraequipa(equipas *hashtable_equipas, char *nome_equipa, int NL) /* COMANDO P */
{
	equipas x = lookupequipa(hashtable_equipas, nome_equipa); 
	if (x != NULL)
	{
		printf("%d %s %d\n", NL, x->nome_equipa, x->vitorias);
	}
	else
	{
		printf("%d Equipa inexistente.\n", NL);
	}
}

/*Funcao principal que altera o score e as vitorias das equipas a partir desse score que foi
alterado. Procurando um jogo na tabela dos jogos atraves do uso de ponteiros auxiliares 
e ao apontar para a estrutura do jogo e da equipa consegue se aceder ao score anterior
e fazer as alteracoes de score enquanto se aumenta ou diminui as vitorias*/
void alterascore(jogos *hashtable_jogos, equipas *hashtable_equipas, char *nome, int score1, 
	int score2, int NL) /* COMANDO s */
{
	jogos x;
	equipas y;
	equipas z;
	if (lookupjogo(hashtable_jogos, nome) != NULL)
	{
		x = lookupjogo(hashtable_jogos, nome);
		y = lookupequipa(hashtable_equipas, x->equipa1);
		z = lookupequipa(hashtable_equipas, x->equipa2);
		if (x->score1 == x->score2) /*Testa se o jogo antigo era um empate*/
		{
			if (score1 > score2) 
			{
				y->vitorias++; /*Se o anterior era empate e agora a equipa1 ganha aumenta 
				se as vitorias da equipa1*/
			}
			else if (score1 < score2)
			{
				z->vitorias++; /*anterior e empate e agora equipa2 ganha aumenta vitorias 
				da equipa2*/
			}
		}
		else if (x->score1 < x->score2) 
		{
			if (score1 == score2)
			{
				z->vitorias--; /*se o jogo anterior foi vitoria da equipa2 e agora e empate
				o numero de vitorias da equipa2 diminui*/ 
			}
			else if (score1 > score2) 
			{
				y->vitorias++; /*se o jogo anteriro foi vitoria da equipa2 e agora a equipa1
				ganha o numero de vitorias da equipa1 aumenta e o da equipa2 diminui*/
				z->vitorias--;
			}
		}
		else if (x->score1 > x->score2)
		{
			if (score1 == score2)
			{
				y->vitorias--; /*se o jogo anterior foi vitoria da equipa1 e agora e empate
				diminui o numero de vitorias da equipa1*/
			}
			else if (score1 < score2)
			{
				y->vitorias--; /*se o jogo anterior foi vitoria da equipa1 e agora  ganha
				a equipa2 diminui vitoria de equipa1 e aumenta da equipa2*/
				z->vitorias++;
			}
		}
		x->score1 = score1; /*O score anterior e atualizado e passa ao que e dado no input*/
		x->score2 = score2;
	}
	else
	{
		printf("%d Jogo inexistente.\n", NL);
	}
}
