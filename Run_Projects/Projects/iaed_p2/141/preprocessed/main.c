/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"


char *copia_string(char *string);
void ad_novo_jogo(int linha, Hashtable_j ht_jogos, Lista nomes, Hashtable_eq ht_equipas);
void imprime_jogos(int linha, Hashtable_j ht_jogos, Lista nomes);
void procura_jogo(int linha, Hashtable_j ht_jogos);
void apaga_jogo(int linha, Hashtable_j ht_jogos, Lista nomes);
void altera_score(int linha, Hashtable_j ht_jogos);
void ad_nova_equipa(int linha, Hashtable_eq ht_equipas, Vetor equipas);
void procura_equipa(int linha, Hashtable_eq ht_equipas);
void encontra_melhores(int linha, Hashtable_eq ht_equipas, Vetor equipas);
int comparador(const void *a, const void *b);
int main()
{
  char letra;
  int linha = 1;
  Lista nomes = criaLista();
  Vetor equipas = inicializaVetor(389);
  Hashtable_j ht_jogos = inicializaHT_j(769);
  Hashtable_eq ht_equipas = inicializaHT_eq(389);
  while (1)
  {
    switch (letra = getchar())
    {
      case 'a':
        ad_novo_jogo(linha, ht_jogos, nomes, ht_equipas);
        linha++;
        break;

      case 'l':
        imprime_jogos(linha, ht_jogos, nomes);
        linha++;
        break;

      case 'p':
        procura_jogo(linha, ht_jogos);
        linha++;
        break;

      case 'r':
        apaga_jogo(linha, ht_jogos, nomes);
        linha++;
        break;

      case 's':
        altera_score(linha, ht_jogos);
        linha++;
        break;

      case 'A':
        ad_nova_equipa(linha, ht_equipas, equipas);
        linha++;
        break;

      case 'P':
        procura_equipa(linha, ht_equipas);
        linha++;
        break;

      case 'g':
        encontra_melhores(linha, ht_equipas, equipas);
        linha++;
        break;

      case 'x':
        freeLista(nomes);
        freeVetor(equipas);
        freeHT_eq(ht_equipas);
        freeHT_j(ht_jogos);
        return 0;

    }

  }

}

char *copia_string(char *string)
{
  char *nova = malloc(((sizeof(char)) * strlen(string)) + 1);
  strcpy(nova, string);
  return nova;
}

void ad_novo_jogo(int linha, Hashtable_j ht_jogos, Lista nomes, Hashtable_eq ht_equipas)
{
  char *n;
  char nome[1023];
  char equipa1[1023];
  char equipa2[1023];
  int score1;
  int score2;
  Equipa eq1;
  Equipa eq2;
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
  if (procuraHT_j(ht_jogos, nome))
  {
    printf("%d Jogo existente.\n", linha);
  }
  else
  {
    if ((!(eq1 = procuraHT_eq(ht_equipas, equipa1))) || (!(eq2 = procuraHT_eq(ht_equipas, equipa2))))
    {
      printf("%d Equipa inexistente.\n", linha);
    }
    else
    {
      {
        Jogo jogo = malloc(sizeof(struct jogo));
        n = copia_string(nome);
        jogo->nome = n;
        insereLista(nomes, n);
        jogo->equipa1 = eq1;
        jogo->equipa2 = eq2;
        jogo->score1 = score1;
        jogo->score2 = score2;
        if (score1 > score2)
        {
          eq1->vitorias++;
        }
        else
        {
          if (score2 > score1)
          {
            eq2->vitorias++;
          }
          else
          {
            
          }

        }

        insereHT_j(ht_jogos, jogo);
      }
    }

  }

}

void imprime_jogos(int linha, Hashtable_j ht_jogos, Lista nomes)
{
  Node current = nomes->primeiro;
  while (current != 0)
  {
    printf("%d ", linha);
    imprime_jogo(procuraHT_j(ht_jogos, current->c));
    current = current->prox;
  }

}

void procura_jogo(int linha, Hashtable_j ht_jogos)
{
  char nome[1023];
  Jogo jogo;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (jogo = procuraHT_j(ht_jogos, nome))
  {
    {
      printf("%d ", linha);
      imprime_jogo(jogo);
    }
  }
  else
  {
    printf("%d Jogo inexistente.\n", linha);
  }

}

