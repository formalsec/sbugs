#include <stdio.h>
#include <string.h> 

/* #####################################################################

                              CONSTANTES

##################################################################### */

/* Numero maximo de produtos diferentes */
#define PRODUTOS_DIF 10000
/* Numero maximo de encomendas */
#define ENCOMENDAS_MAX 500 
/* Peso maximo de uma encomenda */
#define PESO_MAX 200 
/* Tamanho maximo da descricao de um produto */
#define DESCRICAO_MAX 63 

/* ##################################################################### 

                   PROTOTIPOS DAS FUNCOES PRINCIPAIS

##################################################################### */ 

void adiciona_produto();
void aumenta_stock();
void cria_encomenda();
void aumenta_encomenda();
void diminui_stock();
void diminui_encomenda();
void custo_encomenda();
void altera_preco();
void produto_na_encomenda();
void maximo_produto();
void lista_produtos_crescente();
void lista_produtos_alfabetico();
void lista_produtos();
void descricao_encomenda();

/* ##################################################################### 

                               ESTRUTURAS

##################################################################### */

typedef struct
    {
        char descricao[DESCRICAO_MAX]; /* Descricao do produto */
        int preco; /* Preco por unidade do produto */
        int peso; /* Peso do produto */
        int qtd_stock; /* Quantidade existente em stock */
    } produto;

typedef struct 
{
    /* Em cada indice esta a quantidade referente ao idp */
    int quantidades[PRODUTOS_DIF]; 
    int peso; /* Peso total da encomenda */
} encomenda;

/* #####################################################################

                           VARIAVEIS GLOBAIS

##################################################################### */

/* Conjunto dos produtos no sistema */
produto stock[PRODUTOS_DIF];
/* Proximo identificador de produto (idp) */
int conta_stock;
/* Lista das encomendas. */
encomenda encomendas[ENCOMENDAS_MAX]; 
/* Proximo identificador de encomenda (ide) */
int conta_encomendas; 

/* vetor com os idp ordenados em funcao do pre?o */
int ordem[PRODUTOS_DIF];
/* Numero de produtos adicionados a ordem desde o ultimo "sort" */
int mudancas;
/* Vale 1 se ja foi feito merge_sort a "ordem" */
int sorted; 
/* Vale 1 se algum preco foi alterado desde o ultimo "sort" */
int mudanca_preco; 

/* ##################################################################### 

                              FUNCAO MAIN

##################################################################### */

/* Interpreta o caracter recebido e executa o comando pretendido */
int main()
{
    int comando;
    while ((comando = getchar()) != 'x')
    {
        switch ( comando )
        {
            /* Cada letra chama a funcao correspondente ao comando */
            case 'a':
                adiciona_produto();
                break;
            case 'q':
                aumenta_stock();
                break;
            case 'N':
                cria_encomenda();
                break;
            case 'A':
                aumenta_encomenda();
                break;
            case 'r':
                diminui_stock();
                break;
            case 'R':
                diminui_encomenda();
                break;
            case 'C':
                custo_encomenda();
                break;
            case 'p':
                altera_preco();
                break;
            case 'E':
                produto_na_encomenda();
                break;
            case 'm':
                maximo_produto();
                break;
            case 'l':
                lista_produtos_crescente();
                break;
            case 'L':
                lista_produtos_alfabetico();
                break;
            case 'k':
                lista_produtos();
                break;
            case 'K':
                descricao_encomenda();
                break;
            default:
                break;
        }
    }
    return 0;
}

/* #####################################################################

                          FUNCOES AUXILIARES

##################################################################### */

/* Devolve o preco de um produto */
int preco(int produto)
{
    return stock[produto].preco;
}

/* Devolve o peso de um produto */
int peso_p(int produto)
{
    return stock[produto].peso;
}

/* Devolve a quantidade em stock de um produto */
int qtd_p(int produto)
{
    return stock[produto].qtd_stock;
}
/* Devolve o peso de uma encomenda */
int peso_e(int encomenda)
{
    return encomendas[encomenda].peso;
}

