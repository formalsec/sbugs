#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

#define MAX_PESO 200
#define MAX_INPUT 200

int produtosAtuais=0;
int encomendasAtuais=0;

int  merge1Aux[MAX_PRODUTOS], merge2Aux[MAX_PRODUTOS], temp[MAX_PRODUTOS];
Produto produtos[MAX_PRODUTOS];
Encomenda encomendas[MAX_ENCOMENDAS];


/*#####################################################################*/
/*	FUNCOES                                                            */
/*#####################################################################*/

int __a__(){

	Produto novoProduto;
	char* token;
	char input[MAX_INPUT];
	int c, i;

	c=getchar();	/* remove o espaco entre o 'a' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';

	token=strtok(input, ":");
	strcpy(novoProduto.descricao, token); 	/* preenche o campo "descricao" */

	token=strtok(NULL, ":");
	novoProduto.preco=atoi(token);			/* preenche o campo "preco" */

	token=strtok(NULL, ":");
	novoProduto.peso=atoi(token);			/* preenche o campo "peso" */

	token=strtok(NULL, ":");
	novoProduto.quantidade=atoi(token);		/* preenche o campo "quantidade" */

	novoProduto.idp=produtosAtuais;	/* preenche o campo "idp" */

	novoProduto.pCriado=1;			/* mete o produto ativo */

	produtosAtuais ++;				/* atualiza o numero de Produtos */

	produtos[novoProduto.idp] = novoProduto;	/* adiciona o novo Produto ao vetor de Produtos */

	printf("Novo produto %d.\n", novoProduto.idp);

	return 0;
}


int __q__(){

	int i, c, _idp, _quantidade;
	char input[MAX_INPUT];
	char* token;

	c=getchar();	/* remove o espaco entre o 'q' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';

	token=strtok(input, ":");	
	_idp=atoi(token);				/* guarda o valor "idp" */

	token=strtok(NULL, ":");
	_quantidade=atoi(token);		/* guarda o valor "quantidade" */

	if(_idp<produtosAtuais){
		produtos[_idp].quantidade+=_quantidade;		/* atualiza a quantidade em stock do produto */
		return 0;
	}
	else
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", _idp);		/* ERRRO: nao existe produto com o idp inserido */
	return 0;
}


int __N__(){

	Encomenda novaEncomenda;
	int i;

	novaEncomenda.ide=encomendasAtuais;				/* preenche o campo "ide" */
	novaEncomenda.pesoEnc=0;						/* preenche o campo "pesoEnc" */
	novaEncomenda.numberOfProds=0;					/* preenche o campo "numberOfProds" */
	novaEncomenda.eCriado=1;
	for(i=0;i<MAX_PRODUTOS;i++)						/* inicializo o vetor de produtos a 0 */
		novaEncomenda.prodsEnc[i]=0;

	encomendas[novaEncomenda.ide]=novaEncomenda;	/* adiciona uma nova encomenda ao vetor de Encomendas */
	encomendasAtuais++;								/* atualiza o numero de encomendas */

	printf("Nova encomenda %d.\n", novaEncomenda.ide);	

	return 0;
}


int __A__(){

	int i, c, _ide, _idp, _qtd;
	char input[MAX_INPUT];
	char* token;

	c=getchar();	/* remove o espaco entre o 'A' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';

	token=strtok(input, ":");
	_ide=atoi(token);			/* guarda o valor "ide" */

	token=strtok(NULL, ":");
	_idp=atoi(token);			/* guarda o valor "idp" */

	token=strtok(NULL, ":");
	_qtd=atoi(token);			/* guarda o valor "quantidade" */

	if(encomendas[_ide].eCriado!=1){		/* verifica se a encomenda existe */
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", _idp, _ide);
		return 0;
	}	

	if(produtos[_idp].pCriado!=1){		/* verifica se o produto existe */
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", _idp, _ide);	
		return 0;
	}

	if(produtos[_idp].quantidade<_qtd){	/* verifica se existe stock sufeciente do produto */
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", _idp, _ide);
		return 0;
	}	
		
	if((encomendas[_ide].pesoEnc+(_qtd*produtos[_idp].peso))>200){	/* verifica se ha excesso de peso  */	
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", _idp, _ide);
		return 0;
	}	

	if(encomendas[_ide].numberOfProds>0 && encomendas[_ide].prodsEnc[_idp]==0)	/* atualiza o numero de produtos na encomenda */
		encomendas[_ide].numberOfProds++;	
	encomendas[_ide].prodsEnc[_idp]+=_qtd;	/* atualiza o stock do produto na encomenda */
	encomendas[_ide].pesoEnc+=(_qtd*produtos[_idp].peso);	/* atualiza o peso da encomenda */			

	produtos[_idp].quantidade-=_qtd;		/* atualiza o stock total do produto */	

	return 0;
}


