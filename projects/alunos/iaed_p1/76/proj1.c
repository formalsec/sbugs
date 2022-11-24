#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "proj1.h"

/*Tabela dos produtos*/
produto registo_prod[MAX_PRODUTOS];

/*Tabela das encomendas*/
encomenda registo_enc[MAX_ENCOMENDAS];

/*Contadores de produtos e encomendas*/
int cont_produtos, cont_encomendas;

/*Vetor auxiliar na funcao mergesort*/
int aux[MAX_PRODUTOS];

int main()
{
    int comando;
    
    while ((comando = getchar()) != 'x')
    {
        switch (comando)
        {
        case 'a':
            cria_produto();
            break;

        case 'q':
            adiciona_stock();
            break;

        case 'N':
            cria_encomenda();
            break;

        case 'A':
            adiciona_produto();
            break;

        case 'r':
            remove_stock();
            break;

        case 'R':
            remove_produto();
            break;

        case 'C':
            calcula_custo();
            break;

        case 'p':
            altera_preco();
            break;

        case 'E':
            descricao_produto();
            break;

        case 'm':
            encomenda_maior();
            break;

        case 'l':
            lista_produtos();
            break;

        case 'L':
            lista_produtos_encomenda();
            break;

        default:
            break;
        }
    }
    return 0;
}

/*---FUNCOES AUXILIARES PARA MELHOR ABSTRACAO---*/

/*Devolve a quantidade de produto de indice idp existente na encomenda de indice ide*/
int qtd_na_encomenda(int ide, int idp)
{
    return registo_enc[ide].produtos[idp];
}

/*Devolve 1 se o produto existe e 0 se o produto nao existe*/
int produto_existe(int idp)
{
    return registo_prod[idp].state;
}

/*Devolve 1 se a encomenda existe e 0 se a encomenda nao existe*/
int encomenda_existe(int ide)
{
    return registo_enc[ide].state;
}

/*Devolve a quantidade de produto em stock*/
int qtd_prod(int idp)
{
    return registo_prod[idp].qtd;
}

/*Devolve o peso de um produto*/
int peso_prod(int idp)
{
    return registo_prod[idp].peso;
}

/*Devolve o preco de um produto*/
int preco_prod(int idp)
{
    return registo_prod[idp].preco;
}

/*Altera a quantidade de um produto no stock*/
void altera_quantidade(int idp, int qtd)
{
    registo_prod[idp].qtd += qtd;
}

/*Remove um produto e organiza o vetor prod_ord quando essa remocao ocorre*/
void remove_prod_ord(int ide, int idp)
{
    int i;

    /*Percorre o vetor prod_ord ate encontrar o produto a remover*/
    for (i=0; i<registo_enc[ide].n_prod;i++)
            if (registo_enc[ide].prod_ord[i] == idp)
                break;

    /*Decrementa o numero de produtos na encomenda*/
    registo_enc[ide].n_prod--;

    /*Cada produto que se encontra apos o produto a remover "anda" um indice para tras*/
    for(;i<registo_enc[ide].n_prod;i++)
        registo_enc[ide].prod_ord[i] = registo_enc[ide].prod_ord[i+1];
}

/*---FUNCOES PRINCIPAIS---*/

/*Adiciona um novo produto ao sistema*/
void cria_produto()
{
    char des[TAMANHO_DES];
    produto prod;
    int i, preco, peso, qtd;

    scanf(" %[^:]:%d:%d:%d", des, &preco, &peso, &qtd);

    i = 0;
    while ((prod.des[i] = des[i]) != '\0')
        i++;
    prod.preco = preco;
    prod.peso = peso;
    prod.qtd = qtd;
    prod.state = 1;

    /*Adiciona o produto ao registo de produtos e incrementa o cont_produtos*/
    registo_prod[cont_produtos] = prod;
    printf("Novo produto %d.\n", cont_produtos);
    cont_produtos++;
}

/*Adiciona stock a um produto existente no sistema*/
void adiciona_stock()
{
    int idp, qtd;

    scanf("%d:%d", &idp, &qtd);

    /*Se o produto existe, adiciona stock*/
    if (produto_existe(idp))
        altera_quantidade(idp, qtd);
    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

/*Cria uma nova encomenda*/
void cria_encomenda()
{
    /*Adiciona a encomenda ao registo de encomendas e incrementa o cont_encomendas*/
    registo_enc[cont_encomendas].state = 1;
    printf("Nova encomenda %d.\n", cont_encomendas);
    cont_encomendas++;
}

/*Adiciona um produto a uma encomenda. Se o produto ja existir na encomenda, adiciona a nova quantidade a quantidade existente.*/
void adiciona_produto()
{
    int ide, idp, qtd;

    scanf("%d:%d:%d", &ide, &idp, &qtd);

    if (!encomenda_existe(ide))
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    if (!produto_existe(idp))
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    if (qtd_prod(idp) < qtd)
    { 
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }
    if ((registo_enc[ide].peso + qtd*peso_prod(idp)) > MAX_PESO)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }

    /*Se o produto nao existir na encomenda*/
    if (qtd_na_encomenda(ide, idp) == 0)
    {   
        registo_enc[ide].prod_ord[registo_enc[ide].n_prod] = idp;               /*Adiciona o produto ao final do vetor prod_ord*/
        registo_enc[ide].n_prod++;                                              /*Incrementa o numero de produtos na encomenda*/
        insertion_sort (registo_enc[ide].prod_ord, registo_enc[ide].n_prod);    /*Organiza alfabeticamente o vetor prod_ord*/
    }

    /*Atualiza a quantidade e o peso na encomenda e a quantidade no stock*/
    registo_enc[ide].produtos[idp] += qtd;
    registo_enc[ide].peso += peso_prod(idp)*qtd;
    altera_quantidade(idp, -qtd);
}

