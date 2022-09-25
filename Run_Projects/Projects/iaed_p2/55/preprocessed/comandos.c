/*File generated by PreProcessor.py*/


#include "constantes.h"
#include "comandos.h"
#include "listas.h"
#include "estruturas.h"
#include "tabelas_dispersao.h"


void seleciona_funcao(char comando, lista_ponteiro *lp, tabela_equipa *TB_eq, tabela_jogo *TB_jg, int M, int MJ, int NL)
{
  if (0)
  {
    printf("s_f:  comando=%c### NL = %d\n", comando, NL);
  }
  else
  {
    
  }

  switch (comando)
  {
    case 'a':
      a(lp, TB_eq, TB_jg, M, MJ, NL);
      break;

    case 'A':
      A(TB_eq, M, NL);
      break;

    case 'l':
      l(lp, NL);
      break;

    case 'p':
      p(TB_jg, MJ, NL);
      break;

    case 'P':
      P(TB_eq, M, NL);
      break;

    case 'r':
      r(lp, TB_eq, TB_jg, M, MJ, NL);
      break;

    case 's':
      s(TB_eq, TB_jg, M, MJ, NL);
      break;

    case 'g':
      g(TB_eq, M, NL);
      break;

  }

}

void a(lista_ponteiro *lp, tabela_equipa *TB_equipa, tabela_jogo *TB_jogo, int M, int MJ, int NL)
{
  char jogo[1024] = "";
  char equipa1[1024] = "";
  char equipa2[1024] = "";
  int score1 = 0;
  int score2 = 0;
  elo_jogo Novo_no = 0;
  elo_ponteiro no_ponteiro;
  elo_equipa No_equipa1 = 0;
  elo_equipa No_equipa2 = 0;
  lista_equipa *LE1 = 0;
  lista_equipa *LE2 = 0;
  lista *LJ = 0;
  for (int jogo_index = 0; jogo_index < 10; jogo_index++)
  {
    jogo[jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  jogo[10 - 1] = '\0';
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
  getchar();
  if (0)
  {
    printf("%d a %s:%s:%s:%i:%i\n", NL, jogo, equipa1, equipa2, score1, score2);
  }
  else
  {
    
  }

  LE1 = pesquisa_lista_equipa(TB_equipa, equipa1, M);
  LE2 = pesquisa_lista_equipa(TB_equipa, equipa2, M);
  LJ = pesquisa_lista_jogo(TB_jogo, jogo, MJ);
  if (LJ != 0)
  {
    if (procura_no_jogo(LJ, jogo) != 0)
    {
      printf("%d Jogo existente.\n", NL);
      return;
    }
    else
    {
      
    }

  }
  else
  {
    
  }

  if ((LE1 != 0) && (LE2 != 0))
  {
    No_equipa1 = procura_no_equipa(LE1, equipa1);
    No_equipa2 = procura_no_equipa(LE2, equipa2);
    if ((No_equipa1 == 0) || (No_equipa2 == 0))
    {
      printf("%d Equipa inexistente.\n", NL);
      return;
    }
    else
    {
      if ((No_equipa1 != 0) && (No_equipa2 != 0))
      {
        LJ = insere_ou_cria_lista_jogo(TB_jogo, jogo, MJ);
        Novo_no = cria_no_jogo(jogo, equipa1, equipa2, score1, score2);
        no_ponteiro = cria_no_ponteiro(Novo_no);
        Novo_no->pt_no_ponteiro = no_ponteiro;
        no_ponteiro->ponteiro = Novo_no;
        adiciona_fim(LJ, Novo_no);
        adiciona_fim_ponteiro(lp, no_ponteiro);
        if (score1 > score2)
        {
          *No_equipa1->vitorias += 1;
        }
        else
        {
          if (score1 < score2)
          {
            *No_equipa2->vitorias += 1;
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
  else
  {
    printf("%d Equipa inexistente.\n", NL);
  }

  return;
}

void A(tabela_equipa *TB_equipa, int M, int NL)
{
  char nome[1024] = "";
  elo_equipa Novo_no = 0;
  lista_equipa *LE = 0;
  if (0)
  {
    printf("comando A: \n");
  }
  else
  {
    
  }

  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  getchar();
  if (0)
  {
    printf("A %d:%s\n", NL, nome);
  }
  else
  {
    
  }

  LE = insere_ou_cria_lista_equipa(TB_equipa, nome, M);
  if (procura_no_equipa(LE, nome) != 0)
  {
    printf("%d Equipa existente.\n", NL);
  }
  else
  {
    Novo_no = cria_no_equipa(nome);
    adiciona_equipa_fim(LE, Novo_no);
  }

  return;
}

void l(lista_ponteiro *lp, int NL)
{
  elo_ponteiro inicio = lp->inicio;
  getchar();
  if (0)
  {
    printf("comando l: NL = %d\n", NL);
  }
  else
  {
    
  }

  while (inicio != 0)
  {
    printf("%d %s %s", NL, *inicio->ponteiro->jogo, *inicio->ponteiro->equipa1);
    printf(" %s", *inicio->ponteiro->equipa2);
    printf(" %d %d\n", *inicio->ponteiro->score1, *inicio->ponteiro->score2);
    inicio = inicio->proximo;
  }

  return;
}

void p(tabela_jogo *TB_jogo, int MJ, int NL)
{
  char jogo[1024] = "";
  elo_jogo No_jogo = 0;
  lista *LJ = 0;
  for (int jogo_index = 0; jogo_index < 10; jogo_index++)
  {
    jogo[jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  jogo[10 - 1] = '\0';
  getchar();
  if (0)
  {
    printf("p %s\n", jogo);
  }
  else
  {
    
  }

  if (0)
  {
    printf("comando l: NL = %d\n", NL);
  }
  else
  {
    
  }

  LJ = pesquisa_lista_jogo(TB_jogo, jogo, MJ);
  if (LJ != 0)
  {
    No_jogo = procura_no_jogo(LJ, jogo);
    if (No_jogo != 0)
    {
      printf("%d %s %s %s", NL, *No_jogo->jogo, *No_jogo->equipa1, *No_jogo->equipa2);
      printf(" %d %d\n", *No_jogo->score1, *No_jogo->score2);
    }
    else
    {
      printf("%d Jogo inexistente.\n", NL);
    }

  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

  return;
}

void P(tabela_equipa *TB_equipa, int M, int NL)
{
  char equipa[1024] = "";
  elo_equipa No_equipa = 0;
  lista_equipa *LE = 0;
  for (int equipa_index = 0; equipa_index < 10; equipa_index++)
  {
    equipa[equipa_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa[10 - 1] = '\0';
  getchar();
  LE = pesquisa_lista_equipa(TB_equipa, equipa, M);
  if (0)
  {
    printf("P %s\n", equipa);
  }
  else
  {
    
  }

  if (LE != 0)
  {
    No_equipa = procura_no_equipa(LE, equipa);
    if (No_equipa == 0)
    {
      printf("%d Equipa inexistente.\n", NL);
    }
    else
    {
      printf("%d %s %d\n", NL, equipa, *No_equipa->vitorias);
    }

  }
  else
  {
    printf("%d Equipa inexistente.\n", NL);
  }

  return;
}

void r(lista_ponteiro *lp, tabela_equipa *TB_equipa, tabela_jogo *TB_jogo, int M, int MJ, int NL)
{
  char jogo[1024] = "";
  elo_jogo No_jogo = 0;
  elo_ponteiro no_ponteiro = 0;
  elo_equipa No_equipa1 = 0;
  elo_equipa No_equipa2 = 0;
  lista_equipa *LE1 = 0;
  lista_equipa *LE2 = 0;
  lista *LJ = 0;
  for (int jogo_index = 0; jogo_index < 10; jogo_index++)
  {
    jogo[jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  jogo[10 - 1] = '\0';
  getchar();
  if (0)
  {
    printf("r %s\n", jogo);
  }
  else
  {
    
  }

  LJ = pesquisa_lista_jogo(TB_jogo, jogo, MJ);
  if (LJ != 0)
  {
    No_jogo = procura_no_jogo(LJ, jogo);
    if (No_jogo != 0)
    {
      LE1 = pesquisa_lista_equipa(TB_equipa, *No_jogo->equipa1, M);
      LE2 = pesquisa_lista_equipa(TB_equipa, *No_jogo->equipa2, M);
      if ((LE1 != 0) && (LE2 != 0))
      {
        No_equipa1 = procura_no_equipa(LE1, *No_jogo->equipa1);
        No_equipa2 = procura_no_equipa(LE2, *No_jogo->equipa2);
        if ((*No_jogo->score1) > (*No_jogo->score2))
        {
          *No_equipa1->vitorias -= 1;
        }
        else
        {
          if ((*No_jogo->score1) < (*No_jogo->score2))
          {
            *No_equipa2->vitorias -= 1;
          }
          else
          {
            
          }

        }

        no_ponteiro = No_jogo->pt_no_ponteiro;
        No_jogo->pt_no_ponteiro = 0;
        remove_no_ponteiro(lp, no_ponteiro);
        remove_no_jogo(LJ, No_jogo);
      }
      else
      {
        
      }

    }
    else
    {
      printf("%d Jogo inexistente.\n", NL);
    }

  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

  return;
}

void s(tabela_equipa *TB_equipa, tabela_jogo *TB_jogo, int M, int MJ, int NL)
{
  char jogo[1024] = "";
  int score1 = 0;
  int score2 = 0;
  int score_velho1 = 0;
  int score_velho2 = 0;
  elo_jogo No_jogo = 0;
  elo_equipa No_equipa1 = 0;
  elo_equipa No_equipa2 = 0;
  lista_equipa *LE1 = 0;
  lista_equipa *LE2 = 0;
  lista *LJ = 0;
  for (int jogo_index = 0; jogo_index < 10; jogo_index++)
  {
    jogo[jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  jogo[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  getchar();
  LJ = pesquisa_lista_jogo(TB_jogo, jogo, MJ);
  if (LJ != 0)
  {
    No_jogo = procura_no_jogo(LJ, jogo);
    if (No_jogo != 0)
    {
      LE1 = pesquisa_lista_equipa(TB_equipa, *No_jogo->equipa1, M);
      LE2 = pesquisa_lista_equipa(TB_equipa, *No_jogo->equipa2, M);
      if ((LE1 != 0) && (LE2 != 0))
      {
        score_velho1 = *No_jogo->score1;
        score_velho2 = *No_jogo->score2;
        No_equipa1 = procura_no_equipa(LE1, *No_jogo->equipa1);
        No_equipa2 = procura_no_equipa(LE2, *No_jogo->equipa2);
        altera_vitorias_empate(score1, score2, score_velho1, score_velho2, No_equipa1, No_equipa2);
        altera_vitorias_equipa1(score1, score2, score_velho1, score_velho2, No_equipa1, No_equipa2);
        altera_vitorias_equipa2(score1, score2, score_velho1, score_velho2, No_equipa1, No_equipa2);
        altera_score(score1, score2, No_jogo);
      }
      else
      {
        
      }

    }
    else
    {
      printf("%d Jogo inexistente.\n", NL);
    }

  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

  return;
}

int compara_nome(const void *a, const void *b)
{
  char ***aa;
  char ***bb;
  aa = (char ***) a;
  bb = (char ***) b;
  return strcmp(*(*aa), *(*bb));
}

void g(tabela_equipa *TB_equipa, int M, int NL)
{
  int i = 0;
  int k = 0;
  elo_equipa inicio = 0;
  lista_equipa *LE;
  int Max_vitorias = retorna_max_vitorias_tabela(TB_equipa, M);
  int Contador_vitorias = retorna_contador_max_vitorias_tabela(TB_equipa, M, Max_vitorias);
  char ***Vetor_equipas = (char ***) malloc((sizeof(char **)) * Contador_vitorias);
  getchar();
  if (eh_vazia_tabela_equipa(TB_equipa, M))
  {
    free(Vetor_equipas);
    return;
  }
  else
  {
    
  }

  if (!eh_vazia_tabela_equipa(TB_equipa, M))
  {
    for (i = 0; i < M; i++)
    {
      LE = TB_equipa->cabecas_eq[i];
      if (LE != 0)
      {
        inicio = LE->inicio;
        while (inicio != 0)
        {
          if ((*inicio->vitorias) == Max_vitorias)
          {
            Vetor_equipas[k++] = inicio->equipa;
          }
          else
          {
            
          }

          inicio = inicio->proximo;
        }

      }
      else
      {
        
      }

    }

  }
  else
  {
    
  }

  qsort(Vetor_equipas, Contador_vitorias, sizeof(char **), compara_nome);
  printf("%d Melhores %d\n", NL, Max_vitorias);
  for (i = 0; i < Contador_vitorias; i++)
  {
    printf("%d * %s\n", NL, *Vetor_equipas[i]);
  }

  free(Vetor_equipas);
  return;
}

