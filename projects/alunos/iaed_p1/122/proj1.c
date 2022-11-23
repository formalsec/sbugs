#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS_DIF 10000
#define MAX_DESC 63
#define MAX_ENCOMENDAS 500

int idp = 0;                                                                /* identificador do produto */
int ide = 0;                                                                /* identificador da encomenda */

/* estrutura de um produto */
typedef struct
    {
        int idp;
        char descricao[MAX_DESC];
        int preco;
        int peso;
        int qtd;
    } produto;

produto sistema_produtos[MAX_PRODUTOS_DIF] = {0};                           /* inicializa tudo a zeros */
produto sistema_encomendas[MAX_ENCOMENDAS][MAX_PRODUTOS_DIF] = {0};

int aux[MAX_PRODUTOS_DIF];

/* ordenacao dos produtos pelo preco para a funcao l */

void merge_produtos(int a[], int left, int m, int right)
{ 
  int i, j, k;
  for (i = m+1; i > left; i--) 
  {
    aux[i-1] = a[i-1];
  }
  for (j = m; j < right; j++)
  {
    aux[right+m-j] = a[j+1];
  }
  for (k = left; k <= right; k++)
  {
    if ((sistema_produtos[aux[j]].preco < sistema_produtos[aux[i]].preco) || i > m)
    {
      a[k] = aux[j--];
    }
    else
    {
      a[k] = aux[i++];
    }
  }
}
  
void mergeSort_produtos(int a[], int left, int right) 
{ 
    int m = left+(right-left)/2;
    if (right <= left) 
    {
        return;
    }
    else
    {
        mergeSort_produtos(a, left, m); 
        mergeSort_produtos(a, m+1, right); 
        merge_produtos(a, left, m, right); 
    }
} 

/* funcao que serve para a criacao de um novo produto */
void novo_produto()                                                         /* funcao do a */
{
    scanf(" %[^:]:%d:%d:%d", sistema_produtos[idp].descricao, &sistema_produtos[idp].preco, &sistema_produtos[idp].peso, &sistema_produtos[idp].qtd);
    sistema_produtos[idp].idp = idp;
    printf("Novo produto %d.\n", idp);
    idp++;
    return;
}

/* funcao que serve para aumentar a quantidade de um produto no sistema de produtos */
void adiciona_stock()                                                       /* funcao do q */
{
    int extrastock, idp_aux;
    scanf("%d:%d", &idp_aux, &extrastock);
    /* verifica se o idp_aux existe */
    if (idp_aux > (idp-1))
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_aux);
        return;
    }
    else
    {
        /* atualizacao da quantidade do produto no sistema */
        sistema_produtos[idp_aux].qtd += extrastock;
        return;
    }   
}

/* funcao que cria uma encomenda */
void cria_encomenda()                                                       /* funcao do N */
{
    /* cria encomenda vazia */
    printf("Nova encomenda %d.\n", ide);
    ide++;
    return;
}

/* funcao que serve para adicionar um dado produto a uma dada encomenda */
void add_encomenda()                                                       
{
    int i, ide_aux, idp_aux, qtd_aux, peso_aux;
    peso_aux = 0;
    scanf("%d:%d:%d", &ide_aux, &idp_aux, &qtd_aux);

    /* verifica se o ide_aux existe */
    if (ide_aux > (ide-1))                                                  /* verifica se o ide_aux esta dentro dos limites dos ides existentes */
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_aux, ide_aux);
        return;
    }

    /* verifica se o idp_aux existe */
    else if (idp_aux > (idp-1))                                             /* o que ta em cima mas para os idps */
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_aux, ide_aux);
        return;
    }

    /* verifica se a quantidade que queremos tirar eh maior que a quantidade existente do produto */
    else if (qtd_aux > sistema_produtos[idp_aux].qtd)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_aux, ide_aux);
        return;
    }

    peso_aux += qtd_aux * sistema_produtos[idp_aux].peso;
    /* verificacao do peso dos produtos que quero por */
    for (i = 0; i < MAX_PRODUTOS_DIF; i++)
    {
        peso_aux += sistema_produtos[i].peso * sistema_encomendas[ide_aux][i].qtd;
    }

    if (peso_aux > 200)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_aux, ide_aux);
        return;
    }

    else
    {
        /* atualizacao da encomenda e do produto */
        sistema_encomendas[ide_aux][idp_aux].idp = idp;
        sistema_encomendas[ide_aux][idp_aux].preco = sistema_produtos[idp_aux].preco;
        sistema_encomendas[ide_aux][idp_aux].qtd += qtd_aux;
        sistema_produtos[idp_aux].qtd -= qtd_aux;
        return;
    }
}

/* funcao que serve para remover uma certa quantidade de um dado produto no sistema */
void remove_stock()
{
    int idp_aux, qtd_aux;
    scanf("%d:%d", &idp_aux, &qtd_aux);

    if (idp_aux > (idp-1))
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_aux);
        return;
    }
    else if (qtd_aux > sistema_produtos[idp_aux].qtd)
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd_aux, idp_aux);
        return;
    }
    else
    {
        /* atualizacao da quantidade do produto no sistema */
        sistema_produtos[idp_aux].qtd -= qtd_aux;
        return;
    }
}

