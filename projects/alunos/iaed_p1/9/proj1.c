#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DESCRICAO 63       /* N?mero m?ximo de caracteres da descricao do produto. */
#define PRODUTO_MAX 10001  /* N?mero m?ximo de produtos adicionados mais um. */
#define ENCOMENDA_MAX 50   /* N?mero m?ximo de encomendas adicionadas. */
#define PESO_MAX 200       /* Peso m?ximo de uma encomenda. */
#define DETALHE_MAX 100000 /* N?mero maximo de linhas de detalhe de encomendas (n?mero m?ximo de encomendas * n?mero m?ximo de produtos no pressuposto cada produto tem peso = 1). */
#define INPUT_MAX 10000    /* Tamanho do input. */

/* Um produto (estrutura) definida por um identificador, uma descricao, um preco, um peso e a quantidade em stock. */
typedef struct produto
{
    int identificador;
    char descricao[DESCRICAO];
    int preco;
    int peso;
    int quantidade;
} Produto;

/* Uma encomenda (estrutura) definida por um identificador, peso total da encomenda e custo. */
typedef struct encomenda
{
    int identificador;
    int peso_total;
    int custo;
} Encomenda;

/* Detalhes de uma emcomenda (estrutura) definida por um identificador da encomenda, identificador do produto e quantidade encomendada. */
typedef struct detalhes_encomenda
{
    int identificador_encomenda;
    int identificador_produto;
    int quantidade_produto;
} Detalhes_encomenda;

/* Uma estrutura definida por uma descri??o de produto, preco do produto e quantidade numa encomenda para efeito de ordena??o. */
typedef struct encomenda_temp
{
    char descricao[DESCRICAO];
    int preco;
    int quantidade;
} Temp_enc;

/* DECLARACAO DE VARIAVEIS */

/* Array de produtos. */
Produto lista_prod[PRODUTO_MAX];
/* Array de encomendas. */
Encomenda lista_enc[ENCOMENDA_MAX];
/* Array de detalhes de uma encomenda. */
Detalhes_encomenda lista_det_enc[DETALHE_MAX];
/* Array tempor?rio de estruturas "Produtos" para efeito de ordena??o. */
Produto lista_prod_temp[PRODUTO_MAX];
/* Array tempor?rio de estruturas "Temp_enc" para efeito de ordena??o. */
Temp_enc lista_enc_temp[DETALHE_MAX];
/* Array tempor?rio auxiliar de estrutura "Temp_enc" para efeito de ordena??o. */
Temp_enc aux[DETALHE_MAX];

/* Vari?veis de contadores. */
int total_produtos = 0, total_encomendas = -1, total_detalhes = 0, total_temp = 0;

/* DECLARACAO DE FUNCOES */

void func_a();
void func_q();
void func_N();
void func_A();
void func_r();
void func_R();
void func_C();
void func_p();
void func_E();
void func_m();
void func_l();
void func_L();

int procura_encomenda(int);
int procura_produto(int);
int encomenda_contem_produto(int, int);
void k();
void K(int);
void merge_sort_prod(Produto[], int, int);
void merge_prod(Produto[], int, int, int);
void merge_sort_enc(Temp_enc[], int, int);
void merge_enc(Temp_enc[], int, int, int);

/* FUNCAO PRINCIPAL */

/* Fun??o principal que executa uma funcao de acordo com o primeiro parametro do input. */
int main()
{
    char command;
    while (1)
    {
        command = getchar();
        switch (command)
        {
        case 'a':
            func_a();
            break;
        case 'q':
            func_q();
            break;
        case 'N':
            func_N();
            break;
        case 'A':
            func_A();
            break;
        case 'r':
            func_r();
            break;
        case 'R':
            func_R();
            break;
        case 'C':
            func_C();
            break;
        case 'p':
            func_p();
            break;
        case 'E':
            func_E();
            break;
        case 'm':
            func_m();
            break;
        case 'l':
            func_l();
            break;
        case 'L':
            func_L();
            break;
        case 'x':
            return EXIT_SUCCESS;
        default:
            printf("ERRO: Comando desconhecido\n");
        }
        getchar();
    }
    return EXIT_FAILURE;
}

