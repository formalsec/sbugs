/*File generated by PreProcessor.py*/


#include "jogos.h"
#include "equipas.h"
#include "common.h"


void adiciona_jogo(int nl, TabelaJogos *tabJogos, TabelaEquipas *tabEquipas)
{
  Jogo *jogo = criar_jogo();
  Equipa *e1;
  Equipa *e2;
  if (procura_jogo(tabJogos, jogo->nome) != 0)
  {
    {
      printf("%d Jogo existente.\n", nl);
      free_jogo(jogo);
      return;
    }
  }
  else
  {
    
  }

  e1 = procura_equipa(tabEquipas, jogo->equipas[0]);
  e2 = procura_equipa(tabEquipas, jogo->equipas[1]);
  if ((e1 == 0) || (e2 == 0))
  {
    {
      printf("%d Equipa inexistente.\n", nl);
      free_jogo(jogo);
      return;
    }
  }
  else
  {
    
  }

  if (jogo->scores[0] > jogo->scores[1])
  {
    {
      e1->score++;
    }
  }
  else
  {
    if (jogo->scores[0] < jogo->scores[1])
    {
      {
        e2->score++;
      }
    }
    else
    {
      
    }

  }

  inserir_jogo(tabJogos, jogo);
}

void adiciona_equipa(int nl, TabelaEquipas *tabEquipas)
{
  Equipa *equipa;
  char input[1024];
  for (int input_index = 0; input_index < 10; input_index++)
  {
    input[input_index] = new_sym_var(sizeof(char) * 8);
  }

  input[10 - 1] = '\0';
  if (procura_equipa(tabEquipas, input) != 0)
  {
    {
      printf("%d Equipa existente.\n", nl);
      return;
    }
  }
  else
  {
    
  }

  equipa = malloc(sizeof(Equipa));
  equipa->nome = copiar_texto(input);
  equipa->score = 0;
  inserir_equipa(tabEquipas, equipa);
}

void lista_jogos(int nl, TabelaJogos *tabJogos)
{
  struct node *no = tabJogos->first;
  while (no != 0)
  {
    if (no->v != 0)
    {
      {
        printf("%d %s %s %s %d %d\n", nl, no->v->nome, no->v->equipas[0], no->v->equipas[1], no->v->scores[0], no->v->scores[1]);
      }
    }
    else
    {
      
    }

    no = no->next;
  }

}

void procurar_jogo(int nl, TabelaJogos *tabJogos)
{
  char nome[1024];
  Jogo *jogo;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  jogo = procura_jogo(tabJogos, nome);
  if (jogo == 0)
  {
    {
      printf("%d Jogo inexistente.\n", nl);
      return;
    }
  }
  else
  {
    
  }

  printf("%d %s %s %s %d %d\n", nl, jogo->nome, jogo->equipas[0], jogo->equipas[1], jogo->scores[0], jogo->scores[1]);
}

void procurar_equipa(int nl, TabelaEquipas *tabEquipas)
{
  char nome[1024];
  Equipa *equipa;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  equipa = procura_equipa(tabEquipas, nome);
  if (equipa == 0)
  {
    {
      printf("%d Equipa inexistente.\n", nl);
      return;
    }
  }
  else
  {
    
  }

  printf("%d %s %d\n", nl, equipa->nome, equipa->score);
}

void apaga_jogo(int nl, TabelaJogos *tabJogos, TabelaEquipas *tabEquipas)
{
  char nome[1024];
  Jogo *jogo;
  Equipa *e1;
  Equipa *e2;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  jogo = procura_jogo(tabJogos, nome);
  if (jogo == 0)
  {
    {
      printf("%d Jogo inexistente.\n", nl);
      return;
    }
  }
  else
  {
    
  }

  e1 = procura_equipa(tabEquipas, jogo->equipas[0]);
  e2 = procura_equipa(tabEquipas, jogo->equipas[1]);
  if (jogo->scores[0] > jogo->scores[1])
  {
    {
      e1->score--;
    }
  }
  else
  {
    if (jogo->scores[0] < jogo->scores[1])
    {
      {
        e2->score--;
      }
    }
    else
    {
      
    }

  }

  apagar_jogo(tabJogos, nome);
}

