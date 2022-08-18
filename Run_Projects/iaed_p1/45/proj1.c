#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/*tamanho maximo de uma string*/
#define STRINGSIZE 64
/*numero maximo de produtos*/
#define MAXPRODUCTS 10000
/*numero maximo de encomendas*/
#define MAXORDERS 500
/*peso maximo de uma encomenda*/
#define MAXWEIGHT 200
/*valor maximo de idp*/
#define MAXIDP 9999
/*valor maximo de ide*/
#define MAXIDE 499

/*contador de idp*/
long int IDP=0;
/*contador de ide*/
int IDE=0;

/*caracterizacao de um produto*/
typedef struct produto{
    char descricao[STRINGSIZE];
    long int peso, preco, qtd, idp;  
} produto;

/*vetor de produtos - stack*/
produto produtos[MAXPRODUCTS];

/*caracterizacao de uma encomenda*/
typedef struct encomenda {
    int status;
    int peso, numProdutos;
    produto listaProdutos[MAXWEIGHT];
} encomenda;

/*vetor das encomendas*/
encomenda encomendas[MAXORDERS];

/*funcao usada pela funcao partition para alterar elementos de posicao*/
void exch (int *a, int *b);

/*funcao usada pela partition_l*/
int less_l(int a, int b);
/*funcao usada pela funcao quicksort_l*/
int partition_l(int a[], int left, int right);
/*quicksort_l*/
void quicksort_l(int a[], int left, int right);

/*funcao usada pela partition_L*/
int less_L(int a, int b, int ide);
/*funcao usada pela funcao quicksort_L*/
int partition_L(int a[], int left, int right, int ide);
/*quicksort_L*/
void quicksort_L(int a[], int left, int right, int ide);

void a();
void q();
void N();
void A();
void r();
void R();
void C();
void p();
void E();
void m();
void l();
void L();

void app();

int main() {
    app();
    return 0;
}





