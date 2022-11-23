#ifndef _EQUIPAS_
#define _EQUIPAS_ 


/* Definicao de estruturas relativas as equipas e seus ponteiros e 
   declaracao de prototipos das funcoes relativas aos equipas. */


typedef struct equipa {
    char *nome;
    unsigned int vitorias;
}equipa;

typedef equipa* equipa_ptr;

typedef struct node_e {
    equipa_ptr e;
    struct node_e* next;
}node_e;

typedef node_e* link_e;


void hash_init_equipa(link_e* heads_equipas);
link_e NEW_equipa(equipa_ptr equipa_ptr);
link_e insertBeginList_equipa(link_e head, equipa_ptr e);
int hash_equipa(char *v);
void hash_insert_equipa(equipa_ptr e, link_e* heads_equipas);
equipa_ptr searchList_equipa(link_e head, char* nome_ptr);
equipa_ptr hash_search_equipa(char* nome, link_e* heads_equipas);

#endif