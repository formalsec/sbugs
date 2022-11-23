#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

/* Tamanho do vetor que armazena a descricao de um produto. */
#define TAMANHO_DESC 64
/* Numero maximo de produtos distintos. */
#define PRODUTOS_MAX 10000
/* Numero maximo de encomendas. */
#define ENCOMENDAS_MAX 500
/* Peso maximo por encomenda. */
#define PESO_MAX_ENC 200
/* Numero maximo de produtos por encomenda. */
#define PRODUTO_MAX_ENC (PESO_MAX_ENC)
/* Identificador de produto utilizado na inexistencia de produto. */
#define ID_INVALIDO -1
/* Troca dois inteiros de posicao. */
#define troca(B, A) { int p = A; A = B; B = p; }
/* Troca dois dados de encomenda de posicao. */
#define trocaDadosEnc(B, A) { dados_encomenda p = A; A = B; B = p; }


/* Estrutura que representa um produto. */
typedef struct produto {
    /* Indentificador do produto. */
    int id;
    /* Descricao do produto. */
    char desc[TAMANHO_DESC];
    /* Preco do produto. */
    int preco;
    /* Peso do produto. */
    int peso;
    /* Quantidade do produto. */
    int qtd;
}produto;

/* Estrutura que representa os dados de um produto numa encomenda. */
typedef struct dados_encomenda {
    /* Indentificador do produto. */
    int id;
    /* Quantidade do produto na encomenda. */
    int qtd;
}dados_encomenda;

/* Estrutura que representa uma encomenda. */
typedef struct encomenda {
    /* Indentificador da encomenda. */
    int id;
    /* Vetor que armazena dados sobre itens da encomenda. */
    dados_encomenda item[PRODUTO_MAX_ENC];
}encomenda;


/* Vetor que contem os produtos existentes no sistema. */
produto vetor_produtos[PRODUTOS_MAX];
/* Vetor que contem as encomendas existentes. */
encomenda vetor_encomendas[ENCOMENDAS_MAX];


void a();
void q();
void N();
int pesoEncomenda(int ide);
void A();
void r();
void R();
void C();
int quantidadeProdutoEnc(int idp, int ide);
void p();
void E();
void m();
int maiorPreco( int id1, int id2);
int particaoPreco(int vec[], int i, int j);
void ordenaPreco(int vetor_id[], int inicio, int fim);
void l();
int maiorAlfab(dados_encomenda d1, dados_encomenda d2);
int particaoAlfab(dados_encomenda vec[], int inicio, int fim);
void ordenaAlfab(dados_encomenda vetor_dados[], int inicio, int fim);
void L();


/* Le do input o carater correspondente ao comando a executar. */
int main() {
    int continua_ciclo = TRUE;
    char comando;

    /* Inicializacao com o valor de ID_INVALIDO do vetor de produtos e de encomendas. */
    memset(vetor_produtos, ID_INVALIDO, sizeof(vetor_produtos));
    memset(vetor_encomendas, ID_INVALIDO, sizeof(vetor_encomendas));

    /* Aguarda a insercao de um carater correspondente a um comando. */
    while (continua_ciclo) {
        comando = getchar();
        switch (comando) {
            case 'a':
                getchar();
                a();
                break;

            case 'q':
                getchar();
                q();
                break;
            
            case 'N':
                getchar();
                N();
                break;

            case 'A':
                getchar();
                A();
                break;

            case 'r':
                getchar();
                r();
                break;
            
            case 'R':
                getchar();
                R();
                break;

            case 'C':
                getchar();
                C();
                break;
            
            case 'p':
                getchar();
                p();
                break;
            
            case 'E':
                getchar();
                E();
                break;
            
            case 'm':
                getchar();
                m();
                break;
            
            case 'l':
                getchar();
                l();
                break;

            case 'L':
                getchar();
                L();
                break;

            case 'x':
                continua_ciclo = FALSE;
                break;
        }
    }
    return 0;
}


/* 
Le do input a descricao, preco, peso e quantidade de um novo produto
e adiciona-o ao vetor global de produtos. 
*/
void a() {
    /* Menor valor disponivel para identificador do novo produto. */
    static int i = 0;
    
    vetor_produtos[i].id = i;
    scanf("%[^:]:%d:%d:%d", vetor_produtos[i].desc, &vetor_produtos[i].preco, &vetor_produtos[i].peso, &vetor_produtos[i].qtd);

    printf("Novo produto %d.\n", vetor_produtos[i++].id);
}


