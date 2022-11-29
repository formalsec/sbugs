#ifndef PROJ2_AUX_H
#define PROJ2_AUX_H

#define MAX_ENTRADA 4000 /*Numero maximo de carateres que o input pode ter.*/
#define ESPACO " " /*Carater que separa o comando do restante input.*/
#define SEPARADOR ":" /*Carater que separa os atributos do input.*/
#define NOVA_LINHA "\n" /*Carater de nova linha.*/
#define TAMANHO_TABELA 23 /*Tamanho da tabela de dispersao, numero primo.*/

typedef struct equipa{  /*Define uma equipa como uma estrutura com um nome e um numero de vitorias.*/
    char *nome;
    int vitorias;
    struct equipa *equipa_seguinte; /*Aponta para a proxima equipa na lista de equipas.*/
    struct equipa *prox_tabela; /*Aponta para a proxima equipa na tabela de dispersao.*/
    struct equipa *prox_vit_max; /*Aponta para a proxima equipa na lista de vitorias maximas.*/
    struct equipa *anterior_vit_max; /*Aponta para a equipa anterior na lista de vitoria maximas.*/
}Equipa;

typedef struct jogo{    /*Define um jogo como uma estrutura com um nome, duas equipas e dois scores.*/
    char *nome;
    Equipa *equipa1;
    Equipa *equipa2;
    int score1;
    int score2;
    struct jogo *jogo_seguinte; /*Aponta para o proximo jogo na lista de jogos.*/
    struct jogo *jogo_anterior; /*Aponta para o jogo anterior na lista de jogos.*/
    struct jogo *prox_tabela;   /*Aponta para o proximo jogo na tabela de dispersao.*/
    struct jogo *anterior_tabela;   /*Aponta para o jogo anterior na tabela de dispersao.*/
}Jogo;

typedef struct tabela_equipas{ /*Define uma tabela de equipas como uma estrutura que guarda dois ponteiros.*/
    Equipa *primeira_equipa;
    Equipa *ultima_equipa;
}Tabela_equipas;

typedef struct tabela_jogos{ /*Define uma tabela de jogos como uma estrutura que guarda dois ponteiros.*/
    Jogo *primeiro_jogo;
    Jogo *ultimo_jogo;
}Tabela_jogos;

typedef struct lista_jogos_equipas{ /*Define uma lista de jogos e equipas que guarda os ponteiros*/
    Jogo *primeiro_jogo;            /*para o primeiro e ultimo jogos inseridos e para a primeira e*/
    Jogo *ultimo_jogo;              /*ultima equipa inseridas. Guarda tambem os ponteiros para as*/
    Equipa *primeira_equipa;        /*tabelas de dispersao de jogos e equipas.*/
    Equipa *ultima_equipa;
    Tabela_equipas *tab_equipa[TAMANHO_TABELA];
    Tabela_jogos *tab_jogo[TAMANHO_TABELA];
}Lista_jogos_equipas;

/*DECLARACOES DE TODAS AS FUNCOES AUXILIARES AOS COMANDOS*/

/*Cria e retorna uma lista_jogos_equipas.*/
Lista_jogos_equipas* cria_lista();

/*Cria e retorna uma lista de equipas.*/
Tabela_equipas* cria_lista_equipas();

/*Funcao de dispersao para adicionar as equipas e jogos as respetivas tabelas de dispersao.*/
int hash(char *b);

/*Adiciona uma nova equipa ao sistema, caso a equipa ainda nao exista.*/
Equipa* adiciona_equipa(char *atr1);

/*Procura e retorna uma equipa a partir do nome.*/
Equipa* procura_nome_equipa(Lista_jogos_equipas *lje, char *atr1);

/*Adiciona um novo jogo ao sistema, caso o jogo ainda nao exista e ambas as equipas existam.*/
Jogo* adiciona_jogo(char *atr1, Equipa *equipa_1, Equipa *equipa_2, char *atr2, char *atr3);

/*Procura e retorna um jogo a partir do nome.*/
Jogo* procura_nome_jogo(Lista_jogos_equipas *lje, char *atr1);

/*Procura o numero maximo de vitorias.*/
int procura_max_vitorias(Lista_jogos_equipas *lje);

/*Procura as equipas que ganharam o numero maximo de jogos
e retorna uma lista com essas equipas.*/
Tabela_equipas* procura_equipa_vitorias(Lista_jogos_equipas *lje, int num_max_vitorias);

/*Ordena e imprime as equipas que ganharam o numero maximo de jogos
e liberta a lista dessas equipas.*/
void ordena_equipa_vitorias( Tabela_equipas *lista_mais_ganhos, int NL, int num_max_vitorias);

/*Liberta toda a memoria alocada do sistema.*/
void free_lista(Lista_jogos_equipas *lje);

#endif