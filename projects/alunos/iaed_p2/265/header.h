#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Max_char 1023
#define Max_tam 509

int hashU(char *v, int M)
{
  int h, a = 31415, b = 27183;
  for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
    h = (a*h + *v) % M;
  return h;
}
typedef struct 
{
	char *nome_e;
	int ganhos;
}EQUIPE;
typedef struct htable_entrada_equipe
{
	struct htable_entrada_equipe *seguinte_e;
	EQUIPE *equipe;

}lugar_no_hash_e;
typedef struct
{
	char *nome_j;
	EQUIPE *equipa1;
	EQUIPE *equipa2;
	int score1;
	int score2;
}JOGO;
typedef struct htable_entrada_jogo
{
	struct htable_entrada_jogo *seguinte_j;
	JOGO *jogo;

}lugar_no_hash_j;

typedef struct node {
	JOGO *jogo;
	struct node *next;
} link;
link **iniciar_listinha(int m);
lugar_no_hash_e **iniciar_hash_equipe(int m);
EQUIPE *cria_equipe(char *nomee);
lugar_no_hash_e *adicionar_a_listinha_e(lugar_no_hash_e *point_e, EQUIPE *eq);
void adiciona_equipe(lugar_no_hash_e **hashtable_e,int NL);
void encontrar_equipe(lugar_no_hash_e **hashtable_e, int NL);
EQUIPE *encontrar_equipe_aux(char *names, lugar_no_hash_e **hashtable_e);
lugar_no_hash_j **iniciar_hash_jogo(int m);
link *listinha_da_ordem(link *apoint, JOGO *jogou);
JOGO *cria_jogo(char *nomej, EQUIPE *equipa_1, EQUIPE *equipa_2, int a, int b);
lugar_no_hash_j *adicionar_a_listinha_j(lugar_no_hash_j *point_j, JOGO *jg);
void adiciona_jogo(lugar_no_hash_j **hashtable_j, link **fila, lugar_no_hash_e **hashtable_e, int NL);
void lista_de_jogos(link **fila);
void encontrar_jogo(lugar_no_hash_j **hashtable_j,int NL);
JOGO *encontrar_jogo_aux(char *names, lugar_no_hash_j **hashtable_j);
