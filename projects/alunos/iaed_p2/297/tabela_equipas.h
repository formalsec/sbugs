#ifndef TABELA_EQUIPAS_H
#define TABELA_EQUIPAS_H
#include <stdlib.h>

#define INIC_CAP_E  1013            /*  Capacidade da tabela das equipas */
#define MAX_FLAG_SZ 1023            /*  Numero maximo de caracteres do nome da equipa */    
#define INVALID_E   -1              /*  Indicacao de que algo nao pertence a esta representacao */
#define ITEM char*                  /*  Definicao do tipo item a trocar */


/*  Troca elementos de tipo Item */
#define exch(X, Y) { ITEM t = X; X = Y; Y = t; }  

/*  Verifica igualdade entre strings */
#define equal_e(A, B) strcmp(A, B) == 0

/*  == Representacao do tipo estrutura de dados
 
 *  - hashtable de procura linear cujos elementos sao estruturas de equipa
 *  - organizados de acordo com a sua hash
 *  - referencia o proprio pointer da equipa
 
 *  == Fim da representacao */

/*--------------------------------------Estruturas--------------------------------------*/

/*  Estrutura de uma equipa */
typedef struct str_equipa{
    char* flag;
    size_t vitorias;
}equipa;

/*  Estrutura da tabela de equipas */
typedef struct h_t_equipas{
    equipa** tb;
    size_t capacidade, sz;
}equipas;

/*----------------------------Prototipos->Funcoes Principais----------------------------*/

/*  Inicializa tabela de equipas alocando o espaco suficiente */
equipas* inic_equipas(size_t max);

/*  Procura equipa. Se nao existir retorna NULL, caso contrario a hash da e */
int procura_e(const char* flag, equipas* tb_e);

/*  Adiciona uma equipa a tabela de equipas */
equipas* insere_e(size_t vit, const char* flag, equipas* tb_e);

/*  Devolve o numero de strings correspondentes ao nome das melhores equipas da tabela */
size_t n_strings(size_t max, equipas* tb_e);

/*  Devolve o maior numero de jogos ganhos das equipas da tabela */
size_t max_vitorias(equipas* tb_e);

/*  Encontra as melhores equipas da tabela, devolvendo os nomes correspondentes */
char** encontra_melhores(size_t n_strings, size_t max, equipas* tb_e);

/*  Liberta toda a memoria alocada dos jogos e da tabela */
void free_equipas(equipas* tb_e);

#endif