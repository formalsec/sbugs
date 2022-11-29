#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_STRING 1024
#define MAX_TABEL 1051
#define MAX_G 1000;
#include "operationsovertable.h"
#include "operationsoverteamlist.h"

Junta *a(Junta *tabela, team equipa, int count);
team A(team equipa, int count);
void p(campeonato *tabela, int count);
void P(team equipa, int count);
void l(copa *golo, int count);
Junta *r(Junta *tudo, team equipa, int M, int Count);
Junta *s(Junta *tudo, team equipa, int count);
void g(team equipa, int Count);
void x(Junta *tudo, team equipa);
team libertaequipa(team equipa);
copa *libertalista(copa *lista);
campeonato libertahashtable(campeonato jogo);


int main()
{
    Junta *tudo;
    /* Esta estrutura representa a hashtable em que sao guardados os jogos e 
    a sua lista ordenada por ordem insercao */
    team equipa;
    /* A lista simplesmente ligada de equipas que contem tambem as suas vitorias */
    char c;
    int M = MAX_TABEL, i = 0;
    /* Este M vai definir o tamanho da hashtable */
    equipa=NULL;
    tudo = (Junta*)can_fail_malloc(sizeof(struct Junta));
    /* Inicializaca da variavel do tipo Junta */
    tudo ->hashtable = init_array(tudo->hashtable, M);
    tudo->lista = NULL;
    while ((c = getchar()) != EOF)
    {
        switch(c)
        {
            case 'a':
            /* Adiciona um novo jogo */
                i += 1;
                tudo = a(tudo, equipa, i);
                break;
            case 'A':
            /* Adiciona uma nova equipa */
                i += 1;    
                equipa = A(equipa, i);  
                break;
            case 'l':
            /* Lista todos os jogos pela ordem de insercao */
                i += 1;   
                l(tudo->lista, i); 
                break;
            case 'p':
            /* Procura um jogo */
                i += 1;  
                p(tudo->hashtable, i); 
                break;
            case 'P':
            /* Procura uma equipa */
                i += 1;
                P(equipa, i); 
                break;
            case 'r':
            /* Apaga um jogo */ 
                i += 1; 
                r(tudo, equipa, M, i); 
                break;
            case 's':
            /* Altera a pontuacao(score) de um jogo */
                i += 1;
                tudo = s(tudo, equipa, i);   
                break;
            case 'g':
            /* Encontra as equipas que venceram mais jogos */ 
                i += 1;
                g(equipa, i); 
                break;
            case 'x':
                x(tudo, equipa);
                break;
        }
    }
    return 0;
}

Junta *a(Junta *tudo, team equipa, int count)
{
    char n[MAX_STRING], e1[MAX_STRING], e2[MAX_STRING];
    int i, z, M = MAX_TABEL;
    game head = (game)can_fail_malloc(sizeof(struct jogo));
    /* Esta variavel do tipo jogo servem para guardar os valores recebidos */
    campeonato cabeca; 
    /* A cabeca resulta da procura na hashtable */
    team crazy1; 
    team crazy2; 
    scanf(" %[^:]:%[^:]:%[^:]:%d:%d", n, e1, e2, &i, &z);
    /* A strdup e uma funcao que supostamente estava na string.h.
    Como nao estava, criei uma nova */
    head->nome = strdup(n);
    head->equipa1 = strdup(e1);
    head->equipa2 = strdup(e2);
    head->score1 = i;
    head->score2 = z;
    cabeca = search_hash(tudo->hashtable, head->nome);
    if (cabeca == NULL)
    {
        /* Verifica se a existencia deste jogo */
        crazy1 = searchTeams(head->equipa1, equipa);
        crazy2 = searchTeams(head->equipa2, equipa);
        if (crazy1 != NULL && crazy2 != NULL)
        {
            /* Verifica se a existencia de equipas */
            tudo->lista = InsereEnd(tudo->lista, head);
            equipa = analisaVitorias(head->equipa1, head->equipa2, head->score1, head->score2, equipa);
            tudo->hashtable = insert_hash(tudo->hashtable, head, M);
            /* Caso nenhuma das anteriores se verifique, sao guardadas aqui */
            free(head->nome);
            free(head->equipa1);
            free(head->equipa2);
            free(head);
            return tudo;
        }
        else
        {
            /* Se a equipa for nao existente */
            printf("%d Equipa inexistente.\n", count);
        }
    }
    else
    {
        /* Se o jogo for nao existente */
        printf("%d Jogo existente.\n", count);
    }
    free(head->nome);
    free(head->equipa1);
    free(head->equipa2);
    free(head);
    return tudo;
}


