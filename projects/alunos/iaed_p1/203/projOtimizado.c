#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>


/*tamanhos maximos descritos no enunciado*/
#define MAX_DESCRICAO 64
#define MAX_IDP 10000
#define MAX_IDE 500
#define MAX_PESO 200
#define MAX_PROD_ENC 200
#define SIM 1
#define NAO 0


/* estrutura produto com preco, peso, quantidade, nome e o seu idp proprio */
typedef struct produto
{
    int preco, peso, qtd, idp;
    char nome[MAX_DESCRICAO];
}prod;


/* regista o numero de produtos em stock */
int idp = 0;


/* lista de todos os produtos */
prod produtos[MAX_IDP];




/* estrutura encomenda com peso, numero de produtos na encomenda e uma lista de produtos que nela se encontram */
typedef struct encomenda
{
    int peso, num_prod_enc;
    prod prods_enc[MAX_PROD_ENC];
}enc;


/* regista o numero de encomendas */
int ide = 0;


/* lista de encomendas */
enc encomendas[MAX_IDE];

int obtem_pesoP();
int obtem_qtd();
int obtem_preco();
void a_add_prod();
void q_add_stock();
void N_cria_encomenda();
void A_add_prod_enc();
void r_remove_stock();
void R_remove_produto_encomenda();
void C_calcula_custo_encomenda();
void p_altera_preco_produto();
void E_lista_produtos_por_encomenda();
void m_lista_mais_requisitado();
void mergeSort();
void printArray();
void merge();
void l_lista_prod_preco();
void L_lista_prod_enc_ordemAlfabetica();
int less();

int main()
{
    char n;
    n = getchar();
    while(n != 'x')
    {
        switch(n)
        {
            case 'a':
                a_add_prod();
                break;
            case 'q':
                q_add_stock();
                break;
            case 'N':
                N_cria_encomenda();
                break;
            case 'A':
                A_add_prod_enc();
                break;
            case 'r':
                r_remove_stock();
                break;
            case 'R':
                R_remove_produto_encomenda();
                break;
            case 'C':
                C_calcula_custo_encomenda();
                break;
            case 'p':
                p_altera_preco_produto();
                break;
            case 'E':
                E_lista_produtos_por_encomenda();
                break;
            case 'm':
                m_lista_mais_requisitado();
                break;
            case 'l':
                l_lista_prod_preco();
                break;
            case 'L':
                L_lista_prod_enc_ordemAlfabetica();
        }
    n = getchar();
    }
    return 0;
}



/* recebe um nome, preco, peso e qtd e cria um produto com essas informa?oes mais o idp */
void a_add_prod()
{
    prod produto;
    scanf(" %[^:]:%d:%d:%d", produto.nome, &produto.preco, &produto.peso, &produto.qtd);
    printf("Novo produto %d.\n", idp);
    produtos[idp] = produto;
    produtos[idp].idp = idp;
    idp++;
}


/* recebe um idp e uma qtd e adiciona ao stock do produto idp uma quantidade qtd */
void q_add_stock()
{
    int qtd, idp_aux;
    scanf("%d:%d",&idp_aux,&qtd);
    if(idp_aux < idp)
        produtos[idp_aux].qtd += qtd;
    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_aux);
}


/* nao recebe nada, cria simplesmente uma struct encomenda e aumenta o valor do ide */
void N_cria_encomenda()
{
    printf("Nova encomenda %d.\n", ide);
    encomendas[ide].peso = 0;
    encomendas[ide].num_prod_enc = 0;
    ide++;
}


/* recebe um ide, um idp e uma qtd e adiciona a encomenda ide o produto idp 
com a quantidade qtd associada, removendo do stock essa mesma qtd */
void A_add_prod_enc()
{
    int ide_aux, idp_aux, qtd, i, existe_na_encomenda, n_prod_enc;
    existe_na_encomenda = NAO;
    scanf("%d:%d:%d", &ide_aux, &idp_aux, &qtd);
    n_prod_enc = encomendas[ide_aux].num_prod_enc;
    if(ide_aux >= ide)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp_aux, ide_aux);
    else if(idp_aux >= idp)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_aux, ide_aux);
    else if(produtos[idp_aux].qtd < qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_aux, ide_aux);
    else if(encomendas[ide_aux].peso + (qtd * produtos[idp_aux].peso) > MAX_PESO)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_aux, ide_aux);
    else
    {
        for(i = 0; i < n_prod_enc; i++)
        {
            /* se ja se encontra na encomenda */
            if(encomendas[ide_aux].prods_enc[i].idp == produtos[idp_aux].idp)
            {
                /* somo as quantidades */
                encomendas[ide_aux].prods_enc[i].qtd += qtd; 
                existe_na_encomenda = SIM;
                break;
            }
        }
        /* se nao esta na encomenda, adiciona-se o produto a lista de produtos por encomenda */
        if(! (existe_na_encomenda))
        {
            encomendas[ide_aux].prods_enc[n_prod_enc] = produtos[idp_aux];
            encomendas[ide_aux].prods_enc[n_prod_enc].qtd = qtd;
            encomendas[ide_aux].num_prod_enc++;
        }
        /* independentemente de ja la estar o produto ou nao, 
        soma se ao peso da encomenda o (peso do produto * a qtd a adicionar) 
        e retira-se essa qtd do stock */
        encomendas[ide_aux].peso += (qtd * produtos[idp_aux].peso);
        produtos[idp_aux].qtd -= qtd;
    }
}


