/*File generated by PreProcessor.py*/


#include <stdio.h>
#include "wrapper_futebol.h"


void a(tabela *jogos, tabela *equipas, int numero_linha);
void A(tabela *equipas, int numero_linha);
void l(tabela *jogos, int numero_linha);
void p(tabela *jogos, int numero_linha);
void P(tabela *equipas, int numero_linha);
void r(tabela *jogos, tabela *equipas, int numero_linha);
void s(tabela *jogos, tabela *equipas, int numero_linha);
void g();
int main()
{
  tabela *equipas = cria_tabela(1997);
  tabela *jogos = cria_tabela(1997);
  int ch;
  int numero_linha = 0;
  while (1)
  {
    switch (ch = getchar())
    {
      case 'a':
        a(jogos, equipas, ++numero_linha);
        break;

      case 'A':
        A(equipas, ++numero_linha);
        break;

      case 'l':
        l(jogos, ++numero_linha);
        break;

      case 'p':
        p(jogos, ++numero_linha);
        break;

      case 'P':
        P(equipas, ++numero_linha);
        break;

      case 'r':
        r(jogos, equipas, ++numero_linha);
        break;

      case 's':
        s(jogos, equipas, ++numero_linha);
        break;

      case 'g':
      {
        g(equipas, ++numero_linha);
        break;
      }

      case 'x':
        destroi_tabela(equipas, destroi_equipa);
        destroi_tabela(jogos, destroi_jogo);
        return 0;

    }

  }

}

void a(tabela *jogos, tabela *equipas, int numero_linha)
{
  int score_eq1;
  int score_eq2;
  char nome[1024];
  char nome_eq1[1024];
  char nome_eq2[1024];
  jogo novo_jogo;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  for (int nome_eq1_index = 0; nome_eq1_index < 10; nome_eq1_index++)
  {
    nome_eq1[nome_eq1_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_eq1[10 - 1] = '\0';
  for (int nome_eq2_index = 0; nome_eq2_index < 10; nome_eq2_index++)
  {
    nome_eq2[nome_eq2_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_eq2[10 - 1] = '\0';
  score_eq1 = new_sym_var(sizeof(int) * 8);
  score_eq2 = new_sym_var(sizeof(int) * 8);
  if (procura_jogo(jogos, nome) != 0)
  {
    printf("%d Jogo existente.\n", numero_linha);
  }
  else
  {
    if ((procura_equipa(equipas, nome_eq1) == 0) || (procura_equipa(equipas, nome_eq2) == 0))
    {
      printf("%d Equipa inexistente.\n", numero_linha);
    }
    else
    {
      novo_jogo = cria_jogo(nome, nome_eq1, nome_eq2, score_eq1, score_eq2);
      insere_jogo(jogos, equipas, novo_jogo.nome, &novo_jogo);
    }

  }

}

void A(tabela *equipas, int numero_linha)
{
  equipa nova_equipa;
  char nome[1024];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (procura_equipa(equipas, nome) != 0)
  {
    printf("%d Equipa existente.\n", numero_linha);
  }
  else
  {
    nova_equipa = cria_equipa(nome, 0);
    insere_equipa(equipas, nova_equipa.nome, &nova_equipa);
  }

}

bool imprime_jogo(char *nome, void *jogo_void, void *num_ptr)
{
  jogo *j = (jogo *) jogo_void;
  int numero_linha = *((int *) num_ptr);
  if (j != 0)
  {
    printf("%d %s %s %s %d %d\n", numero_linha, nome, j->nome_equipa1, j->nome_equipa2, j->score_eq1, j->score_eq2);
  }
  else
  {
    
  }

  return true;
}

void l(tabela *jogos, int numero_linha)
{
  void *num_ptr = (void *) (&numero_linha);
  iterar_ordenado(jogos, imprime_jogo, num_ptr);
}

void p(tabela *jogos, int numero_linha)
{
  jogo *jogo;
  char nome[1024];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if ((jogo = procura_jogo(jogos, nome)) == 0)
  {
    printf("%d Jogo inexistente.\n", numero_linha);
  }
  else
  {
    printf("%d %s %s %s %d %d\n", numero_linha, jogo->nome, jogo->nome_equipa1, jogo->nome_equipa2, jogo->score_eq1, jogo->score_eq2);
  }

}

void P(tabela *equipas, int numero_linha)
{
  equipa *equipa;
  char nome[1024];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if ((equipa = procura_equipa(equipas, nome)) == 0)
  {
    printf("%d Equipa inexistente.\n", numero_linha);
  }
  else
  {
    printf("%d %s %d\n", numero_linha, nome, equipa->jogos_ganhos);
  }

}

void r(tabela *jogos, tabela *equipas, int numero_linha)
{
  char nome[1024];
  jogo *jogo;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if ((jogo = procura_jogo(jogos, nome)) == 0)
  {
    printf("%d Jogo inexistente.\n", numero_linha);
  }
  else
  {
    remove_jogo(jogos, equipas, nome);
  }

}

void s(tabela *jogos, tabela *equipas, int numero_linha)
{
  int score1;
  int score2;
  char nome[1024];
  jogo *jogo;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if ((jogo = procura_jogo(jogos, nome)) == 0)
  {
    printf("%d Jogo inexistente.\n", numero_linha);
  }
  else
  {
    muda_pontuacao(equipas, jogo, score1, score2);
  }

}

bool melhores_equipas(char *chave, void *equipa_void, void *melhores_void)
{
  int score_max;
  bool status;
  equipa *e = (equipa *) equipa_void;
  lista_equipas *melhores = (lista_equipas *) melhores_void;
  node_equipa *inicio = obtem_inicio_lista(melhores);
  (void) chave;
  if ((melhores != 0) && (inicio != 0))
  {
    if ((e != 0) && (inicio->equipa != 0))
    {
      score_max = inicio->equipa->jogos_ganhos;
      if (e->jogos_ganhos > score_max)
      {
        destroi_lista(melhores);
        status = insere_lista(melhores, e);
      }
      else
      {
        if (e->jogos_ganhos == score_max)
        {
          status = insere_lista(melhores, e);
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
  else
  {
    status = insere_lista(melhores, e);
  }

  return status;
}

void g(tabela *equipas, int numero_linha)
{
  node_equipa *temp;
  lista_equipas melhores = cria_lista();
  lista_equipas melhores_ordenadas = cria_lista();
  iterar_tabela(equipas, melhores_equipas, (void *) (&melhores));
  ordenar_lista_equipas(&melhores, &melhores_ordenadas);
  temp = obtem_inicio_lista(&melhores_ordenadas);
  if ((temp != 0) && (temp->equipa != 0))
  {
    printf("%d Melhores %d\n", numero_linha, temp->equipa->jogos_ganhos);
    for (; temp != 0; temp = temp->next)
    {
      printf("%d * %s\n", numero_linha, temp->equipa->nome);
    }

  }
  else
  {
    
  }

  destroi_lista(&melhores);
  destroi_lista(&melhores_ordenadas);
}
