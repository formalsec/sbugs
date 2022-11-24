#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>

#define MAXSTR 63
#define MAXENC 500
#define MAXPRD 10000
#define MAXPESO 200
#define MAXITENS 1000
/* Max de itens para a tabela itens em encomemda */

/*####################################################################################################################################################*/
/*																																					  */
/*																  #	# # # #	# #	#																	  */
/*																#				  #																	  */
/*															  #					    #																  */
/*															#	 Inicio do Programa	  #																  */
/*															  #						#																  */
/*																#				  #																	  */
/*																  #	# # # #	# #	#																	  */
/*																																					  */
/*####################################################################################################################################################*/

typedef struct produto
{
	int indentificador;
	/* Numero do prod*/
	char descricao[MAXSTR];
	/* Descircao dada */
	int preco;
	int peso;
	int qtd;

}produto;

/*####################################################################################################################################################*/

typedef struct itens
{
	int idp;
	/* Prd a que me refiro*/
	int qtd;
	/* Respectiva quantidade na encomenda */

}itens;

/*####################################################################################################################################################*/

typedef struct encomenda
{
	int N_enc;
	itens itens[MAXITENS];
	/* Lista com os respectivos produtos e as suas quantidades dadas pela struct itens */
	int marcador;
	/* Ate onde a lista itens foi preenchida */

}encomenda;

/*####################################################################################################################################################*/
/*			Objectivo : Recebe adiciona uma quantidade dada a um produto dado.																		  */
/*			Recebe : O produto a adicionar, a qtd a adicionar, lista dos produtos, idp para saber se p e valido	.									  */		
/*			Funcionamento : altera a lista P (Padc) aumentando a qtd de p.																			  */										
/*####################################################################################################################################################*/

void q(int p, int qtd, produto P[], int idp){

	if(P[p].indentificador != p || idp == 0){
		/* Se idp == 0 significa q nenhum produto foi inicializado */
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", p);
		return;
	}

	P[p].qtd += qtd;
	/* Adiciona */
}



/*####################################################################################################################################################*/
/*			Objectivo : Adiciona um produto a uma encomenda.																		  				  */
/*			Recebe : O numero da encomenda a adicionar, o numero do protudo a adicionar, a sua qtd a adicionar, lista dos produtos,lista das   		  */
/*					encomendas , idp e ide para verificacoes.									  													  */		
/*			Funcionamento : altera a lista P (Padc) diminuindo a qtd de p.	Altera a lista E aumentando qtd de um termo ou adicionando um novo.		  */										
/*####################################################################################################################################################*/

void A(int e, int p, int qtd, produto P[], encomenda E[], int ide, int idp){


	int peso_total = 0, i, j, produto_ja_existente = 0;

	if(E[e].N_enc != e || ide == 0){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",p,e);
		return;
	}
	if(P[p].indentificador != p || idp == 0){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",p,e);
		return;
	}
	if(P[p].qtd < qtd){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",p,e);
		return;
	}
	for(i = 0; i < E[e].marcador; i++){
		if(E[e].itens[i].qtd >= 0){
			peso_total += E[e].itens[i].qtd * P[E[e].itens[i].idp].peso;
			/* Ver qual e o peso total da Encomenda e. */
		}
	}
	peso_total += P[p].peso * qtd;
	/* Adcionar o novo peso */
	
	if(peso_total > MAXPESO){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",p,e);
		return;
	}

	for(i = 0; i < E[e].marcador; i++){
		if(E[e].itens[i].idp == p && E[e].itens[i].qtd >= 0){
			/* Verificar se p ja esta em e*/
			produto_ja_existente = 1;
			j = i;
			/* Esta! marca onde */
	 	}
	}

	if(produto_ja_existente == 0){
		E[e].itens[E[e].marcador].idp = p;
		E[e].itens[E[e].marcador].qtd = qtd;
		P[p].qtd -= qtd;
		E[e].marcador += 1;
		/* N estava cria um novo, aumenta marcador de e para verificacoes posteriores */
		/* Diminui o q tiraste de p */
	}

	else{
		E[e].itens[j].qtd += qtd;
		P[p].qtd -= qtd;
		/* Havia, aumenta em e e diminui em p */
	}

}


