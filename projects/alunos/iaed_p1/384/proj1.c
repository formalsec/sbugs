#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include<string.h>

/* Constantes usados ao longo do projeto */
#define NOME 64
#define MAXp 10000
#define MAXe 500
#define PESOE 200
#define YES 1
#define NO 0

/* Caracteristicas do produto */

typedef struct produto{
	char descricao[NOME];
	int idp, preco, peso, qtd, flag;
}Produto;
Produto prod[MAXp];		/* Criacao do vetor do produto */

/* Caracteristicas da encomenda */

typedef struct encomenda{
	int cont, flag, peso;
	Produto encop[PESOE];
}Encomenda;
Encomenda enco[MAXe];		/* Criacao do vetor da encomenda */

/* Declaracoes de variaveis globais */

int prods, encos;

/* Funcao do caso a */

void case_a(int preco, int peso, int qtd){		/* Cada indicie do vetor, esta guardado para um produto */
	prod[prods].preco = preco;
	prod[prods].peso = peso;
	prod[prods].qtd = qtd;
	prod[prods].flag = YES;
	printf("Novo produto %d.\n", prods);
}

/* Funcao do caso q */

void case_q(int idp, int qtd){
	if (prod[idp].flag != YES){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);		
	}
	else{
		prod[idp].qtd += qtd;		/* Atualizado a quantidade do produto */
	}
}

/* Funcao do caso N */

void case_N(int ide){
	printf("Nova encomenda %d.\n", ide);
	enco[encos].flag = YES;
	enco[encos].cont = 0;		/* Inicializado o contador de produtos de cada encomenda */	
}

/* Funcao do caso A */

