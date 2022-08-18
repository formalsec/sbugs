#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* constantes definidas */
#define MAX 63				    /* numero maximo de de carateres da string da descricao do produto */
#define	MAX_PRODUTOS 10000		/* numero maximo de produtos da loja (stock) */
#define MAX_ENCOMENDAS 500		/* numero maximo de encomendas */
#define	MAX_PESO 200			/* peso maximo de uma encomenda */
#define MAX_CARACTERISTICAS 4	
#define MAX_INFOENCOMENDA 2		/* numero maximo da infoencomenda com ide e qtd do produto na encomenda */

/* ESTRUTURA DO PRODUTO */

typedef struct produto 			
{
	int idedoproduto;
	char nomedoproduto[MAX];
	int precodoproduto;
	int pesodoproduto;
	int qtddoproduto;
}produto;

/* ESTRUTURA DA ENCOMENDA */

typedef struct encomenda
{
	int idedaencomenda;
	int pesodaencomenda;
	int infoencomenda[MAX_PESO][MAX_INFOENCOMENDA];
}encomenda;

produto loja[MAX_PRODUTOS];
encomenda encomendas[MAX_ENCOMENDAS];


/* FUN??ES AUXILIARES */

/* Funcao auxiliar que le o input e que e utilizada na maior parte das principais */

int lerlinha(char linha[])
{
	char c; 		
	int i = 0;
	while ((c = getchar()) != '\n')		/* Neste ciclo o c que ? getchar vai fazendo getchar ao longo da linha ou seja l? a linha at? o caracter ser diferente de \n */
	{
		linha[i] = c;		/* cada indice da linha vai ser igual ao c ou seja vai sempre verificando caracter a caracter para ver se da \n */
		i++;	
	}
	linha[i] = '\0';		/* fim do vetor ? igual ao fim da linha lendo assim s? um linha */
	return 0;
}

/* Fun??o auxiliar que separa o input lido pela fun??o auxiliar acima e que ? utilizada na maior parte das principais para aceder a cada dado que nos ? fornecido */

int separarstring(char linha[], char dadosdoinput[][MAX])
{
	int i, a = 0, b = 0, c = 0;
	for (i = 0; i < MAX_CARACTERISTICAS; i++)
	{
		strncpy(dadosdoinput[i], "", MAX);
	}
	while (linha[c] != '\0')
	{
		if (linha[c] == ':')				
 		{
			dadosdoinput[a][b] = '\0';		/* Sempre que na leitura da linha se encontra um ':' corta-se esses dois pontos */
			b = 0;
			a++;
		}
		else 
		{
			dadosdoinput[a][b] = linha[c];  /* Se n?o for encontrado os dois pontos prossegue-se com a leitura da linha */
			b++;			
		}
		c++;
	}
	return 0;								/* No fim fica-se com o input sem dois pontos, ou seja e mais f?cil aceder a cada dado que nos d?o no input */
}

/* Fun??o auxiliar que tem no seu corpo o algoritmo merge em si e como funciona e que de seguida o mergesort o realiza. Tem uma vari?vel 'alfabetica' pois esta fun??o ? usada como fun??o auxiliar no comando l e no comando L que s?o ambas 
para ordena??o uma pelo pre?o e outra por ordem alfab?tica em que se alfabetica ? 0, realiza o merge para os pre?os se for um, realiza para organizar por ordem alfab?tica. A fun??o acaba por criar um vetor auxiliar para ir adicionando
?ndices do vetor principal e para ir comparando entre si para ver se os valores do pre?o s?o maiores ou menores de forma a organiz?-los por ordem crescente de pre?o. Se for para ordenar alfabeticamente em vez de haver uma compara??o entre
as duas tabelas em termos num?ricos, h? em termo de letra usando assim o strcmp que compara duas letras uma de cada tabela e d? menor que 0 se a letra da primeira tabela for anterior ? da segunda.  */

