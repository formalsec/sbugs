#define STRING_SIZE 1024
#define TAM_TABELA 1553
#define EXISTE 1
#define NAO_EXISTE 0
#define SIM 1
#define NAO 0


/* estrutura da linked list da equipas e da equipas */
typedef struct equipa{
	char* nome;						/* nome da equipa */
	unsigned int nr_vitorias;		/* numero de vitorias */
	struct equipa* next;			/* ponteiro pra prox node_equipa */
} link_equipa;

typedef struct{
	link_equipa **entries;			/* ponteiro para um ponteiro */
}ht_equipas;


/* declaracao de funcoes */
unsigned int hash(const char *nome);

ht_equipas *ht_init_equipas(void);

link_equipa *st_search(ht_equipas *hashtable, const char *nome);

void ht_pair_equipas(ht_equipas *hashtable_equipas, const char *nome);
void ht_set_equipas(ht_equipas *hashtable, const char *nome, int NL);
void ht_search_equipas(ht_equipas *hashtable, const char *nome, int NL);