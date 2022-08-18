#include <stdio.h>
#include <string.h>

#define MAX_CHAR 63 /* numero maximo de carateres da descricao de um produto */
#define MAX_PROD 10000 /* numero maximo de produtos no sistema */
#define MAX_ENCO 500 /* numero maximo de encomendas no sistema */
#define MAX_PESO 200 /* peso maximo de uma encomenda */
#define ZERO 0
#define UM 1


#define key(A) (A)
#define less(A,B) (key(A)<key(B))
#define exch_int(A,B) {int t=A;A=B;B=t;}
#define exch_char(A,B) {char t=A;A=B;B=t;}

/* definicao de uma estrutura para o produto */

typedef struct 
{
	int id;  /* identificador */
	char desc[MAX_CHAR]; /* descricao */
	int preco; 
	int peso;
	int qtd_stock; /* quantidade em stock */

}produto;



/* definicao de uma estrutura para as encomendas */

typedef struct 
{
	int ide;
	int peso_total;
	int custo;
	produto produtos[MAX_PROD];
	/* vetor que contem bits de controlo. Se o produto pertencer a encomenda, entao o indice
	com o valor do seu id tem o valor 1, caso contrario permanece a 0.*/
	int produtos_in[MAX_PROD]; 

}encomenda;



/* definicao de uma estrutura para o sistema de logistica */

typedef struct 
{
	produto produtos[MAX_PROD];
	encomenda encomendas[MAX_ENCO];

}sis_log;





/* variavel que serve como contador dos produtos do sistema.E incrementada
a medida que vao sendo adicionados produtos ao sistema.*/
static int i_produtos; 

/* variavel que serve como contador das ecomendas do sistema. E incrementada
a medida que vao sendo adicionadas encomendas ao sistema. */
static int i_encomendas; 


/* variavel global que vai armazenar os dados de todo o sistema */
sis_log sistema; 


/* comandos principais */
void comando_a();
void comando_q();
void comando_N();
void comando_A();
void comando_r();
void comando_R();
void comando_C();
void comando_p();
void comando_E();


void comando_m();
void comando_l();
void comando_L();


/* comandos auxiliares */
void merge_sort(int vetor[],int esquerda, int direita);
void merge(int vetor[],int esquerda, int m, int direita);
void merge_sort_desc(int vetor[],int esquerda,int direita);
void merge_desc(int vetor[],int esquerda, int m, int direita);




int main()
{
	char primeira_letra; /* primeira letra dada como input */
	scanf("%c",&primeira_letra);


	while (primeira_letra != 'x')
	{
		/* corre o codigo de acordo com a primeira letra fornecida como input.
		A funcao 'getchar()' e usada para ler o carater ' ' que separa a letra inicial 
		e o resto do input e '\n' que se encontra no fim do output dado pelos comandos, 
		passando assim para a linha seguinte, que vai ser lida pela funcao 'scanf()'.*/
		switch (primeira_letra)
		{
			case 'a':
				getchar();
				comando_a();
				getchar();
				break;
		
			case 'q':
				getchar();
				comando_q();
				getchar();
				break;

			case 'N':
				comando_N();
				getchar();
				break;

			case 'A':
				getchar();
				comando_A();
				getchar();
				break;

			case 'r':
				getchar();
				comando_r();
				getchar();
				break;

			case 'R':
				getchar();
				comando_R();
				getchar();
				break;

			case 'C':
				getchar();
				comando_C();
				getchar();
				break;
			
			case 'p':
				getchar();
				comando_p();
				getchar();
				break;

			case 'E':
				getchar();
				comando_E();
				getchar();
				break;

			case 'm':
				getchar();
				comando_m();
				getchar();
				break;

			case 'l':
				comando_l();
				getchar();
				break;

			case 'L':
				getchar();
				comando_L();
				getchar();
				break;

		}
		
		scanf("%c",&primeira_letra);
	
	}
	return 0;
}


/* comando principal que adiciona um novo produto ao sistema */

