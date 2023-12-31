#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"


void adiciona_equipa_lista(equipa *e)
{
  node_e *n = malloc(sizeof(node_e));
  node_e *tmp = head_e;
  n->seguinte = 0;
  n->equipa = e;
  n->anterior = 0;
  if (tmp == 0)
  {
    head_e = n;
    return;
  }
  else
  {
    
  }

  while ((strcmp(e->nome, tmp->equipa->nome) > 0) && (tmp->seguinte != 0))
  {
    tmp = tmp->seguinte;
  }

  if ((tmp->seguinte == 0) && (strcmp(e->nome, tmp->equipa->nome) > 0))
  {
    tmp->seguinte = n;
    n->anterior = tmp;
  }
  else
  {
    if ((tmp == head_e) && (strcmp(e->nome, tmp->equipa->nome) < 0))
    {
      tmp->anterior = n;
      n->seguinte = tmp;
      head_e = n;
    }
    else
    {
      tmp->anterior->seguinte = n;
      n->anterior = tmp->anterior;
      n->seguinte = tmp;
      tmp->anterior = n;
    }

  }

}

void adiciona_jogo_lista(jogo *j)
{
  node_j *n = malloc(sizeof(node_j));
  n->seguinte = 0;
  n->anterior = tail_j;
  n->jogo = j;
  if (tail_j != 0)
  {
    tail_j->seguinte = n;
  }
  else
  {
    
  }

  tail_j = n;
  if (head_j == 0)
  {
    head_j = n;
  }
  else
  {
    
  }

}

unsigned int hash(char *nome)
{
  int length = strlen(nome);
  int i;
  unsigned int hash_value = 0;
  for (i = 0; i < length; i++)
  {
    hash_value += nome[i];
    hash_value = (nome[i] * hash_value) % 6661;
  }

  return hash_value;
}

int adiciona_equipa_hash(equipa *e)
{
  int i = hash(e->nome);
  e->seguinte = hash_equipas[i];
  hash_equipas[i] = e;
  return i;
}

void adiciona_jogo_hash(jogo *j)
{
  int i = hash(j->nome);
  j->seguinte = hash_jogos[i];
  hash_jogos[i] = j;
}

void adiciona_jogo_aux(equipa *e1, equipa *e2, jogo *j)
{
  if (j->score1 > j->score2)
  {
    e1->vitorias = e1->vitorias + 1;
  }
  else
  {
    if (j->score2 > j->score1)
    {
      e2->vitorias = e2->vitorias + 1;
    }
    else
    {
      
    }

  }

}

equipa *procura_equipa_hash(char *nome)
{
  int index = hash(nome);
  equipa *tmp = hash_equipas[index];
  while ((tmp != 0) && (strcmp(tmp->nome, nome) != 0))
  {
    tmp = tmp->seguinte;
  }

  return tmp;
}

jogo *procura_jogo_hash(char *nome)
{
  int index = hash(nome);
  jogo *tmp = hash_jogos[index];
  while ((tmp != 0) && (strcmp(tmp->nome, nome) != 0))
  {
    tmp = tmp->seguinte;
  }

  return tmp;
}

jogo *remove_jogo_hash(char *nome)
{
  int index = hash(nome);
  jogo *tmp = hash_jogos[index];
  jogo *anterior = 0;
  while ((tmp != 0) && (strcmp(tmp->nome, nome) != 0))
  {
    anterior = tmp;
    tmp = tmp->seguinte;
  }

  if (tmp == 0)
  {
    return 0;
  }
  else
  {
    
  }

  if (anterior == 0)
  {
    hash_jogos[index] = tmp->seguinte;
  }
  else
  {
    anterior->seguinte = tmp->seguinte;
  }

  return tmp;
}

void remove_jogo_lista(jogo *j)
{
  int i = 0;
  node_j *tmp;
  node_j *anterior;
  node_j *seguinte;
  if (j == head_j->jogo)
  {
    i++, tmp = head_j, head_j = head_j->seguinte;
  }
  else
  {
    
  }

  if (j == tail_j->jogo)
  {
    i++, tmp = tail_j, tail_j = tail_j->anterior;
  }
  else
  {
    
  }

  if (i == 0)
  {
    anterior = head_j;
    tmp = head_j->seguinte;
    seguinte = tmp->seguinte;
    while (j != tmp->jogo)
    {
      anterior = anterior->seguinte;
      tmp = tmp->seguinte;
      seguinte = seguinte->seguinte;
    }

    anterior->seguinte = seguinte;
    seguinte->anterior = anterior;
  }
  else
  {
    
  }

  free(tmp);
}

