#ifndef OPERATIONSOVERTEAMLIST_H
#define OPERATIONSOVERTEAMLIST_H


typedef struct equipa{
    char *nome;
    int vitorias;
    struct equipa *next;
}*team;

/* As equipas estao definidas desta maneira */

team insertBegin(team head, char *text);
team NEW(char* buffer);
team searchTeams(char *name, team head);
team procuraVitorias(char *name, team equipa);
team analisaVitorias(char *equipa1, char *equipa2, int V1, int V2, team equipa);
void Remove_Vitoria(char *equipa1, char *equipa2, int V1, int V2, team equipa);
void Retira_Vitoria(char *nome, team equipa);
void Adiciona_Vitoria(char *nome, team equipa);
int comprimento(team equipa);
int cmpfunc(const void* a, const void* b);
team libertaequipa(team equipa);

#endif