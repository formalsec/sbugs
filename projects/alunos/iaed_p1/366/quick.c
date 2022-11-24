#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h> 

#define PROD 10000	/*numero maximo de produtos*/
#define DESC 63		/*numero maximo de caracteres por descricao*/
#define TAM 500		/*numero maximo de encomendas*/
#define PESO 200	/*numero maximo de unidades de peso por encomenda*/
#define exch(A,B) {int t;t=A;A=B;B=t;}

/*estrutura que representa um produto*/
typedef struct{
	int num;
	int preco, peso, qnt;
	char desc[DESC];
}Produto;

/*estrutura que representa uma encomenda*/
typedef struct{
	int indice;
	Produto pedido[200];
}Encomenda;


Produto obj[PROD];	/*variavel que armazena os produtos*/
Encomenda enc[TAM];	/*variavel que armazena as encomendas*/

/*funcao auxiliar que ajuda a ordenar os produtos por preco*/
int partition_P(int a[], int l, int r){
	int v;
	int i = l-1;
	int j = r;
	v = a[r];
	while (i < j){
		while (obj[a[++i]].preco < obj[v].preco || (obj[a[i]].preco == obj[v].preco && obj[a[i]].num < obj[v].num));
		while (obj[v].preco < obj[a[--j]].preco || (obj[v].preco == obj[a[j]].preco && obj[v].num < obj[a[j]].num))
			if (j == l)
				break;
		if (i < j)
			exch(a[i], a[j]);
	}
	exch(a[i], a[r]);
	return i;
}

/*funcao auxiliar que ajuda a ordenar os produtos por preco*/
void quicksort_P(int a[], int l, int r){
	int i;
	if (r <= l){
		return;
	}
	i = partition_P(a, l, r);
	quicksort_P(a, l, i - 1);
	quicksort_P(a, i + 1, r);
}

/*funcao auxiliar que ajuda a ordenar os produtos de uma encomenda por descricao*/
int partition_L(int a[], int l, int r){
	int v;
	int i = l-1;
	int j = r;
	v = a[r];
	while (i < j){
		while (strcmp(obj[a[++i]].desc, obj[v].desc) < 0);
		while (strcmp(obj[v].desc, obj[a[--j]].desc) < 0)
			if (j == l)
				break;
		if (i < j)
			exch(a[i], a[j]);
	}
	exch(a[i], a[r]);
	return i;
}

/*funcao auxiliar que ajuda a ordenar os produtos de uma encomenda por descricao*/
void quicksort_L(int a[], int l, int r){
	int i;
	if (r <= l){
		return;
	}
	i = partition_L(a, l, r);
	quicksort_L(a, l, i - 1);
	quicksort_L(a, i + 1, r);
}

/*funcao que adiciona stock a um produto existente no sistema*/
void adiciona_produto(int idp){
	char esp;	/*variavel que armazena o primeiro espaco lido*/
	scanf("%c%[^:]:%d:%d:%d", &esp, obj[idp].desc, &obj[idp].preco, &obj[idp].peso, &obj[idp].qnt);
	obj[idp].num = idp; 
	printf("Novo produto %d.\n", idp);
}

/*funcao que adiciona stock a um produto existente*/
void adiciona_stock(int idp){
	int a, b;	/*variaveis que recebem o input*/
	scanf("%d:%d", &a, &b);
	if (a < idp){
		obj[a].qnt += b;
	} else {
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", a);
	}
}

void adiciona_enc(int a, int b, int c){
	int i, k;
	int soma = 0;	/*variavel que armazena o peso total da encomenda lida*/
	for (i = 0; i < enc[a].indice; i++){
			soma += enc[a].pedido[i].peso * enc[a].pedido[i].qnt;	/*verifica se o peso passa a lotacao maxima*/
		}
		soma += c * obj[b].peso;	/*acrescenta o peso do produto acrescentado a variavel*/
		/*verifica se o peso nao excede a capacidade maxima*/
		if (soma > 200){
			printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", b, a);
			return;
		}	
		for (k = 0; k < enc[a].indice; k++){
			/*se o produto ja pertencer a encomenda*/
			if (enc[a].pedido[k].num == b){
				enc[a].pedido[k].qnt += c;
				obj[b].qnt -= c;
				return;
			}
		}
		/*o produto ainda nao pertence a encomenda*/
		enc[a].pedido[enc[a].indice].preco = obj[b].preco;
		enc[a].pedido[enc[a].indice].peso = obj[b].peso;
		enc[a].pedido[enc[a].indice].qnt = c;
		enc[a].pedido[enc[a].indice].num = b;
		obj[b].qnt -= c;
		enc[a].indice += 1;
}

