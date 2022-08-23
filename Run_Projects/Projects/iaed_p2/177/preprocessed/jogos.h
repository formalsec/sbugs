#ifndef JOGOS_H
#define JOGOS_H

#define DIM 1024

/*Estrutura com o nome e as caracteristicas de cada jogo.*/
typedef struct person {
    char *nome, *equipa1, *equipa2;  
    int score1, score2, eliminado;
    struct person *next;
}*pPerson;

/*Estrutura da lista que vai conter os  jogos-*/
typedef struct  {
    struct person *head, *last;
} lista;

/*Estrutura da hash table que vai conter os jogos.*/
typedef struct perso {
    pPerson *v;
    int elementos, tamanho;
}*jogo;

/*lista onde guardo os jogos pela ordem de insercao*/

/*Inicializa a lista onde vou guardar os jogos.*/
lista* inicializa_lista();
/*Faz print dos jogos desde a head (inicio) ate 
ao last (ultimo elemento da lista).*/
void print(lista *l, int nl);


/*hash table onde guardo os jogos*/

/*Funcao esta nos slides*/
int hash(char *v, int M);
/*Inicializa a hash table de procura linear onde vou inserir os jogos.*/
jogo inicializa_jogo(jogo st1, int m);
/*Liberta toda a memoria ocupada pela hash table.*/
jogo destroi_jogo(jogo st);
/*Funcao auxiliar da funcao re_hash_jogo.*/
jogo insere(jogo st, pPerson v, char *name);
/*Fucao auxiliar da funcao insere_jogo. Insere todos os elementos
da hash antiga numa nova mas com o dobro do tamanho.*/
jogo re_hash_jogo(jogo st);
/*Insere o jogo nome na hash table e no fim da lista e caso 
o numero de elementos seja metade do tamanho da hash aumenta
o seu tamanho para o dobro*/
jogo insere_jogo(jogo st, lista *l, char*name, char *equipa1, char *equipa2, int score1, int score2);
/*Averigua se existe algum jogo com o nome nome na hash table.
Caso exista retorna 1 e caso contrario retorna 0.*/
int pertence_jogo(jogo st1, char *name);
/*Faz print do jogo nome*/
void print_jogo(jogo st1, char *nome, int nl);
/*Atualiza o score do jogo nome para os novos scores: score1 e score2.*/
jogo altera_score(jogo st1, char *nome, int novo_score1, int novo_score2);
/*Elimina um jogo, ou seja, altera a componente eliminado da 
estrutura jogo anteriormente a 0 para 1.*/
jogo elimina_jogo(jogo st, char*nome);

#endif
