#ifndef COMANDOS_H
#define COMANDOS_H

/* Prototipos das Funcoes */

/* Adiciona um novo jogo */
void novo_jogo(lstJogos lista, hashJogos hash_jogos, hashEquipas hash_equipas, int nl);
/* Adiciona uma nova equipa */
void nova_equipa(lstEquipas lista, hashEquipas hash_equipas, int nl);
/* Lista todos os jogos pela ordem em que foram introduzidos */
void listar_jogos(lstJogos lista, int nl);
/* Procura o jogo com o nome dado */
void procurar_jogo(hashJogos hash_jogos, int nl);
/* Procura a equipa com o nome dado */
void procurar_equipa(hashEquipas hash_equipas, int nl);
/* Apaga o jogo com o nome dado */
void apagar_jogo(lstJogos lista, hashJogos hash_jogos, int nl);
/* Altera a pontuacao do jogo com o nome dado */
void alterar_pontuacao(hashJogos hash_jogos, int nl);
/* Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica */
void mais_vitorias(lstEquipas lista, int nl);
/* Liberta toda a memoria associada 'as listas, 'as hashtables, 'as equipas e aos jogos */
void terminar_prog(lstJogos lista_jogos, lstEquipas lista_equipas, hashJogos hash_jogos, hashEquipas hash_equipas);
/* Funcao de comparacao passada como argumento do qsort(), utilizada para comparar strings */
int comparar_str(const void *str1, const void *str2);

#endif