/* Devolve a quantidade de um produto numa encomenda */
int qtd_e(int encomenda, int produto)
{
    return encomendas[encomenda].quantidades[produto];
}

/* Verifica se o valor dado corresponde a uma encomenda existente */
int encomenda_falsa(int encomenda)
{
    return (conta_encomendas <= encomenda);
}

/* Verifica se o valor dado corresponde a um produto existente */
int produto_falso(int produto)
{
    return (conta_stock <= produto);  
}

 /* Recebe dois idp e compara os seus precos. Caso estes sejam iguais
    compara os identificadores */
int menor_preco(int a, int b)
{ 
    return (stock[a].preco < stock[b].preco ||
           (stock[a].preco == stock[b].preco && a < b));
           /* Compensa a instabilidade do "merge_sort" */
}

/* Verifica se a string a vem primeiro na ordem alfabetica do que b */
int alfabetico(int a, int b)
{
    return (strcmp(stock[a].descricao, stock[b].descricao) < 0);
}

/* Funcao auxiliar de "merge_sort" */
void merge(int v[], int inicio, int m, int fim, int (*condicao)(int, int))
{
    int aux[PRODUTOS_DIF]; /* Vetor auxiliar */
    int i, j, k;
    for (i = m+1 ; i > inicio ; i--)
    {
        aux[i-1] = v[i-1];
    }
    for (j = m ; j < fim ; j++)
    {
        aux[fim+m-j] = v[j+1];
    }
    for (k = inicio ; k <= fim ; k++)
    {
        if (condicao(aux[j], aux[i]))
        {
            v[k] = aux[j--];
        }
        else
        {
            v[k] = aux[i++];
        }
    }   
}

/* Funcao que ordena os produtos consoante a condicao pretendida */
void merge_sort(int inicio, int fim, int v[], int (*condicao)(int, int))
{
    int m = (fim + inicio)/2; /* Meio do vetor */
    
    if (fim <= inicio)
    {
        return; /* Fim da recursividade */
    }

    merge_sort(inicio, m, v, condicao);
    merge_sort(m+1, fim, v, condicao);
    merge(v, inicio, m, fim, condicao);
}

/* Funcao que insere produtos novos num vetor ja ordenado */
void insert_sort(int inicio, int fim, int (*condicao)(int, int))
{
    int i, k, inserir;
    for (i = inicio ; i != fim+1 ; i++)
    {
        inserir = ordem[i];
        k = i-1;
        while (k >= 0 && condicao(inserir, ordem[k]))
        {
            ordem[k+1] = ordem[k];
            k--;
        }
        ordem[k+1] = inserir;
    }
}

/* ##################################################################### 

                          FUNCOES PRINCIPAIS

##################################################################### */

/* Adiciona um produto novo ao stock. Devolve o idp deste produto */
void adiciona_produto()
{
    scanf(" %[^:]:%d:%d:%d", stock[conta_stock].descricao,
          &stock[conta_stock].preco, &stock[conta_stock].peso,
          &stock[conta_stock].qtd_stock);

    ordem[conta_stock] = conta_stock; 
    mudancas += 1;

    printf("Novo produto %d.\n", conta_stock++);
}

/* Aumenta a quantidade de um produto no stock */
void aumenta_stock()
{
    int qtd, produto;
    scanf( "%d:%d", &produto, &qtd);
    
    if (produto_falso(produto))
    {
        printf("Impossivel adicionar produto %d ao stock."
               " Produto inexistente.\n", produto);
    }
    else
    {
        stock[produto].qtd_stock += qtd;
    }
}

/* Cria uma nova encomenda e devolve o seu identificador */
void cria_encomenda()
{
    /* Nao precisa de operacoes, pois o vetor foi todo inicializado */
    printf("Nova encomenda %d.\n", conta_encomendas++);
}

