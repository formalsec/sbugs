#include <stdio.h>
#include <string.h>
/* Define o numero maximo de produtos no sistema */
#define NUM_TOTAL_PRODUTOS 10000
/* Define o numero maximo de encomendas no sistema */
#define NUM_TOTAL_ENCOMENDAS 500
/* Define o numero maximo de caracteres que a descricao de um produto pode ter */
#define PRODUTO_DESC 64
/* Define o numero maximo de produtos que pode existir numa encomenda */
#define ENCOMENDA_PRODUTOS_IDS 200
/* Define a quantidade maxima de um produto que pode haver numa encomenda */
#define ENCOMENDA_PRODUTOS_QTDS 200
/* PRODUTOS */
/* Criacao do produto e sua introducao no sistema */
/* Cria a estrutura produto */
struct Produto { 
    char d[PRODUTO_DESC];
    int preco;
    int peso;
    int qtd;
    int id;
};
/* Vetor com todos os produtos */
struct Produto produtos[NUM_TOTAL_PRODUTOS];
/* Numero de produtos no vetor */
int num_produtos=0; 
/* Funcao que adiciona um novo produto ao sistema*/
void criaproduto (){
    struct Produto produto;
    int produto_id = num_produtos;
    produto.id = produto_id;
    scanf(" %[^:]:%d:%d:%d", produto.d, &produto.preco, &produto.peso, &produto.qtd);
    produtos[num_produtos] = produto; /* Cria um novo produto no sistema com o respetivo idp */
    num_produtos++; /* Atualiza o numero de produtos no vetor */
    printf("Novo produto %d.\n", produto_id);
}
/*  Funcoes de gestao de stock no sistema */
/* Funcao que adiciona stock a um produto existente no sistema*/
void adicionastock() {
    int n, id,qtd;
    scanf(" %d:%d", &id, &qtd);
    if (id >= num_produtos) { /* Verifica se o produto existe no sistema */
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
        return;
    }
    for (n = 0; n < num_produtos; n++) {
        if ( produtos[n].id == id ) {
            produtos[n].qtd += qtd; /* Se existir acrescentamos a quantidade pretendida ao stock */
            break;
        }
    }
}
/* Funcao que remove stock a um produto existente no sistema e se a quantidade de produto no sistema o permitir*/
void removestock() 	{
    int n, id,qtd;
    scanf(" %d:%d", &id, &qtd);
    if (id >= num_produtos) { /* Verifica se o produto existe no sistema */
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
        return;
    }
    for (n = 0; n < num_produtos; n++) {
        if ( produtos[n].id == id ) {
            if (qtd <= produtos[n].qtd) { /* Verifica se existe quantidade suficiente do produto para ser removida */
                produtos[n].qtd -= qtd; /* Se existir retiramos a quantidade pretendida ao stock */
                return;
            }
            else {
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id);
            }
        }
    }
}
/* Funcao relativa ao custo dos produtos no sistema */
/* Funcao que altera o preco de um produto existente no sistema */
void mudapreco() {
    int n, id,preco;
    scanf(" %d:%d", &id, &preco);
    if (id >= num_produtos) { /* Verifica se o produto existe no sistema */
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id);
        return;
    }
    for (n = 0; n < num_produtos; n++) {
        if ( produtos[n].id == id ) {
            produtos[n].preco = preco; /* Se existir alteramos o preco ao produto */
            break;
        }
    }
}
/* Funcoes de ordenacao dos produtos no sistema */
/* Vetor com o numero maximo de produtos */
int a[10000];
/* 	Funcao auxiliar de ordenacao que devolve um vetor ordenado a[l...r], dados dois vetores a[l...m] e a[m+1...r]
 *  Nos primeiros dois ciclos for controi se o vetor auxiliar 
 *  No terceiro for compara os precos dos produtos
 *  Se forem igual a seguir com os identificadores dos mesmos 
 *  E de seguida os elementos das pontas vao sendo escolhidos de forma a ordenar a[], pela ordem pretendida */
