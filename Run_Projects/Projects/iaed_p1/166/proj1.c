#include <stdio.h>
#include <string.h>

/* Numero maximo de caracteres na string de descricao */
#define MAX_DESC 63
/* Peso maximo de uma encomenda */
#define MAX_PESO 200
/* Numero maximo de produtos */
#define MAX_PROD 10000
/* Numero maximo de encomendas */
#define MAX_ENCO 500
/* Menos Um */
#define MENOS_UM -1;
/* Zero */
#define ZERO 0
/* Um */
#define UM 1
/* Caracter_Comando_q */
#define OPERACAO_q 'q'
/* Caracter_Comando_q */
#define OPERACAO_r 'r'

/* Estrutura de qualquer produto no sistema*/
typedef struct Produto
{
    int Idp; /* Identificador do produto */
    char Descricao[MAX_DESC]; /* String que contem a descricao */
    int Preco; /* Preco do produto */
    int Peso; /* Peso do produto */
    int Stock; /* Stock do produto */
}produto;

/* Estrutura de qualquer encomenda no sistema */
typedef struct Encomenda
{
    int Ide; /* Identificador da encomenda */
    produto Lista_Produtos[MAX_PESO]; /* Vetor que contem os produtos na encomenda */
    int Contador; /* Contador --> Posicao no vetor do ultimo produto inserido */
}encomenda;

/* Vari?veis Globais */
/* Os contadores sao inicializados a -1 para que os valores sejam atuais */
int IdentProduto = MENOS_UM /* Contador de IDP */
int IdentEncom = MENOS_UM /* Contador de IDE */
produto VetorProdutos[MAX_PROD]; /* Vetor para armazenar produtos */
encomenda VetorEncomendas[MAX_ENCO]; /* Vetor para armazenar encomendas */

/* Esta funcao le e devolve o caracter inicial */
char LeCaracterInicial()
{
    char CaracterInicial;
    scanf("%c", &CaracterInicial); /* le o carcter */
    return CaracterInicial; /* retorna o caracte */
}

/* Funcao auxiliar ao comando q e comando r */
void Aux_q_r(int idp, int qtd, char operacao)
{
    int i;
    produto Produto_Aux; /* Produto auxiliar */
    for (i = ZERO; i <= IdentProduto; i++) /* Ciclo para percorrer VetorProdutos */
    {
        Produto_Aux = VetorProdutos[i]; /* Produto aux e o produto na posicao i */
        if (Produto_Aux.Idp == idp) /* Se o produto for o referido */
        {
            if (operacao == OPERACAO_q) /* Se o comando for o q */
            {
                Produto_Aux.Stock = Produto_Aux.Stock + qtd; /* O stock e aumentado */
                VetorProdutos[idp] = Produto_Aux; /* O produto em VetorProdutos e atualizado */
            }
            else if (operacao == OPERACAO_r) /* Se o comando for o r */
            {
                Produto_Aux.Stock = Produto_Aux.Stock - qtd; /* O stock e reduzido */
                VetorProdutos[idp] = Produto_Aux; /* O produto em VetorProdutos e atualizado */
            }
            break; /* Nao e preciso continuar o ciclo */
        }
    }
}

/* Funcao auxiliar para calcular o peso de uma dada encomenda */
int Calcula_Peso(int ide)
{
    int i, Peso = ZERO; /* Peso inicial e zero */
    encomenda Encomenda_aux = VetorEncomendas[ide]; /* Encomenda auxiliar */
    for (i = ZERO; i <= Encomenda_aux.Contador; i++) /* Ciclo para percorrer a lista de produtos de uma encomenda */
    {
        Peso = Peso + (Encomenda_aux.Lista_Produtos[i].Peso * Encomenda_aux.Lista_Produtos[i].Stock); /* Soma o peso dos produtos ao total */
    }
    return Peso; /* Retorna o Peso total de uma encomenda */
}

/* Esta funcao e chamada quando e lido o caracter a - cria uma novo produto */
void Comando_a()
{
    produto NovoProduto; /* Cria o novo produto */
    IdentProduto++; /* O contador e incrementado no inicio para que o valor seja atual */
    scanf(" %[^:]:%d:%d:%d", NovoProduto.Descricao, &NovoProduto.Preco, &NovoProduto.Peso, &NovoProduto.Stock); /* Le o input depois de a */
    NovoProduto.Idp = IdentProduto; /* Define o idp do produto */
    VetorProdutos[IdentProduto] = NovoProduto; /* Guarda o produto em VetorProdutos na posicao idp */ 
    printf("Novo produto %d.\n", IdentProduto); /* Printf do output */
}