/* Adiciona a uma encomenda um produto na quantidade desejada */
void aumenta_encomenda()
{
    int encomenda, produto, qtd;
    scanf(" %d:%d:%d", &encomenda, &produto, &qtd);

    if (encomenda_falsa(encomenda))
    {
        printf("Impossivel adicionar produto %d a encomenda %d."
               " Encomenda inexistente.\n", produto, encomenda);
    }
    else if (produto_falso(produto))
    {
        printf("Impossivel adicionar produto %d a encomenda %d."
               " Produto inexistente.\n", produto, encomenda);
    }
    else if (qtd > qtd_p(produto))
    {
        printf("Impossivel adicionar produto %d a encomenda %d. "
        "Quantidade em stock insuficiente.\n", produto, encomenda);
    }
    else if ((peso_e(encomenda) + peso_p(produto) * qtd) > PESO_MAX)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso"
        " da encomenda excede o maximo de 200.\n", produto, encomenda);
    }
    else
    {
        encomendas[encomenda].quantidades[produto] += qtd;
        stock[produto].qtd_stock -= qtd; /* Retirar do stock */
        encomendas[encomenda].peso += (qtd * peso_p(produto));
    }
}

/* Diminui a quantidade de um produto no stock */
void diminui_stock()
{
    int qtd, produto;
    scanf(" %d:%d", &produto, &qtd);
    if (produto_falso(produto))
    {
        printf("Impossivel remover stock do produto %d."
               " Produto inexistente.\n", produto);
    }
    else if (qtd > qtd_p(produto))
    {
        printf("Impossivel remover %d unidades do produto %d do stock." 
               " Quantidade insuficiente.\n", qtd, produto);
    }
    else
    {
        stock[produto].qtd_stock -= qtd;
    }
}

/* Remove um produto de uma encomenda */
void diminui_encomenda()
{
    int encomenda, produto;
    scanf(" %d:%d", &encomenda, &produto);

    if (encomenda_falsa(encomenda))
    {
        printf("Impossivel remover produto %d a encomenda %d."
               " Encomenda inexistente.\n", produto, encomenda);
    }
    else if (produto_falso(produto))
    {
        printf("Impossivel remover produto %d a encomenda %d."
               " Produto inexistente.\n", produto, encomenda);
    }
    else
    {
        /* Repoe no stock */
        stock[produto].qtd_stock += qtd_e(encomenda, produto);
        encomendas[encomenda].peso -= (peso_p(produto) *
                                      qtd_e(encomenda, produto));
        encomendas[encomenda].quantidades[produto] = 0;
    }
}

/* Devolve o custo de uma encomenda */
void custo_encomenda()
{
    int encomenda, custo = 0, i;
    scanf(" %d", &encomenda);
    
    if (encomenda_falsa(encomenda))
    {
        printf("Impossivel calcular custo da encomenda %d."
               " Encomenda inexistente.\n", encomenda);
    }
    else
    {
        for (i = 0 ; i != conta_stock ; i++)
        {
            /* Verifica se o produto esta na encomenda */
            if (qtd_e(encomenda, i))
            {
                custo += preco(i) * qtd_e(encomenda, i);
            }
        }
        printf("Custo da encomenda %d %d.\n", encomenda, custo);
    }
}

/* Altera o preco de um produto do stock */
void altera_preco()
{
    int produto, preco;
    scanf(" %d:%d", &produto, &preco);
    
    if (produto_falso(produto))
    {
        printf("Impossivel alterar preco do produto %d. Produto"
               " inexistente.\n", produto);
    }
    else
    {
        stock[produto].preco = preco;
        mudanca_preco = 1;
    }
}

/* Devolve o nome e quantidade de um produto numa encomenda */
void produto_na_encomenda()
{
    int encomenda, produto;
    scanf(" %d:%d", &encomenda, &produto);

    if (encomenda_falsa(encomenda))
    {
        printf("Impossivel listar encomenda %d. Encomenda"
               " inexistente.\n", encomenda);
    }
    else if (produto_falso(produto))
    {
        printf("Impossivel listar produto %d. Produto"
               " inexistente.\n", produto);
    }
    else
    {
        printf("%s %d.\n", stock[produto].descricao,
               qtd_e(encomenda, produto));
    }
}