/* 
Le do input o identificador de um produto e uma quantidade 
que eh adicionada a quantidade do produto. 
*/
void q() {
    int idp, qtd;

    scanf("%d:%d", &idp, &qtd);
    
    if (vetor_produtos[idp].id != ID_INVALIDO) {
        vetor_produtos[idp].qtd += qtd;
    }
    else {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
}


/* Adiciona uma nova encomenda ao vetor global de encomendas. */
void N() {
    /* Menor valor disponivel para identificador da nova encomenda. */
    static int i = 0;
       
    vetor_encomendas[i].id = i;
    printf("Nova encomenda %d.\n", vetor_encomendas[i++].id);
}


/* 
Recebe um identificador de uma encomenda e devolve 
a soma do peso de todos os seus produtos.
*/
int pesoEncomenda(int ide) {
    int i;
    int peso_enc = 0;

    /* Para cada produto da encomenda, o peso desta eh aumentado em funcao do peso da quantidade do produto. */
    for (i = 0; i < PRODUTO_MAX_ENC && vetor_encomendas[ide].item[i].id != ID_INVALIDO; i++) {
        peso_enc += vetor_produtos[vetor_encomendas[ide].item[i].id].peso * vetor_encomendas[ide].item[i].qtd;
    }

    return peso_enc;

}


/* 
Le do input um identificador de ecomenda, um identificador de produto e uma quantidade 
e adiciona os dados do produto a encomenda. 
*/
void A() {
    int ide, idp, qtd_prod;
    int i;

    scanf("%d:%d:%d", &ide, &idp, &qtd_prod);

    if (vetor_encomendas[ide].id == ID_INVALIDO) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if (vetor_produtos[idp].id == ID_INVALIDO) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else if (vetor_produtos[idp].qtd < qtd_prod) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    }
    else {
        /* Verifica se peso atual somado com o peso do produto a acrescentar excede o limite. */
        if (pesoEncomenda(ide) + vetor_produtos[idp].peso * qtd_prod > PESO_MAX_ENC) {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        }
        else {
            vetor_produtos[idp].qtd -= qtd_prod;

           
            for (i = 0; i < PRODUTO_MAX_ENC; i++) {
                
                /* Se produto ja existir na encomenda, a quantidade eh aumentada. */
                if (vetor_encomendas[ide].item[i].id == idp) {
                    vetor_encomendas[ide].item[i].qtd += qtd_prod;
                    break;
                }
                /* Quando produto nao existe na encomenda, os seus dados sao adicionados na primeira posisao livre do vetor. */
                if (vetor_encomendas[ide].item[i].id == ID_INVALIDO) {
                    vetor_encomendas[ide].item[i].id = idp;
                    vetor_encomendas[ide].item[i].qtd = qtd_prod;
                    break;
                }
            }
        }
    }
}


/* 
Le do input um identificador de produto e uma quantidade 
e remove essa quantidade ah quantidade total do produto. 
*/
void r() {
    int id, qtd;

    scanf("%d:%d", &id, &qtd);

    if (vetor_produtos[id].id != ID_INVALIDO) {

        if (vetor_produtos[id].qtd - qtd < 0) {
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, id);
        }
        else {
            vetor_produtos[id].qtd -= qtd;
        }
        
    }
    else {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id);
    }
}


/* 
Le do input um identificador de encomenda e um identificador de produto 
e remove um produto da encomenda. 
*/
void R() {
    int ide, idp;
    int i;
    
    scanf("%d:%d", &ide, &idp);

    if (vetor_encomendas[ide].id == ID_INVALIDO) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if (vetor_produtos[idp].id == ID_INVALIDO) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else {
        for (i = 0; i < PRODUTO_MAX_ENC; i++) {
            
            if(vetor_encomendas[ide].item[i].id == idp) {

                vetor_produtos[idp].qtd += vetor_encomendas[ide].item[i].qtd;

                /* Todas as posicoes seguintes ao produto a remover, sao copiadas para a posicao anterior. */
                while (i < PRODUTO_MAX_ENC - 1) {
                    vetor_encomendas[ide].item[i] = vetor_encomendas[ide].item[i+1];
                    i++;
                }
                /* Dados da ultima posicao do vetor tornam-se invalidos. */
                vetor_encomendas[ide].item[i].id = ID_INVALIDO; 
                break;
            }
        }    
    }
}


