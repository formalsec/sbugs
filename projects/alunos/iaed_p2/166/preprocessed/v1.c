#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "listadupJOGO.h"
#include "listadupEQUIPA.h"


void inic_ht_jogos(list_jogo *ht_jogos[10007])
{
  int i = -1;
  while ((++i) < 10007)
    ht_jogos[i] = mk_list_jogo();

}

void inic_ht_equipas(list_equipa *ht_equipas[10007])
{
  int i = -1;
  while ((++i) < 10007)
    ht_equipas[i] = mk_list_equipa();

}

int hash(char *str)
{
  int soma = 0;
  int valorletra;
  while ((*str) != '\0')
  {
    valorletra = *str;
    soma += valorletra;
    ++str;
  }

  return soma % 10007;
}

Jogo *procura_jogo_aux(char *nome, node_jogo *l_head)
{
  node_jogo *copiaL;
  if (l_head == 0)
  {
    return 0;
  }
  else
  {
    if (strcmp(l_head->jogo->nome, nome) == 0)
    {
      return l_head->jogo;
    }
    else
    {
      copiaL = l_head->next;
      return procura_jogo_aux(nome, copiaL);
    }

  }

}

Jogo *procura_jogo(char *nome, list_jogo *ht_jogos[10007])
{
  int hashVal = hash(nome);
  return procura_jogo_aux(nome, ht_jogos[hashVal]->head);
}

Equipa *procura_equipa_aux(char *nome, node_equipa *l_head)
{
  node_equipa *copiaL;
  if (l_head == 0)
  {
    return 0;
  }
  else
  {
    if (strcmp(l_head->equipa->nome, nome) == 0)
    {
      return l_head->equipa;
    }
    else
    {
      copiaL = l_head->next;
      return procura_equipa_aux(nome, copiaL);
    }

  }

}

Equipa *procura_equipa(char *nome, list_equipa *ht_equipas[10007])
{
  int hashVal = hash(nome);
  return procura_equipa_aux(nome, ht_equipas[hashVal]->head);
}

void func_p(list_jogo *ht_jogos[10007], int nl)
{
  char nome[1024];
  Jogo *j;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  j = procura_jogo(nome, ht_jogos);
  if (j == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
  }
  else
  {
    printf("%d %s %s %s %d %d\n", nl, j->nome, j->equipa1, j->equipa2, j->score[0], j->score[1]);
  }

}

void func_a(list_jogo *ht_jogos[10007], list_equipa *ht_equipas[10007], list_jogo *ordem_jogos, int nl)
{
  char nome[1024];
  char eq1[1024];
  char eq2[1024];
  int score[2];
  int hashVal;
  Jogo *novoJogo;
  Equipa *endEquipa1;
  Equipa *endEquipa2;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  for (int eq1_index = 0; eq1_index < 10; eq1_index++)
  {
    eq1[eq1_index] = new_sym_var(sizeof(char) * 8);
  }

  eq1[10 - 1] = '\0';
  for (int eq2_index = 0; eq2_index < 10; eq2_index++)
  {
    eq2[eq2_index] = new_sym_var(sizeof(char) * 8);
  }

  eq2[10 - 1] = '\0';
  score[0] = new_sym_var(sizeof(int) * 8);
  score[1] = new_sym_var(sizeof(int) * 8);
  if (procura_jogo(nome, ht_jogos) != 0)
  {
    printf("%d Jogo existente.\n", nl);
    return;
  }
  else
  {
    
  }

  endEquipa1 = procura_equipa(eq1, ht_equipas);
  endEquipa2 = procura_equipa(eq2, ht_equipas);
  if ((endEquipa1 == 0) || (endEquipa2 == 0))
  {
    printf("%d Equipa inexistente.\n", nl);
    return;
  }
  else
  {
    
  }

  novoJogo = mk_jogo(nome, eq1, eq2, score);
  hashVal = hash(nome);
  if (score[0] > score[1])
  {
    endEquipa1->vitorias += 1;
  }
  else
  {
    if (score[1] > score[0])
    {
      endEquipa2->vitorias += 1;
    }
    else
    {
      
    }

  }

  add_last_jogo(ht_jogos[hashVal], novoJogo);
  add_last_jogo(ordem_jogos, novoJogo);
}