/* recebe um idp e uma quantidade e retira ao stock essa quantidade */
void r_remove_stock()
{
    int idp_aux, qtd;
    scanf("%d:%d", &idp_aux, &qtd);

    /* verificacoes */
    if(idp_aux >= idp)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_aux);
    else if(produtos[idp_aux].qtd < qtd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd, idp_aux);
    else
        produtos[idp_aux].qtd -= qtd;
}


/* recebe um id encomenda e um id produto e remove-o da lista de produtos nessa encomenda */
void R_remove_produto_encomenda()
{
    int ide_aux, idp_aux, i, j, esta_na_encomenda = NAO;
    scanf("%d:%d", &ide_aux, &idp_aux);

    /* verificacoes */
    if(ide_aux >= ide)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp_aux, ide_aux);
    else if(idp_aux >= idp)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp_aux, ide_aux);
    else
    {
        for(i = 0; i < (encomendas[ide_aux].num_prod_enc); i++)
        {
            if(encomendas[ide_aux].prods_enc[i].idp == produtos[idp_aux].idp)
            {
                produtos[idp_aux].qtd += encomendas[ide_aux].prods_enc[i].qtd;
                encomendas[ide_aux].peso -= encomendas[ide_aux].prods_enc[i].qtd * encomendas[ide_aux].prods_enc[i].peso;
                esta_na_encomenda = SIM;
                for(j = i; j < encomendas[ide_aux].num_prod_enc; j++)
                {
                    encomendas[ide_aux].prods_enc[j] = encomendas[ide_aux].prods_enc[j+1];
                }
                break;
            }
        }
        if(esta_na_encomenda)
            encomendas[ide_aux].num_prod_enc--;
    }
}


/* recebe um ide e devolve o custo total da encomenda */
void C_calcula_custo_encomenda()
{
    int ide_aux, i, custo_total;
    custo_total = 0;
    scanf("%d",&ide_aux);
    if(ide_aux >= ide)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide_aux);
    else
    {
        for(i = 0; i < encomendas[ide_aux].num_prod_enc; i++)
        {
            if(encomendas[ide_aux].prods_enc[i].qtd != 0)
                custo_total += encomendas[ide_aux].prods_enc[i].qtd * encomendas[ide_aux].prods_enc[i].preco;
        }
        printf("Custo da encomenda %d %d.\n", ide_aux, custo_total);
    }
}


/* recebe um idp e um preco altera o preco do produto e do mesmo em todas as encomendas. Nao devolve nada */
void p_altera_preco_produto()
{
    int idp_aux, preco, i, j;
    scanf("%d:%d", &idp_aux, &preco);
    if(idp_aux >= idp)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_aux);
    else
    {
        produtos[idp_aux].preco = preco;
        for(j = 0; j < ide ; j++)
        {
            for(i = 0; i < encomendas[j].num_prod_enc; i++)
            {
                if(encomendas[j].prods_enc[i].idp == idp_aux)
                {
                    encomendas[j].prods_enc[i].preco = preco;
                    break;
                }
            }
        }
    }
}


/* esta funcao recebe um ide e um idp e devolve a descricao e a quantidade do produto idp na encomenda ide */
void E_lista_produtos_por_encomenda()
{
    int ide_aux, idp_aux, i, esta_na_encomenda = NAO;
    scanf("%d:%d", &ide_aux, &idp_aux);
    if(ide_aux >= ide)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_aux);
    else if(idp_aux >= idp)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp_aux);
    else
    {
        for(i = 0; i < encomendas[ide_aux].num_prod_enc; i++)
        {
            if(encomendas[ide_aux].prods_enc[i].idp == idp_aux)
            {
                esta_na_encomenda = SIM;
                printf("%s %d.\n", encomendas[ide_aux].prods_enc[i].nome, encomendas[ide_aux].prods_enc[i].qtd );
                break;
            }
        }
        if (! (esta_na_encomenda))
            printf("%s %d.\n", produtos[idp_aux].nome, 0);
    }
}


