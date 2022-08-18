#define DIMENSAO_DO_COMANDO 3079 /* Maximo sera comando + espaco (2) + jogo(1023) + 2 equipas (1023*2) + par de numeros inteiros (4) + : (4) */
#define DIMENSAO_DO_NOME_DE_EQUIPA 1023 
#define DIMENSAO_DO_NOME_DE_JOGO 1023 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Estruturas usadas pelo programa */
/*
Cada __equipa__ e caracterizada por:
* nome: uma string nao vazia, com um maximo de 1023 caracteres
* jogos_ganhos: inteiro que guarda quantos jogos foram ganhos por esta equipa
* apontador: para a proxima equipa na lista
* apontador: para a anterior equipa na lista
*/
typedef struct lista_de_equipas
{
	char *nome;
	int jogos_ganhos;
	struct lista_de_equipas *seguinte;
	struct lista_de_equipas *anterior;
	struct lista_de_equipas *ramo_esquerdo;
	struct lista_de_equipas *ramo_direito;
} Lista_de_equipas;

/*
Cada __jogo__ e caracterizada por:
* nome: uma string nao vazia, com um maximo de 1023 caracteres
* nome_equipa_1: uma string nao vazia, com um maximo de 1023 caracteres
* nome_equipa_2: uma string nao vazia, com um maximo de 1023 caracteres
* score_equipa_1: um inteiro que indica o score de uma equipa
* score_equipa_2: um inteiro que indica o score da outra equipa
* apontador: para o proximo jogo na lista
* apontador: para o anterior jogo na lista
*/
typedef struct lista_de_jogos
{
	char *nome;
	char *nome_equipa_1;
	char *nome_equipa_2;
	int score_equipa_1;
	int score_equipa_2;
	struct lista_de_jogos *seguinte;
	struct lista_de_jogos *anterior;
	struct lista_de_equipas *ramo_esquerdo;
	struct lista_de_equipas *ramo_direito;
} Lista_de_jogos;

/* 
Estrutura que vai manter as variaveis necessarias ao programa */
typedef struct variaveis_mais_ou_menos_globais
{
	Lista_de_equipas *cabeca_equipas;
	Lista_de_equipas *cauda_equipas;
	Lista_de_equipas *raiz_arvore_equipas;
	Lista_de_jogos *cauda_jogos;
	Lista_de_jogos *cabeca_jogos;
	Lista_de_jogos *raiz_arvore_jogos;
	int numero_de_equipas; 	/*Variavel auxiliar*/
	int numero_de_jogos;	/*Variavel auxiliar*/
	int numero_da_linha_do_comando; /*Variavel auxiliar*/
	int numero_maior_de_jogos_ganhos; /* Ao manter esta variavel, escuso de percorrer as listas mais uma vez a procura deste valor */
} Variaveis_mais_ou_menos_globais;


/* Funcao para reallocar memoria de uma string */
/* semelhante a strdup */
char *realoca_memoria_da_string(char *string_a_ser_realocada)
{
	/* vamos ver quantos bytes sao necessaria da string ate ao caracter que a termina */
	int bytes_a_alocar = strlen(string_a_ser_realocada) + 1;
	/* vamos alocar memoria na nova string */
	char *string_a_devolver = malloc(bytes_a_alocar);
	/* Vamos entao passar os bytes utilizaveis para a nova string*/
	strcpy(string_a_devolver, string_a_ser_realocada);
	/* e devolvemos a string com menos memoria */
	return string_a_devolver;
}

/* Funcao que vai ver se existe um jogo e devolve o ponteiro */
Lista_de_jogos *existe_jogo(Variaveis_mais_ou_menos_globais variaveis,char *nome_do_jogo_a_procurar)
{
	/* Variaveis auxiliares */
	Lista_de_jogos *jogo_a_procurar;
	
	if (variaveis.cabeca_jogos == NULL) /* Se nao houver cabeca da lista de jogos, e porque nao ha jogos inseridas */
	{
		return NULL;
	}
	else /* Caso ja haja uma cabeca, podemos procurar pelo jogo */
	{
		/* Comecamos por apontar para a cabeca */
		jogo_a_procurar = variaveis.cabeca_jogos;
		while(1)
		{
			if (strcmp(nome_do_jogo_a_procurar, jogo_a_procurar->nome) == 0) /* Se o nome a procurar for igual ao nome do jogo */
			{
				/* Encontramos o jogo, podemos retornar o ponteiro */
				return jogo_a_procurar;
				break;
			}
			else if (jogo_a_procurar->seguinte == NULL) /* Se o nome nao for igual, vemos se existe proximo jogo... */
			{
				/* Como nao existe jogo seguinte, e nao encontramos o nome, este jogo nao existe */
				return NULL;
				break;
			}
			else
			{
				/* Neste caso, "avancamos" na lista e repetimos o processo */
				jogo_a_procurar = jogo_a_procurar->seguinte;
			}
		}
	}
}


/* Funcao que vai ver se existe uma equipa e devolve o ponteiro */
Lista_de_equipas *existe_equipa(Variaveis_mais_ou_menos_globais variaveis,char *nome_da_equipa_a_procurar)
{
	/* Variaveis auxiliares */
	Lista_de_equipas *equipa_a_procurar;
	
	if (variaveis.cabeca_equipas == NULL) /* Se nao houver cabeca da lista de equipas, e porque nao ha equipas inseridas */
	{
		return NULL;
	}
	else /* Caso ja haja uma cabeca, podemos procurar pela equipa */
	{
		/* Comecamos por apontar para a cabeca */
		equipa_a_procurar = variaveis.cabeca_equipas;
		while(1)
		{
			if (strcmp(nome_da_equipa_a_procurar, equipa_a_procurar->nome) == 0) /* Se o nome a procurar for igual ao nome da equipa */
			{
				/* Encontramos a equipa, podemos retornar o ponteiro */
				return equipa_a_procurar;
				break;
			}
			else if (equipa_a_procurar->seguinte == NULL) /* Se o nome nao for igual, vemos se existe proxima equipa... */
			{
				/* Como nao existe equipa seguinte, e nao encontramos o nome, esta equipa nao existe */
				return NULL;
				break;
			}
			else
			{
				/* Neste caso, "avancamos" na lista e repetimos o processo */
				equipa_a_procurar = equipa_a_procurar->seguinte;
			}
		}
	}
}


