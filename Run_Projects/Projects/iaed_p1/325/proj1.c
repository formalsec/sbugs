#include <stdio.h>
#include <string.h>
#define MAXPROD 10000 			/* o maximo de produtos no sistema*/
#define MAXENC 500				/* o maximo de encomendas no sistema*/
#define MAXDESCPROD 64			/* tamanho maximo da descricao dos produtos*/
#define MAXPESOENC 200			/* o maximo de peso de uma encomenda*/


struct prod 					/* Estrutura que contem as carateristicas de um produto*/
{
	int id;
	int peso;
	int preco;
	int qtd;
	char desc[MAXDESCPROD];
};

struct enc 						/* Estrutura que contem as carateristicas de uma encomenda*/
{
	struct prod prod_enc[MAXPROD]; /* Array com os produtos na encomenda*/
	int peso_g; 				/* Peso total da encomenda*/
	int cont_produtos; 			/* Contador de produtos na encoemenda */
};

struct enc encomendas[MAXENC];  /* Inicializacao do array com as encomendas todas (max 500) feita fora do main pelo espaco que precisa em memoria*/

/* Funcoes auxiliares de ordenamento*/
void alphasort(char nomes[MAXPROD][MAXDESCPROD], int count)  	/* Ordena alfabticamente uma array de strings (descricoes de produtos)*/
{
	int i, j;
	char temp[MAXDESCPROD]; 
	count--;
	for(i=0;i<=count;i++)										/* Ciclos for que ordenam a array atraves de strcmp*/
	{
      	for(j=i+1;j<=count;j++)
      	{
        	if(strcmp(nomes[i],nomes[j])>0)
        	{
            	strcpy(temp,nomes[i]);
            	strcpy(nomes[i],nomes[j]);
           		strcpy(nomes[j],temp);
        	}
        }
	}
}

void mergesort(int A[], int temp[], int left, int right, struct prod produtos[MAXPROD]) 
{ 																/* Implementacao do mergesort adaptada para este caso especifico*/
  	int mid = (left + right)/2, i, curr;						/* este mergesort ordena uma array com os id dos produtos por preco*/
  	int i1 = left;
  	int i2 = mid + 1;
  	if (left == right) 
  		return;
  	mergesort(A, temp, left, mid, produtos); 
  	mergesort(A, temp, (mid+1), right, produtos); 
  	for (i = left; i <= right; i++) 
    	temp[i] = A[i];
  	for (curr = left; curr <= right; curr++)
  	{
    	if (i1 == mid+1)  
      		A[curr] = temp[i2++];
    	else if (i2 > right)   
      		A[curr] = temp[i1++];
    	else if (produtos[temp[i1]].preco <= produtos[temp[i2]].preco) /* compara os precos para a array de id ficar ordenada por preco*/
      		A[curr] = temp[i1++]; 
    	else
      		A[curr] = temp[i2++]; 
    }   
}

/* Funcoes responsaveis por executar os comandos do utilizador*/
void a(int iden_atual, struct prod produtos[MAXPROD])			/* Funcao responsavel por executar o comando 'a' (adicionar um novo*/
{                      											/* produto ao sistema)*/
	int i=0, prec, peso, qtd;
	char desc[MAXDESCPROD], c;
	getchar();
	while ((c = getchar()) != ':')								/* ciclo para ler do input a descricao*/
	{
		desc[i] = c;
		i++;
	}
	desc[i]= '\0';
	scanf("%d:%d:%d", &prec, &peso, &qtd);
	strcpy(produtos[iden_atual].desc,desc);
	produtos[iden_atual].preco = prec;
	produtos[iden_atual].peso = peso;
	produtos[iden_atual].qtd = qtd;
	produtos[iden_atual].id = iden_atual;
	printf("Novo produto %d.\n", iden_atual);
}

