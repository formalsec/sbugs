#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_PRODUTO 10000
#define MAX_DESCRICAO 64
#define MAX_ENCOMENDAS 500

/*estrutura que representa um produto*/
/*indentificador de cada produto e igual ao indice no array pdt*/ 
typedef struct{
	char descricao[MAX_DESCRICAO];
	int preco;
	int peso;
	int stock;
}produto;

/*estrututra auxiliar as encomendas*/
typedef struct{
	/*informacao importante dos produtos so usada nas encomendas*/
	int idp;
	/*encomendas e a quantidadede de vezes que o produto foi encomendado*/
	int encomendas;
}produto_encomendado;

/*estrutura que representa uma encomenda*/
typedef struct{
	int nr_produtos_encomendados;
	produto_encomendado produto[MAX_PRODUTO];
	/*peso total de cada encomenda*/
	int peso;
}encomendas;

produto pdt[MAX_PRODUTO];
encomendas e[MAX_ENCOMENDAS];
int nr_produtos = 0;
int nr_encomendas = 0;

/*funcao que adiciona um novo produto*/
void a(){
	char descricao[MAX_DESCRICAO];
	int preco, peso, qtd;
	/*leitura do input*/
	scanf(" %[^:]:%d:%d:%d", descricao, &preco, &peso, &qtd);
	if(nr_produtos < MAX_PRODUTO){
		/*copia para a estrura o input*/
		strcpy(pdt[nr_produtos].descricao, descricao);
		pdt[nr_produtos].preco = preco;
		pdt[nr_produtos].peso = peso;
		pdt[nr_produtos].stock = qtd;
		printf("Novo produto %d.\n", nr_produtos);
		nr_produtos++;
	}
}

/*funcao auxiliar que lista todos os produtos*/
void k(){
	int i;
	for(i = 0; i < nr_produtos; i++){
		printf("%d %s %d %d %d\n", i, pdt[i].descricao, pdt[i].preco, pdt[i].peso, pdt[i].stock);
	}
}

/*funcao que adiciona o stock de um produto*/
void q(){
	int i, qtd;
	scanf(" %d:%d", &i, &qtd);
	if(i < nr_produtos){
		pdt[i].stock += qtd;
	}
	else{
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", i);
	}
}

/*funcao que remove stock de um produto*/
void r(){
	int i, qtd;
	scanf(" %d:%d", &i, &qtd);
	if(i >= nr_produtos){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", i);
	}
	else if(qtd > pdt[i].stock){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, i);
	}
	else{
		pdt[i].stock -= qtd;
	}
}

/*funcao que altera o preco de um produto*/
void p(){
	int i, preco;
	scanf(" %d:%d", &i, &preco);
	if(i < nr_produtos){
		pdt[i].preco = preco;
	}
	else{
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", i);
	}
}

/*funcao que faz o merge de dois subarrays*/
void merge(produto array[], int l, int m, int r) { 
	produto aux[MAX_PRODUTO], aux1[MAX_PRODUTO];
    int i, j, k;
    /*subarray aux[l,..,m]*/ 
    int n1 = m - l + 1;
    /*subarray aux1[m+1,..,r]*/ 
    int n2 = r - m;
    /*copia os produtos para cada um dos subarrays auxiliares*/ 
    for(i = 0; i < n1; i++){ 
        aux[i] = array[l + i];
    } 
    for(j = 0; j < n2; j++){ 
        aux1[j] = array[m + 1 + j];
    }
    /*merge dos dois subarrays*/ 
    i = 0;
    j = 0;
    /*indice em que faz o merge*/
    k = l; 
    while(i < n1 && j < n2){ 
        if (aux[i].preco <= aux1[j].preco){ 
            array[k] = aux[i]; 
            i++; 
        } 
        else{ 
            array[k] = aux1[j]; 
            j++; 
        } 
        k++; 
    } 
    while(i < n1){ 
        array[k] = aux[i]; 
        i++; 
        k++; 
    } 
    while(j < n2){ 
        array[k] = aux1[j]; 
        j++; 
        k++; 
    } 
} 

