#ifndef _JOGOS_
#define _JOGOS_

/* Definicao de estruturas relativas aos jogos e seus ponteiros e 
   declaracao de prototipos das funcoes relativas aos jogos. */

   
typedef struct jogo {
    char *nome;
    char *equipa1;
    char *equipa2;
    unsigned int score1;
    unsigned int score2; 
}jogo;

typedef jogo* jogo_ptr;

typedef struct node {
    jogo_ptr j;
    struct node* next;
}node;

typedef node* link;


typedef struct list {
    link head;
    link tail;
}list;

typedef list* lst_ptr;

void hash_init_jogo(link* heads);
link NEW_jogo(jogo_ptr jogo_ptr);
link insertBeginList_jogo(link head, jogo_ptr j);
void insertEnd_lista(lst_ptr lista, jogo_ptr j);
int hash_jogo(char *v);
void hash_insert_jogo(jogo_ptr j, link *heads_jogos);
jogo_ptr searchList_jogo(link head, char* nome_ptr);
jogo_ptr hash_search_jogo(char* nome, link* heads_jogos);
void removeItemList_jogo(char* nome, lst_ptr lista);
link removeItemList_jogo_hash(char* nome, link head, lst_ptr lista);
void hash_delete_jogo(char* nome, link* heads_jogos, lst_ptr lista);


#endif