/* Funcao para fazer free das listas de equipas */
Variaveis_mais_ou_menos_globais limpa_lista_de_equipas_da_memoria(Variaveis_mais_ou_menos_globais variaveis)
{
 /* Vamos comecar na cauda e limpar toda a memoria ate a cabeca */
	Lista_de_equipas *equipa_a_limpar;
	equipa_a_limpar = variaveis.cauda_equipas;
	while(1)
	{
		/* Se ja estivermos na cabeca, falta apenas limpar esta ultima equipa */
		if (equipa_a_limpar->anterior == NULL)
		{
			/*printf("(##DEBUG##) Estou a limpar a equipa final %s.\n", equipa_a_limpar->nome); */
			free(equipa_a_limpar->nome);
			free(equipa_a_limpar);
			break;
		}
		/* Se ainda nao estivermos na cabeca, "recuamos" um elemento na lista e limpamos o proximo */
		else
		{
			equipa_a_limpar = equipa_a_limpar->anterior;
			/*printf("(##DEBUG##) Estou a limpar a equipa %s.\n", equipa_a_limpar->seguinte->nome); */
			free(equipa_a_limpar->seguinte->nome);
			free(equipa_a_limpar->seguinte);
		}
	}
	return variaveis;
}

/* Funcao para fazer free das listas de jogos */
Variaveis_mais_ou_menos_globais limpa_lista_de_jogos_da_memoria(Variaveis_mais_ou_menos_globais variaveis)
{
 /* Vamos comecar na cauda e limpar toda a memoria ate a cabeca */
	Lista_de_jogos *jogo_a_limpar;
	
	jogo_a_limpar = variaveis.cauda_jogos;
	while(1)
	{
		/* Se ja estivermos na cabeca, falta apenas limpar esta ultima equipa */
		if (jogo_a_limpar->anterior == NULL)
		{
			/*printf("(##DEBUG##) Estou a limpar o jogo final %s. \n", jogo_a_limpar->nome); */
			free(jogo_a_limpar->nome);
			free(jogo_a_limpar->nome_equipa_1);
			free(jogo_a_limpar->nome_equipa_2);
			free(jogo_a_limpar);
			break;
		}
		/* Se ainda nao estivermos na cabeca, "recuamos" um elemento na lista e limpamos o proximo */
		else
		{
			jogo_a_limpar = jogo_a_limpar->anterior;
			/*printf("(##DEBUG##) Estou a limpar o jogo %s.\n", jogo_a_limpar->seguinte->nome); */
			free(jogo_a_limpar->seguinte->nome);
			free(jogo_a_limpar->seguinte->nome_equipa_1);
			free(jogo_a_limpar->seguinte->nome_equipa_2);
			free(jogo_a_limpar->seguinte);
		}
	}
	return variaveis;
}

/* Funcao que vai limpar a memoria */
Variaveis_mais_ou_menos_globais limpa_memoria_das_listas(Variaveis_mais_ou_menos_globais variaveis)
{
	/* Se nao houver cabecas, nao ha nada para fazer free */
	if (variaveis.cabeca_equipas != NULL) 
	{
		variaveis = limpa_lista_de_equipas_da_memoria(variaveis);
	}
	if (variaveis.cabeca_jogos != NULL)
	{
		variaveis = limpa_lista_de_jogos_da_memoria(variaveis);
	} 
	
	return variaveis;
}

/* Funcao que adiciona uma nova equipa.
Formato de entrada: A nome
Formato de saida: NADA (excepto erro).
Erros:
NL Equipa existente. no caso de ja existir uma equipa com esse nome no sistema.
*/
Variaveis_mais_ou_menos_globais adiciona_nova_equipa_por_listas(char *comando_do_utilizador, Variaveis_mais_ou_menos_globais variaveis)
{	
	/* Variaveis Locais */
	Lista_de_equipas *equipa_a_adicionar;
	Lista_de_equipas *equipa_a_procurar;
	
	/* Variaveis auxiliares */
	int i; /* ciclos for */
	int comprimento_do_comando = 0; /* tamanho da string do comando */
	int contador_componente = 0; /* tamanho da string do comando */

	char nome_aux[DIMENSAO_DO_NOME_DE_EQUIPA];
	
	/* Alocar memoria */
	equipa_a_adicionar = (Lista_de_equipas *)malloc(sizeof(Lista_de_equipas)); 
	/* inicializar os ponteiros para nao dar erros no valgrind */
	equipa_a_adicionar->seguinte = NULL;
	equipa_a_adicionar->anterior = NULL;
	equipa_a_adicionar->jogos_ganhos = 0;
	
	
	/* Ciclo que vai percorrer o comando a procura das componentes */
	/* Desde o 3 caracter ate ao penultimo, porque os dois ultimos caracteres sao '\n' e o caracter null */
	comprimento_do_comando = strlen(comando_do_utilizador);
	for (i = 2; i <= (comprimento_do_comando - 2); i++)
	{
		nome_aux[contador_componente] = comando_do_utilizador[i];
		contador_componente++;
	}
	nome_aux[contador_componente] = '\0'; /* terminamos a string */
	
	
	/* Aqui vamos realocar a memoria para apenas usar a que e necessaria */
	equipa_a_adicionar->nome = realoca_memoria_da_string(nome_aux);
		
	
	
	/* Preencher os valores da equipa */	
	if (variaveis.cabeca_equipas == NULL) /* Se nao houver cabeca da lista de equipas, esta e a primeira equipa a ser inserida */
	{
		variaveis.cabeca_equipas = equipa_a_adicionar;	/* Logo e a cabeca... */
		variaveis.cauda_equipas = equipa_a_adicionar;	/* e a cauda da lista */
		variaveis.numero_de_equipas++;
		return variaveis;
	}

	/* Vamos ver se a equipa existe, se existir o ponteiro apontara para ela */
	equipa_a_procurar = existe_equipa(variaveis,equipa_a_adicionar->nome);
	
	if (equipa_a_procurar == NULL) /* Se o ponteiro nao apontar para nada ... */
	{
		/* ... esta equipa nao existe com este nome, logo podemos adicionar */
		/* Para facilitar, iremos adicionar logo por ordem alfabetica. Vamos procurar na lista o espaco dela e inserir la */
		/* Comecamos na cabeca */
		equipa_a_procurar = variaveis.cabeca_equipas;
		/* Vamos ver se e para inserir antes da cabeca, por ordem alfabetica, ou e para continuar */
		if (strcmp(equipa_a_procurar->nome, equipa_a_adicionar->nome) >= 0)
		{
			/* Como a cabeca tem que ficar "depois" desta, inserimos esta na cabeca */
			equipa_a_adicionar->seguinte = equipa_a_procurar;
			equipa_a_adicionar->anterior = NULL;
			equipa_a_procurar->anterior = equipa_a_adicionar;
			variaveis.cabeca_equipas = equipa_a_adicionar;
			variaveis.numero_de_equipas++; 							/* e incrementamos a variavel para contar equipas */	
			return variaveis;	
		}		
		
		while(1)
		{
			/* Se chegamos a cauda e ja nao ha mais equipas, esta vai ser adicionada na cauda */
			if (equipa_a_procurar->seguinte == NULL)
			{
				equipa_a_adicionar->anterior = variaveis.cauda_equipas; /* A equipa antes desta e ainda a cauda actual */
				variaveis.cauda_equipas->seguinte = equipa_a_adicionar;	/* Apontamos da cauda actual para a nova cauda */
				variaveis.cauda_equipas = equipa_a_adicionar;			/* E depois colocamos a nova equipa como cauda */
				variaveis.numero_de_equipas++; 							/* e incrementamos a variavel para contar equipas */	
				return variaveis;
			}
			else /* como ainda ha equipas a frente ... */
			{
				/* Vamos ver se e para inserir antes da proxima equipa, por ordem alfabetica, ou e para continuar */
				if (strcmp(equipa_a_procurar->seguinte->nome, equipa_a_adicionar->nome) >= 0)
				{
					/* Como a proxima equipa tem que ficar "depois" desta, inserimos esta neste local */
					/* entre a equipa_a_procurar e a equipa_a_procurar->seguinte */
					equipa_a_adicionar->seguinte = equipa_a_procurar->seguinte;
					equipa_a_adicionar->anterior = equipa_a_procurar;
					equipa_a_procurar->seguinte->anterior = equipa_a_adicionar;
					equipa_a_procurar->seguinte = equipa_a_adicionar;
					variaveis.numero_de_equipas++; 							/* e incrementamos a variavel para contar equipas */	
					return variaveis;	
				}
			}
			/* Como ainda nao colocamos a equipa, vamos avancar na lista */
			equipa_a_procurar=equipa_a_procurar->seguinte;
		}
	}
	else
	{
		/* Encontramos a equipa, vamos retornar o erro e libertar esta memoria */
		free(equipa_a_adicionar->nome);
		free(equipa_a_adicionar);
		printf("%d Equipa existente.\n", variaveis.numero_da_linha_do_comando) ;
	}
	
	return variaveis;
	/* printf("##DEBUG## (NL %d)  Nome da Equipa -> %s \n", numero_da_linha_do_comando , equipa_a_adicionar->nome) ; */
	
}

