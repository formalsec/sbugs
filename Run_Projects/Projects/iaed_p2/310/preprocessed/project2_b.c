/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct jogo
{
  char *nome;
  char *equipa1;
  char *equipa2;
  int score1;
  int score2;
} *pJogo;
typedef struct equipa
{
  char *nome;
  int vitorias;
} *pEquipa;
typedef struct jogos
{
  pJogo jogo;
  struct jogos *next;
} *pJogos;
typedef struct equipas
{
  pEquipa equipa;
  struct equipas *next;
} *pEquipas;
pJogos hJogos = 0;
pJogos *TableJogos;
pEquipas *TableEquipas;
pEquipas gEquipas = 0;
int NL = 1;
int getCommand();
void funcao_a();
void funcao_A();
void funcao_l();
void funcao_p();
void funcao_P();
void funcao_r();
void funcao_s();
void funcao_g();
void funcao_x();
pEquipas NewEquipa();
pEquipas AdicionarEquipa();
pEquipas searchEquipa();
void FreeEquipas();
void FreeEquipa();
pJogos NewJogo();
pJogos AdicionarJogo();
pJogos searchJogo();
void FreeJogos();
void FreeJogo();
pJogos DeleteJogo();
void InitHashTableEquipas();
void FreeHashTableEquipas();
void InitHashTableJogos();
void FreeHashTableJogos();
pEquipas AdicionarEquipag();
int main()
{
  InitHashTableEquipas();
  InitHashTableJogos();
  getCommand();
  FreeJogos(hJogos);
  FreeHashTableJogos(TableJogos);
  FreeHashTableEquipas(TableEquipas);
  return 0;
}

int getCommand()
{
  while (1)
  {
    int command = getchar();
    switch (command)
    {
      case 'a':
        getchar();
        funcao_a();
        NL++;
        break;

      case 'A':
        getchar();
        funcao_A();
        NL++;
        break;

      case 'l':
        funcao_l();
        NL++;
        break;

      case 'p':
        getchar();
        funcao_p();
        NL++;
        break;

      case 'P':
        getchar();
        funcao_P();
        NL++;
        break;

      case 'r':
        getchar();
        funcao_r();
        NL++;
        break;

      case 's':
        getchar();
        funcao_s();
        NL++;
        break;

      case 'g':
        funcao_g();
        NL++;
        break;

      case 'x':
        return 0;

      default:
        break;

    }

  }

  return 0;
}

void InitHashTableJogos()
{
  int i;
  TableJogos = malloc((sizeof(struct jogos)) * 2089);
  for (i = 0; i < 2089; i++)
  {
    TableJogos[i] = 0;
  }

}

void FreeHashTableJogos(pEquipas *TableJogos)
{
  int i;
  for (i = 0; i < 2089; i++)
  {
    FreeJogos(TableJogos[i]);
  }

  free(TableJogos);
}

void InitHashTableEquipas()
{
  int i;
  TableEquipas = malloc((sizeof(struct equipas)) * 2089);
  for (i = 0; i < 2089; i++)
  {
    TableEquipas[i] = 0;
  }

}

int Hash(char *nome)
{
  int h;
  int a = 127;
  for (h = 0; (*nome) != '\0'; nome++)
  {
    h = ((a * h) + (*nome)) % 2089;
  }

  return h;
}

void FreeHashTableEquipas(pEquipas *TableEquipas)
{
  int i;
  for (i = 0; i < 2089; i++)
  {
    FreeEquipas(TableEquipas[i]);
  }

  free(TableEquipas);
}

pEquipas NewEquipa(char *buffer)
{
  pEquipas x = malloc(sizeof(struct equipas));
  x->equipa = malloc(sizeof(struct equipa));
  x->equipa->nome = malloc((sizeof(char)) * (strlen(buffer) + 1));
  strcpy(x->equipa->nome, buffer);
  x->equipa->vitorias = 0;
  x->next = 0;
  return x;
}

pEquipas AdicionarEquipa(pEquipas hEquipas, char *nome)
{
  pEquipas NovaEquipa = NewEquipa(nome);
  pEquipas x;
  if (hEquipas == 0)
  {
    return NovaEquipa;
  }
  else
  {
    for (x = hEquipas; x->next != 0; x = x->next)
      ;

    x->next = NovaEquipa;
    return hEquipas;
  }

}

