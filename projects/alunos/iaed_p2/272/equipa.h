#ifndef EQUIPA
#define EQUIPA

/* Definicao das variaveis para o numero de gavetas da hash table das equipas, e o 
numero de caracteres do nome */

#define EQUIPA_GAVETAS 1024
#define MAX_EQUIPA_NOME 1024

/* Definicao da estrutura equipa */

struct Equipa {
    /* Ponteiro que indica o nome da equipa */
    char *nome;
    /* Numero de vitorias dessa equipa */
    int wins;
    /* Ponteiro que indica a equipa que vem a seguir */
    struct Equipa *next_equipa;
};

/* Estrutura onde vamos inserir todas as equipas existentes */
struct Equipas {
    /* Ponteiro que direciona ao numero de gavetas totais que temos na hash table */
    struct Equipa *gavetas[EQUIPA_GAVETAS];
    /* Numero total de equipas */
    int nequipas;
    
    /* Vetor de ponteiros onde vamos colocar as equipas por ordem de insercao na 
    base de dados */
    struct Equipa **ordem;
};

/* Chamada das funcoes que pretendemos usar */
void adiciona_equipa(struct Equipas*equipas,int comandos_total);
void procura_equipa(struct Equipas*equipas,int comandos_total);
void melhores_equipas(struct Equipas*equipas,int comandos_total);


#endif
