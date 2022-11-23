#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "produtos.h"
#include "constants.h"
#include "logisticae.h"
#include <stdio.h>
#include <stdlib.h>

void open_files(int argc, char const *argv[]);

/*
Read value from the input file and treat the commands in the Logistics structure
*/
int main(int argc, char const *argv[]) {
  Logistics *logs = createLog();
  int runer = 0;
  char c;
  char string[MAX_DESCRIPTION_SIZE];
  open_files(argc, argv);
  while (runer == 0 && c != EOF) {
    switch (c = fgetc(inputFile)) {
      /*
      *__a__ - adiciona um novo produto ao sistema
      * Formato de entrada: `a descricao:preco:peso:qtd`
      * Formato de sa?da: `Novo produto <idp>.` onde `<idp>` ? o identificador do produto criado.
      */
      case 'a':
        fscanf(inputFile, "%s", string);
        addProd(logs,string);
        break;
      /*
      * __q__ - adiciona stock a um produto existente no sistema
        * Formato de entrada: `q idp:qtd`
        * Formato de sa?da: NADA (excepto erro)
        * Erros:
          * `Impossivel adicionar produto <idp> ao stock. Produto inexistente.`
            ->No caso de n?o existir nenhum produto criado com esse identificador
      */
      case 'q':
        fscanf(inputFile, "%s", string);
        addProdStock(logs, string);
        break;
      /*
      * __N__ - cria uma nova encomenda
        * Formato de entrada: `N`
        * Formato de sa?da: `Nova encomenda <ide>.` onde `<ide>` ? o identificador da encomenda criada.
      */
      case 'N':
        addEncomenda(logs);
        break;
      /*
      * __A__ - adiciona um produto a uma encomenda. Se o produto j? existir na encomenda,
        adiciona a nova quantidade ? quantidade existente
        * Formato de entrada: `A ide:idp:qtd`
        * Formato de sa?da: NADA (excepto erro)
        * Erros:
          * `Impossivel adicionar produto <idp> a encomenda <ide>. Encomenda inexistente.`
            ->No caso de n?o existir nenhuma encomenda criada com esse identificador
          * `Impossivel adicionar produto <idp> a encomenda <ide>. Produto inexistente.`
            ->No caso de n?o existir nenhum produto criado com esse identificador
          * `Impossivel adicionar produto <idp> a encomenda <ide>. Quantidade em stock insuficiente.`
            ->No caso de n?o existir stock suficiente desse produto para satisfazer a encomenda
          * `Impossivel adicionar produto <idp> a encomenda <ide>. Peso da encomenda excede o
            maximo de 200.`
            ->No caso de a adi??o desse produto exceder o peso m?ximo permitido por encomenda
      */
      case 'A':
        fscanf(inputFile, "%s", string);
        addProdInEnc(logs, string);
        break;
      /*
      * __r__ - remove stock a um produto existente
        * Formato de entrada: `r idp:qtd`
        * Formato de sa?da: NADA (excepto erro)
        * Erros:
          * `Impossivel remover stock do produto <idp>. Produto inexistente.`
            ->No caso de n?o existir nenhum produto criado com esse identificador
          * `Impossivel remover <qtd> unidades do produto <idp> do stock. Quantidade insuficiente.`
            ->No caso de a quantidade de stock restante ap?s a remo??o ser negativa ou ser insuficiente
              para satisfazer as encomendas existentes
      */
      case 'r':
        fscanf(inputFile, "%s", string);
        removeProdStock(logs, string);
        break;
      /*
      * __R__ - remove um produto de uma encomenda
        * Formato de entrada: `R ide:idp`
        * Formato de sa?da: NADA (excepto erro)
        * Erros:
          * `Impossivel remover produto <idp> a encomenda <ide>. Encomenda inexistente.`
            ->No caso de n?o existir nenhuma encomenda criada com esse identificador
          * `Impossivel remover produto <idp> a encomenda <ide>. Produto inexistente.`
            ->No caso de n?o existir nenhum produto criado com esse identificador

      */
      case 'R':
        fscanf(inputFile, "%s", string);
        removeProdInEnc(logs,string);
        break;
      /*
      * __C__ - calcula o custo de uma encomenda
        * Formato de entrada: `C ide`
        * Formato de sa?da: `Custo da encomenda <ide> <total>.` onde `<total>`
         ? o valor total da encomenda `<ide>`
        * Erros:
          * `Impossivel calcular custo da encomenda <ide>. Encomenda inexistente.`
            ->No caso de n?o existir nenhuma encomenda criada com esse identificador
          */
      case 'C':
        fscanf(inputFile, "%s", string);
        getPriceForEnc(logs, string);
        break;
      /*
      * __p__ - altera o pre?o de um produto existente no sistema
        * Formato de entrada: `p idp:preco`
        * Formato de sa?da: NADA (excepto erro)
        * Erros:
          * `Impossivel alterar preco do produto <idp>. Produto inexistente.`
            ->No caso de n?o existir nenhum produto criado com esse identificador
      */
      case 'p':
        fscanf(inputFile, "%s", string);
        changeProdPrice(logs, string);
        break;
      /*
      * __E__ - lista a descri??o e a quantidade de um produto numa encomenda
        * Formato de entrada: `E ide:idp`
        * Formato de sa?da: `<desc> <qtd>.` onde `<desc>` ? a descri??o do produto `<idp>` e `<qtd>`
         ? a quantidade desse produto na encomenda `<ide>`
        * Erros:
          * `Impossivel listar encomenda <ide>. Encomenda inexistente.`
            ->No caso de n?o existir nenhuma encomenda criada com esse identificador
          * `Impossivel listar produto <idp>. Produto inexistente.`
            ->No caso de n?o existir nenhum produto criado com esse identificador
      */
      case 'E':
        fscanf(inputFile, "%s", string);
        printProdInEnc(logs, string);
        break;

      /*
      * __m__ - lista o identificador da encomenda em que o produto dado ocorre mais vezes.
      Se houver 2 ou mais encomendas nessa situa??o, dever? imprimir a encomenda de menor `id`.
        * Formato de entrada: `m idp`
        * Formato de sa?da:
          * `Maximo produto <idp> <ide> <qtd>.` onde `<ide>`
            ? o n?mero da encomenda em que `<idp>` ocorre mais vezes, sendo essa quantidade `<qtd>`
          * N?o dever? listar nada caso o produto `<idp>` n?o ocorra em nenhuma encomenda,
           ou caso n?o haja encomendas
        * Erros:
          * `Impossivel listar maximo do produto <idp>. Produto inexistente.`
           ->No caso de n?o existir nenhum produto criado com esse identificador
      */
      case 'm':
        fscanf(inputFile, "%s", string);
        mostFrequentProd(logs, string);
        break;
      /*
      * __l__ - lista todos os produtos existentes no sistema por ordem crescente de pre?o.
       Se houver 2 ou mais produtos com o mesmo pre?o, dever? imprimir esses por ordem crescente de `id` de produto
        * Formato de entrada: `l`
        * Formato de sa?da: Um bloco no formato abaixo, e em que os produtos s?o listados
         por ordem crescente de pre?o

              Produtos
              * <desc1> <preco1> <qtd1 em stock>
              * <desc2> <preco2> <qtd2 em stock>
              ...
              * <descn> <precon> <qtdn em stock>
        * Erros: N?o aplic?vel
      */
      case 'l':
        printOrdProd(logs);
        break;
      /*
      * __L__ - lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o
        * Formato de entrada: `L <ide>`
        * Formato de sa?da: Um bloco no formato abaixo,
         e em que os produtos s?o listados por ordem alfab?tica de descri??o

              Encomenda <ide>
              * <desc1> <preco1> <qtd1 na ide>
              * <desc2> <preco2> <qtd2 na ide>
              ...
              * <descn> <precon> <qtdn na ide>
        * Erros:
          * `Impossivel listar encomenda <ide>. Encomenda inexistente.`
            ->No caso de n?o existir nenhuma encomenda criada com esse identificador
          */
      case 'L':
        fscanf(inputFile, "%s", string);
        printEncProds(logs, string);
        break;
      /*
      * __x__ - termina o programa
        * Formato de entrada: `x`
        * Formato de sa?da: NADA
      */
      case 'x':
        runer = 1;
    }
  }
  fclose(outputFile);
  fclose(inputFile);
  freeLogistics(logs);
  return 0;
}

/*
If there is an input and output file used as argument, initialise them here, otherwise,
inicialise the input as stdin and the output as stdout
*/

void open_files(int argc, char const *argv[]){
  if(argc == 3){
    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");
  }
  else{
    inputFile = stdin;
    outputFile = stdout;
  }
  if(!inputFile || !outputFile){
    perror("Couldn't open files");
    exit(EXIT_FAILURE);
  }
}
