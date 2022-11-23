#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
/* n?mero m?ximo de caracteres da string */
#define MAXDESC 64
/* n?mero m?ximo de produtos */
#define MAXIDENT 10000
/* n?mero m?ximo de encomendas */
#define MAXENCOM 500
/* n?mero m?ximo de peso dos produtos por encomenda*/
#define MAXPESO 200

/* estrutura do produto caracterizado pelo identificador,descri??o,pre?o,peso e quantidade*/
struct produto{
	int ident;
	char desc[MAXDESC];
	int preco;
	int peso;
	int quant;
};

/* estrutura da encomenda caracterizada pelos produtos, peso,pre?o total da encomenda e o n?mero de produtos existentes na encomenda*/
struct encomenda{
	struct produto encomenda_produtos[MAXIDENT];
	int peso;
	int preco_total;
	int numero_produtos;
};

void a(int contador, struct produto tabela_produtos[MAXIDENT]);
void q(int contador, struct produto tabela_produtos[MAXIDENT]);
void N(int contador_encomendas);
void A(int contador_encomendas, int contador, struct encomenda tabela_encomendas[MAXENCOM], struct produto tabela_produtos[MAXIDENT]);
void r(int contador, struct produto tabela_produtos[MAXIDENT]);
void R(int contador, int contador_encomendas, struct encomenda tabela_encomendas[MAXENCOM], struct produto tabela_produtos[MAXIDENT]);
void C(int contador_encomendas, struct encomenda tabela_encomendas[MAXENCOM]);
void p(int contador, int contador_encomendas, struct produto tabela_produtos[MAXIDENT], struct encomenda tabela_encomendas[MAXENCOM]);
void E(int contador, int contador_encomendas, struct encomenda tabela_encomendas[MAXENCOM], struct produto tabela_produtos[MAXIDENT]);
void m(int contador_encomendas, int contador, struct encomenda tabela_encomendas[MAXENCOM]);
void l(int contador, struct produto tabela_produtos[MAXIDENT]);
void L(int contador_encomendas, struct encomenda tabela_encomendas[MAXENCOM]);

/* Array de encomendas*/
struct encomenda tabela_encomendas[MAXENCOM];

int main ()
{
	/* Array de produtos*/
	struct produto tabela_produtos[MAXIDENT];
	char c;
	/* n?mero de produtos existentes*/
	int contador=0;
	/* n?mero de encomendas existentes*/
	int contador_encomendas=0;
	while((c=getchar()) != 'x'){
		if (c== 'a'){
			a(contador, tabela_produtos);
			contador++;
		} 
		else if (c=='q'){
			q(contador, tabela_produtos);
		}
		else if (c=='N'){
			N(contador_encomendas);
			contador_encomendas++;
		}
		else if (c=='A'){
			A(contador_encomendas, contador, tabela_encomendas, tabela_produtos);
		}
		else if (c=='r'){
			r(contador, tabela_produtos);
		}
		else if (c=='R'){
			R(contador, contador_encomendas, tabela_encomendas, tabela_produtos);
		}
		else if (c=='C'){
			C(contador_encomendas, tabela_encomendas);
		}
		else if (c=='p'){
			p(contador, contador_encomendas, tabela_produtos, tabela_encomendas);
		}
		else if (c=='E'){
			E(contador, contador_encomendas, tabela_encomendas, tabela_produtos);
		}
		else if (c=='m'){
			m(contador_encomendas, contador, tabela_encomendas);
		}
		else if (c=='l'){
			l(contador, tabela_produtos);
		}
		else if (c=='L'){
			L(contador_encomendas, tabela_encomendas);
		}
		else 
			continue;
		}
	return 0;
}

