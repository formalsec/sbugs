#define MAX 1023

typedef struct equipa{
    char nome_equipa[MAX];
    int numero_vit;
} Equipa;

typedef struct jogo{
    char nome[MAX];
    int score1, score2;
    Equipa equipa1;
    Equipa equipa2;
}Jogo;

typedef struct node1{
    Jogo jogos;
    struct node1 *seguinte;
}Node1;

typedef struct node2{
    Equipa eq;
    struct node2 *seguinte;
}Node2;

typedef Node1* link_jogo;
typedef Node2* link_equipa;

/*insere elementos na hash*/
void inserir_hash_jogo(link_jogo *tab, int M, char nome[MAX], char equipa1[MAX], char equipa2[MAX], int score1, int score2);

/*procura na hash pelo nome*/
link_jogo procura_hash(link_jogo *tab, char *nome, int M);

/*apaga o no*/
void apaga_node(link_jogo no);

/*apaga os elementos da hash*/
void apaga_hash(link_jogo *tab, int M);

/*remove elemento da hash pelo nome*/
void remove_hash_el(link_jogo *tab, char *nome, int M);

link_jogo novo_jogo(char nome[MAX], char equipa1[MAX], char equipa2[MAX], int score1, int score2);