/*####################################################################################################################################################*/
/*			Objectivo : Receber um produto e uma qtd e retirar essa qtd do produto.																	  */
/*			Recebe : Recebe um produto, a sua qtd, a lista dos produtos e o idp (IDP).									     						  */		
/*			Funcionamento : altera a lista P (Padc) removendo qtd de p.																				  */										
/*####################################################################################################################################################*/

void r(int idp, int qtd, produto P[], int IDP){

	int total;
	if(P[idp].indentificador == idp && IDP != 0){
	/*Garantir q existe*/
		total = P[idp].qtd - qtd;
		if(total >= 0){
			P[idp].qtd = total;
			/* Altera p */
		}
		else{
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd, idp);
		}

	}
	else{
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	}

}

/*####################################################################################################################################################*/
/*			Objectivo : Remove um produto de uma encomenda.																	  						  */
/*			Recebe : Recebe uma encomenda, um produto, os seus vectores, ide e idp).									     						  */		
/*			Funcionamento : Remove o produto p da encomenda e (remove em E[e].itens), colocando a sua qtd a -1, devolve a stock de p a antiga qtd.	  */										
/*####################################################################################################################################################*/


void R(int e, int p, encomenda E[], produto P[], int ide, int idp){

	int i;
	if (E[e].N_enc != e || ide == 0){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",p,e);
		return;
	}
	if (P[p].indentificador != p || idp == 0){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",p,e);
		return;
	}
	for(i = 0; i < E[e].marcador; i++){
		/* Onde esta o p na encomenda e */
		if(E[e].itens[i].idp == p && E[e].itens[i].qtd >= 0){
			P[p].qtd += E[e].itens[i].qtd;
			/* Devolve o stock a p */
			E[e].itens[i].qtd = -1;
			/* Inutilizavel agora */
			}
	}

}

/*####################################################################################################################################################*/
/*			Objectivo : Calcular o custo total de uma encomenda.																	  				  */
/*			Recebe : Recebe uma encomenda, lista de encomendas, lista de produtos, ide.									     						  */		
/*			Funcionamento : Calcula a soma de todos os precos dos produtos das encomendas de e.			  											  */										
/*####################################################################################################################################################*/


void C(int e, encomenda E[], produto P[], int ide){

	int soma = 0,i;
	if(E[e].N_enc == e || ide == 0){
		for(i = 0; i <	E[e].marcador; i++){
			/* Percorres os produtos de e */
			if(E[e].itens[i].qtd >= 0){
				soma += P[E[e].itens[i].idp].preco * E[e].itens[i].qtd;
				/* Adiciona o preco de um produto de e * a sua qtd em e */
			}

		}
		printf("Custo da encomenda %d %d.\n",e,soma);
	}
	else{
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", e);
	}
}


/*####################################################################################################################################################*/
/*			Objectivo : Alterar um preco de um produto.																	  				  			  */
/*			Recebe : Recebe um produto, preco p, lista de produtos, idp.									     						  			  */		
/*			Funcionamento : Altera na tabela P , o preco do produto			  												 						  */										
/*####################################################################################################################################################*/


void p(int idp, int p, produto P[], int IDP){

	if(P[idp].indentificador == idp || IDP == 0){
		P[idp].preco = p;
	}
	else{
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	}
}


/*####################################################################################################################################################*/
/*			Objectivo : Lista a descricao e a qtd de um produto p numa encomenda e.										  				  			  */
/*			Recebe : Recebe uma encomenda , um produto, Lista de produtos, lista de encomendas, ide e idp.								  			  */		
/*			Funcionamento : Encontrar p em e, e printar a sua descricao e qtd. Se o produto n se encontrar em e print qtd = 0						  */										
/*####################################################################################################################################################*/


void E(int e, int p, produto P[], encomenda E[], int ide, int idp){

	int i;
	if(E[e].N_enc != e || (ide == 0)){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",e);
		return;
	}
	if(P[p].indentificador != p || idp == 0){
		printf("Impossivel listar produto %d. Produto inexistente.\n", p);
		return;
	}
	for(i = 0; i < E[e].marcador;i++){
		if( E[e].itens[i].idp == p && E[e].itens[i].qtd >= 0){
			/* Encontrar um p valido em e (sendo q p pode ter sido eleminado anteriormente, e o primeiro teria qtd = -1) */
			printf("%s %d.\n", P[p].descricao, E[e].itens[i].qtd);
			return;
		}
	}
	printf("%s %d.\n", P[p].descricao, 0);
	return;
}


