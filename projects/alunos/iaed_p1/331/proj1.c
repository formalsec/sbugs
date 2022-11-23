#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define MAXPRODUTOS 10000
#define DESC 64
#define MAXENCOMENDAS 500
#define PESOENCOMENDA 200

typedef struct produto{						/*estrutura dos produtos*/
	char descricao[DESC];
	int idP;
	int preco;
	int peso;
	int quantidade;
}	Produto;

typedef struct encomenda{					/*estrutura de encomendas*/
	Produto ProdutosEnc[MAXPRODUTOS];
	int lista_idsProd_Enc[MAXPRODUTOS];
	int contador;
	int pesoEnc;
	int precoEnc;
}	Encomenda;

Encomenda lista_Enc[MAXENCOMENDAS];			/*variavel global*/

/*
| Comando | Acao |
|  __a__  | adiciona um novo produto ao sistema |
*/
void a(int ContadorProd, Produto armazem[MAXPRODUTOS]){
	int i = 0;
	char lixo, c, vartab[DESC];

	c = getchar();
	while ((c = getchar()) != ':'){
		vartab[i++] = c;
	}
	vartab[i] = '\0';

	for (i = 0; i < DESC; i++){
		armazem[ContadorProd].descricao[i] = vartab[i];
	}

	scanf("%d%c%d%c%d", &armazem[ContadorProd].preco, &lixo, &armazem[ContadorProd].peso, &lixo, &armazem[ContadorProd].quantidade);	
	/*variavel 'lixo' guarda os dois pontos entre campos*/
	printf("Novo produto %d.\n", ContadorProd);
}

/*
| Comando | Acao |
|  __q__  | adiciona stock a um produto existente no sistema |
*/
void q(int ContadorProd, Produto armazem[MAXPRODUTOS]){
	char lixo;
	int id, qtd;

	scanf("%c%d%c%d", &lixo, &id, &lixo, &qtd);
	if (id < ContadorProd)
		armazem[id].quantidade += qtd;
	else
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
}

/*
| Comando | Acao |
|  __r__  | remove stock a um produto existente |
*/
void r(int ContadorProd, Produto armazem[MAXPRODUTOS]){
	char lixo;
	int id, qtd;

	scanf("%c%d%c%d", &lixo, &id, &lixo, &qtd);
	if (id < ContadorProd){
		if (armazem[id].quantidade - qtd >= 0)
			armazem[id].quantidade -= qtd;
		else
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id);
	}
	else
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
}

/*
| Comando | Acao |
|  __p__  | altera o pre?o de um produto existente no sistema |
*/
void p(int ContadorProd, int ContadorEnc, Produto armazem[MAXPRODUTOS], Encomenda lista_Enc[MAXENCOMENDAS]){
	char lixo;
	int id, price, e;

	scanf("%c%d%c%d", &lixo, &id, &lixo, &price);

	if (id < ContadorProd){
		for (e = 0; e < ContadorEnc; e++){
			if (lista_Enc[e].lista_idsProd_Enc[id] == id){

				lista_Enc[e].precoEnc -= (armazem[id].preco * lista_Enc[e].ProdutosEnc[id].quantidade);
				armazem[id].preco = price;
				lista_Enc[e].precoEnc += (armazem[id].preco * lista_Enc[e].ProdutosEnc[id].quantidade);
			}
		}
		armazem[id].preco = price;
	}
	else
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
}

/*
| Comando | Acao |
|  __N__  | cria uma nova encomenda |
*/
void N(int ContadorEnc){
	printf("Nova encomenda %d.\n", ContadorEnc);
}


