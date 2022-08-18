#include "LinkedList.h"

/* Cria nova lista. */
LinkedList list_init()
{
	LinkedList lista;
	lista = malloc(sizeof(struct MasterNode));
	lista->load = 0;
	lista->head = NULL;
	lista->tail = NULL;
	return lista;
}

/* Adiciona um novo node antes do node next. */
Link add_node_before(Link next, Item item)
{
	Link new;
	new = malloc(sizeof(struct Node));
	new->item = item;
	new->next = next;
	return new;
}

/* Adiciona um novo node depois do node anterior. */
Link add_node_after(Link ant, Item item)
{
	Link new, aux;
	if (ant == NULL)
	{
		return add_node_before(ant, item);
	}
	new = malloc(sizeof(struct Node));
	new->item = item;
	aux = ant->next;
	new->next = aux;
	ant->next = new;
	return new;
}

/* Apaga um node. */
void delete_node(Link node)
{
	deleteItem(get_item(node));
	free(node);
}

/* Verifica se a lista esta vazia*/
int is_empty(LinkedList lista)
{
	return lista->load == 0;
}

/* Retorna o item associado ao node.*/
Item get_item(Link node)
{
	if (node != NULL)
	{
		return node->item;
	}
	return NULL;
}

/* Retorna o primeiro elemento da lista. */
Item get_first_item(LinkedList lista)
{
	return get_item(lista->head);
}

/* Retorna o elemento com chave key da lista. */
Link search_list(LinkedList lista, Key key)
{
	Link current;
	for (current = lista->head; current; current = current->next)
	{
		if (eq(key(get_item(current)), key))
		{
			return current;
		}
	}
	return NULL;
}

/*Adiciona ao inicio da lista*/
void push(LinkedList lista, Item i)
{
	Link newNode;
	newNode = add_node_before(lista->head, i);
	lista->head = newNode;
	if (lista->tail == NULL)
	{
		lista->tail = newNode;
	}
	lista->load++;
}

/*Add to end of the lista*/
void append(LinkedList lista, Item i)
{
	Link newNode;
	newNode = add_node_after(lista->tail, i);

	lista->tail = newNode;
	if (lista->head == NULL)
	{
		lista->head = newNode;
	}
	lista->load++;
}

/* Insere um novo item de forma ordenada. */
void insertInOrder(LinkedList lista, Item i)
{
	Link current;
	Link new;
	Link prev;

	if (is_empty(lista))
	{
		append(lista, i);
		return;
	}
	for (current = lista->head, prev = NULL; current && less(get_item(current), i); prev = current, current = current->next)
		;
	if (current == NULL)
	{
		append(lista, i);
		return;
	}
	new = malloc(sizeof(struct Node));
	new->item = i;
	new->next = current;
	if (prev)
	{
		prev->next = new;
	}
	else
	{
		lista->head = new;
	}
	lista->load++;
}

/*Remove cabeca da lista. */
void pop(LinkedList lista)
{
	Link aux;
	if (lista->head == NULL || is_empty(lista))
	{
		return;
	}
	aux = lista->head;
	lista->head = aux->next;
	delete_node(aux);
	lista->load--;
}

/* Remove elemento com chave k da lista. */
void remove_element(LinkedList lista, Key k)
{
	Link current, prev;

	for (current = lista->head, prev = NULL; current; prev = current, current = current->next)
	{
		if (eq(k, key(current->item)))
		{
			/* Quando o elem a apagar eh a cabeca da lista. */
			if (current == lista->head)
			{
				lista->head = current->next;
			}
			else
			{
				prev->next = current->next;
			}
			delete_node(current);
			lista->load--;
			break;
		}
	}
}

/* Destroi os nodes da lista. */
void destroy_list_nodes(LinkedList lista)
{
	Link current, aux;
	if (!lista)
	{
		return;
	}
	if (!is_empty(lista))
	{
		for (current = lista->head, aux = lista->head->next; current; aux = current->next, free(current), current = aux)
			;
	}
	free(lista);
}

/* Destroi o node com key nome da lista. */
void destroy_list_node(LinkedList lista, Key nome)
{
	Link current, prev;

	for (current = lista->head, prev = NULL; current; prev = current, current = current->next)
	{
		if (eq(nome, key(current->item)))
		{
			if (current == lista->head)
			{
				lista->head = current->next;
			}
			else
			{
				prev->next = current->next;
			}
			free(current);
			lista->load--;
			if (current == lista->tail)
			{
				lista->tail = lista->head;
			}
			break;
		}
	}
}

/*Delete lista*/
void destroy_list(LinkedList lista)
{
	Link current, aux;
	if (lista == NULL)
	{
		return;
	}
	if (lista->load != 0)
	{
		for (current = lista->head, aux = lista->head->next; current; aux = current->next, delete_node(current), current = aux)
			;
	}
	free(lista);
}
