#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "main.h"

/* recebe a hash das equipas. Le do stdin o nome da equipa.
   adiciona a equipa a hash.
*/
void criaEquipa(link* hashEquipas, ulong linha) {
  Equipa equipa;
  char buffer[STR_SIZE];
  scanf(" %[^:\n]", buffer);

  /* ve se a equipa existe */
  if (EhashSearch(hashEquipas, buffer) == NULL) {
    /* cria uma nova equipa e adiciona a hash */
    equipa = newEquipa(buffer);
    hashEquipas = EhashInsert(hashEquipas, equipa);
  }
  else {
    printf("%ld Equipa existente.\n", linha);
  }
}

/* recebe a hash dos jogos, das equipas e a ordem de insercao dos jogos. Le do stdin
   o nome do jogo, das equipas e o score do jogo.
   adiciona um jogo a hash das equipas e incrementa a ordem de insercao.
*/
void criaJogo(jlink* hashJogos,link* hashEquipas, ulong linha, ulong* ordem) {
  char nome[STR_SIZE],e1[STR_SIZE],e2[STR_SIZE];
  int s1, s2;
  Jogo jogo;
  scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome,e1,e2,&s1,&s2);

  /* verifica se o jogo ja existe */
  if (JhashSearch(hashJogos, nome) != NULL) {
    printf("%ld Jogo existente.\n", linha);
    return;
  }

  /* verifica se as equipas existem */
  if (EhashSearch(hashEquipas, e1) == NULL || EhashSearch(hashEquipas, e2) == NULL) {
    printf("%ld Equipa inexistente.\n", linha);
    return;
  }

  /* cria um novo jogo e adiciona a hash */
  jogo = newJogo(nome, e1, e2, s1, s2, ordem, hashEquipas);
  hashJogos = JhashInsert(hashJogos, jogo);
  *ordem += 1;

}

/* recebe a hash das equipas, le um nome do stdin e da print no stdout a equipa e aos seus jogos ganhos */
void escreveEquipa(link* hashEquipas, ulong linha) {
  char nome[STR_SIZE];
  Equipa equipa;

  scanf(" %[^:\n]", nome);

  /* procura se a equipa existe */
  equipa = EhashSearch(hashEquipas, nome);

  if (equipa == NULL) {
    printf("%ld Equipa inexistente.\n", linha);
    return;
  }

  printf("%ld %s %d\n", linha, equipa->nome, equipa->ganhos);
}

/* recebe a hash dos jogos, le um nome do stdin e da print no stdout
   ao jogo e as duas equipas e os seus resultados*/
void escreveJogo(jlink* hashJogos, ulong linha) {
  char nome[STR_SIZE];
  Jogo jogo;

  scanf(" %[^:\n]", nome);

  /* procura se o jogo existe */
  jogo = JhashSearch(hashJogos, nome);

  if (jogo == NULL) {
    printf("%ld Jogo inexistente.\n", linha);
    return;
  }

  printf("%ld %s %s %s %d %d\n", linha, jogo->nome, jogo->e1->equipa->nome,
                jogo->e2->equipa->nome, jogo->e1->pontos, jogo->e2->pontos);
}

/* recebe a hash dos jogos, le um nome do stdin e se existir apaga da hash */
void delJogo(jlink* hashJogos, ulong linha) {
  char nome[STR_SIZE];

  scanf(" %[^:\n]", nome);

  /* verifica se o jogo existe */
  if (JhashSearch(hashJogos, nome) == NULL) {
    printf("%ld Jogo inexistente.\n", linha);
    return;
  }

  /* apaga o jogo da hash */
  hashJogos = JhashDelete(hashJogos, nome);
}

/* recebe a hash dos jogos, le um nome e um novo score do stdin e se existir
   altera o score do jogo e o numero de jogos ganhos de cada equipa */
void alteraScore(jlink* hashJogos, ulong linha) {
  char nome[STR_SIZE];
  Jogo jogo;
  int s1, s2;

  scanf(" %[^:\n]:%d:%d", nome, &s1, &s2);

  /* procura o jogo */
  jogo = JhashSearch(hashJogos, nome);

  if (jogo == NULL) {
    printf("%ld Jogo inexistente.\n", linha);
    return;
  }

  /* altera o nr de jogos ganhos em funcao do novo score */
  if (jogo->e1->pontos > jogo->e2->pontos) {
    if (s1 == s2) {
      jogo->e1->equipa->ganhos -= 1;
    }
    else if (s1 < s2) {
      jogo->e1->equipa->ganhos -= 1;
      jogo->e2->equipa->ganhos += 1;
    }
  }
  else if (jogo->e1->pontos < jogo->e2->pontos) {
    if (s1 == s2) {
      jogo->e2->equipa->ganhos -= 1;
    }
    else if (s1 > s2) {
      jogo->e2->equipa->ganhos -= 1;
      jogo->e1->equipa->ganhos += 1;
    }
  }
  else {
    if (s1 > s2) {
      jogo->e1->equipa->ganhos += 1;
    }
    else if (s1 < s2) {
      jogo->e2->equipa->ganhos += 1;
    }
  }

  /* altera o score do jogo */
  jogo->e1->pontos = s1;
  jogo->e2->pontos = s2;
}

/* recebe a hash dos jogos e da print na stdout a todos os jogos  existentes na hash
   por ordem de insercao */
void listaJogos(jlink* hashJogos, ulong linha) {
  /* tamanho incial da lista  */
  ulong i, size = 0;
  Jogo* lista;

  /* lista dos jogos ordenada por ordem de insercao */
  lista = listaOrdenada(hashJogos, &size);

  for (i = 0; i < size; i++) {
    printf("%ld %s %s %s %d %d\n", linha, lista[i]->nome, lista[i]->e1->equipa->nome,
              lista[i]->e2->equipa->nome, lista[i]->e1->pontos, lista[i]->e2->pontos);
  }

  free(lista);
}

/* recebe a hash das equipas e da print a uma lista de todos os jogos com o maior
   numero de vitorias ordenados por ordem alfabetica */
void listaMelhoresEquipas(link* hashEquipas, ulong linha) {
  int i;
  Equipa* lista;
  /* maior nr de jogos ganhos e nr de equipas com esses jogos inicial  */
  int maior = 0, count = 0;

  /* lista de equipas por ordem alfabetica */
  lista = listaMaioresVitorias(hashEquipas, &maior, &count);

  /* se nao existir nao devolve nada */
  if (lista == NULL) {
    return;
  }

  printf("%ld Melhores %d\n", linha, maior);
  for (i = 0; i < count; i++) {
    printf("%ld * %s\n", linha, lista[i]->nome);
  }

  free(lista);
}
