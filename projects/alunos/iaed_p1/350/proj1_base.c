#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* numero maximo de produtos */
#define P_LEN 10000
/* numero maximo de encomendas */
#define E_LEN 500
/* peso maximo de uma encomenda */
#define P_MAX 200
/* numero de caracteres da descricao do produto */
#define DESC_LEN 63

/* estrutura do produto */
typedef struct
{
    char descricao[DESC_LEN];
    int idp;
    int preco;
    int peso;
    int qtd;
}Produto;

/* estrutura da encomenda */
typedef struct
{
    int peso_e;
    Produto produtos[P_MAX];
    int contador;
}Encomenda;

/* vetor onde sao guardados todos os produtos no sistema */
Produto sistema[P_LEN];

/* vetor onde sao guardadas as encomendas criadas */
Encomenda sistema_e[E_LEN];

/* contador do numero de produtos no sistema */
int contador_produtos;

/* contador do numero de encomendas no sistema */
int contador_encomendas;

/* prototipos das funcoes */
int getCommand();
void funcao_a();
void funcao_q();
void funcao_N();
void funcao_A();
void funcao_r();
void funcao_R();
void funcao_C();
void funcao_p();
void funcao_E();
void funcao_m();
void funcao_l();
void funcao_L();

int main()
{
    getCommand();
    return 0;
}

/* executar a accao correspondente ao comando */
int getCommand()
{
    while (1)
    {
        int command = getchar();
        switch (command)
        {
        case 'a':
            getchar();
            funcao_a();
            break;
        case 'q':
            funcao_q();
            break;
        case 'N':
            funcao_N();
            break;
        case 'A':
            funcao_A();
            break;
        case 'r':
            funcao_r();
            break;
        case 'R':
            funcao_R();
            break;
        case 'C':
            funcao_C();
            break;
        case 'p':
            funcao_p();
            break;
        case 'E':
            funcao_E();
            break;
        case 'm':
            funcao_m();
            break;
        case 'l':
            funcao_l();
            break;
        case 'L':
            funcao_L();
            break;
        case 'x':
            return 0;
        default:
            break;
        }
    }
    return 0;
}

/* Entrada: descricao, preco, peso, qtd
 * Funcao: adicionar um novo produto ao sistema, que se identifica pelo seu id 
 * Saida: novo produto
*/ 
void funcao_a()
{
    char descricao[DESC_LEN];
    int preco, peso, qtd;
    if(contador_produtos < P_LEN)
    {
        /* introduzir os atributos dados no produto correspondente */
        scanf("%[^:]:%d:%d:%d", descricao, &preco, &peso, &qtd);
        strcpy(sistema[contador_produtos].descricao, descricao);
        sistema[contador_produtos].preco = preco;
        sistema[contador_produtos].peso = peso;
        sistema[contador_produtos].qtd = qtd;   
        sistema[contador_produtos].idp = contador_produtos;
        printf("Novo produto %d.\n" , contador_produtos);
        contador_produtos++;
    }
}

/* Entrada: id do produto, quantidade
 * Funcao: adicionar stock a um produto no sistema, verifica se o produto existe, e adiciona a quantidade se possivel
 * Saida: *Nada*
*/ 
void funcao_q()
{
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    if(idp < contador_produtos) /* adiciona stock ao produto se este ja existir no sistema */
        sistema[idp].qtd += qtd;
    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n" , idp);
}

/* Entrada: *Nada*
 * Funcao: cria uma nova encomenda no sistema
 * Saida: Nova encomenda
*/ 
void funcao_N()
{
    if(contador_encomendas < E_LEN)
    {
        printf("Nova encomenda %d.\n", contador_encomendas);
        sistema_e[contador_encomendas].peso_e = 0; /* inicializa a encomenda com peso total = 0 */
        sistema_e[contador_encomendas].contador = 0;
        contador_encomendas++;
    }
}

