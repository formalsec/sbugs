#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXPRODUTO 10000
#define MAXENCOMENDA 500
#define MAXPESO 200
#define chave(A) (A)
#define menor(A, B) (chave(A) < chave(B))

typedef struct produtos
{
    char desc[63];
    int idp, preco, peso, qtd;
}p;

p sistema[MAXPRODUTO] = {0};
p encomendas[MAXENCOMENDA][MAXPESO] = {0};

/* Contador global dos idp */
int s = 0;
/* Contador global dos ide */
int e = 0;

/*** Funcoes auxiliares ***/

int peso_encomenda(int ide) /* Calcula o peso da encomenda com ide untroduzido*/
{
    int peso = 0, i;
    for (i = 0; encomendas[ide][i].preco != 0 && i < 200; i++)
        peso += encomendas[ide][i].peso * encomendas[ide][i].qtd;
    return peso;
}

void apagar_produto(int ide, int n) /* Apaga o produto na posicao n da encomenda com ide introduzido */
{
    int a;
    for (a = 0; a < 63; a++)
        encomendas[ide][n].desc[a] = '\0';
    encomendas[ide][n].idp = 0;
    encomendas[ide][n].preco = 0;
    encomendas[ide][n].peso = 0;
    encomendas[ide][n].qtd = 0;
}

void InsertionSort_preco(p v[], int esquerda, int direita)  /* Ordena os elementos do vetor introduzido por ordem crecente de preco */
{
    int i, j;
    for (i = esquerda + 1; i <= direita; i++)
    {
        p aux = v[i];
        j = i - 1;
        while (j >= esquerda && (menor(aux.preco, v[j].preco) || (aux.preco == v[j].preco && menor(aux.idp, v[j].idp))))
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = aux;
    }
}
void InsertionSort_desc(p v[], int esquerda, int direita)   /* Ordena os elementos do vetor introduzido por ordem alfabetica */
{
    int i, j;
    for (i = esquerda + 1; i <= direita; i++)
    {
        p aux = v[i];
        j = i - 1;
        while (j >= esquerda && (strcmp(aux.desc, v[j].desc) < 0 || (strcmp(aux.desc, v[j].desc) == 0 && menor(aux.idp, v[j].idp))))
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = aux;
    }
}

/*** Funcoes dos comandos ***/

void comando_a()            /* Adiciona um novo produto ao sistema */
{ 
    scanf(" %[^:]:%d:%d:%d\n", sistema[s].desc, &sistema[s].preco, &sistema[s].peso, &sistema[s].qtd);
    sistema[s].idp = s;
    printf("Novo produto %d.\n", s);
    s++;
}

void comando_q()            /* Adiciona stock a um produto existente no sistema */
{
    int produ, quant;
    scanf(" %d:%d\n", &produ, &quant);
    if (sistema[produ].preco == 0)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", produ);
    else
        sistema[produ].qtd += quant;
}

void comando_N()            /* Cria uma nova encomenda */
{
    printf("Nova encomenda %d.\n", e);
    e++;
}

void comando_A()            /* Adiciona um produto a uma encomenda */
{
    int ide, produ, quant, i, estado = 0;
    scanf(" %d:%d:%d\n", &ide, &produ, &quant);
    if (ide >= e)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", produ, ide);
    else if(sistema[produ].preco == 0)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", produ, ide);
    else if (sistema[produ].qtd - quant < 0)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", produ, ide);
    else if (peso_encomenda(ide) + quant * sistema[produ].peso > 200)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", produ, ide);
    else
    {
        sistema[produ].qtd -= quant;
        for (i = 0; encomendas[ide][i].preco != 0 && i < 200; i++)
        {
            /*Produto ja existe na encomenda*/
            if (encomendas[ide][i].idp == sistema[produ].idp)
            {
                encomendas[ide][i].qtd += quant;
                estado = 1;
            }
        }
        /*Produto novo na encomenda*/
        if (!estado)
        {
            encomendas[ide][i] = sistema[produ];
            encomendas[ide][i].qtd = quant;
        }
    }  
}

void comando_r()            /* Remove stock a um produto existente */
{
    int produ, quant;
    scanf(" %d:%d\n", &produ, &quant);
    if (sistema[produ].preco == 0)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", produ);
    else if (sistema[produ].qtd - quant < 0)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quant, produ);
    else
        sistema[produ].qtd -= quant;
}

void comando_R()            /* Remove um produto de uma encomenda */
{
    int ide, produ, i, numero_produtos = 0;
    int j = -1;
    scanf(" %d:%d\n", &ide, &produ);
    if (ide >= e)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", produ, ide);
    else if (sistema[produ].preco == 0)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", produ, ide);
    else
    {
        for (i = 0; encomendas[ide][i].preco != 0 && i < 200; i++)
        {
            if (sistema[produ].idp == encomendas[ide][i].idp)
            {
                /* Relembra a posicao do produto na encomenda */
                j = i;
                sistema[produ].qtd += encomendas[ide][i].qtd;
            }
            numero_produtos++;
        }
        /* Ultimo produto da encomenda */
        if (j == numero_produtos - 1)
            apagar_produto(ide, j);
        /* Nao e o ultimo produto da encomenda */ 
        else if (j > -1)                    
        {
            /* Deslocamento dos produtos posteriores ao introduzido pelo utiliador, para os indices antecendentes */
            for (i = j; i < numero_produtos - 1; i++)
                encomendas[ide][i] = encomendas[ide][i + 1];
            /* Apaga-se o ultimo produto, pois ja foi movido para a posicao antecedente */
            apagar_produto(ide, i);
        }
    }
}

