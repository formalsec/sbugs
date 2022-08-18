#define MAXNOME 1024

/* Tipo generico para equipas ou jogos. */
typedef struct item {

  char * nome;
    
  char * e1, * e2;
  int s1, s2;

  int vitorias;

} * Item;


/* hasht.c ***************************************************************************************/

/* Tipo que guarda informacoes revelantes de uma Hashtable. */
typedef struct hasht {
  /* Localizacao da tabela */
  Item * endereco;
  /* Tamanho da tabela */
  int M; 
  /* Numero de elementos */
  int N;

} * Hashtable;

/* Separacao pelo nome */
typedef char * Key;

#define key(a) (a -> nome)
#define eq(a, b) (!strcmp(a, b))


/* lista.c ***************************************************************************************/

typedef struct node {

  Item jogo;
  struct node * next;
  struct node * prev;

} * link;


/* Prototipos ************************************************************************************/

/************ aux.c ******************************************************************************/

/* Devolve um ponteiro para uma string dada. */
char * cria_pchar(char str[]);
/* Aloca memoria para um Item; inicia os seus elementos. */
Item cria_item(char * n, char * e1, char * e2, int s1, int s2);
/* Liberta memoria alocada para um Item, incluindo a dos seus elementos. */
void free_item(Item item);
/* Imprime um Item que representa um jogo. */
void imprime_jogo(Item t, int NL);
/* Devolve Item equipa com maior score. */
Item vencedor (char * e1, char * e2, int s1, int s2, Hashtable hasht);
/* Funcao auxiliar para realizar o qsort (de strings). */
int compara(const void * a, const void * b);

/************ hasht.c ****************************************************************************/

/* Determina posicao do Item de nome "n" na tabela. */
int hash(char * n, int M);
/* Aloca memoria para uma tabela; inicia os seus elementos. */
Hashtable cria_hash(int max);
/* Insere um Item na tabela. */
void insere_hash(Item item, Hashtable hasht);
/* Devolve o Item de nome "n" da tabela. */
Item procura_hash(Key n, Hashtable hasht);
/* Remove um Item jogo de nome "n" da tabela e retorna-o. */
Item apaga_hash(Key n, Hashtable hasht);
/* Liberta a memoria alocada para a tabela, incluindo a dos seus Items. */
void liberta_hash(Hashtable hasht);

/************ lista.c ****************************************************************************/

/* Insere um Item jogo no inicio da lista. */
void insere_lista(Item jogo, link * head);
/* Remove um Item jogo da lista. */
void apaga_lista(Item jogo, link * head);
/* Imprime todos os elementos da lista. */
void imprime_lista(int NL, link head);
/* Liberta a memoria alocada para a lista. */
void liberta_lista(link head);

/************ funcoes.c **************************************************************************/

/* Adiciona um novo jogo. */
void __a__(int NL, Hashtable hash_j, Hashtable hash_e, link * head);
/* Adiciona uma nova equipa. */
void __A__(int NL, Hashtable hasht);
/* Lista todos os jogos introduzidos. */
void __l__(int NL, link head);
/* Procura um jogo com o nome dado. */
void __p__(int NL, Hashtable hasht);
/* Procura uma equipa com o nome dado. */
void __P__(int NL, Hashtable hasht);
/* Apaga um jogo dado um nome. */
void __r__(int NL, Hashtable hash_j, Hashtable hash_e, link * head);
/* Altera o score de um jogo dado o nome. */
void __s__(int NL, Hashtable hash_j, Hashtable hash_e);
/* Lista as equipas que ganharam mais jogos. */
void __g__(int NL, Hashtable hasht);