void comando_a()
{
	produto prod;
	

	scanf("%[^:]:%d:%d:%d",prod.desc,&prod.preco,&prod.peso,&prod.qtd_stock);
	/* o identificador do produto e dado pela variavel estatica */
	prod.id=i_produtos;
	
	/* o produto e adicionado ao sistema */
	sistema.produtos[prod.id].id=prod.id;
	strcpy(sistema.produtos[prod.id].desc,prod.desc);
	sistema.produtos[prod.id].preco=prod.preco;
	sistema.produtos[prod.id].peso=prod.peso;
	sistema.produtos[prod.id].qtd_stock=prod.qtd_stock;
	
	printf("Novo produto %d.\n",prod.id);
	/* a variavel estatica e incrementada pois foi adicionado um novo produto 
	ao sistema */
	i_produtos++;

}


/* comando que adiciona stock a um produto existente no sistema */

void comando_q()
{
	produto prod;
	scanf("%d:%d",&prod.id,&prod.qtd_stock);
	
	/* se o identificador do produto dado pelo input for igual ou superior ao contador do
	numero de produtos que o sistema possui, entao esse produto nao existe. */
	if (prod.id >= i_produtos)
	{
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",prod.id);
	}
	else
	{	
		sistema.produtos[prod.id].qtd_stock+=prod.qtd_stock;
	}

}

/* comando que cria uma nova encomenda */

void comando_N()
{
	printf("Nova encomenda %d.\n",i_encomendas);
	i_encomendas++;
}


/* comando que adiciona um produto a uma encomenda, sendo que se o produto ja existir na encomenda
adiciona a nova quantidade a quantidade existente. */

void comando_A()
{
	produto prod;
	encomenda enco;
	
	scanf("%d:%d:%d",&enco.ide,&prod.id,&prod.qtd_stock);
	
	if (prod.id>=i_produtos)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",prod.id,enco.ide);
	}
	
	/* Se o identificador da encomenda for superior ao contador do numero de encomendas, entao esta nao
	existe. */
	else if (enco.ide>=i_encomendas)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",prod.id,enco.ide);
	}
	
	/* Se o stock do produto que se quer adicionar a encomenda for superior ao que existe no sistema, este
	nao pode ser adicionado a encomenda. */
	else if (prod.qtd_stock>sistema.produtos[prod.id].qtd_stock)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",prod.id,enco.ide);
	}
	
	/* Testa se a soma do peso do produto que vai ser adicionado com o peso preio da encomenda excede
	o peso maximo. */
	else if((sistema.produtos[prod.id].peso)*(prod.qtd_stock) + sistema.encomendas[enco.ide].peso_total > MAX_PESO)
	{
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",prod.id,enco.ide);
	}
	else 
	{
		/*Apenas se alteram os parametros do peso total da encomenda e do stock do produto, visto que
		os outros ja tinham sido adicionados.*/
		if (sistema.encomendas[enco.ide].produtos_in[prod.id])
		{
			sistema.encomendas[enco.ide].peso_total+=((prod.qtd_stock)*(sistema.produtos[prod.id].peso));
			
			sistema.encomendas[enco.ide].produtos[prod.id].qtd_stock+=prod.qtd_stock;
			
			sistema.produtos[prod.id].qtd_stock-=prod.qtd_stock;

		}
		/* Caso contrario, adiciona-se o novo produto a encomenda e retira-se o seu stock ao sistema. */
		else
		{	
			sistema.encomendas[enco.ide].produtos[prod.id].id = sistema.produtos[prod.id].id;
			strcpy(sistema.encomendas[enco.ide].produtos[prod.id].desc,sistema.produtos[prod.id].desc);
			sistema.encomendas[enco.ide].produtos[prod.id].preco = sistema.produtos[prod.id].preco;
			sistema.encomendas[enco.ide].produtos[prod.id].peso = sistema.produtos[prod.id].peso;
			/*apenas se adiciona o stock dado pelo input */
			sistema.encomendas[enco.ide].produtos[prod.id].qtd_stock = prod.qtd_stock;
			
			sistema.encomendas[enco.ide].peso_total += ((prod.qtd_stock)*(sistema.produtos[prod.id].peso));
			sistema.produtos[prod.id].qtd_stock -= prod.qtd_stock;
			/* adiciono o produto a encomenda atraves do bit de conrolo */
			sistema.encomendas[enco.ide].produtos_in[prod.id] = UM;
			
			
		}
	}	
}