/* Devolve a encomenda com maior quantidade de um produto e o valor */
void maximo_produto()
{
    int produto, k, maximo = 0, maior;
    scanf(" %d", &produto);

    if (produto_falso(produto))
    {
        printf("Impossivel listar maximo do produto %d."
               " Produto inexistente.\n", produto);
    }
    else
    {
        /* Encontra a encomenda com maior quantidade */
        for (k = 0 ; k != conta_encomendas ; k++)
        {
            if (qtd_e(k, produto) > maximo)
            {
                maior = k;
                maximo = qtd_e(k, produto);
            }
        }
        /* Verifica se alguma encomenda tem o produto */
        if (maximo)
        {
            printf("Maximo produto %d %d %d.\n",
                   produto, maior, maximo);
        }
    }  
}

/* Devolve uma lista dos produtos, por ordem crescente de precos */
void lista_produtos_crescente()
{    
    int j;
    printf("Produtos\n");

    /* Caso seja precisa uma ordenacao de maior escala usa merge_sort.
       (A primeira ordenacao e sempre por merge) */
    if (mudancas > 15 || !sorted || mudanca_preco)
    {
        merge_sort(0, conta_stock-1, ordem, menor_preco);
        /* Acerta as variaveis auxiliares da ordenacao */
        mudancas = 0;
        sorted = 1;
        mudanca_preco = 0;
    }
    else if (mudancas) /* Caso haja poucas mudancas usa insert_sort */
    {
        insert_sort(conta_stock-mudancas, conta_stock-1, menor_preco);
    }

    /* Caso nao haja mudancas mantem-se a ordem do vetor */

    for (j = 0 ; j != conta_stock ; j++)
    {
        printf("* %s %d %d\n", stock[ordem[j]].descricao,
                               preco(ordem[j]), qtd_p(ordem[j]));
    }
}

/* Devolve os produtos numa encomenda, por ordem alfabetica */
void lista_produtos_alfabetico()
{
    int encomenda;
    /* Vetor com os idp dos produtos da encomenda */
    int ordem_e[PRODUTOS_DIF]; 
    /* Numero de produtos na encomenda */
    int n_produtos = 0;
    int i, k; 
    scanf(" %d", &encomenda);
    
    if (encomenda_falsa(encomenda))
    {
        printf("Impossivel listar encomenda %d. Encomenda"
               " inexistente.\n", encomenda);
    }
    else
    {    
        printf("Encomenda %d\n", encomenda);
        
        /* Cria o vetor com idp dos produtos da encomenda */
        for (i = 0 ; i != conta_stock ; i++)
        {
            /* Verifica se o produto esta na encomenda */
            if (qtd_e(encomenda, i))
            {
                ordem_e[n_produtos++] = i;
            }
        }

        /* Como os vetores nunca sao guardados usa sempre o merge */
        merge_sort(0, n_produtos-1, ordem_e, alfabetico);

        for (k = 0 ; k != n_produtos ; k++)
        {
            printf("* %s %d %d\n", stock[ordem_e[k]].descricao,
                                   preco(ordem_e[k]),
                                   qtd_e(encomenda, ordem_e[k]));
        }
    } 
}

/* #####################################################################

                        FUNCOES FACULTATIVAS   

##################################################################### */

/* Apresenta uma lista dos produtos existentes e suas caracteristicas */
void lista_produtos()
{
    int k;
    printf("Produtos\n");
    
    for (k = 0 ; k != conta_stock ; k++)
    {
        printf("%s %d %d\n", stock[k].descricao, preco(k), qtd_p(k));
    }
}

/* Apresenta os produtos de uma encomenda e suas quantidades */
void descricao_encomenda()
{
    int encomenda, p;
    scanf(" %d", &encomenda);
    printf("Produtos na encomenda %d\n", encomenda);
    
    for (p = 0 ; p != conta_stock ; p++)
    {
        /* Verifica se o produto esta na encomenda */
        if (qtd_e(encomenda, p))
        {
            printf("%s %d\n", stock[p].descricao, qtd_e(encomenda, p));
        }
    }
}