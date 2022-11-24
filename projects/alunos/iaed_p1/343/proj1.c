#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define NUM 64
#define Max_Prod 10000
#define Max_Enc 500

typedef struct produtos {
	char descricao[NUM];
	int preco;
	int peso;
	int qtd;
}produto;
produto storage[Max_Prod]; /*    Tabela dos produtos  */

typedef struct encomendas {
	produto artigos[Max_Prod];
	int preco_total;
	int peso_total;
	int cont_produtos;
	int prod_adic[Max_Prod];
}encomenda;
encomenda order[Max_Enc]; /*    Tabela das encomendas  */

/*
adiciona a um novo produto ao sistema
*/

void a(produto storage[Max_Prod], int idp)
{
	int cont = 0;
	char descript, lstdescript[NUM];
	getchar();
	while((descript=getchar())!=':')
	{
		lstdescript[cont++] = descript;
	}
	lstdescript[cont] = '\0';
	strcpy(storage[idp].descricao, lstdescript);
	scanf("%d:%d:%d", &storage[idp].preco, &storage[idp].peso, &storage[idp].qtd);
	printf("Novo produto %d.\n", idp);
}

/*
adiciona stock a um produto existente no sistema
*/

void q(produto storage[Max_Prod], int idp)
{
	int in_idp, new_stock;
	scanf("%d:%d", &in_idp, &new_stock);
	if(idp <= in_idp){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",in_idp);
	}
	else {
		storage[in_idp].qtd += new_stock;
}}

/*
remove stock a um produto existente
*/

void r(produto storage[Max_Prod], int idp)
{
	int in_idp, rem_stock;
	scanf("%d:%d", &in_idp, &rem_stock);
	if(idp <= in_idp){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n",in_idp);
	}
	else if((storage[in_idp].qtd - rem_stock) < 0){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", rem_stock, in_idp);
	}
	else {
		storage[in_idp].qtd -= rem_stock;
}}

/*
altera o preco de um produto existente no sistema
*/

void p(produto storage[Max_Prod], int idp, int ide, encomenda order[Max_Enc])
{
	int in_idp, new_preco;
	scanf("%d:%d", &in_idp, &new_preco);
	if(idp <= in_idp){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",in_idp);
	}
	else {
		size_t i;
		int ja_existe, c;
		for(c = 0; c <= ide; c++){
			for(i = 0; i < sizeof(order[c].prod_adic) / sizeof(order[c].prod_adic[0]); i++){
				if(order[c].prod_adic[i] == in_idp){
					ja_existe = 1;
				}
			}
			if(ja_existe == 1){
				order[c].artigos[in_idp].preco = new_preco;
				order[c].preco_total -= order[c].artigos[in_idp].preco * order[c].artigos[in_idp].qtd;
				order[c].preco_total += new_preco * order[c].artigos[in_idp].qtd;
			}
		}
		storage[in_idp].preco = new_preco;
}}

/*
cria uma nova encomenda
*/

void N(int ide)
{	
	printf("Nova encomenda %d.\n", ide);
}

/*
adiciona um produto a uma encomenda
*/

void A(encomenda order[Max_Enc], produto storage[Max_Prod], int ide, int idp)
{
	int in_ide, in_idp, in_qtd;
	scanf("%d:%d:%d", &in_ide, &in_idp, &in_qtd);
	if(ide <= in_ide){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", in_idp, in_ide);
	}
	else if (idp <= in_idp){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", in_idp, in_ide);
	}
	else if(storage[in_idp].qtd < in_qtd){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", in_idp, in_ide);
	}
	else if((storage[in_idp].peso * in_qtd + order[in_ide].peso_total) > 200){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", in_idp, in_ide);
	}
	else {
		size_t i;
		int ja_existe;
		for(i = 0; i < sizeof(order[in_ide].prod_adic) / sizeof(order[in_ide].prod_adic[0]); i++){
			if(order[in_ide].prod_adic[i] == in_idp){
				ja_existe = 1;
			}
		}
		if(ja_existe == 1){
			order[in_ide].peso_total += storage[in_idp].peso * in_qtd;
			order[in_ide].preco_total += storage[in_idp].preco * in_qtd;
			order[in_ide].artigos[idp].qtd += in_qtd;
			storage[in_idp].qtd -= in_qtd;
		}
		else{
			order[in_ide].peso_total += storage[in_idp].peso * in_qtd;
			order[in_ide].preco_total += storage[in_idp].preco * in_qtd;
			strcpy(order[in_ide].artigos[in_idp].descricao, storage[in_idp].descricao);
			order[in_ide].artigos[in_idp].preco = storage[in_idp].preco;
			order[in_ide].artigos[in_idp].peso = storage[in_idp].peso;
			order[in_ide].artigos[in_idp].qtd = in_qtd;
			order[in_ide].prod_adic[order[in_ide].cont_produtos] += in_idp;
			order[in_ide].cont_produtos++;
			storage[in_idp].qtd -= in_qtd;
		}
	}
}