team A(team headequipa, int count)

{
    team cabeca;
    char n[MAX_STRING], *s;
    scanf(" %[^:\n]", n);
    s = (char*)can_fail_malloc(sizeof(char)*(strlen(n) + 1)); 
    strcpy(s, n);
    cabeca = searchTeams(s, headequipa);
    /* Procura na lista de equipas o elemento correspondente a equipa recebida */ 
    if (cabeca == NULL)
    {
        /* Se nao existir, insere se no inicio */
        cabeca = insertBegin(headequipa, s);
        free(s);
        return cabeca;
    }
    else
    {
        printf("%d Equipa existente.\n", count);
    }
    free(s);
    /* Devolve a cabeca da lista */
    return headequipa;
}

void p(campeonato *tabela, int count)
{
    int size = 0;
    campeonato cabeca;
    char name[MAX_STRING], *s;
    scanf(" %[^:\n]", name);
    size = strlen(name) + 1;
    s = can_fail_malloc(size);
    strcpy(s, name);
    cabeca = search_hash(tabela, s);
    /* Porcura a cabeca desejada */
    if(cabeca != NULL)
    {
        printf("%d %s %s %s %d %d\n", count, (cabeca->j->nome), (cabeca->j->equipa1), (cabeca->j->equipa2), cabeca->j->score1, cabeca->j->score2);
        free(s);
    }
    else
    {
        printf("%d Jogo inexistente.\n", count);
        free(s);
    }
    
}

void P(team headequipa, int count)
{
    team vitorias;
    char string[MAX_STRING], *S;
    scanf(" %[^:\n]", string);
    S = (char*)can_fail_malloc(sizeof(char) *(strlen(string) + 1));
    strcpy(S, string);
    vitorias = searchTeams(S, headequipa);
    /* Procura a equipa e imprime a equipa e as vitorias */
    if (vitorias != NULL)
    {
        free(S);
        printf("%d %s %d\n", count, vitorias->nome, vitorias->vitorias);
    }
    else
    {
        free(S);
        printf("%d Equipa inexistente.\n", count);   
    }
}

void l(copa *golo, int count)
{
    /* Faz print dos jogos por ordem de insercao */ 
    copa *t;
    for (t = golo; t!= NULL; t = t->next)
        printf("%d %s %s %s %d %d\n", count, t->text, t->Pequipa, t->Sequipa, t->Pscore, t->Sscore);
}

Junta *r(Junta *tudo, team equipa, int M, int Count)
{
    char n[1024], *text;
    campeonato cabeca;
    scanf(" %[^:\n]",n);
    text = (char*)can_fail_malloc(sizeof(char) * (strlen(n) + 1));
    strcpy(text, n);
    cabeca = search_hash(tudo ->hashtable, text);
    /* Verifica se o jogo existe */
    if (cabeca != NULL)
    {
        /* Caso exista o jogo e removido da hashtable e da lista de equipas por insercao */
        Remove_Vitoria(cabeca->j->equipa1, cabeca->j->equipa2, cabeca->j->score1, cabeca->j->score2, equipa);
        tudo->hashtable = removeEl(tudo ->hashtable, text, M);
        tudo->lista = RLista(tudo->lista, text);
        free(text);
        return tudo;
    }
    else
    {
        printf("%d Jogo inexistente.\n", Count);  
    }
    free(text);
    return tudo;
    
}