/* Funcao que adiciona uma nova equipa.
Formato de entrada: A nome
Formato de saida: NADA (excepto erro).
Erros:
NL Equipa existente. no caso de ja existir uma equipa com esse nome no sistema.
*/
Variaveis_mais_ou_menos_globais adiciona_nova_equipa(char *comando_do_utilizador, Variaveis_mais_ou_menos_globais variaveis)
{	
	/* Variaveis Locais */
	Lista_de_equipas *equipa_a_adicionar;
	Lista_de_equipas *equipa_a_procurar;
	
	/* Variaveis auxiliares */
	int i; /* ciclos for */
	int comprimento_do_comando = 0; /* tamanho da string do comando */
	int contador_componente = 0; /* tamanho da string do comando */

	char nome_aux[DIMENSAO_DO_NOME_DE_EQUIPA];
	
	/* Alocar memoria */
	equipa_a_adicionar = (Lista_de_equipas *)malloc(sizeof(Lista_de_equipas)); 
	/* inicializar os ponteiros para nao dar erros no valgrind */
	equipa_a_adicionar->seguinte = NULL;
	equipa_a_adicionar->anterior = NULL;
	equipa_a_adicionar->jogos_ganhos = 0;
	
	
	/* Ciclo que vai percorrer o comando a procura das componentes */
	/* Desde o 3 caracter ate ao penultimo, porque os dois ultimos caracteres sao '\n' e o caracter null */
	comprimento_do_comando = strlen(comando_do_utilizador);
	for (i = 2; i <= (comprimento_do_comando - 2); i++)
	{
		nome_aux[contador_componente] = comando_do_utilizador[i];
		contador_componente++;
	}
	nome_aux[contador_componente] = '\0'; /* terminamos a string */
	
	
	/* Aqui vamos realocar a memoria para apenas usar a que e necessaria */
	equipa_a_adicionar->nome = realoca_memoria_da_string(nome_aux);
		
	
	
	/* Preencher os valores da equipa */	
	if (variaveis.cabeca_equipas == NULL) /* Se nao houver cabeca da lista de equipas, esta e a primeira equipa a ser inserida */
	{
		variaveis.cabeca_equipas = equipa_a_adicionar;	/* Logo e a cabeca... */
		variaveis.cauda_equipas = equipa_a_adicionar;	/* e a cauda da lista */
		variaveis.numero_de_equipas++;
		return variaveis;
	}

	/* Vamos ver se a equipa existe, se existir o ponteiro apontara para ela */
	equipa_a_procurar = existe_equipa(variaveis,equipa_a_adicionar->nome);
	
	if (equipa_a_procurar == NULL) /* Se o ponteiro nao apontar para nada ... */
	{
		/* ... esta equipa nao existe com este nome, logo podemos adicionar */
		/* Para facilitar, iremos adicionar logo por ordem alfabetica. Vamos procurar na lista o espaco dela e inserir la */
		/* Comecamos na cabeca */
		equipa_a_procurar = variaveis.cabeca_equipas;
		/* Vamos ver se e para inserir antes da cabeca, por ordem alfabetica, ou e para continuar */
		if (strcmp(equipa_a_procurar->nome, equipa_a_adicionar->nome) >= 0)
		{
			/* Como a cabeca tem que ficar "depois" desta, inserimos esta na cabeca */
			equipa_a_adicionar->seguinte = equipa_a_procurar;
			equipa_a_adicionar->anterior = NULL;
			equipa_a_procurar->anterior = equipa_a_adicionar;
			variaveis.cabeca_equipas = equipa_a_adicionar;
			variaveis.numero_de_equipas++; 							/* e incrementamos a variavel para contar equipas */	
			return variaveis;	
		}		
		
		while(1)
		{
			/* Se chegamos a cauda e ja nao ha mais equipas, esta vai ser adicionada na cauda */
			if (equipa_a_procurar->seguinte == NULL)
			{
				equipa_a_adicionar->anterior = variaveis.cauda_equipas; /* A equipa antes desta e ainda a cauda actual */
				variaveis.cauda_equipas->seguinte = equipa_a_adicionar;	/* Apontamos da cauda actual para a nova cauda */
				variaveis.cauda_equipas = equipa_a_adicionar;			/* E depois colocamos a nova equipa como cauda */
				variaveis.numero_de_equipas++; 							/* e incrementamos a variavel para contar equipas */	
				return variaveis;
			}
			else /* como ainda ha equipas a frente ... */
			{
				/* Vamos ver se e para inserir antes da proxima equipa, por ordem alfabetica, ou e para continuar */
				if (strcmp(equipa_a_procurar->seguinte->nome, equipa_a_adicionar->nome) >= 0)
				{
					/* Como a proxima equipa tem que ficar "depois" desta, inserimos esta neste local */
					/* entre a equipa_a_procurar e a equipa_a_procurar->seguinte */
					equipa_a_adicionar->seguinte = equipa_a_procurar->seguinte;
					equipa_a_adicionar->anterior = equipa_a_procurar;
					equipa_a_procurar->seguinte->anterior = equipa_a_adicionar;
					equipa_a_procurar->seguinte = equipa_a_adicionar;
					variaveis.numero_de_equipas++; 							/* e incrementamos a variavel para contar equipas */	
					return variaveis;	
				}
			}
			/* Como ainda nao colocamos a equipa, vamos avancar na lista */
			equipa_a_procurar=equipa_a_procurar->seguinte;
		}
	}
	else
	{
		/* Encontramos a equipa, vamos retornar o erro e libertar esta memoria */
		free(equipa_a_adicionar->nome);
		free(equipa_a_adicionar);
		printf("%d Equipa existente.\n", variaveis.numero_da_linha_do_comando) ;
	}
	
	return variaveis;
	/* printf("##DEBUG## (NL %d)  Nome da Equipa -> %s \n", numero_da_linha_do_comando , equipa_a_adicionar->nome) ; */
	
}



