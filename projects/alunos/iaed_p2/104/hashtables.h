#ifndef HASHTABLES_H
#define HASHTABLES_H

/* Definicao de Tipos */

/* Equipas */

typedef lstEquipas *hashEquipas;

/* Jogos */

typedef lstJogos *hashJogos;

/* Prototipos das Funcoes */

/* Funcao de dispersao */
int hash();

/* Equipas */

/* Cria uma hashtable de equipas */
hashEquipas criar_hash_equipas();
/* Adiciona a equipa 'a hashtable */
void adicionar_equipa_hash(hashEquipas hash_equipas, ptrEquipa equipa);
/* Procura na hashtable a equipa com o nome dado */
linkEquipa procurar_equipa_hash(hashEquipas hash_equipas, char *nome);
/* Recebe uma hashtable de equipas e liberta a memoria a ela associada */
void apagar_hash_equipas(hashEquipas hash_equipas);

/* Jogos */

/* Cria uma hashtable de jogos */
hashJogos criar_hash_jogos();
/* Adiciona o jogo 'a hashtable */
void adicionar_jogo_hash(hashJogos hash_jogos, ptrJogo jogo);
/* Procura na hashtable o jogo com o nome dado */
linkJogo procurar_jogo_hash(hashJogos hash_jogos, char *nome);
/* Remove da hashtable o jogo que se encontra no no' dado */
void remover_jogo_hash(hashJogos hash_jogos, linkJogo jogo);
/* Recebe uma hashtable de jogos e liberta a memoria a ela associada */
void apagar_hash_jogos(hashJogos hash_jogos);

#endif