void comando_C()            /* Calcula o custo de uma encomenda */
{
    int ide, i, custo = 0;
    scanf(" %d\n", &ide);
    if (ide >= e)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else
    {
        for (i = 0; encomendas[ide][i].preco != 0 && i < 200; i++)
            custo += encomendas[ide][i].preco * encomendas[ide][i].qtd;
        printf("Custo da encomenda %d %d.\n", ide, custo);
    }
}

void comando_p()            /* Altera o pre?o de um produto existente no sistema */
{
    int produ, novo_preco, ide, i;
    scanf(" %d:%d\n", &produ, &novo_preco);
    if (sistema[produ].preco == 0)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", produ);
    else
    {
        /* Altera o preco no sistema */
        sistema[produ].preco = novo_preco;
        /* Altera o preco nas encomendas */
        for (ide = 0; ide < e; ide++)
        {
            for (i = 0; encomendas[ide][i].preco != 0 && i < 200; i++)
            {
                if (encomendas[ide][i].idp == sistema[produ].idp)
                    encomendas[ide][i].preco = novo_preco;
            }
        }
    }
}

void comando_E()            /* Lista a descri??o e a quantidade de um produto numa encomenda */
{
    int i, ide, produ, estado = 0;
    scanf(" %d:%d\n", &ide, &produ);
    if (ide >= e)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if (sistema[produ].preco == 0)
        printf("Impossivel listar produto %d. Produto inexistente.\n", produ);
    else
    {
        for (i = 0; encomendas[ide][i].preco != 0 && i < 200; i++)
        {
            /* Produto ja existe na encomenda */
            if (encomendas[ide][i].idp == sistema[produ].idp)
            {
                printf("%s %d.\n", encomendas[ide][i].desc, encomendas[ide][i].qtd);
                estado = 1;
            }
        }
        /* Produto nao existe na encomenda*/
        if (!estado)
            printf("%s 0.\n", sistema[produ].desc);
    }
}

void comando_m()            /* Lista o identificador da encomenda em que o produto dado ocorre mais vezes */
{
    int i = 0, maior_quant = 0, ide = 0, produ, resposta, estado = 0;
    scanf(" %d\n", &produ);
    if (sistema[produ].preco == 0)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", produ);
    else
    {
        for (ide = 0; ide < e; ide++)
        {
            for (i = 0; encomendas[ide][i].preco != 0 && i < 200; i++)
            {
                if (sistema[produ].idp == encomendas[ide][i].idp)
                {
                    estado = 1;
                    if (encomendas[ide][i].qtd > maior_quant)
                    {
                        maior_quant = encomendas[ide][i].qtd;
                        /* Como o loop comeca no ide mais baixo, a resposta e sempre o ide mais baixo */
                        resposta = ide;
                    }
                }
            }
        }
        /* Produto existe nas encomendas */
        if (estado)
            printf("Maximo produto %d %d %d.\n", produ, resposta, maior_quant);
    }
}

void comando_l()            /* Lista todos os produtos existentes no sistema por ordem crescente de pre?o */
{
    int i, j;
    /* Vetor auxiliar */
    p aux_preco[MAXPRODUTO] = {0};
    printf("Produtos\n");
    /* Copia-se a parte com produtos do sistema para o vetor auxiliar */
    for (i = 0; i < s; i++)
        aux_preco[i] = sistema[i];
    InsertionSort_preco(aux_preco, 0, i - 1);
    for (j = 0; j < i; j++)
        printf("* %s %d %d\n", aux_preco[j].desc, aux_preco[j].preco, aux_preco[j].qtd);
}

void comando_L()            /* Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
{
    int i, j, ide;
    /* Vetor auxiliar */
    p aux_descricoes[MAXPESO] = {0};
    scanf(" %d\n", &ide);
    if (ide >= e)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else
    {
        printf("Encomenda %d\n", ide);
        /* Copia-se a parte preenchida da encomenda para o auxiliar */
        for (i = 0; encomendas[ide][i].preco != 0 && i < 200; i++)
            aux_descricoes[i] = encomendas[ide][i];
        InsertionSort_desc(aux_descricoes, 0, i - 1);
        for (j = 0; j < i; j++)
            printf("* %s %d %d\n", aux_descricoes[j].desc, aux_descricoes[j].preco, aux_descricoes[j].qtd);
    }
}

/*** main ***/

int main()
{
    /* Le o comando */
    char comando = getchar();           
    while (comando != 'x')
    {
        switch (comando)
        {
            case 'a':
                comando_a();
                break;
            case 'q':
                comando_q();
                break;
            case 'N':
                comando_N();
                break;
            case 'A':
                comando_A();
                break;
            case 'r':
                comando_r();
                break;
            case 'R':
                comando_R();
                break;
            case 'C':
                comando_C();
                break;
            case 'p':
                comando_p();
                break;
            case 'E':
                comando_E();
                break;
            case 'm':
                comando_m();
                break;
            case 'l':
                comando_l();
                break;
            case 'L':
                comando_L();
                break;
            default:
                break;
        }
        comando = getchar();
    }
    return 0;
}
