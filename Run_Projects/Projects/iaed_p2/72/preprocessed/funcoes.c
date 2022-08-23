/*File generated by PreProcessor.py*/


#include "funcoes.h"


unsigned int a(unsigned int NL, Jogos jogos, Equipas equipas)
{
  Jogo novo;
  Equipa eq1;
  Equipa eq2;
  char nome[1024];
  char nome_eq1[1024];
  char nome_eq2[1024];
  int size_nome;
  int score1;
  int score2;
  size_nome = get_string(nome);
  get_string(nome_eq1);
  get_string(nome_eq2);
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (procura_jogo(jogos, nome) != 0)
  {
    {
      printf("%u Jogo existente.\n", NL);
      return ++NL;
    }
  }
  else
  {
    if (((eq1 = procura_equipa(equipas, nome_eq1)) == 0) || ((eq2 = procura_equipa(equipas, nome_eq2)) == 0))
    {
      {
        printf("%u Equipa inexistente.\n", NL);
        return ++NL;
      }
    }
    else
    {
      
    }

  }

  novo = cria_jogo(nome, size_nome, eq1, eq2, score1, score2);
  insere_jogo(jogos, novo);
  return ++NL;
}

unsigned int l(unsigned int NL, Jogos jogos)
{
  print_todos_jogos(jogos, NL);
  return ++NL;
}

unsigned int p(unsigned int NL, Jogos jogos)
{
  Jogo atual;
  char nome[1024];
  get_string(nome);
  if ((atual = procura_jogo(jogos, nome)) == 0)
  {
    printf("%u Jogo inexistente.\n", NL);
  }
  else
  {
    printf("%u %s %s %s %d %d\n", NL, atual->nome, atual->equipa1->nome, atual->equipa2->nome, atual->score1, atual->score2);
  }

  return ++NL;
}

unsigned int A(unsigned int NL, Equipas equipas)
{
  char nome[1024];
  int size;
  Equipa nova;
  size = get_string(nome);
  if (procura_equipa(equipas, nome) != 0)
  {
    {
      printf("%u Equipa existente.\n", NL);
      return ++NL;
    }
  }
  else
  {
    
  }

  nova = cria_equipa(nome, size);
  insere_equipa(equipas, nova);
  return ++NL;
}

unsigned int P(unsigned int NL, Equipas equipas)
{
  Equipa atual;
  char nome[1024];
  get_string(nome);
  if ((atual = procura_equipa(equipas, nome)) == 0)
  {
    {
      printf("%u Equipa inexistente.\n", NL);
      return ++NL;
    }
  }
  else
  {
    printf("%u %s %d\n", NL, atual->nome, atual->vitorias);
  }

  return ++NL;
}

unsigned int r(unsigned int NL, Jogos jogos)
{
  char nome[1024];
  Jogo jogo;
  get_string(nome);
  if ((jogo = remove_jogos(jogos, nome)) == 0)
  {
    printf("%u Jogo inexistente.\n", NL);
  }
  else
  {
    remove_jogo(jogo);
  }

  return ++NL;
}

unsigned int s(unsigned int NL, Jogos jogos)
{
  char nome[1024];
  int score1;
  int score2;
  Jogo jg;
  get_string(nome);
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if ((jg = procura_jogo(jogos, nome)) == 0)
  {
    {
      printf("%u Jogo inexistente.\n", NL);
      return ++NL;
    }
  }
  else
  {
    
  }

  altera_score(jg, score1, score2);
  return ++NL;
}

unsigned int g(unsigned int NL, Equipas equipas)
{
  print_vencedores(equipas, NL);
  return ++NL;
}