/* Funcao que adiciona um novo jogo.
	Formato de entrada: a nome:equipa1:equipa2:score1:score2
	Formato de saida: NADA (excepto erro).
	Erros:
	NL Jogo existente. no caso de ja existir um jogo com esse nome no sistema.
	NL Equipa inexistente. no caso de uma das equipas ou ambas nao existirem no sistema.
*/
Variaveis_mais_ou_menos_globais adiciona_novo_jogo(char *comando_do_utilizador, Variaveis_mais_ou_menos_globais variaveis)
{	
	/* Variaveis Locais */
	Lista_de_jogos *jogo_a_adicionar;
	Lista_de_jogos *jogo_a_procurar;
	
	/* Variaveis auxiliares */
	int i; /* ciclos for */
	int comprimento_do_comando = 0; /* tamanho da string do comando */
	/* Variaveis para controlar onde esta cada comando no vector passado como argumento */
	int paragens = 0; /* Vamos detectar quando muda a componente do comando, ao passarmos no caracater ':' */
	int contador_componente = 0; /*controle da copia do componente do vector original para o seu proprio vector */
	char aux_componente[DIMENSAO_DO_COMANDO]; /*vector auxiliar para receber componentes numericas antes de passar a inteiro*/

	char nome_aux[DIMENSAO_DO_NOME_DE_JOGO];
	char nome_equipa_1_aux[DIMENSAO_DO_NOME_DE_EQUIPA];
	char nome_equipa_2_aux[DIMENSAO_DO_NOME_DE_EQUIPA];
	/* As equipas que entram neste jogo */
	Lista_de_equipas *equipa1;
	Lista_de_equipas *equipa2;
	
	/* Alocar memoria */
	jogo_a_adicionar = (Lista_de_jogos *)malloc(sizeof(Lista_de_jogos)); 
	/* inicializar os ponteiros para nao dar erros no valgrind */
	jogo_a_adicionar->seguinte = NULL;
	jogo_a_adicionar->anterior = NULL;
	
	/* Vamos separar a string nas varias componentes */
	/* Cada vez que encontrarmos o caracter ':' na string, comecando no 3 caracter, e uma das 4 componentes do comando */
	comprimento_do_comando = strlen(comando_do_utilizador);
	
	/* Ciclo que vai percorrer o comando a procura das componentes */
	/* Desde o 3 caracter ate ao penultimo, porque os dois ultimos caracteres sao '\n' e o caracter null */
	for (i = 2; i <= (comprimento_do_comando - 1); i++)
	{
		/* Se for uma mudanca de componente ou o fim do comando... */
		if (comando_do_utilizador[i] == ':' || comando_do_utilizador[i] == '\n')
		{
			/* Para o atoi nao ir buscar a outros sitios da memoria, temos que terminar a string */
			aux_componente[contador_componente] = '\0';
			switch (paragens)
			{
				case 0: /*nome*/
					nome_aux[contador_componente] = '\0'; /* terminamos a string */
				break;
				case 1: /*equipa1*/
					nome_equipa_1_aux[contador_componente] = '\0'; /* terminamos a string */
				break;
				case 2: /*equipa2*/
					nome_equipa_2_aux[contador_componente] = '\0'; /* terminamos a string */
				break;
				case 3: /*score_equipa_1*/
					jogo_a_adicionar->score_equipa_1 = atoi(aux_componente);
				break;
				case 4: /*score_equipa_2*/
					jogo_a_adicionar->score_equipa_2 = atoi(aux_componente);
				break;
			}
			paragens++;
			contador_componente = 0;
			continue; /* como e um ':', avanca para o proximo caracter */
		}
		
		/* Se nao for uma mudanca de componente, continua a preencher o respectivo vector */
		switch (paragens)
		{
			case 0: /*nome*/
				nome_aux[contador_componente] = comando_do_utilizador[i];
				break;
			case 1: /*equipa1*/
				nome_equipa_1_aux[contador_componente] = comando_do_utilizador[i];
				break;
			case 2:/*equipa2*/
				nome_equipa_2_aux[contador_componente] = comando_do_utilizador[i];
				break;
			case 3:/*score_equipa_1*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
			case 4:/*score_equipa_2*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
		}
		contador_componente++;
	}
		
	
	/* Aqui vamos realocar a memoria para apenas usar a que e necessaria */	
	jogo_a_adicionar->nome = realoca_memoria_da_string(nome_aux);
	jogo_a_adicionar->nome_equipa_1 = realoca_memoria_da_string(nome_equipa_1_aux);
	jogo_a_adicionar->nome_equipa_2 = realoca_memoria_da_string(nome_equipa_2_aux);
	
	/* Vamos ver se o jogo existe, se existir o ponteiro apontara para ele */
	jogo_a_procurar = existe_jogo(variaveis,jogo_a_adicionar->nome);

	if (jogo_a_procurar == NULL) /* se o ponteiro nao apontar para nada ... */
	{
		/* Antes de adicionarmos o jogo, teremos de ir ver se as equipas existem criadas */
		/* E guardamos logo os ponteiro para ser mais facil actualizar a que ganhou o jogo */
		equipa1 = existe_equipa(variaveis,jogo_a_adicionar->nome_equipa_1);
		
		/* se a primeira equipa nao existir, escusamos de ir procurar a segunda */
		if (equipa1 != NULL )
		{
			equipa2 = existe_equipa(variaveis,jogo_a_adicionar->nome_equipa_2);
		}
		/* Se alguma das equipas nao existir, o jogo nao pode ser criado */
		if (equipa1 == NULL || equipa2 == NULL)
		{			
			free(jogo_a_adicionar->nome);
			free(jogo_a_adicionar->nome_equipa_1);
			free(jogo_a_adicionar->nome_equipa_2);
			free(jogo_a_adicionar);
			printf("%d Equipa inexistente.\n", variaveis.numero_da_linha_do_comando) ;	
			return variaveis;
		}
		/* O jogo nao existe... se nao existir cabeca, este jogo sera a cabeca e a cauda */
		if (variaveis.cabeca_jogos == NULL)
		{
			variaveis.cabeca_jogos = jogo_a_adicionar;		/* passa a ser a cabeca */
			variaveis.cauda_jogos = jogo_a_adicionar;		/* e a cauda */
			variaveis.numero_de_jogos++; 					/* e incrementamos a variavel para contar jogos */	
		}
		else
		{
		/* O jogo nao existe, e ha cabeca logo vai ser acrescentado no final da cauda */
		jogo_a_adicionar->anterior = variaveis.cauda_jogos; /* O jogo antes deste e ainda a cauda actual */
		variaveis.cauda_jogos->seguinte = jogo_a_adicionar;	/* Apontamos da cauda actual para a nova cauda */
		variaveis.cauda_jogos = jogo_a_adicionar;			/* E depois colocamos o novo jogo como cauda */
		variaveis.numero_de_jogos++; 						/* e incrementamos a variavel para contar jogos */		
		}
	}
	else
	{
		/* Encontramos o jogo, vamos retornar o erro e libertar a memoria usada */
		free(jogo_a_adicionar->nome);
		free(jogo_a_adicionar->nome_equipa_1);
		free(jogo_a_adicionar->nome_equipa_2);
		free(jogo_a_adicionar);
		printf("%d Jogo existente.\n", variaveis.numero_da_linha_do_comando) ;		
		return variaveis;
	}
	
	/* Vamos agora adicionar uma vitoria a equipa que venceu */
	if (jogo_a_adicionar->score_equipa_1 > jogo_a_adicionar->score_equipa_2)
	{
		equipa1->jogos_ganhos++;
		/* Se esta equipa tem mais jogos ganhos que a variavel de controle, actualiza-a */
		if (equipa1->jogos_ganhos > variaveis.numero_maior_de_jogos_ganhos)
		{
			variaveis.numero_maior_de_jogos_ganhos++;
		}
	}
	else if(jogo_a_adicionar->score_equipa_1 < jogo_a_adicionar->score_equipa_2)
	{
		equipa2->jogos_ganhos++;	
		/* Se esta equipa tem mais jogos ganhos que a variavel de controle, actualiza-a */
		if (equipa2->jogos_ganhos > variaveis.numero_maior_de_jogos_ganhos)
		{
			variaveis.numero_maior_de_jogos_ganhos++;
		}
	}
	
	return variaveis;
	
}

/* Funcao que procura uma equipa dado um nome.
Formato de entrada: P nome
Formato de saida: NL nome numero-de-jogos-ganhos.
Erros:
NL Equipa inexistente. no caso de nao existir nenhuma equipa com esse nome no sistema.
*/
Variaveis_mais_ou_menos_globais procura_equipa(char *comando_do_utilizador,Variaveis_mais_ou_menos_globais variaveis)
{	
	/* Variaveis Locais */
	Lista_de_equipas *equipa_a_procurar;
	char nome_da_equipa_a_procurar[DIMENSAO_DO_NOME_DE_EQUIPA];
	
	/* Variaveis auxiliares */
	int i; /* ciclos for */
	int comprimento_do_comando = 0; /* tamanho da string do comando */
	int contador_componente = 0; /* tamanho da string do comando */
	
	/* Ciclo que vai percorrer o comando a procura das componentes */
	/* Desde o 3 caracter ate ao penultimo, porque os dois ultimos caracteres sao '\n' e o caracter null */
	comprimento_do_comando = strlen(comando_do_utilizador);
	for (i = 2; i <= (comprimento_do_comando - 2); i++)
	{
		nome_da_equipa_a_procurar[contador_componente] = comando_do_utilizador[i];
		contador_componente++;
	}
	nome_da_equipa_a_procurar[contador_componente] = '\0'; /* terminamos a string */	
	
	if (variaveis.cabeca_equipas == NULL) /* Se nao houver cabeca da lista de equipas, e porque nao ha equipas inseridas */
	{
		printf("%d Equipa inexistente.\n", variaveis.numero_da_linha_do_comando) ;
		return variaveis;
	}
	
	/* Vamos procurar entao a equipa */
	equipa_a_procurar = existe_equipa(variaveis, nome_da_equipa_a_procurar);

	if (equipa_a_procurar == NULL)
	{
		/* Nao encontramos o nome, esta equipa nao existe */
		printf("%d Equipa inexistente.\n", variaveis.numero_da_linha_do_comando) ;			
	}
	else
	{
		/* Encontramos a equipa, podemos retornar os valores */
		printf("%d %s %d\n", variaveis.numero_da_linha_do_comando, nome_da_equipa_a_procurar, equipa_a_procurar->jogos_ganhos);		
	}

	return variaveis;
}

/* Funcao que procura um jogo com o nome dado.
Formato de entrada: p nome
Formato de saida: Igual ao formato de saida do comando l mas apenas com o jogo nome.
Erros:
NL Jogo inexistente. no caso de nao existir nenhum jogo com esse nome no sistema.
*/
Variaveis_mais_ou_menos_globais procura_jogo(char *comando_do_utilizador,Variaveis_mais_ou_menos_globais variaveis)
{	
	/* Variaveis Locais */
	Lista_de_jogos *jogo_a_procurar;
	char nome_do_jogo_a_procurar[DIMENSAO_DO_NOME_DE_JOGO];
	
	/* Variaveis auxiliares */
	int i; /* ciclos for */
	int comprimento_do_comando = 0; /* tamanho da string do comando */
	int contador_componente = 0; /* tamanho da string do comando */
	
	/* Ciclo que vai percorrer o comando a procura das componentes */
	/* Desde o 3 caracter ate ao penultimo, porque os dois ultimos caracteres sao '\n' e o caracter null */
	comprimento_do_comando = strlen(comando_do_utilizador);
	for (i = 2; i <= (comprimento_do_comando - 2); i++)
	{
		nome_do_jogo_a_procurar[contador_componente] = comando_do_utilizador[i];
		contador_componente++;
	}
	nome_do_jogo_a_procurar[contador_componente] = '\0'; /* terminamos a string */	
	
	if (variaveis.cabeca_jogos == NULL) /* Se nao houver cabeca da lista de jogos, e porque nao ha jogos inseridos */
	{
		printf("%d Jogo inexistente.\n", variaveis.numero_da_linha_do_comando) ;
		return variaveis;
	}
	
	jogo_a_procurar = existe_jogo(variaveis, nome_do_jogo_a_procurar);
	
	if (jogo_a_procurar == NULL)
	{
		/* Como nao existe jogo seguinte, e nao encontramos o nome, este jogo nao existe */
		printf("%d Jogo inexistente.\n", variaveis.numero_da_linha_do_comando) ;	
	}
	else
	{
		/* Encontramos o jogo, podemos retornar os valores */
		printf("%d %s %s %s %d %d\n", variaveis.numero_da_linha_do_comando
					, jogo_a_procurar->nome
					, jogo_a_procurar->nome_equipa_1
					, jogo_a_procurar->nome_equipa_2
					, jogo_a_procurar->score_equipa_1
					, jogo_a_procurar->score_equipa_2);		
	}

	
	return variaveis;
}

/* Funcao que Apaga um jogo dado um nome.
Formato de entrada: r nome
Formato de saida: NADA (excepto erro).
Erros:
NL Jogo inexistente. no caso de nao existir nenhum jogo com esse nome no sistema.
*/
Variaveis_mais_ou_menos_globais apaga_jogo(char *comando_do_utilizador,Variaveis_mais_ou_menos_globais variaveis)
{	
	/* Variaveis Locais */
	Lista_de_jogos *jogo_a_procurar;
	char nome_do_jogo_a_procurar[DIMENSAO_DO_NOME_DE_JOGO];
	
	/* Variaveis auxiliares */
	int i; /* ciclos for */
	int comprimento_do_comando = 0; /* tamanho da string do comando */
	int contador_componente = 0; /* tamanho da string do comando */
	Lista_de_equipas *equipa_a_retirar_vitoria;
	
	/* Ciclo que vai percorrer o comando a procura das componentes */
	/* Desde o 3 caracter ate ao penultimo, porque os dois ultimos caracteres sao '\n' e o caracter null */
	comprimento_do_comando = strlen(comando_do_utilizador);
	for (i = 2; i <= (comprimento_do_comando - 2); i++)
	{
		nome_do_jogo_a_procurar[contador_componente] = comando_do_utilizador[i];
		contador_componente++;
	}
	nome_do_jogo_a_procurar[contador_componente] = '\0'; /* terminamos a string */	
	
	if (variaveis.cabeca_jogos == NULL) /* Se nao houver cabeca da lista de jogos, e porque nao ha jogos inseridos */
	{
		printf("%d Jogo inexistente.\n", variaveis.numero_da_linha_do_comando) ;
	}
	else /* Caso ja haja uma cabeca, podemos procurar pelo jogo */
	{
		/* Comecamos por apontar para a cabeca */
		jogo_a_procurar = variaveis.cabeca_jogos;
		while(1)
		{
			/* printf("(##DEBUG##) Estou a procurar no jogo.%s\n", jogo_a_procurar->nome); */
			if (strcmp(nome_do_jogo_a_procurar, jogo_a_procurar->nome) == 0) /* Se o nome a procurar for igual ao nome do jogo */
			{
				/* Encontramos o jogo, podemos apaga-lo da lista */
				
				/* Antes de apagarmos o jogo da lista, temos que ver qual foi a equipa vencedora e retirar-lhe uma vitoria */
				if (jogo_a_procurar->score_equipa_1 > jogo_a_procurar->score_equipa_2)
				{
					/* A equipa 1 venceu */
					equipa_a_retirar_vitoria = existe_equipa(variaveis, jogo_a_procurar->nome_equipa_1);
					equipa_a_retirar_vitoria->jogos_ganhos--;
				}
				else if (jogo_a_procurar->score_equipa_1 < jogo_a_procurar->score_equipa_2)
				{
					equipa_a_retirar_vitoria = existe_equipa(variaveis, jogo_a_procurar->nome_equipa_2);
					equipa_a_retirar_vitoria->jogos_ganhos--;
				}
				
				
				
				/* Se este jogo tiver um jogo anterior, ou seja, nao e a cabeca...*/
				/* Entao o jogo anterior passa a apontar para o jogo a seguir a este, mesmo que seja null */
				if (jogo_a_procurar->anterior != NULL) 
				{
					jogo_a_procurar->anterior->seguinte = jogo_a_procurar->seguinte;
				}
				/* Se este jogo tiver um jogo seguinte, ou seja, nao e a cauda...*/
				/* Entao o jogo seguinte passa a apontar para o jogo anterior a este, mesmo que seja null */
				if (jogo_a_procurar->seguinte != NULL) 
				{
					jogo_a_procurar->seguinte->anterior = jogo_a_procurar->anterior;
				}				
				
				/* Se este jogo for a cabeca dos jogos ... */
				if (jogo_a_procurar == variaveis.cabeca_jogos) 
				{
					/*e nao tiver mais ninguem agarrado temos que o eliminar na mesma */
					if(jogo_a_procurar->seguinte == NULL)
					{
						variaveis.cabeca_jogos = NULL;
					}
					/* mas se tiver alguem agarrado, passa a ser a nova cabeca*/
					else
					{
						variaveis.cabeca_jogos=jogo_a_procurar->seguinte;
					}
					
				}
				
				/* Se este jogo for a cauda dos jogos ... */
				if (jogo_a_procurar == variaveis.cauda_jogos) 
				{
					/*e nao tiver mais ninguem agarrado temos que o eliminar na mesma */
					if(jogo_a_procurar->anterior == NULL)
					{
						variaveis.cauda_jogos = NULL;
					}
					/* mas se tiver alguem agarrado, passa a ser a nova cauda*/
					else
					{
						variaveis.cauda_jogos=jogo_a_procurar->anterior;
					}
					
				}
				
				free(jogo_a_procurar->nome);
				free(jogo_a_procurar->nome_equipa_1);
				free(jogo_a_procurar->nome_equipa_2);
				free(jogo_a_procurar);
				variaveis.numero_de_jogos--;
				
				break;
			}
			else if (jogo_a_procurar->seguinte == NULL) /* Se o nome nao for igual, vemos se existe proximo jogo... */
			{
				/* Como nao existe jogo seguinte, e nao encontramos o nome, este jogo nao existe */
				printf("%d Jogo inexistente.\n", variaveis.numero_da_linha_do_comando) ;	
				break;
			}
			else
			{
				/* Neste caso, "avancamos" na lista e repetimos o processo */
				jogo_a_procurar = jogo_a_procurar->seguinte;
			}
		}
	}
	return variaveis;
}
	
/* Funcao que lista todos os jogos introduzidos.
	Formato de entrada: l
	Formato de saida: Uma linha por jogo no formato abaixo
	NL nome-jogo nome-equipa1 nome-equipa2 score1 score2
	Os jogos deverao ser listados pela ordem em que foram introduzidos. Caso nao exista nenhum jogo no sistema, o comando nao imprime nada.
	Erros: Nao aplicavel.
*/
void lista_todos_jogos(Variaveis_mais_ou_menos_globais variaveis)
{	
	/* Variaveis Locais */
	Lista_de_jogos *jogo_a_procurar;


	if (variaveis.cabeca_jogos == NULL) /* Se nao houver cabeca da lista de jogos, e porque nao ha jogos inseridos */
	{
		/* Logo nao imprime nada */
		return;
		printf("(##DEBUG##) %d Nao ha jogos!.\n", variaveis.numero_da_linha_do_comando) ;
	}
	else /* Caso ja haja uma cabeca, podemos procurar pelos jogos */
	{
		/* Comecamos por apontar para a cabeca */
		jogo_a_procurar = variaveis.cabeca_jogos;
		while(1)
		{
			/* printf("(##DEBUG##) Estou a procurar no jogo.%s\n", jogo_a_procurar->nome); */
			
				/* Encontramos o jogo, podemos retornar os valores */
				printf("%d %s %s %s %d %d\n", variaveis.numero_da_linha_do_comando
							, jogo_a_procurar->nome
							, jogo_a_procurar->nome_equipa_1
							, jogo_a_procurar->nome_equipa_2
							, jogo_a_procurar->score_equipa_1
							, jogo_a_procurar->score_equipa_2);
			
		
			if (jogo_a_procurar->seguinte == NULL) /* Vemos se existe proximo jogo... */
			{
				/* Como nao existe jogo seguinte, este jogo foi o ultimo */
				break;
			}
			else
			{
				/* Neste caso, "avancamos" na lista e repetimos o processo */
				jogo_a_procurar = jogo_a_procurar->seguinte;
			}
		}
	}
	return;
}
		
/* Funcao que encontra as equipas que ganharam mais jogos e lista por ordem lexicografica (do nome da equipa).
    Formato de entrada: g
    Formato de saida:
    NL Melhores numero-de-jogos-ganhos
    NL * nome-equipa1
    NL * nome-equipa2
    NL * nome-equipa3
    ...
    Caso nao exista nenhuma equipa, o comando nao imprime nada (nem a palavra Melhores).
*/
void equipas_que_ganharam_mais_jogos(Variaveis_mais_ou_menos_globais variaveis)
{	
	/* Variaveis Locais */
	Lista_de_equipas *equipa_a_procurar;

	if (variaveis.cabeca_equipas == NULL) /* Se nao houver cabeca da lista de equipas, e porque nao ha equipas inseridas */
	{
		/* Logo nao imprime nada */
		return;
	}
	else /* Caso ja haja uma cabeca, podemos procurar pelas equipas */
	{
		/* Comecamos por apontar para a cabeca */
		equipa_a_procurar = variaveis.cabeca_equipas;
		printf("%d Melhores %d\n", variaveis.numero_da_linha_do_comando, variaveis.numero_maior_de_jogos_ganhos);
		while(1)
		{
		
			/* Encontramos uma equipa, se ela tiver tantos jogos ganhos como a variavel de controlo, podemos retornar os valores */
			if (equipa_a_procurar->jogos_ganhos == variaveis.numero_maior_de_jogos_ganhos)
			{
				printf("%d * %s\n", variaveis.numero_da_linha_do_comando, equipa_a_procurar->nome);
			}
		
			if (equipa_a_procurar->seguinte == NULL) /* Vemos se existe proxima equipa... */
			{
				/* Como nao existe equipa seguinte, esta foi a ultima */
				break;
			}
			else
			{
				/* Neste caso, "avancamos" na lista e repetimos o processo */
				equipa_a_procurar = equipa_a_procurar->seguinte;
			}
		}
	}
	return;
}
	
/* Funcao que Altera o score de um jogo dado o nome.
Formato de entrada: s nome:score1:score2
Formato de saida: NADA (excepto erro).
Erros:
NL Jogo inexistente. no caso de nao existir nenhum jogo com esse nome no sistema.
*/
Variaveis_mais_ou_menos_globais altera_score(char *comando_do_utilizador, Variaveis_mais_ou_menos_globais variaveis)
{	
	/* Variaveis Locais */
	Lista_de_jogos *jogo_a_procurar;
	char nome_do_jogo_a_procurar[DIMENSAO_DO_NOME_DE_JOGO];
	
	/* Variaveis auxiliares */
	int i; /* ciclos for */
	int comprimento_do_comando = 0; /* tamanho da string do comando */

	/* Variaveis para controlar onde esta cada comando no vector passado como argumento */
	int paragens = 0; /* Vamos detectar quando muda a componente do comando, ao passarmos no caracater ':' */
	int contador_componente = 0; /*controle da copia do componente do vector original para o seu proprio vector */
	char aux_componente[DIMENSAO_DO_COMANDO]; /*vector auxiliar para receber componentes numericas antes de passar a inteiro*/
	int score_1_novo;
	int score_2_novo;
	
	/* As equipas que entram neste jogo */
	Lista_de_equipas *equipa1;
	Lista_de_equipas *equipa2;
	
	/* Vamos separar a string nas varias componentes */
	/* Cada vez que encontrarmos o caracter ':' na string, comecando no 3 caracter, e uma das 4 componentes do comando */
	comprimento_do_comando = strlen(comando_do_utilizador);
	
	/* Ciclo que vai percorrer o comando a procura das componentes */
	/* Desde o 3 caracter ate ao penultimo, porque os dois ultimos caracteres sao '\n' e o caracter null */
	for (i = 2; i <= (comprimento_do_comando - 1); i++)
	{
		/* Se for uma mudanca de componente ou o fim do comando... */
		if (comando_do_utilizador[i] == ':' || comando_do_utilizador[i] == '\n')
		{
			/* Para o atoi nao ir buscar a outros sitios da memoria, temos que terminar a string */
			aux_componente[contador_componente] = '\0';
			switch (paragens)
			{
				case 0: /*nome*/
					nome_do_jogo_a_procurar[contador_componente] = '\0'; /* terminamos a string */
				break;
				case 1: /*score_equipa_1*/
					score_1_novo = atoi(aux_componente);
				break;
				case 2: /*score_equipa_2*/
					score_2_novo = atoi(aux_componente);
				break;
			}
			paragens++;
			contador_componente = 0;
			continue; /* como e um ':', avanca para o proximo caracter */
		}
		
		/* Se nao for uma mudanca de componente, continua a preencher o respectivo vector */
		switch (paragens)
		{
			case 0: /*nome*/
				nome_do_jogo_a_procurar[contador_componente] = comando_do_utilizador[i];
				break;
			case 1:/*score_equipa_1*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
			case 2:/*score_equipa_2*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
		}
		contador_componente++;
	}
	
	/* Vamos ver se o jogo existe, se existir o ponteiro apontara para ele */
	jogo_a_procurar = existe_jogo(variaveis,nome_do_jogo_a_procurar);
	

	
	if (jogo_a_procurar == NULL) /* se o ponteiro nao apontar para nada ... */
	{
		/* O jogo nao existe */
		/* retornamos o erro */
		printf("%d Jogo inexistente.\n", variaveis.numero_da_linha_do_comando) ;	
	}
	else
	{
			equipa1 = existe_equipa(variaveis, jogo_a_procurar->nome_equipa_1);
			equipa2 = existe_equipa(variaveis, jogo_a_procurar->nome_equipa_2);
		/* Encontramos o jogo, vamos procurar as equipas e alterar o score do jogo */
		/* Primeiro vamos ver quem era a equipa vencedora e retirar-lhe uma vitoria */
				if (jogo_a_procurar->score_equipa_1 > jogo_a_procurar->score_equipa_2)
				{
					equipa1->jogos_ganhos--;
				}
				else if(jogo_a_procurar->score_equipa_1 < jogo_a_procurar->score_equipa_2)
				{
					equipa2->jogos_ganhos--;	
				}		
		/* Agora alteramos o score */
		jogo_a_procurar->score_equipa_1 = score_1_novo;
		jogo_a_procurar->score_equipa_2 = score_2_novo;
		/* Agora vamos ver quem era a equipa vencedora e dar-lhe uma vitoria */
				if (jogo_a_procurar->score_equipa_1 > jogo_a_procurar->score_equipa_2)
				{
					equipa1->jogos_ganhos++;
					/* Se esta equipa tem mais jogos ganhos que a variavel de controle, actualiza-a */
					if (equipa1->jogos_ganhos > variaveis.numero_maior_de_jogos_ganhos)
					{
						variaveis.numero_maior_de_jogos_ganhos++;
					}
				}
				else if(jogo_a_procurar->score_equipa_1 < jogo_a_procurar->score_equipa_2)
				{
					equipa2->jogos_ganhos++;
					/* Se esta equipa tem mais jogos ganhos que a variavel de controle, actualiza-a */
					if (equipa2->jogos_ganhos > variaveis.numero_maior_de_jogos_ganhos)
					{
						variaveis.numero_maior_de_jogos_ganhos++;
					}					
				}			
		
		return variaveis;
	}
	
	return variaveis;
	
}
	
	
	
int main()
{
	char comando_do_utilizador[DIMENSAO_DO_COMANDO];
	
	/* Inicializadores */
	Variaveis_mais_ou_menos_globais variaveis;
	

	variaveis.numero_da_linha_do_comando = 0;
	variaveis.cabeca_equipas = NULL;
	variaveis.cabeca_jogos = NULL;
	variaveis.cauda_equipas = NULL;
	variaveis.cauda_jogos = NULL;
	variaveis.numero_de_equipas = 0;
	variaveis.numero_de_jogos = 0;
	variaveis.numero_maior_de_jogos_ganhos = 0;
		
	/* Ciclo que vai aguardar pelos comandos do utilizador. E interrompido se o comando for "x" */
	while  (1)
	{	
		variaveis.numero_da_linha_do_comando++;
		/* Espera pelo comando do utilizador */
		fgets(comando_do_utilizador, DIMENSAO_DO_COMANDO, stdin);

		switch (comando_do_utilizador[0])
		{
			/* | __x__ | termina o programa | */
			/* Mas antes disso, limpa a memoria das listas */
			case 'x':
				limpa_memoria_das_listas(variaveis);
				return 0;
				break;
				
			/* __A__ - Adiciona uma nova equipa. 
				Formato de entrada: A nome
				Formato de saida: NADA (excepto erro).
				Erros:
				NL Equipa existente. no caso de ja existir uma equipa com esse nome no sistema.
			*/
			case 'A':
				variaveis = adiciona_nova_equipa(comando_do_utilizador, variaveis);
				break;
				
			/* __P__ - Procura uma equipa dado um nome.
				Formato de entrada: P nome
				Formato de saida: NL nome numero-de-jogos-ganhos.
				Erros:
				NL Equipa inexistente. no caso de nao existir nenhuma equipa com esse nome no sistema.
			*/
			case 'P':
				variaveis = procura_equipa(comando_do_utilizador, variaveis);
				break;

			/* __a__ - Adiciona um novo jogo. 
				Formato de entrada: a nome:equipa1:equipa2:score1:score2
				Formato de saida: NADA (excepto erro).
				Erros:
				NL Jogo existente. no caso de ja existir um jogo com esse nome no sistema.
				NL Equipa inexistente. no caso de uma das equipas ou ambas nao existirem no sistema.
			*/
			case 'a':
				variaveis = adiciona_novo_jogo(comando_do_utilizador, variaveis);
				break;								
				
			/* __p__ - Procura um jogo com o nome dado. 
				Formato de entrada: p nome
				Formato de saida: Igual ao formato de saida do comando l mas apenas com o jogo nome.
				Erros:
				NL Jogo inexistente. no caso de nao existir nenhum jogo com esse nome no sistema.
			*/
			case 'p':
				variaveis = procura_jogo(comando_do_utilizador, variaveis);
				break;
								
			/* __l__ - Lista todos os jogos introduzidos.
				Formato de entrada: l
				Formato de saida: Uma linha por jogo no formato abaixo
				NL nome-jogo nome-equipa1 nome-equipa2 score1 score2
				Os jogos deverao ser listados pela ordem em que foram introduzidos. Caso nao exista nenhum jogo no sistema, o comando nao imprime nada.
				Erros: Nao aplicavel.
			*/
			case 'l':
				lista_todos_jogos(variaveis);
				break;
				
			/* __r__ - Apaga um jogo dado um nome.
				Formato de entrada: r nome
				Formato de saida: NADA (excepto erro).
				Erros:
				NL Jogo inexistente. no caso de nao existir nenhum jogo com esse nome no sistema.
			*/
			case 'r':
				variaveis = apaga_jogo(comando_do_utilizador, variaveis);
				break;
							
			/* __s__ - Altera o score de um jogo dado o nome.
				Formato de entrada: s nome:score1:score2
				Formato de saida: NADA (excepto erro).
				Erros:
				NL Jogo inexistente. no caso de nao existir nenhum jogo com esse nome no sistema.
			*/
			case 's':
				variaveis = altera_score(comando_do_utilizador, variaveis);
				break;
				
			/* __g__ - Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica (do nome da equipa).
				Formato de entrada: g
				Formato de saida:
				NL Melhores numero-de-jogos-ganhos
				NL * nome-equipa1
				NL * nome-equipa2
				NL * nome-equipa3
				...
				Caso nao exista nenhuma equipa, o comando nao imprime nada (nem a palavra Melhores).
			*/
			case 'g':
				equipas_que_ganharam_mais_jogos(variaveis);
				break;
				
				
				
		}
	}
	
	return 0;
}