#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipa.h"
#include "HT_equipas.h"
#include "jogo.h"
#include "HT_jogos.h"
#include "lista_jogos.h"


void comando_A(int NL, HT_eq equipas);
void comando_P(int NL, HT_eq equipas);
void comando_a(int NL, HT_eq equipas, HT_jg jogos, Lista_jg lista);
void comando_p(int NL, HT_jg jogos);
void comando_s(int NL, HT_jg jogos);
void comando_l(int NL, Lista_jg lista);
void comando_r(int NL, HT_jg jogos, Lista_jg lista_jogos);
void comando_g(int NL, HT_eq equipas);
void termina(HT_eq equipas, HT_jg jogos, Lista_jg lista_jogos);
int main()
{
  int NL = 1;
  char comando;
  HT_eq equipas = HTeq_inicializa(1013);
  HT_jg jogos = HTjg_inicializa(1013);
  Lista_jg lista_jogos = LSTjg_inicializa();
  while (1)
  {
    comando = getchar();
    switch (comando)
    {
      case 'A':
      {
        comando_A(NL, equipas);
        break;
      }

      case 'P':
      {
        comando_P(NL, equipas);
        break;
      }

      case 'a':
      {
        comando_a(NL, equipas, jogos, lista_jogos);
        break;
      }

      case 'p':
      {
        comando_p(NL, jogos);
        break;
      }

      case 's':
      {
        comando_s(NL, jogos);
        break;
      }

      case 'l':
      {
        comando_l(NL, lista_jogos);
        break;
      }

      case 'r':
      {
        comando_r(NL, jogos, lista_jogos);
        break;
      }

      case 'g':
      {
        comando_g(NL, equipas);
        break;
      }

      case 'x':
      {
        termina(equipas, jogos, lista_jogos);
        return 0;
      }

    }

    getchar();
    NL++;
  }

  return 0;
}

void comando_A(int NL, HT_eq equipas)
{
  char n[1023];
  char *nome;
  for (int n_index = 0; n_index < 10; n_index++)
  {
    n[n_index] = new_sym_var(sizeof(char) * 8);
  }

  n[10 - 1] = '\0';
  nome = strdup(n);
  if (HTeq_procura(equipas, nome, 1013) == 0)
  {
    HTeq_adiciona(equipas, nome, 1013);
  }
  else
  {
    printf("%d Equipa existente.\n", NL);
  }

  free(nome);
}

void comando_P(int NL, HT_eq equipas)
{
  char n[1023];
  char *nome;
  Equipa eq;
  for (int n_index = 0; n_index < 10; n_index++)
  {
    n[n_index] = new_sym_var(sizeof(char) * 8);
  }

  n[10 - 1] = '\0';
  nome = strdup(n);
  eq = HTeq_procura(equipas, nome, 1013);
  if (eq == 0)
  {
    printf("%d Equipa inexistente.\n", NL);
  }
  else
  {
    printf("%d %s %d\n", NL, nome_equipa(eq), vitorias_equipa(eq));
  }

  free(nome);
}