/* COMANDOS */

/* Adicionar um novo produto ao sistema de acordo com a estrutura "Produto". */
void func_a()
{
    char input[INPUT_MAX];
    char *tok;
    int i = 0;
    char *array[4];

    if (total_produtos < PRODUTO_MAX)
    {
        scanf("%s", input);
        tok = strtok(input, ":");

        while (tok != NULL)
        {
            array[i] = tok;
            tok = strtok(NULL, ":");
            i++;
        }
    }

    lista_prod[total_produtos].identificador = total_produtos;
    strcpy(lista_prod[total_produtos].descricao, array[0]);
    lista_prod[total_produtos].preco = atoi(array[1]);
    lista_prod[total_produtos].peso = atoi(array[2]);
    lista_prod[total_produtos].quantidade = atoi(array[3]);

    printf("Novo produto %d.\n", lista_prod[total_produtos].identificador);

    total_produtos++;
}

/*Adicionar mais stock a um produto existente no sistema. */
void func_q()
{
    char input[INPUT_MAX];
    char *tok;
    int i = 0, prod = -1;
    char *array[2];

    scanf("%s", input);
    tok = strtok(input, ":");

    while (tok != NULL)
    {
        array[i] = tok;
        tok = strtok(NULL, ":");
        i++;
    }

    prod = procura_produto(atoi(array[0]));

    /* Validar exist?ncia do produto. */
    if (prod == -1)
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", atoi(array[0]));
    }
    else
        lista_prod[prod].quantidade += atoi(array[1]);
}

/* Criar uma nova encomenda de acordo com a estrutura "Encomenda". */
void func_N()
{
    lista_enc[total_encomendas + 1].identificador = total_encomendas + 1;
    lista_enc[total_encomendas + 1].peso_total = 0;
    lista_enc[total_encomendas + 1].custo = 0;

    printf("Nova encomenda %d.\n", total_encomendas + 1);

    total_encomendas++;
}

/* Adicionar um produto a uma encomenda. */
void func_A()
{
    char input[INPUT_MAX];
    char *tok;
    int i = 0, j = 0, enc = -1, prod = -1, peso_enc, peso_prod, preco_prod, quant_prod;
    char *array[3];

    if (total_produtos < PRODUTO_MAX)
    {
        scanf("%s", input);
        tok = strtok(input, ":");

        while (tok != NULL)
        {
            array[i] = tok;
            tok = strtok(NULL, ":");
            i++;
        }
    }

    /* Validar exist?ncia de encomendas. */
    if (total_encomendas == -1)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", atoi(array[1]), atoi(array[0]));
    }
    else
    {
        enc = procura_encomenda(atoi(array[0]));
        prod = procura_produto(atoi(array[1]));

        /* Validar exist?ncia da encomenda. */
        if (enc == -1)
        {
            printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", atoi(array[1]), atoi(array[0]));
        }
        /* Validar exist?ncia do produto. */
        else if (prod == -1)
        {
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", atoi(array[1]), atoi(array[0]));
        }
        else
        {
            quant_prod = lista_prod[prod].quantidade;
            peso_prod = lista_prod[prod].peso;
            peso_enc = lista_enc[enc].peso_total;

            /* Validar pedido de encomenda. */
            /* Validar quantidade do produto. */
            if (quant_prod < atoi(array[2]))
            {
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", atoi(array[1]), atoi(array[0]));
            }
            /* Validar peso total da encomenda somando, ao peso da encomenta o valor da nova linha e verificando se ultrapassa o limite definido (PESO_MAX). */
            else if (peso_enc + (atoi(array[2]) * peso_prod) > PESO_MAX)
            {
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n", atoi(array[1]), atoi(array[0]), PESO_MAX);
            }
            else
            {
                preco_prod = lista_prod[prod].preco;

                j = encomenda_contem_produto(atoi(array[0]), atoi(array[1]));

                if (j != -1) /* Caso o produto esteja na encomenda, adiciona a quantidade ? existente. */
                {
                    lista_det_enc[j].quantidade_produto += atoi(array[2]);
                    lista_enc[enc].peso_total += (atoi(array[2]) * peso_prod);
                    lista_enc[enc].custo += (atoi(array[2]) * preco_prod);
                    lista_prod[prod].quantidade -= atoi(array[2]);
                }
                else /* Caso o produto n?o esteja na encomenda, adiciona nova linha ao array de detalhe de encomenda. */
                {
                    lista_det_enc[total_detalhes].identificador_encomenda = atoi(array[0]);
                    lista_det_enc[total_detalhes].identificador_produto = atoi(array[1]);
                    lista_det_enc[total_detalhes].quantidade_produto = atoi(array[2]);

                    total_detalhes++;

                    /* atualiza a encomenda com o valor do custo e o peso. Necess?rio para efeitos de consulta, e subtrai a quantidade ao stock do produto. */
                    lista_enc[enc].peso_total += (atoi(array[2]) * peso_prod);
                    lista_enc[enc].custo += (atoi(array[2]) * preco_prod);
                    lista_prod[prod].quantidade -= atoi(array[2]);
                }
            }
        }
    }
}

