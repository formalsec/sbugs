#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "estruturas.h"
/*esta constante define o tamanho da hashtable*/
#define M 997
typedef struct str_jogos{
    Jogo jogo;
    struct str_jogos *next;
} *lista_jogos;

typedef struct str_equipas{
    Equipa equipa;
    struct str_equipas *next;
} *lista_equipas;

/*a head e o last vao facilitar a insercao da lista jogos no final
 e a listagem destes por ordem */
typedef struct{
    lista_jogos head,last;
}lista;



lista* lista_por_ordem_inicializar();

/*prototipos das funcoes referentes a hashtable das equipas e jogos
 e a linked list */
void lista_por_ordem_add(lista *l,Jogo jogo1);
void apagar_jogo_lista_por_ordem(lista *l, char *nome);
/*esta funcao faz parte do main decidi mante la aqui por questoes de organizacao*/
void listar_jogos(lista *l, int count);
lista_jogos* lst_inicializar_jg(lista_jogos *heads_jg);
lista_equipas* lst_inicializar_eq(lista_equipas *heads_eq);
void JGinserir(lista_jogos *heads_jg, Jogo jogo);
void EQinserir(lista_equipas *heads_eq,Equipa equipa);
lista_jogos inserirInicio_da_Lista_JG(lista_jogos head_jg,Jogo jogo);
lista_equipas inserirInicio_da_Lista_EQ(lista_equipas head_eq,Equipa equipa);
lista_jogos procuraLista_jg(lista_jogos head_jg,char *nome_jogo);
lista_equipas procuraLista_eq(lista_equipas head_eq, char *nome_equipa);
lista_jogos JGprocurar(lista_jogos *heads_jg, char *nome_jogo);
lista_equipas EQprocurar(lista_equipas *heads_eq, char *nome_equipa);
void free_heads_jg(lista_jogos *heads_jg);
void free_heads_eq(lista_equipas *heads_eq);
void free_head(lista *l);
lista_jogos Elimina_jogo_aux(lista_jogos head_jg, char *nome);
void Elimina_jogo(lista_jogos *heads_jg, char *nome);

#endif