void merge(int l, int r, int m, int tabela_indices[], int alfabetica)
{
	int a,b,c, tabela_auxiliar[MAX_PRODUTOS], tabela_alfabetica[MAX_PESO]; /* S?o criadas tabelas ou vetores uma para o algoritmo de ordena??o de pre?os e outra para a de ordena??o por ordem alfb?tica, l ? o limite ? esquerda do vetor inicial, r ? o limite final, m ? o meio  */
	if (alfabetica == 0)		/* Testa para que algoritmo ? que o merge vai atuar, como alfabetica == 0 escolhe o de ordena??o de pre?os que ? com a utiliza??o da tabela_auxiliar e onde se esquece a tabela_alfab?tica */ 
	{	
		for (a = m + 1; a > l; a--)																		 
		{																								
			tabela_auxiliar[a - 1] = tabela_indices[a - 1];		
		}
		for (b = m; b < r; b++)			
		{
			tabela_auxiliar[r + m - b] = tabela_indices[b + 1];		 
		}	
		for (c = l; c <= r; c++)		
		{
			if (loja[tabela_auxiliar[b]].precodoproduto < loja[tabela_auxiliar[a]].precodoproduto)		 
			{
				tabela_indices[c] = tabela_auxiliar[b--];
			}
			else if (loja[tabela_auxiliar[b]].idedoproduto < loja[tabela_auxiliar[a]].idedoproduto && loja[tabela_auxiliar[b]].precodoproduto == loja[tabela_auxiliar[a]].precodoproduto)
			{
				tabela_indices[c] = tabela_auxiliar[b--];
			}
			else
			{
				tabela_indices[c] = tabela_auxiliar[a++];
			}
		}	
	}
	else 
	{
		for (a = m + 1; a > l; a--)
		{
			tabela_alfabetica[a - 1] = tabela_indices[a - 1];
		}
		for (b = m; b < r; b++)
		{
			tabela_alfabetica[r + m - b] = tabela_indices[b + 1];
		}	
		for (c = l; c <= r; c++)
		{
			if (strcmp(loja[tabela_alfabetica[b]].nomedoproduto, loja[tabela_alfabetica[a]].nomedoproduto) < 0)
			{
				tabela_indices[c] = tabela_alfabetica[b--];
			}
	
			else
			{
				tabela_indices[c] = tabela_alfabetica[a++];
			}
		}	
	}
}

/* Fun??o auxiliar que realiza o algoritmo descrito na fun??o auxiliar merge usada em ambos os comandos de ordena??o*/ 
void mergesort(int tabela_indices[], int l , int r, int alfabetica)
{
	int m = (r + l) / 2;
	if (r <= l)		/* testa se o limite do lado direito e menor ou igual ao esquerdo */
		return;		/* se for a fun??o acaba pois o limite do lado direito tem sempre de ser maior */
	mergesort(tabela_indices, l, m, alfabetica);
	mergesort(tabela_indices, m+1, r, alfabetica);
	merge(l, r, m, tabela_indices, alfabetica);
}



/* FUN??ES PRINCIPAIS */

/* Esta fun??o principal recebe uma descri??o que ? o nome do produto, o seu preco, o seu peso e a sua quantidade e adiciona um novo produto ao sistema */

