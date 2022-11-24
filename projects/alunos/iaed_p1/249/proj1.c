#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXDESC 64 /*tamanho maximo da string de descricao de um produto*/
#define MAXENC 500 /*numero maximo de encomendas*/
#define MAXPROD 10000 /*numero maximo de produtos*/
#define MAXPESO 200 /*numero maximo de peso por encomenda*/
#define VAZIO -1 /*constante usada para verificar se um idp ou ide e valido*/

/*DEFINICOES DE ESTRUTURAS "PRODUTO" E "ENCOMENDA"*/

typedef struct {
	int idp;
	char desc[MAXDESC];
	int preco;
	int peso;
	int stock;
} Produto;

typedef struct {
	int ide;
	Produto vetor[MAXENC];
} Encomenda;

/*VARIAVEIS GLOBAIS*/

Produto sistemaprod[MAXPROD];	/*vetor onde serao guardados todos os produtos do sistema*/

Produto prodvazio = { -1, " ", 0, 0, 0};	/*este produto representa um produto de existencia impossivel*/

Encomenda sistemaenc[MAXENC];	/*vetor onde serao guardadas todas as encomendas do sistema*/

/*FUNCOES AUXILIARES*/

/*initprod(vetorprod) serve para preencher o sistema com prodvazio, representarao posicoes vazias do vetor
? passado o argumento vetorprod ao inv?s de se atuar diretamente sobre o sistemaprod acima definido porque
esta mesma funcao sera usada num vetor de produtos auxiliar mais a frente.*/
void initprod(Produto vetorprod[]) {
	int i;
	for (i = 0; i < MAXPROD; i++) {
		vetorprod[i] = prodvazio;
	}
}

/*encvazia() cria uma encomenda de existencia impossivel*/
Encomenda encvazia() {
	Encomenda enc;
	int i;
	enc.ide = -1;
	for (i = 0; i < 200; i++) {
		enc.vetor[i] = prodvazio;
	}
	return enc;
}

/*initenc() serve para preencher o vetor que contem todas as encomendas com "posicoes vazias"*/
void initenc() {
	int i;
	for (i = 0; i < MAXENC; i++) {
		sistemaenc[i] = encvazia();
	}
}

/*eixsteProd(idp) verifica se existe algum produto com o idp indicado registado no sistema*/
int existeProd(int idp) {
	int i;
	for (i = 0; i < MAXPROD; i++) {
		if (sistemaprod[i].idp == idp) {
			return 1;
		}
	}
	return 0;
}

/*existeEnc(ide) verifica se existe alguma encomenda com o ide indicado registada no sistema*/
int existeEnc(int ide) {
	int i;
	for (i = 0; i < MAXENC; i++) {
		if (sistemaenc[i].ide == ide) {
			return 1;
		}
	}
	return 0;
}

/*pesoEnc(ide) devolve o valor do peso da encomenda ide*/
int pesoEnc(int ide) {
	int i = 0, peso = 0;
	while (i < MAXPESO && sistemaenc[ide].vetor[i].idp != -1) {
		peso += sistemaenc[ide].vetor[i].peso*sistemaenc[ide].vetor[i].stock;
		i++;
	}
	return peso;
}

/*merge e mergesort sao funcoes de ordenacao que vao ser usadas no comando l, pois mergesort e um algoritmo estavel e mantem a ordem entre produtos no sistema*/
void merge(Produto a[], int l, int m, int r) {
	Produto aux[MAXPROD];
	int i, j, k;
	for (i = m+1; i > l; i--) {
		aux[i-1] = a[i-1];
	}
	for (j = m; j < r; j++) {
		aux[r+m-j] = a[j+1];
	}
	for (k = l; k <= r; k++) {
		if ((aux[j].preco < aux[i].preco) || i > m) { /*produto com menor preco*/
			a[k] = aux[j--];
		}
		else {
			a[k] = aux[i++];
		}
	}
}

void mergesort(Produto a[], int l, int r) {
	int m = (r+l)/2;
	if (r <= l) {
		return;
	}
	mergesort(a, l, m);
	mergesort(a, m+1, r);
	merge(a, l, m, r);
}