/*Remove stock a um produto existente*/
void remove_stock()
{
    int idp, qtd;

    scanf("%d:%d", &idp, &qtd);

    if (!produto_existe(idp))
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }
    if ((qtd_prod(idp) - qtd) < 0)
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        return;
    }

    altera_quantidade(idp, -qtd);
}

/*Remove um produto de uma encomenda*/
void remove_produto()
{
    int ide, idp;

    scanf("%d:%d", &ide, &idp);

    if (!encomenda_existe(ide))
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    if (!produto_existe(idp))
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }

    /*Remove o produto do vetor prod_ord e todos os produtos a seguir a esse "andam" um indice para tras*/
    if (qtd_na_encomenda(ide, idp) > 0)
        remove_prod_ord (ide, idp);
    
    /*Atualiza a quantidade de produto no stock e o peso e a quantidade na encomenda*/
    altera_quantidade(idp, qtd_na_encomenda(ide, idp));
    registo_enc[ide].peso -= qtd_na_encomenda(ide, idp)*peso_prod(idp);
    registo_enc[ide].produtos[idp] = 0;
    
}

/*Calcula o custo de uma encomenda*/
void calcula_custo()
{
    int i, ide, total=0;

    scanf("%d", &ide);

    if (!encomenda_existe(ide))
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    for (i=0; i<MAX_PRODUTOS; i++)
        total += preco_prod(i) * qtd_na_encomenda(ide, i);

    printf("Custo da encomenda %d %d.\n", ide, total);
}

/*Altera o preco de um produto existente no sistema*/
void altera_preco()
{
    int idp, preco;

    scanf("%d:%d", &idp, &preco);

    if (!produto_existe(idp))
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }

    registo_prod[idp].preco = preco;
}

/*Lista a descricao e a quantidade de um produto numa encomenda*/
void descricao_produto()
{
    int ide, idp;

    scanf("%d:%d", &ide, &idp);

    if (!encomenda_existe(ide))
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    if (!produto_existe(idp))
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }

    printf("%s %d.\n", registo_prod[idp].des, qtd_na_encomenda(ide, idp));
}

/*Lista o identificador da encomenda em que o produto dado ocorre mais vezes.*/
void encomenda_maior()
{
    int i, encomenda, idp, maior=0;

    scanf("%d", &idp);

    if (!produto_existe(idp))
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }

    for (i = 0; i < cont_encomendas; i++)
        if (qtd_na_encomenda(i, idp) > maior)
        {
            maior = qtd_na_encomenda(i, idp);
            encomenda = i;
        }
    /*Se o produto nao existe em nenhuma encomenda, nao da output*/
    if (maior > 0)
        printf("Maximo produto %d %d %d.\n", idp, encomenda, maior);
}

/*Lista todos os produtos existentes no sistema por ordem crescente de preco.*/
void lista_produtos()
{
    int i, idp;
    int idp_prod[MAX_PRODUTOS]; /*Vetor auxiliar com os indices dos produtos existentes que vai ser ordenado*/

    for (i = 0; i < cont_produtos; i++)
        idp_prod[i] = i;

    mergesort (idp_prod, 0, cont_produtos-1);

    printf("Produtos\n");
        for (i = 0; i < cont_produtos; i++)
        {
            idp = idp_prod[i];
            printf("* %s %d %d\n", registo_prod[idp].des, preco_prod(idp), qtd_prod(idp));
        }
}

/*Lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/
void lista_produtos_encomenda()
{
    int i, ide, idp;

    scanf("%d", &ide);

    if (!encomenda_existe(ide))
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    /*Da print ao vetor prod_ord existente na encomenda*/
    printf("Encomenda %d\n", ide);
    for (i=0;i<registo_enc[ide].n_prod;i++)
    {
        idp = registo_enc[ide].prod_ord[i];
        printf("* %s %d %d\n", registo_prod[idp].des, preco_prod(idp), qtd_na_encomenda(ide, idp));
    }
}

/*---FUNCOES DE SORTING---*/

/*Organiza um vetor utilizando o algoritmo de insertion sort*/
void insertion_sort(int arr[], int n) 
{
    int i, element;

    element = arr[n-1];

    if (n == 1)
        return;

    for (i=(n-2);i>=0;i--)
    {
        if (strcmp (registo_prod[element].des, registo_prod[arr[i]].des) < 0)
            arr[i+1] = arr[i];

        else
        {
            arr[i+1] = element;
            break;
        }
    }
    if (i == -1)
        arr[i+1] = element;
}

/*Organiza um vetor utilizando o algoritmo de merge sort*/
void mergesort (int arr[], int esq, int drt)
{
    int m = (drt+esq)/2;

    if (drt <= esq)
        return;

    mergesort (arr, esq, m);
    mergesort (arr, m+1, drt);
    merge (arr, esq, m, drt);
}

/*Devolve um vector ordenado, em a[esq..drt] , dados dois vectores ordenados em arr[esq..m] e a[m+1..drt]*/
void merge (int arr[], int esq, int m, int drt)
{
    int i, j, k;

    for (i=m+1;i>esq;i--)
        aux[i-1] = arr[i-1];
    
    for (j=m;j<drt;j++)
        aux[drt+m-j] = arr[j+1];
    
    for (k=esq;k<=drt;k++)
    {
        if (preco_prod(aux[j]) < preco_prod(aux[i]) || (preco_prod(aux[j]) == preco_prod(aux[i]) && aux[j] < aux[i]))
            arr[k] = aux[j--];
        else
            arr[k] = aux[i++];
    }
}
