#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Constantes */
#define OK 1
#define IDPMAX 10000
#define IDEMAX 500
#define ENCMAX 200 /* No maximo existe 200 produtos de 1 de peso numa encomenda */
#define DESC 64
#define PESOMAX 200
#define SEPARA ':'
#define ENTRADA 100 /* Convencao de tamanho maximo de um comando */
#define ZERO '0'
#define VAZIO -1 /* Convencao de stock de um espaco vazio de uma enc */


/* Tipo Produto */

typedef struct produto 
{
    int id, preco, peso, stock;
    char desc[DESC];

} prd;

/* Tipo Encomenda */

typedef struct encomenda
{
    int peso;
    int interior[IDPMAX]; /* Guardara as quantidades correspondentes aos ids, genero dicionario */

    /* No interior, stock negativo corresponde ao id de um produto nao existente na encomenda */
    
} enc;


/* Variaveis Globais */
int idp_gb = 0; /* Contador que contem o identificador do proximo produto */
int ide_gb = 0; /* O mesmo, para o identificador de encomendas */
int igb; /* Contador para uso entre funcoes do mesmo comando - leitura da info dos comandos */
prd memoriaPRD[IDPMAX]; /* Array com todos os produtos existentes */
enc memoriaENC[IDEMAX]; /* Array com todas as encomendas existentes */


/* Lista de Funcoes de Comandos */
void novo_prd(char info[]);
void adiciona_stock(char info[]);
void nova_enc(void);
void adiciona_prd(char info[]);
void retira_stock(char info[]);
void retira_prd(char info[]);
void custo_enc(char info[]);
void muda_preco(char info[]);
void prd_em_enc(char info[]);
void max_prd(char info[]);
void l_prd_preco(void);
void l_prds_enc(char info[]);


/* Lista de Funcoes Auxiliares */
int inteiro(char info[]);
void ini_interior(int interior[]);
void ordena_precos(prd prds[], int n, int max);
void ordena_descs(int esq, int dir, prd prds[]);
void merge_desc(int esq, int med, int dir, prd prds[]);



/* Main - Entrada de Comandos */
int main()
{
    char com, info[ENTRADA];

    while (OK)
    {
        switch (com = getchar())
        {
            case 'a':
            {
                scanf("%s",info);
                novo_prd(info);
                break;
            }
            case 'q':
            {
                scanf("%s",info);
                adiciona_stock(info);
                break;
            }
            case 'N':
            {
                nova_enc();
                break;
            }
            case 'A':
            {
                scanf("%s",info);
                adiciona_prd(info);
                break;
            }
            case 'r':
            {
                scanf("%s",info);
                retira_stock(info);
                break;
            }
            case 'R':
            {
                scanf("%s",info);
                retira_prd(info);
                break;
            }
            case 'C':
            {
                scanf("%s",info);
                custo_enc(info);
                break;
            }
            case 'p':
            {
                scanf("%s",info);
                muda_preco(info);
                break;
            }
            case 'E':
            {
                scanf("%s",info);
                prd_em_enc(info);
                break;
            }
            case 'm':
            {
                scanf("%s",info);
                max_prd(info);
                break;
            }
            case 'l':
            {
                l_prd_preco();
                break;
            }
            case 'L':
            {
                scanf("%s",info);
                l_prds_enc(info);
                break;
            }
            case 'x':
                return EXIT_SUCCESS;
        }
        getchar(); /*\n */
        igb = 0; /* Reset do contador global */
    }
    
    return EXIT_FAILURE;
}


  /*---------------------*/
 /* Funcoes de Comandos */
/*---------------------*/

/* Adicao de novos produtos ao sistema - a */
void novo_prd(char info[])
{
    prd novo;

    /* Descricao do produto */
    for(igb = 0; info[igb] != SEPARA && igb < ENTRADA; igb++)
        novo.desc[igb] = info[igb];
    
    novo.desc[igb] = '\0'; 

    /* Caracteristicas do produto */
    novo.preco = inteiro(info); novo.peso = inteiro(info);
    novo.stock = inteiro(info); novo.id = idp_gb;

    printf("Novo produto %d.\n", novo.id);

    memoriaPRD[idp_gb++] = novo; /* Apos a atualizacao, idp global e incrementado */
}