void addproduto()  /*comando a */
{
	int i = 0, a = 0;
	char linha[MAX], dadosdoinput[MAX_CARACTERISTICAS][MAX];
	getchar();		/* Eliminar o espa?o que vem a seguir ao comando */
	lerlinha(linha);		/* L? a linha do input */
	separarstring(linha, dadosdoinput);		/* Separa a string em dados separados sendo possivel aceder ao indice a partir do dadosdoinput[] */
	while (i < MAX_PRODUTOS)
	{
		if (loja[i].idedoproduto != -1)		/* Inicializando o indice dos produtos a -1, ou seja, para ver se existe */  
		{
			a++;						
		}
		else
		{
			break;
		}
		i++;
	}
	loja[a].idedoproduto = a;								/* O indice do produto ? igual ao n?mero do produto da loja */
	strcpy(loja[a].nomedoproduto , dadosdoinput[0]);		/* O primeiro dado que o imput da ? o nome desse produto */
	loja[a].precodoproduto = atoi(dadosdoinput[1]);			/* O pre?o do produto ? igual ao segundo dado do input */
	loja[a].pesodoproduto = atoi(dadosdoinput[2]);			/* O peso do produto e igual ao terceiro dado do input */
	loja[a].qtddoproduto = atoi(dadosdoinput[3]);			/* O quarto dado que o input d? e a quantidade do produto */
	printf("Novo produto %d.\n", a);
}

/* Esta fun??o principal recebe um indice de um produto e uma quantidade e adiciona stock a esse produto existente no sistema e d? erro se o produto n?o existe no sistema */ 

void addstock()  /* comando q */
{
	char linha[MAX], dadosdoinput[MAX_CARACTERISTICAS][MAX];
	getchar();		/* Eliminar o espa?o que vem a seguir ao comando */
	lerlinha(linha);		/* L? a linha do input */
	separarstring(linha, dadosdoinput);		/* Separa a string em dados separados sendo possivel aceder ao indice a partir do dadosdoinput[] */
	if (loja[atoi(dadosdoinput[0])].idedoproduto != -1)		/* Para ver se o produto existe */
	{	
		loja[atoi(dadosdoinput[0])].qtddoproduto += atoi(dadosdoinput[1]);		/* Se existir adiciona ? quantidade do produto na loja a quantidade que foi dada no input */
	}
	else
	{
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", atoi(dadosdoinput[0]));
	}
	
}
/* Esta fun??o principal cria uma nova encomenda */

void criaencomenda()  /* comando N */
{
	int i = 0;
	int a = 0;
	getchar();
	while (i < MAX_ENCOMENDAS)
	{
		if (encomendas[i].idedaencomenda != -1)		/* Se a encomenda nao existir adiciona um ao a */
			a++; 
		else 
			break;
		i++; 
	}
	encomendas[i].idedaencomenda = a;		/* Cria a nova encomenda com o numero que a ficar que vai sempre aumentando de um em um */
	printf("Nova encomenda %d.\n", a);
}

/* Esta fun??o principal recebe um indice de uma encomenda, um indice de um produto e uma quantidade desse produto e adiciona a quantidade de produto a essa encomenda, em que se o produto j? estiver na encomenda adiciona quantidade e que d? erros se a encomenda n?o existir, 
se o produto n?o existir, se a quantidade dada no input for maior do que a que existe no stock da loja, ou se o peso da encomenda exceder os 200 */ 

