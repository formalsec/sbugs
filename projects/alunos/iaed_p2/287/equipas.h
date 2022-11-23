#ifndef equipas_h
#define equipas_h
#define TAM_HASHTABLE_EQUI 997
#define key(a) (a->nome)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct equipa{
    char* nome; /* string de tamanho arbitrario */
    int vitorias; /* numero de vitorias de uma equipa */
};

typedef struct equipa* Equipa; /* pointer para uma equipa */

typedef char* Key; /* tipo da chave char* */


typedef struct node{
    Equipa equipa;
    struct node *next;
}*link_equi; /* link para a linked list das cadeias da hashtable */



/*Prototipos*/

void apaga_Equipa(Equipa a);
Equipa nova_Equipa(char* nome);
int compara_equipas(const void * a, const void * b);

int hash(Key nome, int tamanho);
int hashU(char *v,int tamanho);
link_equi * inicia_tab_equi(int m);
void insere_tab_equi(Equipa equipa,link_equi *equipas,int tamanho);
Equipa procura_tab_equi(Key v,link_equi *equipas, int tamanho);
link_equi insere_cadeia_equi(link_equi equi_slot,Equipa equipa);
Equipa procura_cadeia_equi(link_equi equi_slot,Key v);
link_equi removeItemList(link_equi equi_slot,Equipa equipa);
void apaga_tab_equi(link_equi*equipas);


#endif /* equipas_h*/
