#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "estruturas.h"

void A_add_equipa(int cont, NodeE **tabelaE);
/* adiciona uma equipa, recebendo um nome e com as vitorias a 0 */
NodeJ *a_add_jogo(int cont, NodeJ **tabelaJ, NodeE **tabelaE, NodeJ **cauda, NodeJ *cabeca);
/* adiciona um jogo, recebendo o seu nome, os nomes das duas equipas envolventes e quantos golos marcou cada uma, atualizando as vitorias */
void l_listaJ_data(int cont, NodeJ *cabecaJ);
/* imprime os jogos por ordem de antiguidade */
void p_procura_jogo(int cont, NodeJ **tabelaJ);
/* recebendo um nome, imprime o jogo com esse mesmo nome */ 
void P_procura_equipa(int cont, NodeE **tabelaE);
/* recebendo um nome, imprime a equipa que tem esse nome */
NodeJ *r_remove_jogo(int cont, NodeJ **tabelaJ, NodeJ *cabecaJ, NodeJ **caudaJ, NodeE **tabelaE);
/* recebendo um nome, remove o jogo que tem esse nome, assim como atualiza as vitorias das equipas intervenientes se for caso para tal */
void s_altera_resultado(int cont, NodeJ **tabelaJ, NodeE **tabelaE);
/* recebendo o nome do jogo, altera o resultado assim como as vitorias das equipas envolventes, se for caso para tal */
void g_encontra_mais_vitorias(int cont, NodeE **tabelaE);
/* imprime as equipas com mais vitorias por ordem lexicografica */

int main()
{
    char n;
    int cont = 1;
    /* inicializacoes das tabelas e linked lists */
    NodeE **tabelaE = init_hash_tableE();
    NodeJ **tabelaJ = init_hash_tableJ();
    NodeJ *cabecaJ = NULL;
    NodeJ *caudaJ = NULL;
    n = getchar();
    while(n != 'x')
    {
        switch(n)
        {
            case 'a':
                cabecaJ = a_add_jogo(cont++, tabelaJ, tabelaE, &caudaJ, cabecaJ);
                break;
            case 'A':
                A_add_equipa(cont++, tabelaE);
                break;
            case 'l':
                l_listaJ_data(cont++, cabecaJ);
                break;
            case 'p':
                p_procura_jogo(cont++, tabelaJ);
                break;
            case 'P':
                P_procura_equipa(cont++, tabelaE);
                break;
            case 'r':
                cabecaJ = r_remove_jogo(cont++, tabelaJ, cabecaJ, &caudaJ, tabelaE);
                break;
            case 's':
                s_altera_resultado(cont++, tabelaJ, tabelaE);
                break;
            case 'g':
                g_encontra_mais_vitorias(cont++, tabelaE);
                break;
        }
    n = getchar();
    }
    /* liberta os jogos e as equipas alocadas atraves das tabelas */
    free_tabelaE(tabelaE);
    free_tabelaJ(tabelaJ);
    return 0;
}

void A_add_equipa(int cont, NodeE **tabelaE)
{
    char nome[MAX_NOME];
    scanf(" %[^:\n]", nome);
    /* verificacoes */
    if(encontra_tabelaE(tabelaE, nome) != NULL)
        printf("%d Equipa existente.\n", cont);
    else
        hash_table_insertE(tabelaE, nome, 0);
}

NodeJ *a_add_jogo(int cont, NodeJ **tabelaJ, NodeE **tabelaE, NodeJ **caudaJ, NodeJ *cabecaJ)
{
    char nomej[MAX_NOME], nome1[MAX_NOME], nome2[MAX_NOME];
    int res1, res2;
    NodeE *equipa1, *equipa2;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nomej, nome1, nome2, &res1, &res2);
    equipa1 = encontra_tabelaE(tabelaE, nome1);
    equipa2 = encontra_tabelaE(tabelaE, nome2);
    /* verificacoes */
    if(encontra_tabelaJ(tabelaJ, nomej) != NULL)
        printf("%d Jogo existente.\n", cont);
    else if((equipa1 == NULL) || (equipa2 == NULL))
        printf("%d Equipa inexistente.\n", cont);
    else
    {
        cabecaJ = insertEnd_listaJ(cabecaJ, caudaJ, tabelaJ, nomej, nome1, nome2, res1, res2);
        /* atualiza as vitorias */
        if(res1>res2)
            equipa1->vitorias += 1;
        else if (res1<res2)
            equipa2->vitorias += 1;
    }
    return cabecaJ;
}

void l_listaJ_data(int cont, NodeJ *cabecaJ)
{
    print_listaJ(cont, cabecaJ);
}

void p_procura_jogo(int cont, NodeJ **tabelaJ)
{
    char nome[MAX_NOME];
    NodeJ *jogo;
    scanf(" %[^:\n]", nome);
    jogo = encontra_tabelaJ(tabelaJ, nome);
    /* verificacoes */
    if (jogo == NULL)
        printf("%d Jogo inexistente.\n", cont);
    else
        print_jogo(cont, jogo);
}

