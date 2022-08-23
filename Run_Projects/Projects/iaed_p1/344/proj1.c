#include <stdio.h>
#include <string.h>

/* Constantes */
#define MAX_PRODUTOS   	10000  	/* numero maximo de produtos */
#define MAX_DESCRICAO  	64     	/* numero maximo de caracteres da descricao de um produto e mais 1 para '\0' */
#define MAX_ECOMENDAS  	500    	/* numero maximo de encomendas */
#define MAX_UNIS_PESO  	200    	/* numero maximo de unidades de peso de cada encomenda */
#define MAX_DIG_MAIS_10 11 	   	/* numero maximo de digitos que um numero interio positivo pode ter em maquinas de 64 bits, mais 1 pelo 10 que fica no final */


/****************************/
/****************************/
/*********Estruturas*********/
/****************************/
/****************************/

typedef struct produto {
	char desc[MAX_DESCRICAO]; 		/* descricao do produto */
	int pr; 						/* preco do produto */
	int pe; 						/* peso do produto */
	int qtd;  						/* quantidade do produto */
	int ativo;						/* variavel de estado que indica se o produto esta ativo */
	int searched; 					/* variavel de estado que indica se o produto foi procurado */
} produto;

typedef struct encomenda {
	int pe_total; 					/* peso total da encomenda */
	int ativo;						/* variavel de estado que indica se a encomenda esta ativa */
	produto conteudo[MAX_PRODUTOS];	/* vetor produtos da encomenda */
} encomenda;


/***************************/
/***************************/
/*****Variaveis Globais*****/
/***************************/
/***************************/

produto inventario[MAX_PRODUTOS]; 		/* inventario: vetor com os produtos */
int idp_gl; 							/* (=0) identificador de produto e ponteiro do inventario */
encomenda encomendas[MAX_ECOMENDAS];	/* vetor com todas as encomendas */
int ide_gl; 							/* (=0) identificador de encomenda e ponteiro das encomendas */


/*****************************/
/*****************************/
/******Funces Auxiliares******/
/*****************************/
/*****************************/

/********************/
/*****Aritmetica*****/
/********************/

/* Potencia de 2 numeros inteiros. */
int pot(int b, int e){
	int res=1;

	if(e == 0) 
		return 1;
	
	for(; e > 0; e--){
		res *= b;
	}

	return res;
}

/********************/
/**Leitura de Input**/
/********************/

/* Le uma sequencia de digitos ate ao caracter de terminacao (que e argumento),
   colocando-os num vetor.  */
void numsIn_em_vet(char term, int num[]){
	int i;		 			  	
	int n; 	/* numero do caracter ASCII lido do input, (n-48) e o numero real */ 
	
	/* coloca digitos no vetor num e o finalizador */
	for(i=0; ((n = getchar()) != term) && i < MAX_DIG_MAIS_10; i++){
		num[i] = n - 48;
	}
	/* 10 e para num como \0 e para uma string */
	num[i] = 10;
}

/* Devolve o numero de digitos presentes num vetor num,
   de digitos e 10 apos o ultimo. */
int num_digs(int num[]){
	int i;
	int res=0;

	for(i=0; num[i] != 10 && i < MAX_DIG_MAIS_10; i++){
		res += 1;
	}

	return res;
}

/* Recebe um vetor com digitos e 10 apos o ultimo.
   Devolve o numero que os digitos formam. */
int vetNums_em_int(int num[]){
	int i;
	int digs = num_digs(num); 		/* numero de digitos */
	int xdez = digs-1;				/* expoente de base 10 */
	int res=0; 						

	for(i=0; num[i] != 10 && i < MAX_DIG_MAIS_10; i++){
		res += num[i] * pot(10, xdez);
		xdez -= 1;
	}

	return res;
}

/* Devolve o numero presente numa parte do input.
   Recebe o caracter de terminacao para delimitar a parte do input a ler. */
int numsIn_em_int(char term){
	static int num[MAX_DIG_MAIS_10]; 	/* Vetor em que cada entrada e um digito de um numero
				   						e no final tem 10, como as strings no final tem \0. */
	int res;

	numsIn_em_vet(term, num);
	res = vetNums_em_int(num);

	return res;
}

/********************/
/******Outras********/
/********************/

/* Devolve 1(True) se o identificado estiver dentro do vetor e
   0(False) caso contrario. */
int in_vet_p(produto vet[], int id){

	if(vet[id].ativo){
		return 1;
	}
	else{
		return 0;
	}
}

/* Devolve 1(True) se o identificado estiver dentro do vetor e
   0(False) caso contrario. */
int in_vet_e(encomenda vet[], int id){

	if(vet[id].ativo){
		return 1;
	}
	else{
		return 0;
	}
}