void apaga_jogo(int linha, Hashtable_j ht_jogos, Lista nomes)
{
  char nome[1023];
  Jogo jogo;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (!(jogo = procuraHT_j(ht_jogos, nome)))
  {
    printf("%d Jogo inexistente.\n", linha);
  }
  else
  {
    {
      if (jogo->score1 > jogo->score2)
      {
        jogo->equipa1->vitorias--;
      }
      else
      {
        if (jogo->score2 > jogo->score1)
        {
          jogo->equipa2->vitorias--;
        }
        else
        {
          
        }

      }

      apagaLista(nomes, nome);
      apagaHT_j(ht_jogos, nome);
    }
  }

}

void altera_score(int linha, Hashtable_j ht_jogos)
{
  char nome[1023];
  int antigo_score1;
  int antigo_score2;
  int score1;
  int score2;
  Jogo jogo;
  Equipa eq1;
  Equipa eq2;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (!(jogo = procuraHT_j(ht_jogos, nome)))
  {
    printf("%d Jogo inexistente.\n", linha);
  }
  else
  {
    {
      eq1 = jogo->equipa1;
      eq2 = jogo->equipa2;
      antigo_score1 = jogo->score1;
      antigo_score2 = jogo->score2;
      jogo->score1 = score1;
      jogo->score2 = score2;
      if ((antigo_score1 > antigo_score2) && (score1 <= score2))
      {
        {
          if (score1 < score2)
          {
            eq2->vitorias++;
          }
          else
          {
            
          }

          eq1->vitorias--;
        }
      }
      else
      {
        if ((antigo_score1 < antigo_score2) && (score1 >= score2))
        {
          {
            if (score1 > score2)
            {
              eq1->vitorias++;
            }
            else
            {
              
            }

            eq2->vitorias--;
          }
        }
        else
        {
          if (antigo_score1 == antigo_score2)
          {
            {
              if (score1 > score2)
              {
                eq1->vitorias++;
              }
              else
              {
                if (score1 < score2)
                {
                  eq2->vitorias++;
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

      }

    }
  }

}

void ad_nova_equipa(int linha, Hashtable_eq ht_equipas, Vetor equipas)
{
  char nome[1023];
  char *eq;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (procuraHT_eq(ht_equipas, nome))
  {
    printf("%d Equipa existente.\n", linha);
  }
  else
  {
    {
      Equipa nova = malloc(sizeof(struct equipa));
      eq = copia_string(nome);
      nova->nome = eq;
      nova->vitorias = 0;
      insereHT_eq(ht_equipas, nova);
      insereVetor(equipas, nova);
    }
  }

}

void procura_equipa(int linha, Hashtable_eq ht_equipas)
{
  char nome[1023];
  Equipa equipa;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (equipa = procuraHT_eq(ht_equipas, nome))
  {
    {
      printf("%d ", linha);
      imprime_equipa(equipa);
    }
  }
  else
  {
    printf("%d Equipa inexistente.\n", linha);
  }

}

void encontra_melhores(int linha, Hashtable_eq ht_equipas, Vetor equipas)
{
  int N = ht_equipas->N;
  if (N > 0)
  {
    {
      int max_vitorias;
      int i = 0;
      qsort(equipas->vetor, equipas->N, sizeof(Equipa), comparador);
      max_vitorias = equipas->vetor[0]->vitorias;
      printf("%d Melhores %d\n", linha, max_vitorias);
      while ((i < N) && (equipas->vetor[i]->vitorias == max_vitorias))
      {
        printf("%d * %s\n", linha, equipas->vetor[i]->nome);
        i++;
      }

    }
  }
  else
  {
    
  }

}

int comparador(const void *a, const void *b)
{
  const Equipa *eq1 = (Equipa *) a;
  const Equipa *eq2 = (Equipa *) b;
  int diferenca = (*eq2)->vitorias - (*eq1)->vitorias;
  if (diferenca != 0)
  {
    return diferenca;
  }
  else
  {
    return strcmp((*eq1)->nome, (*eq2)->nome);
  }

}