void addqtdprodutoaencomenda()  /* comando A */
{
	int i;
	char linha[MAX], dadosdoinput[MAX_CARACTERISTICAS][MAX];
	getchar();		/* Eliminar o espa?o que vem a seguir ao comando */
	lerlinha(linha);		/* L? a linha do input */
	separarstring(linha, dadosdoinput);		/* Separa a string em dados separados sendo possivel aceder ao indice a partir do dadosdoinput[] */
	if (encomendas[atoi(dadosdoinput[0])].idedaencomenda != -1)		/* Testa se a encomenda existe ou n?o */
	{
		if (loja[atoi(dadosdoinput[1])]. idedoproduto != -1)		/* Testa se o produto existe ou n?o */
		{
			if (loja[atoi(dadosdoinput[1])].qtddoproduto >= atoi(dadosdoinput[2]))		/* Testa que a quantidade existente na loja ? superior ou igual a quantidade dada no input */
			{
				if (atoi(dadosdoinput[2]) * loja[atoi(dadosdoinput[1])].pesodoproduto + encomendas[atoi(dadosdoinput[0])].pesodaencomenda <= MAX_PESO)		/* Testa se a quantidade dada vezes o peso do produto mais o peso da encomenda onde esta inserido da maior que 200 */
				{
					for (i = 0 ; i < MAX_PESO; i++)		/* Este for percorre os indices do produto na encomenda */
					{	
						if (encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0] == atoi(dadosdoinput[1]))		/* Testa se algum dos indices da encomenda ? igual ao dado no input, ou seja se o produto j? est? inserido na encomenda */
						{
							encomendas[atoi(dadosdoinput[0])].infoencomenda[i][1] += atoi(dadosdoinput[2]);		/* Como o produto j? est? na encomenda soma-se ? quantidade que j? l? estava */
							loja[atoi(dadosdoinput[1])].qtddoproduto -= atoi(dadosdoinput[2]);			/* Como se adicionou a quantidade ? encomenda retira-se ao stock da loja */
							encomendas[atoi(dadosdoinput[0])].pesodaencomenda += atoi(dadosdoinput[2]) * loja[atoi(dadosdoinput[1])].pesodoproduto;		/* E atualiza-se o peso da encomenda que j? se sabe que n?o passa os 200 */
							break;
						}		
					else if (encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0] == -1)		/* Se ainda n?o esta na encomenda testa-se se ? produto criando assim um novo indice para ele na encomenda */
						{
							encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0] = atoi(dadosdoinput[1]);		/* O indice do produto na encomenda correspondente ao que ? dado no input */ 
							encomendas[atoi(dadosdoinput[0])].infoencomenda[i][1] = atoi(dadosdoinput[2]);		/* A indice da quantidade no infoencomenda corresponde ? quantidade que ? dado no input */
							loja[atoi(dadosdoinput[1])].qtddoproduto -= atoi(dadosdoinput[2]);		/* Como se adicionou a quantidade ? encomenda retira-se ao stock da loja como se fez acima */	
							encomendas[atoi(dadosdoinput[0])].pesodaencomenda += atoi(dadosdoinput[2]) * loja[atoi(dadosdoinput[1])].pesodoproduto;		/* E atualiza-se o peso da encomenda que j? se sabe que n?o passa os 200 como se fez acima */
							break;
						}
					}		 	
				}
				else
				{
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", atoi(dadosdoinput[1]), atoi(dadosdoinput[0]));
				}	
			}
			else
			{
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", atoi(dadosdoinput[1]), atoi(dadosdoinput[0]));
			}
		}
		else
		{
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", atoi(dadosdoinput[1]), atoi(dadosdoinput[0]));	
		}
	}
	else
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", atoi(dadosdoinput[1]), atoi(dadosdoinput[0]));
	}
}	

/* Esta fun??o principal recebe no input um indice de um produto e uma quantidade e remove essa quantidade no stock desse produto e da erro se o produto nao existir ou se o produto nao tiver stock suficiente para remover */

void removestock()  /* comando r */
{
	char linha[MAX], dadosdoinput[MAX_CARACTERISTICAS][MAX];
	getchar();		/* Eliminar o espa?o que vem a seguir ao comando */
	lerlinha(linha);		/* L? a linha do input */
	separarstring(linha, dadosdoinput);		/* Separa a string em dados separados sendo possivel aceder ao indice a partir do dadosdoinput[] */
	if (loja[atoi(dadosdoinput[0])].idedoproduto != -1)		/* Testa se o produto dado ? um produto */
	{
		if (loja[atoi(dadosdoinput[0])].qtddoproduto >= atoi(dadosdoinput[1]))		/* Testa se a quantidade for maior ou igual ? quantidade que ? dada no input pode se remover o produto do stock */ 
		{
			loja[atoi(dadosdoinput[0])].qtddoproduto -= atoi(dadosdoinput[1]);		/* Remove o produto */
		}
		else
		{
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", atoi(dadosdoinput[1]), atoi(dadosdoinput[0]));
		}
	}
	else
	{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", atoi(dadosdoinput[0]));
	}
}