void P_procura_equipa(int cont, NodeE **tabelaE)
{
    char nome[MAX_NOME];
    NodeE *equipa;
    scanf(" %[^:\n]", nome);
    equipa = encontra_tabelaE(tabelaE, nome);
    /* verificacoes */
    if(equipa == NULL)
        printf("%d Equipa inexistente.\n", cont);
    else
        print_equipa(cont, equipa);
}

NodeJ *r_remove_jogo(int cont, NodeJ **tabelaJ, NodeJ *cabecaJ, NodeJ **caudaJ, NodeE **tabelaE)
{
    char nome[MAX_NOME];
    NodeJ *jogo;
    NodeE *equipa1, *equipa2;
    scanf(" %[^:\n]", nome);
    jogo = encontra_tabelaJ(tabelaJ, nome);
    /* verificacoes */
    if(jogo == NULL)
        printf("%d Jogo inexistente.\n", cont);
    else
    {
        equipa1 = encontra_tabelaE(tabelaE, jogo->casa);
        equipa2 = encontra_tabelaE(tabelaE, jogo->fora);
        /* atualiza as vitorias */
        if(jogo->resCasa > jogo->resFora)
            equipa1->vitorias -= 1;
        else if (jogo->resFora > jogo->resCasa)
            equipa2->vitorias -= 1;
        /* so depois remove o jogo da lista */
        cabecaJ = remove_listaJ(cabecaJ, caudaJ, tabelaJ, jogo->nome);
    }
    return cabecaJ;
}

void s_altera_resultado(int cont, NodeJ **tabelaJ, NodeE **tabelaE)
{
    char nome[MAX_NOME];
    int score1, score2;
    NodeJ *jogo;
    NodeE *equipaCasa, *equipaFora;
    scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);
    jogo = encontra_tabelaJ(tabelaJ, nome);
    /* verificacoes */
    if(jogo == NULL)
        printf("%d Jogo inexistente.\n", cont);
    else
    {
        equipaCasa = encontra_tabelaE(tabelaE, jogo->casa);
        equipaFora = encontra_tabelaE(tabelaE, jogo->fora);
        if ((jogo->resCasa > jogo->resFora) && (score1 <= score2))
        /* se a equipa da casa afinal nao ganhou */
        {
            equipaCasa->vitorias -= 1;
            if(score1 < score2)
                equipaFora->vitorias += 1;
        }
        else if((jogo->resCasa < jogo->resFora) && (score1 >= score2))
        /* se a equipa visitante tinha ganho mas com a alteracao ja nao */
        {
            equipaFora->vitorias -= 1;
            if(score1 > score2)
                equipaCasa->vitorias += 1;
        }
        /* se o jogo era um empate */
        else if (jogo->resCasa == jogo->resFora)
        {    
            if(score1 > score2)
                equipaCasa->vitorias += 1;
            else if(score1 < score2)
                equipaFora->vitorias += 1;
        }
        jogo->resCasa = score1;
        jogo->resFora = score2;
    }
}

/* funcao comparadora para o qsort */
int comparador_de_strings(const void *x, const void *y)
{
    char **pont1 = (char **) x, **pont2 = (char **) y;
    return strcmp(*pont1, *pont2) > 0;
}


void g_encontra_mais_vitorias(int cont, NodeE **tabelaE)
{
    int i = 0, n = 0, max = 0, k;
    char **vector;
    NodeE *t;
    for (i = 0; i < TAM_HASH; i++) /* para todos os indices da tabela */
    {
        if(tabelaE[i] != NULL) /* que estejam ocupados */
        {   
            t = tabelaE[i];
            while(t != NULL) /* percorremos a lista encadeada que corresponde ao indice */
            {
                if(t->vitorias == max) 
                /* se o numero de vitorias da equipa for igual ao valor de max, somo 1 ao n */
                {
                    n += 1;
                }
                else if(t->vitorias > max)
                /* se for maior, atualizo o valor de max */
                {
                    max = t->vitorias;
                    n = 1;
                }
            t = t->next;
            }
        }
    }
    vector = can_fail_malloc(n * sizeof(char*));
    n = 0;
    for (i = 0; i < TAM_HASH; i++) /* para todos os indices da tabela */
    {
        if(tabelaE[i] != NULL) /* que estejam ocupados */
        {   
            t = tabelaE[i];
            while(t != NULL) /* percorremos a lista encadeada que corresponde ao indice */
            {
                if(t->vitorias == max) 
                /* se o numero de vitorias da equipa for igual ao valor de max, insiro o nome no vetor */
                {
                    vector[n] = t->nome;
                    n += 1;
                }
            t = t->next;
            }
        }
    }
    if (n)
    /* ordena os testes lexicograficamente */
    {
        qsort(vector, n, sizeof(char *), comparador_de_strings);
        printf("%d Melhores %d\n", cont, max);
        for(k = 0; k < n; k++)
        {
            printf("%d * %s\n", cont, vector[k]);
        }
    }
    /* apos dar print, liberta o vetor */
    free(vector);
}