/* Remove quantidade de um produto no inventario. */
void remove_qtd_invent(int idp, int Qtd){
	inventario[idp].qtd -= Qtd;
}


/* Devolve numero de produtos ativos num vetor de produtos. */
int n_ps_ati(produto vet[]){
	int res=0;
	int i;

	for(i=0; i < MAX_PRODUTOS; i++){
		if(vet[i].ativo){
			res += 1;
		}
	}

	return res;
}


/****************************/
/****************************/
/**********Comandos**********/
/****************************/
/****************************/

/*************/
/* Comando a */
/*************/

/* Adiciona um produto ao sistema. */
void a(){
	char c; 	/* caracter do input */
	int i;
	int prop; 	/* valor da propriedade */
	
	/* leitura das propriedades do produto */ 
	/* descricao */
	for(i=0; i < MAX_DESCRICAO; i++){
		if((c = getchar()) != ':'){
			inventario[idp_gl].desc[i] = c;
		}
		else if(c == ':'){
			break;
		}
	}
	inventario[idp_gl].desc[i] = '\0';

	/* preco */
	prop = numsIn_em_int(':');
	inventario[idp_gl].pr = prop;
	/* peso */
	prop = numsIn_em_int(':');
	inventario[idp_gl].pe = prop;
	/* quantidade */	
	prop = numsIn_em_int('\n');
	inventario[idp_gl].qtd = prop;
	/* ativa o produto*/
	inventario[idp_gl].ativo = 1;
	
	/* output */
	printf("Novo produto %d.\n", idp_gl);
	
	/* incrementa ponteiro do inventario */
	idp_gl += 1;
}

/****Fim a****/



/*************/
/* Comando q */
/*************/

/* Adiciona stock a um produto existente no sistema. */
void q(){
	int idp = numsIn_em_int(':'); 	/* identificador do produto */
	int Qtd = numsIn_em_int('\n');	/* valor da quantidade a aumentar */

	/* produto existe? */
	if(!in_vet_p(inventario, idp)){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	}
	else{
		inventario[idp].qtd += Qtd;
	}
}

/****Fim q****/



/*************/
/* Comando N */
/*************/

/* Cria uma nova encomenda. */
void N(){
	/* inicializa propriedades */
	encomendas[ide_gl].ativo = 1;
	encomendas[ide_gl].pe_total = 0;

	/* output */
	printf("Nova encomenda %d.\n", ide_gl);

	/* avanca o ponteiro */
	ide_gl += 1;
}

/****Fim N****/



/*************/
/* Comando A */
/*************/