int __r__(){

	int i, c, _idp, _qtd;
	char input[MAX_INPUT];
	char* token;

	c=getchar();	/* remove o espaco entre o 'r' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';

	token=strtok(input, ":");
	_idp=atoi(token);		/* guarda o valor de "idp" */

	token=strtok(NULL, ":");
	_qtd=atoi(token);		/* guarda o valor de "quantidade" */

	if(produtos[_idp].pCriado!=1){		/* verifca se o produto existe */
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", _idp);
		return 0;
	}

	if(produtos[_idp].quantidade-_qtd<0){		/* verifica se apos a remocao de stock ainda ha stock disponivel */
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", _qtd, _idp);
		return 0;
	}

	produtos[_idp].quantidade-=_qtd;	/* remove quantidade ao produto */

	return 0;	
}


int __R__(){

	int i, c, _ide, _idp;
	char input[MAX_INPUT];
	char* token;

	c=getchar();	/* remove o espaco entre o 'R' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';

	token=strtok(input, ":");
	_ide=atoi(token);			/* guarda o valor de "ide" */

	token=strtok(NULL, ":");
	_idp=atoi(token);			/* guarda o valor de "idp" */

	if(encomendas[_ide].eCriado!=1){	/* verifica se a encomenda existe */
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", _idp, _ide);
		return 0;
	}

	if(produtos[_idp].pCriado!=1){		/* verifica se o produto existe */
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", _idp, _ide);	
		return 0;
	}

	encomendas[_ide].pesoEnc-=(encomendas[_ide].prodsEnc[_idp]*produtos[_idp].peso);	/* atualiza o peso da encomenda */
	encomendas[_ide].numberOfProds--;		/* atualiza o numero de produtos na encomenda */
	produtos[_idp].quantidade+=encomendas[_ide].prodsEnc[_idp];	/* devolve o stock do produto da encomenda ao stock geral do produto */
	encomendas[_ide].prodsEnc[_idp]=0;		/* remove o produto da encomenda */

	return 0;
}


int __C__(){

	int i, c, _ide, contadorPreco=0;
	char input[MAX_INPUT];
	char* token;

	c=getchar();	/* remove o espaco entre o 'C' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';

	token=strtok(input, "\0");
	_ide=atoi(token);			/* guarda o valor de "ide" */

	if(encomendas[_ide].eCriado!=1){	/* verifica se a encomenda existe */
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", _ide);
		return 0;
	}
	
	for(i=0;i<MAX_PRODUTOS;i++){
		if(encomendas[_ide].prodsEnc[i]>0)
			contadorPreco+=(produtos[i].preco*encomendas[_ide].prodsEnc[i]);	/* contabiliza o preco dos produtos */
	}

	printf("Custo da encomenda %d %d.\n", _ide, contadorPreco);

	return 0;
}


int __p__(){

	int i, c, _idp, _preco;
	char input[MAX_INPUT];
	char* token;

	c=getchar();	/* remove o espaco entre o 'p' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';

	token=strtok(input, ":");
	_idp=atoi(token);			/* guarda o valor de "idp" */

	token=strtok(NULL, ":");
	_preco=atoi(token);			/* guarda o valor do novo preco */

	if(produtos[_idp].pCriado!=1){		/* verifica se o produto existe */
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", _idp);
		return 0;
	}

	produtos[_idp].preco=_preco;	/* atualiza o preco do produto */

	return 0;
}


int __E__(){

	int i, c, _ide, _idp, contadorErros=0;
	char input[MAX_INPUT];
	char* token;

	c=getchar();	/* remove o espaco entre o 'E' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';

	token=strtok(input, ":");
	_ide=atoi(token);			/* guarda o valor de "ide" */

	token=strtok(NULL, ":");
	_idp=atoi(token);			/* guarda o valor de "idp" */

	if(encomendas[_ide].eCriado!=1){	/* verifica se a encomenda existe */
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", _ide);
		contadorErros++;
	}

	if(produtos[_idp].pCriado!=1){		/* verifica se o produto existe */
		printf("Impossivel listar produto %d. Produto inexistente.\n", _idp);	
		contadorErros++;
	}

	if(contadorErros>0)	return 0;	/* verifica se houve erros, se houve sai */

	printf("%s %d.\n", produtos[_idp].descricao, encomendas[_ide].prodsEnc[_idp]);

	return 0;
}


