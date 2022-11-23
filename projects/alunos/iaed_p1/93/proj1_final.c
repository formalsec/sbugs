#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>


/* Definicao de constantes */
#define PRODUTOS_MAX 10000
#define DESC_MAX 63
#define ENCOMENDAS_MAX 500
#define PESO_MAX 200


/* Definicao de estruturas */
typedef struct produto
{
    int idp;
    char descricao[DESC_MAX];
    int preco;
    int peso;
    int qtd;

}produto;

typedef struct encomenda
{
    int lista[PRODUTOS_MAX];

}encomenda;


/* Variaveis globais */
produto sistema[PRODUTOS_MAX];
encomenda encomendas[ENCOMENDAS_MAX];
produto copia[PRODUTOS_MAX];
produto aux[PRODUTOS_MAX];
int identificador_p = 0; /* Variavel que enumera o numero de produtos existentes */
int identificador_e = 0; /* Variavel que enumera o numero de encomendas existentes */


/* Funcao 'a' que adiciona um produto ao sistema.
   Formato de entrada: `a descricao:preco:peso:qtd`
   Formato de sa?da: `Novo produto <idp>.` onde `<idp>` ? o identificador do produto criado.
*/
void comando_a()
{
    if (identificador_p < PRODUTOS_MAX)
    {
        scanf(" %[^:]:%d:%d:%d", sistema[identificador_p].descricao, &sistema[identificador_p].preco, 
                                &sistema[identificador_p].peso, &sistema[identificador_p].qtd);

    
        sistema[identificador_p].idp = identificador_p; 
    
        printf("Novo produto %d.\n", identificador_p);

        identificador_p++;
    }
}


/* Funcao 'q' que adiciona stock a um produto existente no sistema.
   Formato de entrada: `q idp:qtd`
   Formato de sa?da: NADA (excepto erro) 
*/
void comando_q()
{
    int idp, quantidade;

    scanf(" %d:%d", &idp, &quantidade);

    if (idp >= identificador_p) /* Verificacao se o produto existe no sistema ou nao */
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }

    else
    {
        sistema[idp].qtd += quantidade;
    }
}


/* Funcao 'N' que cria uma nova encomenda.
   Formato de entrada: `N`
   Formato de sa?da: `Nova encomenda <ide>.` onde `<ide>` ? o identificador da encomenda criada.
*/
void comando_N()
{
    int n = 0;

    if (identificador_e < ENCOMENDAS_MAX)
    {
        while (n < PRODUTOS_MAX)
        {
            encomendas[identificador_e].lista[n] = 0;
            n++;
        } 

        printf("Nova encomenda %d.\n", identificador_e);

        identificador_e++;
    }
}


/* Funcao 'A' adiciona um produto a uma encomenda. Se o produto j? existir na encomenda, 
   adiciona a nova quantidade ? quantidade existente.
   Formato de entrada: `A ide:idp:qtd`
   Formato de sa?da: NADA (excepto erro) 
*/
void comando_A()
{
    int ide, idp, quantidade, peso = 0, n = 0;

    scanf(" %d:%d:%d", &ide, &idp, &quantidade);

    while (n < identificador_p) /* Calculo do peso */
    {
        peso = peso + (encomendas[ide].lista[n] * sistema[n].peso);
        n++;
    }
    
    if (ide >= identificador_e) /* Verificacao se a encomenda existe ou nao */
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }

    else if (idp >= identificador_p) /* Verificacao se o produto existe no sistema ou nao */
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }

    else if (quantidade > sistema[idp].qtd) /* Verificacao se a quantidade em stock ? suficiente ou nao */
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    }

    else if ((peso + (quantidade * sistema[idp].peso)) > PESO_MAX) /* Verificacao se o peso ? superior ao maximo */
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    }

    else
    {
        encomendas[ide].lista[idp] = encomendas[ide].lista[idp] + quantidade;
        sistema[idp].qtd = sistema[idp].qtd - quantidade;
    }
}


