#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include "products.h"
#include "packages.h"

int main()
{
    int command = getchar();

    while (command != EOF)
    {
        if (command == 'a')
            /* Adiciona um novo produto ao sistema. */
            addProductCmd();
        else if (command == 'q')
            /* Adiciona stock a um produto existente no sistema. */
            addStockCmd();
        else if (command == 'N')
            /* Cria uma nova encomenda. */
            createPackageCmd();
        else if (command == 'A')
            /* Adiciona um produto a uma encomenda. */
            addProdToPackCmd();
        else if (command == 'r')
            /* Remove stock a um produto existente. */
            removeStockCmd();
        else if (command == 'R')
            /* Remove um produto de uma encomenda. */
            removeProdFromPackCmd();
        else if (command == 'C')
            /* Calcula o custo de uma encomenda. */
            calcPackagePriceCmd();
        else if (command == 'p')
            /* Altera o preco de um produto existente no sistema. */
            changePriceCmd();
        else if (command == 'E')
            /* Retorna a descricao e a quantidade de um produto numa dada
               encomenda. */
            returnProdInfoCmd();
        else if (command == 'm')
            /* Retorna o identificador da encomenda em que um dado produto
               ocorre mais vezes. */
            biggestOccurrenceCmd();
        else if (command == 'l')
            /* Lista todos os produtos existentes no sistema por ordem
               crescente de preco. */
            listAllProductsCmd();
        else if (command == 'L')
            /* Lista todos os produtos de uma encomenda por ordem alfabetica da
               descricao */
            listPackageProdsCmd();
        else if (command == 'k')
            /* Lista todos os produtos existentes no sistema por ordem
               crescente de identificador. */
            listAllProductsIDCmd();
        else if (command == 'K')
            /* Lista todos os produtos de uma encomenda por ordem de
               insercao. */
            listPackageProdsIDCmd();
        else if (command == 'x')
            /* Termina o programa. */
            return 0;
        else if (command != '\n')
            /* Mensagem de erro para efeitos de depurracao. */
            printf("Comando inexistante! ('%c')\n", command);

        /* Ignorar o restante de uma linha caso um comando nao tenha processado
           esta completamente. Isto apenas eh util para efeitos de
           depurracao. */
        while (command != EOF && command != '\n')
            command = getchar();

        command = getchar();
    }

    return 0;
}
