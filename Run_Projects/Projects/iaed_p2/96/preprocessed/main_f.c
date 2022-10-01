/*File generated by PreProcessor.py*/


#include "main_f.h"


void A(bloco_hash_equipa *table_e, bloco_hash_equipa *lista_e, int NL)
{
  char nome_e[1043];
  equipa *e;
  for (int nome_e_index = 0; nome_e_index < 10; nome_e_index++)
  {
    nome_e[nome_e_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_e[10 - 1] = '\0';
  if (procura_equipa_hash(table_e, nome_e) != 0)
  {
    printf("%d Equipa existente.\n", NL);
  }
  else
  {
    e = malloc(sizeof(equipa));
    e->nome = malloc((sizeof(char)) * (strlen(nome_e) + 1));
    strcpy(e->nome, nome_e);
    e->vitorias = 0;
    guarda_lista_e(lista_e, e);
    guarda_equipa_hash(table_e, e);
  }

}

void a(bloco_hash_jogo *table_j, bloco_hash_equipa *table_e, bloco_hash_jogo *lista_ord_h, bloco_hash_jogo *lista_ord_t, int NL)
{
  char nome_j[1043];
  char equipa1[1043];
  char equipa2[1043];
  int score1;
  int score2;
  equipa *aux1;
  equipa *aux2;
  for (int nome_j_index = 0; nome_j_index < 10; nome_j_index++)
  {
    nome_j[nome_j_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_j[10 - 1] = '\0';
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
  aux1 = procura_equipa_hash(table_e, equipa1);
  aux2 = procura_equipa_hash(table_e, equipa2);
  if (procura_jogo_hash(table_j, nome_j) != 0)
  {
    printf("%d Jogo existente.\n", NL);
  }
  else
  {
    if ((aux1 == 0) || (aux2 == 0))
    {
      printf("%d Equipa inexistente.\n", NL);
    }
    else
    {
      jogo *j = malloc(sizeof(jogo));
      j->nome = malloc((sizeof(char)) * (strlen(nome_j) + 1));
      j->equipa1 = aux1;
      j->equipa2 = aux2;
      strcpy(j->nome, nome_j);
      j->score1 = score1;
      j->score2 = score2;
      if (score1 > score2)
      {
        j->equipa1->vitorias += 1;
      }
      else
      {
        if (score1 < score2)
        {
          j->equipa2->vitorias += 1;
        }
        else
        {
          
        }

      }

      guarda_jogo_hash(table_j, j);
      guarda_lista_ord(lista_ord_h, lista_ord_t, j);
    }

  }

}

void P(bloco_hash_equipa *table_e, int NL)
{
  char nome_e[1043];
  equipa *aux;
  for (int nome_e_index = 0; nome_e_index < 10; nome_e_index++)
  {
    nome_e[nome_e_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_e[10 - 1] = '\0';
  aux = procura_equipa_hash(table_e, nome_e);
  if (aux == 0)
  {
    printf("%d Equipa inexistente.\n", NL);
  }
  else
  {
    printf("%d %s %d\n", NL, aux->nome, aux->vitorias);
  }

}

void p(bloco_hash_jogo *table_j, int NL)
{
  char nome_j[1043];
  jogo *aux;
  for (int nome_j_index = 0; nome_j_index < 10; nome_j_index++)
  {
    nome_j[nome_j_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_j[10 - 1] = '\0';
  aux = procura_jogo_hash(table_j, nome_j);
  if (aux == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    printf("%d %s %s %s %d %d\n", NL, aux->nome, aux->equipa1->nome, aux->equipa2->nome, aux->score1, aux->score2);
  }

}

void s(bloco_hash_jogo *table_j, bloco_hash_equipa *table_e, int NL)
{
  char nome_j[1043];
  int n_score1;
  int n_score2;
  jogo *aux;
  for (int nome_j_index = 0; nome_j_index < 10; nome_j_index++)
  {
    nome_j[nome_j_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_j[10 - 1] = '\0';
  n_score1 = new_sym_var(sizeof(int) * 8);
  n_score2 = new_sym_var(sizeof(int) * 8);
  aux = procura_jogo_hash(table_j, nome_j);
  if (aux == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    equipa *aux_e1;
    equipa *aux_e2;
    aux_e1 = procura_equipa_hash(table_e, aux->equipa1->nome);
    aux_e2 = procura_equipa_hash(table_e, aux->equipa2->nome);
    if (aux->score1 > aux->score2)
    {
      aux_e1->vitorias--;
    }
    else
    {
      if (aux->score1 < aux->score2)
      {
        aux_e2->vitorias--;
      }
      else
      {
        
      }

    }

    if (n_score1 > n_score2)
    {
      aux_e1->vitorias++;
    }
    else
    {
      if (n_score1 < n_score2)
      {
        aux_e2->vitorias++;
      }
      else
      {
        
      }

    }

    aux->score1 = n_score1;
    aux->score2 = n_score2;
  }

}

void r(bloco_hash_jogo *table_j, bloco_hash_jogo *lista_ord_h, bloco_hash_jogo *lista_ord_t, int NL)
{
  char nome_j[1043];
  jogo *aux;
  for (int nome_j_index = 0; nome_j_index < 10; nome_j_index++)
  {
    nome_j[nome_j_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_j[10 - 1] = '\0';
  aux = procura_jogo_hash(table_j, nome_j);
  if (aux == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  if (aux->score1 > aux->score2)
  {
    aux->equipa1->vitorias--;
  }
  else
  {
    if (aux->score1 < aux->score2)
    {
      aux->equipa2->vitorias--;
    }
    else
    {
      
    }

  }

  apaga_lista_ord(lista_ord_h, lista_ord_t, nome_j);
  apaga_jogo_hash(table_j, nome_j);
}

void l(bloco_hash_jogo *head, int NL)
{
  bloco_hash_jogo aux;
  aux = *head;
  if (aux == 0)
  {
    return;
  }
  else
  {
    
  }

  while (aux != 0)
  {
    printf("%d %s %s %s %d %d\n", NL, aux->jogo->nome, aux->jogo->equipa1->nome, aux->jogo->equipa2->nome, aux->jogo->score1, aux->jogo->score2);
    aux = aux->next;
  }

}

void g(bloco_hash_equipa *lista_e, int NL)
{
  int max_v = 0;
  bloco_hash_equipa *lista_e_v;
  bloco_hash_equipa aux1;
  bloco_hash_equipa aux2;
  bloco_hash_equipa aux3;
  aux1 = lista_e[0];
  if (aux1 == 0)
  {
    return;
  }
  else
  {
    
  }

  lista_e_v = malloc(sizeof(bloco_hash_equipa));
  lista_e_v[0] = 0;
  while (aux1 != 0)
  {
    if (aux1->equipa->vitorias > max_v)
    {
      max_v = aux1->equipa->vitorias;
    }
    else
    {
      
    }

    aux1 = aux1->next;
  }

  aux1 = lista_e[0];
  while (aux1 != 0)
  {
    if (aux1->equipa->vitorias == max_v)
    {
      guarda_ord_alfabetica(lista_e_v, aux1->equipa);
    }
    else
    {
      
    }

    aux1 = aux1->next;
  }

  printf("%d Melhores %d\n", NL, max_v);
  aux2 = lista_e_v[0];
  while (aux2 != 0)
  {
    printf("%d * %s\n", NL, aux2->equipa->nome);
    aux2 = aux2->next;
  }

  while ((*lista_e_v) != 0)
  {
    aux3 = (*lista_e_v)->next;
    free(*lista_e_v);
    *lista_e_v = aux3;
  }

  free(lista_e_v);
}

void x(bloco_hash_equipa *h_e, bloco_hash_equipa *l_e, bloco_hash_jogo *h_j, bloco_hash_jogo *l_j_h, bloco_hash_jogo *l_j_t)
{
  int pos_e;
  int pos_j;
  bloco_hash_equipa aux_e;
  bloco_hash_jogo aux_j;
  while ((*l_e) != 0)
  {
    aux_e = (*l_e)->next;
    free(*l_e);
    *l_e = aux_e;
  }

  free(l_e);
  while ((*l_j_h) != 0)
  {
    aux_j = (*l_j_h)->next;
    free(*l_j_h);
    *l_j_h = aux_j;
  }

  free(l_j_h);
  free(l_j_t);
  for (pos_e = 0; pos_e < 149; pos_e++)
  {
    while (h_e[pos_e] != 0)
    {
      aux_e = h_e[pos_e]->next;
      free(h_e[pos_e]->equipa->nome);
      free(h_e[pos_e]->equipa);
      free(h_e[pos_e]);
      h_e[pos_e] = aux_e;
    }

  }

  free(h_e);
  for (pos_j = 0; pos_j < 149; pos_j++)
  {
    while (h_j[pos_j] != 0)
    {
      aux_j = h_j[pos_j]->next;
      free(h_j[pos_j]->jogo->nome);
      free(h_j[pos_j]->jogo);
      free(h_j[pos_j]);
      h_j[pos_j] = aux_j;
    }

  }

  free(h_j);
}
