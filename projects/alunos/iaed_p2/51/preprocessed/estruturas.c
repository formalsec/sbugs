#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "estruturas.h"


List *mk_list()
{
  List *lista;
  lista = (List *) malloc(sizeof(List));
  lista->head = 0;
  lista->last = 0;
  return lista;
}

Node_list *add_node_list(List *lista, void *item)
{
  Node_list *el;
  el = (Node_list *) malloc(sizeof(Node_list));
  el->next = 0;
  el->previous = lista->last;
  el->item = item;
  if (lista->head == 0)
  {
    lista->head = el;
  }
  else
  {
    lista->last->next = el;
  }

  lista->last = el;
  return el;
}

List *remove_node_list(List *lista, Node_list *el, void free_item(void *))
{
  Node_list *prev;
  Node_list *nxt;
  if ((el == 0) || empty_list(lista))
  {
    return lista;
  }
  else
  {
    
  }

  if ((el == lista->head) && (el == lista->last))
  {
    lista->head = 0;
    lista->last = 0;
  }
  else
  {
    if (el == lista->head)
    {
      lista->head = el->next;
      lista->head->previous = 0;
    }
    else
    {
      if (el == lista->last)
      {
        lista->last = el->previous;
        lista->last->next = 0;
      }
      else
      {
        prev = el->previous;
        nxt = el->next;
        prev->next = nxt;
        nxt->previous = prev;
      }

    }

  }

  free_item(el->item);
  free(el);
  return lista;
}

void print_list(List *lista, int linha, void print_item(void *))
{
  Node_list *el = lista->head;
  while (el != 0)
  {
    printf("%d ", linha);
    print_item(el->item);
    el = el->next;
  }

}

void free_list(List *lista, void free_item(void *))
{
  Node_list *el = lista->last;
  Node_list *prev;
  while (el != 0)
  {
    prev = el->previous;
    free_item(el->item);
    free(el);
    el = prev;
  }

  free(lista);
}

int empty_list(List *lista)
{
  return lista->head == 0;
}

Bt *mk_bt()
{
  Bt *bt;
  bt = (Bt *) malloc(sizeof(Bt));
  bt->root = 0;
  return bt;
}

Node_bt *new_node_bt(int chave, Node_bt *l, Node_bt *r)
{
  Node_bt *no;
  no = (Node_bt *) malloc(sizeof(Node_bt));
  no->l = l;
  no->r = r;
  no->count = 0;
  no->height = 1;
  no->items = 0;
  no->key = chave;
  return no;
}

int height_bt(Node_bt *raiz)
{
  if (raiz == 0)
  {
    return 0;
  }
  else
  {
    return raiz->height;
  }

}

Node_bt *rotL_bt(Node_bt *raiz)
{
  Node_bt *aux = raiz->r;
  Node_bt *aux2 = aux->l;
  aux->l = raiz;
  raiz->r = aux2;
  raiz->height = (height_bt(raiz->l) > height_bt(raiz->l)) ? (height_bt(raiz->l) + 1) : (height_bt(raiz->r) + 1);
  aux->height = (height_bt(aux->l) > height_bt(aux->l)) ? (height_bt(aux->l) + 1) : (height_bt(aux->r) + 1);
  return aux;
}

Node_bt *rotR_bt(Node_bt *raiz)
{
  Node_bt *aux = raiz->l;
  Node_bt *aux2 = aux->r;
  aux->r = raiz;
  raiz->l = aux2;
  raiz->height = (height_bt(raiz->l) > height_bt(raiz->l)) ? (height_bt(raiz->l) + 1) : (height_bt(raiz->r) + 1);
  aux->height = (height_bt(aux->l) > height_bt(aux->l)) ? (height_bt(aux->l) + 1) : (height_bt(aux->r) + 1);
  return aux;
}

int get_balance_bt(Node_bt *raiz)
{
  if (raiz == 0)
  {
    return 0;
  }
  else
  {
    return height_bt(raiz->l) - height_bt(raiz->r);
  }

}