pEquipas searchEquipa(pEquipas hEquipas, char *nome)
{
  pEquipas x;
  for (x = hEquipas; x != 0; x = x->next)
  {
    if (strcmp(x->equipa->nome, nome) == 0)
    {
      return x;
    }
    else
    {
      
    }

  }

  return 0;
}

void FreeEquipas(pEquipas hEquipas)
{
  pEquipas x = hEquipas;
  pEquipas y;
  while (x != 0)
  {
    y = x->next;
    FreeEquipa(x);
    x = y;
  }

  hEquipas = 0;
}

void FreeEquipa(pEquipas hEquipas)
{
  free(hEquipas->equipa->nome);
  free(hEquipas->equipa);
  free(hEquipas);
}

pJogos NewJogo(char *nome, char *equipa1, char *equipa2, int score1, int score2)
{
  pJogos x = malloc(sizeof(struct jogos));
  x->jogo = malloc(sizeof(struct jogo));
  x->jogo->nome = malloc((sizeof(char)) * (strlen(nome) + 1));
  x->jogo->equipa1 = malloc((sizeof(char)) * (strlen(equipa1) + 1));
  x->jogo->equipa2 = malloc((sizeof(char)) * (strlen(equipa2) + 1));
  strcpy(x->jogo->nome, nome);
  strcpy(x->jogo->equipa1, equipa1);
  strcpy(x->jogo->equipa2, equipa2);
  x->jogo->score1 = score1;
  x->jogo->score2 = score2;
  x->next = 0;
  return x;
}

pJogos AdicionarJogo(pJogos hJogos, char *nome, char *equipa1, char *equipa2, int s1, int s2)
{
  pJogos NovoJogo = NewJogo(nome, equipa1, equipa2, s1, s2);
  pJogos x;
  if (hJogos == 0)
  {
    return NovoJogo;
  }
  else
  {
    for (x = hJogos; x->next != 0; x = x->next)
      ;

    x->next = NovoJogo;
    return hJogos;
  }

}

pJogos searchJogo(pJogos hJogos, char *nome)
{
  pJogos x;
  for (x = hJogos; x != 0; x = x->next)
    if (strcmp(x->jogo->nome, nome) == 0)
  {
    return x;
  }
  else
  {
    
  }


  return 0;
}

void FreeJogos(pJogos hJogos)
{
  pJogos x = hJogos;
  pJogos y;
  while (x != 0)
  {
    y = x->next;
    FreeJogo(x);
    x = y;
  }

  hJogos = 0;
}

void FreeJogo(pJogos hJogos)
{
  free(hJogos->jogo->nome);
  free(hJogos->jogo->equipa1);
  free(hJogos->jogo->equipa2);
  free(hJogos->jogo);
  free(hJogos);
}

pJogos DeleteJogo(pJogos hJogos, char *nome)
{
  pJogos x;
  pJogos prev;
  for (x = hJogos, prev = 0; x != 0; prev = x, x = x->next)
  {
    if (strcmp(x->jogo->nome, nome) == 0)
    {
      if (x == hJogos)
      {
        hJogos = x->next;
      }
      else
      {
        prev->next = x->next;
      }

      FreeJogo(x);
      break;
    }
    else
    {
      
    }

  }

  return hJogos;
}

