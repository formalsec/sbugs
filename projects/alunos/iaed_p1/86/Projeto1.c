#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Definicao de constantes */
#define ZERO 0 /* Usado como flag de selecao do comparador de valores (dependente do tipo de array a ordenar) e como valor minimo nos arrays usados no merge sort. */
#define UM 1 /* Usado como flag no merge sort. */
#define MAX_NOME 64 /* Maximo de caracteres que uma string de descricao de um produto pode ter (incluindo '\0'). */
#define MAX_PESO 200 /* Peso maximo de uma encomenda. */
#define MAX_ENC 500 /* Maximo de encomendas permitidas no sistema. */
#define MAX_PROD 10000 /* Maximo de produtos permitidos no sistema. */

/* Definicao da estrutura usada nos produtos, composto pelo seu nome, preco, peso e quantidade do produto no sistema. */
typedef struct
{
    char nome[MAX_NOME];
    int preco;
    int peso;
    int qtd;
}
produto;

/* Inicializacao das variaveis e arrays a usar no projeto. Foi necessario 
faze-lo globalmente, devido a dimensao insuficente da pilha. */
produto produtos[MAX_PROD]; /* Inicializacao do array dos produtos. */
char comm; /* Inicializacao do caracter usado como comando do programa. */
int encomendas[MAX_ENC][MAX_PROD]; /* Inicializaco do array das encomendas. */
int contador_prod = 0, contador_enc = 0; /* Inicializacao dos contadores do numero de produtos e de encomendas no sistema. */
int ord[MAX_PROD]; /* Inicializacao do array dos indices usado no merge sort, chamado pelas funcoes comm_l e comm_L. */

/* Adiciona um produto novo ao sistema (com auxilio do incremento do contador de produtos,
feito dentro da funcao main), de acordo com a definicao da estrutura correspondente. */
void comm_a(int contador_prod)
{
    scanf (" %[^:]:%d:%d:%d", produtos[contador_prod].nome, &produtos[contador_prod].preco, &produtos[contador_prod].peso, &produtos[contador_prod].qtd);
    printf ("Novo produto %d.\n", contador_prod);
}

