#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "estruturas.h"


void A_add_equipa(int cont, NodeE **tabelaE);
NodeJ *a_add_jogo(int cont, NodeJ **tabelaJ, NodeE **tabelaE, NodeJ **cauda, NodeJ *cabeca);
void l_listaJ_data(int cont, NodeJ *cabecaJ);
void p_procura_jogo(int cont, NodeJ **tabelaJ);
void P_procura_equipa(int cont, NodeE **tabelaE);
NodeJ *r_remove_jogo(int cont, NodeJ **tabelaJ, NodeJ *cabecaJ, NodeJ **caudaJ, NodeE **tabelaE);
void s_altera_resultado(int cont, NodeJ **tabelaJ, NodeE **tabelaE);
void g_encontra_mais_vitorias(int cont, NodeE **tabelaE);
int main()
{
  char n;
  int cont = 1;
  NodeE **tabelaE = init_hash_tableE();
  NodeJ **tabelaJ = init_hash_tableJ();
  NodeJ *cabecaJ = 0;
  NodeJ *caudaJ = 0;
  n = getchar();
  while (n != 'x')
  {
    switch (n)
    {
      case 'a':
        cabecaJ = a_add_jogo(cont++, tabelaJ, tabelaE, &caudaJ, cabecaJ);
        break;

      case 'A':
        A_add_equipa(cont++, tabelaE);
        break;

      case 'l':
        l_listaJ_data(cont++, cabecaJ);
        break;

      case 'p':
        p_procura_jogo(cont++, tabelaJ);
        break;

      case 'P':
        P_procura_equipa(cont++, tabelaE);
        break;

      case 'r':
        cabecaJ = r_remove_jogo(cont++, tabelaJ, cabecaJ, &caudaJ, tabelaE);
        break;

      case 's':
        s_altera_resultado(cont++, tabelaJ, tabelaE);
        break;

      case 'g':
        g_encontra_mais_vitorias(cont++, tabelaE);
        break;

    }

    n = getchar();
  }

  free_tabelaE(tabelaE);
  free_tabelaJ(tabelaJ);
  return 0;
}

void A_add_equipa(int cont, NodeE **tabelaE)
{
  char nome[1024];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (encontra_tabelaE(tabelaE, nome) != 0)
  {
    printf("%d Equipa existente.\n", cont);
  }
  else
  {
    hash_table_insertE(tabelaE, nome, 0);
  }

}

NodeJ *a_add_jogo(int cont, NodeJ **tabelaJ, NodeE **tabelaE, NodeJ **caudaJ, NodeJ *cabecaJ)
{
  char nomej[1024];
  char nome1[1024];
  char nome2[1024];
  int res1;
  int res2;
  NodeE *equipa1;
  NodeE *equipa2;
  for (int nomej_index = 0; nomej_index < 10; nomej_index++)
  {
    nomej[nomej_index] = new_sym_var(sizeof(char) * 8);
  }

  nomej[10 - 1] = '\0';
  for (int nome1_index = 0; nome1_index < 10; nome1_index++)
  {
    nome1[nome1_index] = new_sym_var(sizeof(char) * 8);
  }

  nome1[10 - 1] = '\0';
  for (int nome2_index = 0; nome2_index < 10; nome2_index++)
  {
    nome2[nome2_index] = new_sym_var(sizeof(char) * 8);
  }

  nome2[10 - 1] = '\0';
  res1 = new_sym_var(sizeof(int) * 8);
  res2 = new_sym_var(sizeof(int) * 8);
  equipa1 = encontra_tabelaE(tabelaE, nome1);
  equipa2 = encontra_tabelaE(tabelaE, nome2);
  if (encontra_tabelaJ(tabelaJ, nomej) != 0)
  {
    printf("%d Jogo existente.\n", cont);
  }
  else
  {
    if ((equipa1 == 0) || (equipa2 == 0))
    {
      printf("%d Equipa inexistente.\n", cont);
    }
    else
    {
      cabecaJ = insertEnd_listaJ(cabecaJ, caudaJ, tabelaJ, nomej, nome1, nome2, res1, res2);
      if (res1 > res2)
      {
        equipa1->vitorias += 1;
      }
      else
      {
        if (res1 < res2)
        {
          equipa2->vitorias += 1;
        }
        else
        {
          
        }

      }

    }

  }

  return cabecaJ;
}

void l_listaJ_data(int cont, NodeJ *cabecaJ)
{
  print_listaJ(cont, cabecaJ);
}

