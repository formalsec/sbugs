#include "Jogo.h" 

/* Prototipos das funcoes referentes a hashtable */

Jogo* inicializa(int M);
Jogo* insere(Jogo jogo, Jogo *HashTable, int Tamanho_HashTable);
Jogo* apaga_jogo(Jogo *HashTable, char* nome, int Tamanho_HashTable);
Jogo* altera_score(char *nome, Jogo *HashTable, int Tamanho_HashTable);
int procura_indice(Jogo* Hashtable, char* nome, int tamanho_Hashtable);

Equipa* inicializa_equipas(int tamanho_Hashtable);
Equipa* insere_equipa(Equipa equipa, Equipa *Hashtable, int tamanho_Hashtable);
Equipa* atribui_vitoria(Equipa * Hashtable, char *equipa1, char *equipa2, int score1, int score2, int tamanho_Hashtable);
Equipa* retira_vitoria(Equipa * Hashtable, char *equipa1, char *equipa2, int score1, int score2, int tamanho_Hashtable);