/* Funcao 'r' que remove stock a um produto existente.
   Formato de entrada: `r idp:qtd`
   Formato de sa?da: NADA (excepto erro)
*/
void comando_r()
{
    int idp, quantidade;

    scanf(" %d:%d", &idp, &quantidade);

    if (idp >= identificador_p) /* Verificacao se o produto existe no sistema ou nao */
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }

    else if (quantidade > sistema[idp].qtd) /* Verificacao se a quantidade que existe no sistema ? superior ? pretendida */
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
    }

    else
    {
        sistema[idp].qtd = sistema[idp].qtd - quantidade;
    }
}


/* Funcao 'R' que remove um produto da encomenda.
   Formato de entrada: `R ide:idp`
   Formato de sa?da: NADA (excepto erro)
*/
void comando_R()
{
    int ide, idp;

    scanf(" %d:%d", &ide, &idp);

    if (ide >= identificador_e) /* Verificacao se a encomenda existe ou nao */
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide); 
    }

    else if (idp >= identificador_p) /* Verificacao se o produto existe no sistema ou nao */
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }

    else
    {
        sistema[idp].qtd += encomendas[ide].lista[idp];
        encomendas[ide].lista[idp] = 0;
    }
}


/* Funcao 'C' que calcula o custo de uma encomenda.
   Formato de entrada: `C ide`
   Formato de sa?da: `Custo da encomenda <ide> <total>.` onde `<total>` ? o valor total da encomenda `<ide>`
*/
void comando_C()
{
    int ide, n=0, preco=0;

    scanf(" %d", &ide);

    if (ide >= identificador_e) /* Verificacao se a encomenda existe ou nao */
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }

    else
    {
        while (n < identificador_p)
        {
            if(encomendas[ide].lista[n]!=0)
            {
                preco = preco + (encomendas[ide].lista[n] * sistema[n].preco);
            }

            n++;
        }

        printf("Custo da encomenda %d %d.\n", ide, preco);
    }
}


/* Funcao 'p' que altera o preco de um produto existente no sistema. 
   Formato de entrada: `p idp:preco`
   Formato de sa?da: NADA (excepto erro)
*/
void comando_p()
{
    int idp, preco;

    scanf(" %d:%d", &idp, &preco);

    if (idp >= identificador_p) /* Verificacao se o produto existe no sistema ou nao */
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }

    else
    {
        sistema[idp].preco = preco;
    }
}


/* Funcao 'E' que lista a descricao e a quantidade de um produto numa encomenda. 
   Formato de entrada: `E ide:idp`
   Formato de sa?da: `<desc> <qtd>.` onde `<desc>` ? a descri??o do produto `<idp>`
   e `<qtd>` ? a quantidade desse produto na encomenda `<ide>`
*/
void comando_E()
{
    int ide, idp;

    scanf(" %d:%d", &ide, &idp);

    if (ide >= identificador_e) /* Verificacao se a encomenda existe ou nao */
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);    
    }

    else if (idp >= identificador_p) /* Verificacao se o produto existe no sistema ou nao */
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);  
    }

    else
    {
        printf("%s %d.\n", sistema[idp].descricao, encomendas[ide].lista[idp]);
    }
}


/* Funcao 'm' que lista o identificador da encomenda em que o produto dado ocorre mais vezes. 
   Se houver 2 ou mais encomendas nessa situa??o, dever? imprimir a encomenda de menor `id`.
   Formato de entrada: `m idp`
   Formato de sa?da:`Maximo produto <idp> <ide> <qtd>.` onde `<ide>` ? o n?mero da encomenda 
   em que `<idp>` ocorre mais vezes, sendo essa quantidade `<qtd>`
   N?o dever? listar nada caso o produto `<idp>` n?o ocorra em nenhuma encomenda, ou caso n?o haja encomendas
*/
void comando_m()
{
    int idp, n=0, maior_qtd=0, maior_ide;

    scanf(" %d", &idp);

    if (idp >= identificador_p) /* Verificacao se o produto existe no sistema ou nao */
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }

    while (n < identificador_e)
    {
        if(encomendas[n].lista[idp] > maior_qtd)
        {
            maior_qtd = encomendas[n].lista[idp];
            maior_ide = n;
        }

        n++; 
    }

    if (maior_qtd > 0 && n > 0)
    {
        printf("Maximo produto %d %d %d.\n", idp, maior_ide, maior_qtd);
    }
}


