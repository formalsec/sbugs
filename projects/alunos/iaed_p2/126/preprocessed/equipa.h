#ifndef EQUIPA_H
#define EQUIPA_H

/* Estrutura de uma equipa */
typedef struct eq {
    char *nome; /* nome da equipa */
    int vitorias; /* numero de jogos ganhos pela equipa */
} *Equipa;

/*------------------------| Prototipos das funcoes |--------------------------------------*/

Equipa nova_equipa(char *nome);
char* nome_equipa(Equipa eq);
int vitorias_equipa(Equipa eq);
void altera_vitorias_eq(Equipa eq, int v);
void apaga_equipa(Equipa eq);
int compara_eq(const void *a, const void *b);
char *strdup(const char *str);

#endif