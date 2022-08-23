#ifndef estruturas
#define estruturas
#define M 1013

/* Estrutura de uma equipa*/
typedef struct equipa{
    char *nome;
    int vitorias;
}equipas;

/* Estrutura correspondente ao no de uma equipa*/
typedef struct no_equipa{
    equipas *p;
    struct no_equipa *next;
}no_equipa;

/* Estrutura de um jogo*/
typedef struct jogos{
    char *nome;
    equipas *equipa1;
    equipas *equipa2;
    int resultado1;
    int resultado2;
}jogos;

/*Estrutura correspondente ao no do jogo*/
typedef struct no_jogo{
    jogos *p;
    struct no_jogo *next,*previous;
}no_jogo;

/*Estrutura da hash table dos jogos*/
typedef struct{
    no_jogo *heads[M];
}acede_jogos;

/*Estrutura da hash table das equipas*/
typedef struct lista_equipa{
    no_equipa *heads[M];
}lista_equipas;

/*Estrutura do no da lista ligada normal das equipas*/
typedef struct no_equipa_normal{
    equipas *p;
    struct no_equipa_normal *next;
}no_equipa_normal;

/*Estrutura da cabeca e do ultimo elemento da lista ligada normal das equipas*/
typedef struct{
    no_equipa_normal *head,*last;
}acede_equipa_normal;

/*Estrutura dos jogos que vao ser adicionados a lista ligada dos jogos que nao corresponde a hash table*/
typedef struct jogos_normais{
    char *nome;
    equipas *equipa1;
    equipas *equipa2;
    int resultado1;
    int resultado2;
}jogo_normal;

/*Estrutura do no da lista ligada normal dos jogos*/
typedef struct no_jogo_normal{
    jogo_normal *p;
    struct no_jogo_normal *next;
}no_jogo_normal;

/*Estrutura da cabeca e do ultimo elemento da lista ligada normal dos jogos*/
typedef struct{
    no_jogo_normal *head,*last;
}acede_jogo_normal;


/*Prototipos das funcao relacionadas com as estruturas*/
acede_equipa_normal* adiciona_equipa_fim(equipas *p,acede_equipa_normal *a);

jogo_normal* cria_no_jogo_normal(char *nome,equipas *equipa1,equipas *equipa2, int res1, int res2);

acede_jogo_normal* adiciona_jogo_fim(jogo_normal *p,acede_jogo_normal *a);

void inicia_normais(acede_equipa_normal *a,acede_jogo_normal *b);

int hash(char *v);

no_jogo* coloca_inicio_jogo(acede_jogos *lista,jogos *p);

jogos* procura_jogo(acede_jogos *lista,char *nome);

no_jogo* remove_jogo(acede_jogos *lista,char *nome);

acede_jogos* inicializa_jogo(acede_jogos *lista_ligada_jogos);

jogos* jogos_procura(char *nome,acede_jogos *lista_ligada_jogos);

void jogos_insere(jogos *p,acede_jogos *lista_ligada_jogos);

void jogos_apaga(char *nome,acede_jogos *lista_ligada_jogos);

jogos* cria_no_jogo(char *nome,equipas *equipa1,equipas *equipa2, int res1, int res2);

no_equipa* coloca_inicio_equipa(lista_equipas *lista,equipas *p);

equipas* procura_equipa(lista_equipas *lista,char *nome);

lista_equipas* inicializa_equipa(lista_equipas *lista_ligada_equipas);

equipas* equipa_procura(char *nome,lista_equipas *lista_ligada_equipas);

void equipa_insere(equipas *p,lista_equipas *lista_ligada_equipas);

equipas* cria_no_equipa(char *nome);
#endif