/*funcao recursiva que executa o merge sort*/
void mergeSort(produto array[], int i, int e){ 
	int aux;
    if(i < e){ 
        aux = i + (e - i) / 2; 
        mergeSort(array, i, aux); 
        mergeSort(array, aux + 1, e); 
        merge(array, i, aux, e); 
    } 
} 

/*funcao que lista os produtos por ordem crescente de preco*/
void l(){
	/*array de produtos auxiliar para preservar a ordem de produtos*/
	produto aux[MAX_PRODUTO];
	int i;
	for(i = 0; i < nr_produtos; i++){
		aux[i] = pdt[i];
	}
	/*sort dos produtos atraves de um merge sort*/
	mergeSort(aux, 0, nr_produtos - 1);
	printf("Produtos\n");
	for(i = 0; i < nr_produtos; i++){
		printf("* %s %d %d\n", aux[i].descricao, aux[i].preco, aux[i].stock);
	}
}

/*funcao que cria encomendas*/
void N(){
	if(nr_encomendas < MAX_ENCOMENDAS){
		printf("Nova encomenda %d.\n", nr_encomendas);
		e[nr_encomendas].nr_produtos_encomendados = 0;
		e[nr_encomendas].peso = 0;
		nr_encomendas++;
	}
}

/*funcao que dado uma encomenda e indentificador de produto retorna o
indice em que se encontra esse produto
caso o produto n estiver n encomenda retorna -1*/
int findIdp(int ide, int idp){
	int i;
	for(i = 0; i < e[ide].nr_produtos_encomendados; i++){
		if(idp == e[ide].produto[i].idp){
			return i;
		}
	}
	return -1;
}

