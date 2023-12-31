#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include "proj2_aux.h"
#include "proj2_comandos.h"


void a(int NL, char *atr1, char *atr2, char *atr3, char *atr4, char *atr5, Lista_jogos_equipas *lje)
{
  Equipa *equipa_1;
  Equipa *equipa_2;
  Jogo *novo_jogo;
  int posicao = hash(atr1);
  if (procura_nome_jogo(lje, atr1) != 0)
  {
    printf("%d Jogo existente.\n", NL);
    return;
  }
  else
  {
    
  }

  equipa_1 = procura_nome_equipa(lje, atr2);
  equipa_2 = procura_nome_equipa(lje, atr3);
  if ((equipa_1 == 0) || (equipa_2 == 0))
  {
    printf("%d Equipa inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  novo_jogo = adiciona_jogo(atr1, equipa_1, equipa_2, atr4, atr5);
  if (lje->primeiro_jogo == 0)
  {
    lje->primeiro_jogo = novo_jogo;
  }
  else
  {
    novo_jogo->jogo_anterior = lje->ultimo_jogo;
    lje->ultimo_jogo->jogo_seguinte = novo_jogo;
  }

  lje->ultimo_jogo = novo_jogo;
  if (lje->tab_jogo[posicao]->primeiro_jogo == 0)
  {
    lje->tab_jogo[posicao]->primeiro_jogo = novo_jogo;
  }
  else
  {
    novo_jogo->anterior_tabela = lje->tab_jogo[posicao]->ultimo_jogo;
    lje->tab_jogo[posicao]->ultimo_jogo->prox_tabela = novo_jogo;
  }

  lje->tab_jogo[posicao]->ultimo_jogo = novo_jogo;
  if (novo_jogo->score1 > novo_jogo->score2)
  {
    novo_jogo->equipa1->vitorias += 1;
  }
  else
  {
    if (novo_jogo->score2 > novo_jogo->score1)
    {
      novo_jogo->equipa2->vitorias += 1;
    }
    else
    {
      
    }

  }

}

void A(int NL, char *atr1, Lista_jogos_equipas *lje)
{
  Equipa *nova_equipa;
  int posicao = hash(atr1);
  if (procura_nome_equipa(lje, atr1) != 0)
  {
    printf("%d Equipa existente.\n", NL);
    return;
  }
  else
  {
    
  }

  nova_equipa = adiciona_equipa(atr1);
  if (lje->primeira_equipa == 0)
  {
    lje->primeira_equipa = nova_equipa;
  }
  else
  {
    lje->ultima_equipa->equipa_seguinte = nova_equipa;
  }

  lje->ultima_equipa = nova_equipa;
  if (lje->tab_equipa[posicao]->primeira_equipa == 0)
  {
    lje->tab_equipa[posicao]->primeira_equipa = nova_equipa;
  }
  else
  {
    lje->tab_equipa[posicao]->ultima_equipa->prox_tabela = nova_equipa;
  }

  lje->tab_equipa[posicao]->ultima_equipa = nova_equipa;
}

void l(int NL, Lista_jogos_equipas *lje)
{
  Jogo *jogo = lje->primeiro_jogo;
  while (jogo != 0)
  {
    printf("%d %s %s %s %d %d\n", NL, jogo->nome, jogo->equipa1->nome, jogo->equipa2->nome, jogo->score1, jogo->score2);
    jogo = jogo->jogo_seguinte;
  }

}

void p(int NL, char *atr1, Lista_jogos_equipas *lje)
{
  Jogo *jogo = procura_nome_jogo(lje, atr1);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    printf("%d %s %s %s %d %d\n", NL, jogo->nome, jogo->equipa1->nome, jogo->equipa2->nome, jogo->score1, jogo->score2);
  }

}

void P(int NL, char *atr1, Lista_jogos_equipas *lje)
{
  Equipa *equipa = procura_nome_equipa(lje, atr1);
  if (equipa == 0)
  {
    printf("%d Equipa inexistente.\n", NL);
  }
  else
  {
    printf("%d %s %d\n", NL, equipa->nome, equipa->vitorias);
  }

}

void r(int NL, char *atr1, Lista_jogos_equipas *lje)
{
  Jogo *jogo;
  int posicao = hash(atr1);
  jogo = procura_nome_jogo(lje, atr1);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  if (lje->primeiro_jogo == jogo)
  {
    if (lje->ultimo_jogo == jogo)
    {
      lje->primeiro_jogo = 0;
      lje->ultimo_jogo = 0;
    }
    else
    {
      jogo->jogo_seguinte->jogo_anterior = 0;
      lje->primeiro_jogo = jogo->jogo_seguinte;
    }

  }
  else
  {
    if (lje->ultimo_jogo == jogo)
    {
      jogo->jogo_anterior->jogo_seguinte = 0;
      lje->ultimo_jogo = jogo->jogo_anterior;
    }
    else
    {
      jogo->jogo_anterior->jogo_seguinte = jogo->jogo_seguinte;
      jogo->jogo_seguinte->jogo_anterior = jogo->jogo_anterior;
    }

  }

  if (lje->tab_jogo[posicao]->primeiro_jogo == jogo)
  {
    if (lje->tab_jogo[posicao]->ultimo_jogo == jogo)
    {
      lje->tab_jogo[posicao]->primeiro_jogo = 0;
      lje->tab_jogo[posicao]->ultimo_jogo = 0;
    }
    else
    {
      jogo->prox_tabela->anterior_tabela = 0;
      lje->tab_jogo[posicao]->primeiro_jogo = jogo->prox_tabela;
    }

  }
  else
  {
    if (lje->tab_jogo[posicao]->ultimo_jogo == jogo)
    {
      jogo->anterior_tabela->prox_tabela = 0;
      lje->tab_jogo[posicao]->ultimo_jogo = jogo->anterior_tabela;
    }
    else
    {
      jogo->anterior_tabela->prox_tabela = jogo->prox_tabela;
      jogo->prox_tabela->anterior_tabela = jogo->anterior_tabela;
    }

  }

  if (jogo->score1 > jogo->score2)
  {
    jogo->equipa1->vitorias -= 1;
  }
  else
  {
    if (jogo->score2 > jogo->score1)
    {
      jogo->equipa2->vitorias -= 1;
    }
    else
    {
      
    }

  }

  free(jogo->nome);
  free(jogo);
}

void s(int NL, char *atr1, char *atr2, char *atr3, Lista_jogos_equipas *lje)
{
  Jogo *jogo = procura_nome_jogo(lje, atr1);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  if (jogo->score1 > jogo->score2)
  {
    jogo->equipa1->vitorias -= 1;
  }
  else
  {
    if (jogo->score2 > jogo->score1)
    {
      jogo->equipa2->vitorias -= 1;
    }
    else
    {
      
    }

  }

  jogo->score1 = atoi(atr2);
  jogo->score2 = atoi(atr3);
  if (jogo->score1 > jogo->score2)
  {
    jogo->equipa1->vitorias += 1;
  }
  else
  {
    if (jogo->score2 > jogo->score1)
    {
      jogo->equipa2->vitorias += 1;
    }
    else
    {
      
    }

  }

}

void g(int NL, Lista_jogos_equipas *lje)
{
  Tabela_equipas *max_vitorias;
  int num_max_vitorias;
  num_max_vitorias = procura_max_vitorias(lje);
  max_vitorias = procura_equipa_vitorias(lje, num_max_vitorias);
  ordena_equipa_vitorias(max_vitorias, NL, num_max_vitorias);
}