Node_bt *balance_bt(Node_bt *raiz)
{
  int balance;
  if (raiz == 0)
  {
    return raiz;
  }
  else
  {
    
  }

  raiz->height = ((1 + height_bt(raiz->l)) > height_bt(raiz->l)) ? (height_bt(raiz->l) + 1) : (height_bt(raiz->r) + 1);
  balance = get_balance_bt(raiz);
  if (balance > 1)
  {
    if (get_balance_bt(raiz->l) >= 0)
    {
      raiz = rotR_bt(raiz);
    }
    else
    {
      raiz->l = rotL_bt(raiz->l);
      raiz = rotR_bt(raiz);
    }

  }
  else
  {
    if (balance < (-1))
    {
      if (get_balance_bt(raiz->r) <= 0)
      {
        raiz = rotL_bt(raiz);
      }
      else
      {
        raiz->r = rotR_bt(raiz->r);
        raiz = rotL_bt(raiz);
      }

    }
    else
    {
      
    }

  }

  return raiz;
}

Node_bt *max_bt(Node_bt *raiz)
{
  if ((raiz == 0) || (raiz->r == 0))
  {
    return raiz;
  }
  else
  {
    return max_bt(raiz->r);
  }

}

Node_bt *add_node_bt(int chave, Node_bt *raiz)
{
  if (raiz == 0)
  {
    return new_node_bt(chave, 0, 0);
  }
  else
  {
    
  }

  if (chave < raiz->key)
  {
    raiz->l = add_node_bt(chave, raiz->l);
  }
  else
  {
    if (raiz->key < chave)
    {
      raiz->r = add_node_bt(chave, raiz->r);
    }
    else
    {
      return raiz;
    }

  }

  raiz = balance_bt(raiz);
  return raiz;
}

Node_bt *remove_node_bt(int chave, Node_bt *raiz, void free_item(void *))
{
  if (raiz == 0)
  {
    return raiz;
  }
  else
  {
    if (chave < raiz->key)
    {
      raiz->l = remove_node_bt(chave, raiz->l, free_item);
    }
    else
    {
      if (raiz->key < chave)
      {
        raiz->r = remove_node_bt(chave, raiz->r, free_item);
      }
      else
      {
        if ((raiz->l != 0) && (raiz->r != 0))
        {
          Node_bt *aux = max_bt(raiz->l);
          Node_bt *aux2;
          aux2 = (Node_bt *) malloc(sizeof(Node_bt));
          aux2->count = raiz->count;
          aux2->items = raiz->items;
          raiz->key = aux->key;
          raiz->count = aux->count;
          raiz->items = aux->items;
          aux->count = aux2->count;
          aux->items = aux2->items;
          free(aux2);
          raiz->l = remove_node_bt(aux->key, raiz->l, free_item);
        }
        else
        {
          Node_bt *aux = raiz;
          if ((raiz->l == 0) && (raiz->r == 0))
          {
            raiz = 0;
          }
          else
          {
            if (raiz->l == 0)
            {
              raiz = raiz->r;
            }
            else
            {
              raiz = raiz->l;
            }

          }

          if (aux->count != 0)
          {
            while (aux->count != 0)
            {
              aux->count -= 1;
              free_item(*(aux->items + aux->count));
            }

            free(aux->items);
          }
          else
          {
            
          }

          free(aux);
        }

      }

    }

  }

  raiz = balance_bt(raiz);
  return raiz;
}

Node_bt *search_bt(int chave, Node_bt *raiz)
{
  if ((raiz == 0) || (chave == raiz->key))
  {
    return raiz;
  }
  else
  {
    if (chave < raiz->key)
    {
      return search_bt(chave, raiz->l);
    }
    else
    {
      return search_bt(chave, raiz->r);
    }

  }

}

Node_bt *add_aux_bt(void *item, Node_bt *raiz, int key(void *))
{
  if (key(item) == raiz->key)
  {
    raiz->count += 1;
    if (raiz->count == 1)
    {
      raiz->items = (void **) malloc(sizeof(void *));
    }
    else
    {
      raiz->items = (void **) realloc(raiz->items, (sizeof(void *)) * raiz->count);
    }

    *(raiz->items + (raiz->count - 1)) = item;
  }
  else
  {
    if (key(item) < raiz->key)
    {
      raiz->l = add_item_bt(item, raiz->l, key);
    }
    else
    {
      raiz->r = add_item_bt(item, raiz->r, key);
    }

  }

  return raiz;
}

Node_bt *add_item_bt(void *item, Node_bt *raiz, int key(void *))
{
  if (search_bt(key(item), raiz) == 0)
  {
    raiz = add_node_bt(key(item), raiz);
  }
  else
  {
    
  }

  add_aux_bt(item, raiz, key);
  return raiz;
}

