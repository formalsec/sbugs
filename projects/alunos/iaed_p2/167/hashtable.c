#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

/* ============================================================ */
int Hash(char *name, int m)
{
    int h = 0, a = 127;
    for (; *name != '\0'; name++)
    { h = (a*h + *name) % m; }
return h;
}
/* ============================================================ */
p_game * Init(int m)
{
    int i;
    p_game * p;
    p = (p_game *) can_fail_malloc(m * sizeof(p_game));
    for (i = 0; i < m; i++)
    { p[i] = NULL; }
    return p;
}
/* ============================================================ */
p_game * HTInsertElement(p_game *p, char *name, char *team1, char *team2, int score1, int score2, int N, int M)
{
    int i = Hash(name, M);
    if (N++ > M/2)
        return NULL;
    while (p[i] != NULL)
    { i++; }
    p[i] = (p_game) can_fail_malloc(sizeof(struct game));
    p[i]->name = d_strdup(name);
    p[i]->team1 = d_strdup(team1);
    p[i]->team2 = d_strdup(team2);
    p[i]->score1 = score1;
    p[i]->score2 = score2;
    return p;
}
/* ============================================================ */
p_game Search(p_game *p, char *name, int M)
{
    int i = Hash(name, M);
    while (p[i] != NULL)
    {
        if (strcmp(p[i]->name, name) == 0)
        { 
            return p[i];
        }
        else
        {
            i++;
        }
    }
    return NULL;
}
/* ============================================================ */
p_game * HTRemoveElement(p_game *p, char *name, int N, int M)
{
    int i = Hash(name, M), j;
    p_game v;
    while (p[i] != NULL)
    {
        if (strcmp(p[i]->name, name) == 0)
        {
            break;
        }
        else
        {
            i++;
        }
    }
    if (p[i] == NULL)
    {
        return p;
    }
    N--;
    free(p[i]->name);
    free(p[i]->team1);
    free(p[i]->team2);
    free(p[i]);
    p[i] = NULL;
    for (j = i + 1; p[j] != NULL; j++)
    {
        v = p[j];
        p[j] = NULL;
        p = HTInsertElement(p, v->name, v->team1, v->team2, v->score1, v->score2, N, M);
        free(v->name);
        free(v->team1);
        free(v->team2);
        free(v);
    }
    return p;
}
/* ============================================================ */
p_game * Expand(p_game *p, int N, int M)
{
    int i;
    p_game *v = p;
    M = M + M;
    p = Init(M);
    for (i = 0; i < M/2; i++)
    {
        if (v[i] != NULL)
        {
            p = HTInsertElement(p, v[i]->name, v[i]->team1, v[i]->team2, v[i]->score1, v[i]->score2, N, M);
        }
    }
    free(v);
    return p;   
}
/* ============================================================ */
p_game * FreeAllHT(p_game *p, int M)
{
    int i = 0;
    while (i < M)
    {
        if (p[i]!= NULL)
        {
            free(p[i]->name);
            free(p[i]->team1);
            free(p[i]->team2);
            free(p[i]);
        }
        i++;
    }
    return p;
}

/* ============================================================ */
/* ============================================================ */
p_team * Init_T(int m)
{
    int i;
    p_team * p;
    p = (p_team *) can_fail_malloc(m * sizeof(p_team));
    for (i = 0; i < m; i++)
    { p[i] = NULL; }
    return p;
}
/* ============================================================ */
p_team * HTInsertElement_T(p_team *p, char *name, int wins, int N, int M)
{
    int i = Hash(name, M);
    while (p[i] != NULL)
    { i++; }
    p[i] = (p_team) can_fail_malloc(sizeof(struct team));
    p[i]->name = d_strdup(name);
    p[i]->wins = wins;
    if (N++ > M/2)
        return NULL;
    return p;
}
/* ============================================================ */
p_team Search_T(p_team *p, char *name, int M)
{
    int i = Hash(name, M);
    while (p[i] != NULL)
    {
        if (strcmp(p[i]->name, name) == 0)
        { 
            return p[i];
        }
        else
        {
            i++;
        }
    }
    return NULL;
}
/* ============================================================ */
p_team * HTRemoveElement_T(p_team *p, char *name, int N, int M)
{
    int i = Hash(name, M), j;
    p_team v;
    while (p[i] != NULL)
    {
        if (strcmp(p[i]->name, name) == 0)
        {
            break;
        }
        else
        {
            i++;
        }
    }
    if (p[i] == NULL)
    {
        return p;
    }
    N--;
    free(p[i]->name);
    free(p[i]);
    p[i] = NULL;
    for (j = i+1; p[j] != NULL; j++)
    {
        v = p[j];
        p[j] = NULL;
        p = HTInsertElement_T(p, v->name, v->wins, N, M);
    }
    return p;
}
/* ============================================================ */
p_team * Expand_T(p_team *p, int N, int M)
{
    int i;
    p_team *v = p;
    M = M + M;
    p = Init_T(M);
    for (i = 0; i < M/2; i++)
    {
        if (v[i] != NULL)
        {
            p = HTInsertElement_T(p, v[i]->name, v[i]->wins, N, M);
        }
    }
    free(v); 
    return p;   
}
/* ============================================================ */
p_team * FreeAllHT_T(p_team *p, int M)
{
    int i = 0;
    while (i < M)
    {
        if (p[i]!= NULL)
        {
            free(p[i]->name);
            free(p[i]);
        }
        i++;
    }
    return p;
}
/* ============================================================ */