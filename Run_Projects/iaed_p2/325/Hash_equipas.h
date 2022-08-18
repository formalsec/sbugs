#ifndef Hash_equipas_H
#define Hash_equipas_H

/* Lista ligada em que cada elemento guarda um nome de uma equipa e o numero de jogos ganhos dessa.
 */
typedef struct str_equipa {
    char *nome_equipa;
    int jogos_ganhos;
    struct str_equipa *next;
} * Equipas_hash;

/* Funcao auxiliar da insert_equipa que aloca memoria para a criacao de uma nova equipa, e
 * inicializa as variaveis que estao incluidas nessa equipa. */
Equipas_hash NEWE(char *buffer);

/* Funcao auxiliar da insert_equipa que inserte uma nova equipa no inicio de uma lista ligada na
 * Hashtable. */
Equipas_hash insertBeginE(Equipas_hash head, char *buffer);

/* Funcao que inserte uma nova equipa na Hashtable. */
void insert_equipa(Equipas_hash *todas_equipas, char *nome, int E);

/* Funcao que inicializa a Hahstable alocando memoria. */
Equipas_hash *init_e(int E);

/* Funcao auxiliar da Search que percorre a Hashtable ate encontrar a equipa pretendida. */
Equipas_hash search_listE(Equipas_hash head, char *n);

/* Funcao que retorna uma certa equipa que pertence a Hashtable. */
Equipas_hash SearchE(Equipas_hash *todas_equipas, char *nome, int E);

/* Funcao que elimina todos as equipas armazenadas na Hashtable,
e liberta toda a memoria que esta ocupava. */
void destroy_equipas(Equipas_hash *e, int E);

#endif