/* Entrada: id da encomenda, id do produto, quantidade
 * Funcao: adiciona um produto a uma encomenda, ou adiciona quantidade se ja existir. verifica se a encomenda existe, se o produto existe, se tem excesso de peso e se ha stock do produto
 * Saida: *Nada*
*/ 
void funcao_A()
{
    int idp, ide, qtd, i;
    scanf("%d:%d:%d", &ide, &idp, &qtd);
    if(ide >= contador_encomendas)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if(sistema[idp].descricao[0] == '\0')
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if(sistema[idp].qtd < qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if((sistema_e[ide].peso_e + sistema[idp].peso * qtd) > P_MAX)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    else
    {
        for(i= 0; i < sistema_e[ide].contador; i++)
        {
            if(sistema_e[ide].produtos[i].idp == idp) /* se o produto ja existir, adiciona a quantidade e o peso ao peso total e remove a quantidade do sistema */
            {
                sistema_e[ide].produtos[i].qtd += qtd;
                sistema_e[ide].peso_e += sistema[idp].peso * qtd;
                sistema[idp].qtd -= qtd;
                return;
            }
        }   
        /* se o produto nao existir, adiciona o produto a encomenda, assim como o seu peso e remove a quantidade do sistema */
        sistema_e[ide].produtos[sistema_e[ide].contador] = sistema[idp];
        sistema_e[ide].produtos[sistema_e[ide].contador].qtd = qtd;
        sistema_e[ide].peso_e += sistema[idp].peso * qtd;
        sistema[idp].qtd -= qtd;
        sistema_e[ide].contador++;
        
    }
}

/* Entrada: id do produto, quantidade
 * Funcao: remove stock a uma produto no sistema, verifica se o produto existe, e se a quantidade pode ser removida
 * Saida: *Nada*
*/ 
void funcao_r()
{
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    if(sistema[idp].descricao[0] == '\0')
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if(sistema[idp].qtd < qtd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd, idp);
    else
        sistema[idp].qtd -= qtd;
}

/* Entrada: id da encomenda, id do produto
 * Funcao: remove um produto de uma encomenda, verifica se a encomenda existe, se o produto existe na encomenda e se o produto existe no sistema
 * Saida: *Nada*
*/ 
void funcao_R()
{
    int idp, ide, i, k;
    scanf("%d:%d", &ide, &idp);
    if(ide >= contador_encomendas)
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    else if(sistema[idp].descricao[0] == '\0')
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    for(i = 0; i < sistema_e[ide].contador; i++)
    {
        if(sistema_e[ide].produtos[i].idp == idp)
        {
            sistema[idp].qtd += sistema_e[ide].produtos[i].qtd; /* repor o produto no stock do sistema */
            sistema_e[ide].peso_e -= (sistema[idp].peso * sistema_e[ide].produtos[i].qtd); /* retirar peso da encomenda do produto retirado */ 
            for(k = i; k < sistema_e[ide].contador ; k++)
                sistema_e[ide].produtos[k] = sistema_e[ide].produtos[k+1]; /* puxar todos os produtos um indice para tras para apagar o produto do vetor */
            sistema_e[ide].contador--;
            return;
        }
    }
}


/* Entrada: id da encomenda
 * Funcao: calcula o preco a pagar pela encomenda, verifica se a encomenda existe
 * Saida: Preco da encomenda
*/ 
void funcao_C()
{
    int ide, i, soma = 0, idp;
    scanf("%d", &ide);
    if(ide >= contador_encomendas)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else
    {
        for(i = 0; i < sistema_e[ide].contador;i++) /* calcula o preco total da encomenda atraves da soma dos precos de todos os produtos */
        {    
            idp = sistema_e[ide].produtos[i].idp;
            soma += (sistema[idp].preco * sistema_e[ide].produtos[i].qtd);
        }
        printf("Custo da encomenda %d %d.\n", ide, soma);
    }

}


/* Entrada: id do produto, preco
 * Funcao: alterar o pre?o de um produto existente no sistema
 * Saida: *Nada*
*/ 
void funcao_p()
{
    int idp, preco;
    scanf("%d:%d", &idp, &preco);
    if(sistema[idp].descricao[0] == '\0')
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    sistema[idp].preco = preco; /* altera o preco do produto no sistema */
}


/* Entrada: id da encomenda, id do produto
 * Funcao: display da descricao e quantidade de um produto numa encomenda, verifica se a encomenda existe e se o produto existe
 * Saida: descricao e quantidade do produto
*/ 
void funcao_E()
{
    int ide, idp, i;
    scanf("%d:%d", &ide, &idp);
    if(ide >= contador_encomendas)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    else if(sistema[idp].descricao[0] == '\0')
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }
    for(i= 0; i < sistema_e[ide].contador; i++)
        if(sistema_e[ide].produtos[i].idp == idp) /* ver se o id do produto ? o correto */
        {
            printf("%s %d.\n", sistema[idp].descricao,sistema_e[ide].produtos[i].qtd);
            return;
        }
    printf("%s %d.\n", sistema[idp].descricao,0);
}

