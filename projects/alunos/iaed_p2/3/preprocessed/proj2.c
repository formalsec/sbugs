#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct equipa
{
  char *name;
  int wins;
} *pEquipa;
typedef struct jogo
{
  char *name;
  char *equipa1;
  char *equipa2;
  int score1;
  int score2;
} *pJogo;
typedef struct nomeElemento
{
  char *nome;
  struct nomeElemento *next;
} *pNome;
static int JT_M;
static int EQ_M;
static pEquipa *equipas;
static pJogo *jogos;
static pNome headNomesJogos;
static pNome headNomesEquipas;
int hash(char *v, int M)
{
  int h = 0;
  int a = 127;
  for (; (*v) != '\0'; v++)
  {
    h = ((a * h) + (*v)) % M;
  }

  return h;
}

int hash2(char *v, int M)
{
  unsigned int h;
  unsigned int a = 31415;
  unsigned int b = 27183;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (M - 1))
  {
    h = ((a * h) + (*v)) % M;
  }

  return h;
}

char *strdup(const char *s)
{
  size_t size = strlen(s) + 1;
  char *p = malloc(size);
  if (p)
  {
    memcpy(p, s, size);
  }
  else
  {
    
  }

  return p;
}

pNome newNomeElemento(char *name)
{
  pNome new = (pNome) malloc(sizeof(struct nomeElemento));
  new->nome = strdup(name);
  new->next = 0;
  return new;
}

void freeNomeElemento(pNome elem)
{
  free(elem->nome);
  free(elem);
}

pJogo newGame(char *name, char *equipa1, char *equipa2)
{
  pJogo new = (pJogo) malloc(sizeof(struct jogo));
  new->name = strdup(name);
  new->equipa1 = strdup(equipa1);
  new->equipa2 = strdup(equipa2);
  new->score1 = 0;
  new->score2 = 0;
  return new;
}

void freeGame(pJogo jogo)
{
  free(jogo->name);
  free(jogo->equipa1);
  free(jogo->equipa2);
  free(jogo);
}

pEquipa newTeam(char *name)
{
  pEquipa new = (pEquipa) malloc(sizeof(struct equipa));
  new->wins = 0;
  new->name = strdup(name);
  return new;
}

void NJinit()
{
  headNomesJogos = 0;
}

void NJinsert(pNome jogo)
{
  pNome temp = headNomesJogos;
  if (headNomesJogos == 0)
  {
    headNomesJogos = jogo;
    return;
  }
  else
  {
    
  }

  while (temp->next != 0)
  {
    temp = temp->next;
  }

  temp->next = jogo;
}

void NJdelete(char *nome)
{
  pNome curr = headNomesJogos;
  pNome prev;
  while ((curr->next != 0) & (strcmp(curr->nome, nome) != 0))
  {
    prev = curr;
    curr = curr->next;
  }

  if (curr == headNomesJogos)
  {
    headNomesJogos = curr->next;
  }
  else
  {
    prev->next = curr->next;
  }

  freeNomeElemento(curr);
}

void NEinit()
{
  headNomesEquipas = 0;
}

void NEinsert(pNome equipa)
{
  pNome current = headNomesEquipas;
  if ((headNomesEquipas == 0) || (strcmp(equipa->nome, current->nome) < 0))
  {
    equipa->next = headNomesEquipas;
    headNomesEquipas = equipa;
    return;
  }
  else
  {
    
  }

  while ((current->next != 0) && (strcmp(equipa->nome, current->next->nome) > 0))
  {
    current = current->next;
  }

  equipa->next = current->next;
  current->next = equipa;
}

void EQinit(int m)
{
  int i;
  EQ_M = m;
  equipas = (pEquipa *) malloc(EQ_M * (sizeof(pEquipa)));
  for (i = 0; i < EQ_M; i++)
  {
    equipas[i] = 0;
  }

}

void EQinsert(pEquipa equipa)
{
  int i = hash(equipa->name, EQ_M);
  while (equipas[i] != 0)
  {
    i = (i + 1) % EQ_M;
  }

  equipas[i] = equipa;
}