/* Adicao de stock a produtos existentes - q */
void adiciona_stock(char info[])
{
    /* Leitura da informacao de entrada */
    int idp = inteiro(info); int qtd = inteiro(info);

    if (idp >= idp_gb)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    else
    {
        memoriaPRD[idp].stock += qtd;
    }
}


/* Criacao de encomendas novas - N */
void nova_enc(void)
{
    enc nova;

    /* Inicializacao de uma encomenda com o seu interior vazio */
    ini_interior(nova.interior); /* Equivalente a interior[IDPMAX] = {-1} */
    nova.peso = 0;
    
    printf("Nova encomenda %d.\n", ide_gb);
    memoriaENC[ide_gb++] = nova; /* Apos instrucao, contador e incrementado */
}


/* Adicao de produtos a encomendas existentes - A */
void adiciona_prd(char info[])
{
    /* Leitura da informacao de entrada */
    int ide = inteiro(info); int idp = inteiro(info);
    int qtd = inteiro(info);

    /* Erros Possiveis */
    if (ide >= ide_gb)
        printf("Impossivel adicionar produto %d a encomenda %d. "\
        "Encomenda inexistente.\n", idp,ide);
    
    else if (idp >= idp_gb)
        printf("Impossivel adicionar produto %d a encomenda %d. "\
        "Produto inexistente.\n", idp,ide);

    else if (memoriaPRD[idp].stock < qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. "\
        "Quantidade em stock insuficiente.\n", idp,ide);
    
    else if (memoriaENC[ide].peso + (memoriaPRD[idp].peso * qtd) > PESOMAX)
        printf("Impossivel adicionar produto %d a encomenda %d. "\
        "Peso da encomenda excede o maximo de 200.\n", idp,ide);

    else
    {
        /*Update do peso da Encomenda e do stock do Produto */
        memoriaENC[ide].peso += (memoriaPRD[idp].peso * qtd); memoriaPRD[idp].stock -= qtd;

        /* Se o produto ja existe na encomenda, so se adiciona o stock */
        if (memoriaENC[ide].interior[idp] == VAZIO)
            memoriaENC[ide].interior[idp] = qtd;
        else
            memoriaENC[ide].interior[idp] += qtd;
    }
}


/* Remocao de stock de produtos - r */
void retira_stock(char info[])
{
    /* Leitura da informacao de entrada */
    int idp = inteiro(info); int qtd = inteiro(info);

    /* Erros Possiveis */
    if (idp >= idp_gb)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);

    else if (qtd > memoriaPRD[idp].stock)
        printf("Impossivel remover %d unidades do produto %d do stock." 
        " Quantidade insuficiente.\n", qtd, idp);

    else
        memoriaPRD[idp].stock -= qtd; /* Stock e atualizado */
}


/* Remocao de um produto de uma encomenda - R */
void retira_prd(char info[])
{
    /* Leitura da informacao de entrada */
    int ide = inteiro(info); int idp = inteiro(info);

    /* Erros Possiveis */
    if (ide >= ide_gb)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",
        idp,ide);

    else if (idp >= idp_gb)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",
        idp,ide);

    else
    {
        if (memoriaENC[ide].interior[idp] != VAZIO) /* Nao acontece nada se o produto nao estiver na enc */
        {
            memoriaPRD[idp].stock += memoriaENC[ide].interior[idp]; /* Stock da Enc volta a stock total */
            memoriaENC[ide].peso -= (memoriaENC[ide].interior[idp] * memoriaPRD[idp].peso); /* Peso da enc ajustado */
            memoriaENC[ide].interior[idp] = VAZIO; /* Espaco dentro da encomenda fica vazio */
        }
    }
}


/* Calculo do custo de uma encomenda - C */
void custo_enc(char info[])
{
    /* Leitura da informacao de entrada */
    int total = 0, idp, ide = inteiro(info);
    
    if (ide >= ide_gb)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);

    else
    {
        for (idp = 0; idp < idp_gb; idp++)
        {
            /* Ignora vazios */
            if (memoriaENC[ide].interior[idp] != VAZIO)
                total += (memoriaPRD[idp].preco * memoriaENC[ide].interior[idp]); /* Preco e unitario */
        }
        printf("Custo da encomenda %d %d.\n", ide, total);
    }
}