void merge(int a[], int left, int m, int right) {
    int i, j, k, aux[10000];
  for (i = m+1; i > left; i--) {
    aux[i-1] = a[i-1];
  }
  for (j = m; j < right; j++) {
    aux[right+m-j] = a[j+1];
  }
  for (k = left; k <= right; k++) {
    if ( produtos[ aux[j] ].preco < produtos[ aux[i] ].preco || i > m ) {
      a[k] = aux[j--];
    }
    else {
      a[k] = aux[i++];
    }
  }
 }
/* Funcao recursiva auxiliar de ordenacao 
 * Parte o vetor a[] em duas particoes mais pequenas 
 * E posteriormente aplica o algoritmo recursivamente as duas particoes formadas */
void mergesort(int a[], int l, int r) {
	int m=(r+l)/2;
	if (r<=l) {
		return;
	}
	mergesort(a,l,m);
	mergesort(a,m+1,r);
	merge(a,l,m,r);
}
/* Funcao que lista e apresenta os produtos que haja no sistema organizados recorrendo as funcoes merge e mergesort, para os organizar */
void listaproduto(){
	int i, n;
	for (i=0; i < num_produtos; i++) { /* Selecao de todos os produtos existentes no vetor */
		a[i]=i;
	}
	mergesort(a,0,num_produtos-1);
	printf("Produtos\n");
	for (n = 0; n < num_produtos; n++) {
		printf("* %s %d %d\n", produtos[a[n]].d, produtos[a[n]].preco, produtos[a[n]].qtd);
	}
}
/* ENCOMENDAS */
/* Criacao de uma encomenda no sistema */
/* Cria a estrutura encomenda */
struct Encomenda { 
    int peso;
    int id;
    int produto_ids[ENCOMENDA_PRODUTOS_IDS];
    int produto_qtds[ENCOMENDA_PRODUTOS_QTDS];
    int num_produtos;
};
/* Vetor com todas as encomendas */
struct Encomenda encomendas[NUM_TOTAL_ENCOMENDAS]; 
/* Numero de encomendas no vetor */
int num_encomendas=0; 
/* Funcao que cria uma nova encomenda no sistema*/
void criaencomenda() {
    struct Encomenda encomenda;
    int encomenda_id = num_encomendas;
    encomenda.peso=0;
    encomenda.num_produtos=0;
    encomendas[num_encomendas] = encomenda; /* Cria uma nova encomenda no sistema com o respetivo ide */
    num_encomendas++; /* Atualiza o numero de produtos no vetor */
    printf("Nova encomenda %d.\n", encomenda_id);
}
/*  Funcoes de gestao de produtos nas encomendas */
/* Funcao que adiciona um produto a uma encomenda, se esse produto ja existir adiciona a quantidade pretendida ao produto */
void adicionaproduto() {
    int idp, ide, qtdp, n, produto_id;
    scanf(" %d:%d:%d", &ide,&idp, &qtdp);
    if (ide >= num_encomendas) { /* Verifica se a encomenda existe */
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    if (idp >= num_produtos) { /* Verifica se o produto existe no sistema */
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp,ide);
        return;
    }
    for (n = 0; n < num_produtos; n++) {
        if ( produtos[n].id == idp ) {
            produto_id = n;
            break;
        }
    }
    if (qtdp > produtos[produto_id].qtd) { /* Verifica se existe no sistema a quantidade do produto que pretendemos acrescentar a encomenda */
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }
    if (encomendas[ide].peso + produtos[produto_id].peso * qtdp <= 200){ /* Verifica se a encomenda excede o peso de 200 */
        for (n=0;n < encomendas[ide].num_produtos ;n++) {
            if (idp == (encomendas[ide].produto_ids[n])) {
                encomendas[ide].produto_qtds[n]+=qtdp;
                encomendas[ide].peso += produtos[produto_id].peso * qtdp; /* Atualiza o peso da encomenda*/
                produtos[produto_id].qtd -= qtdp;
                return;
            }
        }
    }
    else { 
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }
    encomendas[ide].produto_ids[ encomendas[ide].num_produtos ] = idp; /* Acrescenta um novo produto a encomenda */
    encomendas[ide].produto_qtds[ encomendas[ide].num_produtos ] = qtdp; /* Acrescenta a quantidade pretendida desse produto a encomenda */
    encomendas[ide].num_produtos += 1; /* Atualiza o numero de produtos na encomenda */
    produtos[produto_id].qtd -= qtdp; /* Tira a quantidade acrescentada a encomenda ao stock no sistema */ 
    encomendas[ide].peso += produtos[produto_id].peso * qtdp; /* Atualiza o peso da encomenda*/
}
/* Funcao que remove um produto de uma encomenda */
void removeproduto() {
    int idp, ide, n, i, produto_id;
    scanf(" %d:%d", &ide,&idp);
    if (ide >= num_encomendas) { /* Verifica se a encomenda existe */
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    if (idp >= num_produtos) { /* Verifica se o produto existe no sistema */
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp,ide);
        return;
    }
    for (n=0;n < encomendas[ide].num_produtos ;n++) {
        if (idp == (encomendas[ide].produto_ids[n])) {
            for (i = 0; i < num_produtos; i++) {
                if ( produtos[i].id == idp ) {
                    produto_id = i;
                    break;
                }
            }
            produtos[produto_id].qtd += encomendas[ide].produto_qtds[n];
            encomendas[ide].peso -= produtos[produto_id].peso * encomendas[ide].produto_qtds[n];
            encomendas[ide].produto_ids[n] = encomendas[ide].produto_ids[ encomendas[ide].num_produtos - 1]; /* Copia o ultimo elemento do vetor e coloca o noutra posicao */
            encomendas[ide].produto_qtds[n]= encomendas[ide].produto_qtds[ encomendas[ide].num_produtos - 1];  /* Copia o ultimo elemento do vetor e coloca o noutra posicao */
            encomendas[ide].num_produtos -=1; /* Retira o ultimo elemento do vetor (o produto em causa) a encomenda */
            return;
        }
    }
}
/* Funcoes de ordenacao dos produtos na encomenda */
/* Vetor com o numero maximo de produtos numa encomenda */
int b[200];
/* 	Funcao auxiliar de ordenacao que devolve um vetor ordenado a[l...r], dados dois vetores a[l...m] e a[m+1...r]
 *  Nos primeiros dois ciclos for controi se o vetor auxiliar 
 *  No terceiro for compara as descricoes dos produtos
 *  E de seguida os elementos das pontas vao sendo escolhidos de forma a ordenar a[], pela ordem pretendida */
