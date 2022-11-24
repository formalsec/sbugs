#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdbool.h>
#define DESCMAX 63
#define PRODMAX 10000
#define ENCMAX 500

typedef struct Produto
{
  /* Estrutura Produto: celula basica do programa */
  char descricao[DESCMAX];
  int idp, preco, peso, stock;
}PRODUTO;

typedef struct Encomenda
{
  /* Estrutura Encomenda: Conjunto de produtos */
  PRODUTO prods[PRODMAX];
  int ide, len_prods, peso_total;
}ENCOMENDA;

typedef struct Sistema
{
  /* Estrutura Sistema: Estrutura que armazena todos os produtos em stock e encomendas */
  PRODUTO conteudo[PRODMAX];
  ENCOMENDA compras[ENCMAX];
  int len_produtos;
  int len_encomendas;
}SISTEMA;

/* inicializacao do sistema, variavel global */
SISTEMA sistema = {0};


/*================================================
==================================================*/
PRODUTO aux[PRODMAX];

bool lessPreco(PRODUTO a, PRODUTO b)
{
  /* Predicado usado para ordenar produtos pelo preco em ordem numerica crescente */
  if (a.preco < b.preco) return true;
  else return false;
}


bool lessDescricao(PRODUTO a, PRODUTO b)
{
  /* Predicado usado para ordenar produtos pela ordem alfabetica da sua descricao */
  if (a.descricao[0] < b.descricao[0]) return true;
  else return false;
}




void mergePROD(PRODUTO a[], int left, int m, int right, bool (*teste)(PRODUTO a, PRODUTO b))
{ 

	int i, j, k;
	for (i = m+1; i > left; i--)
		aux[i-1] = a[i-1];

	for (j = m; j < right; j++)
		aux[right+m-j] = a[j+1];

	for (k = left; k <= right; k++)

		if ( teste(aux[j], aux[i]) || i > m)
			a[k] = aux[j--];

		else
			a[k] = aux[i++];

}


void mergesortPROD(PRODUTO a[],int left, int right,bool (*teste)(PRODUTO a, PRODUTO b))
{

	int m = (right+left)/2;

	if (right <= left) 	return;
	mergesortPROD(a, left, m, teste);
	mergesortPROD(a, m+1, right, teste);
	mergePROD(a, left, m, right, teste);

}




/*================================================
==================================================*/


void listaEncomenda()
{
  int ide, i;
  scanf(" %d", &ide); /* Entrada -> ide */
  printf("Encomenda %d\n", ide);
  /* Escreve no terminal a descricao, o preco e o stock de cada produto na encomenda <ide> */
  for (i = 0; i < sistema.compras[ide].len_prods; i++)
  {
    PRODUTO prod = sistema.compras[ide].prods[i];
    printf("* %s %d %d\n", prod.descricao, prod.preco, prod.stock);
  }
}


void adicionaProduto()
{
  /* Adiciona uma estrutura Produto ah estrutura global sistema */
  PRODUTO prod;
  scanf(" %[^:]:%d:%d:%d", prod.descricao, &prod.preco, &prod.peso, &prod.stock);
  /* id do produto vai ser igual ah quantidade de produtos ja existentes */
  prod.idp = sistema.len_produtos;
  printf("Novo produto %d.\n", sistema.len_produtos);
  /* Incrementar a variavel que controla a quantidade de produtos no sistema */
  sistema.conteudo[sistema.len_produtos++] = prod;
}


void alteraStock(char op, int idp, int qntd)
{
  /* Erro: id produto invalido */
  if (idp < 0 || idp > sistema.len_produtos - 1)
  {
    switch (op)
    {
      case '+':
          printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
          break;
      case '-':
          printf("Impossivel remover produto %d ao stock. Produto inexistente.\n", idp);
          break;
    }
    return;
  }
  switch (op)
  {
    /* O argumento <op> determina se estamos a incrementar ou decrementar <qntd> ao stock */
    case '+':
        sistema.conteudo[idp].stock += qntd;
        break;
    
    case '-':
        /* Erro: quantidade de stock a returar eh superior ao stock disponivel */
        if (qntd > sistema.conteudo[idp].stock)
        {
          printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qntd, idp);
          return;
        }
        sistema.conteudo[idp].stock -= qntd;
  }
}


void alteraPreco()
{
  int idp, preco;
  scanf(" %d:%d", &idp, &preco); /* Entrada ->  idp:preco */
  /* Erro: id produto invalido */
  if (idp < 0 || idp > sistema.len_produtos - 1)
  {
    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    return;
  }
  sistema.conteudo[idp].preco = preco;
}


void listaProdutos()
{
  int i;
  for (i = 0; i < sistema.len_produtos; i++)
  {
    PRODUTO prod = sistema.conteudo[i];
    printf("* %s %d %d", prod.descricao, prod.preco, prod.stock);
  }
}