/*exch: recebe dois inteiros, a e b, e troca os valores das respetivas variaveis*/
void exch (int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/*less_l: compara o preco de dois produtos, a e b, e retorna 1 se a<b*/
int less_l(int a, int b) {
    if (produtos[a].preco<produtos[b].preco) return 1;
    if (produtos[b].preco>produtos[a].preco) return 0;
    if (produtos[b].preco==produtos[a].preco) {
        if (produtos[a].idp<produtos[b].idp) return 1;
        if (produtos[b].idp>produtos[a].idp) return 0;     
    }
    return 0;
}

/*partition_l:*/
int partition_l(int a[], int left, int right) {
    int i = left-1;
    int j = right;
    int v = a[right];
    while (i < j) {
        while (less_l(a[++i], v));
        while (less_l(v, a[--j]))
            if (j == left)
                break;
        if (i < j)
            exch(&a[i], &a[j]);
    }
    exch(&a[i], &a[right]);
    return i;
}

/*quicksort_l:*/
void quicksort_l(int a[], int left, int right) {
    int i;
    if (right <= left) return;
    i = partition_l(a, left, right);
    quicksort_l(a, left, i-1);
    quicksort_l(a, i+1, right);
}

/*less_L: compara duas strings e retorna 1 se a primeira string aparecer primiero alfabeticamente*/
int less_L(int a, int b, int ide) {
    if (strcmp(encomendas[ide].listaProdutos[a].descricao,encomendas[ide].listaProdutos[b].descricao)<0) return 1;
    if (strcmp(encomendas[ide].listaProdutos[a].descricao,encomendas[ide].listaProdutos[b].descricao)>0) return 0;
    return 0;
}

/*partition_L: */
int partition_L(int a[], int left, int right, int ide) {
    int i = left-1;
    int j = right;
    int v = a[right];
    while (i < j) {
        while (less_L(a[++i], v, ide));
        while (less_L(v, a[--j], ide))
            if (j == left)
                break;
        if (i < j)
            exch(&a[i], &a[j]);
    }
    exch(&a[i], &a[right]);
    return i;
}

/*quicksort_L: */
void quicksort_L(int a[], int left, int right, int ide) {
    int i;
    if (right <= left) return;
    i = partition_L(a, left, right, ide);
    quicksort_L(a, left, i-1, ide);
    quicksort_L(a, i+1, right, ide);
}

/*a: adiciona um novo produto ao sistema*/
void a() {
    int peso=0;
    long int preco=0, qtd=0;
    char descricao[STRINGSIZE];
    produto p;
    
    /*leitura dos dados do standard input no formato:*/
    /* descricao:preco:peso:qtd*/
    getchar();
    scanf("%[^:]:%ld:%d:%ld", descricao, &preco, &peso, &qtd);

    if (preco>0&&peso>0&&qtd>=0) {
        p.peso=peso; p.preco=preco; p.qtd=qtd;
        strcpy(p.descricao, descricao);
        p.idp=IDP;
        produtos[IDP]=p;
        printf("Novo produto %ld.\n", IDP);
        IDP++;
    }
}

/*q: adiciona stock a um produto existente no sistema*/
void q() {
    long int idp=0, qtd=0;

    /*leitura dos dados do standard input no formato:*/
    /* idp:qtd*/
    getchar();
    scanf("%ld:%ld", &idp, &qtd);

    if (idp>=0&&idp<=MAXIDP&&qtd>=0) {
        if (idp<IDP) {
            produtos[idp].qtd=qtd+produtos[idp].qtd;
            return;
        }
        printf("Impossivel adicionar produto %ld ao stock. Produto inexistente.\n", idp);
    }
}

/*N: cria uma nova encomenda*/
void N() {
    printf("Nova encomenda %d.\n", IDE);
    encomendas[IDE].status=1;
    IDE++;
}

/*A: adiciona um produto a uma encomenda*/
void A() {
    int i=0, ide=0;
    long int idp=0 ,qtd=0;

    /*leitura dos dados do standard input no formato:*/
    /*  ide:idp:qtd*/
    getchar();
    scanf("%d:%ld:%ld", &ide, &idp, &qtd);

    if (encomendas[ide].status==0) {
        printf("Impossivel adicionar produto %ld a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    if (idp>=IDP) {
        printf("Impossivel adicionar produto %ld a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    if (produtos[idp].qtd-qtd<0) {
        printf("Impossivel adicionar produto %ld a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }
    if (produtos[idp].peso*qtd+encomendas[ide].peso>MAXWEIGHT) {
        printf("Impossivel adicionar produto %ld a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }

    /*caso o produto ja faca parte da encomenda aumenta a quantidade desse produto*/
    for (i=0;i<encomendas[ide].numProdutos;i++) {
        if (idp==encomendas[ide].listaProdutos[i].idp && qtd<=produtos[idp].qtd) {
            encomendas[ide].listaProdutos[i].qtd = encomendas[ide].listaProdutos[i].qtd+qtd;
            produtos[idp].qtd = produtos[idp].qtd-qtd;
            encomendas[ide].peso = produtos[idp].peso*qtd+encomendas[ide].peso;
            return;
        }
    }
    /*caso o produto nao faca parte da encomenda coloca esse produto na encomenda*/
    i=encomendas[ide].numProdutos;

    strcpy(encomendas[ide].listaProdutos[i].descricao, produtos[idp].descricao);
    encomendas[ide].listaProdutos[i].peso = produtos[idp].peso;
    encomendas[ide].listaProdutos[i].idp = produtos[idp].idp;
    encomendas[ide].listaProdutos[i].preco = produtos[idp].preco;
    encomendas[ide].listaProdutos[i].qtd = qtd;

    /*incrementa o numero de produtos da encomenda*/
    encomendas[ide].numProdutos++;

    /*calcula o peso total da encomenda*/
    encomendas[ide].peso = produtos[idp].peso*qtd+encomendas[ide].peso;

    /*reducao a quantidade total do produto*/
    if (qtd<=produtos[idp].qtd) {
        produtos[idp].qtd = produtos[idp].qtd-qtd;    
        return;
    }
}

/*r: remove stock a um produto existente*/
void r() {
    long int idp=0, qtd=0;

    /*leitura dos dados do standard input no formato:*/
    /*  idp:qtd*/
    getchar();
    scanf("%ld:%ld", &idp, &qtd);

    if (idp>=IDP) {
        printf("Impossivel remover stock do produto %ld. Produto inexistente.\n", idp);
        return;
    }
    if (produtos[idp].qtd-qtd<0) {
        printf("Impossivel remover %ld unidades do produto %ld do stock. Quantidade insuficiente.\n", qtd, idp);
        return;
    }
    
    /*reducao da quantidade do produto*/
    produtos[idp].qtd=produtos[idp].qtd-qtd;
}

/*R: remove um produto de uma encomenda*/
void R() {
    int ide=0, i=0, j=0;
    long int idp=0;

    /*leitura dos dados do standard input no formato:*/
    /*  ide:idp*/  
    getchar();
    scanf("%d:%ld", &ide, &idp);

    if (encomendas[ide].status==0) {
        printf("Impossivel remover produto %ld a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    if (idp>=IDP) {
        printf("Impossivel remover produto %ld a encomenda %d. Produto inexistente.\n", idp, ide);
        return; 
    }

    /*procura o produto na encomenda*/
    for (i=0;i<encomendas[ide].numProdutos;i++) {
        if (idp==encomendas[ide].listaProdutos[i].idp) {
            /*aumenta a quantidade do produto*/
            produtos[idp].qtd=produtos[idp].qtd+encomendas[ide].listaProdutos[i].qtd;
            /*calcula o peso total da encomenda*/
            encomendas[ide].peso=encomendas[ide].peso-(encomendas[ide].listaProdutos[i].qtd*encomendas[ide].listaProdutos[i].peso);
            if (i<encomendas[ide].numProdutos) {
                /*decrementa o numero de produtos da encomenda*/
                encomendas[ide].numProdutos--;
                for (j=i; j<encomendas[ide].numProdutos; j++) 
                encomendas[ide].listaProdutos[j] = encomendas[ide].listaProdutos[j+1]; 
            }
        }
    }
}

/*C: calcula o custo de uma encomenda*/
void C() {
    int ide=0, i=0;
    long int custo=0;

    /*leitura dos dados do standard input no formato:*/
    /*  ide*/
    getchar();
    scanf("%d", &ide);

    if (encomendas[ide].status==0) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    /*calculo do custo de uma encomenda*/
    for (i=0;i<encomendas[ide].numProdutos;i++) {
        custo=custo+(encomendas[ide].listaProdutos[i].qtd*encomendas[ide].listaProdutos[i].preco);
    }
    printf("Custo da encomenda %d %ld.\n", ide, custo);
}

/*p: altera o preco de um produto existente no sistema*/
void p() {
    long int idp=0, preco=0;
    int i=0, j=0;

    /*leitura dos dados do standard input no formato:*/
    /*  idp:preco*/
    getchar();
    scanf("%ld:%ld", &idp, &preco);

    if (idp>=IDP) {
        printf("Impossivel alterar preco do produto %ld. Produto inexistente.\n", idp);
        return;
    }

    /*altera o preco do produto no stack*/
    produtos[idp].preco=preco;

    /*altera o preco do produto na lista de encomendas*/
    for(i=0;i<IDE;i++)
        if(encomendas[i].numProdutos!=0)
            for (j=0;j<encomendas[i].numProdutos;j++)
                if (idp==encomendas[i].listaProdutos[j].idp)
                    encomendas[i].listaProdutos[j].preco=preco;
}

/*E: retorna a descricao e a quantidade de um produto numa dada encomenda*/
void E() {
    int ide=0, i=0;
    long int idp=0;

    /*leitura dos dados do standard input no formato:*/
    /*  ide:idp*/
    getchar();
    scanf("%d:%ld", &ide, &idp);

    if (encomendas[ide].status==0) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    if (idp>=IDP) {
        printf("Impossivel listar produto %ld. Produto inexistente.\n", idp);
        return;
    }

    /*procura o produto na lista de encomendas*/
    for (i=0;i<encomendas[ide].numProdutos;i++) {
        if (idp==encomendas[ide].listaProdutos[i].idp) {
            printf("%s %ld.\n", encomendas[ide].listaProdutos[i].descricao, encomendas[ide].listaProdutos[i].qtd);
            return;
        }
    }
    printf("%s %d.\n", produtos[idp].descricao, 0);
}

/*m: retorna o identificador da encomenda em que um dado produto ocorre mais vezes*/
void m() {
    int i=0, j=0, ide=0;
    long int max=0, idp=0;

    /*leitura dos dados do standard input no formato:*/
    /*  idp*/
    getchar();
    scanf("%ld", &idp);

    if (idp>=IDP) {
        printf("Impossivel listar maximo do produto %ld. Produto inexistente.\n", idp);
        return;
    }

    /*retorna caso nao hajam encomendas*/
    if (encomendas[0].status==0) 
        return;

    /*procura o produto em cada lista de produtos de cada encomenda*/
    for(i=0;i<IDE;i++)
        if(encomendas[i].numProdutos!=0)
            for (j=0;j<encomendas[i].numProdutos;j++)
                if (idp==encomendas[i].listaProdutos[j].idp)
                    if (max<encomendas[i].listaProdutos[j].qtd) {
                        max=encomendas[i].listaProdutos[j].qtd;
                        ide=i;
                    }
    if (max!=0)
        printf("Maximo produto %ld %d %ld.\n", idp, ide, max);
}

/*l: lista todos os produtos existentes no sistema por ordem crescente de preco*/
void l() {
    int i=0;
    int idps[MAXIDP]; 
    printf("Produtos\n");
    if (IDP>0) {

        /*copia os idps dos produtos para um vetor*/
        for (i=0; i<IDP; i++) {
            idps[i]=produtos[i].idp;
        }

        /*realiza o quicksort do vetor de idps com base no prec dos produtos*/
        quicksort_l(idps, 0, IDP-1);
        for (i=0; i<IDP; i++) {
            printf("* %s %ld %ld\n", produtos[idps[i]].descricao, produtos[idps[i]].preco, produtos[idps[i]].qtd);
        }
    }
}

/*L: lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/
void L() {
    int ide=0, i=0;
    int idps[MAXWEIGHT];
    getchar();
    scanf("%d", &ide);
    if (encomendas[ide].status==0) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    /*copia os idps dos produtos para um vetor*/
    for(i=0;i<encomendas[ide].numProdutos;i++) {idps[i]=i;}

    /*realiza o quicksort do vetor de idps com base na descricao dos produtos*/
    quicksort_L(idps, 0, encomendas[ide].numProdutos-1, ide);
    printf("Encomenda %d\n", ide);
    for(i=0;i<encomendas[ide].numProdutos;i++)
        printf("* %s %ld %ld\n", encomendas[ide].listaProdutos[idps[i]].descricao, encomendas[ide].listaProdutos[idps[i]].preco, encomendas[ide].listaProdutos[idps[i]].qtd);
}

/*app: aplicacao*/
void app() {
    while(1) {
        char cmd = getchar();
        switch (cmd) {
            case 'a':
                a();
                break;
            case 'q':
                q();
                break;
            case 'N':
                N();
                break;
            case 'A':
                A();
                break;
            case 'r':
                r();
                break;
            case 'R':
                R();
                break;
            case 'C':
                C();
                break;
            case 'p':
                p();
                break;
            case 'E':
                E();
                break;
            case 'm':
                m();
                break;
            case 'l':
                l();
                break;
            case 'L':
                L();
                break;
            case 'x':
                return;
            default:
                break;
        }
    }
}