/* Alteracao do preco de um produto - p */
void muda_preco(char info[])
{
    /* Leitura da informacao de entrada */
    int idp = inteiro(info); int pnovo = inteiro (info);

    if (idp >= idp_gb)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    
    else
        memoriaPRD[idp].preco = pnovo; /* Memoria do Sistema e atualizada */
        
    
}


/* Lista a descricao e quantidade de um produto numa encomenda - E */
void prd_em_enc(char info[])
{
    /* Leitura da informacao de entrada */
    int ide = inteiro(info); int idp = inteiro(info);

    /* Erros Possiveis */
    if (ide >= ide_gb)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

    else if (idp >= idp_gb)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);

    else
    {
        /* Se for vazio, stock real e 0. */
        if (memoriaENC[ide].interior[idp] != VAZIO)
            printf("%s %d.\n", memoriaPRD[idp].desc, memoriaENC[ide].interior[idp]);
        else
            printf("%s 0.\n", memoriaPRD[idp].desc);
    }
}


/* Lista o id da encomenda em que o produto dado ocorre mais vezes - m */
void max_prd(char info[])
{
    int ide, max_ide = -1, max_stock = 0;
    /* Leitura da informacao de entrada */
    int idp = inteiro(info);

    /* Erro Possivel */
    if (idp >= idp_gb)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);

    for(ide = 0; ide < ide_gb; ide++)
    {
        /* Tambem se evita casos em que o produto nao existe na encomenda */
        if(memoriaENC[ide].interior[idp] > max_stock)
        {
            max_stock = memoriaENC[ide].interior[idp];
            max_ide = ide;
        }
    }

    /* Ignora casos em que nao existe nenhuma encomenda com o produto desejado */
    if (max_ide != -1) 
        printf("Maximo produto %d %d %d.\n", idp, max_ide, max_stock);
}


/* Lista todos os produtos do sistema por ordem crescente de preco - l */
void l_prd_preco(void)
{
    prd produto;
    int idp, preco_max = 0, total = idp_gb;

    /* Lista com uma copia de todos os produtos*/
    /* Reserva-se espaco na memoria para ter tamanho variavel */
    prd *copia_produtos = (prd*) can_fail_malloc(total * sizeof(prd));
    
    /* Retira os produtos desordenados da memoria */
    for(idp = 0; idp < idp_gb; idp++)
    {
        copia_produtos[idp] = memoriaPRD[idp];

        /* Descoberta do preco maximo */
        if (memoriaPRD[idp].preco > preco_max)
            preco_max = memoriaPRD[idp].preco;
    }

    /* Ordenacao dos prds pelo preco, de forma crescente */
    ordena_precos(copia_produtos, total, preco_max);

    /* Print do bloco com a lista */
    printf("Produtos\n");

    for(idp = 0; idp < total; idp++)
    {
        produto = copia_produtos[idp]; /* Facilita leitura */
        printf("* %s %d %d\n", produto.desc, produto.preco, produto.stock);
    }

    free(copia_produtos); /* Liberta-se Espa?o utilizado */
}


/* Lista todos os produtos de uma encomenda por ordem alfabetica - L */
void l_prds_enc(char info[])
{
    int ide, idp, idp_max;
    prd produto, copia_produtos[ENCMAX];
    int total_prd = 0; /* Total de produtos na encomenda */
    int j = 0; /* Iterador para copia_produtos */

    /* Leitura da informacao de entrada */
    ide = inteiro(info);
    
    /* Erro Possivel */
    if (ide >= ide_gb)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

    else
    {
        /* Copia dos produtos no interior de uma encomenda */
        for(idp = 0; idp < idp_gb; idp++)
        {
            /* Ignora prds vazios */
            if (memoriaENC[ide].interior[idp] != VAZIO)
            {
                copia_produtos[j++] = memoriaPRD[idp];
                total_prd++; /* Aumenta-se o total */
            }
        }

        idp_max = total_prd - 1; /* O extremo da direita e o total - 1*/

        /* Ordenacao alfabetica */
        ordena_descs(0, idp_max, copia_produtos);

        /* Print do bloco com a lista */
        printf("Encomenda %d\n", ide);

        for(idp = 0; idp <= idp_max; idp++)
        {
            produto = copia_produtos[idp]; /* Facilita leitura */

            printf("* %s %d %d\n", produto.desc, produto.preco, memoriaENC[ide].interior[produto.id]);
        }
    }
}



  /*-------------------*/
 /* Funcoes Auxiliares*/
