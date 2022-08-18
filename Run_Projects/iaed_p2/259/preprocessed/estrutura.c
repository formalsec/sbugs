/*File generated by PreProcessor.py*/


#include "estrutura.h"


void inic_hash_j(jogo *aux[])
{
  int i;
  for (i = 0; i < 8059; i++)
  {
    aux[i] = 0;
  }

}

void free_no(jogo *aux)
{
  free(aux->nome);
  free(aux);
}

void free_hash_j(jogo *heads[])
{
  jogo *aux;
  int i;
  for (i = 0; i < 8059; i++)
  {
    while (heads[i])
    {
      aux = heads[i]->next;
      free_no(heads[i]);
      heads[i] = aux;
    }

  }

}

int hash_s(char *nome)
{
  int h;
  int a = 31245;
  int b = 27183;
  for (h = 0; (*nome) != '\0'; nome++, a = (a * b) % (8059 - 1))
  {
    h = ((a * h) + (*nome)) % 8059;
  }

  return h;
}

jogo *adi_no(jogo *heads[], char nome[], equipa *equipa1, equipa *equipa2, int golos1, int golos2)
{
  int i = hash_s(nome);
  jogo *aux = malloc(sizeof(jogo));
  aux->next = heads[i];
  aux->nome = malloc((sizeof(char)) * (strlen(nome) + 1));
  strcpy(aux->nome, nome);
  aux->equipa1 = equipa1;
  aux->equipa2 = equipa2;
  aux->golos1 = golos1;
  aux->golos2 = golos2;
  heads[i] = aux;
  return aux;
}

jogo *procura_j(jogo *heads[], char *nome)
{
  int i = hash_s(nome);
  jogo *aux;
  for (aux = heads[i]; aux != 0; aux = aux->next)
  {
    if (!strcmp(aux->nome, nome))
    {
      {
        return aux;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

void rem_no(jogo *heads[], char *nome)
{
  int i = hash_s(nome);
  jogo *aux;
  jogo *aux_ant;
  for (aux = heads[i], aux_ant = 0; aux != 0; aux_ant = aux, aux = aux->next)
  {
    if (!strcmp(aux->nome, nome))
    {
      {
        if (aux == heads[i])
        {
          heads[i] = aux->next;
        }
        else
        {
          aux_ant->next = aux->next;
        }

        free_no(aux);
        break;
      }
    }
    else
    {
      
    }

  }

}

void inic_hash_e(equipa *aux[])
{
  int i;
  for (i = 0; i < 8059; i++)
  {
    aux[i] = 0;
  }

}

void free_eq(equipa *aux)
{
  free(aux->nome);
  free(aux);
}

void free_hash_e(equipa *heads[])
{
  equipa *aux;
  int i;
  for (i = 0; i < 8059; i++)
  {
    while (heads[i])
    {
      aux = heads[i]->next;
      free_eq(heads[i]);
      heads[i] = aux;
    }

  }

}

void adi_eq(equipa *heads[], char nome[])
{
  int i = hash_s(nome);
  equipa *aux = malloc(sizeof(equipa));
  aux->next = heads[i];
  aux->nome = malloc((sizeof(char)) * (strlen(nome) + 1));
  strcpy(aux->nome, nome);
  aux->vitoria = 0;
  heads[i] = aux;
}

equipa *procura_e(equipa *heads[], char *nome)
{
  int i = hash_s(nome);
  equipa *aux;
  for (aux = heads[i]; aux != 0; aux = aux->next)
  {
    if (!strcmp(aux->nome, nome))
    {
      {
        return aux;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

void rem_eq(equipa *heads[], char *nome)
{
  int i = hash_s(nome);
  equipa *aux;
  equipa *aux_ant;
  for (aux = heads[i], aux_ant = 0; aux != 0; aux_ant = aux, aux = aux->next)
  {
    if (!strcmp(aux->nome, nome))
    {
      {
        if (aux == heads[i])
        {
          heads[i] = aux->next;
        }
        else
        {
          aux_ant->next = aux->next;
        }

        free_eq(aux);
        break;
      }
    }
    else
    {
      
    }

  }

}

lista_jogo *inic_lista()
{
  lista_jogo *lista = malloc(sizeof(lista_jogo));
  lista->head = (lista->last = 0);
  return lista;
}

void free_lista(lista_jogo *lista)
{
  jogo_l *aux;
  while (lista->head)
  {
    aux = lista->head->next;
    free(lista->head);
    lista->head = aux;
  }

  free(lista);
}

void adiciona_fim(lista_jogo *lista, jogo *jogo)
{
  jogo_l *aux = malloc(sizeof(jogo_l));
  aux->prev = lista->last;
  aux->next = 0;
  aux->jogo_lista = jogo;
  if (lista->last)
  {
    lista->last->next = aux;
  }
  else
  {
    {
      lista->head = aux;
    }
  }

  lista->last = aux;
}

jogo *elimina_jo(lista_jogo *lista, char *nome)
{
  jogo_l *aux;
  jogo *aux_ret;
  for (aux = lista->head; aux != 0; aux = aux->next)
  {
    if (!strcmp(aux->jogo_lista->nome, nome))
    {
      {
        if (aux->prev == 0)
        {
          lista->head = aux->next;
        }
        else
        {
          aux->prev->next = aux->next;
        }

        if (aux->next == 0)
        {
          lista->last = aux->prev;
        }
        else
        {
          aux->next->prev = aux->prev;
        }

        aux_ret = aux->jogo_lista;
        free(aux);
        return aux_ret;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

lista_equipa *inic_lista_e()
{
  lista_equipa *lista = malloc(sizeof(lista_equipa));
  lista->head = (lista->last = 0);
  return lista;
}

void free_lista_e(lista_equipa *lista)
{
  equipa_l *aux;
  while (lista->head)
  {
    aux = lista->head->next;
    free(lista->head);
    lista->head = aux;
  }

  free(lista);
}

int adiciona_lex(lista_equipa *lista, equipa *equipa)
{
  equipa_l *aux = malloc(sizeof(equipa_l));
  equipa_l *aux_comp;
  aux->equipa_lista = equipa;
  if ((!lista->head) || (strcmp(equipa->nome, lista->last->equipa_lista->nome) > 0))
  {
    {
      aux->prev = lista->last;
      aux->next = 0;
      if (lista->last)
      {
        lista->last->next = aux;
      }
      else
      {
        lista->head = aux;
      }

      lista->last = aux;
      return 0;
    }
  }
  else
  {
    
  }

  for (aux_comp = lista->head; aux_comp; aux_comp = aux_comp->next)
  {
    if (strcmp(equipa->nome, aux_comp->equipa_lista->nome) < 0)
    {
      {
        aux->next = aux_comp;
        if (lista->head == aux_comp)
        {
          {
            lista->head = aux;
            aux->prev = 0;
          }
        }
        else
        {
          {
            aux->prev = aux_comp->prev;
            aux_comp->prev->next = aux;
          }
        }

        aux_comp->prev = aux;
        return 0;
      }
    }
    else
    {
      
    }

  }

  return 1;
}

