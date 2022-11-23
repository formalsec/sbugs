#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include "products.h"
#include "packages.h"

/* Variavel global que armazena todas as encomendas do sistema. Inicializada a
   zero para que o atributo 'alive' de cada produto seja definido a zero. */
Product packages[MAX_PACKAGES][MAX_PACKAGE_WEIGHT] = {0};

/* Variavel global que armazena o total de encomendas no sistema. */
int packageCount = 0;

/* Retorna se o identificador fornecido corresponde a uma encomenda
   existente. */
int packageExists(int ide)
{
    return ide >= 0 && ide < packageCount;
}

/* Retorna o peso total da encomenda com o identificador dado. */
int packageWeight(int ide)
{
    int weight = 0; /* Peso total da encomenda. */
    int i;

    /* Percorre todos os produtos da encomenda e soma todos os pesos. */
    for (i = 0; i < MAX_PACKAGE_WEIGHT && packages[ide][i].alive; i++)
        weight += packages[ide][i].weight * packages[ide][i].quantity;

    return weight;
}

/* Adiciona um produto dado a uma encomenda dada. */
void addProdToPack(int ide, int idp, int qtd)
{
    int exists = 0; /* Se o produto jah existe na encomenda ou nao. */
    int i;

    products[idp].quantity -= qtd; /* Remover stock do sistema */

    /* Verificar se o produto jah estah na encomenda. */
    for (i = 0; i < MAX_PACKAGE_WEIGHT && packages[ide][i].alive; i++)
        if (packages[ide][i].id == idp)
        { /* Produto jah existente na encomenta, aumentar quantidade. */
            packages[ide][i].quantity += qtd;
            exists = 1;

            break; /* Excusado continuar porque o produto jah foi encontrado. */
        }

    if (!exists)
    { /* Adicionar produto no fim da encomenda caso nao exista na encomenda. */
        packages[ide][i] = products[idp];
        packages[ide][i].quantity = qtd;
    }
}

/* Remove um produto dado de uma encomenda dada. */
void removeProdFromPack(int ide, int idp)
{
    int found = -1; /* Posicao em que o produto foi encontrado. */
    int i;

    /* Procurar produto na encomenda. */
    for (i = 0; i < MAX_PACKAGE_WEIGHT && packages[ide][i].alive; i++)
        if (packages[ide][i].id == idp)
        {
            found = i;
        }

    if (found >= 0)
    {
        /* Adicionar stock de volta ao sistema. */
        products[idp].quantity += packages[ide][found].quantity;

        /* Mover o ultimo produto da encomenda para o espaco do produto
           removido.*/
        packages[ide][found] = packages[ide][i - 1];
        packages[ide][i - 1].alive = 0;
    }
}

/* Algoritmo de particao utilizado na funcao 'sortProductsByAlfa'. Ordena a
   lista por ordem alfabetica da descricao. */
int partitionAlfa(Product products[], int left, int right)
{
    Product pivot = products[right]; /* O pivot. */
    int i = left - 1;                /* Chave dos elementos mais pequeno (que o pivot) */
    int j;
    Product holder; /* Variavel temporaria para fazer a troca de elementos. */

    /* Percorre todos os elementos da array (exceto pivot) e move os elementos
       que veem primeiro no alfabeto que o pivot para o inicio. */
    for (j = left; j <= right - 1; j++)
        /* Condicao para ordenar pela ordem alfabetica da descricao. */
        if (strcmp(products[j].description, pivot.description) < 0)
        {
            i++;

            if (i != j) /* Evitar trocar um elemento consigo mesmo. */
            {
                holder = products[i];
                products[i] = products[j];
                products[j] = holder;
            }
        }

    /* Colocar o pivot entre os elementos mais pequenos e os maiores. */
    i++;
    holder = products[i];
    products[i] = products[j];
    products[j] = holder;

    return i; /* Devolve a posicao final do pivot. */
}

/* Algoritmo QuickSort para ordenar os produtos por ordem alfabetica da
   descricao. */
void sortProductsByAlfa(Product products[], int left, int right)
{
    int pivot; /* Posicao do pivot. */
    if (left < right)
    {
        /* Fazer particao */
        pivot = partitionAlfa(products, left, right);

        /* Ordenar o restante da array, nao alterando mais o pivot. */
        sortProductsByAlfa(products, left, pivot - 1);
        sortProductsByAlfa(products, pivot + 1, right);
    }
}

/*#####################################################
   Funcoes responsaveis pela logica de cada comando:
#####################################################*/

/* Funcao responsavel pela logica do comando 'N'. Cria uma nova encomenda. */
void createPackageCmd()
{
    /* Output */
    printf("Nova encomenda %d.\n", packageCount);

    /* Incrementa o total de encomendas. */
    packageCount++;
}

/* Funcao responsavel pela logica do comando 'A'. Adiciona um produto a uma
   encomenda.*/
