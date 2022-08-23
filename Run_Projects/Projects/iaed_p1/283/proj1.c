#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*no maximo so podem existir 10000 produtos*/ 
#define MAX 10000 
/*uma descricao pode ter no maximo 63 caracteres*/
#define MAXD 64
/*uma encomenda so pode ter no maximo 500 produtos*/
#define ENCOMAX 500
/*o peso maximo ? 200, no entanto faz sentido a minha variavel ser 201 de acordo como estou a definir a funcao mais a frente no programa*/
#define PesoMax 201

/*define-se uma estrutura para os produtos que contem todos os parametros que cada produto tem*/
typedef struct {
	int idp; 
	char description[MAXD];
	int price;
	int quantity; 
	int weight; 
	
} product;

/*define-se uma estrutura para as encomendas que contem todos os parametros que cada produto tem (usando a estrutura product) bem como parametros extra que so se aplicam a estruturas*/
typedef struct{
	product produtos[MAX];
	int ide; 
	int peso; 
	int pesomax;

} encomenda;

/*criaram-se duas variaveis globais com maxidp e maxide (que nao so incrementava o valor do idp e do ide, como foi tambem usada como uma variavel no caso de querer saber quantos produtos e encomendas estao aramzenados nas estruturas)*/
int maxidp, maxide;
product produtos[MAX];
encomenda encomendas[ENCOMAX];



/*funcao auxiliar*/

/*esta funcao permite trocar os vetores de duas posicoes*/
void exch(product a[], int i, int j){
	product aux = a[i]; 
	a[i] = a[j];
	a[j] = aux; 
}

/*funcao permite comparar o preco de dois produtos e caso sejam iguais entao compara o seu idp*/
int less(product a, product v){
	if(a.price == v.price){
		if(a.idp<v.idp)
		return 1;
	}
	if(a.price < v.price)
		return 1;
	return 0; 
}

int partition_preco(product a[], int l, int r){
	int i = l-1;
	int j = r;
	product v = a[r];
	while (i<j){
		while (less(a[++i],v));
		while (less(v, a[--j])){
			if (j == l)
				break;
		}
		if(i<j)
			exch(a, i ,j);
		}
		
	exch(a, i, r);
	return i; 
}

void quicksort_preco(product a[], int l, int r){
	int i = 0; 
	if (r <= l)
		return; 
	i = partition_preco(a, l,r);
	quicksort_preco(a, l, i-1); 
	quicksort_preco(a, i+1, r); 
}





/*funcao permite comparar a descricao de dois produtos*/
void exch_nome(product a[], int i, int j){
	product aux = a[i]; 
	a[i] = a[j];
	a[j] = aux; 
}	

int less_descricao(product a, product v){
	int result;
	result = strcmp(a.description, v.description);
	if(result<0)
		return 1;
	return 0; 
}


int partition_nome(product a[], int l, int r){
	int i = l;
	int j = r;
	product v = a[r];
	while (i<j){
		while (less_descricao(a[++i],v));
		while (less_descricao(v, a[--j]))
		{
			if (j == l)
				break;
		}
		if(i<j)
			exch_nome(a, i ,j);
		}
		
	exch_nome(a, i, r);
	return i; 
}

void quicksort_nome(product a[], int l, int r){
	int i = 0;
	if (r <= l)
		return; 
	i = partition_nome(a, l,r);
	quicksort_nome(a, l, i-1); 
	quicksort_nome(a, i+1, r); 
}



/*funcoes principais*/


/* funcao a - permite adicionar um novo produto ao sistema e onde o maxip e incrementado*/
int criaproduto (){
	char espaco = '\0'; 
	scanf("%c",&espaco);
	scanf("%[^:]:%d:%d:%d", produtos[maxidp].description, &produtos[maxidp].price, &produtos[maxidp].weight, &produtos[maxidp].quantity);
	produtos[maxidp].idp = maxidp;
	printf("Novo produto %d.\n", maxidp);
	return ++maxidp;
}