/*funcao que adiciona um produto a uma encomenda*/
void adiciona_prod_enc(int idp, int ide){
	int a, b, c;	/*variaveis que recebem o input*/
	scanf("%d:%d:%d", &a, &b, &c);
	if (a >= ide){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", b, a);
	} 
	else if (b >= idp){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", b, a);
	} 
	else if (obj[b].qnt < c){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", b, a);
	}
	else{
		adiciona_enc(a, b, c);
	}
}

/*funcao que remove stock a um produto existente*/
void remove_stock(int idp){
	int a, b;		/*variaveis que recebem o input*/
	scanf("%d:%d", &a, &b);
	if (a >= idp){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", a);
	} else if (obj[a].qnt - b < 0){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", b, a);
	} else{
		obj[a].qnt -= b;
	}
}

/*funcao que remove um produto de uma encomenda*/
void remove_produto(int idp, int ide){
	int i;
	int a, b;	/*variaveis que recebem o input*/
	scanf("%d:%d", &a, &b);
	if (a >= ide){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", b, a);
	} else if (b >= idp){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", b, a);
	} else{
		/*percorre a encomenda para encontrar o indice do produto nessa encomenda*/
		for (i = 0; i < enc[a].indice; i++){
			if (enc[a].pedido[i].num == b){
				obj[b].qnt += enc[a].pedido[i].qnt;
				enc[a].pedido[i].qnt = 0;
			}
		}
	}
}

/*funcao que calcula o custo de uma encomenda*/
void custo_encomenda(int ide){
	int c;		/*variavel que recebe o input*/
	int i;
	int custo = 0;		/*variavel que armazena o custo da encomenda*/	
	scanf("%d", &c);
	if (c >= ide){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", c);
	} else{
		/*calcula o preco total de uma encomenda*/
		for (i = 0; i < enc[c].indice; i++){
			custo += enc[c].pedido[i].preco * enc[c].pedido[i].qnt;
		}
		printf("Custo da encomenda %d %d.\n", c, custo);
	}
}

/*funcao que altera o pre?o de um produto existente no sistema*/
void altera_preco(int idp, int ide){
	int a, p;		/*variaveis que recebem o input*/
	int i, j;
	scanf("%d:%d", &a, &p);
	if (a >= idp){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", a);
	} else{
		/*percorre todas as encomendas*/
		for (i = 0; i < ide; i++){
			for (j = 0; j < enc[i].indice; j++){
				/*se o produto pertencer a encomenda altera o seu preco*/
				if (enc[i].pedido[j].num == a){
					enc[i].pedido[j].preco = p;
				}
			}
		}
		obj[a].preco = p;
	}
}

/*funcao que lista a descri??o e a quantidade de um produto numa encomenda*/
void lista_desc_qnt(int idp, int ide){
	int quant = 0;
	int i;
	int a, b;		/*variaveis que recebem o input*/
	scanf("%d:%d", &a, &b);
	if (a >= ide){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", a);
	} else if (b >= idp){
		printf("Impossivel listar produto %d. Produto inexistente.\n", b);
	} else{
		for (i = 0; i < enc[a].indice; i++){
			if (enc[a].pedido[i].num == b){
				quant = enc[a].pedido[i].qnt;
				break;
			}
		}
		printf("%s %d.\n", obj[b].desc, quant);
	}
}