/* Remover stock a um produto existente no sistema. */
void func_r()
{
    char input[INPUT_MAX];
    char *tok;
    int i = 0, prod = -1;
    char *array[2];

    scanf("%s", input);
    tok = strtok(input, ":");

    while (tok != NULL)
    {
        array[i] = tok;
        tok = strtok(NULL, ":");
        i++;
    }

    prod = procura_produto(atoi(array[0]));

    /* Validar exist?ncia do produto. */
    if (prod == -1)
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", atoi(array[0]));
    }
    /* Validar quantidade do produto. */
    else if (lista_prod[prod].quantidade <= 0 || lista_prod[prod].quantidade - atoi(array[1]) < 0)
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", atoi(array[1]), atoi(array[0]));
    }
    else
        lista_prod[prod].quantidade -= atoi(array[1]);
}

void func_R() /*Remove um produto de uma encomenda*/
{
    char input[INPUT_MAX];
    char *tok;
    int i = 0, j = 0, prod = -1, enc = -1;
    int quantidade_restante = 0; /* Guarda a quantidade existente do produto a remover na encomenda. */
    char *array[2];

    scanf("%s", input);
    tok = strtok(input, ":");

    while (tok != NULL)
    {
        array[i] = tok;
        tok = strtok(NULL, ":");
        i++;
    }

    enc = procura_encomenda(atoi(array[0]));
    prod = procura_produto(atoi(array[1]));

    /* Validar exist?ncia da encomenda. */
    if (enc == -1)
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", atoi(array[1]), atoi(array[0]));
    }
    /* Validar exist?ncia do produto. */
    else if (prod == -1)
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", atoi(array[1]), atoi(array[0]));
    }
    else
    {
        for (j = 0; j < total_detalhes; j++)
        {
            if (lista_det_enc[j].identificador_encomenda == atoi(array[0]) && lista_det_enc[j].identificador_produto == atoi(array[1]))
            {
                /* Atualiza a na encomenda, substraindo ao valor existente, o peso do produto * quantidade e pre?o * quantidade, respectivamente o peso total e o custo da encomenda. */
                quantidade_restante = lista_det_enc[j].quantidade_produto;
                lista_enc[enc].custo -= (quantidade_restante * lista_prod[prod].preco);
                lista_enc[enc].peso_total -= (quantidade_restante * lista_prod[prod].peso);

                /* Aumentar stock do produto e coloca a zero  a quantidade na linha de detlhe da encomenda. */
                lista_prod[prod].quantidade += quantidade_restante;
                lista_det_enc[j].quantidade_produto = 0;
            }
        }
    }
}