/* funcao q - permite adicionar stock a um produto existente*/
void novostock(){
	int arg2, arg3; 
	scanf("%d:%d", &arg2, &arg3);
	if (arg2>=maxidp) 
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", arg2);
	else	
		produtos[arg2].quantity += arg3; 
	return;
}

/* funcao N - cria uma nova encomenda e incrementa no valor do maxide*/
int criaencomenda(){
	encomendas[maxide].ide = maxide;
	printf("Nova encomenda %d.\n", maxide);
	return ++maxide;

}

/* funcao A - adiciona um novo produto a encomenda*/
void adicionaproduto(){
	int arg1, arg2, arg3; 
	int quantidade, peso,pesoencomenda, peso_t;
	scanf("%d:%d:%d", &arg1, &arg2, &arg3);
	if(arg1>=maxide)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", arg2, arg1);
	else{
		if (arg2>=maxidp)
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", arg2, arg1);
		else{
			if (produtos[arg2].quantity < arg3) /*se o produto que se pertende adiconar e maior que o stock do produto*/
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", arg2, arg1);
			else{
				if (encomendas[arg1].produtos[arg2].quantity != 0){ /*se o produto existir na encomenda*/
					peso = produtos[arg2].weight; 
					quantidade = arg3; 
					peso_t = peso * quantidade; /*calcula o peso que seria adicionado a encomenda com a adicao da quantidade do produto*/
					pesoencomenda = peso_t + encomendas[arg1].pesomax; /*adicao do peso adicional da encomenda com o peso do que sera adicionado*/
					if(pesoencomenda >= PesoMax) /*se este peso for maior que o PesoMax entao nao sera possivel adicionar*/
						printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", arg2, encomendas[arg1].ide); 
					else{
						encomendas[arg1].pesomax += peso_t; /*senao e adicionado ao pesomax daquela encomenda, o peso adicionado com a nova quantidade adicionada*/
						encomendas[arg1].produtos[arg2].quantity += arg3;
						produtos[arg2].quantity -= arg3;
						strcpy(encomendas[arg1].produtos[arg2].description, produtos[arg2].description);
						} /*se e adicionado quantidade a encomenda, entao a quantidade em stock diminui*/
					}
				else{ /*o produto nao existe na encomenda*/
					peso = produtos[arg2].weight; 
					quantidade = arg3; 
					peso_t = peso * quantidade; 
					pesoencomenda = peso_t + encomendas[arg1].pesomax;
					if(pesoencomenda >= PesoMax)
						printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", arg2, encomendas[arg1].ide); 
					else{
						encomendas[arg1].pesomax += peso_t;
						encomendas[arg1].produtos[arg2].quantity = arg3;
						produtos[arg2].quantity -= arg3;
						strcpy(encomendas[arg1].produtos[arg2].description, produtos[arg2].description);
				}
			}
		}
	}
	}
	return; 
}


/* funcao r - remove stock a um produto existente*/
void removestock() {
	int arg2, arg3, atual;
	scanf("%d:%d", &arg2, &arg3);
	if (arg2>=maxidp)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", arg2);
	else{
		atual = produtos[arg2].quantity;/*quero guardar o valor anterior a fazer alteracoes, caso estas alteracoes nao seja possiveis, volto a adicionar o valor da quantidade inicialmente*/
		produtos[arg2].quantity -= arg3;/*retiro a quantidade desejada ao stock*/
		if (produtos[arg2].quantity < 0){ /*caso o stock seja negativo, sei qeu nao sera possivel tirar toda essa quantidade*/
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", arg3, arg2);
			produtos[arg2].quantity = atual;/*caso o valor final nao seja menor que 0, entao nao volto a colocar a quantidade inicial*/
		}
	}
	return;
}