/* Funcao 'l' que lista todos os produtos existentes no sistema por ordem crescente de pre?o. 
   Se houver 2 ou mais produtos com o mesmo pre?o, dever? imprimir esses por ordem crescente de `id` de produto.
   Formato de entrada: `l`
   Formato de sa?da: Um bloco em que os produtos s?o listados por ordem crescente de pre?o 
*/
void merge_l(int left, int m, int right)
{
  int i, j, k;

  for(i = m + 1; i > left; i--)
    aux[i-1] = copia[i-1];
  
  for(j = m; j < right; j++)
    aux[right+m-j] = copia[j+1];

  for(k = left; k <= right; k++)
  {
    if(aux[j].preco < aux[i].preco)
      copia[k] = aux[j--];

    else if(aux[j].preco == aux[i].preco)
    {
      if (aux[j].idp < aux[i].idp)
        copia[k] = aux[j--];
      
      else
        copia[k]=aux[i++];
    }
    
    else
      copia[k] = aux[i++];
  }
}

void mergesort_l(int left, int right)
{
  int m = (right + left) / 2;
  
  if(right <= left)
    return;
  
  mergesort_l(left, m);
  mergesort_l(m+1, right);
  merge_l(left, m, right);
}


void comando_l()
{
    int n = 0, m = 0; 
    int left = 0;
    int right = identificador_p - 1;

    
    while (n < identificador_p)
    {
        if (sistema[n].preco != 0)
        {
            copia[m] = sistema[n];
            m++;
        }

        n++;
    }

    n = 0;

    mergesort_l(left, right);

    printf("Produtos\n");

    while (n < identificador_p)
    {
        printf("* %s %d %d\n", copia[n].descricao, copia[n].preco, copia[n].qtd);

        n++;
    }
}


/* Funcao 'L' que ordena os produtos de uma encomenda alfabeticamente. 
   Formato de entrada: `L <ide>`
   Formato de sa?da: Um bloco no formato em que os produtos s?o listados por ordem alfab?tica de descri??o
*/
void merge_L(int left, int m, int right){
  int i, j, k;

  for(i = m + 1; i > left; i--)
    aux[i-1] = copia[i-1];
  
  for(j = m; j < right; j++)
    aux[right+m-j] = copia[j+1];

  for(k = left; k <= right; k++)
  {
    if(strcmp(aux[j].descricao, aux[i].descricao) < 0)
      copia[k] = aux[j--];
    
    else
      copia[k] = aux[i++];
  }
}

void mergesort_L(int left, int right)
{
  int m = (right + left) / 2;

  if(right <= left)
    return;
  
  mergesort_L(left, m);
  mergesort_L(m+1, right);
  merge_L(left, m, right);
}

void comando_L()
{
    int ide, n = 0;
    int left = 0;
    int right = identificador_p - 1;

    scanf(" %d", &ide);

    if (ide >= identificador_e)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }

    else
    {
        while (n < identificador_p)
        {
            copia[n] = sistema[n];
            n++;
        }

        n = 0;

        mergesort_L(left, right);

        printf("Encomenda %d\n", ide);

        while (n < identificador_p)
        {
            if (encomendas[ide].lista[copia[n].idp] != 0 && copia[n].preco != 0)
            {
                printf("* %s %d %d\n", copia[n].descricao, copia[n].preco, encomendas[ide].lista[copia[n].idp]);
            }

            n++;
        }
    }
}


/* Funcao principal */
int main()
{
    char c;

    c = getchar();

    while (c != 'x') /* O comando 'x' termina o programa */
    {
        if (c == 'a')
        {
            comando_a();
        }

        else if (c == 'q')
        {
            comando_q();
        }

        else if (c == 'N')
        {
            comando_N();
        }

        else if (c == 'A')
        {
            comando_A();
        }

        else if (c == 'r')
        {
            comando_r();
        }

        else if (c == 'R')
        {
            comando_R();
        }

        else if (c == 'C')
        {
            comando_C();
        }

        else if (c == 'p')
        {
            comando_p();
        }

        else if (c == 'E')
        {
            comando_E();
        }

        else if (c == 'm')
        {
            comando_m();
        }

        else if (c == 'l')
        {
            comando_l();
        }

        else if (c == 'L')
        {
            comando_L();
        }
        
        c = getchar();
        c = getchar();
    }

    return 0;
}