/* Calcular o custo de uma encomenda. */
void func_C()
{
    int input = 0, enc = -1;

    scanf("%d", &input);

    enc = procura_encomenda(input);

    /* Validar exist?ncia da encomenda. */
    if (enc == -1)
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", input);
    }
    /* Procurar o custo de uma encomenda atrav?s do seu id e imprime o custo calculado aquando da inser??o de um produto na mesma. */
    else
    {
        printf("Custo da encomenda %d %d.\n", lista_enc[enc].identificador, lista_enc[enc].custo);
    }
}

/* Alterar o pre?o de um produto existente no sistema. */
void func_p()
{
    char input[INPUT_MAX];
    char *tok;
    int i = 0, j = 0, prod = -1, enc = 0, novo_preco = 0, velho_preco = 0, dif = 0, quantidade = 0;
    char *array[2];

    scanf("%s", input);
    tok = strtok(input, ":");

    while (tok != NULL)
    {
        array[i] = tok;
        tok = strtok(NULL, ":");
        i++;
    }

    prod = procura_produto(atoi(array[0]));

    /*Validar exist?ncia do produto. */
    if (prod == -1)
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", atoi(array[0]));
    }
    else
    {
        velho_preco = lista_prod[prod].preco;
        novo_preco = atoi(array[1]);

        /* Alterar pre?o do produto na lista de produtos. */
        lista_prod[prod].preco = novo_preco;

        /* Alterar custos das encomendas. */
        for (j = 0; j < total_detalhes; j++)
        {
            if (lista_det_enc[j].identificador_produto == atoi(array[0]))
            {
                quantidade = lista_det_enc[j].quantidade_produto;
                /* C?lculo da diferen?a do custo. */
                dif = quantidade * (novo_preco - velho_preco);
                enc = procura_encomenda(lista_det_enc[j].identificador_encomenda);
                /* Atribui??o do novo custo. */
                lista_enc[enc].custo += dif;
            }
        }
    }
}

/* Retornar a descri??o e a quantidade de um produto numa dada encomenda. */
void func_E()
{
    char input[INPUT_MAX];
    char *tok;
    int i = 0, j = 0, enc = -1, prod = -1;
    char *array[2];

    scanf("%s", input);
    tok = strtok(input, ":");

    while (tok != NULL)
    {
        array[i] = tok;
        tok = strtok(NULL, ":");
        i++;
    }

    enc = procura_encomenda(atoi(array[0]));
    prod = procura_produto(atoi(array[1]));

    j = encomenda_contem_produto(atoi(array[0]), atoi(array[1]));

    /* Validar exist?ncia da encomenda. */
    if (enc == -1)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", atoi(array[0]));
    }
    /* Validar exist?ncia do produto. */
    else if (prod == -1)
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", atoi(array[1]));
    }
    else if (j == -1)
    {
        printf("%s %d.\n", lista_prod[prod].descricao, 0);
    }
    else
    {
        for (i = 0; i <= total_detalhes; i++)
        {
            if (lista_det_enc[i].identificador_encomenda == atoi(array[0]) && lista_det_enc[i].identificador_produto == atoi(array[1]) && lista_det_enc[i].quantidade_produto >= 0)
            {
                printf("%s %d.\n", lista_prod[prod].descricao, lista_det_enc[i].quantidade_produto);
                i = total_detalhes;
            }
        }
    }
}