pEquipa EQsearch(char *key)
{
  int i = hash(key, EQ_M);
  while (equipas[i] != 0)
  {
    if (strcmp(equipas[i]->name, key) == 0)
    {
      return equipas[i];
    }
    else
    {
      i = (i + 1) % EQ_M;
    }

  }

  return 0;
}

void EQupdateVictory(char *key, int value)
{
  pEquipa equipa = EQsearch(key);
  equipa->wins += value;
}

void EQmaxVictories(unsigned int nl)
{
  pNome temp = headNomesEquipas;
  int max = 0;
  pEquipa equipa;
  while (temp != 0)
  {
    equipa = EQsearch(temp->nome);
    max = (equipa->wins > max) ? (equipa->wins) : (max);
    temp = temp->next;
  }

  temp = headNomesEquipas;
  printf("%u Melhores %d\n", nl, max);
  while (temp != 0)
  {
    equipa = EQsearch(temp->nome);
    if (equipa->wins == max)
    {
      printf("%u * %s\n", nl, equipa->name);
    }
    else
    {
      
    }

    temp = temp->next;
  }

}

void JTinit(int m)
{
  int i;
  JT_M = m;
  jogos = (pJogo *) malloc(JT_M * (sizeof(pJogo)));
  for (i = 0; i < JT_M; i++)
  {
    jogos[i] = 0;
  }

}

void JTinsert(pJogo jogo)
{
  int i = hash2(jogo->name, JT_M);
  int k = hash(jogo->name, JT_M);
  while (jogos[i] != 0)
  {
    if (strcmp(jogos[i]->name, ":") == 0)
    {
      break;
    }
    else
    {
      i = (i + k) % JT_M;
    }

  }

  jogos[i] = jogo;
}

pJogo JTsearch(char *key)
{
  int i = hash2(key, JT_M);
  int k = hash(key, JT_M);
  while (jogos[i] != 0)
  {
    if (strcmp(jogos[i]->name, key) == 0)
    {
      return jogos[i];
    }
    else
    {
      i = (i + k) % JT_M;
    }

  }

  return 0;
}

void JTremove(char *key, pJogo dummy)
{
  int i = hash2(key, JT_M);
  int k = hash(key, JT_M);
  while (jogos[i] != 0)
  {
    if (strcmp(jogos[i]->name, key) == 0)
    {
      break;
    }
    else
    {
      i = (i + k) % JT_M;
    }

  }

  freeGame(jogos[i]);
  jogos[i] = dummy;
}

void JTupdateScore(pJogo jogo, int score1, int score2)
{
  if (score1 > score2)
  {
    if (jogo->score1 < jogo->score2)
    {
      EQupdateVictory(jogo->equipa1, 1);
      EQupdateVictory(jogo->equipa2, -1);
    }
    else
    {
      if (jogo->score1 == jogo->score2)
      {
        EQupdateVictory(jogo->equipa1, 1);
      }
      else
      {
        
      }

    }

  }
  else
  {
    if (score1 < score2)
    {
      if (jogo->score1 > jogo->score2)
      {
        EQupdateVictory(jogo->equipa1, -1);
        EQupdateVictory(jogo->equipa2, 1);
      }
      else
      {
        if (jogo->score1 == jogo->score2)
        {
          EQupdateVictory(jogo->equipa2, 1);
        }
        else
        {
          
        }

      }

    }
    else
    {
      if (jogo->score1 > jogo->score2)
      {
        EQupdateVictory(jogo->equipa1, -1);
      }
      else
      {
        if (jogo->score1 < jogo->score2)
        {
          EQupdateVictory(jogo->equipa2, -1);
        }
        else
        {
          
        }

      }

    }

  }

  jogo->score1 = score1;
  jogo->score2 = score2;
}

void JTprintJogo(unsigned int nl, pJogo jogo)
{
  printf("%u %s %s %s %d %d\n", nl, jogo->name, jogo->equipa1, jogo->equipa2, jogo->score1, jogo->score2);
}

