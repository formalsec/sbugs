#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Numero maximo de produtos no sistema */
#define MAX_PRODUTOS 10000
/* Numero maximo de encomendas no sistema */
#define MAX_ENCOMENDAS 500
/* Numero maximo de caracteres na descricao de produtos */
#define MAX_DESC 63
/* Peso maximo em cada encomenda */
#define MAX_PESO 200
/* Numero maximo de caracteres para o comando */
#define MAX_CMD 100

/* Contador para atribuicao de IDs a novos produtos */
int CURRENT_IDP = 0;
/* Contador para atribuicao de IDs a novas encomendas */
int CURRENT_IDE = 0;

/* Estrutura para produtos */
typedef struct {
  int idp;
  char desc[MAX_DESC];
  int preco;
  int peso;
  int qtd;
} Produto;

/* Estrutura para encomendas
 * (guarda os produtos encomendados numa
 * lista de pares (idp,qtd encomendada)) */
typedef struct {
  int ide;
  int peso;
  int nprodutos;
  int produtos[MAX_PESO][2];
} Encomenda;

/* compara o preco de dois produtos, retornando 1 se o preco de p1 for
 * inferior ao de p2, ou se os precos forem iguais e o idp de p1 for
 * inferior ao de p2. retorna 0 caso contrario */
int less_price(Produto p1, Produto p2);

/* compara a descricao de dois produtos, retornando 1 se a descricao de p1
 * anteceder alfabeticamente a de p2, ou se as descricoes forem identicas e
 * o idp de p1 for inferior ao de p2. retorna 0 caso contrario */
int less_abc(Produto p1, Produto p2);

/* troca p1 por p2 (e p2 por p1) */
void exch(Produto *p1, Produto *p2);

/* funcao partition para implementacao do quicksort, utilizando como pivot a
 * posicao cujo valor corresponde a mediana dos valores de 3 posicoes
 * (posicao mais a esquerda, centro e posicao mais a direita) */
int partition(Produto produto[], int left, int right, char method);

/* funcao que implementa o quicksort */
void quicksort(Produto produto[], int left, int right, char method);

/* copia uma lista de produtos (que nao se quer alterar) para outra,
 * permitindo, assim, a manipulacao do conteudo */
void copiarProdutos(Produto dest[], Produto src[]);

/* copia para uma nova lista de produtos, os produtos cujo idp esta guardado
 * na encomenda enc_src, substituindo qtd em stock por qtd encomendada */
void copiarProdutosfromEncomenda(Produto dest[], Encomenda enc_src, Produto prod_src[]);

/* imprime os produtos guardados numa lista de produtos */
void imprimirProdutos(Produto produtos[], int size);

/* procura numa encomenda se tem encomendado um produto idp. retorna
 * a posicao que esse produto ocupa na lista de idps dessa encomenda.
 * se nao encontrar, retorna -1 */
int procuraProduto_Encomenda(int idp, Encomenda enc);

/* da "parse" do comando e cria um novo produto (comando 'a') */
void novoProduto(char *command, Produto produtos[]);

/* da "parse" do comando e adiciona unidades ao stock
 * de um produto ja existente (comando 'q') */
void adicionarStock(char *command, Produto produtos[]);

/* cria um nova encomenda (comando 'N') */
void novaEncomenda(Encomenda encomendas[]);

/* da "parse" do comando e adiciona o idp e qtd encomendada de um produto
 * a lista na encomenda correspondente (comando 'A') */
void encomendarProduto(char *command, Produto produtos[], Encomenda encomendas[]);

/* da "parse" do comando e remove unidades ao stock
 * de um produto ja existente (comando 'r') */
void removerStock(char *command, Produto produtos[]);

/* da "parse" do comando e remove o produto da lista de produtos
 * de uma encomenda - remove o par(idp,qtd) (comando 'R') */
void removerProdutoDeEncomenda(char *command, Produto produtos[], Encomenda encomendas[]);

/* da "parse" do comando e calcula o custo total de uma encomenda (comando 'C') */
void calcularCustoEncomenda(char *command, Produto produtos[], Encomenda encomendas[]);

/* da "parse" do comando e altera o preco de um produto (comando 'p') */
void alterarPreco(char *command, Produto produtos[]);

/* da "parse" do comando e imprime produto numa encomenda, assim como
 * a quantidade encomendada (comando 'E') */
void listarProdutoEmEncomenda(char *command, Produto produtos[], Encomenda encomendas[]);

