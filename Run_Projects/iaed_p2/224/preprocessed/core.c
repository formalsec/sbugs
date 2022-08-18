/*File generated by PreProcessor.py*/


#include "core.h"


char SeparaInput(char input[3096], char input_separado[5][1024])
{
  int a = 0;
  int i = 0;
  char *token = 0;
  char comando = '\0';
  token = strtok(input, "\n");
  token = strtok(token, " ");
  comando = *token;
  token = strtok(0, ":");
  for (a = 0; a < 5; a++)
    strcpy(input_separado[a], "\0");

  while (token != 0)
  {
    strcpy(input_separado[i], token);
    token = strtok(0, ":");
    i++;
  }

  return comando;
}

Lista *CriaLista()
{
  Lista *nova_lista = (Lista *) malloc(sizeof(Lista));
  nova_lista->cabeca = 0;
  nova_lista->ultimo = 0;
  return nova_lista;
}

Node **CriaHashTable()
{
  int i;
  Node **Hash_Table;
  Hash_Table = (Node **) malloc(1063 * (sizeof(Node *)));
  for (i = 0; i < 1063; i++)
    Hash_Table[i] = 0;

  return Hash_Table;
}

Node *CriaNode(void *tipo_node)
{
  Node *node = (Node *) malloc(sizeof(Node));
  node->drt = 0;
  node->esq = 0;
  node->tipo_node = tipo_node;
  return node;
}

int GeraHash(char *str)
{
  int i;
  int valor_ascii = 0;
  for (i = 0; str[i] != '\0'; i++)
    valor_ascii += str[i];

  return valor_ascii % 1063;
}

void InsereNaHashTable(Node **hash_table, Node *node, int tipo)
{
  int i = 0;
  Node *atual;
  i = GeraHash((tipo == 0) ? (((Jogo *) node->tipo_node)->nome) : (((Equipa *) node->tipo_node)->nome));
  if (hash_table[i])
  {
    {
      atual = hash_table[i];
      while (atual->drt)
        atual = atual->drt;

      node->esq = atual;
      atual->drt = node;
    }
  }
  else
  {
    hash_table[i] = node;
  }

}

void *ProcuraNaHashTable(char *nome, Node **hash_table, int tipo)
{
  int v = GeraHash(nome);
  Node *node = hash_table[v];
  while (node)
  {
    if (!strcmp((tipo == 0) ? (((Jogo *) node->tipo_node)->nome) : (((Equipa *) node->tipo_node)->nome), nome))
    {
      {
        return node->tipo_node;
      }
    }
    else
    {
      
    }

    node = node->drt;
  }

  return 0;
}

void InsereNaLista(Lista *lista, void *el, int tipo)
{
  if (!lista->cabeca)
  {
    {
      lista->cabeca = el;
      lista->ultimo = el;
    }
  }
  else
  {
    {
      if (tipo == 0)
      {
        {
          ((Jogo *) el)->esq = lista->ultimo;
          ((Jogo *) lista->ultimo)->drt = el;
        }
      }
      else
      {
        if (tipo == 1)
        {
          {
            ((Equipa *) el)->esq = lista->ultimo;
            ((Equipa *) lista->ultimo)->drt = el;
          }
        }
        else
        {
          
        }

      }

      lista->ultimo = el;
    }
  }

}

void *DestroiJogo(void *jogo)
{
  void *drt = ((Jogo *) jogo)->drt;
  free(((Jogo *) jogo)->nome);
  free(((Jogo *) jogo)->equipaX);
  free(((Jogo *) jogo)->equipaY);
  free(jogo);
  return drt;
}

void *DestroiEquipa(void *equipa)
{
  void *drt = ((Equipa *) equipa)->drt;
  free(((Equipa *) equipa)->nome);
  free(equipa);
  return drt;
}

void LimpaElemento(char *nome, Node **hash_table, Lista *lista, void *(*LimpaEl)(void *), int sel)
{
  int v = 0;
  Node *node = 0;
  v = GeraHash(nome);
  if (hash_table[v])
  {
    {
      node = hash_table[v];
      while (strcmp((sel == 0) ? (((Jogo *) node->tipo_node)->nome) : (((Equipa *) node->tipo_node)->nome), nome))
      {
        node = node->drt;
        if (!node)
        {
          return;
        }
        else
        {
          
        }

      }

      if (sel == 0)
      {
        {
          if (((Jogo *) node->tipo_node)->drt && ((Jogo *) node->tipo_node)->esq)
          {
            {
              ((Jogo *) node->tipo_node)->esq->drt = ((Jogo *) node->tipo_node)->drt;
              ((Jogo *) node->tipo_node)->drt->esq = ((Jogo *) node->tipo_node)->esq;
            }
          }
          else
          {
            if (((Jogo *) node->tipo_node)->esq)
            {
              {
                ((Jogo *) node->tipo_node)->esq->drt = 0;
                lista->ultimo = ((Jogo *) node->tipo_node)->esq;
              }
            }
            else
            {
              if (((Jogo *) node->tipo_node)->drt)
              {
                {
                  ((Jogo *) node->tipo_node)->drt->esq = 0;
                  lista->cabeca = ((Jogo *) node->tipo_node)->drt;
                }
              }
              else
              {
                {
                  lista->cabeca = 0;
                  lista->ultimo = 0;
                }
              }

            }

          }

        }
      }
      else
      {
        if (sel == 1)
        {
          {
            if (((Equipa *) node->tipo_node)->drt && ((Equipa *) node->tipo_node)->esq)
            {
              {
                ((Equipa *) node->tipo_node)->esq->drt = ((Equipa *) node->tipo_node)->drt;
                ((Equipa *) node->tipo_node)->drt->esq = ((Equipa *) node->tipo_node)->esq;
              }
            }
            else
            {
              if (((Equipa *) node->tipo_node)->esq)
              {
                {
                  ((Equipa *) node->tipo_node)->esq->drt = 0;
                  lista->ultimo = ((Equipa *) node->tipo_node)->esq;
                }
              }
              else
              {
                if (((Equipa *) node->tipo_node)->drt)
                {
                  {
                    ((Equipa *) node->tipo_node)->drt->esq = 0;
                    lista->cabeca = ((Equipa *) node->tipo_node)->drt;
                  }
                }
                else
                {
                  {
                    lista->cabeca = 0;
                    lista->ultimo = 0;
                  }
                }

              }

            }

          }
        }
        else
        {
          
        }

      }

      LimpaEl(node->tipo_node);
      if (node->esq && node->drt)
      {
        {
          node->esq->drt = node->drt;
          node->drt->esq = node->esq;
        }
      }
      else
      {
        if (node->esq)
        {
          node->esq->drt = 0;
        }
        else
        {
          if (node->drt)
          {
            {
              node->drt->esq = 0;
              hash_table[v] = node->drt;
            }
          }
          else
          {
            hash_table[v] = 0;
          }

        }

      }

      free(node);
    }
  }
  else
  {
    
  }

}

void LimpezaGeral(Node **hash_table, Lista *lista, void *(*LimpaEl)(void *))
{
  int i;
  void *lista_aux = lista->cabeca;
  Node *node_aux = 0;
  Node *del_aux = 0;
  while (lista_aux)
    lista_aux = LimpaEl(lista_aux);

  free(lista);
  for (i = 0; i < 1063; i++)
  {
    if (hash_table[i])
    {
      {
        node_aux = hash_table[i];
        while (node_aux)
        {
          del_aux = node_aux;
          node_aux = node_aux->drt;
          free(del_aux);
        }

      }
    }
    else
    {
      
    }

  }

  free(hash_table);
}