/* Esta funcao e chamada quando e lido o caracter q - adiciona stock a um produto */
void Comando_q()
{
    int idp_q, qtd_q; /* Inicializacao de variaveis para guardar os valores do scanf */
    scanf(" %d:%d", &idp_q, &qtd_q); /* Le o input depois de q */
    if (idp_q > IdentProduto) /* Se o idp for maior do que IdentProduto entao o produto n existe */
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_q); /* Printf do erro */
    }
    else
    {
        Aux_q_r(idp_q, qtd_q, OPERACAO_q); /* Chama a funcao auxiliar */
    }
}

/* Esta funcao e chamada quando e lido o caracter N - cria uma nova encomenda */
void Comando_N()
{
    int i; 
    encomenda NovaEncomenda; /* Cria uma nova encomenda */
    IdentEncom++; /* O contador e incrementado no inicio para que o valor seja atual */
    for (i = ZERO; i < MAX_PESO; i++) /* Ciclo para iniciar todos os produtos com Stock 0 */
    {
        NovaEncomenda.Lista_Produtos[i].Stock = ZERO; /* Stock = 0 --> Produto n esta na encomenda */
    }
    NovaEncomenda.Ide = IdentEncom; /* Define o ide do produto */
    NovaEncomenda.Contador = MENOS_UM; /* Inicia o contador a -1 --> Valores atuais */
    VetorEncomendas[IdentEncom] = NovaEncomenda; /* Guarda a encomenda em VetorEncomendas na posicao ide */
    printf("Nova encomenda %d.\n", IdentEncom); /* Printf do output */
}

/* Esta funcao e chamada quando e lido o caracter A - adiciona um produto a uma encomenda */
void Comando_A()
{
    int ide_A, idp_A, qtd_A, i, dentro = ZERO; /* Inicializacao de variaveis */
    encomenda Encomenda_A; /* Encomenda auxiliar */
    produto Produto_A; /* Produto auxiliar */
    scanf(" %d:%d:%d", &ide_A, &idp_A, &qtd_A); /* Le o input depois de q */
    Produto_A = VetorProdutos[idp_A]; /* Produto_A e o produto referida */
    Encomenda_A = VetorEncomendas[ide_A]; /* Encomenda_A e a encomenda referida */
    if (ide_A > IdentEncom) /* Se o ide for maior do que IdentEncom entao o produto n existe */
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_A, ide_A); /* Printf do erro */
    }
    else if (idp_A > IdentProduto) /* Se o idp for maior do que IdentProduto entao o produto n existe */
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_A, ide_A); /* Printf do erro */
    }
    else if (VetorProdutos[idp_A].Stock < qtd_A) /* Se o stock nao for suficiente */
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_A, ide_A); /* Printf do erro */
    }
    else if ((Calcula_Peso(ide_A) + (qtd_A * VetorProdutos[idp_A].Peso) > MAX_PESO)) /* Se o peso exceder 200 */
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_A, ide_A); /* Printf do erro */
    }
    else
    {
        for (i = ZERO; i <= Encomenda_A.Contador; i++) /* Ciclo para percorrer produtos na Encomenda_A */
        {
            if (Encomenda_A.Lista_Produtos[i].Idp == idp_A) /* Se o produto referido ja estiver na encomenda */ 
            {
                Encomenda_A.Lista_Produtos[i].Stock = Encomenda_A.Lista_Produtos[i].Stock + qtd_A; /* Soma-se qtd ao stock */
                dentro = UM; /* Sinaliza-se que o produto ja esta na encomenda */
                break; /* Ja nao e preciso continuar o ciclo */
            }
        }
        if (dentro != UM) /* Se o produto ainda nao estiver na encomenda */
        {
            Encomenda_A.Contador++; /* Contador da encomenda e incrementado */
            Encomenda_A.Lista_Produtos[Encomenda_A.Contador] = Produto_A; /* Produto e guardado em Lista_Produtos */
            Encomenda_A.Lista_Produtos[Encomenda_A.Contador].Stock = qtd_A; /* O stock e qtd */
        }
        Produto_A.Stock = Produto_A.Stock - qtd_A; /* O stock e sempre reduzido */
        VetorEncomendas[ide_A] = Encomenda_A; /* A encomenda em VetorEncomendas e atualizada */
        VetorProdutos[idp_A] = Produto_A; /* O produto em VetorProdutos e atualizado */
    }
}