void reverte(jogo *tmp)
{
  equipa *e1;
  equipa *e2;
  e1 = procura_equipa_hash(tmp->equipa1);
  e2 = procura_equipa_hash(tmp->equipa2);
  if (tmp->score1 > tmp->score2)
  {
    e1->vitorias = e1->vitorias - 1;
  }
  else
  {
    
  }

  if (tmp->score2 > tmp->score1)
  {
    e2->vitorias = e2->vitorias - 1;
  }
  else
  {
    
  }

}

jogo *altera_jogo_hash(char *nome_jogo, int score1_n, int score2_n)
{
  equipa *e1;
  equipa *e2;
  jogo *tmp = procura_jogo_hash(nome_jogo);
  if (tmp == 0)
  {
    return tmp;
  }
  else
  {
    
  }

  reverte(tmp);
  tmp->score1 = score1_n;
  tmp->score2 = score2_n;
  e1 = procura_equipa_hash(tmp->equipa1);
  e2 = procura_equipa_hash(tmp->equipa2);
  adiciona_jogo_aux(e1, e2, tmp);
  return tmp;
}

int maximo()
{
  int i = 0;
  node_e *tmp = head_e;
  while (tmp != 0)
  {
    if (tmp->equipa->vitorias > i)
    {
      i = tmp->equipa->vitorias;
    }
    else
    {
      
    }

    tmp = tmp->seguinte;
  }

  return i;
}

void finaliza(int equipas)
{
  node_e *tmp1 = head_e;
  node_j *tmp2 = head_j;
  if (equipas == 0)
  {
    return;
  }
  else
  {
    
  }

  while (tmp1->seguinte != 0)
  {
    free(tmp1->equipa->nome);
    free(tmp1->equipa);
    tmp1 = tmp1->seguinte;
    free(tmp1->anterior);
  }

  free(tmp1->equipa->nome), free(tmp1->equipa), free(tmp1);
  if (tail_j == 0)
  {
    return;
  }
  else
  {
    
  }

  while (tmp2 != tail_j)
  {
    free(tmp2->jogo->nome), free(tmp2->jogo->equipa1), free(tmp2->jogo->equipa2);
    free(tmp2->jogo);
    tmp2 = tmp2->seguinte;
    free(tmp2->anterior);
  }

  free(tmp2->jogo->nome), free(tmp2->jogo->equipa1), free(tmp2->jogo->equipa2), free(tmp2->jogo), free(tmp2);
}

int AdicionarJogo(int nl, char dados[3098], int jogos)
{
  char equipa1[1023];
  char equipa2[1023];
  char nome_jogo[1023];
  int score1;
  int score2;
  jogo *j1;
  jogo *tmp;
  equipa *e1;
  equipa *e2;
  strcpy(nome_jogo, strtok(dados, ":"));
  strcpy(equipa1, strtok(0, ":"));
  strcpy(equipa2, strtok(0, ":"));
  score1 = atoi(strtok(0, ":"));
  score2 = atoi(strtok(0, "\n"));
  tmp = procura_jogo_hash(nome_jogo);
  if (tmp != 0)
  {
    printf("%d Jogo existente.\n", nl);
    return jogos;
  }
  else
  {
    
  }

  e1 = procura_equipa_hash(equipa1);
  e2 = procura_equipa_hash(equipa2);
  if ((e1 == 0) || (e2 == 0))
  {
    printf("%d Equipa inexistente.\n", nl);
    if (e1 == 0)
    {
      free(e1);
    }
    else
    {
      
    }

    if (e2 == 0)
    {
      free(e2);
    }
    else
    {
      
    }

    free(tmp);
    return jogos;
  }
  else
  {
    
  }

  j1 = malloc(sizeof(jogo));
  j1->nome = malloc((sizeof(char)) * (strlen(nome_jogo) + 1));
  j1->equipa1 = malloc((sizeof(char)) * (strlen(equipa1) + 1));
  j1->equipa2 = malloc((sizeof(char)) * (strlen(equipa2) + 1));
  j1->score1 = score1;
  j1->score2 = score2;
  strcpy(j1->nome, nome_jogo);
  strcpy(j1->equipa1, equipa1);
  strcpy(j1->equipa2, equipa2);
  adiciona_jogo_hash(j1);
  adiciona_jogo_lista(j1);
  adiciona_jogo_aux(e1, e2, j1);
  free(tmp);
  return ++jogos;
}

int AdicionarEquipa(int nl, char dados[3098], int equipas)
{
  equipa *e;
  equipa *tmp;
  char nome[1023];
  strcpy(nome, strtok(dados, "\n"));
  tmp = procura_equipa_hash(nome);
  if (tmp == 0)
  {
    e = malloc(sizeof(equipa));
    e->nome = malloc((sizeof(char)) * (strlen(nome) + 1));
    e->vitorias = 0;
    strcpy(e->nome, nome);
    adiciona_equipa_hash(e);
    adiciona_equipa_lista(e);
    free(tmp);
    return ++equipas;
  }
  else
  {
    printf("%d Equipa existente.\n", nl);
    return equipas;
  }

}

