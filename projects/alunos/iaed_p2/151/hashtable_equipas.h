#ifndef HASH_EQUIPAS
#define HASH_EQUIPAS

typedef struct team {
    char *nome;
    int vitorias;
} equipa;

typedef struct nodeeq {
    equipa *pequipa;
    struct nodeeq *next;
} *linkeq;

linkeq* HashEquipas_inic();
int hashfunc(char *nome);
void HashEquipas_insere(linkeq* hash_equipas, equipa *pequipa, int key);
linkeq encontra_equipa(linkeq* hash_equipas, char *nome);

#endif