void funcao_a()
{
  char bufferNome[1023];
  char bufferEquipa1[1023];
  char bufferEquipa2[1023];
  int s1;
  int s2;
  int h0;
  int h1;
  int h2;
  pEquipas x;
  for (int bufferNome_index = 0; bufferNome_index < 10; bufferNome_index++)
  {
    bufferNome[bufferNome_index] = new_sym_var(sizeof(char) * 8);
  }

  bufferNome[10 - 1] = '\0';
  for (int bufferEquipa1_index = 0; bufferEquipa1_index < 10; bufferEquipa1_index++)
  {
    bufferEquipa1[bufferEquipa1_index] = new_sym_var(sizeof(char) * 8);
  }

  bufferEquipa1[10 - 1] = '\0';
  for (int bufferEquipa2_index = 0; bufferEquipa2_index < 10; bufferEquipa2_index++)
  {
    bufferEquipa2[bufferEquipa2_index] = new_sym_var(sizeof(char) * 8);
  }

  bufferEquipa2[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  h0 = Hash(bufferNome);
  h1 = Hash(bufferEquipa1);
  h2 = Hash(bufferEquipa2);
  if (searchJogo(TableJogos[h0], bufferNome) != 0)
  {
    printf("%d Jogo existente.\n", NL);
    return;
  }
  else
  {
    if ((searchEquipa(TableEquipas[h1], bufferEquipa1) == 0) || (searchEquipa(TableEquipas[h2], bufferEquipa2) == 0))
    {
      printf("%d Equipa inexistente.\n", NL);
      return;
    }
    else
    {
      
    }

  }

  hJogos = AdicionarJogo(hJogos, bufferNome, bufferEquipa1, bufferEquipa2, s1, s2);
  TableJogos[h0] = AdicionarJogo(TableJogos[h0], bufferNome, bufferEquipa1, bufferEquipa2, s1, s2);
  if (s1 > s2)
  {
    x = searchEquipa(TableEquipas[h1], bufferEquipa1);
    x->equipa->vitorias++;
  }
  else
  {
    if (s2 > s1)
    {
      x = searchEquipa(TableEquipas[h2], bufferEquipa2);
      x->equipa->vitorias++;
    }
    else
    {
      
    }

  }

}

void funcao_l()
{
  pJogos x;
  for (x = hJogos; x != 0; x = x->next)
    printf("%d %s %s %s %d %d\n", NL, x->jogo->nome, x->jogo->equipa1, x->jogo->equipa2, x->jogo->score1, x->jogo->score2);

}

void funcao_p()
{
  char bufferNome[1023];
  pJogos x;
  int h;
  for (int bufferNome_index = 0; bufferNome_index < 10; bufferNome_index++)
  {
    bufferNome[bufferNome_index] = new_sym_var(sizeof(char) * 8);
  }

  bufferNome[10 - 1] = '\0';
  h = Hash(bufferNome);
  if (searchJogo(TableJogos[h], bufferNome) == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  x = searchJogo(TableJogos[h], bufferNome);
  printf("%d %s %s %s %d %d\n", NL, x->jogo->nome, x->jogo->equipa1, x->jogo->equipa2, x->jogo->score1, x->jogo->score2);
}

void funcao_r()
{
  char bufferNome[1023];
  pJogos x;
  pEquipas y;
  int h;
  for (int bufferNome_index = 0; bufferNome_index < 10; bufferNome_index++)
  {
    bufferNome[bufferNome_index] = new_sym_var(sizeof(char) * 8);
  }

  bufferNome[10 - 1] = '\0';
  h = Hash(bufferNome);
  if (searchJogo(TableJogos[h], bufferNome) == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  x = searchJogo(TableJogos[h], bufferNome);
  if (x->jogo->score1 > x->jogo->score2)
  {
    y = searchEquipa(TableEquipas[Hash(x->jogo->equipa1)], x->jogo->equipa1);
    y->equipa->vitorias--;
  }
  else
  {
    if (x->jogo->score2 > x->jogo->score1)
    {
      y = searchEquipa(TableEquipas[Hash(x->jogo->equipa2)], x->jogo->equipa2);
      y->equipa->vitorias--;
    }
    else
    {
      
    }

  }

  hJogos = DeleteJogo(hJogos, bufferNome);
  TableJogos[h] = DeleteJogo(TableJogos[h], bufferNome);
}

void funcao_s()
{
  char bufferNome[1023];
  int s1;
  int s2;
  int h0;
  int h1;
  int h2;
  pJogos x;
  pJogos x2;
  pEquipas y;
  for (int bufferNome_index = 0; bufferNome_index < 10; bufferNome_index++)
  {
    bufferNome[bufferNome_index] = new_sym_var(sizeof(char) * 8);
  }

  bufferNome[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  h0 = Hash(bufferNome);
  if (searchJogo(TableJogos[h0], bufferNome) == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  x = searchJogo(TableJogos[h0], bufferNome);
  x2 = searchJogo(hJogos, bufferNome);
  h1 = Hash(x->jogo->equipa1);
  h2 = Hash(x->jogo->equipa2);
  if (x->jogo->score1 > x->jogo->score2)
  {
    y = searchEquipa(TableEquipas[h1], x->jogo->equipa1);
    y->equipa->vitorias--;
  }
  else
  {
    if (x->jogo->score2 > x->jogo->score1)
    {
      y = searchEquipa(TableEquipas[h2], x->jogo->equipa2);
      y->equipa->vitorias--;
    }
    else
    {
      
    }

  }

  if (s1 > s2)
  {
    y = searchEquipa(TableEquipas[h1], x->jogo->equipa1);
    y->equipa->vitorias++;
  }
  else
  {
    if (s2 > s1)
    {
      y = searchEquipa(TableEquipas[h2], x->jogo->equipa2);
      y->equipa->vitorias++;
    }
    else
    {
      
    }

  }

  x->jogo->score1 = s1;
  x->jogo->score2 = s2;
  x2->jogo->score1 = s1;
  x2->jogo->score2 = s2;
}

void funcao_A()
{
  char bufferNome[1023];
  int x;
  for (int bufferNome_index = 0; bufferNome_index < 10; bufferNome_index++)
  {
    bufferNome[bufferNome_index] = new_sym_var(sizeof(char) * 8);
  }

  bufferNome[10 - 1] = '\0';
  if (searchEquipa(TableEquipas[Hash(bufferNome)], bufferNome) != 0)
  {
    printf("%d Equipa existente.\n", NL);
    return;
  }
  else
  {
    
  }

  x = Hash(bufferNome);
  TableEquipas[x] = AdicionarEquipa(TableEquipas[x], bufferNome);
}

void funcao_P()
{
  char bufferNome[1023];
  pEquipas x;
  int y;
  for (int bufferNome_index = 0; bufferNome_index < 10; bufferNome_index++)
  {
    bufferNome[bufferNome_index] = new_sym_var(sizeof(char) * 8);
  }

  bufferNome[10 - 1] = '\0';
  y = Hash(bufferNome);
  if (searchEquipa(TableEquipas[y], bufferNome) == 0)
  {
    printf("%d Equipa inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  x = searchEquipa(TableEquipas[y], bufferNome);
  printf("%d %s %d\n", NL, bufferNome, x->equipa->vitorias);
}

void funcao_g()
{
  pEquipas x;
  int i;
  int max = 0;
  for (i = 0; i < 2089; i++)
  {
    if (TableEquipas[i] != 0)
    {
      for (x = TableEquipas[i]; x != 0; x = x->next)
      {
        if (x->equipa->vitorias >= max)
        {
          if (x->equipa->vitorias > max)
          {
            FreeEquipas(gEquipas);
            gEquipas = 0;
            max = x->equipa->vitorias;
          }
          else
          {
            
          }

          gEquipas = AdicionarEquipag(gEquipas, x->equipa->nome);
        }
        else
        {
          
        }

      }

    }
    else
    {
      
    }

  }

  if (gEquipas != 0)
  {
    printf("%d Melhores %d\n", NL, max);
    for (x = gEquipas; x != 0; x = x->next)
      printf("%d * %s\n", NL, x->equipa->nome);

    FreeEquipas(gEquipas);
    gEquipas = 0;
  }
  else
  {
    
  }

}

pEquipas AdicionarEquipag(pEquipas hEquipas, char *nome)
{
  pEquipas NovaEquipa = NewEquipa(nome);
  pEquipas x;
  int menor;
  int small = 0;
  if (hEquipas == 0)
  {
    return NovaEquipa;
  }
  else
  {
    
  }

  if (strlen(NovaEquipa->equipa->nome) > strlen(hEquipas->equipa->nome))
  {
    menor = strlen(hEquipas->equipa->nome);
    small = 0;
  }
  else
  {
    menor = strlen(NovaEquipa->equipa->nome);
    small = 1;
  }

  if ((strncmp(NovaEquipa->equipa->nome, hEquipas->equipa->nome, menor) < 0) || ((strncmp(NovaEquipa->equipa->nome, hEquipas->equipa->nome, menor) == 0) && (small == 1)))
  {
    NovaEquipa->next = hEquipas;
    hEquipas = NovaEquipa;
    return hEquipas;
  }
  else
  {
    
  }

  for (x = hEquipas; x->next != 0; x = x->next)
  {
    if (strlen(NovaEquipa->equipa->nome) > strlen(x->next->equipa->nome))
    {
      menor = strlen(x->next->equipa->nome);
      small = 0;
    }
    else
    {
      menor = strlen(NovaEquipa->equipa->nome);
      small = 1;
    }

    if ((strncmp(NovaEquipa->equipa->nome, x->next->equipa->nome, menor) < 0) || ((strncmp(NovaEquipa->equipa->nome, x->next->equipa->nome, menor) == 0) && (small == 1)))
    {
      NovaEquipa->next = x->next;
      x->next = NovaEquipa;
      return hEquipas;
    }
    else
    {
      
    }

  }

  x->next = NovaEquipa;
  return hEquipas;
}