/*
| Comando | Acao |
|  __A__  | adiciona um produto a uma encomenda |
*/
void A(int ContadorEnc, int ContadorProd, Encomenda lista_Enc[MAXENCOMENDAS], Produto armazem[MAXPRODUTOS]){
	int IdEnc, IdProd, qtd, VarEstado = 5, e;
	char lixo;

	scanf("%c%d%c%d%c%d", &lixo, &IdEnc, &lixo, &IdProd, &lixo, &qtd);


	if (IdEnc > ContadorEnc - 1)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", IdProd, IdEnc);

	else if (IdProd > ContadorProd - 1) 
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", IdProd, IdEnc);

	else if (armazem[IdProd].quantidade - qtd < 0) 
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", IdProd, IdEnc);

	else if (armazem[IdProd].peso * qtd + lista_Enc[IdEnc].pesoEnc > PESOENCOMENDA)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", IdProd, IdEnc);
		else{
			for (e = 0; e < lista_Enc[IdEnc].contador; e++){
				if (lista_Enc[IdEnc].ProdutosEnc[e].descricao == armazem[IdProd].descricao)
					VarEstado = 1;		/*variavel de estado controla se um produto ja existe numa encomnda ou nao*/
			}

			if (VarEstado == 1){	/*no caso de o produto ja existir na encomenda, */

				/*apenas o preco e o peso sao alterados na encomenda*/
				lista_Enc[IdEnc].precoEnc += armazem[IdProd].preco * qtd;	
				lista_Enc[IdEnc].pesoEnc += armazem[IdProd].peso * qtd;	
				/*atualiza a qtd do msm produto na encomenda*/
				lista_Enc[IdEnc].ProdutosEnc[IdProd].quantidade += qtd;		
				/*a quantidade do produto em causa e retirada do armazem para ser posto na encomenda*/			
				armazem[IdProd].quantidade -= qtd;					
			}
			else {	/*no caso de o produto ainda nao existir na encomenda*/

				lista_Enc[IdEnc].precoEnc += armazem[IdProd].preco * qtd;			
				lista_Enc[IdEnc].pesoEnc += armazem[IdProd].peso * qtd;
				/*todos os campos sao copiados incluindo a descricao do produto*/
				strcpy(lista_Enc[IdEnc].ProdutosEnc[IdProd].descricao, armazem[IdProd].descricao);	
				/*atualiza a qtd do mesmo produto na encomenda*/
				lista_Enc[IdEnc].ProdutosEnc[IdProd].quantidade += qtd;	
				/*a quantidade do produto em causa e retirada do armazem para ser posto na encomenda*/		
				armazem[IdProd].quantidade -= qtd;
				/*assim como o contador*/		
				lista_Enc[IdEnc].contador += 1;	
				/*o id do produto e adicionado a lista de ids da encomenda*/		
				lista_Enc[IdEnc].lista_idsProd_Enc[IdProd] = IdProd;
			}
		}
}

/*
| Comando | Acao |
|  __C__  | calcula o custo de uma encomenda |
*/
void C(int ContadorEnc, Encomenda lista_Enc[MAXENCOMENDAS]){
	int IdEnc;

	scanf("%d", &IdEnc);

	if (IdEnc > ContadorEnc - 1)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", IdEnc);
	else
		printf("Custo da encomenda %d %d.\n", IdEnc, lista_Enc[IdEnc].precoEnc);
}

/*
| Comando | Acao |
|  __R__  | remove um produto de uma encomenda |
*/
void R(int ContadorProd, int ContadorEnc, Encomenda lista_Enc[MAXENCOMENDAS], Produto armazem[MAXPRODUTOS]){
	int IdEnc, IdProd;
	char lixo;

	scanf("%c%d%c%d", &lixo, &IdEnc, &lixo, &IdProd);

	if (IdEnc > ContadorEnc - 1)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", IdProd, IdEnc);

	else{ if (IdProd > ContadorProd - 1)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", IdProd, IdEnc);				

		else{
			/*a qtd do produto que vai ser retirado da encomenda vai voltar para o stock*/
			armazem[IdProd].quantidade += lista_Enc[IdEnc].ProdutosEnc[IdProd].quantidade;
			/*atualizar a peso da encomenda*/
			lista_Enc[IdEnc].pesoEnc -= armazem[IdProd].peso * lista_Enc[IdEnc].ProdutosEnc[IdProd].quantidade;
			/*atualizar o preco da encomenda*/
			lista_Enc[IdEnc].precoEnc -= armazem[IdProd].preco * lista_Enc[IdEnc].ProdutosEnc[IdProd].quantidade;
			/*a qtd do produto na encomenda e atualizado para 0.*/		
			lista_Enc[IdEnc].ProdutosEnc[IdProd].quantidade = 0;								
		}
	}
}