/* Esta funcao e chamada quando e lido o caracter r - remove stock a um produto */
void comando_r()
{
    int idp_r, qtd_r; /* Inicializacao de variaveis para guardar os valores do scanf */
    scanf(" %d:%d", &idp_r, &qtd_r); /* Le o input a seguir ao r */
    if (idp_r > IdentProduto) /* Se o idp for maior do que IdentProduto entao o produto n existe */
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_r); /* Printf do erro */
    }
    else if (VetorProdutos[idp_r].Stock - qtd_r < ZERO) /* Se o stock do produto for insuficiete */
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd_r, idp_r); /* Printf do erro */
    }
    else
    {
        Aux_q_r(idp_r, qtd_r, OPERACAO_r); /* Chamada da funcao auxiliar */
    }
}

/* Esta funcao e chamada quando e lido o caracter R - remove um produto de uma encomenda */
void comando_R()
{
    int ide_R, idp_R, i; /* Inicializacao de variaveis para guardar os valores do scanf */
    encomenda Encomenda_R; /* Encomenda auxiliar */
    produto Produto_R; /* Produto auxiliar */
    scanf(" %d:%d", &ide_R, &idp_R); /* Le o input a seguir ao R */
    Encomenda_R = VetorEncomendas[ide_R]; /* Encomenda_R e a encomenda referida */
    Produto_R = VetorProdutos[idp_R]; /* Produto_R e o produto referido */
    if (ide_R > IdentEncom) /* Se o ide for maior do que IdentEncom entao a encomenda n existe */
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp_R, ide_R); /* Printf do erro */
    }
    else if (idp_R > IdentProduto) /* Se o idp for maior do que IdentProduto entao o produto n existe */
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp_R, ide_R); /* Printf do erro */
    }
    else
    {
        for (i = ZERO; i <= Encomenda_R.Contador; i++) /* Ciclo para percorrer a lista de produtos da encomenda */
        {
            if (Encomenda_R.Lista_Produtos[i].Idp == idp_R) /* Se o idp for o referido */
            {
                Produto_R.Stock = Produto_R.Stock + Encomenda_R.Lista_Produtos[i].Stock; /* O stock do produto na encomenda e devolvido */
                Encomenda_R.Lista_Produtos[i].Stock = ZERO; /* O produto deixa de estar na encomenda, logo o stock passa a 0 */
                break; /* Ja nao e preciso continuar o ciclo */
            }
        }
        VetorEncomendas[ide_R] = Encomenda_R; /* A encomenda em VetorEncomendas e atualizado */
        VetorProdutos[idp_R] = Produto_R; /* O produto em VetorProdutos e atualizado */
    }
}

/* Esta funcao e chamada quando e lido o caracter C - calcula o custo de uma encomenda */
void Comando_C()
{
    int ide_C, i, PrecoEncomenda = ZERO; /* Inicializacao de variaveis de estado, iteracao e armazenamento */
    encomenda Encomenda_C; /* Encomenda auxiliar */
    produto Produto_C; /* Produto auxiliar */
    scanf(" %d", &ide_C); /* Le o input */
    Encomenda_C = VetorEncomendas[ide_C]; /* Encomenda_C e a encomenda referida */
    if (ide_C > IdentEncom) /* Se o ide for maior do que IdentEncom entao a encomenda n existe */
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide_C); /* Printf do erro */
    }
    else
    {
        for (i = ZERO; i <= Encomenda_C.Contador; i++) /* Ciclo para percorrer a lista de produtos na encomenda */
        {
            Produto_C = Encomenda_C.Lista_Produtos[i]; /* Uso do produto auxiliar */
            PrecoEncomenda = PrecoEncomenda + (Produto_C.Stock * Produto_C.Preco); /* Soma o custo dos produtos ao total */
        }        
        printf("Custo da encomenda %d %d.\n", ide_C, PrecoEncomenda); /* Printf do output */
    }
}

