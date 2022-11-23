#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "estruturas.h"

/******************************************************************************
 * Funcoes:
******************************************************************************/

/************************* Lista duplamente ligada ***************************/

/* mk_list: Funcao que cria uma nova lista vazia, e devolve um ponteiro para a 
mesma. */
List* mk_list() {
    List *lista;

    lista = (List *) can_fail_malloc(sizeof(List));
    lista->head = NULL;
    lista->last = NULL;

    return lista;
}

/* add_node_list: Funcao que adiciona um item como o ultimo elemento de uma 
lista, e devolve o ponteiro do seu no'. 
 lista: parametro que representa o ponteiro para a lista.
 item: parametro que representa o item a inserir. */
Node_list* add_node_list(List *lista, void *item) {
    Node_list *el;

    el = (Node_list *) can_fail_malloc(sizeof(Node_list));
    el->next = NULL;
    el->previous = lista->last;
    el->item = item;
    if (lista->head == NULL) {
        lista->head = el;
    }
    else {
        (lista->last)->next = el;
    }
    lista->last = el;

    return el;
}

/* remove_node_list: Funcao que remove um elemento da lista onde esta inserido, 
e devolve o ponteiro da lista resultante.
 lista: parametro que representa o ponteiro para a lista.
 el: parametro que representa o ponteiro do no' do elemento a remover.
 free_item: parametro que representa o ponteiro para uma funcao que liberta 
toda a memoria associado aos itens do no'. */
List* remove_node_list(List *lista, Node_list *el, void free_item(void *)) {
    Node_list *prev, *nxt;

    if (el == NULL || empty_list(lista)) {
        return lista;
    }
    if (el == lista->head && el == lista->last) {
        lista->head = NULL;
        lista->last = NULL;
    }
    else if (el == lista->head) {
        lista->head = el->next;
        lista->head->previous = NULL;
    }
    else if (el == lista->last) {
        lista->last = el->previous;
        lista->last->next = NULL;
    }
    else {
        prev = el->previous;
        nxt = el->next;
        prev->next = nxt;
        nxt->previous = prev;
    }
    free_item(el->item);
    free(el);
    
    return lista;
}

/* print_list: Funcao que imprime todos os elementos de uma lista pela ordem 
de insercao.
 lista: parametro que representa o ponteiro para a lista.
 linha: parametro que representa a linha de input que esta a ser lida.
 print_item: parametro que representa o ponteiro para uma funcao que imprime 
cada item. */
void print_list(List *lista, int linha, void print_item(void *)) {
    Node_list *el = lista->head;

    while (el != NULL) {
        printf("%d ", linha);
        print_item(el->item);
        el = el->next;
    }
}

/* free_list: Funcao que liberta toda a memoria associada a uma lista.
 lista: parametro que representa o ponteiro para a lista.
 free_item: parametro que representa o ponteiro para uma funcao que liberta 
toda a memoria associado aos itens do no'. */
void free_list(List *lista, void free_item(void *)) {
    Node_list *el = lista->last;
    Node_list *prev;

    while (el != NULL) {
        prev = el->previous;
        free_item(el->item);
        free(el);
        el = prev;
    }
    free(lista);
}

/* empty_list: Funcao que indica se uma lista esta' vazia, ou nao.
 lista: parametro que representa o ponteiro para a lista. */
int empty_list(List *lista) {
    return (lista->head == NULL);
}

/***************************** Arvore binaria ********************************/

/* mk_bt: Funcao que cria uma nova arvore binaria vazia, e devolve um ponteiro 
para a mesma. */
Bt* mk_bt() {
    Bt *bt;

    bt = (Bt *) can_fail_malloc(sizeof(Bt));
    bt->root = NULL;

    return bt;
}

/* new_node_bt: Funcao que cria um novo no' de arvore binaria, e devolve o seu 
ponteiro.
 chave: parametro que representa a chave do no'.
 l: parametro que representa o ramo esquerdo do no'.
 r: parametro que representa o ramo direito do no'. */
