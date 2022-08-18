/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"


struct node
{
  char *chave;
  void *valor;
  struct node *next;
};
typedef struct chaves
{
  char **lista_chaves;
  int tamanho;
  int ultima_chave;
} chaves;
struct tabela
{
  node **tabela;
  int tamanho;
  chaves chaves;
};
char *dupstring(const char *src)
{
  char *dest = (char *) malloc((strlen(src) + 1) * (sizeof(char)));
  if (dest != 0)
  {
    {
      strcpy(dest, src);
      return dest;
    }
  }
  else
  {
    
  }

  return 0;
}

node *cria_elemento(char *chave, void *valor, void *(*copiar)(void *valor))
{
  node *new_node = (node *) malloc(sizeof(node));
  if (new_node == 0)
  {
    return 0;
  }
  else
  {
    
  }

  new_node->chave = dupstring(chave);
  new_node->valor = copiar(valor);
  if ((new_node->chave != 0) && (new_node->valor != 0))
  {
    {
      return new_node;
    }
  }
  else
  {
    
  }

  return 0;
}

void destroi_elemento(node *elemento, void (*destroi)(void *valor))
{
  destroi(elemento->valor);
  free(elemento->chave);
  free(elemento);
}

bool cria_chaves(chaves *c, int tamanho)
{
  c->lista_chaves = (char **) malloc(tamanho * (sizeof(char *)));
  if (c->lista_chaves == 0)
  {
    return 0;
  }
  else
  {
    
  }

  c->tamanho = tamanho;
  c->ultima_chave = -1;
  return 1;
}

bool insere_chave(chaves *c, char *chave)
{
  if (c->ultima_chave == (c->tamanho - 1))
  {
    {
      c->lista_chaves = (char **) realloc(c->lista_chaves, (c->tamanho * 2) * (sizeof(char *)));
      if (c->lista_chaves == 0)
      {
        return 0;
      }
      else
      {
        
      }

      c->tamanho = c->tamanho * 2;
    }
  }
  else
  {
    
  }

  c->ultima_chave++;
  c->lista_chaves[c->ultima_chave] = chave;
  return 1;
}

bool remove_chave(chaves *c, char *chave)
{
  int i;
  char *temp;
  for (i = 0; i <= c->ultima_chave; i++)
  {
    temp = c->lista_chaves[i];
    if ((temp != 0) && (strcmp(temp, chave) == 0))
    {
      {
        c->lista_chaves[i] = 0;
        return 1;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

int hash(tabela *t, char *chave)
{
  int hash = 5381;
  int c;
  while (c = *(chave++))
  {
    hash = (((hash << 5) + hash) + c) % t->tamanho;
  }

  return hash;
}

tabela *cria_tabela(int tamanho)
{
  int i;
  tabela *t = (tabela *) malloc(sizeof(tabela));
  t->tamanho = tamanho;
  t->tabela = (node **) malloc(tamanho * (sizeof(node *)));
  if (t->tabela == 0)
  {
    return 0;
  }
  else
  {
    
  }

  for (i = 0; i < tamanho; i++)
    t->tabela[i] = 0;

  if (!cria_chaves(&t->chaves, tamanho))
  {
    return 0;
  }
  else
  {
    
  }

  return t;
}

bool insere_tabela(tabela *t, char *chave, void *valor, void *(*copiar)(void *valor))
{
  int pos = hash(t, chave);
  node *lista = t->tabela[pos];
  node *new_node;
  node *temp;
  void *valor_anterior;
  for (temp = lista; temp != 0; temp = temp->next)
  {
    if (strcmp(temp->chave, chave) == 0)
    {
      {
        valor_anterior = temp->valor;
        temp->valor = copiar(valor);
        if (valor_anterior != 0)
        {
          free(valor_anterior);
        }
        else
        {
          
        }

        return (temp->valor != 0) ? (1) : (0);
      }
    }
    else
    {
      
    }

  }

  new_node = cria_elemento(chave, valor, copiar);
  if (new_node != 0)
  {
    {
      new_node->next = lista;
      t->tabela[pos] = new_node;
      return insere_chave(&t->chaves, new_node->chave);
    }
  }
  else
  {
    
  }

  return 0;
}

void *procura_tabela(tabela *t, char *chave)
{
  int pos = hash(t, chave);
  node *temp;
  for (temp = t->tabela[pos]; temp != 0; temp = temp->next)
  {
    if (strcmp(temp->chave, chave) == 0)
    {
      {
        return temp->valor;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

bool remove_tabela(tabela *t, char *chave, void (*destroi)(void *valor))
{
  int pos = hash(t, chave);
  node *temp = t->tabela[pos];
  node *prev = 0;
  while (temp != 0)
  {
    if (strcmp(temp->chave, chave) == 0)
    {
      {
        if (prev == 0)
        {
          {
            t->tabela[pos] = temp->next;
          }
        }
        else
        {
          {
            prev->next = temp->next;
          }
        }

        remove_chave(&t->chaves, chave);
        destroi_elemento(temp, destroi);
        return 1;
      }
    }
    else
    {
      
    }

    prev = temp;
    temp = temp->next;
  }

  return 0;
}

void iterar_tabela(tabela *t, bool (*funcao)(char *chave, void *valor, void *contexto), void *contexto)
{
  int i;
  node *temp;
  for (i = 0; i < t->tamanho; i++)
  {
    for (temp = t->tabela[i]; temp != 0; temp = temp->next)
    {
      if (!funcao(temp->chave, temp->valor, contexto))
      {
        return;
      }
      else
      {
        
      }

    }

  }

}

void iterar_ordenado(tabela *t, bool (*funcao)(char *chave, void *valor, void *contexto), void *contexto)
{
  int i;
  void *valor;
  char *chave;
  for (i = 0; i <= t->chaves.ultima_chave; i++)
  {
    chave = t->chaves.lista_chaves[i];
    if (chave != 0)
    {
      {
        valor = procura_tabela(t, chave);
        if (valor != 0)
        {
          {
            if (!funcao(chave, valor, contexto))
            {
              return;
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
    }
    else
    {
      
    }

  }

}

void destroi_tabela(tabela *t, void (*destroi)(void *valor))
{
  int i;
  node *temp;
  node *next;
  for (i = 0; i < t->tamanho; i++)
  {
    temp = t->tabela[i];
    while (temp != 0)
    {
      next = temp->next;
      destroi_elemento(temp, destroi);
      temp = next;
    }

  }

  free(t->chaves.lista_chaves);
  free(t->tabela);
  free(t);
}