/*funcao que adiciana um produto a uma encomenda*/
void A(){
	int ide, idp, qtd, aux;
	scanf(" %d:%d:%d", &ide, &idp, &qtd);
	if(ide >= nr_encomendas){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
	else if(idp >= nr_produtos){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else if(qtd > pdt[idp].stock){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
	}
	else if(qtd * pdt[idp].peso + e[ide].peso > 200){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
	}
	else{
		aux = findIdp(ide, idp);
		if(aux == -1){
			aux = e[ide].nr_produtos_encomendados++;
			e[ide].produto[aux].idp = idp;
			e[ide].produto[aux].encomendas = qtd;
			e[ide].peso += qtd * pdt[idp].peso;
			pdt[idp].stock -= qtd;
		}
		else{
			e[ide].produto[aux].encomendas += qtd;
			e[ide].peso += qtd * pdt[idp].peso;
			pdt[idp].stock -= qtd;
		}
	}
}

/*funcao auxiliar que lista todos os produtos de uma encomenda*/
void K(){
	int ide, i;
	scanf(" %d", &ide);
	printf("%d\n", e[ide].peso);
	for(i = 0; i < e[ide].nr_produtos_encomendados; i++){
		printf("%d %d\n", e[ide].produto[i].idp, e[ide].produto[i].encomendas);
	}
}

/*funcao que remove um produto de uma encomenda*/
void R(){
	int ide, idp, aux, i;
	scanf(" %d:%d", &ide, &idp);
	if(ide >= nr_encomendas){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
	else if(idp >= nr_produtos){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else{
		aux = findIdp(ide, idp);
		if(aux != -1){
			e[ide].peso -= e[ide].produto[aux].encomendas * pdt[idp].peso;
			pdt[idp].stock +=  e[ide].produto[aux].encomendas;
			/*puxa todos os produtos de maior indice que o produto a remover para a
			esquerda a nao ser que o produto a remover seja o ultimo
			diminui o numero de produtos encomendados se o produto for ou nao o ultimo*/
			if(aux != --e[ide].nr_produtos_encomendados){
				for(i = aux; i < e[ide].nr_produtos_encomendados; i++){
					e[ide].produto[i] = e[ide].produto[i + 1]; 
				}
			}
		}
	}
}

/*funcao que calcula o custo de uma encomenda*/
void C(){
	int ide, i, custo = 0;
	scanf(" %d", &ide);
	if(ide >= nr_encomendas){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	}
	else{
		for(i = 0; i < e[ide].nr_produtos_encomendados; i++){
			custo += e[ide].produto[i].encomendas * pdt[e[ide].produto[i].idp].preco;
		}
		printf("Custo da encomenda %d %d.\n", ide, custo);
	}
}

/*funcao que lista a descricao e a quantidade de um produto numa encomenda*/
void E(){
	int ide, idp, aux;
	scanf(" %d:%d", &ide, &idp);
	if(ide >= nr_encomendas){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
	else if(idp >= nr_produtos){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	}
	else{
		aux = findIdp(ide, idp);
		if(aux != -1){
			printf("%s %d.\n", pdt[idp].descricao, e[ide].produto[aux].encomendas);
		}
		/*caso o produto n esteja na encomenda a quantidade e 0*/
		else{
			printf("%s 0.\n", pdt[idp].descricao);
		}
	}
}

/*funcao que lista o indentificador da encomenda que um produto tem maior quantidade*/
void m(){
	int idp, i, aux, ide = -1, max = 0;/*max representa o maximo da quantidade de um produto
										de todas as encomendas*/
	scanf(" %d", &idp);
	if(idp >= nr_produtos){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	}
	for(i = 0; i < nr_encomendas; i++){
		aux = findIdp(i, idp);
		if(aux != -1){
			if(max < e[i].produto[aux].encomendas){
				/*se uma encomenda tiver maior quantidade grava o
				o identificador da encomenda em ide e atualiza o max*/
				ide = i;
				max = e[i].produto[aux].encomendas;
			}
		}
	}
	/*se o produto estiver em pelo menos uma encomenda*/
	if(ide != -1){
		printf("Maximo produto %d %d %d.\n", idp, ide, max);
	}
}

/*funcao auxiliar ao bubble sort*/
void swapL(int ide, int cont){
	produto_encomendado aux = e[ide].produto[cont];
	e[ide].produto[cont] = e[ide].produto[cont + 1];
	e[ide].produto[cont + 1] = aux;
}

/*funcao que lista os produtos de uma encomenda por ordem alfabetica*/
void L(){
	int ide, i, cont;
	scanf(" %d", &ide);
	if(ide >= nr_encomendas){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
	else{
		/*aplicacao do bubble sort*/
		for(i = 0; i < e[ide].nr_produtos_encomendados - 1; i++){
			for(cont = 0; cont < e[ide].nr_produtos_encomendados - i - 1; cont++){
				if(strcmp(pdt[e[ide].produto[cont].idp].descricao, pdt[e[ide].produto[cont + 1].idp].descricao) > 0){
					swapL(ide, cont);
				}
			}
		}
		printf("Encomenda %d\n", ide);
		for(i = 0; i < e[ide].nr_produtos_encomendados; i++){
			printf("* %s %d %d\n", pdt[e[ide].produto[i].idp].descricao, pdt[e[ide].produto[i].idp].preco, e[ide].produto[i].encomendas);
		}
	}
}

int main(){
	int c;
	while(1){
		c = getchar();
		switch(c){
			case 'a':
				a();
				break;
			case 'k':
				k();
				break;
			case 'q':
				q();
				break;
			case 'r':
				r();
				break;
			case 'p':
				p();
				break;
			case 'l':
				l();
				break;
			case 'N':
				N();
				break;
			case 'A':
				A();
				break;
			case 'K':
				K();
				break;
			case 'R':
				R();
				break;
			case 'C':
				C();
				break;
			case 'E':
				E();
				break;
			case 'm':
				m();
				break;
			case 'L':
				L();
				break;
			case 'x':
				return 0;
		}
	}
	return 0;
}