void JTprintJogos(unsigned int nl)
{
  pNome temp = headNomesJogos;
  pJogo jogo;
  while (temp != 0)
  {
    jogo = JTsearch(temp->nome);
    JTprintJogo(nl, jogo);
    temp = temp->next;
  }

}

int main()
{
  char comando;
  unsigned int nl = 0;
  pJogo dummy = newGame(":", "dummy", "dummy");
  EQinit(33637);
  JTinit(83093);
  NJinit();
  NEinit();
  while (1)
  {
    char nome[1024];
    char equipa1[1024];
    char equipa2[1024];
    int score1;
    int score2;
    pEquipa equipa;
    pJogo jogo;
    pNome nomeJogo;
    pNome nomeEquipa;
    comando = getchar();
    switch (comando)
    {
      case 'a':
        nl += 1;
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        for (int equipa1_index = 0; equipa1_index < 10; equipa1_index++)
      {
        equipa1[equipa1_index] = new_sym_var(sizeof(char) * 8);
      }

        equipa1[10 - 1] = '\0';
        for (int equipa2_index = 0; equipa2_index < 10; equipa2_index++)
      {
        equipa2[equipa2_index] = new_sym_var(sizeof(char) * 8);
      }

        equipa2[10 - 1] = '\0';
        score1 = new_sym_var(sizeof(int) * 8);
        score2 = new_sym_var(sizeof(int) * 8);
        if (JTsearch(nome) != 0)
      {
        printf("%u Jogo existente.\n", nl);
      }
      else
      {
        if ((EQsearch(equipa1) == 0) | (EQsearch(equipa2) == 0))
        {
          printf("%u Equipa inexistente.\n", nl);
        }
        else
        {
          jogo = newGame(nome, equipa1, equipa2);
          nomeJogo = newNomeElemento(nome);
          JTinsert(jogo);
          JTupdateScore(jogo, score1, score2);
          NJinsert(nomeJogo);
        }

      }

        break;

      case 'A':
        nl += 1;
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        if (EQsearch(nome) != 0)
      {
        printf("%u Equipa existente.\n", nl);
      }
      else
      {
        equipa = newTeam(nome);
        nomeEquipa = newNomeElemento(nome);
        EQinsert(equipa);
        NEinsert(nomeEquipa);
      }

        break;

      case 'l':
        nl += 1;
        JTprintJogos(nl);
        break;

      case 'p':
        nl += 1;
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        jogo = JTsearch(nome);
        if (jogo != 0)
      {
        JTprintJogo(nl, jogo);
      }
      else
      {
        printf("%u Jogo inexistente.\n", nl);
      }

        break;

      case 'P':
        nl += 1;
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        equipa = EQsearch(nome);
        if (equipa != 0)
      {
        printf("%u %s %d\n", nl, equipa->name, equipa->wins);
      }
      else
      {
        printf("%u Equipa inexistente.\n", nl);
      }

        break;

      case 'r':
        nl += 1;
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        jogo = JTsearch(nome);
        if (jogo != 0)
      {
        JTupdateScore(jogo, 0, 0);
        JTremove(nome, dummy);
        NJdelete(nome);
      }
      else
      {
        printf("%u Jogo inexistente.\n", nl);
      }

        break;

      case 's':
        nl += 1;
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        score1 = new_sym_var(sizeof(int) * 8);
        score2 = new_sym_var(sizeof(int) * 8);
        jogo = JTsearch(nome);
        if (jogo != 0)
      {
        JTupdateScore(jogo, score1, score2);
      }
      else
      {
        printf("%u Jogo inexistente.\n", nl);
      }

        break;

      case 'g':
        nl += 1;
        if (headNomesEquipas == 0)
      {
        break;
      }
      else
      {
        
      }

        EQmaxVictories(nl);
        break;

      case 'x':
        freeGame(dummy);
        return 0;

      default:
        printf("ERRO: Comando desconhecido\n");
        break;

    }

    getchar();
  }

  return 1;
}

