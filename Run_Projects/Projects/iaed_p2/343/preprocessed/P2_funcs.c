/*File generated by PreProcessor.py*/


#include "funcs.h"


void sub_score(jg *jogo)
{
  if (jogo->scr1 > jogo->scr2)
  {
    jogo->eq1->vitorias--;
  }
  else
  {
    if (jogo->scr1 < jogo->scr2)
    {
      jogo->eq2->vitorias--;
    }
    else
    {
      
    }

  }

}

void acommand(int nl, node_jg *table_jg, node_eq *table_eq, link *lista)
{
  char nome[1024];
  char eq1[1024];
  char eq2[1024];
  int sc1;
  int sc2;
  int i;
  jg *njogo;
  eq *equipa1;
  eq *equipa2;
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
  sc1 = new_sym_var(sizeof(int) * 8);
  sc2 = new_sym_var(sizeof(int) * 8);
  i = f_hash(nome);
  equipa1 = search_eq(table_eq[f_hash(eq1)], eq1);
  equipa2 = search_eq(table_eq[f_hash(eq2)], eq2);
  if (search_jg(table_jg[i], nome) != 0)
  {
    printf("%d Jogo existente.\n", nl);
  }
  else
  {
    if ((equipa1 == 0) || (equipa2 == 0))
    {
      printf("%d Equipa inexistente.\n", nl);
    }
    else
    {
      {
        njogo = malloc(sizeof(jg));
        njogo->nome = malloc((sizeof(char)) * (strlen(nome) + 1));
        strcpy(njogo->nome, nome);
        njogo->eq1 = equipa1;
        njogo->eq2 = equipa2;
        njogo->scr1 = sc1;
        njogo->scr2 = sc2;
        table_jg[i] = push_jg(table_jg[i], njogo);
        if (sc1 > sc2)
        {
          equipa1->vitorias++;
        }
        else
        {
          if (sc1 < sc2)
          {
            equipa2->vitorias++;
          }
          else
          {
            
          }

        }

        push_lista(lista, njogo);
      }
    }

  }

}

void Acommand(int nl, node_eq *table_eq, node_eq *lista_eq)
{
  char dest[1024];
  int i;
  eq *nequipa;
  for (int dest_index = 0; dest_index < 10; dest_index++)
  {
    dest[dest_index] = new_sym_var(sizeof(char) * 8);
  }

  dest[10 - 1] = '\0';
  i = f_hash(dest);
  if (search_eq(table_eq[i], dest) != 0)
  {
    printf("%d Equipa existente.\n", nl);
  }
  else
  {
    {
      nequipa = malloc(sizeof(eq));
      nequipa->des = malloc((sizeof(char)) * (strlen(dest) + 1));
      strcpy(nequipa->des, dest);
      nequipa->vitorias = 0;
      table_eq[i] = push_eq(table_eq[i], nequipa);
      lista_eq[0] = push_eq(lista_eq[0], nequipa);
    }
  }

}

void gcommand(int nl, node_eq *lista_eq)
{
  int max = 0;
  int cont = 0;
  int i = 0;
  node_eq atual;
  eq **lista;
  getchar();
  if (lista_eq[0] != 0)
  {
    {
      for (atual = lista_eq[0]; atual != 0; atual = atual->next)
      {
        if (max < atual->equipa->vitorias)
        {
          {
            max = atual->equipa->vitorias;
            cont = 1;
          }
        }
        else
        {
          if (max == atual->equipa->vitorias)
          {
            cont++;
          }
          else
          {
            
          }

        }

      }

      lista = malloc((sizeof(eq *)) * cont);
      for (atual = lista_eq[0]; atual != 0; atual = atual->next)
      {
        if (max == atual->equipa->vitorias)
        {
          lista[i++] = atual->equipa;
        }
        else
        {
          
        }

      }

      quicksort(lista, 0, cont - 1);
      printf("%d Melhores %d\n", nl, max);
      for (i = 0; i < cont; i++)
        printf("%d * %s\n", nl, lista[i]->des);

      free(lista);
    }
  }
  else
  {
    
  }

}