void novaEncomenda()
{
  /* Adiciona uma estrutura Encomenda ah estrutura global sistema */
  ENCOMENDA nova = {0};
  sistema.compras[sistema.len_encomendas] = nova;
  printf("Nova encomenda %d.\n",sistema.len_encomendas++);
}


void adicionaProdutoEncomenda()
{
  int i, ide, idp, qntd;
  bool novo = true;
  scanf(" %d:%d:%d", &ide, &idp, &qntd); /* Entrada ->  ide:idp:qntd */

  /* Erro: id encomenda invalido */ 
  if (ide < 0 || ide > sistema.len_encomendas - 1) 
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  /* Erro: id produto invalido */
  if (idp < 0 || idp > sistema.len_produtos - 1)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  /* Erro: n?o existe quantidade suficiente em stock */
  if (qntd > sistema.conteudo[idp].stock)
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    return;
  }
  /* Erro: Excedeu o limite de 200 de peso */
  if (sistema.conteudo[idp].peso * qntd + sistema.compras[ide].peso_total > 200) 
  {
    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    return;
  }
  /* Verifica se o produto <idp> est? na encomenda <ide> */
  for (i = 0; i < sistema.compras[ide].len_prods; i++)
  {
    if (sistema.compras[ide].prods[i].idp == idp)
    {
      /* Produto <idp> ja se encontra na encomenda <ide> */
      novo = false;
      /* Incrementa quantidade do produto <idp> na encomenda <ide> */
      sistema.compras[ide].prods[i].stock += qntd;
    }
  }
  /* Adiciona o produto <idp> ao fim da lista da encomenda <ide> caso este nao se encontre na encomenda. */
  if (novo)
  {
    sistema.compras[ide].prods[sistema.compras[ide].len_prods] = sistema.conteudo[idp];
    /* Corrige o stock do produto <idp> para <qntd> */
    sistema.compras[ide].prods[sistema.compras[ide].len_prods].stock = qntd;
    /* Incrementa o numero de produtos na encomenda <ide> */
    sistema.compras[ide].len_prods++;
  }
  /* Incrementa o peso do produto <idp> ao peso total da encomenda <ide> */
  sistema.compras[ide].peso_total += sistema.conteudo[idp].peso * qntd;
  /* Depois de adicionado a encomeda <ide>, decrementa <qntd> ao stock de <idp> */
  alteraStock('-', idp, qntd);
}


void removeProdutoEncomenda()
{
  int i, j, ide, idp;
  scanf(" %d:%d", &ide, &idp); /* Entrada -> ide:idp */
  /* Erro: id encomenda invalido */
  if (ide < 0 || ide > sistema.len_encomendas - 1)
  {
    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    return;
  }
  /* Erro: id produto invalido */
  if (idp < 0 || idp > sistema.len_produtos - 1)
  {
    printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    return;
  }
  /* Procurar o indice do produto <idp> na encomenda <ide> */
  for (i = 0; i < sistema.compras[ide].len_prods; i++)
  {
    if (sistema.compras[ide].prods[i].idp == idp)
    {
      for (j = i; j < sistema.compras[ide].len_prods; j++)
      {
        /* A partir do indice j, os elementos ser?o igual ao elemento j + 1, assim removendo
          o elemento de indice j do vetor */
        sistema.compras[ide].prods[j] = sistema.compras[ide].prods[j + 1];
      }
      sistema.compras[ide].len_prods--;
      return;
    }
  }
}


void infoProduto()
{
  int i, ide, idp;
  scanf(" %d:%d", &ide, &idp); /* Entrada -> ide:idp */
  /* Erro: id encomenda invalido */
  if (ide < 0 || ide > sistema.len_encomendas - 1)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  /* Erro: id produto invalido */
  if (idp < 0 || idp > sistema.len_produtos - 1)
  {
    printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    return;
  }
  /* Encontrar indice do produto <idp> na encomenda <ide> */
  for (i = 0; i < sistema.compras[ide].len_prods; i++)
  {
    if (sistema.compras[ide].prods[i].idp == idp)
    {
      printf("%s %d\n", sistema.compras[ide].prods[i].descricao, sistema.compras[ide].prods[i].stock);
      /* Atencao: o stock do produto difere do sistema para a encomenda */
    }
  }
}