void q(int iden_atual, struct prod produtos[MAXPROD])			/* Funcao responsavel por executar o comando 'q' (adicionar stock a um produto)*/
{
	int id, stck_add;											/* stck_add variavel inteira que contem o stock a adicionar*/
	getchar();
	scanf("%d:%d", &id, &stck_add);
	if(id >= iden_atual)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
	else
		produtos[id].qtd += stck_add;
}
void r(int iden_atual, struct prod produtos[MAXPROD])			/* Funcao responsavel por executar o comando 'r' (retirar stock a um produto)*/
{
	int id, stck_rem;											/* stck_rem variavel inteira que contem o stock a remover*/
	getchar();
	scanf("%d:%d", &id, &stck_rem);
	if(id >= iden_atual)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
	else if ((produtos[id].qtd - stck_rem)<0)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", stck_rem, id);
	else
		produtos[id].qtd -= stck_rem;
}
void p(int enc_atual, int iden_atual, struct prod produtos[MAXPROD], struct enc encomendas[MAXENC])
{																/* Funcao responsavel por executar o comando 'p' (alterar o preco de um produto)*/
	int id, n_prec, e=0, i=0;
	getchar();
	scanf("%d:%d", &id, &n_prec);
	if(id >= iden_atual)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
	else
	{
		produtos[id].preco = n_prec;
		while (e < enc_atual)									/* Ciclos que procuram o produto nas encomendas e a;teram o seu preco tambem nessa estrutura*/
		{
			i = 0;
			while(i < encomendas[e].cont_produtos)
			{
				if (strcmp(encomendas[e].prod_enc[i].desc,produtos[id].desc)==0)
				{
					encomendas[e].prod_enc[i].preco = n_prec;
				}
				i++;
			}
			e++;
		}
	}	

}

void N(int enc_atual)										/* Funcao responsavel por executar o comando 'N' (Criar uma nova encomenda)*/	
{
	printf("Nova encomenda %d.\n", enc_atual);
}

void A(int enc_atual, int iden_atual, struct prod produtos[MAXPROD], struct enc encomendas[MAXENC])
{															/* Funcao responsavel por executar o comando 'A' (adicionar um produto a uma encomenda)*/
	int ide, id, qtd, i=-1, a=0;
	getchar();
	scanf("%d:%d:%d", &ide, &id, &qtd);
	if(ide >= enc_atual)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id, ide);
	else if (id >= iden_atual)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id, ide);
	else if ((produtos[id].qtd - qtd)<0)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id, ide);
	else if ((encomendas[ide].peso_g + (produtos[id].peso*qtd)) > MAXPESOENC)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id, ide);
	else
		{
		while(i < encomendas[ide].cont_produtos)
		{
			i++;
			if (strcmp(encomendas[ide].prod_enc[i].desc,produtos[id].desc)==0)
			{
				a=1;										/* Se a variavel a estiver a 1, o produto ja existe na encomenda*/
				break;
			}
		}

		if (a == 1)											/* como o produto ja existe na encomenda adiciona-se so a quantidade*/
		{
			encomendas[ide].prod_enc[i].qtd += qtd;
			produtos[id].qtd -= qtd;
			encomendas[ide].peso_g+=produtos[id].peso*qtd;

		}
		else
		{
			encomendas[ide].prod_enc[encomendas[ide].cont_produtos].peso = produtos[id].peso;
			encomendas[ide].prod_enc[encomendas[ide].cont_produtos].preco = produtos[id].preco;
			encomendas[ide].prod_enc[encomendas[ide].cont_produtos].qtd = qtd;
			strcpy(encomendas[ide].prod_enc[encomendas[ide].cont_produtos].desc,produtos[id].desc);
			produtos[id].qtd -= qtd;
			encomendas[ide].peso_g+=produtos[id].peso*qtd;
			encomendas[ide].cont_produtos++;
		}
		}
}		