/* Esta funcao principal recebe um indice de uma encomenda e de um produto e remove esse produto dessa encomenda e da erro se nem a encomenda nem o produto existirem */

void removeprodutodaencomenda()  /* comando R */
{
	int i, quantidade, indice;
	char linha[MAX], dadosdoinput[MAX_CARACTERISTICAS][MAX];
	getchar();		/* Eliminar o espa?o que vem a seguir ao comando */
	lerlinha(linha);		/* L? a linha do input */
	separarstring(linha, dadosdoinput);		/* Separa a string em dados separados sendo possivel aceder ao indice a partir do dadosdoinput[] */
	if (encomendas[atoi(dadosdoinput[0])].idedaencomenda != -1)		/* Testa se a ecnomenda existe */
	{
		if (loja[atoi(dadosdoinput[1])].idedoproduto != -1)		/* Testa se o produto existe */
		{
			for (i = 0; i < MAX_PESO; i++)		/* Este for percorre todos os indices de produtos existentes na encomenda */
			{
				if (encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0] == atoi(dadosdoinput[1]))		/* Testa se algum dos indices ? igual ao indice dado no input */ 
				{
					quantidade = encomendas[atoi(dadosdoinput[0])].infoencomenda[i][1];		/* A quantidade ? o indice um do MAX_IDENCOMENDA */
					indice = encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0];		/* O indice do produto ? o indice 0 do MAX_IDENCOMENDA */
					encomendas[atoi(dadosdoinput[0])].infoencomenda[i][1] = 0;		/* A quantidade do produto passa a zero pois vai ser removido da empresa */
					encomendas[atoi(dadosdoinput[0])].pesodaencomenda -= quantidade * loja[atoi(dadosdoinput[1])].pesodoproduto; /* Atualiza??o do peso quando ? retirado o produto da encomenda */
					loja[indice].qtddoproduto += quantidade;		/* Como o produto foi removido da encomenda vai ser adicionada a sua quantidade ao stock da loja */
				}	
			}
		}
		else
		{
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", atoi(dadosdoinput[1]), atoi(dadosdoinput[0]));
		}
	}
	else
	{
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", atoi(dadosdoinput[1]), atoi(dadosdoinput[0]));
	}

}

/* Esta fun??o principal recebe um indice de uma encomenda e calcula o seu custo e d? erro se a ecnomenda n?o existir */

void custoencomenda()  /* comando C */
{
	int i, indice, quantidade, custo = 0;
	char linha[MAX], dadosdoinput[MAX_CARACTERISTICAS][MAX];
	getchar();		/* Eliminar o espa?o que vem a seguir ao comando */
	lerlinha(linha);		/* L? a linha do input */
	separarstring(linha, dadosdoinput);		/* Separa a string em dados separados sendo possivel aceder ao indice a partir do dadosdoinput[] */
	if (encomendas[atoi(dadosdoinput[0])].idedaencomenda != -1)
	{
		for (i = 0; i < MAX_PESO; i++)		/* O for percorre os indices dos produtos nas encomendas */
		{
			if (encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0] != -1)		/* Testa se por cada indice i que vai aumentando 1 a 1 se o produto existe na encomenda */
			{
				indice = encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0];		/* O indice do produto ? o ?ndice 0 do MAX_IDENCOMENDA por cada produto encontrado */
				quantidade = encomendas[atoi(dadosdoinput[0])].infoencomenda[i][1];		/* A quantidade do produto na encomenda ? o ?ndice 1 do MAX_IDENCOMENDA por cada produto encontrado */
				custo += loja[indice].precodoproduto * quantidade;		/* Encontrado o preco do produto na loja com o cada indice encontrado, multiplica-se pela sua quantidade na encomenda e soma-se sempre ao custo que ? uma vari?vel inicializada a 0 */		
			}
		}
		printf("Custo da encomenda %d %d.\n", atoi(dadosdoinput[0]), custo);	
	}
	else
	{
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", atoi(dadosdoinput[0]));
	}
}