/* funcao R - remove o produto de uma encomenda*/
void removeproduto(){
	int arg1, arg2,c, peso;
	int pesototal = 0;  
	scanf("%d:%d", &arg1, &arg2);
	if(arg1>=maxide)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", arg2, arg1);
	else{
		if (arg2>=maxidp)
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", arg2, arg1);
		else{
			c = encomendas[arg1].produtos[arg2].quantity; 
			produtos[arg2].quantity += c; /*adiciona ao stock da funcao o que estava na encomenda*/
			encomendas[arg1].produtos[arg2].quantity = 0; /*nao e necessario retirar a encomenda, basta colocar a sua quantidade a zero*/
			peso = produtos[arg2].weight; 
			pesototal = peso*c; 
			encomendas[arg1].pesomax -= pesototal; /*retiro o peso ocupado pela quantidade daquele produto no peso de cada encomenda*/
		}
	}
	return; 
}

/* funcao C - calcula o custo de cada encomenda*/
int calculapreco(){
	int arg1, x, preco, quantidade, precototal; 
	int contador = 0;  
	scanf("%d", &arg1);
	if(arg1>=maxide)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", arg1);
	else{
		for (x= 0; encomendas[arg1].produtos[x].description < encomendas[arg1].produtos[maxidp].description; x++){ /*percorre todas as posicoes das encomendas e procura quais os produtos que se encontram em cada encomenda*/
			quantidade = encomendas[arg1].produtos[x].quantity;
			preco = produtos[x].price; 
			precototal = quantidade * preco;
			contador += precototal; /*vai adicionado o preco de cada produto ao contador que inclui o preco total da encomenda*/
		}
		printf("Custo da encomenda %d %d.\n", arg1, contador);
	}
	return 0; 
}

/* funcao p - altera o preco de um produto existente no sistema*/
void alterapreco(){
	int arg2, arg3; 
	scanf("%d:%d", &arg2, &arg3);
	if (arg2>=maxidp)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", arg2);
	else
		produtos[arg2].price = arg3;/*altera o preco do produto para o novo valor*/
	return;
}

/* funcao E - lisra a descricao e a quantidade de um produto numa encomenda*/
void lista(){
	int arg1, arg2, quantidade = 0;
	scanf("%d:%d", &arg1, &arg2);
	if(arg1 >= maxide){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", arg1);
	} 
	else{
		if (arg2 >= maxidp)
			printf("Impossivel listar produto %d. Produto inexistente.\n", arg2);
		else{
			quantidade += encomendas[arg1].produtos[arg2].quantity;
			printf("%s %d.\n", produtos[arg2].description, quantidade);
		}
	}
	return; 
}

/* funcao m - lista o identificador da encomenda em que o produto dado ocorre mais vezes*/
int maximo(){
	int contador = 0, encomendaide, quantidade; 
	int arg1,x,c = 0; 
	scanf("%d", &arg1);
	if(arg1 >= maxidp)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", arg1);
	else{
		for (x = 0; x<maxidp; x++){
			c += encomendas[x].produtos[arg1].quantity; /*percorre aquele produto para ver se existe nalguma encomenda, se o valor de c for 0 entao o produto nao se encontra em nenhuma encomenda*/
		}
		if (c != 0){
			for (x = 0; x<=maxide; x++){
				if (encomendas[x].produtos[arg1].quantity != 0){ /*percorre todas as encomendas que contenham aquele produto*/
					quantidade = encomendas[x].produtos[arg1].quantity;
					if(quantidade == contador){ /*o contador indica qual a encomenda com a maior quantidade do produto, no entanto caso haja duas encomendas com a mesma quantidade, eu tenho de ordena-las de acordo com o seu ide*/
						if(encomendas[x].ide < encomendaide){ /*criei uma variavel encomenda, para me ir sempre dizendo qual o ide da encomenda com maior quantidade do produto escolhido*/
							contador = encomendas[x].produtos[arg1].quantity; /*caso a nova encomenda seja maior do que aquela que ja la estava, entao o seu contador (apesar de o seu valor ficar igual) passa a ter a quantidade do produto na encomensa*/
							encomendaide = encomendas[x].ide; /*a variavel encomenda vai mudar pois o seu ide vai fazer diferente*/
						}
					}
					if(quantidade > contador){ /*caso a quantidade seja maior que o contador*/
						contador = encomendas[x].produtos[arg1].quantity; /*a quantidade no contador vai mudar*/
						encomendaide = encomendas[x].ide;/*e o valor do ide da encomenda tamebm vai mudar*/
					}
				}
			}
			printf("Maximo produto %d %d %d.\n", arg1, encomendaide, contador);
		}
	}
	return 0;
}