void case_A(int ide, int idp, int qtd){
	if(enco[ide].flag != YES){	
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
	else if(prod[idp].flag != YES){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else if(qtd > prod[idp].qtd){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
	}
	else if((enco[ide].peso + (prod[idp].peso * qtd)) > PESOE || (prod[idp].peso * qtd) > PESOE){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
	}
	else{
		int i;		
		for(i = 0; i < enco[ide].cont; i++){		/* Ve se o produto ja esta na encomenda, comparando se os idps, se sim flag YES */		
			if(enco[ide].encop[i].idp == idp){
				enco[ide].encop[i].flag = YES;
				break;
			}
			else{
				enco[ide].encop[i].flag = NO;
			}
		}
		if(enco[ide].encop[i].flag){		/* Se a flag for YES, muda se o peso da encomenda e atualiza se as qtds */
			enco[ide].peso += prod[idp].peso * qtd;				
			enco[ide].encop[i].qtd += qtd;
			prod[idp].qtd -= qtd;
		}
		else{		/* Se a flag for NO, o produto e adicionado, e aumenta se o contador */
			enco[ide].encop[enco[ide].cont] = prod[idp];		
			enco[ide].encop[enco[ide].cont].qtd = qtd;
			enco[ide].peso += prod[idp].peso * qtd;							
			prod[idp].qtd -= qtd;
			enco[ide].encop[i].flag = YES;
			enco[ide].cont ++;
		}
	}
}

/* Funcao do caso r */

void case_r(int idp, int qtd){
	if(prod[idp].flag != YES){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	}
	else if(prod[idp].qtd < qtd){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
	}
	else{
		prod[idp].qtd -= qtd;
	}
}

/* Funcao do caso R */

void case_R(int ide, int idp){
	if(enco[ide].flag != YES){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
	else if(prod[idp].flag != YES){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else{
		int i, j, in;
		for(i = 0; i < enco[ide].cont; i++){		/* Incrementa se o i, ate encontrar o produto da encomenda com o mesmo idp */
			if(enco[ide].encop[i].idp == idp){		/* i = idp por causa do break, e retirada o peso, e posto a qtd de volta ao produto */
				enco[ide].peso -= prod[idp].peso * enco[ide].encop[i].qtd;	
				prod[idp].qtd += enco[ide].encop[i].qtd;
				in = YES;
				break;
			}
			else{
				in = NO;
			}
		}
		if(in){
			for(j = i; j < enco[ide].cont; j++){		/* O vetor da encomenda ide e atualizada, retirada o produto idp e tudo para a frente e feito um shift left */
				enco[ide].encop[j] = enco[ide].encop[j + 1];
			}
			enco[ide].cont--;		/* O contador desta encomenda e decrementada */
			if(enco[ide].cont < 0){
				enco[ide].cont = 0;
			}
		}
	}
}

/* Funcao do caso C */

void case_C(int ide){
	if(enco[ide].flag != YES){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	}
	else{
		int i = 0, total = 0;
		while(enco[ide].encop[i].qtd > 0){		/* Percorre se o vetor ate nao haver mais produtos na encomenda, e somando ao total o (preco x qtd) */
			total += prod[enco[ide].encop[i].idp].preco * enco[ide].encop[i].qtd;
			i++;
		}
		printf("Custo da encomenda %d %d.\n", ide, total);
	}
}

/* Funcao do caso p */

void case_p(int idp, int preco){
	if(prod[idp].flag != YES){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	}
	else{
		int i, j;
		prod[idp].preco = preco;		/* E mudado o preco do produto */
		for(i = 0; i < encos; i++){		/* E mudado o preco nas encomendas, percorrendo todos os produtos de cada encomenda */
			for(j = 0; j < enco[i].cont; j++){
				if(enco[i].encop[j].idp == idp){
					enco[i].encop[j].preco = preco;
					break;
				}
			}
		}
	}
}

/* Funcao do caso E */

void case_E(int ide, int idp){
	int a = 0, i;
	if(enco[ide].flag != YES){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
	else if(prod[idp].flag != YES){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	}
	else{
		for(i = 0; i < enco[ide].cont; i++){		/* Percorre se o vetor dos produtos da encomenda ide */
			if(enco[ide].encop[i].idp == idp){
				a = enco[ide].encop[i].qtd;
				break;
			}
		}
	printf("%s %d.\n", prod[idp].descricao, a);
	}
}

/* Funcao do caso m */

void case_m(int idp){
	if(prod[idp].flag != YES){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	}
	else{		
		int maxA = 0, i, j, m_ide, in = NO;
		for(i = 0; i < encos; i++){		/* Percorre se o vetor das encomendas, e em cada e percorrido o vetor dos produtos */
			for(j = 0; j < enco[i].cont; j++){
				if(enco[i].encop[j].idp == idp){
					if(maxA < enco[i].encop[j].qtd){
						maxA = enco[i].encop[j].qtd;		/* O maxA tomara sempre o produto com maior qtd */
						m_ide = i;
						in = YES;
						break;
					}
				}
			}
		}
		if(in){ 
			printf("Maximo produto %d %d %d.\n", idp, m_ide, maxA);
		}
	}
}

/* Funcao do caso l */
void copy_newprod(Produto newprod[]){		/* Para nao destruir o meu vetor de produtos e passado para um novo vetor */
	int i;
	for(i = 0; i < prods; i++){
		newprod[i] = prod[i];
	}
}

void merge(Produto newprod[], int left, int mid, int right){
	int i, j, k;
	Produto aux[MAXp];
	for(i = mid + 1; i > left; i--){
		aux[i - 1] = newprod[i - 1];
	}
	for(j = mid; j < right; j++){
		aux[right + mid - j] = newprod[j + 1];
	}
	for(k = left; k <= right; k++){
		if(aux[j].preco < aux[i].preco){		/* Se os precos forem diferentes, e ordenada de forma crescente */
			newprod[k] = aux[j--];
		}
		else if(aux[j].preco == aux[i].preco){		/* Se os precos forem iguais, e ordenada o idp de forma crescente */
			if(aux[j].idp < aux[i].idp){
				newprod[k] = aux[j--];
			}
			else{
				newprod[k] = aux[i++];
			}
		}
		else{
			newprod[k] = aux[i++];
		}
	}
}

void mergesort(Produto newprod[], int left, int right){
	int mid = (right + left)/2;
	if(right <= left)
		return;
	mergesort(newprod, left, mid);
	mergesort(newprod, mid + 1, right);
	merge(newprod, left, mid, right);
}

void case_l(){
	Produto newprod[MAXp];		/* criada um vetor que copia o vetor dos produtos */
	int i;
	copy_newprod(newprod);
    mergesort(newprod, 0, prods - 1);
    printf("Produtos\n");
    for(i = 0; i < prods; i++){
    	printf("* %s %d %d\n", newprod[i].descricao, newprod[i].preco, newprod[i].qtd);
    }
}

/* Funcao para o caso L */

void bubblesort(int ide){
	Produto aux;		/* Crio um aux com struct do produto, para trocar os dois produtos, sem destruir nenhum */
	int i, j;
    for(i = 0; i < enco[ide].cont; i++)
       for(j = i + 1; j < enco[ide].cont; j++){
          if(strcmp(enco[ide].encop[i].descricao, enco[ide].encop[j].descricao) > 0){
            aux = enco[ide].encop[i]; 
    		enco[ide].encop[i] = enco[ide].encop[j]; 
    		enco[ide].encop[j] = aux;
        }
    }
}

void case_L(int ide){
    if(enco[ide].flag != YES){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{	
    	int i;
	    bubblesort(ide);
		printf("Encomenda %d\n", ide);
		for(i = 0; i < enco[ide].cont; i++){
			printf("* %s %d %d\n", enco[ide].encop[i].descricao, enco[ide].encop[i].preco, enco[ide].encop[i].qtd);
		}
	}
}

/* Corpo principal do codigo */

int main(){
	char a;
	int qtd, idp = 0, ide = 0, preco = 0;
	while(a != 'x'){
		switch(a = getchar()){		/* Ve a letra que e fornecida e escolhe o caso com a mesma letra */
			case 'a':
				getchar();		/* Este getchar serve para tirar o espaco entra a letra e a descricao */
				scanf("%[^:]:%d:%d:%d", prod[prods].descricao, &prod[prods].preco, &prod[prods].peso, &prod[prods].qtd);
				case_a(prod[prods].preco, prod[prods].peso, prod[prods].qtd);
				prod[prods].idp = prods;		/* Prods serve como contador de produtos e idp para dizer o id de cada produto */
				prods++;		/* Numero de produtos que existem no sistema */
				break;
			case 'q':
				scanf("%d:%d", &idp, &qtd);
				case_q(idp, qtd);
				break;
			case 'N':
				case_N(encos);
				encos++;		/* Numero de encomendas que existe no sistema */				
				break;
			case 'A':
				scanf("%d:%d:%d", &ide, &idp, &qtd);
				case_A(ide, idp, qtd);
				break;
			case 'r':
				scanf("%d:%d", &idp, &qtd);
				case_r(idp, qtd);
				break;
			case 'R':			
				scanf("%d:%d", &ide, &idp);
				case_R(ide, idp);
				break;
			case 'C':
				scanf("%d", &ide);
				case_C(ide);
				break;
			case 'p':
				scanf("%d:%d", &idp, &preco);
				case_p(idp, preco);
				break;
			case 'E':
				scanf("%d:%d", &ide, &idp);
				case_E(ide, idp);
				break;
			case 'm':
				scanf("%d", &idp);
				case_m(idp);
				break;
			case 'l':
				case_l();
				break;
			case 'L':
				scanf("%d", &ide);
				case_L(ide);
				break;
			default:
				break;
		}
	}
	return 0;
}