void p_procura_jogo(int cont, NodeJ **tabelaJ)
{
  char nome[1024];
  NodeJ *jogo;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  jogo = encontra_tabelaJ(tabelaJ, nome);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", cont);
  }
  else
  {
    print_jogo(cont, jogo);
  }

}

void P_procura_equipa(int cont, NodeE **tabelaE)
{
  char nome[1024];
  NodeE *equipa;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  equipa = encontra_tabelaE(tabelaE, nome);
  if (equipa == 0)
  {
    printf("%d Equipa inexistente.\n", cont);
  }
  else
  {
    print_equipa(cont, equipa);
  }

}

NodeJ *r_remove_jogo(int cont, NodeJ **tabelaJ, NodeJ *cabecaJ, NodeJ **caudaJ, NodeE **tabelaE)
{
  char nome[1024];
  NodeJ *jogo;
  NodeE *equipa1;
  NodeE *equipa2;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  jogo = encontra_tabelaJ(tabelaJ, nome);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", cont);
  }
  else
  {
    equipa1 = encontra_tabelaE(tabelaE, jogo->casa);
    equipa2 = encontra_tabelaE(tabelaE, jogo->fora);
    if (jogo->resCasa > jogo->resFora)
    {
      equipa1->vitorias -= 1;
    }
    else
    {
      if (jogo->resFora > jogo->resCasa)
      {
        equipa2->vitorias -= 1;
      }
      else
      {
        
      }

    }

    cabecaJ = remove_listaJ(cabecaJ, caudaJ, tabelaJ, jogo->nome);
  }

  return cabecaJ;
}

void s_altera_resultado(int cont, NodeJ **tabelaJ, NodeE **tabelaE)
{
  char nome[1024];
  int score1;
  int score2;
  NodeJ *jogo;
  NodeE *equipaCasa;
  NodeE *equipaFora;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  jogo = encontra_tabelaJ(tabelaJ, nome);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", cont);
  }
  else
  {
    equipaCasa = encontra_tabelaE(tabelaE, jogo->casa);
    equipaFora = encontra_tabelaE(tabelaE, jogo->fora);
    if ((jogo->resCasa > jogo->resFora) && (score1 <= score2))
    {
      equipaCasa->vitorias -= 1;
      if (score1 < score2)
      {
        equipaFora->vitorias += 1;
      }
      else
      {
        
      }

    }
    else
    {
      if ((jogo->resCasa < jogo->resFora) && (score1 >= score2))
      {
        equipaFora->vitorias -= 1;
        if (score1 > score2)
        {
          equipaCasa->vitorias += 1;
        }
        else
        {
          
        }

      }
      else
      {
        if (jogo->resCasa == jogo->resFora)
        {
          if (score1 > score2)
          {
            equipaCasa->vitorias += 1;
          }
          else
          {
            if (score1 < score2)
            {
              equipaFora->vitorias += 1;
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

    }

    jogo->resCasa = score1;
    jogo->resFora = score2;
  }

}

int comparador_de_strings(const void *x, const void *y)
{
  char **pont1 = (char **) x;
  char **pont2 = (char **) y;
  return strcmp(*pont1, *pont2) > 0;
}

void g_encontra_mais_vitorias(int cont, NodeE **tabelaE)
{
  int i = 0;
  int n = 0;
  int max = 0;
  int k;
  char **vector;
  NodeE *t;
  for (i = 0; i < 1507; i++)
  {
    if (tabelaE[i] != 0)
    {
      t = tabelaE[i];
      while (t != 0)
      {
        if (t->vitorias == max)
        {
          n += 1;
        }
        else
        {
          if (t->vitorias > max)
          {
            max = t->vitorias;
            n = 1;
          }
          else
          {
            
          }

        }

        t = t->next;
      }

    }
    else
    {
      
    }

  }

  vector = malloc(n * (sizeof(char *)));
  n = 0;
  for (i = 0; i < 1507; i++)
  {
    if (tabelaE[i] != 0)
    {
      t = tabelaE[i];
      while (t != 0)
      {
        if (t->vitorias == max)
        {
          vector[n] = t->nome;
          n += 1;
        }
        else
        {
          
        }

        t = t->next;
      }

    }
    else
    {
      
    }

  }

  if (n)
  {
    qsort(vector, n, sizeof(char *), comparador_de_strings);
    printf("%d Melhores %d\n", cont, max);
    for (k = 0; k < n; k++)
    {
      printf("%d * %s\n", cont, vector[k]);
    }

  }
  else
  {
    
  }

  free(vector);
}