/*
| Comando | Acao |
|  __E__  | retorna a descricao e a quantidade de um produto numa dada encomenda |
*/
void E(int ContadorEnc, int ContadorProd, Encomenda lista_Enc[MAXENCOMENDAS], Produto armazem[MAXPRODUTOS]){
	int IdEnc, IdProd;
	char lixo;

	scanf("%c%d%c%d", &lixo, &IdEnc, &lixo, &IdProd);

	if (IdEnc > ContadorEnc - 1)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", IdEnc);

	else { if (IdProd > ContadorProd - 1)
		printf("Impossivel listar produto %d. Produto inexistente.\n", IdProd);

		else{
			/*no caso de o produto existir na encomenda*/
			if (lista_Enc[IdEnc].lista_idsProd_Enc[IdProd] == IdProd){
				strcpy(lista_Enc[IdEnc].ProdutosEnc[IdProd].descricao, armazem[IdProd].descricao);
				printf("%s", lista_Enc[IdEnc].ProdutosEnc[IdProd].descricao);	/*imprime descricao do produto na encomenda*/
				printf(" %d.\n", lista_Enc[IdEnc].ProdutosEnc[IdProd].quantidade);			/*imprime qtd do produto na encomenda*/
			}
			/*no caso de o produto nao existir na encomenda*/
			else{
				printf("%s", armazem[IdProd].descricao);	/*imprime descricao do produto na encomenda*/
				printf(" 0.\n");			/*imprime qtd do produto na encomenda*/
			}
		}
	}
}

/*
| Comando | Acao |
|  __m__  | retorna o identificador da encomenda em que um dado produto ocorre mais vezes |
*/
void m(int ContadorEnc, int ContadorProd, Encomenda lista_Enc[MAXENCOMENDAS]){
	int IdProd, e, maiorQTD = 0, EncAlvo = 0;
	char lixo;

	scanf("%c%d", &lixo, &IdProd);

	if (ContadorEnc == 0 || IdProd > ContadorProd - 1)				/*caso nao haja encomendas criadas ou o produto nao exista*/
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", IdProd);

	else {
		for (e = 0; e < ContadorEnc; e++){
			if (lista_Enc[e].ProdutosEnc[IdProd].quantidade > maiorQTD){
				maiorQTD = lista_Enc[e].ProdutosEnc[IdProd].quantidade;		/*atualiza o maior*/
				EncAlvo = e;		
			}
		}
		if (maiorQTD <= 0)		/*caso a quantidade nao tenha sido atualizada*/
			return;

		printf("Maximo produto %d %d %d.\n", IdProd, EncAlvo, maiorQTD);
	}
}