/* da "parse" do comando e imprime o ide da encomenda em que o produto
 * ocorre mais vezes, assim como a quantidade encomendada (comando 'm') */
void listarEncomendaComProdutoMax(char *command, Encomenda encomendas[]);

/* copia a lista de produtos no sistema, ordena-a por ordem crescente
 * de preco com o quicksort e imprime (comando 'l') */
void listarProdutosPorPreco(Produto produtos[]);

/* da "parse" do comando, copia os produtos cujo idp consta da lista de
 * produtos (par idp,qtd) na encomenda, ordena-a alfabeticamente
 * com o quicksort e imprime (comando 'L') */
void listarProdutosEmEncomendaPorABC(char *command, Produto produtos[], Encomenda encomendas[]);

/* recebe comandos do stdin, determina a partir do primeiro caracter a operacao
 * a efectuar e chama a funcao correspondente */
int main() {

  Produto produtos[MAX_PRODUTOS];
  Encomenda encomendas[MAX_ENCOMENDAS];
  char command[MAX_CMD];

  while(1) {
    fgets(command, MAX_CMD, stdin);
    switch(command[0]) {
      case 'a':
        novoProduto(command, produtos);
        break;
      case 'q':
        adicionarStock(command, produtos);
        break;
      case 'N':
        novaEncomenda(encomendas);
        break;
      case 'A':
        encomendarProduto(command, produtos, encomendas);
        break;
      case 'r':
        removerStock(command, produtos);
        break;
      case 'R':
        removerProdutoDeEncomenda(command, produtos, encomendas);
        break;
      case 'C':
        calcularCustoEncomenda(command, produtos, encomendas);
        break;
      case 'p':
        alterarPreco(command, produtos);
        break;
      case 'E':
        listarProdutoEmEncomenda(command, produtos, encomendas);
        break;
      case 'm':
        listarEncomendaComProdutoMax(command, encomendas);
        break;
      case 'l':
        listarProdutosPorPreco(produtos);
        break;
      case 'L':
        listarProdutosEmEncomendaPorABC(command, produtos, encomendas);
        break;
      case 'x':
        return EXIT_SUCCESS;
      default:
        printf("ERROR: Unknown command\n");
    }
  }

  return EXIT_FAILURE;
}

/* Implementacoes de funcoes */

int less_price(Produto p1, Produto p2) {
  int res = p1.preco - p2.preco;
  if(res < 0 || (res == 0 && p1.idp < p2.idp)) {
    return 1;
  }
  else {
    return 0;
  }
}

int less_abc(Produto p1, Produto p2) {
  int res = strcmp(p1.desc, p2.desc);
  if(res < 0 || (res == 0 && p1.idp < p2.idp)) {
    return 1;
  }
  else {
    return 0;
  }
}

void exch(Produto *p1, Produto *p2) {
  Produto ptemp;
  ptemp = *p1;
  *p1 = *p2;
  *p2 = ptemp;
}

int partition(Produto produtos[], int left, int right, char method) {
  int i = (left - 1);
  int j = right;
  Produto p1 = produtos[left];
  Produto p2 = produtos[(right-left)/2+left];
  Produto p3 = produtos[right-1];
  switch(method) {
    case 'l':
      if((less_price(p1, p2) && less_price(p2, p3)) || (less_price(p3, p2) && less_price(p2, p1))) {
        p1 = p2;
      }
      else if((less_price(p1, p3) && less_price(p3, p2)) || (less_price(p2, p3) && less_price(p3, p1))) {
        p1 = p3;
      }
      while(1) {
        j--;
        while(less_price(p1, produtos[j])) {
          j--;
        }
        i++;
        while(less_price(produtos[i], p1)) {
          i++;
        }
        if(i < j) {
          exch(&produtos[i], &produtos[j]);
        }
        else {
          return j + 1;
        }
      }
      break;
    case 'L':
      if((less_abc(p1, p2) && less_abc(p2, p3)) || (less_abc(p3, p2) && less_abc(p2, p1))) {
        p1 = p2;
      }
      else if((less_abc(p1, p3) && less_abc(p3, p2)) || (less_abc(p2, p3) && less_abc(p3, p1))) {
        p1 = p3;
      }
      while(1) {
        j--;
        while(less_abc(p1, produtos[j])) {
          j--;
        }
        i++;
        while(less_abc(produtos[i], p1)) {
          i++;
        }
        if(i < j) {
          exch(&produtos[i], &produtos[j]);
        }
        else {
          return j + 1;
        }
      }
      break;
    default:
      break;
  }
  return -1;
}


