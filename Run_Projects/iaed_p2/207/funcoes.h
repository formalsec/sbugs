#ifndef FUNC
#define FUNC
#define VETOR_HASH_SZ 20

typedef struct jogo {
	char *nome, *equipa1, *equipa2;
	int score1, score2;
} *JOGO;


typedef struct equipa {
	char *nome;
	int vitorias;
} *EQUIPA;

/* Estrutura Principal */
typedef struct principal {

	struct jogo** hashJogo;		/* Hash Table */
	struct equipa** hashEquipa;		/* Hash Table */
	struct equipa** lista_equipas;		/* Vetor */
	struct node_jogo* lista_jogos;		/* Lista ligada */


	int input_contador;
	int tamanho_jogos;
	int tamanho_equipas;
	int cap_jogos;
	int cap_equipas;

} *PRINCIPAL;


typedef struct node_jogo {
	struct jogo* jogo;
	struct node_jogo* next;
} *NODE;


/* processa_comando */
int get_comando(PRINCIPAL p);
int exe_comando(char action, char *args, PRINCIPAL p);

/* comandos */
PRINCIPAL init_stPrincipal(PRINCIPAL p);
char *strdup(const char *src);
int hashCode(char *str, int tamanho);
int insert_jogo(JOGO j, PRINCIPAL p);
void delete_jogo(char *jogo_nome, PRINCIPAL p);
int procura_jogo(char *jogo_nome, PRINCIPAL p);
void display_jogo(PRINCIPAL p);

/* Hash_e */
void adiciona_vitoria(char *equipa_nome, PRINCIPAL p);
void remove_vitoria(char *equipa_nome, PRINCIPAL p);
int procura_equipa(char *equipa_nome, PRINCIPAL p);
int insert_equipa(char* nome, PRINCIPAL p);
void delete_equipa(char *equipa_nome, PRINCIPAL p);
void display_equipa(PRINCIPAL p);

/* Hash_j */
int adiciona_jogo(JOGO j, PRINCIPAL p);
int adiciona_equipa_cmd(char* nome, PRINCIPAL p);
void lista_jogos(PRINCIPAL p);
int procura_jogo_cmd(char *nome, PRINCIPAL p);
int procura_equipa_cmd(char *nome, PRINCIPAL p);
void remove_jogo_cmd(char *nome, PRINCIPAL p);
void altera_score_cmd(char *nome, int score1, int score2, PRINCIPAL p);
int compare(const void *a, const void *b);
void lista_melhor_equipas(PRINCIPAL p);
JOGO copia_jogo(JOGO jogo1, JOGO jogo2);
void free_jogo(JOGO jogo);

/* lista_ligada */
NODE new_node(JOGO j);
NODE insert_node(NODE head, JOGO j);
NODE procura_node(NODE head, JOGO j);
NODE delete_node(NODE head, char* nome);
void FREEnode(NODE t);
void freeList(NODE head);
#endif