/*
remove um produto de uma encomenda
*/

void R(int idp, int ide, encomenda order[Max_Enc], produto storage[Max_Prod])
{
	int in_ide, in_idp;
	scanf("%d:%d", &in_ide, &in_idp);
	if(ide <= in_ide){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", in_idp, in_ide);
	}
	else if (idp <= in_idp){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", in_idp, in_ide);
	}
	else {
		order[in_ide].peso_total -= order[in_ide].artigos[in_idp].peso * order[in_ide].artigos[in_idp].qtd;
		order[in_ide].preco_total -= order[in_ide].artigos[in_idp].preco * order[in_ide].artigos[in_idp].qtd;
		storage[in_idp].qtd += order[in_ide].artigos[in_idp].qtd;
		order[in_ide].artigos[in_idp].qtd = 0;
		order[in_ide].artigos[in_idp].preco = 0;
		order[in_ide].artigos[in_idp].peso = 0;

	}
}

/*
calcula o custo de uma encomenda
*/

void C(int ide, encomenda order[Max_Enc])
{
	int in_ide;
	scanf("%d", &in_ide);
	if(ide <= in_ide){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", in_ide);
	}
	else {
		printf("Custo da encomenda %d %d.\n", in_ide, order[in_ide].preco_total);
	}
}

/*
lista a descricao e a quantidade de um produto numa encomenda
*/

void E(int ide, int idp, encomenda order[Max_Enc])
{
	int in_ide, in_idp;
	scanf("%d:%d", &in_ide, &in_idp);
	if(ide <= in_ide){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", in_ide);
	}
	else if(idp <= in_idp){
		printf("Impossivel listar produto %d. Produto inexistente.\n", in_idp);
	}
	else {
		if(order[in_ide].artigos[in_idp].qtd != 0){
			printf("%s %d.\n", order[in_ide].artigos[in_idp].descricao, order[in_ide].artigos[in_idp].qtd);
	}
		else {
			printf("%s %d.\n", storage[in_idp].descricao, order[in_ide].artigos[in_idp].qtd);
		}
	}
}

/*
lista o identificador da encomenda em que o produto dado ocorre mais vezes.
*/

void m(int idp, int ide, encomenda order[Max_Enc])
{
	int in_idp;
	scanf("%d", &in_idp);
	if(idp <= in_idp){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", in_idp);
	}
	else {
		int mais_stock = 0, quantificador = 0, maior_ide = 0, c;
		size_t i;
		for(c = 0; c <= ide; c++){
			for(i = 0; i < sizeof(order[c].prod_adic) / sizeof(order[c].prod_adic[0]); i++){
				if(order[c].prod_adic[i] == in_idp){
					quantificador = order[c].artigos[in_idp].qtd;
				}}
					if(mais_stock < quantificador){
						mais_stock = quantificador;
						maior_ide = c;
				}
	}
		printf("Maximo produto %d %d %d.", in_idp, maior_ide, mais_stock);
	}
}



int main()
{
	char str;
	int idp = 0;
	int ide = 0; 
	while(str != 'x'){
		scanf("%c", &str); 
		if(str == 'a'){
			a(storage, idp);
			idp++;
		}
		if(str == 'q'){
			q(storage, idp);
		}
		if(str == 'r'){
			r(storage, idp);
		}
		if(str == 'p'){
			p(storage, idp, ide, order);
		}
		if(str == 'N'){
			N(ide);
			ide++;
		}
		if(str == 'A'){
			A(order, storage, ide, idp);
		}
		if(str == 'R'){
			R(idp, ide, order, storage);
		}
		if(str == 'C'){
			C(ide, order);
		}
		if(str == 'E'){
			E(ide, idp, order);
		}
		if(str == 'm'){
			m(idp, ide, order);
		}
	}
	return 0;
}