void quicksort(Produto produtos[], int left, int right, char method) {
  if (left < right - 1) {
    int i = partition(produtos, left, right, method);
    quicksort(produtos, left, i, method);
    quicksort(produtos, i, right, method);
  }
}

void copiarProdutos(Produto dest[], Produto src[]) {
  int i;
  for(i = 0; i < CURRENT_IDP; i++) {
    dest[i] = src[i];
  }
}

void copiarProdutosDeEncomenda(Produto dest[], Encomenda enc_src, Produto prod_src[]) {
  int i;
  int n = enc_src.nprodutos;
  for(i = 0; i < n; i++) {
    dest[i] = prod_src[enc_src.produtos[i][0]];
    dest[i].qtd = enc_src.produtos[i][1];
  }
}

void imprimirProdutos(Produto produtos[], int size) {
  int i;
  for(i = 0; i < size; i++) {
    printf("* %s %d %d\n", produtos[i].desc, produtos[i].preco, produtos[i].qtd);
  }
}

int procuraProduto_Encomenda(int idp, Encomenda enc) {
  int i;
  for(i = 0; i < enc.nprodutos; i++) {
    if(enc.produtos[i][0] == idp) {
      return i;
    }
  }
  return -1;
}

void novoProduto(char *command, Produto produtos[]) {
  int idp, preco, peso, qtd;
  char *token, *desc;

  token = strtok(command, " ");
  idp = CURRENT_IDP;
  desc = token = strtok(NULL, ":");
  preco = atoi(token = strtok(NULL, ":"));
  peso = atoi(token = strtok(NULL, ":"));
  qtd = atoi(token = strtok(NULL, "\n"));
  produtos[idp].idp = idp;
  strcpy(produtos[idp].desc, desc);
  produtos[idp].preco = preco;
  produtos[idp].peso = peso;
  produtos[idp].qtd = qtd;
  CURRENT_IDP++;
  printf("Novo produto %d.\n", idp);
}

void adicionarStock(char *command, Produto produtos[]) {
  int idp, qtd;
  char *token;

  token = strtok(command, " ");
  idp = atoi(token = strtok(NULL, ":"));
  if(idp >= CURRENT_IDP) {
    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    return;
  }
  qtd = atoi(token = strtok(NULL, "\n"));
  produtos[idp].qtd += qtd;
}

void novaEncomenda(Encomenda encomendas[]) {
  int ide;

  ide = CURRENT_IDE;
  encomendas[ide].ide = ide;
  encomendas[ide].peso = 0;
  encomendas[ide].nprodutos = 0;
  CURRENT_IDE++;
  printf("Nova encomenda %d.\n", ide);
}