/* Retornar o identificador da encomenda em que um dado produto ocorre mais vezes. */
void func_m()
{
    int i = 0, input = 0, prod = -1;
    int ide_out = -1, qtd_max_out = -1; /* ide_out n?mero da encomenta onde o produto tem maior quantidade, qtd_max_out maior quantidade do produto. */

    scanf("%d", &input);

    prod = procura_produto(input);

    /* Validar exist?ncia do produto. */
    if (prod == -1)
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", input);
    }
    else
    {
        for (i = 0; i < total_detalhes; i++)
        {
            if (lista_det_enc[i].identificador_produto == input)
            {
                if (lista_det_enc[i].quantidade_produto == qtd_max_out)
                {
                    if (lista_det_enc[i].identificador_encomenda < ide_out)
                    {
                        ide_out = lista_det_enc[i].identificador_encomenda;
                    }
                }
                else
                {
                    if (lista_det_enc[i].quantidade_produto > qtd_max_out)
                    {
                        qtd_max_out = lista_det_enc[i].quantidade_produto;
                        ide_out = lista_det_enc[i].identificador_encomenda;
                    }
                }
            }
        }
        if (ide_out != -1 && qtd_max_out > 0)
        {
            printf("Maximo produto %d %d %d.\n", input, ide_out, qtd_max_out);
        }
    }
}

/* Listar todos os produtos existentes no sistema por ordem crescente de pre?o e caso seja este seja igual, ordena por ordem crescente o identificador. */
void func_l()
{
    if (total_produtos > 0)
    {
        merge_sort_prod(lista_prod, 0, total_produtos - 1);
    }
    k();
}

/* Listar todos os produtos de uma encomenda por ordem alfab?tica da descri??o do produto. */
void func_L()
{
    int input = 0;
    int enc = -1, i = 0, id_prod = 0, count = -1;

    /* Inicializa o array. */
    for (i = 0; i < total_detalhes; i++)
    {
        strcpy(lista_enc_temp[i].descricao, "");
        lista_enc_temp[i].preco = 0;
        lista_enc_temp[i].quantidade = 0;
    }

    scanf("%d", &input);

    enc = procura_encomenda(input);

    if (enc == -1)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", input);
    }
    else
    {
        printf("Encomenda %d\n", input);

        /* Cria uma lista tempor?ria com as linhas de detalhe de encomenda igual ao parametro de entrada, incluindo a descri??o do produto. */
        for (i = 0; i < total_detalhes; i++)
        {
            if (lista_det_enc[i].identificador_encomenda == input && lista_det_enc[i].quantidade_produto > 0)
            {
                ++count;
                id_prod = procura_produto(lista_det_enc[i].identificador_produto);

                strcpy(lista_enc_temp[count].descricao, lista_prod[id_prod].descricao);
                lista_enc_temp[count].preco = lista_prod[id_prod].preco;
                lista_enc_temp[count].quantidade = lista_det_enc[i].quantidade_produto;
            }
        }
        /* Tratamento quando existe um ou dois produtos na encomenda. */
        if (count == 0 || count == 1)
        {
            for (i = 0; i < (count + 1); i++)
            {
                if (lista_enc_temp[i].preco != 0 && lista_enc_temp[i].quantidade != 0)
                {
                    merge_sort_enc(lista_enc_temp, 0, count);
                }
            }
        }
        /* Tratamento quando existe mais do que dois produtos na encomenda. */
        else if (count > 1)
        {
            merge_sort_enc(lista_enc_temp, 0, count);
        }
        K(count);
    }
}

/* FUNCOES AUXILIARES */

/* Obter id da encomenda no array de encomendas. */
int procura_encomenda(int id)
{
    int i = 0, enc = -1;

    for (i = 0; i <= total_encomendas; i++)
    {
        if (lista_enc[i].identificador == id)
        {
            enc = i;
        }
    }
    return enc;
}

/* Obter id do produto no array de produtos. */
int procura_produto(int id)
{
    int i = 0, prod = -1;

    for (i = 0; i < total_produtos; i++)
    {
        if (lista_prod[i].identificador == id)
        {
            prod = i;
        }
    }
    return prod;
}

/* Verificar se o produto existe na encomenda. */
int encomenda_contem_produto(int n1, int n2)
{
    int j = 0;
    for (j = 0; j < total_detalhes; j++)
    {
        if (lista_det_enc[j].identificador_encomenda == n1 && lista_det_enc[j].identificador_produto == n2)
        {
            return j;
        }
    }
    return -1;
}