Node_bt* new_node_bt(int chave, Node_bt *l, Node_bt *r) {
    Node_bt *no;

    no = (Node_bt *) can_fail_malloc(sizeof(Node_bt));
    no->l = l;
    no->r = r;
    no->count = 0;
    no->height = 1;
    no->items = NULL;
    no->key = chave;
    
    return no;
}

/* heigth_bt: Funcao que determina e devolve o numero de niveis de uma arvore 
binaria.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
int height_bt(Node_bt *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    else {
        return raiz->height;
    }
}

/* rotL_bt: Funcao que executa uma rotacao esquerda numa arvore binaria, e 
devolve o ponteiro para a raiz da arvore resultante.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
Node_bt* rotL_bt(Node_bt *raiz) {
    Node_bt *aux= raiz->r, *aux2 = aux->l;

    aux->l = raiz;
    raiz->r = aux2;

    raiz->height = height_bt(raiz->l) > height_bt(raiz->l) ?
     height_bt(raiz->l) + 1 : height_bt(raiz->r) + 1;
    aux->height = height_bt(aux->l) > height_bt(aux->l) ?
     height_bt(aux->l) + 1 : height_bt(aux->r) + 1;
    
    return aux;
}

/* rotD_bt: Funcao que executa uma rotacao direita numa arvore binaria, e 
devolve o ponteiro para a raiz da arvore resultante.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
Node_bt* rotR_bt(Node_bt *raiz) {
    Node_bt *aux = raiz->l, *aux2 = aux->r;

    aux->r = raiz;
    raiz->l = aux2;

    raiz->height = height_bt(raiz->l) > height_bt(raiz->l) ?
     height_bt(raiz->l) + 1 : height_bt(raiz->r) + 1;
    aux->height = height_bt(aux->l) > height_bt(aux->l) ?
     height_bt(aux->l) + 1 : height_bt(aux->r) + 1;
    
    return aux;   
}

/* get_balance_bt: Funcao que determina e devolve o parametro de balanceamento 
de uma arvore binaria.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
int get_balance_bt(Node_bt *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    else {
        return height_bt(raiz->l) - height_bt(raiz->r);
    }    
}

/* balance_bt: Funcao que faz o balanceamento de uma arvore binaria, e devolve 
o ponteiro para a raiz da arvore resultante.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
Node_bt* balance_bt(Node_bt *raiz) {
    int balance;

    if (raiz == NULL) {
        return raiz;
    }

    raiz->height = 1 + height_bt(raiz->l) > height_bt(raiz->l) ?
     height_bt(raiz->l) + 1 : height_bt(raiz->r) + 1;
    balance = get_balance_bt(raiz);
    if (balance > 1) {
        if (get_balance_bt(raiz->l) >= 0) {
            raiz = rotR_bt(raiz);
        }
        else {
            raiz->l = rotL_bt(raiz->l);
            raiz = rotR_bt(raiz);
        }
    }
    else if (balance < -1) {
        if (get_balance_bt(raiz->r) <= 0) {
            raiz = rotL_bt(raiz);
        }
        else {
            raiz->r = rotR_bt(raiz->r);
            raiz = rotL_bt(raiz);
        }
    }

    return raiz;
}

/* max_bt: Funcao que procura e devolve o no' com a maior chave numa arvore 
binaria.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
Node_bt* max_bt(Node_bt *raiz) {
    if (raiz == NULL || raiz->r == NULL) {
        return raiz;
    }
    else {
        return max_bt(raiz->r);
    }
}

/* add_node_bt: Funcao que adiciona um no' a uma arvore binaria, e devolve o 
ponteiro para a raiz da arvore resultante.
 chave: parametro que representa a chave que identifica o no' que vai ser 
adicionado.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
Node_bt* add_node_bt(int chave, Node_bt *raiz) {
    if (raiz == NULL) {
        return new_node_bt(chave, NULL, NULL);
    }

    if (chave < raiz->key) {
        raiz->l = add_node_bt(chave, raiz->l);
    }
    else if (raiz->key < chave) {
        raiz->r = add_node_bt(chave, raiz->r);
    }
    else {
        return raiz;
    }
    raiz = balance_bt(raiz);

    return raiz;
}

/* remove_node_bt: Funcao que remove um no' a uma arvore binaria, e devolve o 
ponteiro para a raiz da arvore resultante.
 chave: parametro que representa a chave que identifica o no' que vai ser 
removido.
 raiz: parametro que representa o ponteiro para a raiz da arvore.
 free_item: parametro que representa o ponteiro para uma funcao que liberta 
toda a memoria associado aos itens do no'. */
Node_bt* remove_node_bt(int chave, Node_bt *raiz, void free_item(void *)) {
    if (raiz == NULL) {
        return raiz;
    }
    else if (chave < raiz->key) {
        raiz->l = remove_node_bt(chave, raiz->l, free_item);
    }
    else if (raiz->key < chave) {
        raiz->r = remove_node_bt(chave, raiz->r, free_item);
    }
    else {
        if (raiz->l != NULL && raiz->r != NULL) {
            Node_bt *aux = max_bt(raiz->l), *aux2;
            aux2 = (Node_bt *) can_fail_malloc(sizeof(Node_bt));
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
        else {
            Node_bt *aux = raiz;
            if (raiz->l == NULL && raiz->r == NULL) {
                raiz = NULL;
            }
            else if (raiz->l == NULL) {
                raiz = raiz->r;
            }
            else {
                raiz = raiz->l;
            }
            if (aux->count != 0) {
                while (aux->count != 0) {
                    aux->count -= 1;
                    free_item(*(aux->items + aux->count));
                }
                free(aux->items);
            }
            free(aux);
        }
    }
    raiz = balance_bt(raiz);

    return raiz;
}

/* search_bt: Funcao que procura e devolve um no' de uma arvore binaria.
 chave: parametro que representa a chave que identifica o no' que esta' a ser 
procurado.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
Node_bt* search_bt(int chave, Node_bt *raiz) {
    if (raiz == NULL || chave == raiz->key) {
        return raiz;
    }
    else if (chave < raiz->key) {
        return search_bt(chave, raiz->l);
    }
    else {
        return search_bt(chave, raiz->r);
    }
}

/* add_aux_bt: Funcao auxiliar da funcao add_item_bt.
 item: parametro que representa o ponteiro do item a adicionar.
 raiz: parametro que representa o ponteiro para a raiz da arvore.
 key: parametro que representa o ponteiro para uma funcao que acede 'a chave que
identifica o item numa arvore binaria. */
Node_bt* add_aux_bt(void *item, Node_bt *raiz, int key(void *)) {
    if (key(item) == raiz->key) {
        raiz->count += 1;
        if (raiz->count == 1) {
            raiz->items = (void **) can_fail_malloc(sizeof(void *));
        }
        else {
            raiz->items = (void **)
             can_fail_realloc(raiz->items, sizeof(void *) * raiz->count);
        }
        *(raiz->items + (raiz->count - 1)) = item;
    }
    else if (key(item) < raiz->key) {
        raiz->l = add_item_bt(item, raiz->l, key);
    }
    else {
        raiz->r = add_item_bt(item, raiz->r, key);
    }

    return raiz;
}

/* add_item_bt: Funcao que adiciona um item a uma arvore binaria, e devolve o 
ponteiro para a raiz da arvore resultante.
 item: parametro que representa o ponteiro do item a adicionar.
 raiz: parametro que representa o ponteiro para a raiz da arvore.
 key: parametro que representa o ponteiro para uma funcao que acede 'a chave que
identifica o item numa arvore binaria. */
Node_bt* add_item_bt(void *item, Node_bt *raiz, int key(void *)) {
    if (search_bt(key(item), raiz) == NULL) {
        raiz = add_node_bt(key(item), raiz);
    }
    add_aux_bt(item, raiz, key);

    return raiz;
}

/* remove_item_bt: Funcao que remove um item a uma arvore binaria, e devolve o 
ponteiro para a raiz da arvore resultante.
 item: parametro que representa o ponteiro do item a remover.
 raiz: parametro que representa o ponteiro para a raiz da arvore.
 key: parametro que representa o ponteiro para uma funcao que acede 'a chave que
identifica o item numa arvore binaria.
 free_item: parametro que representa o ponteiro para uma funcao que liberta 
toda a memoria associado aos itens do no'. */
Node_bt* remove_item_bt(void *item, Node_bt *raiz, int key(void *),
 void free_item(void *)) {
    int contador;
    Node_bt *no;

    no = search_bt(key(item), raiz);
    if (no != NULL) {
        if (no->count == 1) {
            if (*(no->items) == item) {
                no->count -= 1;
                free(no->items);
                raiz = remove_node_bt(no->key, raiz, free_item);
            }
        }
        else if (no->count > 1) {
            for (contador = 0; contador < no->count; contador++) {
                if (*(no->items + contador) == item) {
                    no->count -= 1;
                    *(no->items + contador) = *(no->items + no->count);
                    no->items = (void **) can_fail_realloc(no->items,
                     sizeof(void *) * no->count);
                    break;
                }
            }
        }
    }

    return raiz;
}

/* free_aux_bt: Funcao auxiliar da funcao free_bt.
 raiz: parametro que representa o ponteiro para a raiz da arvore.
 free_item: parametro que representa o ponteiro para uma funcao que liberta 
toda a memoria associado aos itens do no'. */
void free_aux_bt(Node_bt *raiz, void free_item(void *)) {
    int contador;

    if (raiz == NULL) {
        return;
    }
    if (raiz->count > 0) {
        for (contador = 0; contador < raiz->count; contador++) {
            free_item(*(raiz->items + contador));
        }
        free(raiz->items);
    }
    free_aux_bt(raiz->l, free_item);
    free_aux_bt(raiz->r, free_item);
    free(raiz);
}

/* free_bt: Funcao que liberta toda a memoria associada a uma arvore binaria.
 arvore: parametro que representa o ponteiro para a arvore binaria.
 free_item: parametro que representa o ponteiro para uma funcao que liberta 
toda a memoria associado aos itens do no'. */
void free_bt(Bt *arvore, void free_item(void *)) {
    free_aux_bt(arvore->root, free_item);
    free(arvore);
}

/* empty_bt: Funcao que indica se uma arvore binaria esta' vazia, ou nao.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
int empty_bt(Node_bt *raiz) {
    return (raiz == NULL);
}

/***************** Tabela de dispersao por procura linear ********************/

/* mk_lp: Funcao que cria uma nova tabela de dispersao por procura linear, e 
devolve um ponteiro para a mesma.
 tamanho: parametro que representa o tamanho incial da tabela. */
Lp* mk_lp(long tamanho) {
    long cont;
    Lp *lp;

    lp = (Lp *) can_fail_malloc(sizeof(Lp));
    lp->size = tamanho;
    lp->cap = 0;
    lp->table = (void **) can_fail_malloc(sizeof(void *) * tamanho);
    for (cont = 0; cont < tamanho; cont++) {
        lp->table[cont] = NULL;
    }

    return lp;
}

/* double_lp: Funcao que duplica o tamanho de uma tabela de dispersao, e devolve 
o ponteiro para a tabela de dispersao resultante. 
 lp: parametro que representa o ponteiro para a tabela de dispersao.
 key: parametro que representa o ponteiro para uma funcao que acede 'a chave que
identifica o item numa tabela de dispersao.
 hash: parametro que representa o ponteiro para uma funcao que distribui os 
indices para a tabela de dispersao. */
Lp* double_lp(Lp *lp, char* key(void *), long hash(void *, long)) {
    long cont, cont2 = 0;
    Lp *new_lp;

    new_lp = mk_lp(lp->size * 2);
    for (cont = 0; cont < lp->size; cont++) {
        if (lp->table[cont] != NULL) {
            add_item_lp(new_lp, lp->table[cont], key, hash);
            cont2++;
            if (cont2 >= lp->size / 2) {
                break;
            }
        }
    }
    free_lp(lp);

    return new_lp;
}

/* add_item_lp: Funcao que adiciona um item a uma tabela de dispersao, e devolve 
o ponteiro para a tabela de dispersao resultante. 
 lp: parametro que representa o ponteiro para a tabela de dispersao.
 item: parametro que representa o ponteiro para o item a adicionar.
 key: parametro que representa o ponteiro para uma funcao que acede 'a chave que
identifica o item numa tabela de dispersao.
 hash: parametro que representa o ponteiro para uma funcao que distribui os 
indices para a tabela de dispersao. */
Lp* add_item_lp(Lp *lp, void *item, char* key(void *), long hash(void *, long)) {
    long pos;
    char *chave = key(item);

    if (lp->cap + 1 >= lp->size / 2) {
        lp = double_lp(lp, key, hash);
    }
    pos = hash(chave, lp->size);
    while (lp->table[pos] != NULL) {
        pos = (pos + 1) % lp->size;
    }
    lp->table[pos] = item;
    lp->cap += 1;

    return lp;
}

/* search_item_lp: Funcao que procura um item numa tabela de dispersao, e 
devolve o seu ponteiro. 
 lp: parametro que representa o ponteiro para a tabela de dispersao.
 chave: parametro que representa a chave que identifica o item que esta' a ser 
procurado.
 key: parametro que representa o ponteiro para uma funcao que acede 'a chave que
identifica o item numa tabela de dispersao.
 hash: parametro que representa o ponteiro para uma funcao que distribui os 
indices para a tabela de dispersao. */
void* search_item_lp(Lp *lp, char* chave, char* key(void *),
 long hash(void *, long)) {
    long pos = hash(chave, lp->size);
    
    while(lp->table[pos] != NULL) {
        if (strcmp(key(lp->table[pos]), chave) == 0) {
            return lp->table[pos];
        }
        else {
            pos = (pos + 1) % lp->size;
        }
    }

    return NULL;
}

/* delete_item_lp: Funcao que elimina um item a uma tabela de dispersao, e 
devolve o seu ponteiro (para depois ser processado). 
 lp: parametro que representa o ponteiro para a tabela de dispersao.
 chave: parametro que representa a chave que identifica o item que esta' a ser 
procurado.
 key: parametro que representa o ponteiro para uma funcao que acede 'a chave que
identifica o item numa tabela de dispersao.
 hash: parametro que representa o ponteiro para uma funcao que distribui os 
indices para a tabela de dispersao. */
void* delete_item_lp(Lp *lp, char *chave, char* key(void *),
 long hash(void *, long)) {
    long pos, cont;
    void *aux1, *aux2;

    pos = hash(chave, lp->size);
    while(lp->table[pos] != NULL) {
        if (strcmp(key(lp->table[pos]), chave) == 0) {
            break;
        }
        else {
            pos = (pos + 1) % lp->size;
        }
    }
    if (lp->table[pos] == NULL) {
        return NULL;
    }
    aux1 = lp->table[pos];
    lp->table[pos] = NULL;
    lp->cap -= 1;
    for (cont = (pos + 1) % lp->size; lp->table[cont] != NULL;
     cont = (cont + 1) % lp->size) {
        aux2 = lp->table[cont];
        lp->table[cont] = NULL;
        lp->cap -= 1;
        add_item_lp(lp, aux2, key, hash);
    }

    return aux1;
}

/* free_lp: Funcao que liberta toda a memoria associada a uma tabela de 
dispersao. 
 lp: parametro que representa o ponteiro para a tabela de dispersao. */
void free_lp(Lp *lp) {
    free(lp->table);
    free(lp);
}