void addProdToPackCmd()
{
    int ide; /* Identificador da encomenda. */
    int idp; /* Identificador do produto. */
    int qtd; /* Quantidade de produto a adicionar. */

    /* Ler argumentos */
    scanf(" %d:%d:%d", &ide, &idp, &qtd);

    if (!packageExists(ide)) /* Verificar se a encomenda existe. */
        printf(
            "Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",
            idp,
            ide);
    else if (!productExists(idp)) /* Verificar se o produto existe. */
        printf(
            "Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",
            idp,
            ide);
    else if (products[idp].quantity < qtd) /* Verificar se existe stock. */
        printf(
            "Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",
            idp,
            ide);
    /* Verificar limite de peso. */
    else if (packageWeight(ide) + (products[idp].weight * qtd) > MAX_PACKAGE_WEIGHT)
        printf(
            "Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n",
            idp,
            ide,
            MAX_PACKAGE_WEIGHT);
    else /* Adiciona produto ah encomenda e remove stock. */
        addProdToPack(ide, idp, qtd);
}

/* Funcao responsavel pela logica do comando 'R'. Remove um produto de uma
   encomenda. */
void removeProdFromPackCmd()
{
    int ide; /* Identificador da encomenda. */
    int idp; /* Identificador do produto. */

    /* Ler argumentos */
    scanf(" %d:%d", &ide, &idp);

    if (!packageExists(ide)) /* Verficar se a encomenda existe. */
        printf(
            "Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",
            idp,
            ide);
    else if (!productExists(idp)) /* Verificar se o produto existe. */
        printf(
            "Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",
            idp,
            ide);
    else /* Remover produto da encomenda e devolver stock ao sistema. */
        removeProdFromPack(ide, idp);
}

/* Funcao responsavel pela logica do comando 'C'. Calcula o custo de uma
   encomenda. */
void calcPackagePriceCmd()
{
    int ide;      /* Identificador da encomenda. */
    int cost = 0; /* Custo total. */
    int i;

    /* Ler argumentos. */
    scanf(" %d", &ide);

    if (!packageExists(ide)) /* Verificar se a encomenda existe. */
    {
        printf(
            "Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",
            ide);
    }
    else
    {
        for (i = 0; i < MAX_PACKAGE_WEIGHT && packages[ide][i].alive; i++)
            /* Adiciona o preco de cada produto. O preco na encomenda pode
               nao estar atualizado portanto utilizamos o preco do stock. */
            cost += products[packages[ide][i].id].price * packages[ide][i].quantity;

        /* Output */
        printf("Custo da encomenda %d %d.\n", ide, cost);
    }
}

/* Funcao responsavel pela logica do comando 'E'. Retorna a descricao e a
   quantidade de um produto numa dada encomenda. */
void returnProdInfoCmd()
{
    int ide;     /* Identificador da encomenda. */
    int idp;     /* Identificador do produto. */
    int qtd = 0; /* Quantidade de produto na encomenda. */
    int i;

    /* Ler argumentos. */
    scanf(" %d:%d", &ide, &idp);

    if (!packageExists(ide)) /* Verificar se a encomenda existe. */
        printf(
            "Impossivel listar encomenda %d. Encomenda inexistente.\n",
            ide);
    else if (!productExists(idp)) /* Verificar se o produto existe. */
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else
    {
        /* Encontrar o produto. */
        for (i = 0; i < MAX_PACKAGE_WEIGHT && packages[ide][i].alive; i++)
            if (packages[ide][i].id == idp)
            {
                qtd = packages[ide][i].quantity;
                break; /* Produto foi encontrado, nao precisamos continuar
                          o loop. */
            }

        /* Output */
        printf("%s %d.\n", products[idp].description, qtd);
    }
}

/* Funcao responsavel pela logica do comando 'L'. Lista todos os produtos de
   uma encomenda por ordem alfabetica da descricao. */
void listPackageProdsCmd()
{
    int ide;   /* Identificador da encomenda. */
    int items; /* Quantidade de items na encomenda. */
    int i;

    /* Ler argumentos. */
    scanf(" %d", &ide);

    if (!packageExists(ide)) /* Verificar se a encomenda existe. */
    {
        printf(
            "Impossivel listar encomenda %d. Encomenda inexistente.\n",
            ide);
    }
    else
    {
        /* Conta o numero de items na encomenda. */
        for (items = 0; items < MAX_PACKAGE_WEIGHT && packages[ide][items].alive; items++)
            ;

        /* Ordenar encomenda */
        sortProductsByAlfa(packages[ide], 0, items - 1);

        /* Output */
        printf("Encomenda %d\n", ide);

        for (i = 0; i < items; i++)
            printf(
                "* %s %d %d\n",
                packages[ide][i].description,
                /* Preco da encomenda pode nao estar atualizado na encomenda,
                   portanto retiramos do stock. */
                products[packages[ide][i].id].price,
                packages[ide][i].quantity);
    }
}

/* Funcao responsavel pela logica do comando 'K'. Lista todos os produtos de
   uma encomenda por ordem de insercao. */
void listPackageProdsIDCmd()
{
    int ide; /* Identificador da encomenda. */
    int i;

    /* Ler argumentos */
    scanf(" %d", &ide);

    /* Output dos produto por ordem arbitraria */
    printf(
        "Encomenda %d\n%-4s %-5s %-4s %-10s %s\n",
        ide,
        "ID",
        "Preco",
        "Peso",
        "Quantidade",
        "Descricao");

    for (i = 0; i < MAX_PACKAGE_WEIGHT && packages[ide][i].alive; i++)
        printf(
            "%-4d %-5d %-4d %-10d %s\n",
            packages[ide][i].id,
            packages[ide][i].price,
            packages[ide][i].weight,
            packages[ide][i].quantity,
            packages[ide][i].description);
}