void func_A(list_equipa *ht_equipas[10007], int nl)
{
  char nome[1024];
  Equipa *e;
  int hashVal;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  e = procura_equipa(nome, ht_equipas);
  if (e != 0)
  {
    printf("%d Equipa existente.\n", nl);
    return;
  }
  else
  {
    
  }

  hashVal = hash(nome);
  e = mk_equipa(nome);
  add_last_equipa(ht_equipas[hashVal], e);
}

void func_P(list_equipa *ht_equipas[10007], int nl)
{
  char nome[1024];
  Equipa *e;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  e = procura_equipa(nome, ht_equipas);
  if (e == 0)
  {
    printf("%d Equipa inexistente.\n", nl);
    return;
  }
  else
  {
    
  }

  printf("%d %s %d\n", nl, e->nome, e->vitorias);
}

void func_l(list_jogo *ordem_jogos, int nl)
{
  node_jogo *nodeAtual = ordem_jogos->head;
  while (nodeAtual != 0)
  {
    printf("%d %s %s %s %d %d\n", nl, nodeAtual->jogo->nome, nodeAtual->jogo->equipa1, nodeAtual->jogo->equipa2, nodeAtual->jogo->score[0], nodeAtual->jogo->score[1]);
    nodeAtual = nodeAtual->next;
  }

}

void func_s(list_jogo *ht_jogos[10007], list_equipa *ht_equipas[10007], int nl)
{
  char nome[1024];
  int score0;
  int score1;
  Jogo *jogo;
  Equipa *equipa1;
  Equipa *equipa2;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  score0 = new_sym_var(sizeof(int) * 8);
  score1 = new_sym_var(sizeof(int) * 8);
  jogo = procura_jogo(nome, ht_jogos);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
    return;
  }
  else
  {
    
  }

  equipa1 = procura_equipa(jogo->equipa1, ht_equipas);
  equipa2 = procura_equipa(jogo->equipa2, ht_equipas);
  if (jogo->score[0] > jogo->score[1])
  {
    if (score0 <= score1)
    {
      equipa1->vitorias--;
    }
    else
    {
      
    }

  }
  else
  {
    if (score0 > score1)
    {
      equipa1->vitorias++;
    }
    else
    {
      
    }

  }

  if (jogo->score[1] > jogo->score[0])
  {
    if (score1 <= score0)
    {
      equipa2->vitorias--;
    }
    else
    {
      
    }

  }
  else
  {
    if (score1 > score0)
    {
      equipa2->vitorias++;
    }
    else
    {
      
    }

  }

  jogo->score[0] = score0;
  jogo->score[1] = score1;
}

void func_r(list_jogo *ht_jogos[10007], list_equipa *ht_equipas[10007], list_jogo *ordem_jogos, int nl)
{
  char nome[1024];
  int hashVal;
  Jogo *j;
  Equipa *e;
  node_jogo *membro_ordem;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  j = procura_jogo(nome, ht_jogos);
  if (j == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
    return;
  }
  else
  {
    
  }

  if (j->score[0] > j->score[1])
  {
    e = procura_equipa(j->equipa1, ht_equipas);
    e->vitorias--;
  }
  else
  {
    
  }

  if (j->score[0] < j->score[1])
  {
    e = procura_equipa(j->equipa2, ht_equipas);
    e->vitorias--;
  }
  else
  {
    
  }

  hashVal = hash(nome);
  remove_jogo(ht_jogos[hashVal], j);
  membro_ordem = ordem_jogos->head;
  while (membro_ordem->jogo != j)
    membro_ordem = membro_ordem->next;

  if (ordem_jogos->head == ordem_jogos->last)
  {
    ordem_jogos->head = 0;
    ordem_jogos->last = 0;
  }
  else
  {
    
  }

  if (membro_ordem == ordem_jogos->head)
  {
    ordem_jogos->head = membro_ordem->next;
  }
  else
  {
    
  }

  if (membro_ordem->previous != 0)
  {
    membro_ordem->previous->next = membro_ordem->next;
  }
  else
  {
    
  }

  if (membro_ordem == ordem_jogos->last)
  {
    ordem_jogos->last = membro_ordem->previous;
  }
  else
  {
    
  }

  if (membro_ordem->next != 0)
  {
    membro_ordem->next->previous = membro_ordem->previous;
  }
  else
  {
    
  }

  free(membro_ordem);
}