/* Fun??o principal que recebe um ?ndice de um produto e um pre?o e altera o pre?o desse produto para o pre?o dado e d? erro se o produto n?o existir */

void alteraprecodoproduto()  /* comando p */
{
	char linha[MAX], dadosdoinput[MAX_CARACTERISTICAS][MAX];
	getchar();		/* Eliminar o espa?o que vem a seguir ao comando */
	lerlinha(linha);		/* L? a linha do input */
	separarstring(linha, dadosdoinput);		/* Separa a string em dados separados sendo possivel aceder ao indice a partir do dadosdoinput[] */
	if (loja[atoi(dadosdoinput[0])].idedoproduto != -1)		/* Testa se o produto existe */
	{
		loja[atoi(dadosdoinput[0])].precodoproduto = atoi(dadosdoinput[1]);		/* Altera o pre?o do produto para o pre?o dado no input */
	}
	else
	{
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", atoi(dadosdoinput[0]));	
	}
}	
	

/* Fun??o principal que recebe um indice de uma encomenda e um indice de um produto e da print do nome do produto e da quantidade existente na encomenda e d? erro se a encomenda n?o existir ou se o produto n?o existir */

void descqtdprodutonaencomenda()  /* comando E */
{
	int i, quantidade = 0;
	char linha[MAX], dadosdoinput[MAX_CARACTERISTICAS][MAX];
	getchar();		/* Eliminar o espa?o que vem a seguir ao comando */
	lerlinha(linha);		/* L? a linha do input */
	separarstring(linha, dadosdoinput);		/* Separa a string em dados separados sendo possivel aceder ao indice a partir do dadosdoinput[] */
	if (encomendas[atoi(dadosdoinput[0])].idedaencomenda != -1)		/* Verifica se a encomenda dada existe */
	{
		if (loja[atoi(dadosdoinput[1])].idedoproduto != -1)		/* Verifica se o produto dado existe */
		{
			for (i = 0; i < MAX_PESO; i++)		/* Este for corre todos os indices do produto dentro da encomenda */
			{
				if (encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0] == atoi(dadosdoinput[1]))		/* Testa se algum dos indices que o for correu ? igual ao ?ndice do produto dado no input */
				{
					quantidade += encomendas[atoi(dadosdoinput[0])].infoencomenda[i][1];		/* A quantidade ? igual ao indice 1 do MAX_IDENCOMENDA que ? a quantidade do produto na encomenda, a variavel foi feita so para simplificar no print */
				}				
			}
			printf("%s %d.\n", loja[atoi(dadosdoinput[1])].nomedoproduto, quantidade);			
		}
		else
		{
			printf("Impossivel listar produto %d. Produto inexistente.\n", atoi(dadosdoinput[1]));	
		}
	}
	else
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(dadosdoinput[0]));	
	}
}

/* Fun??o principal que recebe um indice de um produto e e lista o identificador da encomenda, o indice do produto e a sua quantidade na encomenda e d? erro se o produto n?o existir */ 

