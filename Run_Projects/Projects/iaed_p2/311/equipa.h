#ifndef EQUIPA
#define EQUIPA

typedef struct equipa
{
	int wins;
	char *nome;
} *Equipa;

typedef struct lista_equipa
{
	Equipa equipa;
	struct lista_equipa *next;
} *link_E;

typedef link_E *hashE;

/* a maior parte das funcoes aqui encontram-se nos slides ou sao self-explanatory*/

int lengthE(link_E head);

link_E NewE(Equipa equipa);

link_E insertBeginE(link_E head, Equipa equipa);

link_E lookupE(link_E head, char *nome);

link_E deleteE(link_E head, char *nome);

void printNodeE(link_E head);

void free_nodesE(link_E head);

void free_listaE(link_E head);

hashE inicia_hash_equipa(int M);

hashE insere_hash_equipa(hashE equipas, Equipa equipa, int M);

void free_hashE(hashE equipas, int M);

link_E procura_hash_equipa(hashE equipas, char *nome, int M);

int compara(const void *e1, const void *e2);

void print_lista_equipa(link_E head, int contador);

#endif