/* Le do input um identificador de encomenda e imprime o custo da encomenda. */
void C() {
    int ide;
    int i;
    int custo = 0;

    scanf("%d", &ide);

    if (vetor_encomendas[ide].id == ID_INVALIDO) {
            printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    else {
        for (i = 0; i < PRODUTO_MAX_ENC && vetor_encomendas[ide].item[i].id != ID_INVALIDO; i++) {
            /* Custo da encomenda eh aumentado em funcao do preco e quantidade do produto. */
            custo += vetor_produtos[vetor_encomendas[ide].item[i].id].preco * vetor_encomendas[ide].item[i].qtd;
        }
        printf("Custo da encomenda %d %d.\n", ide, custo);
    }
}


/* 
Le do input um identificador de produto e um preco e altera 
o preco do produto para o valor introduzido. 
*/
void p() {
    int idp, novo_preco;

    scanf("%d:%d", &idp, &novo_preco);

    if (vetor_produtos[idp].id == ID_INVALIDO) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else {
        vetor_produtos[idp].preco = novo_preco;
    }
}


/* 
Recebe um identificador de produto e um identificador de encomenda 
e devolve a quantidade do produto na encomenda. 
*/
int quantidadeProdutoEnc(int idp, int ide) {
    int i;

    for (i = 0; i < PRODUTO_MAX_ENC && vetor_encomendas[ide].item[i].id != ID_INVALIDO; i++) {
        if (vetor_encomendas[ide].item[i].id == idp) {
            return vetor_encomendas[ide].item[i].qtd;
        }
    }
    return 0;
}


/* 
Le do input um identificador de encomenda e um identificador de produto 
e imprime a descricao e a quantidade do produto na encomenda. 
*/
void E() {
    int ide, idp;
    
    scanf("%d:%d", &ide, &idp);

    if (vetor_encomendas[ide].id == ID_INVALIDO) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else if (vetor_produtos[idp].id == ID_INVALIDO) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else {
        printf("%s %d.\n", vetor_produtos[idp].desc, quantidadeProdutoEnc(idp, ide));
    }
}


/*
Le do input um identificador de produto e imprime o identificador da encomenda 
em que o produto dado ocorre mais vezes e a quantidade maxima em que ocorre. 
*/
void m() {
    int idp;
    int i;
    /* Quantidade do produto na encomenda. */
    int qtd_enc; 
    /* Identificador da encomenda em que o produto ocorre mais vezes. */
    int max_ide = ID_INVALIDO;
    /* Quantidade maxima do produto. */
    int max_qtd = 0;

    scanf("%d", &idp);

    if (vetor_produtos[idp].id == ID_INVALIDO) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }

    else {
        for (i = 0; i < ENCOMENDAS_MAX && vetor_encomendas[i].id != ID_INVALIDO; i++) {
            qtd_enc = quantidadeProdutoEnc(idp, i);
            
            if (qtd_enc > max_qtd) {
                max_qtd = qtd_enc;
                max_ide = i;
            }

        }
        
        if (max_ide != ID_INVALIDO) {
            printf("Maximo produto %d %d %d.\n", idp, max_ide, max_qtd);
        }
    }
}


/* 
Recebe dois identificadores de produto e devolve 1 se o produto correspondente ao primeiro 
identificador tem maior preco, caso contrario devolve 0. Caso os dois produtos tenham o mesmo preco, 
devolve 1 se o primeiro identificador for maior que o segundo.
*/
int maiorPreco(int id1, int id2) {
    if (vetor_produtos[id1].preco > vetor_produtos[id2].preco) {
        return TRUE;
    }
    else if (vetor_produtos[id1].preco < vetor_produtos[id2].preco) {
        return FALSE;
    }
    else {
        return vetor_produtos[id1].id > vetor_produtos[id2].id;
    }
}


/* 
Recebe um vetor de inteiros (identificadores de produto), uma posicao final e uma posicao inicial e organiza o vetor 
colocando o ultimo elemento entre os elementos cujo produto correspondente tem menor preco 
e os elementos cujo produto correspondente tem maior preco.
*/
int particaoPreco(int vec[], int inicio, int fim) {
    int i = inicio, j = fim;
    int p;

    /* Pivot eh o ultimo elemento do vetor. */
    p = vec[j];

    while (i < j) {
        /* Percorre o vetor ate encontrar um elemento maior que o pivot. */
        while (maiorPreco(p, vec[i])) {
            i++;
        }

        /* Percorre o vetor por ordem inversa ate encontrar um elemento menor que o pivot. */
        while (!maiorPreco(p,vec[--j])) {
            if (j == inicio) {
                break;
            }
        }
        
        if (i < j) {
            troca(vec[i], vec[j]);
        }
    }

    /* Coloca o pivot entre elementos maiores e menores. */
    troca(vec[i], vec[fim]);
    return i;
}