int encomendacommaisproduto()  /* comando m */
{
	int i, j, qtdmax = 0, idedaencomendacomqtdmax;
	char linha[MAX], dadosdoinput[MAX_CARACTERISTICAS][MAX];
	getchar();		/* Eliminar o espa?o que vem a seguir ao comando */
	lerlinha(linha);		/* L? a linha do input */
	separarstring(linha, dadosdoinput);		/* Separa a string en dados separados sendo possivel aceder ao indice a partir do dadosdoinput[] */
	if (loja[atoi(dadosdoinput[0])].idedoproduto != -1)		/* Testa se o ?ndice do produto dado no input existe na loja */
	{
		for (i = 0; i < MAX_ENCOMENDAS; i++)		/* Este for percorre os indices da encomendas */
		{
			if (encomendas[i].idedaencomenda != -1)		/* Testa se a encomenda existe */
			{
				for (j = 0; j < MAX_PESO; j++)		/* Este for percorre todos os indices dos produtos dentro da encomenda */
				{
					if (encomendas[i].infoencomenda[j][0] == atoi(dadosdoinput[0]) && qtdmax < encomendas[i].infoencomenda[j][1])		/* Testa em que encomendas e que existe o produto dado no input, e em que a sua quantidade seja maior que uma variavel qtdmax inicializada a 0, pois se o produto for encontrado numa encomenda mas a qtd ? menor j? nao vale a pena test?-lo */
					{
						qtdmax = encomendas[i].infoencomenda[j][1];		/* A vari?vel qtd m?xima vai sendo atualizada pela que lhe ? maior pois quando ? menor j? nem ? testado */
						idedaencomendacomqtdmax = encomendas[i].idedaencomenda;		/* E sempre que ? encontrado uma encomenda o produto dado no input em maior quantidade, a variavel idedaencomendacomqtdmax guarda o id dessa encomenda */
					}
				}
			}
			else
				break;		/* Como n?o h? erro se a encomenda n?o existir acaba o programa, para poupar tempo em vez ler todas as encomendas */
		}
		if (qtdmax != 0)		/* Testa se n?o houver nenhum produto com quantidade maior que 0 tambem n?o h? nenuma encomenda com produto em quantidade m?xima logo a fun??o termina sen?o da print */
		{
			printf("Maximo produto %d %d %d.\n", atoi(dadosdoinput[0]), idedaencomendacomqtdmax, qtdmax);
		}
	}
	else
	{
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", atoi(dadosdoinput[0]));
	}
	return 0;	
}

/* Fun??o principal que lista todos os produtos por ordem crescente de pre?o e se houver produtos com o mesmo pre?o ? devolvido o que t?m menor id primeiro, ou seja, tem que ser est?vel */

void ordemdeprodutos()  /* comando l */ 
{
	int tabela_indices[MAX_PRODUTOS], r = 0, i, j;
	for (i = 0; i < MAX_PRODUTOS; i++)
	{
		if (loja[i].idedoproduto != -1)		/* Este for percorre todos os produtos dentro da loja */
		{
			tabela_indices[i] = loja[i].idedoproduto;		/* Adciona ? tabela os ?ndices dos produtos na loja */
			r++;		/* Adiciona ? vari?vel r que vai ser o limite do lado direito do algoritmo de ordena??o merge */
		}
		else
			break;	
	}
	mergesort(tabela_indices, 0, r - 1, 0);		/* Fun??o auxiliar que organiza com o algortimo merge todos os produtos de acordo com os que est?o inserido na tabela que s?o todos pelo que foi feito dentro do if */
	printf("Produtos\n");
	for (j = 0; j < r; j++)		/* Este for serve para ir dando print de todos os produtos que est?o inseridos na tabela de indices pela ordem desejada de caracteristica, nome, preco, quantidade */ 
	{
		printf("* %s %d %d\n", loja[tabela_indices[j]].nomedoproduto, loja[tabela_indices[j]].precodoproduto, loja[tabela_indices[j]].qtddoproduto);
	}


}

/* Fun??o principal que recebe um ?ndice de uma encomenda e ordena os seus produtos por ordem alfab?tica de nome e d? erro se a encomenda n?o existir */