void R(int enc_atual, int iden_atual, struct prod produtos[MAXPROD], struct enc encomendas[MAXENC])
{															/* Funcao responsavel por executar o comando 'R' (remover um produto a uma encomenda)*/
	int ide, i=-1, id;
	getchar();
	scanf("%d:%d", &ide, &id);
	if(ide >= enc_atual)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id, ide);
	else if (id >= iden_atual)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id, ide);
	else
	{
		while(i < encomendas[ide].cont_produtos)
		{
			i++;
			if (strcmp(encomendas[ide].prod_enc[i].desc,produtos[id].desc)==0)
				break;
		}
		produtos[id].qtd += encomendas[ide].prod_enc[i].qtd;
		encomendas[ide].peso_g -= (produtos[id].peso * encomendas[ide].prod_enc[i].qtd); /* Atualizar o peso geral da encomenda qunado o produto e removido*/
		encomendas[ide].prod_enc[i].qtd = 0;
	}
}	

void C(int enc_atual, struct enc encomendas[MAXENC])
{														/* Funcao responsavel por executar o comando 'C' (Listar o custo da encomenda)*/
	int custo=0, ide, i=0;
	getchar();
	scanf("%d", &ide);
	if(ide >= enc_atual)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	else
	{
		while(i < encomendas[ide].cont_produtos)		/* Ciclo que vai por todos os produtos e descobre o custo total*/
		{
			custo+=(encomendas[ide].prod_enc[i].preco*encomendas[ide].prod_enc[i].qtd);
			i++;
		}
		printf("Custo da encomenda %d %d.\n", ide, custo);
	}
}	

void E(int enc_atual, int iden_atual, struct prod produtos[MAXPROD], struct enc encomendas[MAXENC])
{														/* Funcao responsavel por executar o comando 'E ' (listar a descricao e quantidade de um produto numa encomenda)*/
	int ide, i=-1, id, a=0;
	getchar();
	scanf("%d:%d", &ide, &id);
	if(ide >= enc_atual)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else if (id >= iden_atual)
		printf("Impossivel listar produto %d. Produto inexistente.\n", id);
	else
	{
		while(i < encomendas[ide].cont_produtos)
		{
			i++;
			if (strcmp(encomendas[ide].prod_enc[i].desc,produtos[id].desc)==0)
			{
				a = 1;
				break;
			}
		}
		if (a==1)
			printf("%s %d.\n", produtos[id].desc, encomendas[ide].prod_enc[i].qtd);
		else
			printf("%s 0.\n", produtos[id].desc);
	}
}	

void m(int enc_atual, int iden_atual, struct prod produtos[MAXPROD], struct enc encomendas[MAXENC])
{														/* Funcao responsavel por executar o comando 'm' (listar a quantidade maxima de*/ 
	int  ide_max=-1, qnt_max=-1, e=0, i=0, id;			/*  um produto numa encomenda e em que encomenda acontece)*/
	getchar();
	scanf("%d", &id);
	if (id >= iden_atual)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id);
	else
	{
		while (e < enc_atual)
		{
			i = 0;
			while(i < encomendas[e].cont_produtos)
			{
				if (strcmp(encomendas[e].prod_enc[i].desc,produtos[id].desc)==0)
				{
					if ((encomendas[e].prod_enc[i].qtd) > qnt_max)
					{
						ide_max=e;
						qnt_max=encomendas[e].prod_enc[i].qtd;
					}
					break;
				}
				i++;
			}
			e++;
		}
		if (ide_max!=-1 && qnt_max > 0)
			printf("Maximo produto %d %d %d.\n",id,ide_max,qnt_max);
	}
}	

