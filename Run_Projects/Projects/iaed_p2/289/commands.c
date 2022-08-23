#include "commands.h"

/* Comando a recebe um novo nome para um jogo, os nomes de duas equipas e os
 * scores das respetivas equipas e guarda o jogo na Lista jogos e na Hash jogos,
 * caso nao exista uma ou as duas equipas retorna um erro, caso ja exista
 * um jogo com o mesmo nome tambem retorna erro */
void cmd_a(link_jg *heads_jg, link_eq *heads_eq, list *jogos, int M, int m, int NL)
{
    char nome_jogo[MAXNOME], nome1[MAXEQUIPA], nome2[MAXEQUIPA];
    int score1 = 0, score2 = 0;
    ptr_equipa equipa1 = NULL, equipa2 = NULL;
    link_jogo novo_jogo = NULL;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome_jogo, nome1, nome2, &score1, &score2);
    equipa1 = HT_eq_search(nome1, heads_eq, m);
    equipa2 = HT_eq_search(nome2, heads_eq, m);
    if (HT_jg_search(nome_jogo, heads_jg, M) != NULL)
    {
        printf("%d Jogo existente.\n", NL);
    }
    else if (equipa1 == NULL || equipa2 == NULL)
    {
        printf("%d Equipa inexistente.\n", NL);
    }
    else
    {
        novo_jogo = LS_jg_insert(newJogo(nome_jogo, equipa1, equipa2, score1, score2), jogos);
        HT_jg_insert(novo_jogo, heads_jg, M);
        if (score1 > score2)
        {
            equipa1->jogos_ganhos++;
        }
        if (score2 > score1)
        {
            equipa2->jogos_ganhos++;
        }
    }
}

/* Comando l lista os jogos por ordem de entrada de input */
void cmd_l(list *jogos, link_jg *heads_jg, int M, int NL)
{
    link_jogo t, a;
    for (t = jogos->head; t != NULL; t = t->next)
    {
        a = HT_jg_search(t->jogo->nome, heads_jg, M);
        printf("%d %s %s %s %d %d\n", NL, a->jogo->nome, a->jogo->equipa1->nome,
               a->jogo->equipa2->nome, a->jogo->score1, a->jogo->score2);
    }
}

/* Comando p recebe um nome de um jogo e procura esse jogo,
 * caso esse jogo nao exista retorna erro, caso contrario
 * retorna o o jogo e as suas componentes */
void cmd_p(link_jg *heads_jg, int M, int NL)
{
    char nome_jogo[MAXNOME];
    link_jogo a = NULL;
    scanf(" %[^:\n]", nome_jogo);
    a = HT_jg_search(nome_jogo, heads_jg, M);
    if (a == NULL)
    {
        printf("%d Jogo inexistente.\n", NL);
    }
    else
    {
        printf("%d %s %s %s %d %d\n", NL, a->jogo->nome, a->jogo->equipa1->nome,
               a->jogo->equipa2->nome, a->jogo->score1, a->jogo->score2);
    }
}

/* Comando r recebe um nome de um jogo e remove esse jogo
 * caso esse jogo nao exista retorna erro, caso contrario
 * remove o jogo da Hash jogos e da Lista jogos */
void cmd_r(link_jg *heads_jg, list *jogos, int M, int NL)
{
    char nome_jogo[MAXNOME];
    link_jogo a = NULL;
    scanf(" %[^:\n]", nome_jogo);
    a = HT_jg_search(nome_jogo, heads_jg, M);
    if (a == NULL)
    {
        printf("%d Jogo inexistente.\n", NL);
    }
    else
    {
        if (a->jogo->score1 > a->jogo->score2)
        {
            a->jogo->equipa1->jogos_ganhos--;
        }
        else if (a->jogo->score1 < a->jogo->score2)
        {
            a->jogo->equipa2->jogos_ganhos--;
        }
        HT_jg_delete(a, heads_jg, M);
        LS_jg_delete(a, jogos);
    }
}

/* Funcao auxiliar ao comando s que altera os antigos scores quando sao diferentes */
void muda_score(ptr_equipa equipa1, ptr_equipa equipa2, ptr_jogo jogo, int novoscore1,
                int novoscore2)
{
    if ((jogo->score1 > jogo->score2) && novoscore1 < novoscore2)
    {
        equipa1->jogos_ganhos--;
        equipa2->jogos_ganhos++;
    }
    else if ((jogo->score2 > jogo->score1) && novoscore1 > novoscore2)
    {
        equipa1->jogos_ganhos++;
        equipa2->jogos_ganhos--;
    }
    else if ((jogo->score1 > jogo->score2) && novoscore1 == novoscore2)
    {
        equipa1->jogos_ganhos--;
    }
    else if ((jogo->score2 > jogo->score1) && novoscore1 == novoscore2)
    {
        equipa2->jogos_ganhos--;
    }
}