/* Esta funcao e chamada quando e lido o caracter p - altera o preco de um dado produto */
void Comando_p()
{
    int idp_p, preco_p, i, k; /* Inicializacao de variaveis de memoria e iteracao */
    encomenda Encomenda_p; /* Encomenda auxiliar */
    produto Produto_p; /* Produto auxiliar */
    scanf(" %d:%d", &idp_p, &preco_p); /* Le o input */
    Produto_p = VetorProdutos[idp_p]; /* Produto_p e o produto referido */
    if (idp_p > IdentProduto) /* Se o idp for maior do que IdentProduto entao o produto n existe */
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_p); /* Printf do erro */
    }
    else
    {
        Produto_p.Preco = preco_p; /* Preco e alterado */
        VetorProdutos[idp_p] = Produto_p; /* O produto em VetorProdutos e atualizado */
        for (i = ZERO; i <= IdentEncom; i++) /* Ciclo para percorrer todas as encomendas */
        {
            Encomenda_p = VetorEncomendas[i]; /* Uso da encomenda auxiliar */
            for (k = ZERO; k <= Encomenda_p.Contador; k++) /* Ciclo para percorrer os produtos na encomenda */
            {
                if (Encomenda_p.Lista_Produtos[k].Idp == idp_p) /* Se os idp for o dado */
                {
                    Encomenda_p.Lista_Produtos[k].Preco = preco_p; /* O preco e alterado */
                }
            }
            VetorEncomendas[i] = Encomenda_p; /* A encomenda em VetorEncomendas e atualizada */
        }
    }
}

/* Esta funcao e chamada quando e lido o caracter E - retorna a descricao e a quantidade de um produto numa encomenda */
void Comando_E()
{
    int ide_E, idp_E, i, dentro = ZERO; /* Inicializacao de variaveis de armazenamento, estado e iteracao */
    encomenda Encomenda_E; /* Encomenda auxiliar */
    produto Produto_E; /* Produto auxiliar */
    scanf(" %d:%d", &ide_E, &idp_E); /* Le o input */
    Encomenda_E = VetorEncomendas[ide_E]; /* Encomenda_E e a encomenda referida */
    Produto_E = VetorProdutos[idp_E]; /* Produto_E e o produto referido */
    if (ide_E > IdentEncom) /* Se o ide for maior do que IdentEncom entao a encomenda n existe */
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_E); /* Printf do erro */
    }
    else if (idp_E > IdentProduto) /* Se o idp for maior do que IdentProduto entao o produto n existe */
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp_E); /* Printf do erro */
    }
    else
    {
        for (i = ZERO; i <= Encomenda_E.Contador; i++) /* Percorre a encomenda */
        {
            if (Encomenda_E.Lista_Produtos[i].Idp == idp_E) /* Se o idp for o referido */
            {
                printf("%s %d.\n", Encomenda_E.Lista_Produtos[i].Descricao, Encomenda_E.Lista_Produtos[i].Stock); /* Printf do output */
                dentro = UM; /* O produto esta na encomenda */
                break; /* Ja nao e preciso percorrer o ciclo */
            }
        }
        if (dentro == ZERO) /* Se o produto nao estiver na encomenda */
        {
            printf("%s %d.\n", Produto_E.Descricao, ZERO); /* Printf do output */
        } 
    } 
}

/* Esta funcao e chamada quando e lido o caracter m - retorna o ide da encomenda onde um produto ocorre mais vezes */
void Comando_m()
{
    int idp_m, i, k, Stock_max = ZERO, dentro = ZERO; /* Variaveis de armazenamento, estado e iteracao */
    encomenda Encomenda_m, Encomenda_max; /* Encomendas auxiliares */
    produto Produto_m; /* Produtos auxiliar */
    scanf(" %d", &idp_m); /* Le o input */
    if (idp_m > IdentProduto) /* Se o idp for maior do que IdentProduto entao o produto n existe */
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_m); /* Printf do erro */
    }
    else
    {
        for (i = ZERO; i <= IdentEncom; i++) /* Ciclo para percorrer todas as encomendas */
        {
            Encomenda_m = VetorEncomendas[i]; /* Uso da encomenda auxiliar */
            for (k = ZERO; k <= Encomenda_m.Contador; k++) /* Ciclo para percorrer a lista de produtos da encomenda */ 
            {
                Produto_m = Encomenda_m.Lista_Produtos[k]; /* Uso do produto auxiliar */
                if (Produto_m.Idp == idp_m && Produto_m.Stock > ZERO) /* Se o produto for o referido e existir na encomenda */
                {
                    dentro = UM; /* O produto esta em pelo menos uma encomenda */
                    if (Produto_m.Stock > Stock_max) /* Se o stock for superior ao meximo verificado */
                    {
                        Stock_max = Produto_m.Stock; /* O stock maximo e substituido */
                        Encomenda_max = Encomenda_m; /* A encomenda com o maior stock e atualizada */
                    }
                }
            }
        }
    }
    if (IdentEncom >= ZERO && dentro == UM) /* Se houver encomendas e se o produto estiver em alguma */
    {
        printf("Maximo produto %d %d %d.\n", idp_m, Encomenda_max.Ide, Stock_max); /* Printf do output */
    }
}

