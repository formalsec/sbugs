/*File generated by PreProcessor.py*/


#include "lista_jogos.h"


lista *inicializa_lista_jogos()
{
  lista *lista_jogos = (lista *) malloc(sizeof(lista));
  lista_jogos->cabeca = 0;
  lista_jogos->ultimo = 0;
  return lista_jogos;
}

void adiciona_jogo_lista(lista *lista_jogos, pJogo jogo)
{
  link_jogo link_novo = (link_jogo) malloc(sizeof(struct node_jogo));
  link_novo->jogo = jogo;
  link_novo->next = 0;
  if (lista_jogos->cabeca == 0)
  {
    {
      lista_jogos->cabeca = link_novo;
      lista_jogos->ultimo = link_novo;
    }
  }
  else
  {
    {
      lista_jogos->ultimo->next = link_novo;
      lista_jogos->ultimo = link_novo;
    }
  }

}

pJogo remove_jogo_lista(lista *lista_jogos, char *nome)
{
  pJogo jogo;
  link_jogo aux;
  link_jogo iterador = lista_jogos->cabeca;
  if (strcmp(obtem_nome_jogo(iterador->jogo), nome) == 0)
  {
    {
      lista_jogos->cabeca = iterador->next;
      jogo = iterador->jogo;
      if (lista_jogos->ultimo->jogo == jogo)
      {
        lista_jogos->ultimo = lista_jogos->cabeca;
      }
      else
      {
        
      }

      free(iterador);
    }
  }
  else
  {
    {
      for (aux = iterador->next; iterador->next != 0; iterador = aux, aux = iterador->next)
      {
        if (strcmp(obtem_nome_jogo(aux->jogo), nome) == 0)
        {
          {
            if (lista_jogos->ultimo == aux)
            {
              lista_jogos->ultimo = iterador;
            }
            else
            {
              
            }

            jogo = aux->jogo;
            iterador->next = aux->next;
            free(aux);
            break;
          }
        }
        else
        {
          
        }

      }

    }
  }

  return jogo;
}

void print_lista_jogos(lista *lista_jogos, unsigned int Num_Linha)
{
  link_jogo iterador;
  for (iterador = lista_jogos->cabeca; iterador != 0; iterador = iterador->next)
  {
    print_jogo(iterador->jogo, Num_Linha);
  }

  return;
}

void destroi_lista_jogos(lista *lista_jogos)
{
  link_jogo iterador;
  link_jogo aux;
  for (iterador = lista_jogos->cabeca; iterador != 0; iterador = aux)
  {
    aux = iterador->next;
    free_jogo(iterador->jogo);
    free(iterador);
  }

  free(lista_jogos);
  return;
}