/* Funcao auxiliar ao comando s que altera os scores antigos quando sao iguais */
void muda_score_igual(ptr_equipa equipa1, ptr_equipa equipa2, ptr_jogo jogo, int novoscore1,
                      int novoscore2)
{
    if ((jogo->score2 == jogo->score1) && novoscore1 < novoscore2)
    {
        equipa2->jogos_ganhos++;
    }
    else if ((jogo->score2 == jogo->score1) && novoscore1 > novoscore2)
    {
        equipa1->jogos_ganhos++;
    }
}

/* Comando s recebe um nome de um jogo e dois novos scores
 * se o jogo nao existir retorna um erro, caso contrario
 * muda o score do jogo e ajusta as vitorias de cada equipa */
void cmd_s(link_jg *heads_jg, int M, int NL)
{
    char nome_jogo[MAXNOME];
    int novoscore1, novoscore2;
    link_jogo a = NULL;
    ptr_equipa equipa1 = NULL, equipa2 = NULL;
    scanf(" %[^:\n]:%d:%d", nome_jogo, &novoscore1, &novoscore2);
    a = HT_jg_search(nome_jogo, heads_jg, M);
    if (a == NULL)
    {
        printf("%d Jogo inexistente.\n", NL);
    }
    else
    {
        equipa1 = a->jogo->equipa1;
        equipa2 = a->jogo->equipa2;
        muda_score(equipa1, equipa2, a->jogo, novoscore1, novoscore2);
        muda_score_igual(equipa1, equipa2, a->jogo, novoscore1, novoscore2);
        a->jogo->score1 = novoscore1;
        a->jogo->score2 = novoscore2;
    }
}

/* Comando A recebe um nome de uma equipa e adiciona a mesma
 * a Hash equipas caso essa equipa exista retorna erro,
 * caso contrario adiciona a equipa */
void cmd_A(link_eq *heads_eq, int m, int *numeq, int NL)
{
    char nome[MAXNOME];
    ptr_equipa equipa = NULL;
    scanf(" %[^:\n]", nome);
    if (HT_eq_search(nome, heads_eq, m) == NULL)
    {
        equipa = newEquipa(nome, 0);
        HT_eq_insert(equipa, heads_eq, m);
        *numeq = *numeq + 1;
    }
    else
    {
        printf("%d Equipa existente.\n", NL);
    }
}

/* Comando P recebe um nome de uma equipa e remove essa equipa
 * caso essa equipa nao exista retorna erro, caso contrario
 * remove a equipa da Hash equipas */
void cmd_P(link_eq *heads_eq, int M, int NL)
{
    char nome[MAXNOME];
    ptr_equipa equipa;
    scanf(" %[^:\n]", nome);
    equipa = HT_eq_search(nome, heads_eq, M);
    if (equipa == NULL)
    {
        printf("%d Equipa inexistente.\n", NL);
    }
    else
    {
        printf("%d %s %d\n", NL, equipa->nome, equipa->jogos_ganhos);
    }
}

/* Funcao auxiliar ao qsort que compara as equipas com
 * mais vitorias pelo seu nome */
int comparador_por_vitorias(const void *a, const void *b)
{
    struct equipa *equipa1 = *(struct equipa **)a;
    struct equipa *equipa2 = *(struct equipa **)b;
    return (strcmp(equipa1->nome, equipa2->nome));
}

/* Comando g imprime as equipas com mais vitorias por
 * ordem lexicografica, ou seja, pela ordem do seu nome */
void cmd_g(link_eq *heads_eq, int m, int *numeq, int NL)
{
    unsigned int j = 0;
    int i, k = 0;
    link_eq temp = NULL;
    ptr_equipa *array = NULL;
    if (*numeq > 0)
    {
        for (i = 0; i < m; i++)
        {
            temp = heads_eq[i];
            while (temp != NULL)
            {
                if (temp->link_team->jogos_ganhos > j)
                    j = temp->link_team->jogos_ganhos; /* Determina o maximo de vitorias */
                temp = temp->next;
            }
        }
        array = malloc(*numeq * sizeof(struct equipa));
        for (i = 0; i < m; i++)
        {
            temp = heads_eq[i];
            while (temp != NULL)
            {
                if (temp->link_team->jogos_ganhos ==
                    j) /* So insere as equipas que tem o maximo de vitorias */
                {
                    array[k] = temp->link_team;
                    k++;
                }
                temp = temp->next;
            }
        }
        qsort(array, k, sizeof(struct equipa *), comparador_por_vitorias);
        printf("%d Melhores %d\n", NL, array[0]->jogos_ganhos);
        for (i = 0; i < k; i++)
        {
            printf("%d * %s\n", NL, array[i]->nome);
        }
        free(array);
    }
}