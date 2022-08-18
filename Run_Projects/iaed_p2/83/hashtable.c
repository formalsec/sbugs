#include <stdlib.h>
#include "hashtable.h"

/* Funcao hash que permite calcular a posicao na hashtable */
int hash(char* string, int max)
{
    int h = 0, a = 127;
    
    for (; *string != '\0'; string++)
        h = (a*h + *string) % max;

    return h;
}


/* Funcoes referentes ah hashtable dos Jogos */

/* Funcao auxiliar que inicializa a hashtable para os Jogos */
void TabJogosinit(int* max_jogos, int* N_jogos, Jogo* TabJogos)
{
    int i;
    (*N_jogos) = 0;

    for (i = 0; i < (*max_jogos); i++)
    {
        TabJogos[i] = NULL;
    }
}


/* Funcao auxiliar que duplica a capacidade da hashtable dos Jogos */
Jogo* expand_jogos(int* max_jogos, int* N_jogos, Jogo* TabJogos)
{
    int i;
    Jogo *aux = TabJogos;

    (*max_jogos) = (*max_jogos) * 2;
    TabJogos = (Jogo*)malloc((*max_jogos) * sizeof(Jogo));
    (*N_jogos) = 0;

    for (i = 0; i < (*max_jogos); i++)
    {
        TabJogos[i] = NULL;
    }

    for (i = 0; i < (*max_jogos)/2; i++)
    {
        if (aux[i] != NULL)
        {
            TabJogosinsert(max_jogos, N_jogos, TabJogos, aux[i]);
        }
    }

    free(aux);
    return TabJogos;
}


/* Funcao auxiliar que insere um elemento na hashtable dos Jogos */
void TabJogosinsert(int* max_jogos, int* N_jogos, Jogo* TabJogos, Jogo Jogo)
{
    int i =  hash((Jogo -> nome), *max_jogos);

    while (TabJogos[i] != NULL)
    {
        i = (i+1) % (*max_jogos);
    }

    TabJogos[i] = Jogo;
    (*N_jogos)++;
}


/* Funcao auxiliar que remove um dado jogo da hashtable */
void TabJogosdelete(int* max_jogos, int* N_jogos, Jogo* TabJogos, char* string)
{
    int j, i = hash(string, *max_jogos); 
    Jogo aux;
    Jogo v;

    while (TabJogos[i] != NULL)
    {
        if (eq(string, (TabJogos[i] -> nome)) == 0)
        {
            break;
        }

        else
        {
            i = (i + 1) % (*max_jogos);
        }
    }

    if (TabJogos[i] == NULL)
    {
        return;
    }

    aux = TabJogos[i]; /* Guarda o Jogo a ser removido em aux */
    TabJogos[i] = NULL;
    (*N_jogos)--;

    for (j = (i + 1) % (*max_jogos); TabJogos[j] != NULL; j = (j + 1) % (*max_jogos), 
                                                        (*N_jogos)--)
    {
        v = TabJogos[j];
        TabJogos[j] = NULL;
        TabJogosinsert(max_jogos, N_jogos, TabJogos, v);
    }

    freeJogo(aux); /* Libertacao da memoria que estava a ser utilizada pelo elemento que
                      foi removido */
}


/* Funcao auxiliar que procura um dado elemento na hashtable dos Jogos dado o nome desse Jogo */
Jogo TabJogossearch(int* max_jogos, Jogo* TabJogos, char* string)
{
    int i = hash(string, *max_jogos);

    while (TabJogos[i] != NULL)
    {
        if (eq(string, (TabJogos[i] -> nome)) == 0)
        {
            return TabJogos[i];
        }

        else
        {
            i = (i + 1) % (*max_jogos);
        }
    }

    return NULL;
}


/* Funcao auxiliar que liberta a memoria ocupada pela hashtable dos Jogos */
void freeTabJogos(int* max_jogos, Jogo* TabJogos)
{
    int i = 0;

    while (i < (*max_jogos))
    {
        if (TabJogos[i] != NULL)
        {
            freeJogo(TabJogos[i]);
        }

        i++;
    }

    free(TabJogos);
}



/* Funcoes referentes ah hashtable das equipas */

/* Funcao auxiliar que inicializa a hashtable para as Equipas */
void TabEquipasinit(int* max_equipas, int* N_equipas, Equipa* TabEquipas)
{
    int i;
    (*N_equipas) = 0;

    for (i = 0; i < (*max_equipas); i++)
    {
        TabEquipas[i] = NULL;
    }
}


/* Funcao auxiliar que duplica a capacidade da hashtable das Equipas */
Equipa* expand_equipas(int* max_equipas, int* N_equipas, Equipa* TabEquipas)
{
    int i;
    Equipa *aux = TabEquipas;

    (*max_equipas) = (*max_equipas) * 2;
    TabEquipas = (Equipa*)malloc((*max_equipas) * sizeof(Equipa));
    (*N_equipas) = 0;

    for (i = 0; i < (*max_equipas); i++)
    {
        TabEquipas[i] = NULL;
    }

    for (i = 0; i < (*max_equipas)/2; i++)
    {
        if (aux[i] != NULL)
        {
            TabEquipasinsert(max_equipas, N_equipas, TabEquipas, aux[i]);
        }
    }

    free(aux);
    return TabEquipas;
}


/* Funcao auxiliar que insere um elemento na hashtable das Equipas */
void TabEquipasinsert(int* max_equipas, int* N_equipas, Equipa* TabEquipas, Equipa Equipa)
{
    int i =  hash((Equipa -> nome), *max_equipas);

    while (TabEquipas[i] != NULL)
    {
        i = (i+1) % (*max_equipas);
    }

    TabEquipas[i] = Equipa;
    (*N_equipas)++;
}


/* Funcao auxiliar que procura um dado elemento na hashtable das Equipas dado o nome da Equipa */
Equipa TabEquipassearch(int* max_equipas, Equipa* TabEquipas, char* string)
{
    int i = hash(string, *max_equipas);

    while (TabEquipas[i] != NULL)
    {
        if (eq(string, (TabEquipas[i] -> nome)) == 0)
        {
            return TabEquipas[i];
        }

        else
        {
            i = (i + 1) % (*max_equipas);
        }
    }

    return NULL;
}


/* Funcao auxiliar que liberta a memoria ocupada pela hashtable das Equipas */
void freeTabEquipas(int* max_equipas, Equipa* TabEquipas)
{
    int i = 0;

    while (i < (*max_equipas))
    {
        if (TabEquipas[i] != NULL)
        {
            freeEquipa(TabEquipas[i]);
        }

        i++;
    }

    free(TabEquipas);
}