Node_bt *remove_item_bt(void *item, Node_bt *raiz, int key(void *), void free_item(void *))
{
  int contador;
  Node_bt *no;
  no = search_bt(key(item), raiz);
  if (no != 0)
  {
    if (no->count == 1)
    {
      if ((*no->items) == item)
      {
        no->count -= 1;
        free(no->items);
        raiz = remove_node_bt(no->key, raiz, free_item);
      }
      else
      {
        
      }

    }
    else
    {
      if (no->count > 1)
      {
        for (contador = 0; contador < no->count; contador++)
        {
          if ((*(no->items + contador)) == item)
          {
            no->count -= 1;
            *(no->items + contador) = *(no->items + no->count);
            no->items = (void **) realloc(no->items, (sizeof(void *)) * no->count);
            break;
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

  return raiz;
}

void free_aux_bt(Node_bt *raiz, void free_item(void *))
{
  int contador;
  if (raiz == 0)
  {
    return;
  }
  else
  {
    
  }

  if (raiz->count > 0)
  {
    for (contador = 0; contador < raiz->count; contador++)
    {
      free_item(*(raiz->items + contador));
    }

    free(raiz->items);
  }
  else
  {
    
  }

  free_aux_bt(raiz->l, free_item);
  free_aux_bt(raiz->r, free_item);
  free(raiz);
}

void free_bt(Bt *arvore, void free_item(void *))
{
  free_aux_bt(arvore->root, free_item);
  free(arvore);
}

int empty_bt(Node_bt *raiz)
{
  return raiz == 0;
}

Lp *mk_lp(long tamanho)
{
  long cont;
  Lp *lp;
  lp = (Lp *) malloc(sizeof(Lp));
  lp->size = tamanho;
  lp->cap = 0;
  lp->table = (void **) malloc((sizeof(void *)) * tamanho);
  for (cont = 0; cont < tamanho; cont++)
  {
    lp->table[cont] = 0;
  }

  return lp;
}

Lp *double_lp(Lp *lp, char *key(void *), long hash(void *, long))
{
  long cont;
  long cont2 = 0;
  Lp *new_lp;
  new_lp = mk_lp(lp->size * 2);
  for (cont = 0; cont < lp->size; cont++)
  {
    if (lp->table[cont] != 0)
    {
      add_item_lp(new_lp, lp->table[cont], key, hash);
      cont2++;
      if (cont2 >= (lp->size / 2))
      {
        break;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  free_lp(lp);
  return new_lp;
}

Lp *add_item_lp(Lp *lp, void *item, char *key(void *), long hash(void *, long))
{
  long pos;
  char *chave = key(item);
  if ((lp->cap + 1) >= (lp->size / 2))
  {
    lp = double_lp(lp, key, hash);
  }
  else
  {
    
  }

  pos = hash(chave, lp->size);
  while (lp->table[pos] != 0)
  {
    pos = (pos + 1) % lp->size;
  }

  lp->table[pos] = item;
  lp->cap += 1;
  return lp;
}

void *search_item_lp(Lp *lp, char *chave, char *key(void *), long hash(void *, long))
{
  long pos = hash(chave, lp->size);
  while (lp->table[pos] != 0)
  {
    if (strcmp(key(lp->table[pos]), chave) == 0)
    {
      return lp->table[pos];
    }
    else
    {
      pos = (pos + 1) % lp->size;
    }

  }

  return 0;
}

void *delete_item_lp(Lp *lp, char *chave, char *key(void *), long hash(void *, long))
{
  long pos;
  long cont;
  void *aux1;
  void *aux2;
  pos = hash(chave, lp->size);
  while (lp->table[pos] != 0)
  {
    if (strcmp(key(lp->table[pos]), chave) == 0)
    {
      break;
    }
    else
    {
      pos = (pos + 1) % lp->size;
    }

  }

  if (lp->table[pos] == 0)
  {
    return 0;
  }
  else
  {
    
  }

  aux1 = lp->table[pos];
  lp->table[pos] = 0;
  lp->cap -= 1;
  for (cont = (pos + 1) % lp->size; lp->table[cont] != 0; cont = (cont + 1) % lp->size)
  {
    aux2 = lp->table[cont];
    lp->table[cont] = 0;
    lp->cap -= 1;
    add_item_lp(lp, aux2, key, hash);
  }

  return aux1;
}

void free_lp(Lp *lp)
{
  free(lp->table);
  free(lp);
}