/* comando que remove stock a um produto existente */

void comando_r()
{
	produto prod;

	scanf("%d:%d",&prod.id,&prod.qtd_stock);

	/* testa se o identificador do produto e superior a do contador do numero de produtos. Se for esse o caso
	o produto nao existe */
	if (prod.id>=i_produtos)
	{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n",prod.id);
	}
	
	/* testa se a quantidade do produto dada pelo input e superior a que existe no sistema.*/
	else if (prod.qtd_stock>sistema.produtos[prod.id].qtd_stock)
	{
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",prod.qtd_stock,prod.id);
	}
	else 
	{
		/* e subtraida a quantidade dada como input a quantidade de produto no sistema */
		sistema.produtos[prod.id].qtd_stock-=prod.qtd_stock;
	}
}


/* comando que remove um produto de uma encomenda */
void comando_R()
{
	produto prod;
	encomenda enco;
	
	scanf("%d:%d",&enco.ide,&prod.id);

	if (enco.ide>=i_encomendas)
	{
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",prod.id,enco.ide);
	}
	else if (prod.id>=i_produtos)
	{
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",prod.id,enco.ide);
	}
	
	/*Garante que o produto se encontra na encomenda */
	else if (sistema.encomendas[enco.ide].produtos_in[prod.id])
	{
		/*Subtrai ao peso total da encomenda o peso do produto que foi removido*/
		sistema.encomendas[enco.ide].peso_total-=((sistema.encomendas[enco.ide].produtos[prod.id].peso)*
		(sistema.encomendas[enco.ide].produtos[prod.id].qtd_stock));
		
		/*Devolve o stock do produto que estava na encomenda ao sistema */
		sistema.produtos[prod.id].qtd_stock += sistema.encomendas[enco.ide].produtos[prod.id].qtd_stock;

		/*Remove o produto da encomenda */
		sistema.encomendas[enco.ide].produtos_in[prod.id]=ZERO;
	}

}


void comando_C()
{
	encomenda enco;
	int i;

	scanf("%d",&enco.ide);
	sistema.encomendas[enco.ide].custo=0;

	if (enco.ide>=i_encomendas)
	{
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",enco.ide);
	}
	else
	{	/*Ciclo que percorre todos os produtos da encomenda cujo ide foi fornecido como input e 
	calcula o preco da encomenda somando o custo do produto ao custo total da encomenda.*/
		for(i=ZERO;i<i_produtos;i++)
		{
			
			if(sistema.encomendas[enco.ide].produtos_in[i])
			{
				/* o custo de cada produto e calculado multiplicando o seu preco pela sua quantidade 
				em stock na encomenda */
				sistema.encomendas[enco.ide].custo+=(sistema.encomendas[enco.ide].produtos[i].preco)*
				(sistema.encomendas[enco.ide].produtos[i].qtd_stock);
			}
		}

		printf("Custo da encomenda %d %d.\n",enco.ide,sistema.encomendas[enco.ide].custo);
	}


}


/* comando que altera o preco de um produto existente no sistema */

void comando_p()
{
	produto prod;
	int i;

	scanf("%d:%d",&prod.id,&prod.preco);

	if (prod.id>=i_produtos)
	{
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",prod.id);
	}
	else
	{
		/* o preco do produto no sistema passa a ser o valor que e dado como input. */
		sistema.produtos[prod.id].preco = prod.preco;
		for(i=ZERO;i<i_encomendas;i++)
		{
			/*Altera o preco nas encomendas em que o produto esta. */
			if(sistema.encomendas[i].produtos_in[prod.id])
			{
				sistema.encomendas[i].produtos[prod.id].preco=prod.preco;
			}
		}
	}
}