void merge_L(int b[], int left, int m, int right, int ide) {
	int i, j, k, aux[200];
  for (i = m+1; i > left; i--) 
    aux[i-1] = b[i-1];
  for (j = m; j < right; j++) 
    aux[right+m-j] = b[j+1];
  for (k = left; k <= right; k++) {
    if (strcmp(produtos[ encomendas[ide].produto_ids[aux[j]] ].d,produtos[ encomendas[ide].produto_ids[aux[i]] ].d) < 0) {
      b[k] = aux[j--];
	}
    else {
      b[k] = aux[i++];
	}
	}
}
/* Funcao recursiva auxiliar de ordenacao 
 * Parte o vetor a[] em duas particoes mais pequenas 
 * E posteriormente aplica o algoritmo recursivamente as duas particoes formadas */
void mergesort_L(int b[], int l, int r, int ide) {
	int m=(r+l)/2;
	if (r<=l) 
		return;
	
	mergesort_L(b,l,m, ide);
	mergesort_L(b,m+1,r, ide);
	merge_L(b,l,m,r, ide);
}
/* Funcao que lista e apresenta os produtos que haja no sistema organizados recorrendo as funcoes merge_L e mergesort_L, para os organizar */
void listaencomenda(){
	int i, n, ide;
	scanf("%d", &ide);
	if (ide >= num_encomendas) { /* Verifica se a encomenda existe */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
	for (i=0; i < encomendas[ide].num_produtos; i++) /* Selecao de todos os produtos existentes no vetor */
		b[i] = i;
	
	mergesort_L(b,0,encomendas[ide].num_produtos-1,ide);
	printf("Encomenda %d\n", ide);
	for (n = 0; n < encomendas[ide].num_produtos; n++) 
		printf("* %s %d %d\n", produtos[ encomendas[ide].produto_ids[ b[n] ] ].d, produtos[ encomendas[ide].produto_ids[ b[n] ] ].preco, encomendas[ide].produto_qtds[ b[n] ]);
	
}
/* Funcoes de retorno */
/* Funcao que retorna o identificador em que um determinado produto ocorre mais vezes, em caso de empate, retorna a encomenda com o menor identificador */
void listaidrepetido () {
     int id,n,ide,qtd,idemax,qtdmax;
     qtdmax= -1;
     idemax=-1;
     scanf(" %d", &id);
     if (id >= num_produtos) { /* Verifica se o produto existe no sistema */
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id);
        return;
    }
    for (ide = 0; ide < num_encomendas; ide++) {
        for (n=0; n < encomendas[ide].num_produtos; n++) {
            if ( encomendas[ide].produto_ids[n] == id) {
                qtd = encomendas[ide].produto_qtds[n];
                if ( qtd > qtdmax) {
                    qtdmax=qtd; /* quantidade maxima dum produto nas encomendas existentes */
                    idemax=ide; /* Ide da encomenda com maior quantidade */
                }
                else if ((qtd == qtdmax) && (ide < idemax)) {
                    qtdmax = qtd;
                    idemax=ide; /* Ide minimo entre encomendas com iguais quantidades */
                }
            }
        }
    }
    if (idemax != -1) {
    printf("Maximo produto %d %d %d.\n", id, idemax, qtdmax);
    }
}
/* Funcao que retorna a descricao de um produto e a quantidade dele numa dada encomenda */
void listadesceqtd() {
    int idp, ide, n, i;
    scanf(" %d:%d",&ide,&idp);
    if (ide >= num_encomendas) { /* Verifica se a encomenda existe */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    if (idp >= num_produtos) { /* Verifica se o produto existe no sistema */
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }
    for(n=0; n < encomendas[ide].num_produtos; n++) { 
        if (encomendas[ide].produto_ids[n] == idp) { /* Seleciona cada produto da encomenda separadamente */
            for (i = 0; i < num_produtos; i++) {
                if ( produtos[i].id == idp ) {
                    printf("%s %d.\n", produtos[i].d ,encomendas[ide].produto_qtds[n]);
                    return;
                }
            }
        }
    }
    for (i = 0; i < num_produtos; i++) {
        if ( produtos[i].id == idp ) {
            printf("%s 0.\n", produtos[i].d);
            return;
        }
    }
}
/* Funcao que calcula o custo de uma encomenda */
void calculacusto() {
    int ide, custo, n, produto_id, i;
    custo=0;
    scanf(" %d", &ide);
    if (ide >= num_encomendas) { /* Verifica se a encomenda existe */
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n" ,ide);
        return;
    }
    for (n=0; n < encomendas[ide].num_produtos;n++) {
        for (i = 0; i < num_produtos; i++) {
            if ( produtos[i].id == encomendas[ide].produto_ids[n] ) {
                produto_id = i;
                break;
            }
        }
        
        custo += encomendas[ide].produto_qtds[n] * produtos[produto_id].preco; /* Multiplica o preco de cada produto pela respetiva quantidade que existe na encomenda e soma tudo */ 
    }
    printf("Custo da encomenda %d %d.\n", ide, custo);
}
/* PRINCIPAL */
/* Funcao que seleciona o comando a executar */
 int main () { 
    int c;
    while (1) { /* Ciclo criado para se poder efetuar varios comandos durante a execucao do programa */
        c=getchar();
        if (c == EOF){
            return 0;
        }
        switch (c) { /* Seleciona e executa o respetivo comando de acordo com os inputs */
            case 'a':
                criaproduto();
                break;
            case 'q':
                adicionastock();
                break;
			case 'r':
                removestock();
                break;
			 case 'p':
                mudapreco();
                break;
			case 'l':
                listaproduto();
                break;
            case 'N':
                criaencomenda();
                break;
            case 'A':
                adicionaproduto();
                break;
			case 'R':
                removeproduto();
                break;
			case 'L':
                listaencomenda();
                break;
			case 'm':
                listaidrepetido();
                break;
            case 'E':
                listadesceqtd();
                break;
            case 'C':
                calculacusto();
                break;
            case 'x': /* Termina o programa */
                return 0;
        }
    }
    return 0;
}