#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 1069
#define CHAR_MAXIMO 1024
#define JOGOS_MAX 100000
#define EQUIPAS_MAX 100000

typedef struct equipa
{
    char *nome;
    int vitorias;
} *pEquipa;

typedef struct jogo
{
    char *nome_jogo;
    char *equipa1;
    char *equipa2;
    unsigned int score1;
    unsigned int score2;
} *pJogo;

typedef struct node_equipa
{
    pEquipa e;
    struct node_equipa *next;
} *link_equipa;

typedef struct node_jogo
{
    pJogo j;
    struct node_jogo *next;
} *link_jogo;

link_equipa *heads_equipa;
link_jogo *heads_jogo;


int hash_code(char *v)
{
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a * b % (M - 1))
    {
        h = (a*h + *v) % M;
    }
    return h;
}

void init_hash_table_equipas() 
{
    int i;
    heads_equipa = (link_equipa*)can_fail_malloc(M*sizeof(link_equipa));
    for (i = 0; i < M; i++)
    {
        heads_equipa[i] = NULL;
    }
}

void init_hash_table_jogos() 
{
    int i;
    heads_jogo = (link_jogo*)can_fail_malloc(M*sizeof(link_jogo));
    for (i = 0; i < M; i++)
    {
        heads_jogo[i] = NULL;
    }
}

link_equipa NEW_equipa(char* buffer)
{
    link_equipa x = (link_equipa)can_fail_malloc(sizeof(struct node_equipa));
    x->e = (pEquipa)can_fail_malloc(sizeof(struct equipa));
    x->e->nome = (char*)can_fail_malloc((strlen(buffer)+1));
    strcpy(x->e->nome, buffer);
    x->e->vitorias = 0;
    return x;
}

link_jogo NEW_jogo(char* nome_jogo, char* equipa1, char* equipa2, int score1, int score2)
{
    link_jogo x = (link_jogo)can_fail_malloc(sizeof(struct node_jogo));
    x->j = (pJogo)can_fail_malloc(sizeof(struct jogo));
    x->j->nome_jogo = (char*)can_fail_malloc((strlen(nome_jogo)+1));
    x->j->equipa1 = (char*)can_fail_malloc((strlen(equipa1)+1));
    x->j->equipa2 = (char*)can_fail_malloc((strlen(equipa2)+1));
    strcpy(x->j->nome_jogo, nome_jogo);
    strcpy(x->j->equipa1, equipa1);
    strcpy(x->j->equipa2, equipa2);
    x->j->score1 = score1;
    x->j->score2 = score2;
    return x;
}

void insert_tab_equipas(char *nome, int ed, int equipas[EQUIPAS_MAX])
{
    equipas[ed] = hash_code(nome);
    return;
}

void insert_tab_jogos(char *nome_jogo, int id, int jogos[JOGOS_MAX])
{
    jogos[id] = hash_code(nome_jogo);
    return;
}

link_equipa insertBegin_equipa(link_equipa head, char* nome, int ed, int equipas[EQUIPAS_MAX])
{
    link_equipa x = NEW_equipa(nome);
    insert_tab_equipas(nome, ed, equipas);
    x->next = head;
    return x;
} 

link_jogo insertBegin_jogo(link_jogo head, char* nome_jogo, char* equipa1, char* equipa2, int score1, int score2, int id, int jogos[JOGOS_MAX])
{
    link_jogo x = NEW_jogo(nome_jogo, equipa1, equipa2, score1, score2);
    insert_tab_jogos(nome_jogo, id, jogos);
    x->next = head;
    return x;
}

link_equipa searchList_equipa(link_equipa head, char* nome)
{
    link_equipa x;
    for(x = head; x != NULL; x = x->next)
    {
        if(strcmp(x->e->nome, nome) == 0)
        {
            return x;
        }
    }
    return NULL; 
}

link_jogo searchList_jogo(link_jogo head, char* nome)
{
    link_jogo x;
    for(x = head; x != NULL; x = x->next)
    {
        if(strcmp(x->j->nome_jogo, nome) == 0)
        {
            return x;
        }
    }
    return NULL; 
}

void insert_equipa(char *nome, int ed, int equipas[EQUIPAS_MAX])
{
    int i = hash_code(nome);
    heads_equipa[i] = insertBegin_equipa(heads_equipa[i], nome, ed, equipas);
}

void insert_jogo(char *nome_jogo, char *equipa1, char *equipa2, int score1, int score2, int id, int jogos[JOGOS_MAX])
{
    int i = hash_code(nome_jogo);
    heads_jogo[i] = insertBegin_jogo(heads_jogo[i], nome_jogo, equipa1, equipa2, score1, score2, id, jogos);
}

link_jogo delete(link_jogo head, char* nome_jogo)
{
    link_jogo t, prev;
    for(t = head, prev = NULL; t != NULL;
        prev = t, t = t->next)
        {
            if(strcmp(t->j->nome_jogo, nome_jogo) == 0)
            {
                if(t == head)
                    head = t->next;
                else
                    prev->next = t->next;
                free(t->j);
                free(t);
            }
        }
    return head;
}