void ordemalfabeticadeprodnumaencomenda()  /* comando L */
{	
	int tabela_idpnaencomenda[MAX_PESO], r = 0, i, j;
	char linha[MAX], dadosdoinput[MAX_CARACTERISTICAS][MAX];
	getchar();		/* Eliminar o espa?o que vem a seguir ao comando */
	lerlinha(linha);		/* L? a linha do input */
	separarstring(linha, dadosdoinput);		/* Separa a string en dados separados sendo possivel aceder ao indice a partir do dadosdoinput[] */
	if (encomendas[atoi(dadosdoinput[0])].idedaencomenda != -1)		/* Testa se a encomenda existe */
	{	
		for (i = 0; i < MAX_PESO; i++)		/* Este for percorre todos os indices de produtos na encomenda */
		{
			if (encomendas[atoi(dadosdoinput[0])].infoencomenda[i][0] != -1 && encomendas[atoi(dadosdoinput[0])].infoencomenda[i][1] > 0)		/* Testa se o ?ndice do produto existir e se a sua quantidade ? maior que 0 */
			{
				tabela_idpnaencomenda[r] = i;		/* Adiciona-se esse indice ? tabela principal que vai ser usado no algoritmo do merge */
				r++;		
			}
			else
				break;	
		}
		mergesort(tabela_idpnaencomenda, 0, r - 1, 1);		/* Efetua o algoritmo de ordena??o */
		printf("Encomenda %d\n", atoi(dadosdoinput[0]));
		for (j = 0; j < r; j++)		/* Este for percorre todos os indices guardados dessa tabela e vai dando print do nome, preco, quantidade desse produto que j? foi ordenado alfabeticamente pelo mergesort que usou a parte alfabetica do merge*/
		{
			printf("* %s %d %d\n", loja[tabela_idpnaencomenda[j]].nomedoproduto, loja[tabela_idpnaencomenda[j]].precodoproduto, encomendas[atoi(dadosdoinput[0])].infoencomenda[tabela_idpnaencomenda[j]][1]);			
		}
	}
	else
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(dadosdoinput[0]));
	}


}

/* Fun??o main ? a fun??o que 'decide tudo', oou seja ? a fun??o que d? run ao projeto em que sempre que a vari?vel run est? a 1 o programa corre e quando passa a 0 para de correr. 
Nesta fun??o inicializa-se o que ? necess?rio a -1 e escolhe qual comando ? que ? para fazer atrav?s do comando switch */

int main()
{
	int i, j, k, command, run = 1;
	for (i = 0; i < MAX_PRODUTOS; i++)		/* Este for percorre todos os produtos da loja */
	{
		loja[i].idedoproduto = -1;		/* Inicializa??o dos indices dos produtos da loja a -1 */							
	}
	for (j = 0; j < MAX_ENCOMENDAS; j++)		/* Este for percorre todas as encomendas */
	{
		encomendas[j].pesodaencomenda = 0;		/* Inicializa??o do peso de cada encomenda a 0 */
		encomendas[j].idedaencomenda = -1;		/* Inicializa??o do indice da encomenda a -1 */
		
		for (k = 0; k < MAX_PESO; k++)		/* Este for percorre os indices dod produtos dentro das encomendas */
		{
			encomendas[j].infoencomenda[k][0] = -1;		/* Inicializa??o dos indices dos produtos dentro da encomenda a -1 */
		}
	}	
	while (run)
	{
		command = getchar();
		switch (command)		/* Como o command ? getchar o switch testa cada primeira letra do input para saber qual comando deve usar em que cada comando est? associado a uma fun??o *em que se fo x a vari?vel run passa a 0 ou seja acaba o programa */
		{
			case 'a':		
				addproduto();
				break;
			case 'q':
				addstock();
				break;
			case 'N':
				criaencomenda();
				break;
			case 'A':
				addqtdprodutoaencomenda();
				break;
			case 'r':
				removestock();
				break;
			case 'R':
				removeprodutodaencomenda();
				break;
			case 'C':
				custoencomenda();
				break;
			case 'p':
				alteraprecodoproduto();
				break;
			case 'E':
				descqtdprodutonaencomenda();
				break;
			case 'm':
				encomendacommaisproduto();
				break;
			case 'l':
				ordemdeprodutos();
				break;
			case 'L':
				ordemalfabeticadeprodnumaencomenda();
				break;
			case 'x':
				run = 0;
				break;  
				
		}
	}	
	return 0;
}