/* Listar todos os produtos. */
void k()
{
    int i = 0;

    printf("Produtos\n");
    for (i = 0; i < total_produtos; i++)
    {
        printf("* %s %d %d\n", lista_prod[i].descricao, lista_prod[i].preco, lista_prod[i].quantidade);
    }
}

/* Listar uma dada encomenda. */
void K(int number)
{
    int i = 0;

    for (i = 0; i <= number; i++)
    {
        if (lista_enc_temp[i].preco != 0 && lista_enc_temp[i].quantidade != 0)
        {
            printf("* %s %d %d\n", lista_enc_temp[i].descricao, lista_enc_temp[i].preco, lista_enc_temp[i].quantidade);
        }
    }
}

/* ALGORITMO ORDENACAO */

/*  Fun??o principal Merge Sort do produto. Utiliza a fun??o merge_sort_prod para ordenar por pre?o e Identificador. */
void merge_sort_prod(Produto a[], int low, int high)
{
    int mid = 0;

    if (low == high)
    {
        return;
    }
    else
    {
        mid = (low + high) / 2;

        merge_sort_prod(a, low, mid);

        merge_sort_prod(a, mid + 1, high);

        merge_prod(a, low, mid, high);
    }
}

/* Fun??o que efetua a compara??o de valores para o Merge Sort. */
void merge_prod(Produto a[], int low, int mid, int high)
{
    int i = 0;
    int left_index = low;
    int right_index = mid + 1;
    int combined_index = low;

    Produto tempA[PRODUTO_MAX];

    while (left_index <= mid && right_index <= high)
    {
        if (a[left_index].preco < a[right_index].preco)
        {
            tempA[combined_index++] = a[left_index++];
        }
        else
        {
            if (a[left_index].preco > a[right_index].preco)
            {
                tempA[combined_index++] = a[right_index++];
            }
            else
            {
                if (a[left_index].identificador < a[right_index].identificador)
                {
                    tempA[combined_index++] = a[left_index++];
                }
                else
                {
                    tempA[combined_index++] = a[right_index++];
                }
            }
        }
    }

    if (left_index == mid + 1)
    {
        while (right_index <= high)
        {
            tempA[combined_index++] = a[right_index++];
        }
    }
    else
    {
        while (left_index <= mid)
        {
            tempA[combined_index++] = a[left_index++];
        }
    }

    for (i = low; i <= high; i++)
    {
        a[i] = tempA[i];
    }
}

/*  Fun??o principal Merge Sort da encomenda. Utiliza a fun??o merge_sort_enc para ordenar por ordem alfab?tica da descri??o do produto. */
void merge_sort_enc(Temp_enc a[], int low, int high)
{
    int mid = 0;

    if (low == high)
    {
        return;
    }
    else
    {
        mid = (low + high) / 2;

        merge_sort_enc(a, low, mid);

        merge_sort_enc(a, mid + 1, high);

        merge_enc(a, low, mid, high);
    }
}

/* Fun??o que efetua a compara??o de valores para o Merge Sort. */
void merge_enc(Temp_enc a[], int low, int mid, int high)
{
    int i = 0;
    int left_index = low;
    int right_index = mid + 1;
    int combined_index = low;

    Temp_enc tempA[ENCOMENDA_MAX];

    while (left_index <= mid && right_index <= high)
    {
        if (strcmp(a[left_index].descricao, a[right_index].descricao) < 0)
        {
            tempA[combined_index++] = a[left_index++];
        }
        else
        {
            tempA[combined_index++] = a[right_index++];
        }
    }

    if (left_index == mid + 1)
    {
        while (right_index <= high)
        {
            tempA[combined_index++] = a[right_index++];
        }
    }
    else
    {
        while (left_index <= mid)
        {
            tempA[combined_index++] = a[left_index++];
        }
    }

    for (i = low; i <= high; i++)
    {
        a[i] = tempA[i];
    }
}