link_equipa procura_equipa(char *nome)
{
    int i = hash_code(nome);
    return searchList_equipa(heads_equipa[i], nome);   
}

link_jogo procura_jogo(char *nome_jogo)
{
    int i = hash_code(nome_jogo);
    return searchList_jogo(heads_jogo[i], nome_jogo);
}

void delete_tab_jogos(char *nome_jogo, int id, int jogos[JOGOS_MAX])
{
    int e;
    for (e = 0; e < id; e++)
    {
        if (jogos[e] == hash_code(nome_jogo))
        {   
            jogos[e] = 0;
            return;
        }
    }
    return;
}

void delete_jogo(char *nome_jogo, int id, int jogos[JOGOS_MAX]) 
{
    int i = hash_code(nome_jogo);
    delete_tab_jogos(nome_jogo, id, jogos);
    heads_jogo[i] = delete(heads_jogo[i], nome_jogo);
}

/* funcao para adicionar uma equipa ao sistema */
void A(int cont, int ed, int equipas[EQUIPAS_MAX])
{
    char equipa[CHAR_MAXIMO];
    scanf(" %[^:\n]", equipa);
    if (procura_equipa(equipa) == NULL)
    {
        insert_equipa(equipa, ed, equipas);
        return;
    }
    else
    {
        printf("%d Equipa existente.\n", cont);
        return;
    }
}

/* funcao para procurar uma certa equipa */
void P(int cont)
{
    char equipa[CHAR_MAXIMO];
    scanf(" %[^:\n]", equipa);
    if (procura_equipa(equipa) != NULL)
    {
        printf("%d %s %d\n", cont, equipa, heads_equipa[hash_code(equipa)]->e->vitorias);
        return;
    }
    else
    {
        printf("%d Equipa inexistente.\n", cont);
        return;
    }
}

/* funcao para adicionar uma vitoria quando eh inserido um novo jogo no sistema */
void add_vitoria(char *equipa1, char *equipa2, int score1, int score2)
{
    if (score1 > score2)
    {
        /* equipa1 ganhou */
        heads_equipa[hash_code(equipa1)]->e->vitorias++;
        return;
    }
    else if (score2 > score1)
    {
        /* equipa2 ganhou */
        heads_equipa[hash_code(equipa2)]->e->vitorias++;
        return;
    }
    else
    {
        /* empate */
        return;
    }
}

/* funcao para inserir um novo jogo no sistema */
void a(int cont, int id, int jogos[JOGOS_MAX])
{
    char jogo[CHAR_MAXIMO], equipa1[CHAR_MAXIMO], equipa2[CHAR_MAXIMO];
    int score1, score2;
    scanf(" %[^:\n]: %[^:\n]: %[^:\n]:%d:%d", jogo, equipa1, equipa2, &score1, &score2);
    /* se o jogo nao existir da erro */
    if (procura_jogo(jogo) != NULL)
    {
        printf("%d Jogo existente.\n", cont);
        return;
    }
    /* se nao existir alguma equipa da erro */
    else if (procura_equipa(equipa1) == NULL || procura_equipa(equipa2) == NULL)
    {
        printf("%d Equipa inexistente.\n", cont);
        return;
    }
    else
    {
        insert_jogo(jogo, equipa1, equipa2, score1, score2, id, jogos);
        add_vitoria(equipa1, equipa2, score1, score2);
        return;
    }
}

/* funcao para procurar um dado jogo */
void p(int cont)
{
    char jogo[CHAR_MAXIMO];
    scanf(" %[^:\n]", jogo);
    if (procura_jogo(jogo) != NULL)
    {
        printf("%d %s %s %s %d %d\n", cont, jogo, heads_jogo[hash_code(jogo)]->j->equipa1, heads_jogo[hash_code(jogo)]->j->equipa2, heads_jogo[hash_code(jogo)]->j->score1, heads_jogo[hash_code(jogo)]->j->score2);
        return;
    }
    else
    {
        printf("%d Jogo inexistente.\n", cont);
        return;
    }
}

/* funcao para modificar as vitorias de uma certa equipa quando eh chamada a funcao s */
void muda_vitoria(char *equipa1, char *equipa2, int score1, int score2)
{
    if (score1 > score2 && score2 > 0)
    {
        /* se o novo score1 > novo score2, a equipa1 passou a ganhar o jogo */
        heads_equipa[hash_code(equipa1)]->e->vitorias++;
        heads_equipa[hash_code(equipa2)]->e->vitorias--;
        return;
    }
    else if (score2 > score1 && score1 > 0)
    {
        /* o contrario */
        heads_equipa[hash_code(equipa2)]->e->vitorias++;
        heads_equipa[hash_code(equipa1)]->e->vitorias--;
        return;
    }
    else
    {
        /* empate. nao muda nada */
        return;
    }
}

