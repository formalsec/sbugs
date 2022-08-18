#include "tabdispercao.h"
#include <stdlib.h>
#include <string.h>

/* Funcao usada para calcular o lugar na tabela de dispercao onde vai ficar
 * um certo item que tem como chave uma string. Esta funcao recebe essa chave
 * assim como o valor m que corresponde ao numero maximo de elementos na tabela
 * e percorre a string calculando para cada caracter uma soma ponderada atraves
 * de uma certa formula escolhida para minimizar colisoes.
 */
int hash(Chave v, int m){
  int h, a = 31415, b = 27183;
  for (h = 0; *v != '\0'; v++, a = a*b % (m-1))
    h = (a*h + *v) % m;
  return h;
}

/* Funcao de inicializacao da tabela de dispercao das equipas. Esta funcao recebe
 * um inteiro que quando multiplicado por 2 se torna no tamanho maximo da tabela.
 * E alocada memoria para a tabela representada pela estrutura tab_equipas e para
 * um vetor que contem as entradas da mesma e por fim inicializa-se tudo a NULL
*/
pTabEquipas inicia_te(int max){
  int i, m = 2 * max;
  pTabEquipas tab_dispercao = malloc(sizeof(struct tab_equipas));
  equipas(tab_dispercao) = malloc(m * sizeof(pEquipa));
  M(tab_dispercao) = m; N(tab_dispercao) = 0;
  for (i = 0; i < m; i++)
    equipas(tab_dispercao)[i] = NULLitem();
  return tab_dispercao;
}

/* Funcao de inicializacao da tabela de dispercao dos jogos. Esta funcao recebe
 * um inteiro que quando multiplicado por 2 se torna no tamanho maximo da tabela.
 * E alocada memoria para a tabela representada pela estrutura tab_jogos e para
 * um vetor que contem as entradas da mesma e por fim inicializa-se tudo a NULL
*/
pTabJogos inicia_tj(int max){
  int i, m = 2 * max;
  pTabJogos tab_dispercao = malloc(sizeof(struct tab_jogos));
  jogos(tab_dispercao) = malloc(m * sizeof(pJogo));
  M(tab_dispercao) = m; N(tab_dispercao) = 0;
  for (i = 0; i < m; i++)
    jogos(tab_dispercao)[i] = NULLitem();
  return tab_dispercao;
}

/* Funcao que insere um elemento na tabela de dispercao das equipas atraves do
 * seu hash e que percorre a tabela ate encontrar um espaco livre no caso de
 * existirem colisoes. Recebe um ponteiro para a equipa a inserir e um ponteiro
 * para a tabela das equipas
 */
void insere_eq(pEquipa equipa, pTabEquipas tab_dispercao){
  int i = hash(nome(equipa), M(tab_dispercao));
  while (equipas(tab_dispercao)[i] != NULLitem())
    i = (i+1) % M(tab_dispercao);
  equipas(tab_dispercao)[i] = equipa;
  N(tab_dispercao)++;  /* aumenta contador equipas na tabela */
}

/* Funcao que insere um elemento na tabela de dispercao dos jogos atraves do
 * seu hash e que percorre a tabela ate encontrar um espaco livre no caso de
 * existirem colisoes. Recebe um ponteiro para o jogo a inserir e um ponteiro
 * para a tabela dos jogos
 */
void insere_jg(pJogo jogo, pTabJogos tab_dispercao){
  int i = hash(nome(jogo), M(tab_dispercao));
  while (jogos(tab_dispercao)[i] != NULLitem())
    i = (i+1) % M(tab_dispercao);
  jogos(tab_dispercao)[i] = jogo;
  N(tab_dispercao)++;  /* aumenta contador jogos na tabela */
}

/* Aumenta o tamanho da tabela de dispercao das equipas alocando mais memoria
 * para a mesma e copiando os elementos da tabela anterior atraves do novo hash
 * visto que se o tamanho da tabela mudou a posicao dos elementos na mesma tambem
 * muda. Recebe um ponteiro para a tabela de dispercao das equipas e nao devolve nada.
 */
void aumenta_te(pTabEquipas tab_dispercao){
  int i;
  pEquipa *t = equipas(tab_dispercao); /* guarda a posicao dos elementos */
  tab_dispercao = inicia_te(M(tab_dispercao) + M(tab_dispercao));
  for (i = 0; i < M(tab_dispercao)/2; i++) /* Reinsere os elementos na nova tabela */
    if (nome(t[i]) != NULLitem())
      insere_eq(t[i], tab_dispercao);
  free(t);
}

/* Aumenta o tamanho da tabela de dispercao dos jogos alocando mais memoria
 * para a mesma e copiando os elementos da tabela anterior atraves do novo hash
 * visto que se o tamanho da tabela mudou a posicao dos elementos na mesma tambem
 * muda. Recebe um ponteiro para a tabela de dispercao dod jogos e nao devolve nada.
 */