void encomendarProduto(char *command, Produto produtos[], Encomenda encomendas[]) {
  int ide, idp, qtd;
  int id, n;
  char *token;

  token = strtok(command, " ");
  ide = atoi(token = strtok(NULL, ":"));
  idp = atoi(token = strtok(NULL, ":"));
  if(ide >= CURRENT_IDE) {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  if(idp >= CURRENT_IDP) {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  qtd = atoi(token = strtok(NULL, "\n"));
  if(qtd - produtos[idp].qtd > 0) {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    return;
  }
  if(encomendas[ide].peso + qtd * produtos[idp].peso > MAX_PESO) {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    return;
  }
  id = procuraProduto_Encomenda(idp, encomendas[ide]);
  if(id != -1) {
    encomendas[ide].produtos[id][1] += qtd;
  }
  else {
    n = encomendas[ide].nprodutos++;
    encomendas[ide].produtos[n][0] = idp;
    encomendas[ide].produtos[n][1] = qtd;
  }
  encomendas[ide].peso += qtd * produtos[idp].peso;
  produtos[idp].qtd -= qtd;
}

void removerStock(char *command, Produto produtos[]) {
  int idp, qtd;
  char *token;

  token = strtok(command, " ");
  idp = atoi(token = strtok(NULL, ":"));
  if(idp >= CURRENT_IDP) {
    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    return;
  }
  qtd = atoi(token = strtok(NULL, "\n"));
  if(qtd - produtos[idp].qtd > 0) {
    printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    return;
  }
  produtos[idp].qtd -= qtd;
}

void removerProdutoDeEncomenda(char *command, Produto produtos[], Encomenda encomendas[]) {
  int ide, idp;
  int id, qtd, i, n;
  char *token;

  token = strtok(command, " ");
  ide = atoi(token = strtok(NULL, ":"));
  idp = atoi(token = strtok(NULL, "\n"));
  if(ide >= CURRENT_IDE) {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  if(idp >= CURRENT_IDP) {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  id = procuraProduto_Encomenda(idp, encomendas[ide]);
  if(id != -1) {
    qtd = encomendas[ide].produtos[id][1];
    encomendas[ide].peso -= qtd * produtos[idp].peso;
    produtos[idp].qtd += qtd;
    n = encomendas[ide].nprodutos--;
    for(i = id; i < n; i++) {
      encomendas[ide].produtos[i][0] = encomendas[ide].produtos[i+1][0];
      encomendas[ide].produtos[i][1] = encomendas[ide].produtos[i+1][1];
    }
  }
}

void calcularCustoEncomenda(char *command, Produto produtos[], Encomenda encomendas[]) {
  int ide;
  int i, n, total;
  char *token;

  token = strtok(command, " ");
  ide = atoi(token = strtok(NULL, "\n"));
  if(ide >= CURRENT_IDE) {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  total = 0;
  n = encomendas[ide].nprodutos;
  for(i = 0; i < n; i++) {
    total += encomendas[ide].produtos[i][1] * produtos[encomendas[ide].produtos[i][0]].preco;
  }
  printf("Custo da encomenda %d %d.\n", ide, total);
}

void alterarPreco(char *command, Produto produtos[]) {
  int idp, preco;
  char *token;

  token = strtok(command, " ");
  idp = atoi(token = strtok(NULL, ":"));
  if(idp >= CURRENT_IDP) {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    return;
  }
  preco = atoi(token = strtok(NULL, "\n"));
  produtos[idp].preco = preco;
}

void listarProdutoEmEncomenda(char *command, Produto produtos[], Encomenda encomendas[]) {
  int ide, idp;
  int id, qtd;
  char *token;

  token = strtok(command, " ");
  ide = atoi(token = strtok(NULL, ":"));
  if(ide >= CURRENT_IDE) {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  idp = atoi(token = strtok(NULL, ":"));
  if(idp >= CURRENT_IDP) {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    return;
  }
  id = procuraProduto_Encomenda(idp, encomendas[ide]);
  if(id != -1) {
    qtd = encomendas[ide].produtos[id][1];
  }
  else {
    qtd = 0;
  }
  printf("%s %d.\n", produtos[idp].desc, qtd);
}

void listarEncomendaComProdutoMax(char *command, Encomenda encomendas[]) {
  int idp;
  int max, max_ide, id, i;
  char *token;

  token = strtok(command, " ");
  idp = atoi(token = strtok(NULL, "\n"));
  if(idp >= CURRENT_IDP) {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    return;
  }
  if(CURRENT_IDE <= 0) {
    return;
  }
  max = 0;
  max_ide = -1;
  for(i = 0; i < CURRENT_IDE; i++) {
    id = procuraProduto_Encomenda(idp, encomendas[i]);
    if(id != -1 && encomendas[i].produtos[id][1] > max) {
      max = encomendas[i].produtos[id][1];
      max_ide = encomendas[i].ide;
    }
  }
  if(max_ide != -1) {
    printf("Maximo produto %d %d %d.\n", idp, max_ide, max);
  }
}

void listarProdutosPorPreco(Produto produtos[]) {
  Produto tempProdutos[MAX_PRODUTOS];

  copiarProdutos(tempProdutos, produtos);
  quicksort(tempProdutos, 0, CURRENT_IDP, 'l');
  printf("Produtos\n");
  imprimirProdutos(tempProdutos, CURRENT_IDP);
}

void listarProdutosEmEncomendaPorABC(char *command, Produto produtos[], Encomenda encomendas[]) {
  Produto tempProdutos[MAX_PRODUTOS];
  int ide;
  char *token;

  token = strtok(command, " ");
  ide = atoi(token = strtok(NULL, "\n"));
  if(ide >= CURRENT_IDE) {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  copiarProdutosDeEncomenda(tempProdutos, encomendas[ide], produtos);
  quicksort(tempProdutos, 0, encomendas[ide].nprodutos, 'L');
  printf("Encomenda %d\n", ide);
  imprimirProdutos(tempProdutos, encomendas[ide].nprodutos);
}
