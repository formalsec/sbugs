#ifndef jogos_H
#define jogos_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h" /* Ficheiro que contem as estruturas dos jogos e equipas utilizados no projeto */


/* Funcoes utilizadas na implementacao do sistema de gestao de base de dados de jogos amigaveis */

void Printar(listajogos *list);

/* Funcao auxiliar que permite calcular o indice de um determinado elemento de uma hashtable 
   INPUT: nome de um jogo ou de uma equipa
   OUTPUT: indice do mesmo na respetiva hashtable */
int Hash(char* received);


/* Funcao auxiliar que permite criar uma nova lista duplamente ligada e respetiva hashtable para os jogos 
   INPUT: (nada)
   OUTPUT: lista duplamente ligada e hashtable dos jogos */
listajogos* NovaListaJogos();


/* Funcao auxiliar que permite criar uma nova lista duplamente ligada e respetiva hashtable para as equipas 
   INPUT: (nada)
   OUTPUT: lista duplamente ligada e hashtable das equipas */
listaequipas* NovaListaEquipas();


/* Funcao auxiliar que permite, dado um nome de um jogo, procurar se o mesmo existe na hashtable 
   INPUT: lista de jogos (onde esta inicializada a hashtable) e nome do jogo
   OUTPUT: jogo (caso exista) ou NULL (caso o jogo nao exista) */
jogo* ProcuraJogoAuxiliar(listajogos *list, char* nomejogo);


/* Funcao auxiliar que permite, dado um nome de uma equipa, procurar se a mesma existe na hashtable 
   INPUT: lista de equipas (onde esta inicializada a hashtable) e nome da equipa
   OUTPUT: equipa (caso exista) ou NULL (caso a equipa nao exista) */
equipa* ProcuraEquipaAuxiliar(listaequipas *list1, char* equipanome);


/* Funcao auxiliar que permite, dado um nome de uma equipa, alocar memoria para uma nova equipa e 
atualizar a informacao na mesma 
   INPUT: lista duplamente ligada de equipas e nome da equipa
   OUTPUT: nova equipa */
equipa* NovaEquipa(char* equipanome, listaequipas *list1);


/* Funcao auxiliar que permite, dado toda a informacao de um jogo, alocar memoria para um novo jogo e 
atualizar a informacao no mesmo
   INPUT: lista duplamente ligada de jogos e toda a informacao referente a um jogo (nome, equipa1, equipa2,
   score1, score2)
   OUTPUT: novo jogo */
jogo* NovoJogo(char* nomejogo, char* equipa1nome, char* equipa2nome, int score1recebido, int score2recebido, listajogos *list);


/* Comando 'a':
	Funcao que permite, dado toda a informacao de um jogo, adiciona-lo a lista duplamemte ligada e a hashtable 
	e atualizar o numero de vitorias de cada equipa
   		INPUT: lista de jogos (onde esta inicializada a hashtable), lista de equipas (onde esta inicializada a hashtable)
   		nome do jogo, equipa1, equipa2, score1, score2 e contador de invocacao de comandos
   		OUTPUT: lista e hastable atualizadas */
listajogos* AdicionaJogo(listajogos *list, listaequipas *list1, char* nomejogo, char* equipa1nome, char* equipa2nome, int score1recebido, int score2recebido, int comando);


/* Comando 'p':
	Funcao que permite, dado um nome de um jogo, procurar se o mesmo existe na hashtable 
   		INPUT: lista de jogos (onde esta inicializada a hashtable), nome do jogo e contador 
   		de invocacao de comandos
   		OUTPUT: <nome-jogo> <nome-equipa1> <nome-equipa2> <score1> <score2> ou erro caso nao exista */
jogo* ProcuraJogo(listajogos *list, char* nomejogo, int comando);


/* Comando 'A':
	Funcao que permite, dado o nome de uma equipa, adiciona-la a lista duplamemte ligada e a hashtable 
   		INPUT: lista de equipas (onde esta inicializada a hashtable), nome da equipa e contador de invocacao de comandos
   		OUTPUT: lista e hastable atualizadas */
listaequipas* AdicionaEquipa(listaequipas *list1, char* equipanome, int comando);


/* Comando 'P':
	Funcao que permite, dado um nome de uma equipa, procurar se a mesma existe na hashtable 
   		INPUT: lista de equipas (onde esta inicializada a hashtable), nome da equipa e contador 
   		de invocacao de comandos
   		OUTPUT: <nome-equipa> <numero-vitorias> ou erro caso nao exista */
equipa* ProcuraEquipa(listaequipas *list1, char* equipanome, int comando);


/* Comando 'l':
	Funcao que permite listar todos os jogos introduzidos no sistema por ordem de chegada 
   		INPUT: lista de equipas (onde esta inicializada a hashtable) e contador de invocacao de comandos
   		OUTPUT: lista duplamente ligada de jogos */
void ListaJogos(listajogos* list, int comando);


/* Comando 'r':
	Funcao que permite, dado um nome de um jogo, apaga-lo da lista duplamente ligada e da hashtable 
   		INPUT: lista de jogos (onde esta inicializada a hashtable), nome do jogo e contador 
   		de invocacao de comandos
   		OUTPUT: lista e hashtable atualizadas */
listajogos* ApagaJogo(listajogos *list, listaequipas *list1, char* nomejogo, int comando);


/* Comando 's':
	Funcao que permite, dado um nome de um jogo, alterar o seu score na hashtable, bem como o numero de vitorias
	das equipas do jogo, consoante a alteracao do score
   		INPUT: lista de jogos (onde esta inicializada a hashtable), lista de equipas (onde esta inicializada a hashtable),
   		nome do jogo, score1, score2 e contador de invocacao de comandos
   		OUTPUT: lista e hashtable atualizadas */
listajogos* AlteraScore(listajogos *list, listaequipas *list1, char* nomejogo, int score1recebido, int score2recebido, int comando);


/* Comando 'g':
   Funcao que permite imprimir por ordem alfabetica de equipas com maior numero de vitorias
         INPUT: lista de equipas e contador de invocacao de comandos
         OUTPUT: equipas ordenadas */
void OrdenaEquipas(listaequipas *list1, int comando);

#endif