/* Entrada: id do produto
 * Funcao: display da encomenda em que ha maior quantidade do produto
 * Saida: maximo do produto e a encomenda onde se situa
*/ 
void funcao_m()
{
    int idp, i1, k, v, i2;
    scanf("%d", &idp);
    k = 0;
    if(sistema[idp].descricao[0] == '\0')
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }
    for(i1=0; i1 < contador_encomendas; i1++) /* guardar no k a quantidade do produto e em v a encomenda em que se situa */
        for(i2 = 0; i2 < sistema_e[i1].contador; i2++)
            if((sistema_e[i1].produtos[i2].idp == idp) && (sistema_e[i1].produtos[i2].qtd > k))/* guarda sempre a primeira encomenda com o maior valor(no caso de empate, ficaa a de menor indice) */
                {   
                    k = sistema_e[i1].produtos[i2].qtd;
                    v = i1;
                }
    if(k > 0)
        printf("Maximo produto %d %d %d.\n", idp, v, k);
}

/* Entrada: valor1, valor 2
 * Funcao: trocar 2 valores
 * Saida: valores trocados
*/ 
void exch(Produto* l , Produto* r)
{
    Produto k = *l;
    *l = *r;
    *r = k;
}

/* Entrada: vetor, valor minimo, valor maximo, flag
 * Funcao: ordenar por quicksort o vetor dado entre o valor minimo e o maximo, dependendo da flag, funciona para preco ou descricao
 * Saida: vetor ordenado
*/ 
int particao(Produto a[], int l, int r, int comparacao)
{
    int i = l-1, j;
    Produto v = a[r];
    for(j = l; j <= r-1 ; j++)
    {
        if(comparacao == 0) /* flag para ordenar por  preco */
        {
            if ((a[j].preco == v.preco) && (a[j].idp < v.idp))
            {
                i++;
                exch(&a[i], &a[j]);
            }
            if(a[j].preco < v.preco)
            {
                i++;
                exch(&a[i], &a[j]);
            }
        }
        else if(comparacao == 1) /* flag para ordenar por descricao */
        {
            if(strcmp(a[j].descricao, v.descricao) < 0)
            {
                i++;
                exch(&a[i], &a[j]);
            }
        }
    }
    exch(&a[i+1], &a[r]);
    return (i+1);
}
void quickSrt(Produto a[], int l, int r, int comparacao)
{
    int i;
    if(r <=l)
        return;
    i = particao(a, l, r, comparacao);
    quickSrt(a, l, i-1, comparacao);
    quickSrt(a, i+1, r, comparacao);
}

/* Entrada: *Nada*
 * Funcao: ordenar todos os produtos do sistema por preco, em caso de empate vem o menor id primeiro
 * Saida: lista com todos os produtos do sistema ordenados por preco
*/ 
void funcao_l()
{
    int i, l = 0;
    Produto ordered_sistema[P_LEN];
    for(i = 0; i < contador_produtos; i++) /* copiar o sistema para um novo array que possa ser alterado */
        ordered_sistema[i] = sistema[i];
    printf("Produtos\n");
    if(!(contador_produtos == 0))
    {
        quickSrt(ordered_sistema, 0, contador_produtos-1, l); /* ordenar os produtos por preco */
        for(i = 0; i < contador_produtos; i++)
            printf("* %s %d %d\n", ordered_sistema[i].descricao, ordered_sistema[i].preco,ordered_sistema[i].qtd);
    }
}

/* Entrada: id da encomenda
 * Funcao: display dos produtos dentro de uma encomenda por ordem alfabetica
 * Saida: lista com todos os produtos dentro da encomenda ordenados por ordem alfabetica
*/ 
void funcao_L()
{
    int ide, l =1, i, idp;
    Produto array_produtos[P_MAX];
    scanf("%d", &ide);
    if(ide >= contador_encomendas)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else
    {
        for(i = 0; i < sistema_e[ide].contador; i++) /* copiar os produtos da encomenda para um novo array */
                array_produtos[i] = sistema_e[ide].produtos[i];
        printf("Encomenda %d\n", ide);
        quickSrt(array_produtos, 0, sistema_e[ide].contador-1, l); /* ordenar os produtos por ordem alfabetica de descricao */
        for(i = 0; i < sistema_e[ide].contador; i++)
        {
            idp = array_produtos[i].idp;
            printf("* %s %d %d\n", sistema[idp].descricao, sistema[idp].preco,array_produtos[i].qtd);
        }
    }
}