/*-------------------*/

/* Funcao que retira um inteiro de um segmento de instrucoes dos comandos */
int inteiro(char info[])
{
    int res = 0;
    
    /* Ajusta Contador Global */
    if (info[igb] == SEPARA)
        igb++;

    for(; (info[igb] != SEPARA) && (info[igb] != '\0'); igb++)
    {
        res *= 10; res += info[igb] - ZERO;
    }
    return res;
}


/* Funcao que inicializa o interior de uma encomenda como "vazio" */
void ini_interior(int interior[])
{
    int idp;

    /* Como convencao para inexistente, teremos a quantidade de cada idp a -1 */
    for (idp = 0; idp <= IDPMAX; idp++)
        interior[idp] = -1;
}


/* Ordena um array de produtos de forma crescente de preco. Utiliza countingsort. */
void ordena_precos(prd prds[], int n, int max)
{
    int i; /* Coloca-se maximo como primeiro preco */

    /* Arrays alocados dinamicamente */
    prd *ordenado = can_fail_malloc(n * sizeof(prd)); /* Array que ira conter produtos ordenados */
    int *conta = can_fail_calloc(max + 1, sizeof(int)); /*Tamanho maximo de chaves diferentes - inicializado a 0 */

    /* Incrementacao na lista com chaves para cada preco correspondente a chave */
    for (i = 0; i < n; i++)
    {
        conta[prds[i].preco]++;
    }

    /* Ajuste do array de chaves com a soma do index posterior */
    for (i = 1; i <= max; i++)
    {
        conta[i] += conta[i - 1];
    }

    /* Correspondencia entre lista original com array de chaves */
    for (i = n - 1 ; i >= 0; i--)
    {
        ordenado[conta[prds[i].preco] - 1] = prds[i];
        conta[prds[i].preco]--; /* Decrementacao da chave */
    }

    /* Substituicao do original pelo agora ordenado */
    for (i = n - 1; i >= 0; i--)
    {
        prds[i] = ordenado[i];
    }
    
    free(conta); free(ordenado); /* Libertacao da memoria alocada */
}


/* Ordena um array de produtos de forma alfabetica de descricao. Utiliza mergesort. */
void ordena_descs(int esq, int dir, prd prds[])
{
    int med = (esq + dir) / 2; /* Ponto media da lista dada */

    if (dir <= esq)
        return; /* Fim de Recursao */

    /* Recursao */
    ordena_descs(esq, med, prds);
    ordena_descs(med+1, dir, prds);
    merge_desc(esq, med, dir, prds); 
}


/* Aux da ordenacao por desc */
void merge_desc(int esq, int med, int dir, prd prds[])
{
    prd prds_aux[ENCMAX]; /* Tamanho da auxiliar = tamanho maximo */
    int i, j, k;

    for (i = med+1; i > esq; i--) /* Split da esquerda */
        prds_aux[i-1] = prds[i-1];
    
    for (j = med; j < dir; j++) /* Split da direita */
        prds_aux[dir + med-j] = prds[j+1];

    for (k = esq; k <= dir; k++) /* Ordenacao da auxiliar para principal pelas pontas */
    {
        /* Strcmp devolve um valor negativo se o primeiro caracter ASCII diferente
        tem um valor menor na primeira str do que na segunda str */ 

        if (strcmp(prds_aux[j].desc, prds_aux[i].desc) < 0 || i > med) /* Descs diferentes */
            prds[k] = prds_aux[j--];
        else
            prds[k] = prds_aux[i++];
    }  
} 