/* Comando que lista a descri??o e a quantidade de um produto numa encomenda*/

void comando_E()
{
	encomenda enco;
	produto prod;
	

	scanf("%d:%d",&enco.ide,&prod.id);

	if (enco.ide>=i_encomendas)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",enco.ide);
	}
	else if (prod.id>=i_produtos)
	{
		printf("Impossivel listar produto %d. Produto inexistente.\n",prod.id);
	}
	else
	{	/*Se o produto estiver contido na encomenda imprime a sua descricao e a sua quatidade de stock.*/
		if(sistema.encomendas[enco.ide].produtos_in[prod.id])
		{
			printf("%s %d.\n",sistema.encomendas[enco.ide].produtos[prod.id].desc,
				sistema.encomendas[enco.ide].produtos[prod.id].qtd_stock);
		}
		/*Caso contrario este nao pertence a encomenda, logo o seu stock na encomenda vai ser nulo. */
		else
		{
			printf("%s %d.\n",sistema.produtos[prod.id].desc,ZERO);
		}
		
	}

}

/*Comando que lista o identificador da encomenda em que o produto dado ocorre mais vezes.*/
void comando_m()
{
	
	int i;
	/*variavel que serve como controlo que verifica se o produto dado como input existe em alguma 
	encomenda. */
	int controlo=ZERO;
	
	/*variavel que representa a quantidade de stock do produto da encomenda com o
	maior stock desse produto. */
	int qtd_maior=ZERO; 
	produto prod;
	
	/* Representa a encomenda com o maior stock do produto cujo id foi introduzido como input */
	encomenda enco_prod_maior;
	
	scanf("%d",&prod.id);

	if(prod.id>=i_produtos)
	{
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",prod.id);
	}
	/*Verifica se existem ou nao encomendas*/
	else if(i_encomendas<UM)
	{
		return;
	}
	else
	{
		/*Ciclo que percorre todas as encomendas.*/
		for (i=ZERO;i<i_encomendas;i++)
	
		{	/*Verifica se o produto esta na encomenda*/
			if(sistema.encomendas[i].produtos_in[prod.id])
			{
				/*Confirma que o produto esta em pelo menos uma encomenda.*/
				controlo=UM;
				/*Se o stock do produto for maior nesta encomenda for maior do que o 'maior',
				entao o 'maior' passa a ser esse stock. E a encomenda desejada passa a ser essa. */
				if (sistema.encomendas[i].produtos[prod.id].qtd_stock>qtd_maior)
				{
					enco_prod_maior.ide=i;
					qtd_maior=sistema.encomendas[i].produtos[prod.id].qtd_stock;
				}
			}
		}
		if(controlo)
		{
			printf("Maximo produto %d %d %d.\n",prod.id,enco_prod_maior.ide,qtd_maior);
		}
		
	}

}

/*comando que lista todos os produtos existentes no sistema por ordem crescente de pre?o.*/

void comando_l()
{	/*'contador' e uma variavel que contem o comprimento do vetor 'vetor_indices'. */
	int i,contador=ZERO;
	/*Vetor que contem os indices de todos os produtos do sistema.*/
	int vetor_indices[MAX_PROD];
	
	
	for (i=ZERO;i<i_produtos;i++)
	{
		/*Os indices dos produtos sao adicionados ao vetor_indices.*/
		vetor_indices[i]=i;
		contador++;
	}
	/*O vetor_indices e ordenado segundo o preco dos produtos do sistema.*/
	merge_sort(vetor_indices,ZERO,contador-UM);

	printf("Produtos\n");

	for(i=ZERO;i<contador;i++)
	{
		printf("* %s %d %d\n",sistema.produtos[vetor_indices[i]].desc,sistema.produtos[vetor_indices[i]].preco,
					sistema.produtos[vetor_indices[i]].qtd_stock);
	}
}


/*comando que lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o. */

