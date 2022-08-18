#ifndef proj2_h_j
#define proj2_h_j
#include "proj2_h_e.h"

typedef struct jogo{			/*Struct com as informacoes do jogo*/
	char* nome;
	int sco1, sco2;
	link_e equ1, equ2;
	struct jogo *next, *prev;
} *link_j;

typedef struct {				/*Struct com o primeiro e ultimo elemento da lista duplamente ligada*/
	struct jogo *head, *last;
}list_j;

typedef struct node_j{			/*Um node da hastable dos jogos*/
    link_j jo;
    struct node_j *next;
}*hash_link_j;

extern hash_link_j *head_h_j;	/*Hashtable dos jogos*/
/*Prototipos*/
list_j *mk_list_j();
void insertEnd_j(list_j* ls_j, char* n,link_e e1,link_e e2,int s1,int s2);
void Init_hash_j(int m);
void insert_h_j(link_j j);
link_j lookup_j(char *v);
void delete_h_j(link_j j);
void delete_j(list_j* ls_j, link_j j);

#endif