void l(int iden_atual, struct prod produtos[MAXPROD])
{														/* Funcao responsavel por executar o comando 'l' (Listar todos os produtos por ordem de preco)*/
	int id[MAXPROD], temp[MAXPROD], i=0, x=0;
	if (iden_atual>0)									/* se exitirem produtos*/
	{
		while (i < iden_atual)							/* cria um array com os id dos produtos*/
		{
			id[i]=produtos[i].id;			
			i++;
		}
		mergesort(id, temp, 0, (iden_atual-1), produtos); /* ordena os id por preco atraves de mergesort*/
		printf("Produtos\n");
		while (x < iden_atual)
		{
			printf("* %s %d %d\n", produtos[id[x]].desc, produtos[id[x]].preco, produtos[id[x]].qtd);
			x++;
		}
	}
	else
		printf("Produtos\n");
}

void L(int enc_atual, struct enc encomendas[MAXENC])
{														/* Funcao responsavel por executar o comando 'L' (Listar todos os produtos de */
	char nomes[MAXPROD][MAXDESCPROD];					/* uma encomenda ordenados alfabeticamente por descricao)*/
	int  x=0, i=0, ide, count=0;
	getchar();
	scanf("%d", &ide);
	if(ide >= enc_atual)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	else if(encomendas[ide].cont_produtos==0)
		printf("Encomenda %d\n", ide);
	else
	{
		while (i < encomendas[ide].cont_produtos)		/* cria a array com as descricoes dos produtos para ordenar*/
		{
			strcpy(nomes[i], encomendas[ide].prod_enc[i].desc);
			i++;
		}
		count=encomendas[ide].cont_produtos;
		alphasort(nomes, count);						/* ordena a array dos nomes por ordem alfabetica*/
		printf("Encomenda %d\n", ide);
		while(x<count)									/* ciclo que procura o id dos produtos dentro da encomenda e faz print*/
		{
			i=0;
			while(i < encomendas[ide].cont_produtos)
			{
				if (strcmp(encomendas[ide].prod_enc[i].desc,nomes[x])==0 && encomendas[ide].prod_enc[i].qtd > 0)
				{
					printf("* %s %d %d\n", nomes[x], encomendas[ide].prod_enc[i].preco, encomendas[ide].prod_enc[i].qtd);
				}
				i++;
			}
			x++;
		}
	}
}
/* Funcao main onde o programa volta sempre que acaba um comando*/
int main()
{
	struct prod produtos[MAXPROD]; 						/* Inicializacao do array com os produtos todos (max 10000) */
	char cmd;
	int iden_atual=0, enc_atual=0;						/* inincializacao de dois contadores, um do numero de encomendas*/
	while ((cmd = getchar()) != 'x')					/* existentes e outro do numero de produtos existentes com o objetivo de tornar mais eficaz o programa*/
	{													/* pois deste modo nao e preciso limitar os ciclos com o maximo de cada (produto ou encomenda)*/
		if (cmd == 'a')
		{
			a(iden_atual, produtos);
			iden_atual++;
		}
	    else if (cmd == 'q')
		{
			q(iden_atual, produtos);
		}
		else if (cmd == 'r')
		{
			r(iden_atual, produtos);
		}
		
		else if (cmd == 'N')
		{
			N(enc_atual);
			enc_atual++;
		}
		
		else if (cmd == 'A')							/* ciclo que escolhe o comando a utilizar e termina quando o comando e 'x'*/
		{
			A(enc_atual, iden_atual, produtos, encomendas);			
		}
		
		else if (cmd == 'R')
		{
			R(enc_atual, iden_atual, produtos, encomendas);
		}
		
		else if (cmd == 'C')
		{
			C(enc_atual, encomendas);
		}

		else if (cmd == 'p')
		{
			p(enc_atual, iden_atual, produtos, encomendas);
		}
		else if (cmd == 'E')
		{
			E(enc_atual, iden_atual, produtos, encomendas);
		}
		
		else if (cmd == 'm')
		{
			m(enc_atual, iden_atual, produtos, encomendas);
		}
		else if (cmd == 'l')
		{
			l(iden_atual, produtos);
		}
		else if (cmd == 'L')
		{
			L(enc_atual, encomendas);
		}
		else 
			continue;
	} 	
	return 0;
}