int compara(const void *a, const void *b)
{
  Equipa *e1 = *((Equipa **) a);
  Equipa *e2 = *((Equipa **) b);
  return strcmp(e1->nome, e2->nome);
}

void func_g(list_equipa *ht_equipas[10007], int nl)
{
  int max = 0;
  int cont_max = 0;
  int i = -1;
  int poslivre = 0;
  list_equipa *lista;
  node_equipa *membro_lista;
  Equipa **v;
  while ((++i) < 10007)
  {
    lista = ht_equipas[i];
    membro_lista = lista->head;
    while (membro_lista != 0)
    {
      if (membro_lista->equipa->vitorias == max)
      {
        cont_max++;
      }
      else
      {
        
      }

      if (membro_lista->equipa->vitorias > max)
      {
        max = membro_lista->equipa->vitorias;
        cont_max = 1;
      }
      else
      {
        
      }

      membro_lista = membro_lista->next;
    }

  }

  if (cont_max == 0)
  {
    return;
  }
  else
  {
    
  }

  v = malloc(cont_max * (sizeof(Equipa *)));
  i = -1;
  while ((++i) < 10007)
  {
    lista = ht_equipas[i];
    membro_lista = lista->head;
    while (membro_lista != 0)
    {
      if (membro_lista->equipa->vitorias == max)
      {
        v[poslivre] = membro_lista->equipa;
        ++poslivre;
      }
      else
      {
        
      }

      membro_lista = membro_lista->next;
    }

  }

  qsort((void *) v, cont_max, sizeof(Equipa *), compara);
  i = -1;
  printf("%d Melhores %d\n", nl, max);
  while ((++i) < cont_max)
    printf("%d * %s\n", nl, v[i]->nome);

  free(v);
}

int main()
{
  char c;
  int nl = 1;
  int i = -1;
  list_jogo *ht_jogos[10007];
  list_equipa *ht_equipas[10007];
  list_jogo *ordem_jogos = mk_list_jogo();
  node_jogo *ordem_jogos_last;
  inic_ht_equipas(ht_equipas);
  inic_ht_jogos(ht_jogos);
  while ((c = getchar()) != 'x')
  {
    switch (c)
    {
      case 'a':
        func_a(ht_jogos, ht_equipas, ordem_jogos, nl);
        nl++;
        break;

      case 'l':
        func_l(ordem_jogos, nl);
        nl++;
        break;

      case 'p':
        func_p(ht_jogos, nl);
        nl++;
        break;

      case 'r':
        func_r(ht_jogos, ht_equipas, ordem_jogos, nl);
        nl++;
        break;

      case 's':
        func_s(ht_jogos, ht_equipas, nl);
        nl++;
        break;

      case 'A':
        func_A(ht_equipas, nl);
        nl++;
        break;

      case 'P':
        func_P(ht_equipas, nl);
        nl++;
        break;

      case 'g':
        func_g(ht_equipas, nl);
        nl++;

      default:
        break;

    }

  }

  while ((++i) < 10007)
  {
    if (ht_equipas[i] != 0)
    {
      free_list_equipa(ht_equipas[i]);
    }
    else
    {
      
    }

    if (ht_jogos[i] != 0)
    {
      free_list_jogo(ht_jogos[i]);
    }
    else
    {
      
    }

  }

  ordem_jogos_last = ordem_jogos->last;
  if (ordem_jogos_last != 0)
  {
    while (ordem_jogos_last != ordem_jogos->head)
    {
      ordem_jogos_last = ordem_jogos_last->previous;
      free(ordem_jogos_last->next);
    }

    free(ordem_jogos_last);
  }
  else
  {
    
  }

  free(ordem_jogos);
  return 0;
}

