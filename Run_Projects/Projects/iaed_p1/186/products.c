#include <stdio.h>
#include <string.h>
#include "products.h"
#include "packages.h"

/* Variavel global que armazena todos os produtos do sistema. Inicializada a
   zero para que o atributo 'alive' de cada produto seja definido a zero. */
Product products[MAX_PRODUCTS] = {0};

/* Variavel global correspodente ao numero total de produtos existentes no
   sistema. */
int productCount = 0;

/* Extrai um argumento em formato string e escreve-o na string dada. Limita
   o tamanho dessa string ao tamanho maximo fornecido. Esta funcao auxiliar
   eh apenas utilizada na logica do comando 'a'. */
void getStringArgument(char s[], int maxSize)
{
    int position = 0;
    int c = getchar();

    /* Ler caracter a caracter ate um ':', '\n' ou EOF. */
    while (c != EOF && c != ':' && c != '\n' && position < maxSize - 1)
    {
        s[position] = c;
        position++;

        c = getchar();
    }

    s[position] = '\0'; /* Finalizar string. */
}

/* Retorna se o identificador fornecido corresponde a um produto existente. */
int productExists(int idp)
{
    return idp >= 0 && idp < productCount;
}

/* Algoritmo de particao utilizado na funcao 'sortProductsByPrice'. Ordena a
   lista por ordem crescente de preco, utilizando a ordem crescente por
   identificador como desempate. */