void altera_score(int nl, TabelaJogos *tabJogos, TabelaEquipas *tabEquipas)
{
  char nome[1024];
  Jogo *jogo;
  Equipa *e1;
  Equipa *e2;
  int novosScores[2];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  novosScores[0] = new_sym_var(sizeof(int) * 8);
  novosScores[1] = new_sym_var(sizeof(int) * 8);
  jogo = procura_jogo(tabJogos, nome);
  if (jogo == 0)
  {
    {
      printf("%d Jogo inexistente.\n", nl);
      return;
    }
  }
  else
  {
    
  }

  e1 = procura_equipa(tabEquipas, jogo->equipas[0]);
  e2 = procura_equipa(tabEquipas, jogo->equipas[1]);
  if (jogo->scores[0] > jogo->scores[1])
  {
    {
      e1->score--;
    }
  }
  else
  {
    if (jogo->scores[0] < jogo->scores[1])
    {
      {
        e2->score--;
      }
    }
    else
    {
      
    }

  }

  jogo->scores[0] = novosScores[0];
  jogo->scores[1] = novosScores[1];
  if (jogo->scores[0] > jogo->scores[1])
  {
    {
      e1->score++;
    }
  }
  else
  {
    if (jogo->scores[0] < jogo->scores[1])
    {
      {
        e2->score++;
      }
    }
    else
    {
      
    }

  }

}

void melhores_equipas(int nl, TabelaEquipas *tabEquipas)
{
  int i;
  int j;
  int numEquipas = 0;
  int jogosGanhos = 0;
  char **equipas = 0;
  if (tabEquipas->tamanho == 0)
  {
    return;
  }
  else
  {
    
  }

  for (i = 0; i < tabEquipas->capacidade; i++)
  {
    if (tabEquipas->equipas[i] != 0)
    {
      {
        if (tabEquipas->equipas[i]->score > jogosGanhos)
        {
          {
            jogosGanhos = tabEquipas->equipas[i]->score;
            numEquipas = 1;
          }
        }
        else
        {
          if (tabEquipas->equipas[i]->score == jogosGanhos)
          {
            {
              numEquipas++;
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
      
    }

  }

  equipas = malloc((sizeof(char *)) * numEquipas);
  j = 0;
  for (i = 0; i < tabEquipas->capacidade; i++)
  {
    if ((tabEquipas->equipas[i] != 0) && (tabEquipas->equipas[i]->score == jogosGanhos))
    {
      {
        equipas[j] = tabEquipas->equipas[i]->nome;
        j++;
      }
    }
    else
    {
      
    }

  }

  ordena_equipas(equipas, 0, numEquipas - 1);
  printf("%d Melhores %d\n", nl, jogosGanhos);
  for (i = 0; i < numEquipas; i++)
  {
    printf("%d * %s\n", nl, equipas[i]);
  }

  free(equipas);
}

int main()
{
  int estado = 1;
  int nl = 1;
  TabelaJogos *tabJogos = inicia_tabela_jogos(13);
  TabelaEquipas *tabEquipas = inicia_tabela_equipas(13);
  while (estado == 1)
  {
    char comando = getchar();
    switch (comando)
    {
      case 'a':
        adiciona_jogo(nl, tabJogos, tabEquipas);
        nl++;
        break;

      case 'A':
        adiciona_equipa(nl, tabEquipas);
        nl++;
        break;

      case 'l':
        lista_jogos(nl, tabJogos);
        nl++;
        break;

      case 'p':
        procurar_jogo(nl, tabJogos);
        nl++;
        break;

      case 'P':
        procurar_equipa(nl, tabEquipas);
        nl++;
        break;

      case 'r':
        apaga_jogo(nl, tabJogos, tabEquipas);
        nl++;
        break;

      case 's':
        altera_score(nl, tabJogos, tabEquipas);
        nl++;
        break;

      case 'g':
        melhores_equipas(nl, tabEquipas);
        nl++;
        break;

      case 'x':
        estado = 0;
        break;

    }

  }

  free_tabela_jogos(tabJogos);
  free_tabela_equipas(tabEquipas);
  return 0;
}