/* Adiciona um produto a uma encomenda */ 
void A(){
	int ide = numsIn_em_int(':');	/* identificador da encomenda */
	int idp = numsIn_em_int(':'); 	/* identificador do produto a adicionar */
	int Qtd = numsIn_em_int('\n'); 	/* quantidade do produto a adicionar */

	/* encomenda existe? */
	if(!in_vet_e(encomendas, ide)){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
	/* produto existe? */
	else if(!in_vet_p(inventario, idp)){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	/* quantidade em stock suficiente? */
	else if(inventario[idp].qtd - Qtd < 0){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
	}
	/* nao excede o peso maximo da encomenda? */
	else if((encomendas[ide].pe_total + (inventario[idp].pe * Qtd)) > MAX_UNIS_PESO){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
	}
	/* produto ja esta presente na encomenda? */
	else if(in_vet_p(encomendas[ide].conteudo, idp)){
		/* soma quantidade */
		encomendas[ide].conteudo[idp].qtd += Qtd;
		/* atualiza peso total */
		encomendas[ide].pe_total += inventario[idp].pe * Qtd;
		/* atualiza quantidade do produto no inventario */
		remove_qtd_invent(idp, Qtd);
	}
	/* produto nao esta presente na encomenda */
	else{
		/* adiciona produto a encomenda */
		encomendas[ide].conteudo[idp] = inventario[idp]; 	
		/* quantidade do produto adicionada na encomenda */
		encomendas[ide].conteudo[idp].qtd = Qtd;
		/* atualiza peso total */
		encomendas[ide].pe_total += inventario[idp].pe * Qtd;
		/* atualiza quantidade do produto no inventario */
		remove_qtd_invent(idp, Qtd);

	}
}

/****Fim A****/



/*************/
/* Comando r */
/*************/

/* Remove stock a um produto existente. */
void r(){
	int idp = numsIn_em_int(':'); 	/* identificador do produto */
	int Qtd = numsIn_em_int('\n');	/* quantidade do produtdo a retirar */

	/* produto existe? */
	if(!in_vet_p(inventario, idp)){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	}
	/* ha quantidade suficiente para remover o pretendido? */
	else if(inventario[idp].qtd - Qtd < 0){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", Qtd, idp);
	}
	/* e possivel fazer a remocao */
	else{
		remove_qtd_invent(idp, Qtd);
	}
}

/****Fim r****/



/*************/
/* Comando R */
/*************/

/* Remove um produto de uma encomenda. */
void R(){
	int ide = numsIn_em_int(':');	/* identificador da encomenda */
	int idp = numsIn_em_int('\n');	/* identificador do produto a remover */

	/* encomenda existe? */
	if(!in_vet_e(encomendas, ide)){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
	/* produto existe? */
	else if(!in_vet_p(inventario, idp)){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	/* remocao do produto e possivel */
	else{
		/* o produto esta de facto na encomenda? */
		if(in_vet_p(encomendas[ide].conteudo, idp)){
			/* atualiza peso total */
			encomendas[ide].pe_total -= inventario[idp].pe * encomendas[ide].conteudo[idp].qtd;
			/* repor a quantidade no inventario */
			inventario[idp].qtd += encomendas[ide].conteudo[idp].qtd;
		}

		/* remover o produto da encomenda */
		encomendas[ide].conteudo[idp].ativo = 0;
		/* remove a quantidade na encomenda */ 
		encomendas[ide].conteudo[idp].qtd = 0;
	}
}

/****Fim R****/



/*************/
/* Comando C */
/*************/

/* Calcula o custo de uma encomenda. */
void C(){
	int ide = numsIn_em_int('\n'); 	/* identificador da encomenda */
	int total=0;					/* custo da encomenda */
	int i;							

	/* encomenda existe? */
	if(!in_vet_e(encomendas, ide)){
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);;
	}
	else{
		/* soma precos */
		for(i=0; i < MAX_PRODUTOS; i++){
			if(in_vet_p(encomendas[ide].conteudo, i)){
				total += encomendas[ide].conteudo[i].pr * encomendas[ide].conteudo[i].qtd;
			}
		}
		/* output */
		printf("Custo da encomenda %d %d.\n", ide, total);
	}
}

/****Fim C****/



/*************/
/* Comando p */
/*************/

/* Altera o preco de um produto existente no sistema. */
void p(){
	int idp = numsIn_em_int(':');		/* identificador do produto */
	int preco = numsIn_em_int('\n');	/* valor do novo preco */
	int i;

	/* produto existe? */
	if(!in_vet_p(inventario, idp)){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	}
	else{
		/* altera no inventario */
		inventario[idp].pr = preco;

		/* altera nas encomendas */
		for(i=0; i < MAX_ECOMENDAS; i++){
			encomendas[i].conteudo[idp].pr = preco;
		}
	}
}

/****Fim p****/



/*************/
/* Comando E */
/*************/

/* Lista a descricao e a quantidade de um produto numa encomenda. */ 
void E(){
	int ide = numsIn_em_int(':');	/* identificador da encomenda */
	int idp = numsIn_em_int('\n'); 	/* identificador do produto */

	/* encomenda existe? */
	if(!in_vet_e(encomendas, ide)){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
	/* produto existe? */
	else if(!in_vet_p(inventario, idp)){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	}
	/* encomenda e produto existe */
	else{
		printf("%s %d.\n", inventario[idp].desc, encomendas[ide].conteudo[idp].qtd);
	}
}

/****Fim E****/



/*************/
/* Comando m */
/*************/

/* Lista o identificador da encomenda em que o produto dado ocorre mais vezes. */
void m(){
	int idp = numsIn_em_int('\n');	/* identificador do produto*/
	int ide;						/* indentificador da encomenda */
	int maior_qtd=-1; 				/* maior quantidade */
	int ide_maior=-1;				/* identificador da encomenda em que dado produto ocorre mais vezes */

	/* produto existe? */
	if(!in_vet_p(inventario, idp)){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
		return;
	}

	for(ide=0; ide < MAX_ECOMENDAS; ide++){
		/* a quantidade do produto numa dada encomenda e a maior ate agora? */
		if(in_vet_e(encomendas, ide) && in_vet_p(encomendas[ide].conteudo, idp) && encomendas[ide].conteudo[idp].qtd > maior_qtd){
			maior_qtd = encomendas[ide].conteudo[idp].qtd;
			ide_maior = ide;
		}
	}
	
	/* produto nao ocorre em nenhuma encomenda nem existem ecomendas */
	if(maior_qtd == -1 || ide_maior == -1){
		return;	
	}

	/* output */
	printf("Maximo produto %d %d %d.\n", idp, ide_maior, maior_qtd);
}

/****Fim m****/



/*************/
/* Comando l */
/*************/

/* Lista todos os produtos existentes no sistema por ordem crescente de preco */
void l(){
	int i; 							
	int menor_pr = -1; 							/* menor preco */
	int maior_definitivo;						/* valor que e superior a qualquer preco */
	int i_menor = 0;							/* indice do produto com menor preco */
	int num_ps_searched = n_ps_ati(inventario);	/* numero de produtos ativos */

	/* coloca valor em menor_pr que e guarantidamente maior que todos os precos */
	for(i=0; i < MAX_PRODUTOS; i++){
			maior_definitivo += inventario[i].pr;
	}
	menor_pr = maior_definitivo;

	/* output e algoritmo de organizacao */
	printf("Produtos\n");
	while(num_ps_searched > 0){
		for(i=0; i < MAX_PRODUTOS; i++){
			/* o produto ja foi procurado? */
			if(!(inventario[i].searched)){
				if(0 < inventario[i].pr && inventario[i].pr < menor_pr){
					/* atualiza menor preco */
					menor_pr = inventario[i].pr;
					/* e guarda indice do mesmo */
					i_menor = i;
				}
			}
		}
		printf("* %s %d %d\n", inventario[i_menor].desc, inventario[i_menor].pr, inventario[i_menor].qtd);
		/* marca o produto em questao como procurado */
		inventario[i_menor].searched = 1;
		/* repoe menor_pr*/
		menor_pr = maior_definitivo;
		
		num_ps_searched -= 1;
	}

	/* repoe a o estado de procurado de todos os produtos do inventario */
	for(i=0; i < MAX_PRODUTOS; i++){
			inventario[i].searched = 0;
	}
}

/****Fim l****/

/*************/
/* Comando L */
/*************/

/* Lista todos os produtos de uma encomenda por ordem alfabetica na descricao */
void L(){
	int ide = numsIn_em_int('\n');								/* identificador da encomenda */
	int i; 														/* indice generico */
	char menor_desc[MAX_DESCRICAO]; 							/* menor descicao */
	char maior_definitivo[MAX_DESCRICAO];						/* maior string possivel com MAX_DESCRICAO caracteres */
	int i_menor = 0;											/* indice do produto com menor descricao */
	int num_ps_searched = n_ps_ati(encomendas[ide].conteudo);	/* numero de produtos ativos */

	/* encomenda existe? */
	if(!in_vet_e(encomendas, ide)){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return;
	}

	/* maior string possivel com MAX_DESCRICAO caracteres */
	maior_definitivo[0] = 127;
	maior_definitivo[1] = '\0';
	strcpy(menor_desc, maior_definitivo);

	/* output e algoritmo de organizacao */
	printf("Encomenda %d\n", ide);
	while(num_ps_searched > 0){
		for(i=0; i < MAX_PRODUTOS; i++){
			/* o produto ja foi procurado? */
			if(!(encomendas[ide].conteudo[i].searched) && in_vet_p(encomendas[ide].conteudo, i)){
				if(strcmp(encomendas[ide].conteudo[i].desc, menor_desc) < 0 && strlen(encomendas[ide].conteudo[i].desc) != 0){
					/* atualiza menor preco */
					strcpy(menor_desc, encomendas[ide].conteudo[i].desc);
					/* e guarda indice do mesmo */
					i_menor = i;
				}
			}	
		}

		printf("* %s %d %d\n", encomendas[ide].conteudo[i_menor].desc, encomendas[ide].conteudo[i_menor].pr, encomendas[ide].conteudo[i_menor].qtd);
		/* marca o produto em questao como procurado */
		encomendas[ide].conteudo[i_menor].searched = 1;
		/* repoe menor_desc */
		strcpy(menor_desc, maior_definitivo);

		num_ps_searched -= 1;
	}

	/* repoe o estado de procurado em todos os produtos da encomenda */
	for(i=0; i < MAX_PRODUTOS; i++){
			encomendas[ide].conteudo[i].searched = 0;
	}
}

/****Fim L****/

/*****************************/
/*****************************/
/*******Ciclo Principal*******/
/*****************************/
/*****************************/

/* Onde o sistema vai estar em ciclo.
   Recebe o input e corre o comando respetivo. */
int main(){
	char c; /* caracter do input */

	/* selecao de funcao */
	/* os "c = getchar();" antes da chamada da funcao servem para passar o ' ' a frente */
	while((c = getchar()) != 'x'){
		switch(c){
			case 'a':
				c = getchar();  
				a();
				break;
			case 'q':
				c = getchar();  
				q();
				break;
			case 'N':  
				N();
				break;
			case 'A':
				c = getchar();  
				A();
				break;
			case 'r':
				c = getchar();  
				r();
				break;	
			case 'R':
				c = getchar();  
				R();
				break;
			case 'C':
				c = getchar();  
				C();
				break;
			case 'p':
				c = getchar();  
				p();
				break;
			case 'E':
				c = getchar();  
				E();
				break;
			case 'm':
				c = getchar();  
				m();
				break;
			case 'l':  
				l();
				break;
			case 'L':
				c = getchar();  
				L();
				break;
		}
	}
	return 0;
}	