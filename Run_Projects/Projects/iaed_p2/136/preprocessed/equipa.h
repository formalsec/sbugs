#ifndef _EQUIPA_
#define _EQUIPA_

/* ABSTRACAO */

typedef char * chave_eq; /* a chave de uma equipa e o seu nome -> char * */

/* ESTRUTURA */

/* definicao da estrutura equipa: ADT */
struct str_equipa
{
    char * nome; /* ponteiro para uma string - nome */
    int vitorias; /* inteiro - vitorias */
};

typedef struct str_equipa * equipa; /* ponteiro para a equipa */

/* ABSTRACOES */

#define CHAVE_EQ(a) (a->nome) /* chave de uma equipa - o seu nome */
#define EQUIPA(A) ((equipa) A) /* cast de um ponteiro qualquer para equipa */
#define NO_EQ (NULL) /* equipa nula (ponteiro NULL) */
#define EQ_CERTA(a, b) (strcmp(a->nome,b) == 0) /* equipa certa (mesmo nome) */

/* PROTOTIPOS DAS FUNCOES */

/* criacao de uma equipa */
equipa cria_equipa(chave_eq nome); 
/* eliminacao de uma equipa */
void apaga_equipa(equipa e);
/* incrementa/decrementa o numero de vitorias de uma equipa */
void muda_vitorias(equipa e, char op);
/* escrita de uma equipa no stdout - formatos do comando P */
void escreve_equipa(int nL, equipa e);
/* escrita do nome de uma equipa - formatos do comando g*/
void escreve_equipa_g(int nL, chave_eq nome);

#endif
