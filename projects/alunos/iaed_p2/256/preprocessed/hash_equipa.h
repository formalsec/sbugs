#ifndef hash_table
#define hash_table
#include "equipas.h"

/*Tamanho da hash table*/
extern int M;

/*Head da hash table das equipas*/
extern equipa **head_hash_e;

/*Head da hash table dos jogos*/
extern jogo **head_hash_j;

/*Funcao de dispersao*/
int hash(char *v, int M);

/*Funcao que inicia a hash table das equipas*/
void init_hash_equipa(int m);

/*Funcao que inicia a hash table dos jogos*/
void init_hash_jogo(int m);

/*Funcao para inserir uma equipa na hash table das equipas*/
void hash_equipa_insert(equipa*p);

/*Funcao para inserir um jogo na hash table dos jogos*/
void hash_jogo_insert(jogo*p);

/*Funcao para apagar um jogo da hash table dos jogos*/
void hash_delete_j(char*id);

#endif
