#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIMENSAO_DO_COMANDO 250 /* Comando feito por input do utilizador */
#define DIMENSAO_DESCRICAO_PRODUTO 64
#define NUMERO_MAXIMO_DE_PRODUTOS_DIFERENTES 10000
#define NUMERO_MAXIMO_DE_ENCOMENDAS_DIFERENTES 500
#define NUMERO_MAXIMO_DE_PESO_NUMA_ENCOMENDA 200



/*
Cada __produto__ ? caracterizado por:

* um identificador (um n?mero inteiro no intervalo [0, 9 999])
* uma descri??o (uma string n?o vazia com um m?ximo de 63 caracteres)
* o seu pre?o (um n?mero inteiro maior que 0)
* o seu peso (um n?mero inteiro maior que 0)
* a sua quantidade em stock ou na encomenda (um n?mero inteiro maior ou igual a 0)
*/
struct produto
{
	int identificador;
	char descricao[DIMENSAO_DESCRICAO_PRODUTO];
	int preco;
	int peso;
	int quantidade;
};

/*
Uma __encomenda__ ? um conjunto de produtos.
*/
struct encomenda
{
	/* Como cada produto pesa no m?nimo 1, a encomenda pode ter no m?ximo 200 produtos diferentes, todos a pesar 1 */
		struct produto produtos_na_encomenda[NUMERO_MAXIMO_DE_PESO_NUMA_ENCOMENDA];
	/* Peso total da encomenda */
		int peso;
	/* Numero de produtos nesta encomenda */
		int numero_de_produtos_criados_em_encomenda;
};

/* Vari?veis globais */
	/* Vari?vel que controla que produtos existem no stock */
		struct produto stock_de_produtos[NUMERO_MAXIMO_DE_PRODUTOS_DIFERENTES];
	/* Vector para auxiliar ? ordena??o, sem alterar o vector inicial */
		struct produto vector_de_ordenacao[NUMERO_MAXIMO_DE_PRODUTOS_DIFERENTES];
	/* Vector para auxiliar ? ordena??o, sem alterar o vector inicial */
		struct produto vector_auxiliar_de_ordenacao[NUMERO_MAXIMO_DE_PRODUTOS_DIFERENTES];
	/* Vari?vel que controla as encomendas existentes */
		struct encomenda lista_de_encomendas[NUMERO_MAXIMO_DE_ENCOMENDAS_DIFERENTES];
	/* Vari?vel que controla o comando inserido pelo utilizador */
		char comando_do_utilizador[DIMENSAO_DO_COMANDO];
	/* Vari?vel que controla quantos produtos est?o criados no sistema */
		int numero_de_produtos_criados = 0;
	/* Vari?vel que controla quantas encomendas est?o criadas no sistema */
		int numero_de_encomendas_criadas = 0;

		
void merge_por_preco(int esquerda,int meio,int direita)		
{
	int iterador_i, iterador_j; /* Iteradores dos vectores auxiliares */
	int iterador_k; /* iterador do vector de ordenacao para o ciclo */
	/* Vamos contruir o vector auxiliar */
	for (iterador_i = meio + 1; iterador_i > esquerda; iterador_i--)
	{
		vector_auxiliar_de_ordenacao[iterador_i - 1] = vector_de_ordenacao[iterador_i - 1];
	}
	for (iterador_j = meio; iterador_j < direita; iterador_j++)
	{
		vector_auxiliar_de_ordenacao[direita + meio - iterador_j] = vector_de_ordenacao[iterador_j + 1];
	}
	/* Ap?s termos o vector auxiliar contruido, vamos escolhendo os elementos das pontas de forma a order o vector de ordena??o */
	for (iterador_k = esquerda; iterador_k <= direita; iterador_k++)
	{
		/* Vamos comparar ent?o os dois elementos em vector_auxiliar_de_ordenacao[iterador_i] e vector_auxiliar_de_ordenacao[iterador_j], */
		/* para ver qual fica "? esquerda", neste caso ? ordenar por preco */
		/* ou, caso o preco seja igual, pelo id */
		if (vector_auxiliar_de_ordenacao[iterador_i].preco > vector_auxiliar_de_ordenacao[iterador_j].preco ||
			(vector_auxiliar_de_ordenacao[iterador_i].preco == vector_auxiliar_de_ordenacao[iterador_j].preco &&
			vector_auxiliar_de_ordenacao[iterador_i].identificador > vector_auxiliar_de_ordenacao[iterador_j].identificador)
			)
			   {
					vector_de_ordenacao[iterador_k] = vector_auxiliar_de_ordenacao[iterador_j --];
			   }
			   else
			   {   
					vector_de_ordenacao[iterador_k] = vector_auxiliar_de_ordenacao[iterador_i ++];
			   }
	}
}
			
/* Funcao que ordena um vector por ordem do preco do produto */
void mergesort_por_preco(int esquerda,int direita)
{
	/* Vamos definir onde "partir" o vector */
	int meio = (esquerda + direita) / 2;
	/* Enquanto a esquerda for menor que a direita... */
	if (esquerda < direita)
	{
		mergesort_por_preco(esquerda,meio); /* Partimos de novo a primeira metade */
		mergesort_por_preco(meio + 1,direita); /* Partimos de novo a segunda metade */
		merge_por_preco(esquerda,meio,direita);
	}
}
			
void merge_por_ordem_alfabetica(int esquerda,int meio,int direita)		
{
	int iterador_i, iterador_j; /* Iteradores dos vectores auxiliares */
	int iterador_k; /* iterador do vector de ordenacao para o ciclo */
	/* Vamos contruir o vector auxiliar */
	for (iterador_i = meio + 1; iterador_i > esquerda; iterador_i--)
	{
		vector_auxiliar_de_ordenacao[iterador_i - 1] = vector_de_ordenacao[iterador_i - 1];
	}
	for (iterador_j = meio; iterador_j < direita; iterador_j++)
	{
		vector_auxiliar_de_ordenacao[direita + meio - iterador_j] = vector_de_ordenacao[iterador_j + 1];
	}
	/* Ap?s termos o vector auxiliar contruido, vamos escolhendo os elementos das pontas de forma a order o vector de ordena??o */
	for (iterador_k = esquerda; iterador_k <= direita; iterador_k++)
	{
		/* Vamos comparar ent?o os dois elementos em vector_auxiliar_de_ordenacao[iterador_i] e vector_auxiliar_de_ordenacao[iterador_j], */
		/* para ver qual fica "? esquerda", neste caso ? ordenar por ordem alfab?tica */
		if (strcmp(stock_de_produtos[vector_auxiliar_de_ordenacao[iterador_i].identificador].descricao,
				   stock_de_produtos[vector_auxiliar_de_ordenacao[iterador_j].identificador].descricao) > 0)
				   {
						vector_de_ordenacao[iterador_k] = vector_auxiliar_de_ordenacao[iterador_j --];
				   }
				   else
				   {   
						vector_de_ordenacao[iterador_k] = vector_auxiliar_de_ordenacao[iterador_i ++];
				   }
	}
}
			
/* Funcao que ordena um vector por ordem alfabetica da descricao do produto */
void mergesort_por_ordem_alfabetica(int esquerda,int direita)
{
	/* Vamos definir onde "partir" o vector */
	int meio = (esquerda + direita) / 2;
	/* Enquanto a esquerda for menor que a direita... */
	if (esquerda < direita)
	{
		mergesort_por_ordem_alfabetica(esquerda,meio); /* Partimos de novo a primeira metade */
		mergesort_por_ordem_alfabetica(meio + 1,direita); /* Partimos de novo a segunda metade */
		merge_por_ordem_alfabetica(esquerda,meio,direita);
	}
}
	