/* Esta funcao e chamada quando e lido o caracter l - lista todos os produtos existentes por ordem crescente de pre?o, usando o selection sort*/
void Comando_l()
{
    int l, i, j, k;
    produto Vetor_Copia[MAX_PROD]; /* Vetor de produtos auxiliar */
    for (l = ZERO; l <= IdentProduto; l++) /* Ciclo para copiar os conteudos de VetorProdutos para o vetor auxiliar */
    {
        Vetor_Copia[l] = VetorProdutos[l];
    }
    printf("Produtos\n");
    for (i = ZERO; i < IdentProduto; i++) /* Selection Sort */
    {
        produto aux; int min = i;
        for (j = i+UM; j <= IdentProduto ; j++)
        {
            if (Vetor_Copia[j].Preco < Vetor_Copia[min].Preco) /* Compara os precos */
            {
                min = j; /* Troca o minimo */
            }
        }
        aux = Vetor_Copia[i]; Vetor_Copia[i] = Vetor_Copia[min]; Vetor_Copia[min] = aux; /* Troca de valores */
    }
    for (k = ZERO; k <= IdentProduto; k++) /* Ciclo para percorrer o Vetor_Copia */
    {
        printf("* %s %d %d\n", Vetor_Copia[k].Descricao, Vetor_Copia[k].Preco, Vetor_Copia[k].Stock);
    } 
}

/* Esta funcao e chamada quando e lido o caracter L - lista todos os produtos de uma encomenda por ordem alfabetica da descricao, usando o selection sort */
void Comando_L()
{
    int ide_L, i, j, k, l;
    produto Produtos_ide[MAX_PESO], Produto_L; /* Produto e vetor de produtos auxiliares */
    scanf(" %d", &ide_L); /* Le o input */
    if (ide_L > IdentEncom) /* Se o ide for maior do que IdentEncom entao a encomenda n existe */
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_L); /* Printf do erro */
    }
    else
    {
        for (i = 0; i <= VetorEncomendas[ide_L].Contador; i++) /* Ciclo para copiar os produtos para um vetor auxiliar */
        {   
            Produtos_ide[i] = VetorEncomendas[ide_L].Lista_Produtos[i];
        }
        printf("Encomenda %d\n", ide_L);
        for (j = 0; j < VetorEncomendas[ide_L].Contador ; j++) /* Selection Sort */
        {
            produto aux; int min = j;
            for (k = j+UM; k <= VetorEncomendas[ide_L].Contador; k++)
            {
                if (strcmp(Produtos_ide[k].Descricao, Produtos_ide[min].Descricao) < 0) /* Compara as descricoes */
                {
                    min = k; /* Troca o minimo */
                }
            }
            aux = Produtos_ide[j]; Produtos_ide[j] = Produtos_ide[min]; Produtos_ide[min] = aux; /* Troca de valores */
        }
        for (l = 0; l <= VetorEncomendas[ide_L].Contador; l++) /* Ciclo para percorrer Produtos_ide */
        {
            if (Produtos_ide[l].Stock > 0) /* Se o produto existir na encomenda */
            {
                Produto_L = Produtos_ide[l];
                printf("* %s %d %d\n", Produto_L.Descricao, Produto_L.Preco, Produto_L.Stock); /* Printf do output */
            }
        }
    }
}

/* Funcao principal - Main */
int main()
{
    char Comando = LeCaracterInicial(); /* Le o caracter inicial */
    while (Comando != 'x') /* Se o comando nao for x */
    {
        switch (Comando)
        {
        case 'a':
            Comando_a();
            break;

        case 'q':
            Comando_q();
            break;

        case 'N':
            Comando_N();
            break;

        case 'A':
            Comando_A();
            break;
        
        case 'r':
            comando_r();
            break;

        case 'R':
            comando_R();
            break;

        case 'C':
            Comando_C();
            break;

        case 'p':
            Comando_p();
            break;
        
        case 'E':
            Comando_E();
            break;
        
        case 'm':
            Comando_m();
            break;

        case 'l':
            Comando_l();
            break;
        
        case 'L':
            Comando_L();
            break;
        
        default:
            break;
        }
        Comando = LeCaracterInicial(); /* Le o procimo caracter */
    }
    return 0;
}