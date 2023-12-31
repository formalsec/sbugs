#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "tabela_jogos.h"


pTabela_jogos inicializa_tabela_jogos(unsigned int max)
{
  unsigned int i;
  pTabela_jogos tabela = (pTabela_jogos) malloc(sizeof(struct tabela_jogos));
  tabela->num_jogos = 0;
  tabela->tamanho = max;
  tabela->jogos = (pJogo *) malloc(max * (sizeof(pJogo)));
  for (i = 0; i < tabela->tamanho; i++)
    tabela->jogos[i] = 0;

  return tabela;
}

void expande_tabela_jogos(pTabela_jogos tabela)
{
  unsigned int i;
  pTabela_jogos tabela_aux;
  tabela_aux = inicializa_tabela_jogos(tabela->tamanho * 2);
  for (i = 0; i < tabela->tamanho; i++)
    if (tabela->jogos[i] != 0)
  {
    adiciona_jogo_tabela(tabela_aux, tabela->jogos[i]);
  }
  else
  {
    
  }


  free(tabela->jogos);
  tabela->jogos = tabela_aux->jogos;
  tabela->tamanho = tabela_aux->tamanho;
  free(tabela_aux);
  return;
}

void adiciona_jogo_tabela(pTabela_jogos tabela, pJogo jogo)
{
  unsigned int i = gera_hash(obtem_nome_jogo(jogo), tabela->tamanho);
  while (tabela->jogos[i] != 0)
    i = (i + 1) % tabela->tamanho;

  tabela->jogos[i] = jogo;
  if ((tabela->num_jogos++) > (tabela->tamanho / 2))
  {
    expande_tabela_jogos(tabela);
  }
  else
  {
    
  }

  return;
}

pJogo procura_jogo_tabela(pTabela_jogos tabela, char *nome_jogo)
{
  int i = gera_hash(nome_jogo, tabela->tamanho);
  while (tabela->jogos[i] != 0)
    if (strcmp(tabela->jogos[i]->nome, nome_jogo) == 0)
  {
    return tabela->jogos[i];
  }
  else
  {
    i = (i + 1) % tabela->tamanho;
  }


  return 0;
}

pJogo remove_jogo_tabela(pTabela_jogos tabela_jogos, char *nome_jogo)
{
  int i;
  unsigned tamanho_tabela;
  pJogo aux;
  pJogo jogo_removido;
  tamanho_tabela = tabela_jogos->tamanho;
  i = gera_hash(nome_jogo, tamanho_tabela);
  while (tabela_jogos->jogos[i] != 0)
    if (strcmp(nome_jogo, obtem_nome_jogo(tabela_jogos->jogos[i])) == 0)
  {
    break;
  }
  else
  {
    i = (i + 1) % tamanho_tabela;
  }


  if (tabela_jogos->jogos[i] == 0)
  {
    return 0;
  }
  else
  {
    
  }

  jogo_removido = tabela_jogos->jogos[i];
  tabela_jogos->jogos[i] = 0;
  tabela_jogos->num_jogos--;
  for (i = (i + 1) % tamanho_tabela; tabela_jogos->jogos[i] != 0; i = (i + 1) % tamanho_tabela)
  {
    tabela_jogos->num_jogos--;
    aux = tabela_jogos->jogos[i];
    tabela_jogos->jogos[i] = 0;
    adiciona_jogo_tabela(tabela_jogos, aux);
  }

  return jogo_removido;
}

void destroi_tabela_jogos(pTabela_jogos tabela)
{
  free(tabela->jogos);
  free(tabela);
  return;
}