void aumenta_tj(pTabJogos tab_dispercao){
  int i;
  pJogo *t = jogos(tab_dispercao); /* guarda a posicao dos elementos */
  tab_dispercao = inicia_tj(M(tab_dispercao) + M(tab_dispercao));
  for (i = 0; i < M(tab_dispercao)/2; i++) /* Reinsere os elementos na nova tabela */
    if (nome(t[i]) != NULLitem())
      insere_jg(t[i], tab_dispercao);
  free(t);
}

/* Funcao de procura de um elemento na tabela de dispercao das equipas que recebe
 * um ponteiro para a chave do elemento a procurar (nome da equipa) e outro para
 * a tabela das equipas. Procura-se um elemento atraves do seu hash e devolve-se
 * um ponteiro para o mesmo se este estiver na tabela.
*/
pEquipa procura_eq(Chave v, pTabEquipas tab_dispercao){
  int i = hash(v, M(tab_dispercao));
  while(equipas(tab_dispercao)[i] != NULLitem())
    /*se o nome do elem atual corresponder a chave do elem que se procura*/
    if (iguais(v, nome(equipas(tab_dispercao)[i])))
      return equipas(tab_dispercao)[i];
    else
      i = (i + 1) % M(tab_dispercao);
  return NULLitem();
}

/* Funcao de procura de um elemento na tabela de dispercao dos jogos que recebe
 * um ponteiro para a chave do elemento a procurar (nome do jogo) e outro para
 * a tabela dos jogos. Procura-se um elemento atraves do seu hash e devolve-se
 * um ponteiro para o mesmo se este estiver na tabela.
*/
pJogo procura_jg(Chave v, pTabJogos tab_dispercao){
  int i = hash(v, M(tab_dispercao));
  while(jogos(tab_dispercao)[i] != NULLitem())
    /*se o nome do elem atual corresponder a chave do elem que se procura*/
    if (iguais(v, nome(jogos(tab_dispercao)[i])))
      return jogos(tab_dispercao)[i];
    else
      i = (i + 1) % M(tab_dispercao);
  return NULLitem();
}

/* Funao para apagar um elemento da tabela de dispercao dos jogos que recebe
 * um ponteiro para a chave do elemento a apagar (nome do jogo) e outro para
 * a tabela dos jogos. Procura-se o elemento a apagar a partir do indice
 * devolvido pela funcao hash, liberta-se a memoria alocada pelo mesmo e volta-se
 * a inserir os elementos seguintes ate se encontrar uma posicao NULL.
*/
void apaga_jg(Chave v, pTabJogos tab_dispercao){
  int j, i = hash(v, M(tab_dispercao)); pJogo aux;
  /*se encontrar um elemento NULL entao o elemento que se quer apagar nao existe*/
  while (jogos(tab_dispercao)[i] != NULLitem())
    /*se a chave for igual ao elemento atual entao encontrou*/
    if (iguais(v, nome(jogos(tab_dispercao)[i])))
      break;
    else
      i = (i + 1) % M(tab_dispercao);
  if (jogos(tab_dispercao)[i] == NULLitem())
    return; /*nao precisa de procurar mais*/
  liberta_jogo(jogos(tab_dispercao)[i]); jogos(tab_dispercao)[i] = NULLitem();
  N(tab_dispercao)--;
  for (j = (i + 1) % M(tab_dispercao) ; jogos(tab_dispercao)[j] != NULLitem();
   j = (j + 1) % M(tab_dispercao) , N(tab_dispercao)--){
    aux = jogos(tab_dispercao)[j];
    jogos(tab_dispercao)[j] = NULLitem();
    insere_jg(aux, tab_dispercao); /* volta a inserir os elementos seguintes */
  }
}

/* Liberta a memoria alocada pela tabela de dispercoa das equipas (recebe um
 * ponteiro para a mesma) percorrendo toda a tabela e libertanto todos os
 * elementos que existirem assim como colocando-os a NULL. Por fim liberta
 * a memoria alocada para o vetor de equipas presente na estrutura usada para
 * representar a tabela e a memoria para a estrutura em si.
*/
void liberta_te(pTabEquipas tab_dispercao){
  int i = 0;
  for ( ; i < M(tab_dispercao); i++)
    if (equipas(tab_dispercao)[i] != NULLitem()){
      liberta_equipa(equipas(tab_dispercao)[i]); equipas(tab_dispercao)[i] = NULLitem();
      N(tab_dispercao)--;
    }
  free(equipas(tab_dispercao)); free(tab_dispercao);
}

/* Liberta a memoria alocada pela tabela de dispercoa dos jogos (recebe um
 * ponteiro para a mesma) percorrendo toda a tabela e libertanto todos os
 * elementos que existirem assim como colocando-os a NULL. Por fim liberta
 * a memoria alocada para o vetor de jogos presente na estrutura usada para
 * representar a tabela e a memoria para a estrutura em si.
*/
void liberta_tj(pTabJogos tab_dispercao){
  int i = 0;
  for ( ; i < M(tab_dispercao); i++)
    if (jogos(tab_dispercao)[i] != NULLitem()){
      liberta_jogo(jogos(tab_dispercao)[i]); jogos(tab_dispercao)[i] = NULLitem();
      N(tab_dispercao)--;
    }
  free(jogos(tab_dispercao)); free(tab_dispercao);
}