/*####################################################################################################################################################*/
/*			Objectivo : Listar em que encomenda um produto ocorre mais vezes.										  				  				  */
/*			Recebe : Recebe um produto, ide (e), lista de encomendas e produtos, e idp (IDP).											  			  */		
/*			Funcao : Percorre todas as encomendas (ate ide (e)) e ,marca as suas qtd, aquele q possuir mais ? printado.								  */										
/*####################################################################################################################################################*/	


void m(int idp, int e, encomenda E[], produto P[], int IDP){

	int i,j, IDE = 0, QTD = 0, Ocorrencia = 0;
	/* QTD = maior qtd, IDE = encomenda com p em maior qtd */
	if(idp != P[idp].indentificador || IDP == 0){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
		return;
	}
	for(i = 0; i < e; i++){
		/* Percorre as encomendas, lista E */
		for(j = 0; j < E[i].marcador; j++){
			/*Percorre os produtos dessa encomenda */
			if(E[i].itens[j].idp == P[idp].indentificador){
				if(E[i].itens[j].qtd > QTD){
					QTD = E[i].itens[j].qtd;
					IDE = i;
					Ocorrencia = 1;
					/* Ha pelo menos um produto numa encomenda*/
				}
				else if(E[i].itens[j].qtd == QTD){
					/* Garantir que a encomenda com menor numero de identificacao e que e print */
					if(E[i].N_enc < IDE){
						QTD = E[i].itens[j].qtd;
						IDE = i;
						Ocorrencia = 1;
						/* Ha pelo menos um produto numa encomenda*/
					}
				}
			}
		}
	}
	if(Ocorrencia != 0){printf("Maximo produto %d %d %d.\n", idp, IDE, QTD);}
	/* Houve um? print */
}


/*####################################################################################################################################################*/
/*			Funcao auxiliar de mergesort.									  				  				 	 									  */
/*			Recebe: A lista a ordenar, inicio, meio, fim, lista P.																		  			  */		
/*			Funcionamento: Ordena a lista de numeros inteiros (idp de produtos) basiando no seu preco e na sua posicao relativa na lista prod.		  */										
/*####################################################################################################################################################*/

void merge(int a[], int l, int m, int r, produto P[]){

	int i, j, k;
	int aux[MAXPRD];
	for (i = m+1; i > l; i --){
		aux[i -1] = a[i -1];
	}
	for (j = m; j < r; j ++){
		aux[r+m-j] = a[j+1];
	}
	for(k = l; k <= r; k++){
		if(P[aux[j]].preco < P[aux[i]].preco)
			/* Comparar o preco ,do inteiro (que representa um prd) */
			a[k] = aux[j--];
		else if(P[aux[j]].preco == P[aux[i]].preco){
			/* Garantir que e estavel */
			if(P[aux[j]].indentificador < P[aux[i]].indentificador)
				a[k] = aux[j--];
			else
				a[k] = aux[i++];
		}
		else
			a[k] = aux[i++];
	}
}

/*####################################################################################################################################################*/
/*			Funcao auxiliar de l.									  				  				 	 									  		  */
/*			Recebe: A lista a ordenar, inicio, fim, lista P.																		  			   	  */		
/*			Funcionamento: Divide a lista, para esta ser organizada pela sua aux.		  															  */										
/*####################################################################################################################################################*/

void mergesort(int a[], int l, int r, produto P[]){

	int m = (r+l)/2;
	/* Encontrar o meio */

	if(r <= l)
		return;
	mergesort(a, l, m, P);
	mergesort(a, m+1, r, P);
	merge(a, l, m ,r, P);

}

/*####################################################################################################################################################*/
/*			Objectivo : Printar a lista de todos os produtos ordenada pelo seu respectivo custo.									  				  */
/*			Aux: mergesort, merge. 																													  */
/*			Recebe : Lista de produtos, idp											  			  													  */		
/*			Funcao : Passa os indentificadores de P (idp) para um vector aux e organiza-os com as suas funcoes aux. Printa o vector.				  */
/*			Algoritmo utilizado : mergesort																											  */
/*####################################################################################################################################################*/