void lcommand(int nl, link *lista)
{
  node_jg temp;
  getchar();
  for (temp = lista->head; temp != 0; temp = temp->next)
    printf("%d %s %s %s %d %d\n", nl, temp->jogo->nome, temp->jogo->eq1->des, temp->jogo->eq2->des, temp->jogo->scr1, temp->jogo->scr2);

}

void pcommand(int nl, node_jg *table_jg)
{
  char nome[1024];
  jg *jogo;
  getchar();
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  jogo = search_jg(table_jg[f_hash(nome)], nome);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
  }
  else
  {
    printf("%d %s %s %s %d %d\n", nl, jogo->nome, jogo->eq1->des, jogo->eq2->des, jogo->scr1, jogo->scr2);
  }

}

void Pcommand(int nl, node_eq *table_eq)
{
  char dest[1024];
  eq *ver;
  for (int dest_index = 0; dest_index < 10; dest_index++)
  {
    dest[dest_index] = new_sym_var(sizeof(char) * 8);
  }

  dest[10 - 1] = '\0';
  ver = search_eq(table_eq[f_hash(dest)], dest);
  if (ver != 0)
  {
    printf("%d %s %d\n", nl, ver->des, ver->vitorias);
  }
  else
  {
    printf("%d Equipa inexistente.\n", nl);
  }

}

void rcommand(int nl, node_jg *table_jg, link *lista)
{
  char nome[1024];
  int i;
  jg *jogo;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  i = f_hash(nome);
  jogo = search_jg(table_jg[i], nome);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
  }
  else
  {
    {
      sub_score(jogo);
      remove_lista(lista, jogo);
      table_jg[i] = remove_jg(table_jg[i], jogo);
      free(jogo->nome);
      free(jogo);
    }
  }

}

void scommand(int nl, node_jg *table_jg)
{
  char nome[1024];
  jg *jogo;
  int sc1;
  int sc2;
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  sc1 = new_sym_var(sizeof(int) * 8);
  sc2 = new_sym_var(sizeof(int) * 8);
  jogo = search_jg(table_jg[f_hash(nome)], nome);
  if (jogo == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
  }
  else
  {
    {
      sub_score(jogo);
      jogo->scr1 = sc1;
      jogo->scr2 = sc2;
      if (sc1 > sc2)
      {
        jogo->eq1->vitorias++;
      }
      else
      {
        if (sc1 < sc2)
        {
          jogo->eq2->vitorias++;
        }
        else
        {
          
        }

      }

    }
  }

}

void xcommand(node_eq *table_eq, node_eq *lista_eq, node_jg *table_jg, link *lista)
{
  int i;
  node_eq eq;
  node_eq eq_temp;
  node_jg jg;
  node_jg jg_temp;
  for (i = 0; i < 157; i++)
  {
    if (table_eq[i] != 0)
    {
      {
        for (eq = table_eq[i]; eq != 0; eq = eq_temp)
        {
          eq_temp = eq->next;
          free(eq->equipa->des);
          free(eq->equipa);
          free(eq);
        }

      }
    }
    else
    {
      
    }

    if (table_jg[i] != 0)
    {
      {
        for (jg = table_jg[i]; jg != 0; jg = jg_temp)
        {
          jg_temp = jg->next;
          free(jg->jogo->nome);
          free(jg->jogo);
          free(jg);
        }

      }
    }
    else
    {
      
    }

  }

  free(table_eq);
  free(table_jg);
  for (eq = lista_eq[0]; eq != 0; eq = eq_temp)
  {
    eq_temp = eq->next;
    free(eq);
  }

  free(lista_eq);
  for (jg = lista->head; jg != 0; jg = jg_temp)
  {
    jg_temp = jg->next;
    free(jg);
  }

  free(lista);
}

