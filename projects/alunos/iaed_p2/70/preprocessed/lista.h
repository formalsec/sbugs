#define Max 1024

typedef struct equipa{
    char *nome;
    struct equipa *next;
    int i;
}equipa;

typedef struct jogo  {
    struct jogo * next, * previous;
    char *n_jogo;
    equipa *equipa1, *equipa2;
    int sc1,sc2;
} jogo;

typedef struct  {
    struct jogo *  head, * last;
} l_jogo;

typedef struct hash_jogo{
    struct jogo *nome;
    struct hash_jogo *next;
}hash_jogo;







/* cria um lista */
l_jogo* cria_list_jogo(l_jogo *l);
/*eliminar um lista */
void free_list_jogo(l_jogo* l);
/* acrecenta um jogo a lista*/
void add_jogo(l_jogo* l, char jog[Max],equipa* eq1,
    equipa* eq2,int sc1,int sc2);
/* Faz o print de todos os elementos da lista*/
void print(l_jogo *head,int nl);


/* cria uma hashtable para os jogos*/
hash_jogo** init(hash_jogo** hash_game,int m);
/* Indica a posicao da hashtable*/
int key(char nome[Max]);
/* Insere um novo jogo a uma head da hashtable dos jogos*/
hash_jogo* insertBeginList(hash_jogo* head, jogo*jog);
/*Insere um novo jogo a hashtable dos jogo*/
void insere_jogo(hash_jogo**head,char nome[Max],jogo*jog,int m);
/* Remove jogo da hashtable dos jogos e a lista dos jogos*/
hash_jogo* remove_jogo(hash_jogo*head,l_jogo *l,
     char nome[Max],int nl);

/* Remove jogo da hashtable dos jogos e a lista dos jogos*/
void remo_jog(hash_jogo**heads,char item[Max],
    l_jogo* l,int m, int nl);

/*Procura o jogo na hashtable dos jogos*/
jogo* searchList(hash_jogo* head, char item[Max]);
/*Procura o jogo na hashtable dos jogos*/
jogo* encontra_jogo(hash_jogo**heads,char item[Max],int m);

/* Elimina a hashtable das listas*/
void end(hash_jogo** head,int m);

/* Cria uma nova hashtable das equipas*/
equipa** init_eq(equipa** equipas,int m);
/*Insere uma nova equipa na hashtable das equipas*/
equipa* insertBeginList_eq(equipa* head, char*c);
/*Insere uma nova equipa na hashtable das equipas*/
void insere_equipa(equipa **head,char nome[Max],int m);
/* Procura uma equipa na hashtable das equipas*/
equipa* searchteam(equipa *equipas, char item[Max]);
/* Procura uma equipa na hastable das equipas*/
equipa* encontra_equipa(equipa **equipas,char item[Max],int m);

/*Procura o melhor resultado entra as equipas (sc1) e o 
    como o numero de equipas(*i)*/
int ent_meh(equipa* head, int sc1, int*i);
/* Procura o melhor resulta entre as equiaps na 
    hashtable das equipas e o numero de equipas com 
    esse resultaod*/
int encontr_melhor(equipa** equipas,int m, int sc1,int* i);
/* Procura as equipas com melhor resultado e insere 
    na tabela  haed*/
void procurar(equipa* hash, equipa**haed,int sc1,int sc2, int* i);
/* Procura as equipas com melhor resultado na hashtable e insere 
    na tabela  haed*/
void proc(equipa** hash,equipa**haed,int sc1,int m,int sc2);
/* Eliminar a hashtable da equipas*/
void end_q(equipa** equipas, int m);

/* Faz a particao da tabelas das equipas(head)*/
int particao(equipa**  head,int inicio,int fim);
/* Ordena um tabela de equipas(head) atravez do 
    algoritmo quicksort*/
void ordena_lista(equipa** head,int inicio, int fim);