/* funcao para modificar o resultado de um jogo */
void s(int cont)
{
    char jogo[CHAR_MAXIMO];
    int score1, score2;
    scanf(" %[^:\n]:%d:%d", jogo, &score1, &score2);
    if (procura_jogo(jogo) != NULL)
    {
        heads_jogo[hash_code(jogo)]->j->score1 = score1;
        heads_jogo[hash_code(jogo)]->j->score2 = score2;
        muda_vitoria(heads_jogo[hash_code(jogo)]->j->equipa1, heads_jogo[hash_code(jogo)]->j->equipa2, score1, score2);
        return;
    }
    else
    {
        printf("%d Jogo inexistente.\n", cont);
        return;
    }
}

/* funcao auxiliar de r (remove jogo) */
void tira_vitoria(char *equipa1, char *equipa2, int score1, int score2)
{
    if (score1 > score2)
    {
        /* se score1 > score2, a equipa1 tinha ganho o jogo logo tiramos a vitoria */
        heads_equipa[hash_code(equipa1)]->e->vitorias--;
        return;
    }
    else if (score2 > score1)
    {
        /* o contrario */
        heads_equipa[hash_code(equipa2)]->e->vitorias--;
        return;
    }
    else
    {
        /* empate */
        return;
    }
}

/* funcao para remover um jogo do sistema */
void r(int cont, int id, int jogos[JOGOS_MAX])
{
    char jogo[CHAR_MAXIMO];
    scanf(" %[^:\n]", jogo);
    if (procura_jogo(jogo) == NULL)
    {
        printf("%d Jogo inexistente.\n", cont);
        return;
    }
    else
    {
        tira_vitoria(heads_jogo[hash_code(jogo)]->j->equipa1, heads_jogo[hash_code(jogo)]->j->equipa2, heads_jogo[hash_code(jogo)]->j->score1, heads_jogo[hash_code(jogo)]->j->score2);
        delete_jogo(jogo, id, jogos);
        return;
    }   
}

void l(int cont, int id, int jogos[JOGOS_MAX])
{   
    int e;
    for (e = 0; e < id; e++)
    {
        if (jogos[e] != 0)
        {
            printf("%d %s %s %s %d %d\n", cont, heads_jogo[jogos[e]]->j->nome_jogo, heads_jogo[jogos[e]]->j->equipa1, heads_jogo[jogos[e]]->j->equipa2, heads_jogo[jogos[e]]->j->score1, heads_jogo[jogos[e]]->j->score2);
        }
    }
    return;
}

/* qsort C-string comparison function */ 
int compare(const void *a, const void *b) 
{ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
	/* strcmp functions works exactly as expected from
	comparison function */ 
} 

void g(int cont, int ed, int equipas[EQUIPAS_MAX])
{
    int e;
    int i = 0;
    char winners[100][CHAR_MAXIMO];
    int maior_vitorias = 0;
    for (e = 0; e < ed; e++)
    {
        if (heads_equipa[equipas[e]]->e->vitorias > maior_vitorias)
        {
            /* apanha o maior valor das vitorias e guarda */
            maior_vitorias = heads_equipa[equipas[e]]->e->vitorias;
        }
    }

    if (maior_vitorias == 0)
    {
        return;
    }

    for (e = 0; e < ed; e++)
    {
        /* verifica se alguma equipa tem as mesmas vitorias para por num vetor de vencedores */
        if ((heads_equipa[equipas[e]]->e->vitorias == maior_vitorias) && maior_vitorias != 0)
        {
            strcpy(winners[i], heads_equipa[equipas[e]]->e->nome);
            i++;
        }
    }
    qsort(winners, 1, sizeof(char*), compare);
    printf("%d Melhores numero-de-jogos-ganhos\n", cont);
    for (e = 0; e < i; e++)
    {
        printf("%d * %s\n", cont, winners[e]);
    }
    return;
}

int main()
{
    int carater;
    int cont = 1;
    /* vetor de todos os jogos */
    int jogos[JOGOS_MAX];
    /* id dos jogos */
    int id = 0;
    /* vetor de todas as equipas */
    int equipas[EQUIPAS_MAX];
    /* id das equipas... */
    int ed = 0;
    init_hash_table_equipas();
    init_hash_table_jogos();

    while ((carater = getchar()) != EOF)
    {
        switch(carater)
        {
            case 'a':
            {
                a(cont, id, jogos);
                cont++;
                id++;
                break;
            } 
            case 'l':
            {
                l(cont, id, jogos);
                cont++;
                break;
            }
            case 'p':
            {
                p(cont);
                cont++;
                break;
            }
            case 'r':
            {
                r(cont, id, jogos);
                cont++;
                break;
            }
            case 's':
            {
                s(cont);
                cont++;
                break;
            }
            case 'A':
            {
                A(cont, ed, equipas);
                cont++;
                ed++;
                break;
            }
            case 'P':
            {
                P(cont);
                cont++;
                break;
            }
            case 'g':
            {
                g(cont, ed, equipas);
                cont++;
                break;
            } 
        free(heads_equipa);
        free(heads_jogo);
        }
    }   
    return 0;
}