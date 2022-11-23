#ifndef HASH_EQ
#define HASH_EQ
#define MAX_TABELA 1000


typedef struct equipa{
    char *nome; /*nome da equipa*/
    int ganhos; /*numero de jogos vencidos*/
    struct equipa* next;
}equipa;



void inserir_tabela_equipa(equipa *j,equipa *tabela_hash_equipa[MAX_TABELA]);
equipa *procura_tabela_equipa(char *nome,equipa *tabela_hash_equipa[MAX_TABELA]);
void apaga_mem_equipa(equipa *tabela_hash_equipa[MAX_TABELA]);


#endif