void calculaPreco()
{
  int i, ide, total;
  scanf(" %d", &ide); /* Entrada -> ide */
  /* Erro: id encomenda invalido */
  if (ide < 0 || ide > sistema.len_encomendas - 1)
  {
    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  /* Cicla pelos produtos da encomenda <ide> e soma o seu preco para calcular o preco total */
  for (i = 0, total = 0; i < sistema.compras[ide].len_prods; i++)
  {
    total += sistema.compras[ide].prods[i].preco * sistema.compras[ide].prods[i].stock;
  }
  printf("Custo da encomenda %d %d.\n", ide, total);
}


void maxProduto()
{
  int i, j, max, idp, ide;
  bool encontrou = false;
  scanf(" %d", &idp); /* Entrada -> idp */
  /* Erro: id produto invalido */
  if (idp < 0 || idp > sistema.len_produtos - 1)
  {
    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
  }
  /* Cicla pelas encomendas existentes */
  for (i = 0, max = 0; i < sistema.len_encomendas; i++)
  {
    /* Cicla pelos produtos em cada encomenda e procura pelo produto <idp> */
    for (j = 0; j < sistema.compras[i].len_prods; j++)
    {
      if (sistema.compras[i].prods[j].idp == idp)
      {
        /* Compara o stock do produto <idp> ao max */
        if (sistema.compras[i].prods[j].stock > max)
        {
          max = sistema.compras[i].prods[j].stock;
          ide = i;
          encontrou = true;
        }
      }
    }
  }
  /* Escreve no terminal o maximo produto apenas se este existir */
  if (encontrou) printf("Maximo produto %d %d %d.\n", idp, ide, max);
}


void ordenaProdutos()
{
  int i, len = sistema.len_produtos;
  PRODUTO prods[PRODMAX];
  /* Criar vetor com os produtos existentes */
  for (i = 0; i < len; i++) prods[i] = sistema.conteudo[i];
  /* Ordenar o vetor com recurso a mergesort segundo a ordem numerica crescente do preco */
  mergesortPROD(prods, 0, len - 1, lessPreco);
  /* Escrever a descricao, preco e stock dos produtos */
  printf("Produtos\n");
  for (i = 0; i < len; i++)
  {
    printf("* %s %d %d\n", prods[i].descricao, prods[i].preco, prods[i].stock);
  }
}


void ordenaEncomenda()
{
  PRODUTO prods[PRODMAX];
  int i, ide, len;
  scanf(" %d", &ide); /* Entrada: ide */
  /* Erro: id encomenda invalido */
  if (ide < 0 || ide > sistema.len_encomendas - 1)
  {
    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    return;
  }
  len = sistema.compras[ide].len_prods;
  
  /* Criar vetor com os produtos da encomenda <ide> */
  for (i = 0; i < len; i++) prods[i] = sistema.compras[ide].prods[i];
  /* Ordenar o vetor com recurso a mergesort segundo a ordem crescente alfabetica da descricao */
  mergesortPROD(prods, 0, len - 1, lessDescricao);
  /* Escrever a descricao, preco e stock dos produtos da encomenda <ide> */
  printf("Encomenda %d\n", ide);
  for (i = 0; i < len; i++)
  {
    printf("* %s %d %d\n", prods[i].descricao, prods[i].preco, prods[i].stock);
  }
}


/*================================================
==================================================*/


int main()
{
  char c;
  int i1, i2;
  while (true) /* Loop principal */
  {
    c = getchar();
    switch (c)
    {
      case 'a':
      /* a: adiciona um novo produto ao sistema */
          adicionaProduto();
          break;
      case 'q':
      /* q: incrementa a quantidade de um produto existente no sistema */
          scanf(" %d:%d", &i1, &i2); /* Entrada -> idp:qntd */
          alteraStock('+', i1, i2);
          break;
    
      case 'r':
      /* r: decrementa a quantidade de um produto existente no sistema */
          scanf(" %d:%d", &i1, &i2);
          alteraStock('-', i1, i2);
          break;

      case 'p':
      /* p: altera o preco de um produto existente no sistema */
          alteraPreco();
          break;

      case 'k':
      /* k: escreve no terminal todos os produtos, com descricao, preco e stock */
          listaProdutos();
          break;

      case 'N':
      /* N: cria uma nova encomenda */
          novaEncomenda();
          break;

      case 'A':
      /* A: adiciona um produto a uma encomenda */
          adicionaProdutoEncomenda();
          break;

      case 'R':
      /* R: remove um produto a uma encomenda */
          removeProdutoEncomenda();
          break;

      case 'K':
      /* K: escreve no terminal todos os produtos de uma encomenda */
          listaEncomenda();
          break;

      case 'E':
      /* E: escreve no terminal informacao sobre um produto de uma Encomenda */
          infoProduto();
          break;

      case 'C':
      /* C: calcula o custo total de uma encomenda */
          calculaPreco();
          break;

      case 'm':
      /* m: devolve o id da encomenda onde certo produto encontra-se em maior quantidade */
          maxProduto();
          break;

      case 'l':
      /* l: lista os produtos existentes no sistema por ordem crescente de preco */
          ordenaProdutos();
          break;

      case 'L':
      /* L: lista os produtos de uma encomenda por ordem alfabetica de descricao */
          ordenaEncomenda();
          break;
            
      case 'x':
      /* x: interrompe o loop principal, terminando o programa */
          return 0;

      c = getchar(); /* char '\n' */
    }
  }
}