/* Fun??o que avalia se existe um determinado produto criado no stock */
/* Formato de entrada: int id_do_produto */
/* Formato de sa?da: int 0 se n?o existir, ou 1 se existir */	
int existe_produto_em_stock(int id_do_produto)
{
	if (id_do_produto >= numero_de_produtos_criados)
	{	
		/* O produto n?o est? criado em stock */
		return 0;
	}		
	/* O produto existe criado no stock */
	return 1;
}

/* Fun??o que avalia se existe uma determinada encomenda criada */
/* Formato de entrada: int id_da_encomenda */
/* Formato de sa?da: int 0 se n?o existir, ou 1 se existir */	
int existe_encomenda(int id_da_encomenda)
{
	if (id_da_encomenda >= numero_de_encomendas_criadas)
	{
		/* A encomenda n?o est? criada */
		return 0;
	}
	/* A encomenda est? criada*/
	return 1;
}

/* Fun??o que avalia se existe um determinado produto criado na encomenda */
/* Formato de entrada: int id_do_produto e int id_da_encomenda */
/* Formato de sa?da: int -1 se n?o existir esse produto nessa encomenda, ou o indice desse produto nessa encomenda se existir */	
int existe_produto_em_encomenda(int id_da_encomenda, int id_do_produto)
{
	/* Vari?veis auxiliares */
	int i; /* ciclo for*/
	
	/* Ciclo que vai percorrer a encomenda */
	for (i=0; i < lista_de_encomendas[id_da_encomenda].numero_de_produtos_criados_em_encomenda ;i++)
	{	
		/* Vamos ver se ? o produto que estamos ? procura */
		if (lista_de_encomendas[id_da_encomenda].produtos_na_encomenda[i].identificador == id_do_produto)
		{
			/* Como ? o produto que estamos ? procura, devolve o indice do mesmo dentro desta encomeda */
			return i;
		}
	}
	/* O produto n?o est? criado na encomenda */
	return -1;
}

	
/* Fun??o que cria um produto novo para inserir no stock */
/* Formato de entrada: `a descricao:preco:peso:qtd` */
/* Formato de sa?da: `Novo produto <idp>.` onde `<idp>` ? o identificador do produto criado. */	
void adiciona_produto(char *comando_do_utilizador)
{
	/* Vari?veis Locais */
	int id_do_produto_adicionado = 0;
	char descricao[DIMENSAO_DESCRICAO_PRODUTO];
	int preco = 0;
	int peso = 0;
	int quantidade = 0;
	struct produto produto_a_adicionar;
	
	/* Vari?veis auxiliares */
	int comprimento_do_comando; /* tamanho do comando */
	int i; /* ciclo for */
	
	/* Vari?veis para controlar onde est? cada comando no vector passado como argumento */
	int paragens = 0; /* Vamos detectar quando muda a componente do comando, ao passarmos no caracater ':' */
	int contador_componente = 0; /*controle da c?pia do componente do vector original para o seu pr?prio vector */
	char aux_componente[DIMENSAO_DO_COMANDO]; /*vector auxiliar para receber componentes num?ricas antes de passar a inteiro*/

	/* Vamos separar a string nas v?rias componentes */
	/* Cada vez que encontrarmos o caracter ':' na string, come?ando no 3? caracter, ? uma das 4 componentes do comando */
	comprimento_do_comando = strlen(comando_do_utilizador);
	
	/* Ciclo que vai percorrer o comando ? procura das componentes */
	/* Desde o 3? caracter at? ao pen?ltimo, porque os dois ?ltimos caracteres s?o '\n' e o caracter null */
	for (i = 2; i <= (comprimento_do_comando - 1); i++)
	{
		/* Se for uma mudanca de componente ou o fim do comando... */
		if (comando_do_utilizador[i] == ':' || comando_do_utilizador[i] == '\n')
		{
			/* Para o atoi n?o ir buscar a outros s?tios da mem?ria, temos que terminar a string */
			aux_componente[contador_componente] = '\0';
			switch (paragens)
			{
				case 0: /*descricao*/
					descricao[contador_componente] = '\0'; /* terminamos a string */
				break;
				case 1: /*preco*/
					preco = atoi(aux_componente);
				break;
				case 2: /*peso*/
					peso = atoi(aux_componente);
				break;
				case 3: /*quantidade*/
					quantidade = atoi(aux_componente);
				break;
			}
			paragens++;
			contador_componente = 0;
			continue; /* como ? um ':', avan?a para o pr?ximo caracter */
		}
		
		/* Se n?o for uma mudanca de componente, continua a preencher o respectivo vector */
		switch (paragens)
		{
			case 0: /*descricao*/
				descricao[contador_componente] = comando_do_utilizador[i];
				break;
			case 1: /*preco*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
			case 2:/*peso*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
			case 3:/*quantidade*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
		}
		contador_componente++;
	}
	
	/* Passamos para o novo produto os valores obtidos*/
	/*descricao:preco:peso:qtd*/
	strcpy(produto_a_adicionar.descricao, descricao);
	produto_a_adicionar.preco = preco;
	produto_a_adicionar.peso = peso;
	produto_a_adicionar.quantidade = quantidade;

	
	/*Vemos quantos produtos j? temos inseridos no vector do stock e adicionamos no pr?ximo espa?o*/
	/* Vamos adicionar o produto no espa?o a "seguir" ao numero total de produtos criados  */
	id_do_produto_adicionado = numero_de_produtos_criados;
	
	/* Completamos a estrutura com o identificador  */
	produto_a_adicionar.identificador = id_do_produto_adicionado;
	/* adicionamos o produto a este espa?o no vector */
	stock_de_produtos[id_do_produto_adicionado] = produto_a_adicionar;

	/* Ap?s o produto ter sido criado, devolvemos a informa??o do id */
	printf ("Novo produto %d.\n", id_do_produto_adicionado);	
	/* E actualizamos a vari?vel de controle */
	numero_de_produtos_criados++;
	
	/* sa?mos da fun??o, */	
	return;
}

/* Fun??o adiciona stock a um produto existente no sistema*/
/* Formato de entrada: `q idp:qtd`*/
/* Formato de sa?da: NADA (excepto erro)*/
void adiciona_stock_a_produto(char *comando_do_utilizador)
{
	/* Vari?veis Locais */
	int id_do_produto = 0;
	int quantidade = 0;
	
	/* Vari?veis auxiliares */
	int comprimento_do_comando; /* tamanho do comando */
	int i; /* ciclo for */
	
	/* Vari?veis para controlar onde est? cada comando no vector passado como argumento */
	int paragens = 0; /* Vamos detectar quando muda a componente do comando, ao passarmos no caracater ':' */
	int contador_componente = 0; /*controle da c?pia do componente do vector original para o seu pr?prio vector */
	char aux_componente[DIMENSAO_DO_COMANDO]; /*vector auxiliar para receber componentes num?ricas antes de passar a inteiro*/

	/* Vamos separar a string nas v?rias componentes */
	/* Cada vez que encontrarmos o caracter ':' na string, come?ando no 3? caracter, ? uma das 4 componentes do comando */
	comprimento_do_comando = strlen(comando_do_utilizador);

	/* Ciclo que vai percorrer o comando ? procura das componentes */
	/* Desde o 3? caracter at? ao pen?ltimo, porque os dois ?ltimos caracteres s?o '\n' e o caracter null */
	for (i = 2; i <= (comprimento_do_comando - 1); i++)
	{
		/* Se for uma mudanca de componente ou o fim do comando... */			
		if (comando_do_utilizador[i] == ':' || comando_do_utilizador[i] == '\n')
		{
			/* Para o atoi n?o ir buscar a outros s?tios da mem?ria, temos que terminar a string */
			aux_componente[contador_componente] = '\0';
			switch (paragens)
			{
				case 0: /*id_do_produto*/
				id_do_produto = atoi(aux_componente);
				break;
				case 1: /*quantidade*/
				quantidade = atoi(aux_componente);
				break;
			}
			paragens++;
			contador_componente = 0;
			continue; /* como ? um ':', avan?a para o pr?ximo caracter */
		}
		switch (paragens)
		{
			case 0: /*id_do_produto*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
			case 1:/*quantidade*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
		}
		contador_componente++;
	}
	
	/* Vamos ver se o id do produto existe, e se n?o existir d? erro */	
	if (existe_produto_em_stock(id_do_produto) == 0)
	{
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id_do_produto);
		return ;
	}
	
	/* Se existir, o produto existe e podemos adicionar stock */
	stock_de_produtos[id_do_produto].quantidade = stock_de_produtos[id_do_produto].quantidade + quantidade;
	return;
}

/* Fun??o que cria uma nova encomenda */
/* Formato de entrada: `N`*/
void cria_encomenda()
{
	/* Vari?veis Locais */
	int id_da_encomenda_adicionada = 0;
	
	/*Vemos quantas encomendas j? temos inseridos no vector das encomendas e adicionamos no pr?ximo espa?o*/
	/* Vamos criar a encomenda no espa?o a numero_de_encomendas_criadas */
	id_da_encomenda_adicionada = numero_de_encomendas_criadas;

	/* Ap?s a encomenda ter sido criada, devolvemos a informa??o do id */	
	printf ("Nova encomenda %d.\n",id_da_encomenda_adicionada);
	
	/* E actualizamos a vari?vel de controle */
	numero_de_encomendas_criadas++;
	
	/* sa?mos da fun??o */	
	return;

}

/* Fun??o que adiciona um produto a uma encomenda existente */
/* Formato de entrada: `A ide:idp:qtd*/
/* Formato de sa?da: NADA (excepto erro)*/
/* Erros:*/
/* `Impossivel adicionar produto <idp> a encomenda <ide>. Encomenda inexistente.` no caso de n?o existir nenhuma encomenda criada com esse identificador*/
/* `Impossivel adicionar produto <idp> a encomenda <ide>. Produto inexistente.` no caso de n?o existir nenhum produto criado com esse identificador*/
/* `Impossivel adicionar produto <idp> a encomenda <ide>. Quantidade em stock insuficiente.` no caso de n?o existir stock suficiente desse produto para satisfazer a encomenda*/
/* `Impossivel adicionar produto <idp> a encomenda <ide>. Peso da encomenda excede o maximo de 200.` no caso de a adi??o desse produto exceder o peso m?ximo permitido por encomenda*/
void adiciona_produto_a_encomenda(char *comando_do_utilizador)
{
	/* Vari?veis Locais */
	int id_do_produto = 0;
	int id_da_encomenda = 0;
	int quantidade = 0;
	int peso_produto = 0; /* peso total de produto a adicionar ? encomenda */
	int peso_encomenda = 0;
	
	/* Vari?veis auxiliares */
	int comprimento_do_comando; /* tamanho do comando */
	int i; /* ciclo for */	
	int indice_do_produto_na_encomenda = 0; /* para controlar onde est? o produto da encomenda */
	
	/* Vari?veis para controlar onde est? cada comando no vector passado como argumento */
	int paragens = 0; /* Vamos detectar quando muda a componente do comando, ao passarmos no caracater ':' */
	int contador_componente = 0; /*controle da c?pia do componente do vector original para o seu pr?prio vector */
	char aux_componente[DIMENSAO_DO_COMANDO]; /*vector auxiliar para receber componentes num?ricas antes de passar a inteiro*/

	/* Vamos separar a string nas v?rias componentes */
	/* Cada vez que encontrarmos o caracter ':' na string, come?ando no 3? caracter, ? uma das 4 componentes do comando */
	comprimento_do_comando = strlen(comando_do_utilizador);
	
	/* Ciclo que vai percorrer o comando ? procura das componentes */
	/* Desde o 3? caracter at? ao pen?ltimo, porque os dois ?ltimos caracteres s?o '\n' e o caracter null */
	for (i = 2; i <= (comprimento_do_comando - 1); i++)
	{
		/* Se for uma mudanca de componente ou o fim do comando... */
		if (comando_do_utilizador[i] == ':' || comando_do_utilizador[i] == '\n')
		{
			/* Para o atoi n?o ir buscar a outros s?tios da mem?ria, temos que terminar a string */
			aux_componente[contador_componente] = '\0';
			switch (paragens)
			{
				case 0: /*id_da_encomenda*/
				id_da_encomenda = atoi(aux_componente);
				break;
				case 1: /*id_do_produto*/
				id_do_produto = atoi(aux_componente);
				break;
				case 2: /*quantidade*/
				quantidade = atoi(aux_componente);
				break;
			}
			paragens++;
			contador_componente = 0;
			continue; /* como ? um ':', avan?a para o pr?ximo caracter */
		}
		
		/* Se n?o for uma mudanca de componente, continua a preencher o respectivo vector */
		switch (paragens)
		{
			case 0: /*id_da_encomenda*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
			case 1:/*id_do_produto*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
			case 2:/*quantidade*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
		}
		contador_componente++;
	}
	
	/* Vamos ver se a encomenda existe criada */
	if (existe_encomenda(id_da_encomenda) == 0)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",id_do_produto,id_da_encomenda);
		return;
	}
	
	/* Vamos ver se o produto existe criado */
	if (existe_produto_em_stock(id_do_produto) == 0)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",id_do_produto,id_da_encomenda);
		return;
	}

	/* Vamos ver se temos o produto suficiente em stock */
	if (stock_de_produtos[id_do_produto].quantidade < quantidade)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",id_do_produto,id_da_encomenda);
		return;		
	}

	/* Calculamos o peso que esta quantidade deste produto vai ter */
	peso_produto = quantidade * stock_de_produtos[id_do_produto].peso;
	peso_encomenda = lista_de_encomendas[id_da_encomenda].peso;
	
	/* Agora vamos ver se h? espa?o na encomenda para este produto entrar*/
	if ((peso_encomenda+peso_produto) > NUMERO_MAXIMO_DE_PESO_NUMA_ENCOMENDA)
	{
		/* Se o peso ultrapassar o limite, n?o podemos adicionar e devolvemos um erro */
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",id_do_produto,id_da_encomenda);
		return;
	}
	
	/* Se tudo correu bem at? aqui, podemos adicionar o produto ? encomenda. */
	/*Se o produto j? existir na encomenda, adiciona a nova quantidade ? quantidade existente*/
	
	/*Vamos procurar na encomenda a ver se o produto existe*/
	indice_do_produto_na_encomenda = existe_produto_em_encomenda(id_da_encomenda,id_do_produto);
	if (indice_do_produto_na_encomenda >= 0)
	{
		/* O produto existe na encomenda, por isso adicionamos ao j? existente */
		/* Adicionamos a quantidade de produto ? encomenda */
		lista_de_encomendas[id_da_encomenda].produtos_na_encomenda[indice_do_produto_na_encomenda].quantidade += quantidade;
		/* Actualizamos o peso da encomenda */
		lista_de_encomendas[id_da_encomenda].peso += peso_produto;
		/* Retiramos a quantidade de produto do stock */
		stock_de_produtos[id_do_produto].quantidade -= quantidade;
		/* Ap?s adicionarmos quantidade ao produto, sa?mos da fun??o */
		return;		 
	}
	else
	{
		/* O produto n?o est? criado na encomenda, por isso vamos cri?-lo */
		indice_do_produto_na_encomenda = lista_de_encomendas[id_da_encomenda].numero_de_produtos_criados_em_encomenda;

		lista_de_encomendas[id_da_encomenda].produtos_na_encomenda[indice_do_produto_na_encomenda].identificador = id_do_produto;
		/* Adicionamos a quantidade de produto ? encomenda */
		lista_de_encomendas[id_da_encomenda].produtos_na_encomenda[indice_do_produto_na_encomenda].quantidade = quantidade;
		/* Actualizamos o peso da encomenda */
		lista_de_encomendas[id_da_encomenda].peso += peso_produto;
		/* Retiramos a quantidade de produto do stock */
		stock_de_produtos[id_do_produto].quantidade -= quantidade;
		/* Alteramos a vari?vel de controle desta encomenda */
		lista_de_encomendas[id_da_encomenda].numero_de_produtos_criados_em_encomenda++;
		/* Ap?s criarmos o produto, sa?mos da fun??o */
	}
	
	/* sa?mos da fun??o, */	
	return;
}

/* Fun??o que remove stock a um produto existente*/
/* Formato de entrada: `r idp:qtd`*/
/* Formato de sa?da: NADA (excepto erro)*/
/* Erros:*/
/* `Impossivel remover stock do produto <idp>. Produto inexistente.` no caso de n?o existir nenhum produto criado com esse identificador*/
/* `Impossivel remover <qtd> unidades do produto <idp> do stock. Quantidade insuficiente.` no caso de a quantidade de stock restante ap?s a remo??o ser negativa*/
void remove_stock_a_produto(char *comando_do_utilizador)
{
	/* Vari?veis Locais */
	int id_do_produto = 0;
	int quantidade = 0;
	
	/* Vari?veis auxiliares */
	int comprimento_do_comando; /* tamanho do comando */
	int i; /* ciclo for */
	
	/* Vari?veis para controlar onde est? cada comando no vector passado como argumento */
	int paragens = 0; /* Vamos detectar quando muda a componente do comando, ao passarmos no caracater ':' */
	int contador_componente = 0; /*controle da c?pia do componente do vector original para o seu pr?prio vector */
	char aux_componente[DIMENSAO_DO_COMANDO]; /*vector auxiliar para receber componentes num?ricas antes de passar a inteiro*/

	/* Vamos separar a string nas v?rias componentes */
	/* Cada vez que encontrarmos o caracter ':' na string, come?ando no 3? caracter, ? uma das 4 componentes do comando */
	comprimento_do_comando = strlen(comando_do_utilizador);

	/* Ciclo que vai percorrer o comando ? procura das componentes */
	/* Desde o 3? caracter at? ao pen?ltimo, porque os dois ?ltimos caracteres s?o '\n' e o caracter null */
	for (i = 2; i <= (comprimento_do_comando - 1); i++)
	{
		/* Se for uma mudanca de componente ou o fim do comando... */			
		if (comando_do_utilizador[i] == ':' || comando_do_utilizador[i] == '\n')
		{
			/* Para o atoi n?o ir buscar a outros s?tios da mem?ria, temos que terminar a string */
			aux_componente[contador_componente] = '\0';
			switch (paragens)
			{
				case 0: /*id_do_produto*/
				id_do_produto = atoi(aux_componente);
				break;
				case 1: /*quantidade*/
				quantidade = atoi(aux_componente);
				break;
			}
			paragens++;
			contador_componente = 0;
			continue; /* como ? um ':', avan?a para o pr?ximo caracter */
		}
		switch (paragens)
		{
			case 0: /*id_do_produto*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
			case 1:/*quantidade*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
		}
		contador_componente++;
	}
	
	/* Vamos ver se o id do produto existe, e se n?o existir d? erro */	
	if (existe_produto_em_stock(id_do_produto) == 0)
	{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_do_produto);
		return;
	}
	
	/* Vamos ver se existe quantidade de produto suficiente para remover */
	if (stock_de_produtos[id_do_produto].quantidade < quantidade)
	{
		/* Se n?o houver quantidade suficiente, d? erro */
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, id_do_produto);
		return;
	}
	
	/* Caso exista o produto e haja quantidade suficiente para remover podemos remover stock */
	stock_de_produtos[id_do_produto].quantidade = stock_de_produtos[id_do_produto].quantidade - quantidade;
	return;
}

/* Fun??o que remove um produto a uma encomenda existente */
/* Formato de entrada: `R ide:idp`*/
/* Formato de sa?da: NADA (excepto erro)*/
/* Erros:*/
/* `Impossivel remover produto <idp> a encomenda <ide>. Encomenda inexistente.` no caso de n?o existir nenhuma encomenda criada com esse identificador*/
/* `Impossivel remover produto <idp> a encomenda <ide>. Produto inexistente.` no caso de n?o existir nenhum produto criado com esse identificador*/
void remove_produto_a_encomenda(char *comando_do_utilizador)
{
	/* Vari?veis Locais */
	int id_do_produto = 0;
	int id_da_encomenda = 0;
	
	/* Vari?veis auxiliares */
	int comprimento_do_comando; /* tamanho do comando */
	int i; /* ciclo for */
	int peso_produto = 0; /* Peso total a remover da encomenda */
	int indice_do_produto_na_encomenda = 0; /* para controlar onde est? o produto da encomenda */
	
	/* Vari?veis para controlar onde est? cada comando no vector passado como argumento */
	int paragens = 0; /* Vamos detectar quando muda a componente do comando, ao passarmos no caracater ':' */
	int contador_componente = 0; /*controle da c?pia do componente do vector original para o seu pr?prio vector */
	char aux_componente[DIMENSAO_DO_COMANDO]; /*vector auxiliar para receber componentes num?ricas antes de passar a inteiro*/

	/* Vamos separar a string nas v?rias componentes */
	/* Cada vez que encontrarmos o caracter ':' na string, come?ando no 3? caracter, ? uma das 4 componentes do comando */
	comprimento_do_comando = strlen(comando_do_utilizador);
	
	/* Ciclo que vai percorrer o comando ? procura das componentes */
	/* Desde o 3? caracter at? ao pen?ltimo, porque os dois ?ltimos caracteres s?o '\n' e o caracter null */
	for (i = 2; i <= (comprimento_do_comando - 1); i++)
	{
		/* Se for uma mudanca de componente ou o fim do comando... */
		if (comando_do_utilizador[i] == ':' || comando_do_utilizador[i] == '\n')
		{
			/* Para o atoi n?o ir buscar a outros s?tios da mem?ria, temos que terminar a string */
			aux_componente[contador_componente] = '\0';
			switch (paragens)
			{
				case 0: /*id_da_encomenda*/
				id_da_encomenda = atoi(aux_componente);
				break;
				case 1: /*id_do_produto*/
				id_do_produto = atoi(aux_componente);
				break;
			}
			paragens++;
			contador_componente = 0;
			continue; /* como ? um ':', avan?a para o pr?ximo caracter */
		}
		
		/* Se n?o for uma mudanca de componente, continua a preencher o respectivo vector */
		switch (paragens)
		{
			case 0: /*id_da_encomenda*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
			case 1:/*id_do_produto*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
		}
		contador_componente++;
	}
	
	/* Vamos ver se a encomenda existe criada */
	if (existe_encomenda(id_da_encomenda) == 0)
	{
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",id_do_produto,id_da_encomenda);
		return;
	}
	
	/* Vamos ver se o id do produto existe, e se n?o existir d? erro */	
	if (existe_produto_em_stock(id_do_produto) == 0)
	{
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",id_do_produto,id_da_encomenda);	
		return;
	}	
	
	
	/*Vamos procurar na encomenda a ver se o produto existe*/
	indice_do_produto_na_encomenda = existe_produto_em_encomenda(id_da_encomenda, id_do_produto);
	if (indice_do_produto_na_encomenda >= 0)
	{
		/* Calculamos o peso que esta quantidade deste produto vai ter */
		peso_produto = lista_de_encomendas[id_da_encomenda].produtos_na_encomenda[indice_do_produto_na_encomenda].quantidade * stock_de_produtos[id_do_produto].peso;
		/* Passamos a quantidade de produto existente para o stock */
		stock_de_produtos[id_do_produto].quantidade += lista_de_encomendas[id_da_encomenda].produtos_na_encomenda[indice_do_produto_na_encomenda].quantidade;
		/* Podemos ent?o remover o produto */
		lista_de_encomendas[id_da_encomenda].produtos_na_encomenda[indice_do_produto_na_encomenda].quantidade = 0;
		/* E vamos retirar o peso deste produto retirado ? encomenda */
		lista_de_encomendas[id_da_encomenda].peso -= peso_produto;
		/* Como o produto foi detectado e retirado, podemos sair da fun??o */
		return;
	}
	
	/* Se cheg?mos aqui, n?o detect?mos produto na encomenda, apesar de existir em stock, logo n?o devolvemos nada */
	
	/* sa?mos da fun??o, */	
	return;
}

/* Fun??o que calcula o custo de uma encomenda*/
/* Formato de entrada: `C ide`*/
/* Formato de sa?da: `Custo da encomenda <ide> <total>.` onde `<total>` ? o valor total da encomenda `<ide>`*/
/* Erros:*/
/* `Impossivel calcular custo da encomenda <ide>. Encomenda inexistente.` no caso de n?o existir nenhuma encomenda criada com esse identificador	*/		
void calcula_custo_encomenda(char *comando_do_utilizador)
{
	/* Vari?veis Locais */
	int id_da_encomenda = 0;
	int preco_da_encomenda = 0;

	/* Vari?veis auxiliares */
	int comprimento_do_comando; /* tamanho do comando */
	int i; /* ciclo for */
	int preco_produto; /*preco do produto antes de ser adicionado ao preco total da encomenda */
	int id_do_produto; /*identificador do produto no stock*/

	/* Vari?veis para controlar onde est? cada comando no vector passado como argumento */
	int contador_componente = 0; /*controle da c?pia do componente do vector original para o seu pr?prio vector */
	char aux_componente[DIMENSAO_DO_COMANDO]; /*vector auxiliar para receber componentes num?ricas antes de passar a inteiro*/
	
	/* Vamos separar a string nas v?rias componentes */
	/* Cada vez que encontrarmos o caracter ':' na string, come?ando no 3? caracter, ? uma das 4 componentes do comando */
	comprimento_do_comando = strlen(comando_do_utilizador);
	
	/* Ciclo que vai percorrer o comando ? procura das componentes */
	/* Desde o 3? caracter at? ao pen?ltimo, porque os dois ?ltimos caracteres s?o '\n' e o caracter null */
	for (i = 2; i <= (comprimento_do_comando - 1); i++)
	{
		/* Se for o fim do comando... */
		if (comando_do_utilizador[i] == '\n')
		{
			/* Para o atoi n?o ir buscar a outros s?tios da mem?ria, temos que terminar a string */
			aux_componente[contador_componente] = '\0';
			id_da_encomenda = atoi(aux_componente);
		}
		aux_componente[contador_componente] = comando_do_utilizador[i];
		contador_componente++;
	}

	
	/* Vamos ver se a encomenda existe criada */
	if (existe_encomenda(id_da_encomenda) == 0)
	{
		/* Como esta encomenda n?o est? criada, devolve o erro */
		printf ("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",id_da_encomenda);
		/* E sa?mos da fun??o */
		return;
	}

	/*Como a encomenda est? criada, temos que ir ver o pre?o de todos os produtos criados nessa encomenda e somar o pre?o de cada um*/
	for (i=0;i<lista_de_encomendas[id_da_encomenda].numero_de_produtos_criados_em_encomenda;i++)
	{
		id_do_produto = lista_de_encomendas[id_da_encomenda].produtos_na_encomenda[i].identificador;
		/* Se o produto estiver criado, temos que multiplicar o pre?o do produto pela quantidade na encomenda */
		preco_produto = lista_de_encomendas[id_da_encomenda].produtos_na_encomenda[i].quantidade * stock_de_produtos[id_do_produto].preco;
		/* Agora que temos o preco do produto, podemos adicionar ao preco total da encomenda */
		preco_da_encomenda += preco_produto;
	}	
	printf ("Custo da encomenda %d %d.\n",id_da_encomenda, preco_da_encomenda);	
	/* sa?mos da fun??o */	
	return;
}

/* Fun??o que altera o pre?o de um produto existente no sistema*/
/* Formato de entrada: `p idp:preco`*/
/* Formato de sa?da: NADA (excepto erro)*/
/* Erros:*/
/* `Impossivel alterar preco do produto <idp>. Produto inexistente.` no caso de n?o existir nenhum produto criado com esse identificador*/
void altera_preco_de_produto(char *comando_do_utilizador)
{
	/* Vari?veis Locais */
	int id_do_produto = 0;
	int preco = 0;
	
	/* Vari?veis auxiliares */
	int comprimento_do_comando; /* tamanho do comando */
	int i; /* ciclo for */
	
	/* Vari?veis para controlar onde est? cada comando no vector passado como argumento */
	int paragens = 0; /* Vamos detectar quando muda a componente do comando, ao passarmos no caracater ':' */
	int contador_componente = 0; /*controle da c?pia do componente do vector original para o seu pr?prio vector */
	char aux_componente[DIMENSAO_DO_COMANDO]; /*vector auxiliar para receber componentes num?ricas antes de passar a inteiro*/

	/* Vamos separar a string nas v?rias componentes */
	/* Cada vez que encontrarmos o caracter ':' na string, come?ando no 3? caracter, ? uma das 4 componentes do comando */
	comprimento_do_comando = strlen(comando_do_utilizador);
	
	/* Ciclo que vai percorrer o comando ? procura das componentes */
	/* Desde o 3? caracter at? ao pen?ltimo, porque os dois ?ltimos caracteres s?o '\n' e o caracter null */
	for (i = 2; i <= (comprimento_do_comando - 1); i++)
	{
		/* Se for uma mudanca de componente ou o fim do comando... */
		if (comando_do_utilizador[i] == ':' || comando_do_utilizador[i] == '\n')
		{
			/* Para o atoi n?o ir buscar a outros s?tios da mem?ria, temos que terminar a string */
			aux_componente[contador_componente] = '\0';
			switch (paragens)
			{
				case 0: /*id_do_produto*/
				id_do_produto = atoi(aux_componente);
				break;
				case 1: /*preco*/
				preco = atoi(aux_componente);
				break;
			}
			paragens++;
			contador_componente = 0;
			continue; /* como ? um ':', avan?a para o pr?ximo caracter */
		}
		
		/* Se n?o for uma mudanca de componente, continua a preencher o respectivo vector */
		switch (paragens)
		{
			case 0: /*id_do_produto*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
			case 1:/*preco*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
		}
		contador_componente++;
	}
	
	/* Vamos ver se o id do produto existe, e se n?o existir d? erro */	
	if (existe_produto_em_stock(id_do_produto) == 0)
	{
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",id_do_produto);
		return;
	}
		
	/* Se cheg?mos aqui, detect?mos produto, logo alteramos o preco */
	stock_de_produtos[id_do_produto].preco = preco;
	
	/* sa?mos da fun??o, */	
	return;
}

/* Fun??o lista a descri??o e a quantidade de um produto numa encomenda*/
/* Formato de entrada: `E ide:idp`*/
/* Formato de sa?da: `<desc> <qtd>.` onde `<desc>` ? a descri??o do produto `<idp>` e `<qtd>` ? a quantidade desse produto na encomenda `<ide>`*/
/* Erros:*/
/* `Impossivel listar encomenda <ide>. Encomenda inexistente.` no caso de n?o existir nenhuma encomenda criada com esse identificador*/
/* `Impossivel listar produto <idp>. Produto inexistente.` no caso de n?o existir nenhum produto criado com esse identificador*/
void lista_descricao_e_quantidade_de_produto_numa_encomenda(char *comando_do_utilizador)
{
	/* Vari?veis Locais */
	int id_do_produto = 0;
	int id_da_encomenda = 0;
	
	/* Vari?veis auxiliares */
	int comprimento_do_comando; /* tamanho do comando */
	int i; /* ciclo for */
	int indice_do_produto_na_encomenda = 0; /* para controlar onde est? o produto da encomenda */
	
	/* Vari?veis para controlar onde est? cada comando no vector passado como argumento */
	int paragens = 0; /* Vamos detectar quando muda a componente do comando, ao passarmos no caracater ':' */
	int contador_componente = 0; /*controle da c?pia do componente do vector original para o seu pr?prio vector */
	char aux_componente[DIMENSAO_DO_COMANDO]; /*vector auxiliar para receber componentes num?ricas antes de passar a inteiro*/

	/* Vamos separar a string nas v?rias componentes */
	/* Cada vez que encontrarmos o caracter ':' na string, come?ando no 3? caracter, ? uma das 4 componentes do comando */
	comprimento_do_comando = strlen(comando_do_utilizador);
	
	/* Ciclo que vai percorrer o comando ? procura das componentes */
	/* Desde o 3? caracter at? ao pen?ltimo, porque os dois ?ltimos caracteres s?o '\n' e o caracter null */
	for (i = 2; i <= (comprimento_do_comando - 1); i++)
	{
		/* Se for uma mudanca de componente ou o fim do comando... */
		if (comando_do_utilizador[i] == ':' || comando_do_utilizador[i] == '\n')
		{
			/* Para o atoi n?o ir buscar a outros s?tios da mem?ria, temos que terminar a string */
			aux_componente[contador_componente] = '\0';
			switch (paragens)
			{
				case 0: /*id_da_encomenda*/
				id_da_encomenda = atoi(aux_componente);
				break;
				case 1: /*id_do_produto*/
				id_do_produto = atoi(aux_componente);
				break;
			}
			paragens++;
			contador_componente = 0;
			continue; /* como ? um ':', avan?a para o pr?ximo caracter */
		}
		
		/* Se n?o for uma mudanca de componente, continua a preencher o respectivo vector */
		switch (paragens)
		{
			case 0: /*id_da_encomenda*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
			case 1:/*id_do_produto*/
				aux_componente[contador_componente] = comando_do_utilizador[i];
				break;
		}
		contador_componente++;
	}
	
	/* Vamos ver se a encomenda existe criada */
	if (existe_encomenda(id_da_encomenda) == 0)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_da_encomenda);
		return;
	}
	
	/* Vamos ver se o id do produto existe, e se n?o existir d? erro */	
	if (existe_produto_em_stock(id_do_produto) == 0)
	{
		printf("Impossivel listar produto %d. Produto inexistente.\n",id_do_produto);	
		return;
	}	

	/*Vamos procurar na encomenda a ver se o produto existe*/
	indice_do_produto_na_encomenda = existe_produto_em_encomenda(id_da_encomenda, id_do_produto);
	if (indice_do_produto_na_encomenda >= 0)
	{
		/* Vamos listar a descricao e a quantidade do produto  nesta encomenda*/
		printf("%s %d.\n",stock_de_produtos[id_do_produto].descricao,lista_de_encomendas[id_da_encomenda].produtos_na_encomenda[indice_do_produto_na_encomenda].quantidade);
		return;
	}
	
	/* Se cheg?mos aqui, n?o detect?mos produto, logo devolvemos o produto com 0 de quantidade */
		/* Vamos listar a descricao e a quantidade do produto = 0  */
		printf("%s 0.\n",stock_de_produtos[id_do_produto].descricao);
	
	/* sa?mos da fun??o, */	
	return;
	
}

/* Fun??o que lista o identificador da encomenda em que o produto dado ocorre mais vezes. Se houver 2 ou mais encomendas nessa situa??o, dever? imprimir a encomenda de menor `id`.*/
/* Formato de entrada: `m idp`*/
/* Formato de sa?da:*/
/* `Maximo produto <idp> <ide> <qtd>.` onde `<ide>` ? o n?mero da encomenda em que `<idp>` ocorre mais vezes, sendo essa quantidade `<qtd>`*/
/* N?o dever? listar nada caso o produto `<idp>` n?o ocorra em nenhuma encomenda, ou caso n?o haja encomendas*/
/* Erros:*/
/* `Impossivel listar maximo do produto <idp>. Produto inexistente.` no caso de n?o existir nenhum produto criado com esse identificador*/
void lista_maximo_do_produto(char *comando_do_utilizador)
{
	/* Vari?veis Locais */
	int id_do_produto = 0;
	int id_da_encomenda = 0;

	/* Vari?veis auxiliares */
	int comprimento_do_comando; /* tamanho do comando */
	int i; /* ciclo for */
	int quantidade_de_produto_maximo = 0; /* quantidade de produto maior encontrado numa encomenda */
	int indice_do_produto_na_encomenda = 0; /* para controlar onde est? o produto da encomenda */	

	/* Vari?veis para controlar onde est? cada comando no vector passado como argumento */
	int contador_componente = 0; /*controle da c?pia do componente do vector original para o seu pr?prio vector */
	char aux_componente[DIMENSAO_DO_COMANDO]; /*vector auxiliar para receber componentes num?ricas antes de passar a inteiro*/
	
	/* Vamos separar a string nas v?rias componentes */
	/* Cada vez que encontrarmos o caracter ':' na string, come?ando no 3? caracter, ? uma das 4 componentes do comando */
	comprimento_do_comando = strlen(comando_do_utilizador);
	
	/* Ciclo que vai percorrer o comando ? procura das componentes */
	/* Desde o 3? caracter at? ao pen?ltimo, porque os dois ?ltimos caracteres s?o '\n' e o caracter null */
	for (i = 2; i <= (comprimento_do_comando - 1); i++)
	{
		/* Se for o fim do comando... */
		if (comando_do_utilizador[i] == '\n')
		{
			/* Para o atoi n?o ir buscar a outros s?tios da mem?ria, temos que terminar a string */
			aux_componente[contador_componente] = '\0';
			id_do_produto = atoi(aux_componente);
		}
		aux_componente[contador_componente] = comando_do_utilizador[i];
		contador_componente++;
	}
	
	/* Vamos ver se o id do produto existe, e se n?o existir d? erro */	
	if (existe_produto_em_stock(id_do_produto) == 0)
	{
		/* Como este produto n?o est? criado, devolve o erro */
		printf ("Impossivel listar maximo do produto %d. Produto inexistente.\n",id_do_produto);
		/* E sa?mos da fun??o */
		return;
	}

	/* Se o produto est? criado vamos ent?o percorrer todas as encomendas ? procura deste produto */
	for (i=0;i<numero_de_encomendas_criadas;i++)
	{
		/*Vamos procurar na encomenda a ver se o produto existe*/
		indice_do_produto_na_encomenda = existe_produto_em_encomenda(i,id_do_produto); /* -1 se nao existir, >= 0 se existir */
		if (indice_do_produto_na_encomenda >= 0)
		{
			/*Como este produto est? na encomenda e est? criado, vamos ver se a quantidade ? maior do que j? t?nhamos ou se a quantidade ? igual e o id ? menor*/
			if (quantidade_de_produto_maximo < lista_de_encomendas[i].produtos_na_encomenda[indice_do_produto_na_encomenda].quantidade)
			{
				/* Como a quantidade de produto nesta encomenda ? maior, fica esta encomenda para ser listada */
				id_da_encomenda = i;
				quantidade_de_produto_maximo = lista_de_encomendas[i].produtos_na_encomenda[indice_do_produto_na_encomenda].quantidade;
			}						
		}	
	}
	/* Formato de sa?da:*/
	/* `Maximo produto <idp> <ide> <qtd>.` onde `<ide>` ? o n?mero da encomenda em que `<idp>` ocorre mais vezes, sendo essa quantidade `<qtd>`*/
	/* N?o dever? listar nada caso o produto `<idp>` n?o ocorra em nenhuma encomenda, ou caso n?o haja encomendas*/
	
	/*Caso o produto m?ximo seja 0, quer dizer que n?o foi encontrado este produto em nenhuma encomenda, logo n?o devolve nada */
	if (quantidade_de_produto_maximo == 0)
	{
		return;
	}
	/*Caso contr?rio, lista a encomenda em quest?o com a quantidade de produto*/
	printf("Maximo produto %d %d %d.\n", id_do_produto, id_da_encomenda, quantidade_de_produto_maximo);
	return;
}

/* Fun??o que lista todos os produtos existentes no sistema por ordem crescente de pre?o. Se houver 2 ou mais produtos com o mesmo pre?o, dever? imprimir esses por ordem crescente de `id` de produto*/
/* Formato de entrada: `l`*/
/* Formato de sa?da: Um bloco no formato abaixo, e em que os produtos s?o listados por ordem crescente de pre?o~*/
/*Produtos*/
/* <desc1> <preco1> <qtd1 em stock>*/
/* <desc2> <preco2> <qtd2 em stock>*/
/*...*/
/* <descn> <precon> <qtdn em stock>*/
/* Erros: N?o aplic?vel*/
void lista_produtos_por_preco()
{
	/* Vari?veis auxiliares */
	int i; /* ciclo for */


	/* Depois, vamos popular este vector com os v?rios produtos */
	for (i=0;i<numero_de_produtos_criados;i++)
	{
		/* Este produto est? criado, por isso podemos adicionar ao vector de produtos a ordenar o id do produto em quest?o */
		vector_de_ordenacao[i] = stock_de_produtos[i];
	}
	
	/* Aqui j? temos o vector_de_ordenacao preenchido com os id's de todos os produtos criados no sistema */
	/* desde vector_de_ordenacao[0] at? vector_de_ordenacao[numero_de_produtos_criados] */
	
	/* Vamos ordenar este vector com o mergesort */
	mergesort_por_preco(0,numero_de_produtos_criados - 1);
	
	/* imprime o vector */
	/* Formato de sa?da: Um bloco no formato abaixo, e em que os produtos s?o listados por ordem crescente de pre?o~*/
	/*Produtos*/
	/* <desc1> <preco1> <qtd1 em stock>*/
	/* <desc2> <preco2> <qtd2 em stock>*/
	/*...*/
	/* <descn> <precon> <qtdn em stock>*/
	printf("Produtos\n");
	for (i=0;i<numero_de_produtos_criados;i++)
	{
		printf("* %s %d %d\n", vector_de_ordenacao[i].descricao, vector_de_ordenacao[i].preco, vector_de_ordenacao[i].quantidade);
	}
	return;	
}

/* Fun??o que lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o*/
/* Formato de entrada: `L <ide>`*/
/* Formato de sa?da: Um bloco no formato abaixo, e em que os produtos s?o listados por ordem alfab?tica de descri??o*/
/*Encomenda <ide>*/
/* <desc1> <preco1> <qtd1 na ide>*/
/* <desc2> <preco2> <qtd2 na ide>*/
/*...*/
/* <descn> <precon> <qtdn na ide>*/
/* Erros:*/
/* `Impossivel listar encomenda <ide>. Encomenda inexistente.` no caso de n?o existir nenhuma encomenda criada com esse identificador*/
void lista_descricao_de_produtos_numa_encomenda_por_ordem(char *comando_do_utilizador)
{
	/* Vari?veis Locais */
	int id_da_encomenda = 0;
	
	/* Vari?veis auxiliares */
	int comprimento_do_comando; /* tamanho do comando */
	int i; /* ciclo for */
	
	/* Vari?veis para controlar onde est? cada comando no vector passado como argumento */
	int contador_componente = 0; /*controle da c?pia do componente do vector original para o seu pr?prio vector */
	char aux_componente[DIMENSAO_DO_COMANDO]; /*vector auxiliar para receber componentes num?ricas antes de passar a inteiro*/

	/* Vamos separar a string nas v?rias componentes */
	/* Cada vez que encontrarmos o caracter ':' na string, come?ando no 3? caracter, ? uma das 4 componentes do comando */
	comprimento_do_comando = strlen(comando_do_utilizador);
	
	/* Ciclo que vai percorrer o comando ? procura das componentes */
	/* Desde o 3? caracter at? ao pen?ltimo, porque os dois ?ltimos caracteres s?o '\n' e o caracter null */
	for (i = 2; i <= (comprimento_do_comando - 1); i++)
	{
		/* Se for o fim do comando... */
		if (comando_do_utilizador[i] == '\n')
		{
			/* Para o atoi n?o ir buscar a outros s?tios da mem?ria, temos que terminar a string */
			aux_componente[contador_componente] = '\0';
			id_da_encomenda = atoi(aux_componente);
			break;
		}
		aux_componente[contador_componente] = comando_do_utilizador[i];
		contador_componente++;
	}
	
	/* Vamos ver se a encomenda existe criada */
	if (existe_encomenda(id_da_encomenda) == 0)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_da_encomenda);
		return;
	}

	
	/* Vamos imprimir o cabe?alho */
	printf("Encomenda %d\n",id_da_encomenda);	
	
	/*Vamos procurar na encomenda todos os produtos existentes e popular o vector auxiliar de ordenacao com eles*/
	for (i=0;i<lista_de_encomendas[id_da_encomenda].numero_de_produtos_criados_em_encomenda;i++)
	{
		vector_de_ordenacao[i] = lista_de_encomendas[id_da_encomenda].produtos_na_encomenda[i];		
	}
	
	
	/* Vamos ordenar o vector auxiliar de ordenacao usando o mergesort */
	mergesort_por_ordem_alfabetica(0,lista_de_encomendas[id_da_encomenda].numero_de_produtos_criados_em_encomenda - 1);
	
	
	/* Vamos listar todos os produtos no vector auxiliar de ordena??o, se a quantidade for superior a zero*/
	for (i=0;i<lista_de_encomendas[id_da_encomenda].numero_de_produtos_criados_em_encomenda;i++)
	{
		if (vector_de_ordenacao[i].quantidade > 0)
		{
			printf("* %s %d %d\n",stock_de_produtos[vector_de_ordenacao[i].identificador].descricao,
								 stock_de_produtos[vector_de_ordenacao[i].identificador].preco,
								 vector_de_ordenacao[i].quantidade);
		}
	}

	

	/* sa?mos da fun??o, */	
	return;
	
}



int main()
{
		
	/* Ciclo que vai aguardar pelos comandos do utilizador. ? interrompido se o comando for "x" */
	while  (1)
	{
		
		/* Espera pelo comando do utilizador */
		/* fgets em vez de scanf para podermos receber o whitespace */
		fgets(comando_do_utilizador, DIMENSAO_DO_COMANDO, stdin);
		
		switch(comando_do_utilizador[0])
		{
			
		/* | __x__ | termina o programa | */
			case 'x':
				return 0;
				break;
			
		/* __a__ - adiciona um novo produto ao sistema */
		/* Formato de entrada: `a descricao:preco:peso:qtd` */
		/* Formato de sa?da: `Novo produto <idp>.` onde `<idp>` ? o identificador do produto criado. */
			case 'a':
				adiciona_produto(comando_do_utilizador);
				break;
		/* __q__ - adiciona stock a um produto existente no sistema*/
		/* Formato de entrada: `q idp:qtd`*/
		/* Formato de sa?da: NADA (excepto erro)*/
		/* Erros:*/
		/* `Impossivel adicionar produto <idp> ao stock. Produto inexistente.` no caso de n?o existir nenhum produto criado com esse identificador*/
			case 'q':
				adiciona_stock_a_produto(comando_do_utilizador);
				break;
		/* __N__ - cria uma nova encomenda*/
		/* Formato de entrada: `N`*/
		/* Formato de sa?da: `Nova encomenda <ide>.` onde `<ide>` ? o identificador da encomenda criada.		*/
			case 'N':
				cria_encomenda(comando_do_utilizador);
				break;
		/* __A__ - adiciona um produto a uma encomenda. Se o produto j? existir na encomenda, adiciona a nova quantidade ? quantidade existente*/
		/* Formato de entrada: `A ide:idp:qtd`*/
		/* Formato de sa?da: NADA (excepto erro)*/
		/* Erros:*/
		/* `Impossivel adicionar produto <idp> a encomenda <ide>. Encomenda inexistente.` no caso de n?o existir nenhuma encomenda criada com esse identificador*/
		/* `Impossivel adicionar produto <idp> a encomenda <ide>. Produto inexistente.` no caso de n?o existir nenhum produto criado com esse identificador*/
		/* `Impossivel adicionar produto <idp> a encomenda <ide>. Quantidade em stock insuficiente.` no caso de n?o existir stock suficiente desse produto para satisfazer a encomenda*/
		/* `Impossivel adicionar produto <idp> a encomenda <ide>. Peso da encomenda excede o maximo de 200.` no caso de a adi??o desse produto exceder o peso m?ximo permitido por encomenda*/
			case 'A':
				adiciona_produto_a_encomenda(comando_do_utilizador);
				break;
		/* __r__ - remove stock a um produto existente*/
		/* Formato de entrada: `r idp:qtd`*/
		/* Formato de sa?da: NADA (excepto erro)*/
		/* Erros:*/
		/* `Impossivel remover stock do produto <idp>. Produto inexistente.` no caso de n?o existir nenhum produto criado com esse identificador*/
		/* `Impossivel remover <qtd> unidades do produto <idp> do stock. Quantidade insuficiente.` no caso de a quantidade de stock restante ap?s a remo??o ser negativa*/
			case 'r':
				remove_stock_a_produto(comando_do_utilizador);
				break;
		/* __R__ - remove um produto de uma encomenda*/
		/* Formato de entrada: `R ide:idp`*/
		/* Formato de sa?da: NADA (excepto erro)*/
		/* Erros:*/
		/* `Impossivel remover produto <idp> a encomenda <ide>. Encomenda inexistente.` no caso de n?o existir nenhuma encomenda criada com esse identificador*/
		/* `Impossivel remover produto <idp> a encomenda <ide>. Produto inexistente.` no caso de n?o existir nenhum produto criado com esse identificador*/
			case 'R':
				remove_produto_a_encomenda(comando_do_utilizador);
				break;
		/* __C__ - calcula o custo de uma encomenda*/
		/* Formato de entrada: `C ide`*/
		/* Formato de sa?da: `Custo da encomenda <ide> <total>.` onde `<total>` ? o valor total da encomenda `<ide>`*/
		/* Erros:*/
		/* `Impossivel calcular custo da encomenda <ide>. Encomenda inexistente.` no caso de n?o existir nenhuma encomenda criada com esse identificador	*/		
			case 'C':
				calcula_custo_encomenda(comando_do_utilizador);
				break;
		/* __p__ - altera o pre?o de um produto existente no sistema*/
		/* Formato de entrada: `p idp:preco`*/
		/* Formato de sa?da: NADA (excepto erro)*/
		/* Erros:*/
		/* `Impossivel alterar preco do produto <idp>. Produto inexistente.` no caso de n?o existir nenhum produto criado com esse identificador*/
			case 'p':
				altera_preco_de_produto(comando_do_utilizador);
				break;
		/* __E__ - lista a descri??o e a quantidade de um produto numa encomenda*/
		/* Formato de entrada: `E ide:idp`*/
		/* Formato de sa?da: `<desc> <qtd>.` onde `<desc>` ? a descri??o do produto `<idp>` e `<qtd>` ? a quantidade desse produto na encomenda `<ide>`*/
		/* Erros:*/
		/* `Impossivel listar encomenda <ide>. Encomenda inexistente.` no caso de n?o existir nenhuma encomenda criada com esse identificador*/
		/* `Impossivel listar produto <idp>. Produto inexistente.` no caso de n?o existir nenhum produto criado com esse identificador*/
			case 'E':
				lista_descricao_e_quantidade_de_produto_numa_encomenda(comando_do_utilizador);
				break;
		/* __m__ - lista o identificador da encomenda em que o produto dado ocorre mais vezes. Se houver 2 ou mais encomendas nessa situa??o, dever? imprimir a encomenda de menor `id`.*/
		/* Formato de entrada: `m idp`*/
		/* Formato de sa?da:*/
		/* `Maximo produto <idp> <ide> <qtd>.` onde `<ide>` ? o n?mero da encomenda em que `<idp>` ocorre mais vezes, sendo essa quantidade `<qtd>`*/
		/* N?o dever? listar nada caso o produto `<idp>` n?o ocorra em nenhuma encomenda, ou caso n?o haja encomendas*/
		/* Erros:*/
		/* `Impossivel listar maximo do produto <idp>. Produto inexistente.` no caso de n?o existir nenhum produto criado com esse identificador*/
			case 'm':
				lista_maximo_do_produto(comando_do_utilizador);
				break;
		/* __l__ - lista todos os produtos existentes no sistema por ordem crescente de pre?o. Se houver 2 ou mais produtos com o mesmo pre?o, dever? imprimir esses por ordem crescente de `id` de produto*/
		/* Formato de entrada: `l`*/
		/* Formato de sa?da: Um bloco no formato abaixo, e em que os produtos s?o listados por ordem crescente de pre?o*/
		/*Produtos*/
		/* <desc1> <preco1> <qtd1 em stock>*/
		/* <desc2> <preco2> <qtd2 em stock>*/
		/*...*/
		/* <descn> <precon> <qtdn em stock>*/
		/* Erros: N?o aplic?vel		*/	
			case 'l':
				lista_produtos_por_preco();
				break;
		/* __L__ - lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o*/
		/* Formato de entrada: `L <ide>`*/
		/* Formato de sa?da: Um bloco no formato abaixo, e em que os produtos s?o listados por ordem alfab?tica de descri??o*/
		/*Encomenda <ide>*/
		/* <desc1> <preco1> <qtd1 na ide>*/
		/* <desc2> <preco2> <qtd2 na ide>*/
		/*...*/
		/* <descn> <precon> <qtdn na ide>*/
		/* Erros:*/
		/* `Impossivel listar encomenda <ide>. Encomenda inexistente.` no caso de n?o existir nenhuma encomenda criada com esse identificador*/
			case 'L':
				lista_descricao_de_produtos_numa_encomenda_por_ordem(comando_do_utilizador);
				break;

		}
	}
	return 0;
}