/* funcao que serve para remover um dado produto de uma dada encomenda */
void remove_produto()
{
    int ide_aux, idp_aux, qtd_aux, peso_aux;
    scanf("%d:%d", &ide_aux, &idp_aux);
    qtd_aux = 0;
    peso_aux = 0;

    if (ide_aux > (ide-1))
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp_aux, ide_aux);
        return;
    }
    
    else if (idp_aux > (idp-1))
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp_aux, ide_aux);
        return;
    }
    
    else
    {
        qtd_aux = sistema_encomendas[ide_aux][idp_aux].qtd;
        peso_aux = sistema_encomendas[ide_aux][idp_aux].peso * sistema_encomendas[ide_aux][idp_aux].qtd;
        /* atualiza tudo na encomenda */
        sistema_encomendas[ide_aux][idp_aux].qtd = 0;
        sistema_encomendas[ide_aux][idp_aux].preco = 0;
        sistema_encomendas[ide_aux][idp_aux].peso -= peso_aux;
        /* atualiza a quantidade do produto no sistema de produtos */
        sistema_produtos[idp_aux].qtd += qtd_aux;
        return;
    }
}

/* funcao que serve para devolver o custo total de uma encomenda */
void give_me_custo()
{   
    int ide_aux, i, custo_encomenda;
    custo_encomenda = 0;
    scanf("%d", &ide_aux);

    if (ide_aux > (ide-1))
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide_aux);
        return;
    }
    
    else
    {
        /* ciclo para contar o custo total da encomenda */
        for (i = 0; i < idp ; i++)
        {
            custo_encomenda += (sistema_encomendas[ide_aux][i].preco * sistema_encomendas[ide_aux][i].qtd);
        }
        printf("Custo da encomenda %d %d.\n", ide_aux, custo_encomenda);
        return;
    }
}

/* funcao que serve para alterar o preco de um dado produto no sistema */
void altera_preco()
{
    int e, preco_aux, idp_aux;
    scanf("%d:%d", &idp_aux, &preco_aux);
    if (idp_aux > (idp-1))
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_aux);
        return;
    }
    else
    {
        
        sistema_produtos[idp_aux].preco = preco_aux;

        /* tbm tenho de atualizar o preco dos produtos nas encomendas */

        for (e = 0; e < ide; e++)
        {
            sistema_encomendas[e][idp_aux].preco = preco_aux;
        }
        return;
    }
}

/* funcao para listar produtos existentes numa dada encomenda */
void lista_produto()
{
    int ide_aux, idp_aux;
    scanf("%d:%d", &ide_aux, &idp_aux);
    
    if (ide_aux > (ide-1))
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_aux);
        return;
    }
    
    else if (idp_aux > (idp-1))
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp_aux);
        return;
    }

    else
    {
        /* para ser listado a quantidade tem de ser maior >= 0, senao nao existe */

        if (sistema_encomendas[ide_aux][idp_aux].qtd >= 0)
        {
            printf("%s %d.\n", sistema_produtos[idp_aux].descricao, sistema_encomendas[ide_aux][idp_aux].qtd);
            return;
        }
        return;
    }
}

/* funcao que ve em que encomenda o produto dado ocorre mais */
 void ocorre_mais()
{
    int e, i, idp_aux, enco_index, product_index, maior;
    maior = 0;
    product_index = 0;
    enco_index = 0;

    scanf("%d", &idp_aux);

    if (idp_aux > (idp-1))
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_aux);
        return;
    }
    
    for (e = 0; e < ide; e++)
    {
        for (i = 0; i < idp; i++)
        {
            if (i == idp_aux)
            {   /* atualizacao do novo maior */
                if (maior < sistema_encomendas[e][i].qtd) 
                {
                    /* guardo o indice da encomenda e do produto */
                    maior = sistema_encomendas[e][i].qtd;
                    enco_index = e;    
                    product_index = i; 
                }
            }
        }  
    }

    if (maior != 0)
    {
    printf("Maximo produto %d %d %d.\n", product_index, enco_index, maior); 
    return;
    }
}


/* funcao para ordenar o preco dos produtos no sistema */
void ordena_price()
{
    int i;
    int ids[MAX_PRODUTOS_DIF];

    /* cria vetor com ids para usar depois como indices */
    for (i = 0; i < idp; i++)
    {
        ids[i] = i;
    }

    mergeSort_produtos(ids, 0, idp - 1);

    printf("Produtos\n");
    for (i = 0; i < idp; i++)
    {
        printf("* %s %d %d\n", sistema_produtos[ids[i]].descricao, sistema_produtos[ids[i]].preco, sistema_produtos[ids[i]].qtd);
    }
    return;
}

int main()
{
    int carater;

    while ((carater = getchar()) != EOF)
    {
        switch (carater)
        {
            case 'a':
            {   
                novo_produto();
                break; 
            }
            case 'q':
            {
                adiciona_stock();
                break;
            }
            case 'N':
            {
                cria_encomenda();
                break;
            }
            case 'A':
            {
                add_encomenda();
                break;
            }
            case 'r':
            {
                remove_stock();
                break;
            }
            case 'R':
            {
                remove_produto();
                break;
            }
            case 'C':
            {
                give_me_custo();
                break;
            }
            case 'p':
            {
                altera_preco();
                break;
            }
            case 'E':
            {
                lista_produto();
                break;
            }
            case 'm':
            {
                ocorre_mais();
                break;
            }
            case 'l':
            {
                ordena_price();
                break;
            }
            case 'x':
            {
                break;
            }
        }   
    }
    return 0;
}