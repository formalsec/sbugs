#ifndef proj2_h_e
#define proj2_h_e

typedef struct equipa{			/*Struct com as informacoes da equipa*/
	char *nome;
	int jogos_ganhos;
	struct equipa *next, *prev;
} *link_e;
	
typedef struct {				/*Struct com o primeiro e ultimo elemento da lista duplamente ligada*/
	link_e head, last;
}list_e;

typedef struct node_e{			/*Um node da hastable das equipas*/
    link_e eq;
    struct node_e *next;
}*hash_link_e;

extern hash_link_e *head_h_e;	/*Hashtable das equipas*/
/*Prototipos*/
list_e *mk_list_e();
void insertEnd_e(list_e* ls_e, char* n);
void Init_hash_e(int m);
void insert_h_e(link_e e);
link_e lookup_e(char *v);
void delete_h_e(link_e e);
void delete_e(list_e* ls_e, link_e e);

#endif
