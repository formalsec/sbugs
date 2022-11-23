#ifndef equipas
#define equipas

/*Estrutura que representa as equipas*/
typedef struct equipa{
    char*nome;
    int vitorias;
    struct equipa*next, *prev;
}equipa;

/*Estrutura que representa os jogos*/
typedef struct jogo{
    char*nome;
    equipa *e1;
    equipa *e2;
    int resultado1;
    int resultado2;
    struct jogo*next, *prev;
}jogo;

/*Estrutura que representa a lista das equipas*/
typedef struct {
    equipa*head,*last;
}lista_e;

/*Estrutura que representa a lista dos jogos*/
typedef struct {
    jogo*head,*last;
}lista_j;

/*Funcao que inicializa a lista das equipas*/
lista_e*  mk_lista_e();

/*Funcao que inicializa a lista dos jogos*/
lista_j*  mk_lista_j();

/*Funcao para adicionar uma equipa a lista das equipas*/
void add_last_equipa(lista_e*l,const char*n);

/*Funcao para adicionar um jogo a lista dos jogos*/
void add_last_jogo(lista_j*l,const char*n, equipa *e1, equipa *e2, int o, int i);

/*Funcao para procurar uma equipa*/
equipa* lookup_e(char* text);

/*Funcao para procurar um jogo*/
jogo* lookup_j(char* text);

/*Funcao que remove a lista das equipas*/
void free_list_equipa(lista_e*l);

/*Funcao que remove a lista dos jogos*/
void free_list_jogo(lista_j*l);

/*Funcao que remove uma equipa da lista das equipas*/
void rm_equipa(lista_e*l,equipa*n);

/*Funcao que remove um jogo da lista dos jogos*/
void rm_jogo(lista_j*l,jogo*n);

#endif