Junta *s(Junta *tudo, team equipa, int Count)
{
    char n[MAX_STRING], *string;
    campeonato cabeca;
    copa *cabana;
    int s1 = 0, s2 = 0;
    scanf(" %[^:\n]:%d:%d", n, &s1, &s2);
    string = (char*)can_fail_malloc(sizeof(char)*(strlen(n) + 1));
    strcpy(string, n);
    cabeca = search_hash(tudo->hashtable, string);
    /* Verifica se todos os casos em que e necessario alterar o numero de vitorias */
    if (cabeca != NULL)
    {
        if (s1 == s2)
        {
            if (cabeca->j->score1 > cabeca->j->score2)
            {
                Retira_Vitoria(cabeca->j->equipa1, equipa);
                cabeca->j->score1 = s1;
                cabeca->j->score2 = s2;
            }
            else if (cabeca->j->score2 > cabeca->j->score1)
            {
                Retira_Vitoria(cabeca->j->equipa2, equipa);
                cabeca->j->score1 = s1;
                cabeca->j->score2 = s2;
            }
        }
        else if (s1 > s2)
        {
            if (cabeca->j->score1 == cabeca->j->score2)
            {
                Adiciona_Vitoria(cabeca->j->equipa1, equipa);
                cabeca->j->score1 = s1;
                cabeca->j->score2 = s2;
            }
            else if (cabeca->j->score1 < cabeca->j->score2)
            {
                Retira_Vitoria(cabeca->j->equipa2, equipa);
                Adiciona_Vitoria(cabeca->j->equipa1, equipa);
                cabeca->j->score1 = s1;
                cabeca->j->score2 = s2;
            }
        }
        else if (s1 < s2)
        {
            if (cabeca->j->score1 == cabeca->j->score2)
            {
                Adiciona_Vitoria(cabeca->j->equipa2, equipa);
                cabeca->j->score1 = s1;
                cabeca->j->score2 = s2;
            }
            else if (cabeca->j->score1 > cabeca->j->score2)
            {
                Retira_Vitoria(cabeca->j->equipa1, equipa);
                Adiciona_Vitoria(cabeca->j->equipa2, equipa); 
                cabeca->j->score1 = s1;
                cabeca->j->score2 = s2;
            } 
        }
        /* situacoes em que nao se verificam nenhum dos casos anteriores */
        cabeca->j->score1 = s1;
        cabeca->j->score2 = s2;
        cabana = Search_Copas(tudo->lista, cabeca->j->nome);
        /* Altera o score na lista organizada por ordem de insercao de equipas */
        cabana ->Pscore = s1;
        cabana->Sscore = s2;
    }
    else 
    {
        printf("%d Jogo inexistente.\n", Count);
    }
    free(string);
    return tudo;
}

void g(team cabeca, int Count)
{
    int size = 0;
    char *nomes[500];
    /* Cria uma tabela de nomes */
    team t;
    if (cabeca != NULL)
    {
        int j = cabeca->vitorias, e = 0, i = 0;
        for (t = cabeca; t != NULL; t=t->next)
        {
            /* Procura pelo maior numero de vitorias */
            if (j < t -> vitorias)
            {
                j = t->vitorias;
            }
        }
        for (t = cabeca; t != NULL; t = t->next)
        {
            /* Passa as equipas para a tabela com o maior numero de vitorias */
            if (j == t->vitorias)
            {
                size = strlen(t->nome) + 1;
                nomes[e] = can_fail_malloc(size);
                strncpy(nomes[e], t->nome, size);
                e++;
            }
        }
        printf("%d Melhores %d\n", Count, j);
        qsort(nomes, e, sizeof(team), cmpfunc);
        for (i = 0; i < e; i++)
        {
            printf("%d * %s\n", Count, nomes[i]);
            free(nomes[i]);
        }
    }
}

void x(Junta *tudo, team equipa)
{
    /* Funcao feita pra libertar todas as estruturas usadas */
    int i;
    while (equipa != NULL)
    {
        equipa = libertaequipa(equipa);
    }
    while (tudo->lista != NULL)
    {
        tudo ->lista = libertalista(tudo->lista);
    }
    for (i = 0; i < MAX_TABEL; i++)
    {
        if (tudo->hashtable[i] != NULL)
        {
            while (tudo->hashtable[i] != NULL)
            {
                tudo->hashtable[i] = libertahashtable(tudo->hashtable[i]);
            }
            free(tudo->hashtable[i]);
        }
    }
    free(tudo->hashtable);
    free(tudo->lista);
    free(tudo);
}