void comando_L()
{
	encomenda enco;
	/*'contador' guarda o comprimento do vetor 'vetor_indices'.*/
	int i,contador=ZERO;
	/*Vetor que contem todos os indices dos produtos que estao contidos na encomenda cujo ide e dado
	como input.*/
	int vetor_indices[MAX_PROD];
	
	scanf("%d",&enco.ide);

	if (enco.ide >= i_encomendas)
	{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",enco.ide);
	}
	else
	{
		for(i=ZERO;i<i_produtos;i++)
		{
			/*Apenas adiciona ao vetor 'vetor_indices' os indices dos produtos contidos na encomenda.*/
			if(sistema.encomendas[enco.ide].produtos_in[i])
			{
				vetor_indices[contador]=i;
				contador++;
			}
		}
		
		/*O vetor 'vetor_indices' e ordenado de acordo com as descricoes dos produtos da encomenda. */
		merge_sort_desc(vetor_indices,ZERO,contador-UM);
		
		printf("Encomenda %d\n",enco.ide);
		for (i=ZERO;i<contador;i++)
		{
			printf("* %s %d %d\n",sistema.encomendas[enco.ide].produtos[vetor_indices[i]].desc,sistema.encomendas[enco.ide].produtos[vetor_indices[i]].preco,
						sistema.encomendas[enco.ide].produtos[vetor_indices[i]].qtd_stock);
				
		}
	}


}


/*Funcao de ordenacao que ordena os produtos do sistema por ordem crescente do seu preco. */

void merge_sort(int vetor[],int esquerda, int direita)
{
	int m = (direita+esquerda)/(UM+UM);

	if(direita <= esquerda)
	{
		return;
	}
	merge_sort(vetor,esquerda,m);
	merge_sort(vetor,m+UM,direita);
	merge(vetor,esquerda,m,direita);

}
		

void merge_sort_desc(int vetor[],int esquerda,int direita)
{
	int m=(direita+esquerda)/(UM + UM);

	if(direita<=esquerda)
	{
		return;
	}
	merge_sort_desc(vetor,esquerda,m);
	merge_sort_desc(vetor,m+UM,direita);
	merge_desc(vetor,esquerda,m,direita);
}





int aux[MAX_PROD];

void merge(int vetor[],int esquerda, int m, int direita)
{
	int i,j,k;
	for(i=m+UM;i>esquerda;i--)
	{
		aux[i-UM]=vetor[i-UM];
	}
	for(j=m;j<direita;j++)
	{
		aux[direita+m-j]=vetor[j+UM];
	}
	for(k=esquerda;k<=direita;k++)
	{
		/*Compara os id's dos produtos cujos precos sao iguais. Desta forma oredena os produtos com os
		precos iguais por ordem crescente de id.*/
		if(less(sistema.produtos[aux[j]].id,sistema.produtos[aux[i]].id)&&
			(sistema.produtos[aux[j]].preco==sistema.produtos[aux[i]].preco))
		{
			vetor[k]=aux[j--];
		}
		/*Compara os precos dos produtos do sistema.*/
		else if(less(sistema.produtos[aux[j]].preco,sistema.produtos[aux[i]].preco))
		{
			vetor[k]=aux[j--];
		}
		else
		{
			vetor[k]=aux[i++];
		}
	}
}


int aux1[MAX_PROD];

void merge_desc(int vetor[],int esquerda, int m, int direita)
{
	int i,j,k;
	for(i=m+UM;i>esquerda;i--)
	{
		aux1[i-UM]=vetor[i-UM];
	}
	for(j=m;j<direita;j++)
	{
		aux1[direita+m-j]=vetor[j+UM];
	}
	for(k=esquerda;k<=direita;k++)
	{   
		/*Compara as descricoes dos produtos do sistema.*/
		if(strcmp(sistema.produtos[aux1[j]].desc,sistema.produtos[aux1[i]].desc)<ZERO)
		{
			vetor[k]=aux1[j--];
		}
		else
		{
			vetor[k]=aux1[i++];
		}
	}
}

