int __m__(){

	int i, c, _idp, _ide, _qtd=0;
	char input[MAX_INPUT];
	char* token;

	c=getchar();	/* remove o espaco entre o 'm' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';

	token=strtok(input, "\0");
	_idp=atoi(token);			/* guarda o valor de "idp" */

	if(produtos[_idp].pCriado!=1)		/* verifica se o produto existe */
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", _idp);

	for(i=0;i<MAX_ENCOMENDAS;i++){
		if(encomendas[i].eCriado==1){
			if(_qtd<encomendas[i].prodsEnc[_idp]){
				_qtd=encomendas[i].prodsEnc[_idp];	/* atualiza o valor da quantidade */
				_ide=i;								/* atualiza o valor da encomenda com o maior numero de produto */
			}
		}
	}

	if(_qtd!=0)			/* imprime so se existe alguma encomenda com o produto */
		printf("Maximo produto %d %d %d.\n", _idp, _ide, _qtd);	

	return 0;
}


int __l__(){

	int auxiliar[MAX_PRODUTOS];
	int i, tamanhoAux=0;
		
	for(i=0;i<MAX_PRODUTOS;i++){			
		if(produtos[i].pCriado==1){
			auxiliar[tamanhoAux]=i;		/* copia os indices dos protudos existentes para um vetor auxliar */
			tamanhoAux++;							/* tamanho do vetor auxiliar */
		}
	}

	mergesort1(auxiliar, 0, tamanhoAux-1);			/* ordena o vetor com o algoritmo eficiente MERGESORT */

	printf("Produtos\n");

	for(i=0;i<tamanhoAux;i++)
		printf("* %s %d %d\n", produtos[auxiliar[i]].descricao, produtos[auxiliar[i]].preco, produtos[auxiliar[i]].quantidade);

	return 0;
}


int __L__(){

	int i, c, _ide, tamanhoAux=0, temporario[MAX_PRODUTOS], auxiliar[MAX_PRODUTOS];
	char input[MAX_INPUT];
	char* token;

	c=getchar();	/* remove o espaco entre o 'L' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';

	token=strtok(input, "\0");	
	_ide=atoi(token);

	if(encomendas[_ide].eCriado!=1){			/* verifica se a encomenda existe */
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", _ide);		
		return 0;
	}

	for(i=0;i<MAX_PRODUTOS;i++){
		if(encomendas[_ide].prodsEnc[i]!=0){		
			auxiliar[tamanhoAux]=i;						/* copio os indice dos produtos presentes na encomenda para um vetor auxilar */
			temporario[tamanhoAux]=encomendas[_ide].prodsEnc[i];	/* copio todas as quantidades dos produtos presentes na encomenda para um vetor temporario */
			tamanhoAux++;
		}	
	}

	mergesort2(auxiliar, temporario, 0, tamanhoAux-1);		/* ordena os vetores auxiliares com o algoritmo eficiente MERGESORT */

	printf("Encomenda %d\n", _ide);

	for(i=0;i<tamanhoAux; i++){		/* percorre o vetor de produtos referente a encomenda */
		printf("* %s %d %d\n", produtos[auxiliar[i]].descricao, produtos[auxiliar[i]].preco, temporario[i]);
	}

	return 0;
}


void mergesort1(int a[], int l, int r){

	int m= (r+l)/2;			/* divide sucessivamente o vetor ao meio */

	if(r<=l) return;		/* condi??o de paragem */

	mergesort1(a, l, m);		/* recursao ao lado esquedo do vetor */

	mergesort1(a, m+1, r);	/* recursao ao lado direito do vetor */

	merge1(a, l, m, r);		/* ordena o vetor, depois de estar dividido individualmente */
}


void merge1(int a[], int l, int m, int r){

	int i, j, k;

	for(i=m+1;i>l;i--)
		merge1Aux[i-1]=a[i-1];
	for(j=m;j<r;j++)
		merge1Aux[r+m-j]=a[j+1];
	for(k=l;k<=r;k++){
		if(produtos[merge1Aux[j]].preco<produtos[merge1Aux[i]].preco)	/* condicao de troca */
			a[k]=merge1Aux[j--];
		else if(produtos[merge1Aux[j]].preco==produtos[merge1Aux[i]].preco && produtos[merge1Aux[j]].idp<produtos[merge1Aux[i]].idp) /* condicao de troca */
			a[k]=merge1Aux[j--];
		else
			a[k]=merge1Aux[i++];
	}
}