/*
| Funcao de ordenacao (merge sort) |
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
*/
void merge(Produto arr[], int l, int m, int r){ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 

    Produto L[MAXPRODUTOS], R[MAXPRODUTOS]; 

    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 

    i = 0;  
    j = 0; 
    k = l;  
    while (i < n1 && j < n2){ 
        if (L[i].preco <= R[j].preco){ 
            arr[k] = L[i]; 
            i++; 
        } 
        else{ 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1){ 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2){ 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

/*
| Funcao de ordenacao (merge sort) |
------------------------------------
*/ 
void mergeSort(Produto arr[], int l, int r){ 
    if (l < r){ 
        int m = l+(r-l)/2; 

        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
        merge(arr, l, m, r); 
    } 
} 

/*
| Comando | Acao |
|  __l__  | lista todos os produtos existentes no sistema por ordem crescente de pre?o |
*/
void l(int ContadorProd, Produto armazem[MAXPRODUTOS]){
	Produto lista_Preco_Id[MAXPRODUTOS];		/*vetor auxiliar do tipo Produto*/
	int e;

	for (e = 0; e < ContadorProd; e++){
		lista_Preco_Id[e].preco = armazem[e].preco;		/*copia os valores originais*/
		lista_Preco_Id[e].idP = e;						/*para o vetor auxiliar*/
	}

	mergeSort(lista_Preco_Id, 0, ContadorProd - 1);		/*ordena*/

	printf("Produtos\n");
	for (e = 0; e < ContadorProd; e++){
		printf("* %s %d %d\n", armazem[lista_Preco_Id[e].idP].descricao, armazem[lista_Preco_Id[e].idP].preco, armazem[lista_Preco_Id[e].idP].quantidade);
	}
}

/*
| Comando | Acao |
|  __L__  | lista todos os produtos de uma encomenda por ordem alfabetica da descri??o |
*/
void L(int ContadorEnc, int ContadorProd, Produto armazem[MAXPRODUTOS]){
	int IdEnc, i, j, e;
	char lixo, aux[MAXPRODUTOS][DESC], temp[DESC];

	scanf("%c%d",&lixo, &IdEnc);
	if (IdEnc > ContadorEnc - 1)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.", IdEnc);

	else{
		for (e = 0; e < lista_Enc[IdEnc].contador - 1; e++){
			strcpy(aux[e], lista_Enc[IdEnc].ProdutosEnc[e].descricao);
		}

		for (i = 0;i < lista_Enc[IdEnc].contador - 1; i++){
      		for (j = i + 1; j <= lista_Enc[IdEnc].contador; j++){
	        	if (strcmp (aux[i], aux[j]) > 0){
		            strcpy (temp, aux[i]);
		            strcpy (aux[i], aux[j]);
		            strcpy (aux[j], temp);
	         	}
      		}
      	}

		printf("Produtos\n");
		for (e = 0; e <= lista_Enc[IdEnc].contador; e++){
			for (i = 0; i < ContadorProd; i++){
				if (strcmp(lista_Enc[IdEnc].ProdutosEnc[e].descricao, armazem[i].descricao) == 0)
					printf("* %s %d %d\n", aux[e], armazem[i].preco, armazem[i].quantidade);
			}
		}
	}
}

int main(){
	int ContadorProd = 0, ContadorEnc = 0, c;
	Produto armazem[MAXPRODUTOS];

	while ((c = getchar()) != 'x'){
		if (c == 'a'){
			a(ContadorProd, armazem);
			ContadorProd++;
			continue;
		}
		if (c == 'q'){
			q(ContadorProd, armazem);
			continue;
		}
		if (c == 'N'){
			N(ContadorEnc);
			ContadorEnc++;
			continue;
		}
		if (c == 'A'){
			A(ContadorEnc, ContadorProd, lista_Enc, armazem);
			continue;
		}
		if (c == 'r'){
			r(ContadorProd, armazem);
			continue;
		}
		if (c == 'R'){
			R(ContadorProd, ContadorEnc, lista_Enc, armazem);
			continue;
		}
		if (c == 'C'){
			C(ContadorEnc, lista_Enc);
			continue;
		}
		if (c == 'p'){
			p(ContadorProd, ContadorEnc, armazem, lista_Enc);
			continue;
		}
		if (c == 'E'){
			E(ContadorEnc, ContadorProd, lista_Enc, armazem);
			continue;
		}
		if (c == 'm'){
			m(ContadorEnc, ContadorProd, lista_Enc);
			continue;
		}
		if (c == 'l'){
			l(ContadorProd, armazem);
			continue;
		}
		if (c == 'L'){
			L(ContadorEnc, ContadorProd, armazem);
			continue;
		}
	}
	return 0;
}