/* Adiciona um novo produto ao sistema */
void a(int contador, struct produto tabela_produtos[MAXIDENT])
{
	char c;
	int i=0;
	getchar();
	while((c=getchar())!=':' || i > MAXDESC){
		tabela_produtos[contador].desc[i] = c;
		i++;
	}
	tabela_produtos[contador].desc[i]= '\0';
	tabela_produtos[contador].ident=contador;
	scanf("%d", &tabela_produtos[contador].preco);
	scanf(":%d", &tabela_produtos[contador].peso);
	scanf(":%d", &tabela_produtos[contador].quant);
	printf("Novo produto %d.\n", contador);
}
/* Adiciona stock a um produto existente no sistema */
void q(int contador, struct produto tabela_produtos[MAXIDENT])
{
	int idp, qnt;
	getchar();
	scanf("%d", &idp);
	scanf(":%d", &qnt);
	if (idp >= contador){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	}
	else {
		tabela_produtos[idp].quant+= qnt;
	}
}

/* Cria uma nova encomenda */
void N(int contador_encomendas)
{
	printf("Nova encomenda %d.\n", contador_encomendas);
}

/* Adiciona um produto a uma encomenda. Se o produto j? existir na encomenda, adiciona a nova quantidade ? quantidade existente */
void A(int contador_encomendas, int contador, struct encomenda tabela_encomendas[MAXENCOM], struct produto tabela_produtos[MAXIDENT])
{
	int ide, idp, qtd, i, x;
	x=-1;
	getchar();
	scanf("%d", &ide);
	scanf(":%d", &idp);
	scanf(":%d", &qtd);
	if (ide >= contador_encomendas){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
	else if (idp >= contador){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else if (tabela_produtos[idp].quant < qtd){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
	}
	else if ((tabela_encomendas[ide].peso + (tabela_produtos[idp].peso * qtd)) > MAXPESO){
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
	}
	else{
		for(i=0; i < tabela_encomendas[ide].numero_produtos; i++){
			if (tabela_encomendas[ide].encomenda_produtos[i].ident == idp){
				x=i;
				break;
			}
		}
		/* se o produto j? existir na encomenda, atualiza os dados da encomenda*/
		if (x!=-1){
			tabela_encomendas[ide].encomenda_produtos[x].quant += qtd;
			tabela_produtos[idp].quant -= qtd;
			tabela_encomendas[ide].peso += (tabela_produtos[idp].peso * qtd);
			tabela_encomendas[ide].preco_total += (tabela_produtos[idp].preco * qtd);
		}
		else {
			tabela_encomendas[ide].encomenda_produtos[tabela_encomendas[ide].numero_produtos].ident = idp;
			tabela_encomendas[ide].encomenda_produtos[tabela_encomendas[ide].numero_produtos].peso = tabela_produtos[idp].peso ;
			tabela_encomendas[ide].encomenda_produtos[tabela_encomendas[ide].numero_produtos].preco = tabela_produtos[idp].preco;
			/* copia string para a encomenda */
			strcpy(tabela_encomendas[ide].encomenda_produtos[tabela_encomendas[ide].numero_produtos].desc, tabela_produtos[idp].desc);
			tabela_encomendas[ide].encomenda_produtos[tabela_encomendas[ide].numero_produtos].quant = qtd;
			tabela_produtos[idp].quant -= qtd;
			tabela_encomendas[ide].peso += (tabela_produtos[idp].peso * qtd);
			tabela_encomendas[ide].preco_total += (tabela_produtos[idp].preco * qtd);
			tabela_encomendas[ide].numero_produtos++;
		} 	
	}
}

/* Remove stock a um produto existente */
void r(int contador, struct produto tabela_produtos[MAXIDENT])
{
	int idp, qtd;
	getchar();
	scanf("%d", &idp);
	scanf(":%d", &qtd);
	if (idp >= contador){
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
	} 
	else if((tabela_produtos[idp].quant - qtd) < 0){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
	} 
	else {
		tabela_produtos[idp].quant -= qtd;
	}
}

/* Remove um produto de uma encomenda */
void R(int contador, int contador_encomendas, struct encomenda tabela_encomendas[MAXENCOM], struct produto tabela_produtos[MAXIDENT])
{
	int ide, idp, i;
	getchar();
	scanf("%d", &ide);
	scanf(":%d", &idp);
	if (ide >= contador_encomendas){
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
	}
	else if (idp >= contador){
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else {
		/* atualiza dados da encomenda */
		for (i = 0; i < tabela_encomendas[ide].numero_produtos; i++){
			if (tabela_encomendas[ide].encomenda_produtos[i].ident == idp){
				tabela_encomendas[ide].peso -= (tabela_encomendas[ide].encomenda_produtos[i].peso*tabela_encomendas[ide].encomenda_produtos[i].quant);
				tabela_encomendas[ide].preco_total -= (tabela_encomendas[ide].encomenda_produtos[i].preco*tabela_encomendas[ide].encomenda_produtos[i].quant);
				tabela_produtos[idp].quant += tabela_encomendas[ide].encomenda_produtos[i].quant;
				tabela_encomendas[ide].encomenda_produtos[i].quant = 0;
				break;
			}
		}
	}
}

/* Calcula o custo de uma encomenda */ 
void C(int contador_encomendas, struct encomenda tabela_encomendas[MAXENCOM])
{
 int ide;
 getchar();
 scanf("%d", &ide);
 if (ide >= contador_encomendas){
 	printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
 }
 else {
 	printf("Custo da encomenda %d %d.\n", ide, tabela_encomendas[ide].preco_total);
 }
}

/* Altera o pre?o de um produto existente no sistema */
void p(int contador, int contador_encomendas, struct produto tabela_produtos[MAXIDENT], struct encomenda tabela_encomendas[MAXENCOM])
{
	int idp, preco, i, j;
	getchar();
	scanf("%d", &idp);
	scanf(":%d", &preco);
	if (idp >= contador){
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
	}
	else {
		tabela_produtos[idp].preco = preco;
		for(i=0; i<contador_encomendas; i++){
			for (j=0; j < tabela_encomendas[i].numero_produtos; j++){
				if(tabela_encomendas[i].encomenda_produtos[j].ident==idp){
					/* altera o pre?o do produto na encomenda */
					tabela_encomendas[i].preco_total -= (tabela_encomendas[i].encomenda_produtos[j].preco*tabela_encomendas[i].encomenda_produtos[j].quant);
					tabela_encomendas[i].encomenda_produtos[j].preco = preco;
					tabela_encomendas[i].preco_total += (tabela_encomendas[i].encomenda_produtos[j].preco*tabela_encomendas[i].encomenda_produtos[j].quant);
				}
			}
		}

	}
}

/* Lista a descri??o e a quantidade de um produto numa encomenda */
void E(int contador, int contador_encomendas, struct encomenda tabela_encomendas[MAXENCOM], struct produto tabela_produtos[MAXIDENT])
{
	int ide, idp, i;
	getchar();
	scanf("%d", &ide);
	scanf(":%d", &idp);
	if (ide >= contador_encomendas){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
	else if (idp >= contador){
		printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	}
	else {
		for (i=0; i < tabela_encomendas[ide].numero_produtos; i++){
			if (tabela_encomendas[ide].encomenda_produtos[i].ident == idp){
				printf("%s %d.\n", tabela_encomendas[ide].encomenda_produtos[i].desc, tabela_encomendas[ide].encomenda_produtos[i].quant);
				i=-1;
				break;
			}
		}
		/* se o produto n?o existir na encomenda devolve 0*/
		if (i!=-1){
			printf("%s 0.\n", tabela_produtos[idp].desc);
		}
	}
}

/* Lista o identificador da encomenda em que o produto dado ocorre mais vezes */
void m(int contador_encomendas, int contador, struct encomenda tabela_encomendas[MAXENCOM])
{
	int idp, i, j, qtd_max, cont_max;
	qtd_max=0;
	cont_max=-1;
	getchar();
	scanf("%d", &idp);
	if (idp >= contador){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	}
	else {
		for(i=0; i<contador_encomendas; i++){
			for (j=0; j < tabela_encomendas[i].numero_produtos; j++){
				if(tabela_encomendas[i].encomenda_produtos[j].ident==idp){
					if(tabela_encomendas[i].encomenda_produtos[j].quant > qtd_max){
						qtd_max=tabela_encomendas[i].encomenda_produtos[j].quant;
						/* guarda na vari?vel o identificador da encomenda*/
						cont_max=i;
					}
					break;
				}
			}
		}
		/* verifica se existe o produto idp nas encomendas e se a sua quantidade ? maior que 0*/
		if(qtd_max>0 && cont_max>-1)
			printf("Maximo produto %d %d %d.\n", idp, cont_max, qtd_max);
	}
}

/* Fun??o auxiliar da fun??o l*/
/* Junta dois subarrays de 'p' e ordena-os*/
void merge(int *aux, int *p, int l, int m, int r, struct produto tabela_produtos[MAXIDENT])
{
	int i, j, k, x;
    i = l;
    j = m + 1;
    k = l;
    while(i <= m && j <= r){
        if(tabela_produtos[p[i]].preco <= tabela_produtos[p[j]].preco){
            aux[k] = p[i];
            i++;
        }
        else{
            aux[k] = p[j];
            j++; 
        }
        k++;
    }

    while(i <= m){
        aux[k] = p[i];
        i++;
        k++;
    }

    while(j <= r){
        aux[k] = p[j];
        j++;
        k++;
    }
    /*Copia os elementos que foram ordenados para o auxiliar*/
    for(x = l; x <= r; x++)
        p[x] = aux[x];
}

/* Fun??o auxiliar da fun??o l*/
/* Separa o array 'p' em dois e ordena-os */
void mergeSort(int *aux, int *p, int l, int r, struct produto tabela_produtos[MAXIDENT])
{
	if(l < r){
		int m = (l+r) / 2;
		/* Ordena a primeira e a segunda metade */
		mergeSort(aux, p, l, m, tabela_produtos);
		mergeSort(aux, p, m+1, r, tabela_produtos);
		merge(aux, p, l, m, r, tabela_produtos);
	}
}

/* Lista todos os produtos existentes no sistema por ordem crescente de pre?o */
void l(int contador, struct produto tabela_produtos[MAXIDENT])
{
	int p[MAXIDENT], aux[MAXIDENT], i;
	if (contador == 0){
		printf("Produtos\n");
	}
	else{
		for (i=0; i<contador; i++){
			p[i]=tabela_produtos[i].ident;
		}
		mergeSort(aux, p, 0, contador-1, tabela_produtos);

		printf("Produtos\n");
		for (i=0; i < contador; i++){
			printf("* %s %d %d\n", tabela_produtos[p[i]].desc, tabela_produtos[p[i]].preco, tabela_produtos[p[i]].quant);
		}
	}
}

/* Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
void L(int contador_encomendas, struct encomenda tabela_encomendas[MAXENCOM])
{
	int ide, i, j;
	char tab[MAXIDENT][MAXDESC], temp[MAXDESC];
	getchar();
	scanf("%d", &ide);
	if (ide >= contador_encomendas){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
	else if (tabela_encomendas[ide].numero_produtos==0){
		printf("Encomenda %d\n", ide);
	}
	else {
		for(i=0; i<tabela_encomendas[ide].numero_produtos; i++){
			/* copia todas as descric?es para outro array */
			strcpy(tab[i], tabela_encomendas[ide].encomenda_produtos[i].desc);
		}
		for(i=0;i<tabela_encomendas[ide].numero_produtos;i++){
      		for(j=i+1;j<tabela_encomendas[ide].numero_produtos;j++){
         		/* compara as strings */
         		if(strcmp(tab[i],tab[j])>0){
         			/* ordena as strings por ordem alfab?tica em 'tab' */
            		strcpy(temp,tab[i]);
            		strcpy(tab[i],tab[j]);
            		strcpy(tab[j],temp);
            	}
            }
        }
        printf("Encomenda %d\n", ide);
        for(i=0;i<tabela_encomendas[ide].numero_produtos;i++){
        	for(j=0;j<tabela_encomendas[ide].numero_produtos;j++){
        		if(strcmp(tabela_encomendas[ide].encomenda_produtos[j].desc, tab[i]) == 0 && tabela_encomendas[ide].encomenda_produtos[j].quant > 0){
        			printf("* %s %d %d\n", tab[i], tabela_encomendas[ide].encomenda_produtos[j].preco, tabela_encomendas[ide].encomenda_produtos[j].quant);
        		}
        	}
        }
	}
}


