/* 
Recebe um vetor de inteiros (identificadores de produto), uma posicao inicial e uma posicao final e ordena os elementos, 
entre essas posicoes, por ordem crescente de preco do produto correspondente. 
*/
void ordenaPreco(int vetor_id[], int inicio, int fim) {
    int i;
    if (inicio < fim) {
        i = particaoPreco(vetor_id, inicio, fim);
        ordenaPreco(vetor_id, inicio, i - 1);
        ordenaPreco(vetor_id, i + 1, fim);
    }
}


/* 
Imprime descricao, preco e quantidade dos produtos do vetor global de produtos
por ordem crecente de preco. 
*/
void l() {
    int j, i;
    int vetor_id[PRODUTOS_MAX];

    /* Identificadores dos produtos da encomenda sao introduzidos no vetor auxiliar. */
    for (j = 0; j < PRODUTOS_MAX && vetor_produtos[j].id != ID_INVALIDO; j++)  {
        vetor_id[j] = vetor_produtos[j].id;
    }

    /* Ordena vetor de identificadores. */
    ordenaPreco(vetor_id, 0, j - 1);

    printf("Produtos\n");
    /* Imprime informacoes dos produtos pela ordem dos identificadores no vetor ordenado. */
    for (i = 0; i < j; i++) {
        printf("* %s %d %d\n", vetor_produtos[vetor_id[i]].desc, vetor_produtos[vetor_id[i]].preco, vetor_produtos[vetor_id[i]].qtd);
    }
}


/* 
Recebe dois dados_encomenda e devolve 1 se a descricao do produto correspondente ao primeiro deles eh alfabeticamente maior
do que a do produto referente aos segundos dados, caso contrario devolve 0.
*/
int maiorAlfab(dados_encomenda d1, dados_encomenda d2) {
    return strcmp(vetor_produtos[d1.id].desc, vetor_produtos[d2.id].desc) > 0;
}


/* 
Recebe um vetor de dados_encomenda, uma posicao final e uma posicao inicial e organiza o vetor 
colocando o ultimo elemento entre os elementos cujo produto correspondente tem descricao alfabeticamente menor 
e os elementos cujo produto correspondente tem descricao alfabeticamente maior.
*/
int particaoAlfab(dados_encomenda vec[], int inicio, int fim) {
    int i = inicio, j = fim;
    dados_encomenda p;

    /* Pivot eh o ultimo elemento do vetor. */
    p = vec[j];

    while (i < j) {
        /* Percorre o vetor ate encontrar um elemento maior que o pivot. */
        while (maiorAlfab(p,vec[i])) {
            i++;
        }

        /* Percorre o vetor por ordem inversa ate encontrar um elemento menor que o pivot. */
        while (!maiorAlfab(p, vec[--j])) {
            if (j == inicio) {
                break;
            }
        }

        if (i < j) {
            trocaDadosEnc(vec[i], vec[j]);
        }
    }

    /* Coloca o pivot entre elementos maiores e menores. */
    trocaDadosEnc(vec[i], vec[fim]);
    return i;
}


/* 
Recebe um vetor de dados_encomenda, uma posicao inicial e uma posicao final e ordena os elementos, 
entre essas posicoes, por ordem alfabetica das descricoes dos produtos correspondentes aos elementos. 
*/
void ordenaAlfab(dados_encomenda vetor_dados[], int inicio, int fim) {
    int i;
    if (inicio < fim) {
        i = particaoAlfab(vetor_dados, inicio, fim);
        ordenaAlfab(vetor_dados, 0, i - 1);
        ordenaAlfab(vetor_dados, i + 1, fim);
    }
}


/* 
Le do input um identificador de encomenda, ordena os elementos dessa encomenda por ordem alfabetica da descricao dos pordutos
correspondentes e imprime descricao, preco e quantidade na encomenda dos seus elementos ordenados. 
*/
void L() {
    int i, j;
    int ide;
    int idp;

    scanf("%d", &ide);

    if (vetor_encomendas[ide].id != ID_INVALIDO) {

        /* Encontra a posicao do ultimo produto no vetor de encomenda. */
        for (j = 0; j < PRODUTO_MAX_ENC && vetor_encomendas[ide].item[j].id != ID_INVALIDO; j++);
        
        /* Elementos da encomenda sao ordenados. */
        ordenaAlfab(vetor_encomendas[ide].item, 0, j - 1);

        printf("Encomenda %d\n", ide);
        
        for (i = 0; i < PRODUTO_MAX_ENC && vetor_encomendas[ide].item[i].id != ID_INVALIDO; i++) {
            idp = vetor_encomendas[ide].item[i].id;
            printf("* %s %d %d\n", vetor_produtos[idp].desc, vetor_produtos[idp].preco, vetor_encomendas[ide].item[i].qtd);
        }
    
    }
    else {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
}