void comando_a(int NL, HT_eq equipas, HT_jg jogos, Lista_jg lista)
{
  int score1;
  int score2;
  char n_jg[1023];
  char n_eq1[1023];
  char n_eq2[1023];
  char *nome;
  char *nome_eq1;
  char *nome_eq2;
  Equipa eq1;
  Equipa eq2;
  Jogo jogo;
  for (int n_jg_index = 0; n_jg_index < 10; n_jg_index++)
  {
    n_jg[n_jg_index] = new_sym_var(sizeof(char) * 8);
  }

  n_jg[10 - 1] = '\0';
  for (int n_eq1_index = 0; n_eq1_index < 10; n_eq1_index++)
  {
    n_eq1[n_eq1_index] = new_sym_var(sizeof(char) * 8);
  }

  n_eq1[10 - 1] = '\0';
  for (int n_eq2_index = 0; n_eq2_index < 10; n_eq2_index++)
  {
    n_eq2[n_eq2_index] = new_sym_var(sizeof(char) * 8);
  }

  n_eq2[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  nome = strdup(n_jg);
  nome_eq1 = strdup(n_eq1);
  nome_eq2 = strdup(n_eq2);
  if (HTjg_procura(jogos, nome, 1013) != 0)
  {
    printf("%d Jogo existente.\n", NL);
  }
  else
  {
    eq1 = HTeq_procura(equipas, nome_eq1, 1013);
    eq2 = HTeq_procura(equipas, nome_eq2, 1013);
    if ((eq1 == 0) || (eq2 == 0))
    {
      printf("%d Equipa inexistente.\n", NL);
    }
    else
    {
      jogo = novo_jogo(nome, eq1, eq2, score1, score2);
      HTjg_adiciona(jogos, nome, jogo, 1013);
      LSTjg_adiciona(lista, jogo);
    }

  }

  free(nome);
  free(nome_eq1);
  free(nome_eq2);
}

void comando_p(int NL, HT_jg jogos)
{
  char n[1023];
  char *nome;
  Jogo jg;
  for (int n_index = 0; n_index < 10; n_index++)
  {
    n[n_index] = new_sym_var(sizeof(char) * 8);
  }

  n[10 - 1] = '\0';
  nome = strdup(n);
  jg = HTjg_procura(jogos, nome, 1013);
  if (jg == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    escreve_jogo(jg, NL);
  }

  free(nome);
}

void comando_s(int NL, HT_jg jogos)
{
  int novo_score1;
  int novo_score2;
  char n[1023];
  char *nome;
  Jogo jogo;
  Equipa antigo_vencedor;
  Equipa novo_vencedor;
  for (int n_index = 0; n_index < 10; n_index++)
  {
    n[n_index] = new_sym_var(sizeof(char) * 8);
  }

  n[10 - 1] = '\0';
  novo_score1 = new_sym_var(sizeof(int) * 8);
  novo_score2 = new_sym_var(sizeof(int) * 8);
  nome = strdup(n);
  jogo = HTjg_procura(jogos, nome, 1013);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    antigo_vencedor = vencedor_jogo(jogo);
    atualiza_scores_jg(jogo, novo_score1, novo_score2);
    novo_vencedor = vencedor_jogo(jogo);
    if ((antigo_vencedor == 0) && (novo_vencedor != 0))
    {
      altera_vitorias_eq(novo_vencedor, 1);
    }
    else
    {
      if ((antigo_vencedor != 0) && (novo_vencedor == 0))
      {
        altera_vitorias_eq(antigo_vencedor, -1);
      }
      else
      {
        if (antigo_vencedor != novo_vencedor)
        {
          altera_vitorias_eq(novo_vencedor, 1);
          altera_vitorias_eq(antigo_vencedor, -1);
        }
        else
        {
          
        }

      }

    }

  }

  free(nome);
}

void comando_l(int NL, Lista_jg lista)
{
  LSTjg_escreve(NL, lista);
}

void comando_r(int NL, HT_jg jogos, Lista_jg lista_jogos)
{
  char *nome;
  char n[1023];
  Jogo jogo;
  Equipa vencedor;
  for (int n_index = 0; n_index < 10; n_index++)
  {
    n[n_index] = new_sym_var(sizeof(char) * 8);
  }

  n[10 - 1] = '\0';
  nome = strdup(n);
  jogo = HTjg_procura(jogos, nome, 1013);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    vencedor = vencedor_jogo(jogo);
    if (vencedor != 0)
    {
      altera_vitorias_eq(vencedor, -1);
    }
    else
    {
      
    }

    LSTjg_apaga(lista_jogos, jogo);
    HTjg_apaga(jogos, nome, jogo, 1013);
    apaga_jogo(jogo);
  }

  free(nome);
}

void comando_g(int NL, HT_eq equipas)
{
  int max_num[2];
  int max_v;
  int num;
  int i;
  Equipa *melhores;
  maximo_vitorias(equipas, max_num, 1013);
  max_v = max_num[0];
  num = max_num[1];
  if (num == 0)
  {
    return;
  }
  else
  {
    
  }

  melhores = (Equipa *) malloc(num * (sizeof(Equipa)));
  melhores_equipas(equipas, melhores, max_v, 1013);
  qsort(melhores, num, sizeof(Equipa), compara_eq);
  printf("%d Melhores %d\n", NL, max_v);
  for (i = 0; i < num; i++)
    printf("%d * %s\n", NL, nome_equipa(melhores[i]));

  free(melhores);
}

void termina(HT_eq equipas, HT_jg jogos, Lista_jg lista_jogos)
{
  LSTjg_termina(lista_jogos);
  HTjg_termina(jogos, 1013);
  HTeq_termina(equipas, 1013);
}