int partition(Product products[], int left, int right)
{
    Product pivot = products[right]; /* O pivot. */
    int i = left - 1; /* Chave dos elementos mais pequeno (que o pivot). */
    int j;
    Product holder; /* Variavel temporaria para fazer a troca de elementos. */

    /* Percorre todos os elementos da array (exceto pivot) e move os elementos
       com preco menor que o pivot para o inicio. */
    for (j = left; j <= right - 1; j++)
        /* Condicao para ordenar por preco, usando a ordem crescente do
           identificador como desempate. */
        if (products[j].price < pivot.price || (products[j].price == pivot.price && products[j].id < pivot.id))
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

/* Algoritmo QuickSort para ordenar os produtos por ordem crescente de preco,
   utilizando a ordem crescente de identificador como desempate. */
void sortProductsByPrice(Product products[], int left, int right)
{
    int pivot;
    if (left < right)
    {
        /* Fazer particao */
        pivot = partition(products, left, right);

        /* Ordenar o restante da array, nao alterando mais o pivot. */
        sortProductsByPrice(products, left, pivot - 1);
        sortProductsByPrice(products, pivot + 1, right);
    }
}

/*#####################################################
   Funcoes responsaveis pela logica de cada comando:
#####################################################*/

/* Funcao responsavel pela logica do comando 'a'. Adiciona um novo produto ao
   sistema.*/
void addProductCmd()
{
    Product newProduct; /* Novo produto. */

    /* Ignorar espaco antes da descricao. */
    getchar();

    /* Ler argumentos. */
    getStringArgument(newProduct.description, PROD_DESC_SIZE);
    scanf(
        "%d:%d:%d",
        &newProduct.price,
        &newProduct.weight,
        &newProduct.quantity);

    /* Finalizar novo produto e adicionar ao sistema. */
    newProduct.id = productCount++;
    newProduct.alive = 1;
    products[newProduct.id] = newProduct;

    /* Output */
    printf("Novo produto %d.\n", newProduct.id);
}

/* Funcao responsavel pela logica do comando 'q'. Adiciona stock a um produto
   existente no sistema. */
void addStockCmd()
{
    int idp; /* Identificador do produto. */
    int qtd; /* Quantidade do stock a adcionar. */

    /* Ler argumentos. */
    scanf(" %d:%d", &idp, &qtd);

    if (!productExists(idp)) /* Verificar se o produto existe. */
        printf(
            "Impossivel adicionar produto %d ao stock. Produto inexistente.\n",
            idp);
    else /* Adicionar stock ao sistema. */
        products[idp].quantity += qtd;
}

/* Funcao responsavel pela logica do comando 'r'. Remove stock a um produto
   existente no sistema. */
void removeStockCmd()
{
    int idp; /* Identificador do produto. */
    int qtd; /* Quantidade do stock a adcionar. */

    /* Ler argumentos. */
    scanf(" %d:%d", &idp, &qtd);

    if (!productExists(idp)) /* Verificar se o produto existe. */
        printf(
            "Impossivel remover stock do produto %d. Produto inexistente.\n",
            idp);
    /* Verificar se existe stock suficiente. */
    else if (products[idp].quantity < qtd)
        printf(
            "Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",
            qtd, idp);
    else /* Remover o stock do sistema. */
        products[idp].quantity -= qtd;
}

/* Funcao responsavel pela logica do comando 'p'. Altera o preco de um produto
   existente no sistema. */
void changePriceCmd()
{
    int idp;   /* Identificador do produto. */
    int preco; /* Novo preco. */

    /* Ler argumentos. */
    scanf(" %d:%d", &idp, &preco);

    if (!productExists(idp)) /* Verificar se o produto existe. */
        printf(
            "Impossivel alterar preco do produto %d. Produto inexistente.\n",
            idp);
    else /* Alterar o preco do produto no sistema. */
        products[idp].price = preco;
}

/* Funcao responsavel pela logica do comando 'm'. Retorna o identificador da
   encomenda em que um dado produto ocorre mais vezes. */
void biggestOccurrenceCmd()
{
    int idp;     /* Identificador do produto. */
    int ide;     /* Identificador da encomenda da maior ocorrencia. */
    int qtd = 0; /* Quantidade do produto na maior ocorrencia. */
    int i, j;

    /* Ler argumentos */
    scanf(" %d", &idp);

    if (!productExists(idp)) /* Verificar se o produto existe. */
    {
        printf(
            "Impossivel listar maximo do produto %d. Produto inexistente.\n",
            idp);
    }
    else
    {
        /* Achar a ocorrencia maior. */
        for (j = 0; j < packageCount; j++)
            for (i = 0; i < MAX_PACKAGE_WEIGHT && packages[j][i].alive; i++)
                if (packages[j][i].id == idp)
                {
                    if (packages[j][i].quantity > qtd)
                    {
                        qtd = packages[j][i].quantity;
                        ide = j;
                    }
                    break; /* Instancia do produto jah encontrado na encomenda,
                              nao precisamos continuar a percorrer a encomenda. */
                }

        if (qtd > 0) /* Output */
            printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
    }
}

/* Funcao responsavel pela logica do comando 'l'. Lista todos os produtos
   existentes no sistema por ordem crescente de preco. */
void listAllProductsCmd()
{
    Product productsCopy[MAX_PRODUCTS]; /* Copia da array dos produtos. */
    int i;

    /* Clonar a array de produtos e ordenar por ordem crescente de preco. */
    memcpy(&productsCopy, &products, sizeof(products));
    sortProductsByPrice(productsCopy, 0, productCount - 1);

    /* Output */
    printf("Produtos\n");
    for (i = 0; i < productCount; i++)
        printf(
            "* %s %d %d\n",
            productsCopy[i].description,
            productsCopy[i].price,
            productsCopy[i].quantity);
}

/* Funcao responsavel pela logica do comando 'k'. Lista todos os produtos
   existentes no sistema por ordem crescente de identificador. Apenas para
   efeitos de depurracao. */
void listAllProductsIDCmd()
{
    int i;

    /* Output dos produto por ordem crescente de ID */
    printf(
        "Produtos\n%-4s %-5s %-4s %-10s %s\n",
        "ID",
        "Preco",
        "Peso",
        "Quantidade",
        "Descricao");

    for (i = 0; i < productCount; i++)
        printf(
            "%-4d %-5d %-4d %-10d %s\n",
            products[i].id,
            products[i].price,
            products[i].weight,
            products[i].quantity,
            products[i].description);
}
