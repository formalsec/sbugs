/*File generated by PreProcessor.py*/


#include "main.h"


void criaEquipa(link *hashEquipas, ulong linha)
{
  Equipa equipa;
  char buffer[1023];
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  if (EhashSearch(hashEquipas, buffer) == 0)
  {
    {
      equipa = newEquipa(buffer);
      hashEquipas = EhashInsert(hashEquipas, equipa);
    }
  }
  else
  {
    {
      printf("%ld Equipa existente.\n", linha);
    }
  }

}

void criaJogo(jlink *hashJogos, link *hashEquipas, ulong linha, ulong *ordem)
{
  char nome[1023];
  char e1[1023];
  char e2[1023];
  int s1;
  int s2;
  Jogo jogo;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  for (int e1_index = 0; e1_index < 10; e1_index++)
  {
    e1[e1_index] = new_sym_var(sizeof(char) * 8);
  }

  e1[10 - 1] = '\0';
  for (int e2_index = 0; e2_index < 10; e2_index++)
  {
    e2[e2_index] = new_sym_var(sizeof(char) * 8);
  }

  e2[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  if (JhashSearch(hashJogos, nome) != 0)
  {
    {
      printf("%ld Jogo existente.\n", linha);
      return;
    }
  }
  else
  {
    
  }

  if ((EhashSearch(hashEquipas, e1) == 0) || (EhashSearch(hashEquipas, e2) == 0))
  {
    {
      printf("%ld Equipa inexistente.\n", linha);
      return;
    }
  }
  else
  {
    
  }

  jogo = newJogo(nome, e1, e2, s1, s2, ordem, hashEquipas);
  hashJogos = JhashInsert(hashJogos, jogo);
  *ordem += 1;
}

void escreveEquipa(link *hashEquipas, ulong linha)
{
  char nome[1023];
  Equipa equipa;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  equipa = EhashSearch(hashEquipas, nome);
  if (equipa == 0)
  {
    {
      printf("%ld Equipa inexistente.\n", linha);
      return;
    }
  }
  else
  {
    
  }

  printf("%ld %s %d\n", linha, equipa->nome, equipa->ganhos);
}

void escreveJogo(jlink *hashJogos, ulong linha)
{
  char nome[1023];
  Jogo jogo;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  jogo = JhashSearch(hashJogos, nome);
  if (jogo == 0)
  {
    {
      printf("%ld Jogo inexistente.\n", linha);
      return;
    }
  }
  else
  {
    
  }

  printf("%ld %s %s %s %d %d\n", linha, jogo->nome, jogo->e1->equipa->nome, jogo->e2->equipa->nome, jogo->e1->pontos, jogo->e2->pontos);
}

void delJogo(jlink *hashJogos, ulong linha)
{
  char nome[1023];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (JhashSearch(hashJogos, nome) == 0)
  {
    {
      printf("%ld Jogo inexistente.\n", linha);
      return;
    }
  }
  else
  {
    
  }

  hashJogos = JhashDelete(hashJogos, nome);
}

void alteraScore(jlink *hashJogos, ulong linha)
{
  char nome[1023];
  Jogo jogo;
  int s1;
  int s2;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  jogo = JhashSearch(hashJogos, nome);
  if (jogo == 0)
  {
    {
      printf("%ld Jogo inexistente.\n", linha);
      return;
    }
  }
  else
  {
    
  }

  if (jogo->e1->pontos > jogo->e2->pontos)
  {
    {
      if (s1 == s2)
      {
        {
          jogo->e1->equipa->ganhos -= 1;
        }
      }
      else
      {
        if (s1 < s2)
        {
          {
            jogo->e1->equipa->ganhos -= 1;
            jogo->e2->equipa->ganhos += 1;
          }
        }
        else
        {
          
        }

      }

    }
  }
  else
  {
    if (jogo->e1->pontos < jogo->e2->pontos)
    {
      {
        if (s1 == s2)
        {
          {
            jogo->e2->equipa->ganhos -= 1;
          }
        }
        else
        {
          if (s1 > s2)
          {
            {
              jogo->e2->equipa->ganhos -= 1;
              jogo->e1->equipa->ganhos += 1;
            }
          }
          else
          {
            
          }

        }

      }
    }
    else
    {
      {
        if (s1 > s2)
        {
          {
            jogo->e1->equipa->ganhos += 1;
          }
        }
        else
        {
          if (s1 < s2)
          {
            {
              jogo->e2->equipa->ganhos += 1;
            }
          }
          else
          {
            
          }

        }

      }
    }

  }

  jogo->e1->pontos = s1;
  jogo->e2->pontos = s2;
}

void listaJogos(jlink *hashJogos, ulong linha)
{
  ulong i;
  ulong size = 0;
  Jogo *lista;
  lista = listaOrdenada(hashJogos, &size);
  for (i = 0; i < size; i++)
  {
    printf("%ld %s %s %s %d %d\n", linha, lista[i]->nome, lista[i]->e1->equipa->nome, lista[i]->e2->equipa->nome, lista[i]->e1->pontos, lista[i]->e2->pontos);
  }

  free(lista);
}

void listaMelhoresEquipas(link *hashEquipas, ulong linha)
{
  int i;
  Equipa *lista;
  int maior = 0;
  int count = 0;
  lista = listaMaioresVitorias(hashEquipas, &maior, &count);
  if (lista == 0)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  printf("%ld Melhores %d\n", linha, maior);
  for (i = 0; i < count; i++)
  {
    printf("%ld * %s\n", linha, lista[i]->nome);
  }

  free(lista);
}