/*partition e quicksort sao funcoes de ordenacao que vao ser usadas no comando L, pois quicksort e um algoritmo de ordenacao rapido e eficiente e nao e exigida estabilidade neste caso*/
int partition(Produto a[], int l, int r) {
	int i = l-1;
	int j = r;
	Produto v = a[r], t;
	while (i < j) {
		while (strcmp(a[++i].desc, v.desc) < 0);
		while (strcmp(v.desc, a[--j].desc) < 0) {
			if (j == l) {
				break;
			}
		}
		if (i < j) {
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	t = a[i];
	a[i] = a[r];
	a[r] = t;
	return i;
}

void quicksort(Produto a[], int l, int r) {
	int i;
	if (r <= l) {
		return;
	}
	i = partition(a, l, r);
	quicksort(a, l, i-1);
	quicksort(a, i+1, r);
}

/*COMANDOS*/



/*a(): funcao que processa o comando a adicionando o produto dado ao sistemaprod, associando-o
ao primeito idp disponivel*/
void a() {
	int c, i = 0, j = 0;
	char desc[MAXDESC];
	while (i < MAXPROD && sistemaprod[i].idp != VAZIO) { /*ciclo que define qual o idp do novo produto*/
		i++;
	}
	sistemaprod[i].idp = i;
	getchar(); /*para ignorar o espaco (' ') que existe no comando a segundo a formatacao esperada*/
	while ((c = getchar()) != ':' && j < MAXDESC-1) {
		desc[j] = c;
		j++;
	}
	desc[j] = '\0';
	memcpy(sistemaprod[i].desc, desc, strlen(desc)+1); 
	scanf("%d:%d:%d", &sistemaprod[i].preco, &sistemaprod[i].peso, &sistemaprod[i].stock);
	printf("Novo produto %d.\n", i);
}

/*q(): funcao que processa o comando q, adicionando a quantidade indicada ao stock do produto indicado*/
void q() {
	int idp, qtd;
	scanf(" %d:%d", &idp, &qtd);
	if (existeProd(idp)) {
		sistemaprod[idp].stock += qtd;
	}
	else {
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	}
}

/*N(): funcao que processa o comando N, criando uma nova encomenda associada ao primeiro ide disponivel*/
void N() {
	int i = 0;
	while (i < MAXENC && sistemaenc[i].ide != VAZIO) { /*ciclo que define qual o ide da nova encomenda*/
		i++;
	}
	sistemaenc[i].ide = i;
	printf("Nova encomenda %d.\n", i);
}

/*A(): funcao que processa o comando A, comecando por verificar se existem a encomenda e o produto
indicados, seguidamente se existe quantidade suficiente e se o peso maximo de uma encomenda nao e excedido.
caso todas as condicoes se verifiquem adiciona a quantidade indicada do produto a uma quantidade ja existente
na encomenda ou coloca o produto na encomenda pela primeira vez. em ambos os casos e retirada a mesma quantidade ao stock*/
void A() {
	int idp, ide, qtd, i = 0, encontrou = 0; /*encontrou funcionara como uma flag para verificar se ja existia o produto em causa na encomenda*/
	scanf(" %d:%d:%d", &ide, &idp, &qtd);
	if (existeEnc(ide)) { 
		if (existeProd(idp)) {
			if (sistemaprod[idp].stock >= qtd){
				if (pesoEnc(ide)+sistemaprod[idp].peso*qtd <= MAXPESO) { /*verifica se ao adicionar-se o produto a encomenda o peso limite ia ser excedido*/
					while (i < MAXPESO && sistemaenc[ide].vetor[i].idp != VAZIO && encontrou == 0) {
						if (sistemaenc[ide].vetor[i].idp == idp) {
							sistemaenc[ide].vetor[i].stock += qtd;
							sistemaprod[idp].stock -= qtd;
							encontrou = 1;
						}
						i++;
					}
					if (encontrou == 0) {
						sistemaenc[ide].vetor[i].idp = idp;
						memcpy(sistemaenc[ide].vetor[i].desc, sistemaprod[idp].desc, strlen(sistemaprod[idp].desc)+1);
						sistemaenc[ide].vetor[i].preco = sistemaprod[idp].preco;
						sistemaenc[ide].vetor[i].peso = sistemaprod[idp].peso;
						sistemaenc[ide].vetor[i].stock = qtd;
						sistemaprod[idp].stock -= qtd;
					}
				}
				else {
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
				}
			}
			else {
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
			}
		}
		else {
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		}
	}
	else {
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
}

/*r(): funcao que processa o comando r, comecando por verificar se existe o produto em questao e se e possivel retirar a quantidade indicada.
seguidamente, e retirada essa quantidade de produto ao stock*/
void r() {
	int idp, qtd;
	scanf(" %d:%d", &idp, &qtd);
	if (existeProd(idp)) {
		if (sistemaprod[idp].stock >= qtd) {
			sistemaprod[idp].stock -= qtd;
		}
		else {
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
		}
	}
	else {
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	}
}

/*R(): funcao que processa o comando R, comecando por verificar a existencia da encomenda e do produto indicados.
remove o produto da encomenda adicionando a quantidade que desse produto que la se encontra ao stock e colocandoa a quantidade
do produto a zero na encomenda*/
void R() {
	int ide, idp, i = 0, encontrou = 0;
	scanf(" %d:%d", &ide, &idp);
	if (existeEnc(ide)) {
		if (existeProd(idp)) {
			while (i < MAXPESO && sistemaenc[ide].vetor[i].idp != VAZIO && encontrou == 0) {
				if (sistemaenc[ide].vetor[i].idp == idp) {
					sistemaprod[idp].stock += sistemaenc[ide].vetor[i].stock;
					sistemaenc[ide].vetor[i].stock = 0;
					encontrou = 1;
				}
				i++;
			}
		}
		else {
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		}
	}
	else {
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
}

/*C(): funcao que processa o comando C, verificando se existe a encomenda em causa. caso exista, faz uma adicao em que cada parcela
corresponde ao multiplicado do preco pela quantidade na encomenda de cada produto*/
void C() {
	int ide, i = 0, custo = 0;
	scanf(" %d", &ide);
	if (existeEnc(ide)) {
		while (i < MAXPROD && sistemaenc[ide].vetor[i].idp != VAZIO) {
			custo += sistemaenc[ide].vetor[i].preco*sistemaenc[ide].vetor[i].stock;
			i++;
		}
		printf("Custo da encomenda %d %d.\n", ide, custo);
	}
	else {
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
	}
}

/*p(): funcao que processa o comando p(), verificando se existe o produto em causa. caso exista,
muda o seu preco no sistema, tanto no stock como em todas as encomendas das quais o produto faca parte.*/
void p() {
	int idp, preco, i = 0, j, encontrou;
	scanf(" %d:%d", &idp, &preco);
	if (existeProd(idp)) {
		sistemaprod[idp].preco = preco;
		while (i < MAXENC && sistemaenc[i].ide != VAZIO) {
			j = 0;
			encontrou = 0;
			while (j < MAXPESO && sistemaenc[i].vetor[j].idp != -1 && encontrou == 0) {
				if (sistemaenc[i].vetor[j].idp == idp) {
					sistemaenc[i].vetor[j].preco = preco;
					encontrou = 1;
				}
				j++;
			}
			i++;
		}
	}
	else {
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	}
}

/*E(): verifica se existem a encomenda e o produto indicados. depois, lista a descricao e a quantidade do produto na encomenda.
caso o produto nao se encontre na encomenda, e listada a sua descricao e a quantidade e igual a zero*/
void E() {
	int ide, idp, i = 0, qtd = 0;
	scanf(" %d:%d", &ide, &idp);
	if (existeEnc(ide)) {
		if (existeProd(idp)) {
			while (i < MAXPESO && sistemaenc[ide].vetor[i].idp != VAZIO) {
				if (sistemaenc[ide].vetor[i].idp == idp) {
					qtd = sistemaenc[ide].vetor[i].stock;
					break;
				}
				i++;
			}
			printf("%s %d.\n", sistemaprod[idp].desc, qtd);
		}
		else {
			printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
		}
	}
	else {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
}

/*m(): comeca por verificar a existencia do produto no sistema, depois procura a encomenda onde o produto esta em maior quantidade.
caso duas encomendas tenham a mesma quantidade, prevalece a de menor ide*/ 
void m() {
	int idp, qtd = 0, ide, i = 0, j, encontrou;
	scanf(" %d", &idp);
	if (existeProd(idp)) {
		while (i < MAXENC && sistemaenc[i].ide != VAZIO) {
			j = 0;
			encontrou = 0;
			while (j < MAXPESO && sistemaenc[i].vetor[j].idp != VAZIO && encontrou == 0) {
				if (sistemaenc[i].vetor[j].idp == idp) {
					if (sistemaenc[i].vetor[j].stock > qtd) { /*e usado > e nao >= porque assim a encomenda que prevalece e a de menor ide*/
						qtd = sistemaenc[i].vetor[j].stock;
						ide = i;
					}
					encontrou = 1;
				}
				j++;
			}
			i++;
		}
		if (qtd != 0) {
			printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
		}
	}
	else {
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	} 
}

/*l(): lista os produtos do sistema por ordem crescente de preco recorrendo ao mergesort. casos dois produtos tenham o mesmo preco prevalece o de menor id*/
void l() {
	int i = 0;
	Produto sistemaaux[MAXPROD];
	initprod(sistemaaux);
	while (i < MAXPROD && sistemaprod[i].idp != VAZIO) {
		sistemaaux[i].idp = sistemaprod[i].idp;
		memcpy(sistemaaux[i].desc, sistemaprod[i].desc, strlen(sistemaprod[i].desc)+1);
		sistemaaux[i].preco = sistemaprod[i].preco;
		sistemaaux[i].peso = sistemaprod[i].peso;
		sistemaaux[i].stock = sistemaprod[i].stock;
		i++;
	}
	mergesort(sistemaaux, 0, i-1);
	i = 0;
	printf("Produtos\n");
	while (i < MAXPROD && sistemaaux[i].idp != VAZIO) {
		printf("* %s %d %d\n", sistemaaux[i].desc, sistemaaux[i].preco, sistemaaux[i].stock);
		i++;
	}
}

/*L(): comeca por verificar se existe a encomenda indicada. seguidamente, lista os produtos dessa encomenda por ordem alfabetica recorrendo ao quicksort*/
void L() {
	int ide, i = 0;
	scanf(" %d", &ide);
	if (existeEnc(ide)) {
		while (i < MAXPESO && sistemaenc[ide].vetor[i].idp != VAZIO) {
			i++;
		}
		quicksort(sistemaenc[ide].vetor, 0, i-1);
		i = 0;
		printf("Encomenda %d\n", ide);
		while (i < MAXPESO && sistemaenc[ide].vetor[i].idp != VAZIO) {
			if (sistemaenc[ide].vetor[i].stock != 0) {
				printf("* %s %d %d\n", sistemaenc[ide].vetor[i].desc, sistemaenc[ide].vetor[i].preco, sistemaenc[ide].vetor[i].stock);
			}
			i++;
		}
	}
	else {
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
}

/*main(): a funcao main comeca por inicializar o vetor que contem todos os produtos registados no sistema
e o vetor que contem todas as encomendas do sistema. o programa corre continuamente ate ser interrompido pelo comando x.
cada ciclo le a primeira letra do comando para identificar o que fazer de seguida, chamando a funcao responsavel por processar
cada comando*/
int main() {
	int c;
	initprod(sistemaprod);
	initenc();
	while ((c = getchar()) != EOF) {
		if (c == 'a') {
			a();
		}
		if (c == 'q') {
			q();
		}
		if (c == 'N') {
			N();
		}
		if (c == 'A') {
			A();
		}
		if (c == 'r') {
			r();
		}
		if (c == 'R') {
			R();
		}
		if (c == 'C') {
			C();
		}
		if (c == 'p') {
			p();
		}
		if (c == 'E') {
			E();
		}
		if (c == 'm') {
			m();
		}
		if (c == 'l') {
			l();
		}
		if (c == 'L') {
			L();
		}
		if (c == 'x') {
			exit(0);
		}
	}
	return 0;
}