void mergesort2(int a[], int b[], int l, int r){

	int m= (r+l)/2;			/* divide sucessivamente o vetor ao meio */

	if(r<=l) return;		/* condi??o de paragem */

	mergesort2(a, b, l, m);		/* recursao ao lado esquedo do vetor */

	mergesort2(a, b, m+1, r);	/* recursao ao lado direito do vetor */

	merge2(a, b, l, m, r);		/* ordena o vetor, depois de estar dividido individualmente */
}


void merge2(int a[], int b[], int l, int m, int r){

	int i, j, k;

	for(i=m+1;i>l;i--){
		merge2Aux[i-1]=a[i-1];
		temp[i-1]=b[i-1];
	}
	for(j=m;j<r;j++){
		merge2Aux[r+m-j]=a[j+1];
		temp[r+m-j]=b[j+1];
	}
	for(k=l;k<=r;k++){
		if(strcmp(produtos[merge2Aux[j]].descricao, produtos[merge2Aux[i]].descricao)<0){	/* condicao de troca */
			a[k]=merge2Aux[j];
			b[k]=temp[j];
			j--;
		}	
		else{
			a[k]=merge2Aux[i];
			b[k]=temp[i];
			i++;
		}
	}
}


int __k__(){

	int i;

	printf("Produtos:\n");

	for(i=0;i<produtosAtuais;i++)
		printf("* %s %d %d\n", produtos[i].descricao, produtos[i].preco, produtos[i].quantidade);

	return 0;
}


int __K__(){

	int i, c, _ide;
	char input[MAX_INPUT];
	char* token;

	c=getchar();	/* remove o espaco entre o 'K' e o resto da string*/
	
	for(i=0; c!='\n';i++){ 		/* copia o input dado */
		c=getchar();			/* para um novo vetor */
		input[i]=c;			
	}
	i--;					
	input[i]='\0';

	token=strtok(input, "\0");	
	_ide=atoi(token);				/* guarda o valor "ide" */

	if(encomendas[_ide].eCriado!=1){		/* verifica se a encomenda existe, senao imprime erro */
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", _ide);
		return 0;
	}

	printf("Encomenda %d\n", _ide);

	for(i=0;i<MAX_PRODUTOS; i++){		/* percorre o vetor de produtos referente a encomenda */
		if(encomendas[_ide].prodsEnc[i]>0){		/* se a encomenda ja tiver produtos, lista-os */
			printf("* %s %d %d\n", produtos[i].descricao, produtos[i].preco, encomendas[_ide].prodsEnc[i]);
		}
	}
	
	return 0;
}


/*#####################################################################*/
/*	CODIGO                                                             */
/*#####################################################################*/

int main(){

	int c;
	
	while(c!='x'){
		c=getchar();
		switch(c){
			case 'a':			/* adiciona um novo produto ao sistema */	
				__a__();
				break;
			case 'q':			/* adiciona stock a um produto existente no sistema */
				__q__();
				break;
			case 'N':			/* cria uma nova encomenda */
				__N__();
				break;
			case 'A':			/* adiciona um produto a uma encomenda */
				__A__();
				break;
			case 'r':			/* remove stock a um produto existente */
				__r__();
				break;
			case 'R':			/* remove um produto de uma encomenda */
				__R__();
				break;
			case 'C':			/* calcula o custo de uma encomenda */
				__C__();
				break;
			case 'p':			/* altera o pre?o de um produto existente no sistema */
				__p__();
				break;
			case 'E':			/* lista a descricao e a quantidade de um produto numa encomenda */
				__E__();
				break;
			case 'm':			/* lista o identificador da encomenda em que o produto dado ocorre mais vezes */
				__m__();
				break;
			case 'l':			/* lista todos os produtos existentes no sistema por ordem crescente de pre?o */
				__l__();
				break;
			case 'L':			/* lista todos os produtos de uma encomenda por ordem alfab?tica da descricao */
				__L__();
				break;
			case 'k':			/* AUXILIAR */
				__k__();
				break;
			case 'K':			/* AUXILIAR */
				__K__();
				break;
			case 'x':			/* termina o programa */
				return 0;												
		}
	}

	return 0;
}

/*#####################################################################*/