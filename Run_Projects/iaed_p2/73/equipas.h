#ifndef _EQUIPAS_
#define _EQUIPAS_


/* Estrutura que serve de ponte entre equipas, correspondendo-lhe uma equipa */
typedef struct Link_Equipa
{
    char *nome_equipa;
    int numero_vitorias;
    struct Link_Equipa *next;
} link_equipa;


/* Estrutura que define o inicio de cada lista da hashtable */
typedef struct
{
    link_equipa *next;
} link_hashtable_equipas;


/* Hashtable com um tamanho maximo e um vetor de "cabecas" correspondentes as suas hashes */
typedef struct
{
    int tamanho_maximo;
    link_hashtable_equipas *vetor_hashes;

} hashtable_equipas;


/* Funcoes para a manipulacao de equipas */
hashtable_equipas* inicializa_equipas(int tamanho_maximo);
void adicionar_equipa(char *nome_equipa, hashtable_equipas *equipas);
link_equipa* procurar_equipa (char *nome_equipa, hashtable_equipas *equipas); 
void listar_melhores_equipas(hashtable_equipas *equipas, int linha_input);
void destruir_equipas(hashtable_equipas *equipas);

#endif