/*funcao que lista o identificador da encomenda em que o produto dado ocorre mais vezes*/
void lista_qnt_maxima(int idp, int ide){
	int i, j; 
	int p;		    /*variavel que recebe o input*/
	int maior, max = 0;	/*variaveis que armazenam a encomenda que tem a maior quantidade desse produto e essa quantidade, respetivamente*/
	scanf("%d", &p);
	if (p >= idp){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", p);	
	} else{
		/*percorre todas as encomendas existentes*/
		for(j = 0; j < ide; j++){
			for (i = 0; i < enc[j].indice; i++){
				/* verifica se o produto pertence a encomenda*/
				if (enc[j].pedido[i].num == p){
					/*verifica se a quantidade desse produto e a maior ate aqui*/
					if (enc[j].pedido[i].qnt > max){
						max = enc[j].pedido[i].qnt;
						maior = j;
					}
				}
			}
		}
		/*verifica se o produto pertence a alguma encomenda*/
		if (max){
			printf("Maximo produto %d %d %d.\n", p, maior, max);
		}
	}
}

/*funcao que lista todos os produtos existentes no sistema por ordem crescente de preco*/
void lista_por_preco(int idp){
	int x, h;	/*primeiro e ultimo indice da variavel sort, respetivamente*/		
	int sort[PROD];	/*variavei que armazena o indice de todos os produtos do sistema*/
	for (h = 0; h < idp; h++){
		sort[h] = h;
	}
	/*ordena os elementos da tabela*/
	quicksort_P(sort, 0, idp - 1);
	printf("Produtos\n");
	for (x = 0; x < idp; x++){
		printf("* %s %d %d\n", obj[sort[x]].desc, obj[sort[x]].preco, obj[sort[x]].qnt);
	}
}


/*funcao que lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o*/
void lista_por_desc(int ide){
	int a;		/*variavel que recebe o input*/
	int x, h, y;
	int fra[PESO];		/*variavel que armazena os indices dos produtos da encomenda*/
	scanf("%d", &a);
	if (a >= ide){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", a);
	} else{
		for (h = 0; h < enc[a].indice; h++){
			fra[h] = enc[a].pedido[h].num;
		}
		/*ordena os elementos da tabela*/
		quicksort_L(fra, 0, enc[a].indice - 1);
		printf("Encomenda %d\n", a);
		/*percorre todos os produtos da encomenda*/
		for (x = 0; x < enc[a].indice; x++){
			for (y = 0; y < enc[a].indice; y++){
				/*ve a ordem pela qual vai imprimir e verifica se o produto pertence a encomenda*/
				if (enc[a].pedido[y].num == fra[x] && enc[a].pedido[y].qnt > 0){
					printf("* %s %d %d\n", obj[fra[x]].desc, obj[fra[x]].preco, enc[a].pedido[y].qnt);
				}
			}
		}
	}
}

int main(){
	char v;		/*variavel que le qual e o comando que ira executar*/
	int i;
	int idp = 0;		/*variavel que armazena o numero de produtos*/
	int ide = 0;		/*variavel que armazena o numero de encomendas*/
	/*inicia todas as encomendas com 0 produtos*/
	for (i = 0; i < 500; i++){
		enc[i].indice = 0;
	}
	scanf("%c", &v);
	while (v != 'x'){
		switch (v){
			case 'a': adiciona_produto(idp);
				  	  idp += 1;
				  	  break;
			case 'q': adiciona_stock(idp);
				  	  break;
			case 'N': printf("Nova encomenda %d.\n", ide);
					  ide += 1;
					  break;
			case 'A': adiciona_prod_enc(idp, ide);
					  break;
			case 'r': remove_stock(idp);
					  break;
			case 'R': remove_produto(idp, ide);
					  break;
			case 'C': custo_encomenda(ide);
					  break;
			case 'p': altera_preco(idp, ide);
					  break;
			case 'E': lista_desc_qnt(idp, ide);
					  break;
			case 'm': lista_qnt_maxima(idp, ide);
					  break;
			case 'l': lista_por_preco(idp);
					  break;
			case 'L': lista_por_desc(ide);
					  break;
		}
		scanf("%c", &v);
	}
	return 0;
}