/* esta funcao recebe um idp e devolve o proprio idp, a encomenda em que 
o produto esta em maior quantidade e a essa mesma quantidade */
void m_lista_mais_requisitado()
{
    int i, j, idp_aux, id_encomenda = 0, esta_na_encomenda = NAO, maior = 0;
    scanf("%d", &idp_aux);
    if(idp_aux >= idp)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_aux);
    else
    {
        for(j = 0; j < ide ; j++)
        {
            for(i = 0; i < encomendas[j].num_prod_enc; i++)
            {
                if((encomendas[j].prods_enc[i].idp == idp_aux) 
                && (encomendas[j].prods_enc[i].qtd > maior))
                {
                    esta_na_encomenda = SIM;
                    maior = encomendas[j].prods_enc[i].qtd;
                    id_encomenda = j;
                    break;
                }
            }
        }
        if(esta_na_encomenda)
            printf("Maximo produto %d %d %d.\n", idp_aux, id_encomenda, maior);
    }
}


/* nao recebe nenhum dado, devolve a lista de produtos 
ordenados primeiramente por preco e segundamente por idp */
void l_lista_prod_preco()
{
    int i;
    prod arr[MAX_IDP];
    
    printf("Produtos\n");
    /* crio o vetor auxiliar que mergesort pressupoe */
    for(i = 0; i < idp; i++)
    {
        arr[i] = produtos[i];
    }
    mergeSort(arr, 0, idp-1);
    printArray(arr, idp);
}


/* flag usada para o mergeSort */
int flag_str = NAO;


/* esta funcao recebe o id de uma encomenda e retorna a lista 
dos produtos que la se encontram por ordem alfabetica*/
void L_lista_prod_enc_ordemAlfabetica()
{
    int ide_aux, i;
    prod array[MAX_PROD_ENC];
    scanf("%d", &ide_aux);
    if(ide_aux >= ide)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_aux);
    else
    {
        for(i = 0; i < encomendas[ide_aux].num_prod_enc; i++)
        {
            array[i] = encomendas[ide_aux].prods_enc[i];
        }
        printf("Encomenda %d\n", ide_aux);
        flag_str = SIM;
        mergeSort(array, 0, encomendas[ide_aux].num_prod_enc-1);
        printArray(array, encomendas[ide_aux].num_prod_enc);
        flag_str = NAO;
    }
}

/* lista de produtos auxiliar para o mergeSort */
prod aux[MAX_IDP];

/* recebe dois vetores ordenados e devolve um ordenado ()
com todos os elementos dos outros dois */
void merge(prod arr[], int left, int m, int right) 
{ 
    int i, j, k; 

    /* constroi o vetor auxiliar */
    for (i = m+1; i > left; i--)
        aux[i-1] = arr[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = arr[j+1];

    /* vai percorrendo os indices e ve qual e o menor, 
    inserindo-o no vetor de forma a este ficar ordenado */
    for (k = left; k <= right; k++)
    if (less(aux[j], aux[i]))
        arr[k] = aux[j--];
    else
        arr[k] = aux[i++];
}

void mergeSort(prod arr[], int left, int right) 
{ 
    if (left < right) 
    {
        int m = (left+right)/2; 
        /* se os indices forem iguais ou ja cruzaram quer dizer que 
        os vetores ja tem o tamanho minimo */
        if(right <= left) 
            return;
        /* sort da primeira e segunda parte do vetor */ 
        mergeSort(arr, left, m); 
        mergeSort(arr, m+1, right); 
  
        merge(arr, left, m, right); 
    } 
}

/* funcao less que se adapta ao dois casos atraves da flag_str */

int less(prod A, prod B)
{
    if(flag_str)
        return strcmp(A.nome, B.nome) < 0;
    else
    {
        if(A.preco == B.preco)
            return A.idp < B.idp;
        else
            return A.preco < B.preco;
    }
}

/* funcao simplesmente para imprimir as listas da funcao 'l' e 'L' */

void printArray(prod A[], int n) 
{ 
    int i; 
    for (i=0; i < n; i++) 
        printf("* %s %d %d\n", A[i].nome, A[i].preco, A[i].qtd); 
}