void l(produto P[], int idp){

	int P2[MAXPRD], i;

	for(i = 0; i < idp; i++){
		P2[i] = P[i].indentificador;
	}
	/* Passar os numeros dos produtos da lista P para a auxliar a ser organizada */
	mergesort(P2, 0, idp-1, P);

	printf("Produtos\n");

	for (i = 0; i < idp; i++){
		printf("* %s %d %d\n",P[P2[i]].descricao, P[P2[i]].preco, P[P2[i]].qtd);
	}
	/* Print resultado */

}

/*####################################################################################################################################################*/
/*			Funcao auxiliar de merge2.									  				  				 	 									  	  */
/*			Recebe: Duas listas de caracteres.																		  			  					  */		
/*			Funcionamento: Determinar qual das listas (A, B) vem primeiro em ordem alfabetica. Se for A , return 0. Se for B, return 1.	  			  */										
/*####################################################################################################################################################*/

int Alphabetic(char A[], char B[]){

	int a, b, termina = 0;
	while(termina < MAXSTR){
		a = A[termina];
		b = B[termina];
		/*Passar os caracteres para inteiros para comparacao */
		if (a < b){
			termina = MAXSTR;
			/* Termina ciclo */
			return 0;
		}
		else if (a > b){
			termina = MAXSTR;
			/* Termina ciclo */
			return 1;
		}
		else
			termina += 1;
	}
	return 0;
	/* Se forem iguais considero A primeiro*/

}

/*####################################################################################################################################################*/
/*			Funcao auxiliar de mergesort.									  				  				 	 									  */
/*			Recebe: A lista a ordenar, inicio, meio, fim, lista P.																		  			  */		
/*			Funcionamento: Ordena a lista de numeros inteiros (idp de produtos) basiando no seu posicionamento alfabetico 							  */
/*							(respectiva descicao do prd).		  																					  */										
/*####################################################################################################################################################*/
void merge2(itens a[], int l, int m, int r, produto P[]){

	int i, j, k;
	itens aux[MAXPRD];
	for (i = m+1; i > l; i --){
		aux[i -1].idp = a[i -1].idp;
		aux[i -1].qtd = a[i -1].qtd;
	}
	for (j = m; j < r; j ++){
		aux[r+m-j].idp = a[j+1].idp;
		aux[r+m-j].qtd = a[j+1].qtd;
	}
	for(k = l; k <= r; k++){
		if(Alphabetic(P[aux[j].idp].descricao,P[aux[i].idp].descricao) == 0){
		/* Funcao entre A e B string para ver quem e o "maior" alfabeticamente */
			a[k].idp = aux[j].idp;
			a[k].qtd = aux[j].qtd;
			j -= 1;
		}
		else{
			a[k].idp = aux[i].idp;
			a[k].qtd = aux[i].qtd;
			i += 1;
		}
	/* NOTA : Apenas passo idp e qtd pois e o necessario para printar */
	}
}

/*####################################################################################################################################################*/
/*			Funcao auxiliar de l.									  				  				 	 									  		  */
/*			Recebe: A lista a ordenar, inicio, fim, lista P.																		  			   	  */		
/*			Funcionamento: Divide a lista, para esta ser organizada pela sua aux.		  															  */										
/*####################################################################################################################################################*/

void mergesort2(itens a[], int l, int r, produto P[]){

	int m = (r+l)/2;

	if(r <= l)
		return;
	mergesort2(a, l, m, P);
	mergesort2(a, m+1, r, P);
	merge2(a, l, m ,r, P);

}

/*####################################################################################################################################################*/
/*			Objectivo : Printar a lista de produtos numa encomenda por ordem alfabetica.									  				     	  */
/*			Aux: mergesort2, merge2. 																												  */
/*			Recebe : Lista de produtos, lista de encomendas, encomenda e, ide.																		  */		
/*			Funcao : Passa os indentificadores de P (idp) e a qtd em e para um vector aux e organiza-os com as suas funcoes aux. Printa o vector.	  */
/*			Algoritmo utilizado : mergesort																											  */
/*####################################################################################################################################################*/



