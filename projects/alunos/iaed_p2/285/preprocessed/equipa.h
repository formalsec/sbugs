#define  MAXIMO_CARACTERES 1024 /* usado para definir maximo de caracteres numa string */
#define  NAO_ENCONTRA -1        /* usado para quando uma funcao de procura nao encontra o seu argumento */

/* hash function que vai ser usada tanto para as equipas como para os jogos */
unsigned hash(char *nome, int tamanho_Hashtable);

/*struct equipa representa uma equipa composta pelo seu nome e numero de vitorias */
struct equipa{
    char *Nome;
    int Vitorias;
};
/* Equipa e um ponteiro para equipa */
typedef struct equipa* Equipa;


struct lista_equipas{
    Equipa equipa;
    struct lista_equipas* next;
};

typedef struct lista_equipas* Lista_Equipas;

/* Prototipos das funcoes referentes as equipas e as suas listas */

int equipa_nova(char *nome, Equipa* Hashtable, int tamanho_Hashtable);
Equipa nova_equipa(char *nome);
int procura_equipa(Equipa* HashTable, int tamanho_Hashtable, int NL);
int verifica_equipas(char* equipa1, char *equipa2, Equipa* Hashtable, int tamanho_Hashtable);
int procura_indice_equipas(Equipa* Hashtable, char* nome, int tamanho_Hashtable);
Lista_Equipas insere_lista_equipas(Lista_Equipas lista, Equipa equipa);
int print_lista_equipas(Lista_Equipas lista, int NL);
int free_equipas(Lista_Equipas lista);
void mergesort(char** arr, int l, int r, char** arr2);
void merge(char** arr, int l, int m, int r, char** arr2);
char** cria_array(Lista_Equipas melhores, int contador);