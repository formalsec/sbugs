#ifndef STRUCTS_1
#define STRUCTS_1

/* Constantes e macros utilizadas */
#define TAMANHOHT 2039 /*Numero primo utilizado para tamanho das HashTables*/
#define MAXNOMEEQUIPA 1023 /*Tamanho maximo do nome das equipas*/
#define MAXNOMEJOGO 1023 /*Tamanho maximo do nome dos jogos */
#define LEITURA_NOME_EQUIPA "%1023[^:\n]" /*Macro para aleitura do nome de 1 equipa 
                                        (o numero usado deve ser igual a LEITURA_NOME_EQUIPA)*/
#define LEITURA_NOME_JOGO "%1023[^:\n]" /*Macro para a leitura do nome de 1 jogo 
                                        (o numero usado deve ser igual a LEITURA_NOME_JOGO)*/
#define LEITURA_JOGO_COMPLETO "%1023[^:\n]:%1023[^:\n]:%1023[^:\n]:%d:%d" /*Macro para a leitura das 
informacoes completas de 1 jogo(o 1o numero deve ser igual a LEITURA_NOME_JOGO, 2o e 3o devem
 ser iguais a LEITURA_NOME_JOGO)*/

#define LEITURA_ALTERA_GOLOS "%1023[^:\n]:%d:%d" /*Macro para a leitura dos dados para 
                                                    alteracao dos golos de 1 jogo*/




/* Estruturas(structs) utilizadas no projeto: */

/*No da lista simplesmente ligada das equipas*/
typedef struct NSE{
    struct NSE *proxequipa;
    char* equipa;  /* Nome da equipa */
    int vitorias;  /* Numero de vitorias */
}NoSimplesEquipas;


/*No da lista duplamente ligada dos jogos*/
typedef struct NDJ{
    struct NDJ *antjogo, *proxjogo;
    char *equipa1,*equipa2,*nomejogo; /* Nome das 2 equipas do jogo */
    int golos1, golos2; 
}NoDuploJogos;

/*Estrutura que guarda a cabeca e o ultimo no da lista duplamente ligada dos jogos*/
typedef struct LD {
    NoDuploJogos * cabeca,* ultimo;
}ListaDuplaJogo;


/*No da lista simplesmente ligada das colisoes da Hash Table dos jogos*/
typedef struct HNJ{
    struct HNJ *proxjogoh;
    NoDuploJogos *dadosjogo; /*Ponteiro para o no da lista duplamente ligada com os dados de 1 jogo*/
}HashNoJogos;

/*Hash Table dos jogos por encandeamento externo */
typedef struct HTJ{
    HashNoJogos **listasjog;
    int capacidade;
}HashTableJogos;


/*No da lista simplesmente ligada das colisoes da Hash Table das equipas*/
typedef struct HNE{
    struct HNE *proxequipah;
    NoSimplesEquipas *dadosequipa;/*Ponteiro para o no da lista simplesmente ligada com os dados de 1 equipa*/
}HashNoEquipas;

/*Hash Table das equipas por encadeamento externo */
typedef struct HTE{

    HashNoEquipas **listasequi;
    int capacidade;

}HashTableEquipas;

#endif