void ListaJogos(int nl, int jogos)
{
  node_j *tmp = head_j;
  jogo *j;
  if (jogos == 0)
  {
    return;
  }
  else
  {
    
  }

  if (jogos == 1)
  {
    j = tmp->jogo;
    printf("%d %s %s %s %d %d\n", nl, j->nome, j->equipa1, j->equipa2, j->score1, j->score2);
    return;
  }
  else
  {
    
  }

  while (tmp != 0)
  {
    j = tmp->jogo;
    printf("%d %s %s %s %d %d\n", nl, j->nome, j->equipa1, j->equipa2, j->score1, j->score2);
    tmp = tmp->seguinte;
  }

}

void ProcuraJogo(int nl, char dados[3098])
{
  char nome_jogo[1023];
  jogo *tmp;
  strcpy(nome_jogo, strtok(dados, "\n"));
  tmp = procura_jogo_hash(nome_jogo);
  if (tmp == 0)
  {
    printf("%d Jogo inexistente.\n", nl), free(tmp);
  }
  else
  {
    printf("%d %s %s %s %d %d\n", nl, tmp->nome, tmp->equipa1, tmp->equipa2, tmp->score1, tmp->score2);
  }

}

void ProcuraEquipa(int nl, char dados[3098])
{
  char nome[1023];
  equipa *tmp;
  strcpy(nome, strtok(dados, "\n"));
  tmp = procura_equipa_hash(nome);
  if (tmp == 0)
  {
    printf("%d Equipa inexistente.\n", nl), free(tmp);
  }
  else
  {
    printf("%d %s %d\n", nl, tmp->nome, tmp->vitorias);
  }

}

int RemoveJogo(int nl, char dados[3098], int jogos)
{
  char nome_jogo[1023];
  jogo *tmp;
  strcpy(nome_jogo, strtok(dados, "\n"));
  tmp = remove_jogo_hash(nome_jogo);
  if (tmp == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
    free(tmp);
    return jogos;
  }
  else
  {
    
  }

  remove_jogo_lista(tmp);
  reverte(tmp);
  free(tmp->nome), free(tmp->equipa1), free(tmp->equipa2);
  free(tmp);
  if (jogos == 1)
  {
    head_j = 0;
    tail_j = 0;
  }
  else
  {
    
  }

  return --jogos;
}

void AlteraScore(int nl, char dados[3098])
{
  char nome_jogo[1023];
  int score1;
  int score2;
  jogo *tmp;
  strcpy(nome_jogo, strtok(dados, ":"));
  score1 = atoi(strtok(0, ":"));
  score2 = atoi(strtok(0, "\n"));
  tmp = altera_jogo_hash(nome_jogo, score1, score2);
  if (tmp == 0)
  {
    printf("%d Jogo inexistente.\n", nl), free(tmp);
  }
  else
  {
    
  }

}

void Vencedores(int nl, int equipas)
{
  node_e *tmp;
  int i;
  if (equipas == 0)
  {
    return;
  }
  else
  {
    
  }

  i = maximo();
  tmp = head_e;
  printf("%d Melhores %d\n", nl, i);
  while (tmp != 0)
  {
    if (tmp->equipa->vitorias == i)
    {
      printf("%d * %s\n", nl, tmp->equipa->nome);
    }
    else
    {
      
    }

    tmp = tmp->seguinte;
  }

}

int main()
{
  char c;
  char dados[3100];
  int nl = 0;
  int equipas = 0;
  int jogos = 0;
  while (1)
  {
    nl += 1;
    fgets(dados, 3100, stdin);
    c = dados[0];
    memmove(dados, dados + 2, 3098);
    switch (c)
    {
      case 'a':
        jogos = AdicionarJogo(nl, dados, jogos);
        break;

      case 'A':
        equipas = AdicionarEquipa(nl, dados, equipas);
        break;

      case 'l':
        ListaJogos(nl, jogos);
        break;

      case 'p':
        ProcuraJogo(nl, dados);
        break;

      case 'P':
        ProcuraEquipa(nl, dados);
        break;

      case 'r':
        jogos = RemoveJogo(nl, dados, jogos);
        break;

      case 's':
        AlteraScore(nl, dados);
        break;

      case 'g':
        Vencedores(nl, equipas);
        break;

      case 'x':
        finaliza(equipas);
        return 0;

    }

  }

}