/* Adiciona qtd unidades do produto idp ao sistema, caso esse produto exista. */
void comm_q (int contador_prod)
{
    int idp, qtd;
    scanf (" %d", &idp);
    if (idp < contador_prod) /* Verificacao da existencia do produto. */
    {
        scanf (":%d", &qtd);
        produtos[idp].qtd += qtd;
    }
    else
        printf ("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

/* Adiciona uma encomenda ao sistema (com auxilio do incremento 
do contador de encomendas, feito dentro da funcao main). */
void comm_N (int contador_enc)
{
    printf ("Nova encomenda %d.\n", contador_enc);
}

/* Adiciona qtd unidades do produto idp a encomenda ide, caso esse produto 
exista na quantidade pedida, a encomenda tambem exista e o peso da encomenda
(soma dos produtos, multiplicados, respetivamente, pelo seu peso unitario) nao
exceda 200. Se tal for possivel, essas unidades sao removidas do sistema. */
void comm_A (int contador_prod, int contador_enc)
{
    int ide, idp, qtd, peso = 0, i;
    scanf ("%d:%d:", &ide, &idp);
    if (ide >= contador_enc) /* Verificacao da existencia da encomenda. */
        printf ("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else
    {
        if (idp >= contador_prod) /* Verificacao da existencia do produto. */
            printf ("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        else
        {
            scanf ("%d", &qtd);
            if (produtos[idp].qtd < qtd) /* Verificacao do numero de unidades do produto no sistema. */
                printf ("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
            else
            {
                for (i = 0; i < contador_prod && peso <= MAX_PESO; i++)
                    peso += produtos[i].peso * encomendas[ide][i];
                peso += produtos[idp].peso * qtd;
                if (peso > MAX_PESO) /* Verificacao do peso da encomenda. */
                    printf ("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
                else /* Transferencia das unidades do sistema para a encomenda. */
                {
                    encomendas[ide][idp] += qtd;
                    produtos[idp].qtd -= qtd;
                }
            }
        }
    }
}

/* Remove qtd unidades do produto idp do sistema, 
caso esse produto exista na quantidade pedida.*/
void comm_r (int contador_prod)
{
    int idp, qtd;
    scanf ("%d", &idp);
    if (idp >= contador_prod) /* Verificacao da existencia do produto. */
        printf ("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else
    {
        scanf (":%d", &qtd);
        if (qtd > produtos[idp].qtd) /* Verificacao do numero de unidades do produto no sistema. */
            printf ("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        else
            produtos[idp].qtd -= qtd; /* Remocao das unidades do sistema. */
    }
    
}

/* Remove todas as unidades do produto idp da encomenda ide, caso ambos existam.
Se tal for possivel, essas unidades sao devolvidas ao sistema. */
void comm_R (int contador_prod, int contador_enc)
{
    int ide, idp;
    scanf ("%d:%d:", &ide, &idp);
    if (ide >= contador_enc) /* Verificacao da existencia da encomenda. */
        printf ("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else
    {
        if (idp >= contador_prod) /* Verificacao da existencia do produto. */
            printf ("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        else /* Transferencia de todas as unidades da encomenda para o sistema. */
        {
            produtos[idp].qtd += encomendas[ide][idp];
            encomendas[ide][idp] = 0;
        }
    }
}

/* Calcula e devolve o custo total de uma encomenda (soma dos produtos, multiplicados,
respetivamente, pelo seu custo unitario), caso essa encomenda exista. */
void comm_C (int contador_prod, int contador_enc)
{
    int ide, i, total = 0;
    scanf ("%d", &ide);
    if (ide >= contador_enc) /* Verificacao da existencia da encomenda. */
        printf ("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else
    {
        for (i = 0; i < contador_prod; i++) /* Calculo do custo da encomenda. */
            total += encomendas[ide][i] * produtos[i].preco;
        printf("Custo da encomenda %d %d.\n", ide, total);
    }
}

/* Altera o preco unitario de um produto, caso ele exista. */
void comm_p (int contador_prod)
{
    int idp;
    scanf ("%d", &idp);
    if (idp >= contador_prod) /* Verificacao da existencia do produto. */
        printf ("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else /* Alteracao do custo unitario do produto. */
        scanf (":%d", &produtos[idp].preco);
}

/* Devolve o nome do produto idp e a sua quantidade na encomenda ide, caso ambos existam. */
void comm_E (int contador_prod, int contador_enc)
{
    int ide, idp;
    scanf ("%d", &ide);
    if (ide >= contador_enc) /* Verificacao da existencia da encomenda. */
        printf ("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else
    {
        scanf (":%d", &idp);
        if (idp >= contador_prod) /* Verificacao da existencia do produto. */
            printf ("Impossivel listar produto %d. Produto inexistente.\n", idp);
        else
            printf ("%s %d.\n", produtos[idp].nome, encomendas[ide][idp]);
    }
}

/* Devolve o ide (ID da encomenda) onde o produto idp existe em 
maior quantidade e a respetiva quantidade, caso ambos existam. */
void comm_m (int contador_prod, int contador_enc)
{
    int idp, ide, ide_max, qtd = 0;
    scanf ("%d", &idp);
    if (idp >= contador_prod) /* Verificacao da existencia do produto. */
        printf ("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else
    {
        for (ide = 0; ide < contador_enc; ide++)
        {
            if (encomendas[ide][idp] > qtd)
            {
                ide_max = ide;
                qtd = encomendas[ide][idp];
            }
        }
        if (qtd > 0)
            printf ("Maximo produto %d %d %d.\n", idp, ide_max, qtd);
    }
}

/* Funcao nuclear do merge sort: a flag e usada como alternador entre
o arrays a ordenar, conforme a funcao que invocou o merge sort (1 no
caso de comm_l, 0 no caso de comm_L). Esta funcao e estavel, devido
as restricoes de desempate descritas no enunciado do projeto. */
void merge(int flag, int esq, int meio, int dir)
{
    int aux[MAX_PROD];
    int i, j, k, cmp;
    for (i = meio+1; i > esq; i--)
        aux[i-1] = ord[i-1];
    for (j = meio; j < dir; j++)
        aux[dir+meio-j] = ord[j+1];
    for (k = esq; k <= dir; k++)
    {
        if (flag)
            cmp = produtos[aux[j]].preco < produtos[aux[i]].preco;
        else
            cmp = strcmp(produtos[aux[j]].nome, produtos[aux[i]].nome) < 0;
        if (cmp || (produtos[aux[j]].preco == produtos[aux[i]].preco && aux[j] < aux[i]))
            ord[k] = aux[j--];
        else
            ord[k] = aux[i++];
    }
}

/* Funcao de base do merge sort, incluido a fracao recursiva,
como usado nos slides da unidade curricular. */
void mergesort(int flag, int esq, int dir) 
{
    int meio = (dir+esq)/2;
    if (dir <= esq)
        return;
    mergesort(flag, esq, meio);
    mergesort(flag, meio+1, dir);
    merge(flag, esq, meio, dir);
}

/* Devolve todos os produtos presentes no sistema, por ordem crescente 
de custo unitario, com recurso a um array auxiliar que contem os indices dos produtos
e que, no final, refletira essa ordem. Em caso de empate, os produtos em questao sao 
listados por ordem crescente de idp.*/
void comm_l (int contador_prod)
{
    int i, j;
    puts ("Produtos");
    for (i = 0; i < contador_prod; i++) /* Copia dos indices do array dos produtos da encomenda ide para os ordenar depois. */
        ord[i] = i;
    mergesort (UM, 0, contador_prod-1); /* Merge sort do array dos indices da forma descrita no comentario do cabecalho.*/
    for (j = 0; j < contador_prod; j++)
        printf ("* %s %d %d\n", produtos[ord[j]].nome, produtos[ord[j]].preco, produtos[ord[j]].qtd);
}

/* Devolve todos os produtos presentes na encomenda ide, caso esta exista,
por ordem alfabetica do seu nome, com recurso a um array auxiliar que 
contem os indices dos produtos e que, no final, refletira essa ordem. 
Em caso de empate, os produtos em questao sao listados por ordem crescente de idp. */
void comm_L (int contador_prod, int contador_enc)
{
    int ide, i, j, contador = 0;
    scanf ("%d", &ide);
    if (ide >= contador_enc) /* Verificacao da existencia do produto. */
        printf ("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else
    {
        printf ("Encomenda %d\n", ide);
        for (i = 0; i < contador_prod; i++) /* Copia dos indices do array dos produtos da encomenda ide para os ordenar depois. */
            if (encomendas[ide][i] != 0)
                ord[contador++] = i;
        mergesort (ZERO, 0, contador-1); /* Merge sort do array dos indices da forma descrita no comentario do cabecalho.*/
        for (j = 0; j < contador; j++)
            if (encomendas[ide][ord[j]] > 0)
                printf ("* %s %d %d\n", produtos[ord[j]].nome, produtos[ord[j]].preco, encomendas[ide][ord[j]]);
    }
}

/* Recebe uma letra como comando e invoca a funcao correspondente, como
descrito no enunciado do projeto. O comando 'x' encerra o programa. */
int main()
{
    while ((comm = getchar()) != 'x') /* Introducao do comando. */
    {
        switch (comm)
        {
            case 'a':
                comm_a (contador_prod++);
                break;
            case 'q':
                comm_q (contador_prod);
                break;
            case 'N':
                comm_N (contador_enc++);
                break;
            case 'A':
                comm_A (contador_prod, contador_enc);
                break;
            case 'r':
                comm_r (contador_prod);
                break;
            case 'R':
                comm_R (contador_prod, contador_enc);
                break;
            case 'C':
                comm_C (contador_prod, contador_enc);
                break;
            case 'p':
                comm_p (contador_prod);
                break;
            case 'E':
                comm_E (contador_prod, contador_enc);
                break;
            case 'm':
                comm_m (contador_prod, contador_enc);
                break;
            case 'l':
                comm_l (contador_prod);
                break;
            case 'L':
                comm_L (contador_prod, contador_enc);
                break;
        }
    }
    return 0;
} 