void L(produto P[], encomenda E[], int e, int ide){

	itens E2[MAXPRD];
	/* Uso itens pq necessito de manter guardada a sua qtd na encomenda */
	int i,j = 0;

	if(e != E[e].N_enc || ide == 0){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", e);
		return;
	}

	for(i = 0; i < E[e].marcador; i++){
		if(E[e].itens[i].qtd >= 0){
			E2[j].idp = E[e].itens[i].idp;
			E2[j].qtd = E[e].itens[i].qtd;
			j += 1;
		}
	/* Introduzir produtos validos */	
	}

	mergesort2(E2, 0, j - 1, P);

	printf("Encomenda %d\n", e);
	for (i = 0; i < j; i ++){
		printf("* %s %d %d\n", P[E2[i].idp].descricao, P[E2[i].idp].preco, E2[i].qtd);
	}
}


/*####################################################################################################################################################*/
/*																																					  */
/*		OBSERVACOES: idp e ide corresponde ao ultimo local preenchido +1 no vector Padc e Encomendas, respectivamente.								  */
/*																																					  */
/*####################################################################################################################################################*/

int main(){

	int FIM = 0,idp = 0,ide = 0, l1, l2, l3;
	/* idp e ide terao o valor do proximo elemento a entrar ou seja, por exemplo, para o 4 produto feito idp = 5 quando fizer a.*/
	char X;
	struct encomenda Encomenda[MAXENC];	
	struct produto Padc[MAXPRD];


	scanf("%c", &X);
	/* Procuro o primeiro caracter */
	while (FIM == 0){
		switch(X){

			case 'a':
				Padc[idp].indentificador = idp;
				/* Numero do produto */
				scanf(" %[^:]:%d:%d:%d\n",Padc[idp].descricao,&Padc[idp].preco,&Padc[idp].peso,&Padc[idp].qtd);
				/* Dar a descricao, preco e peso ao novo prodtuto */
				printf("Novo produto %d.\n", Padc[idp].indentificador);
				idp += 1;
				/* Marcador +1 */
				break;

			case 'q':
				l2 = 0;
				scanf(" %d:%d\n", &l1, &l2);
				q(l1, l2, Padc, idp);
				break;

			case 'N':
				Encomenda[ide].N_enc = ide;
				Encomenda[ide].marcador = 0;
				/* Novo encomenda sem produtos, lista 0 */
				printf("Nova encomenda %d.\n",Encomenda[ide].N_enc);
				ide += 1;
				/* Marcador +1 */
				break;

			case 'A':
				scanf(" %d:%d:%d\n",&l1,&l2,&l3);
				A(l1, l2, l3, Padc, Encomenda, ide, idp);
				/*Chama funcao*/
				break;

			case 'r':
				scanf(" %d:%d\n", &l1, &l2);
				r(l1,l2,Padc, idp);
				/*Chama funcao*/
				break;

			case 'R':
				scanf(" %d:%d\n",&l1, &l2);
				R(l1,l2,Encomenda, Padc, ide, idp);
				/*Chama funcao*/
				break;

			case 'C':
				scanf(" %d\n",&l1);
				C(l1, Encomenda, Padc, ide);
				/*Chama funcao*/
				break;

			case 'p':
				scanf(" %d:%d\n",&l1,&l2);
				p(l1, l2, Padc, idp);
				/*Chama funcao*/
				break;

			case 'E':
				scanf(" %d:%d\n", &l1,&l2);
				E(l1, l2, Padc, Encomenda, ide, idp);
				/*Chama funcao*/
				break;

			case 'm':
				scanf(" %d\n", &l1);
				m(l1, ide, Encomenda, Padc, idp);
				/*Chama funcao*/
				break;

			case 'l':
				l(Padc, idp);
				/*Chama funcao*/
				break;

			case 'L':
				scanf(" %d\n", &l1);
				L(Padc, Encomenda, l1, ide);
				/*Chama funcao*/
				break;

			case 'x':
				FIM = 1;
				/* Acaba o ciclo e o programa*/
				break;

		}
	scanf("%c", &X);
	/* Proximo comando */
	}
	return 0;
}
