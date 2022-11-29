#ifndef DECLARACOES_H
#define DECLARACOES_H

#define MAXSTR 1024 /*Tamanho maximo das strings*/
#define HASHTABLESIZE_J 1000 /*Tamanho maximo da hastable dos jogos*/
#define HASHTABLESIZE_E 1000 /*Tamanho maximo da hastable das equipas */
#define TAM 200 /*Tamanho maximo do vetor de nomes*/
#define compara strcmp
#define copia strcpy
#define apaga free
#define chave(A) (A)
#define menor(A,B) (chave(A) < chave(B))
#define maior(A,B) (chave(A) > chave(B))

/*Cada estrutura jogo e caracterizada por um nome, duas equipas e a pontuacao de ambas as equipas*/
typedef struct jogo {
	char *nome;
	char *equipa1;
	char *equipa2;
	int p1;
	int p2;
} jogo;

/*Cada estrutura equipa e caracterizada por um nome*/
typedef struct equipa{
	int vitorias;
	char *nome;
} equipa;

/*Cada estrutura node_jogo e caracterizada por um jogo e um ponteiro para uma estrutura node_jogo*/
typedef struct node_jogo{
	jogo *j;
	struct node_jogo *next;
} node_jogo;

/*Cada estrutura node_equipa e caracterizada por uma equipa e um ponteiro para uma estrutura
 node_equipa */
typedef struct node_equipa{
	equipa e;
	struct node_equipa *next;
} node_equipa;

/*O ponteiro pata a estrutura node_jogo vai constituir a hashtable para os jogos*/
typedef node_jogo *link_j;

/*O ponteiro pata a estrutura node_equipa vai constituir a hashtable para as equipas*/
typedef node_equipa *link_e; 


/*Cada no da estrutura node_j e caracterizada por 2 ponteiros para um estrutura node_j e por
 um ponteiro que aponta para um jogo da hastable dos jogos */
typedef struct jogo_l {
	struct jogo_l * next, * previous;
	jogo *j;
} node_j;

/*Cada estrutura lista e responsavel por um ponteiro para uma estrutura node_j*/
typedef struct{
	node_j * head, * last;
} lista;


int hash(char *v, int M);
link_j pesquisa_jogo(link_j* heads_j, char* nome);
link_e pesquisa_equipa(link_e* heads_e, char* nome);
link_j cria_jogo_node(lista * ls, char* buffer_nome, char* buffer_equipa1,char* buffer_equipa2,int p1, int p2);
link_e cria_equipa_node(char* buffer_nome);
link_j insere_jogo_inicio(lista * ls, link_j head, char* nome, char* equipa1, char* equipa2, int p1, int p2);
link_e insere_equipa_inicio(link_e head, char* nome);
link_j insere_fim(link_j *head_lista, char* nome, char* equipa1, char* equipa2, int p1, int p2);
void adiciona_novo_jogo(lista * ls, link_j *heads_j, link_e *heads_e, int nl);
void adiciona_nova_equipa(link_e *heads_e , int *contador_equipas, int nl);
void le_lixo();
void proucura_jogo(link_j *heads_j, int nl);
void procura_equipa(link_e *heads_e, int nl);
void lista_jogos(lista * ls, int nl);
void altera_score(link_j* heads_j, link_e *heads_e, int nl);
void apaga_jogo(link_j* heads_j, link_e *heads_e, lista * ls, int nl);
link_j apaga_node_jogo(link_j head, char* nome);
void equipa_vitorias(link_e *heads_e, int *contador_equipas, int nl);
int comparador(const void *a, const void *b);
void limpa_ht_jogos(link_j *heads_j);
void limpa_ht_equipas(link_e *heads_e);
void limpa_lista(link_j *head_lista);
lista* cria_lista();
void limpa_lista_ligada(lista * l);
void remove_node(lista *l, node_j *n);
void adiciona_fim(lista * l, jogo* j);

#endif