/* funcao l - lista todos os produtos existentes no sistema por ordem cresecente de preco*/
int listaproduto(){
	int x = 0;
	int y = 0;
	product vetor[MAX];
	for(x = 0; x<maxidp; x++){ /*crio o vetor que vai conter todas as minhas informacoes dos produtos*/
		vetor[x].price = produtos[x].price;
		vetor[x].idp = produtos[x].idp;
		vetor[x].weight = produtos[x].weight; 
		vetor[x].quantity = produtos[x].quantity;
		strcpy(vetor[x].description, produtos[x].description);
	}

	quicksort_preco(vetor, y , maxidp-1);

	printf("Produtos\n");
	for(x = 0; x<maxidp; x++){ /*imprime os vetores ja ordenados*/
		printf("* %s %d %d\n", vetor[x].description, vetor[x].price, vetor[x].quantity);
	}
	return 0; 
}

/* funcao L - lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/
int listaalfabetica(){
	int x = 0, arg1;
	int len = 0;
	int id; 
	product vetor[MAX] = {0};
	int tamanho = 0;
	scanf("%d", &arg1);
	if(arg1 >= maxide)
		return printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", arg1) ;
	else {
		for (x= 0; x<maxidp; x++){ /*encontra o tamanho da encomenda*/
			if(encomendas[arg1].produtos[x].quantity != 0){
				id = produtos[x].idp;
				len += 1;
			}
		}
		if(len == 1){ /*caso o tamanho seja 1 nao necessita de ordenar*/
			printf("Encomenda %d\n", arg1);
			printf("* %s %d %d\n", encomendas[arg1].produtos[id].description, produtos[id].price, encomendas[arg1].produtos[id].quantity);
		}
		else{
			printf("Encomenda %d\n", arg1);
			for(x = 0; x< maxidp; x++){
				if (encomendas[arg1].produtos[x].quantity != 0){
					vetor[x].price = encomendas[arg1].produtos[x].price;
					vetor[x].idp = encomendas[arg1].produtos[x].idp;
					vetor[x].quantity = encomendas[arg1].produtos[x].quantity;
					strcpy(vetor[x].description, encomendas[arg1].produtos[x].description);
					tamanho++;
				}
			}
			quicksort_nome(vetor, 0, len);

			for(x = 0; x<len; x++)
				printf("* %s %d %d\n", vetor[x].description, vetor[x].price, vetor[x].quantity);
			}
		}
	return 0; 
}


/*esta funcao le os comandos do input*/
int main(){
	char frase = '\0'; 
	while (1){
		scanf("%c", &frase);
		switch(frase){
			case 'a': 
			criaproduto();
			break;

			case 'q': 
			novostock();
			break;

			case 'N':
			criaencomenda();
			break;

			case 'A':
			adicionaproduto(); 
			break;

			case 'r': 
			removestock(); 
			break; 

			case 'R':
			removeproduto();
			break;

			case 'C': 
			calculapreco();
			break;

			case 'p':
			alterapreco();
			break;

			case 'E': 
			lista();
			break; 

			case 'm': 
			maximo(); 
			break;

			case 'l':
			listaproduto();
			break;

			case 'L':
			listaalfabetica(); 
			break;

			case 'x': 
			return 0; 
			break;
	
		}
	}
}


