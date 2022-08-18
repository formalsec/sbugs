#ifndef COMANDOS_ESTRUTURAS_H
#define COMANDOS_ESTRUTURAS_H
/* Numero maximo de caracteres para nomes de jogos e equipas */
#define MAX_NOME 1024 

/******************************************************************************/
/*                         ESTRUTURAS JOGOS E EQUIPAS                         */
/******************************************************************************/

typedef struct jogo
{
   char *nome, *equipa1, *equipa2;
   int score1, score2;
   struct jogo *next;
}jogos;


typedef struct equipa
{
   char *nome_equipa;
   int vitoria;
   struct equipa *next;
}equipas;

/******************************************************************************/
/*                                   COMANDOS                                 */
/******************************************************************************/

jogos *comando_a(jogos **, equipas **, int num, jogos *head, equipas *head_e);
equipas *comando_A(equipas **, int num, equipas *head_e);
void comando_l(int num, jogos *head);
void comando_p(jogos **, int num);
void comando_P(equipas **, int num);
jogos *comando_r(jogos **, equipas **, int num, jogos *head, equipas *head_e);
void comando_s(jogos **, equipas **, int num, jogos *head, equipas* head_e);
void comando_g(int num, equipas *head_e);

/******************************************************************************/
/*                             COMANDOS AUXILIARES                            */
/******************************************************************************/

/* -------------------------------- COMANDO a ------------------------------- */

jogos *novo_jogo(char *, char *, char *, int, int);
void HTinserejogo(jogos **, jogos *);
jogos *insere_inicio_jogo(jogos *, jogos *);

/* -------------------------------- COMANDO A ------------------------------- */

equipas *nova_equipa(char *);
void HTinsere_equipa(equipas **, equipas *);
equipas *insere_inicio(equipas *, equipas *);


/* -------------------------------- COMANDO p ------------------------------- */

void HTprocura_p(jogos **, char *, int);
int procura_jogo_p(jogos *, char *, int);

/* -------------------------------- COMANDO P ------------------------------- */

void procura_equipa_P(equipas **, char *, int);
void lista_equipa_P(equipas *, char *, int);

/* -------------------------------- COMANDO r ------------------------------- */

void HT_elimina_jogo(jogos **, equipas **,  char *, int);
jogos *elimina_jogo_r(equipas **, jogos *, char *, int);
void verifica(int, int);
jogos *elimina_jogo_lista(jogos *, char *, equipas *);

/* -------------------------------- COMANDO s ------------------------------- */

void HT_altera_score(jogos **, equipas **, char *, int, int, int, jogos *, equipas *);
int altera_score_lista(equipas **, jogos *, char *, int, int, int, jogos *, equipas *);

/* -------------------------------- COMANDO g ------------------------------- */

int *maior_numero_vitorias(equipas *, int *);
char **maior_equipas(equipas *, int, int);
void mergesort(char **, char **, int, int);
void merge(char **, char **, int, int, int);


/******************************************************************************/
/*                                    HASH                                    */
/******************************************************************************/

unsigned int hash (char *);

/******************************************************************************/
/*                               INSERE LISTAS                                */
/******************************************************************************/

jogos *insere_fim_jogos(jogos *, jogos *);
equipas *insere_fim_equipas(equipas *, equipas *);

/******************************************************************************/
/*                               OUTROS PROCESSOS                             */
/******************************************************************************/

int HTprocurajogo(jogos **, char *);
int procura_jogo(jogos *, char *);

int HTprocura(equipas **, char *);
int procura_equipa(equipas *, char *);

void HT_tira_vitoria(equipas **, char *);
void tirar_vitoria_lista(equipas *, char *);

void HT_soma_vitoria(equipas **, char *);
void soma_vitoria(equipas *, char *);

/******************************************************************************/
/*                                    FREES                                   */
/******************************************************************************/

void procura_free(jogos**, equipas **);
void dar_free_equipas(equipas *);
void dar_free_jogos(jogos *);

#endif