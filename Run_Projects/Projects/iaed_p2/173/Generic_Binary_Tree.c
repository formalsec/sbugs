#include "Generic_Binary_Tree.h"

/*
Cria um elemento da arvore binaria e retorna o seu Link.
*/
BTlink btnode_create(void *data,int size){
    int i;
    BTlink node = (BTlink) malloc(sizeof(struct BTnode));
    node->l = NULL;
    node->r = NULL;
    node->height = 1;

    node->data = malloc(size);

    /* Como "char" apenas ocupa 1 byte, uso isto para copiar a informacao byte por byte */
    for (i = 0; i<size; i++){
        *((char *)(node->data) + i) = *((char *)data+i); 
    }
    free(data);
    return node;
}

/*
Cria uma nova arvore binaria e retorna o Link para o primeiro elemento (NULL pois comeca vazia)
*/
BTlink bintree_create(){
    return NULL;
}

/*
Procura por um elemento na arvore binaria e retorna um ponteiro generico para a informacao deste.
*/
/*
*A funcao get_info serve para obter a informacao que se deseja comparar a partir do que esta guardado na arvore
*info e a informacao que se deseja comparar
*compare e a funcao usada para comparar a informacao
*Esta funcao de comparacao deve retornar:
- 0 se ARG1 == ARG2;
- >0 se ARG1 > ARG2;
- <0 se ARG1 < ARG2;
*Caso o elemento em questao nao exista na arvore, retorna NULL
*/
void *bintree_search(BTlink head,void *info,void *(*get_info)(void*),int (*compare)(void *,void*)){
    int aux;
    
    if (head == NULL)return NULL;

    aux = compare(info,get_info(head->data));

    if (aux == 0){
        return head->data;
    }else if ((head->l == NULL) && (head->r == NULL)){
        return NULL; 
    }else{
        if (aux > 0){
            return bintree_search(head->l,info,get_info, compare);
        }else{
            return bintree_search(head->r,info,get_info, compare);
        }
    }
}

/*
Retorna o Link do elemento com maior valor de uma arvore binaria
*/
BTlink bintree_max(BTlink head){
    if (head->r == NULL){
        return head;
    }else{
        return bintree_max(head->r);
    }
}

/*
Retorna o Link do elemento com menor valor de uma arvore binaria
*/
BTlink bintree_min(BTlink head){
    if (head->l == NULL){
        return head;
    }else{
        return bintree_min(head->l);
    }
}

/*
Liberta um elemento de uma arvore binaria.
*/
/*
Para libertar a informacao armazenada e necessaria funcao free_data que realize essa operacao.
*/
void btnode_free(BTlink node, void (*free_data)(void *)){
    free_data(node->data);
    free(node);
}

/*
Liberta uma arvore binaria.
*/
/*
Para libertar a informacao armazenada e necessaria funcao free_data que realize essa operacao.
*/
void bintree_free(BTlink head, void (*free_data)(void *)){
    if (head == NULL){
        return;
    }
    if (head->r != NULL){
        bintree_free(head->r,free_data);
    }
    if (head->l != NULL){
        bintree_free(head->l,free_data);
    }
    btnode_free(head,free_data);
}

/*
Retorna a "altura" de um elemento de uma arvore binaria.
*/
int bintree_height(BTlink head){
    if (head == NULL) return 0;
    return head->height;
}

/*
Realiza uma rotacao para a esquerda a partir de um elemento de uma arvore binaria.
*/
BTlink rotL(BTlink head){
    int hleft, hright, xleft, xright;
    BTlink x = head->r;
    head->r = x->l;
    x->l = head;

    hleft = bintree_height(head->l);
    hright = bintree_height(head->r);
    head->height = hleft > hright ? hleft + 1 : hright + 1;

    xleft = bintree_height(x->l);
    xright = bintree_height(x->r);
    x->height = xleft > xright ? xleft + 1 : xright + 1;
    return x;
}

/*
Realiza uma rotacao para a direita a partir de um elemento de uma arvore binaria.
*/
BTlink rotR(BTlink head){
    int hleft, hright, xleft, xright;
    BTlink x = head->l;
    head->l = x->r;
    x->r = head;

    hleft = bintree_height(head->l);
    hright = bintree_height(head->r);
    head->height = hleft > hright ? hleft + 1 : hright + 1;

    xleft = bintree_height(x->l);
    xright = bintree_height(x->r);
    x->height = xleft > xright ? xleft + 1 : xright + 1;
    return x;
}

/*
Realiza uma rotacao para a esquerda, seguida de uma rotacao para a direita a partir de um elemento de uma arvore binaria.
Retorna o elemento atualizado
*/
BTlink rotLR(BTlink head)
{
    if (head == NULL) return head;
    head->l = rotL(head->l);
    return rotR(head);
}

/*
Realiza uma rotacao para a direita, seguida de uma rotacao para a esquerda a partir de um elemento de uma arvore binaria.
Retorna o elemento atualizado
*/
BTlink rotRL(BTlink head)
{
    if (head == NULL) return head;
    head->r = rotR(head->r);
    return rotL(head);
}

/*
Retorna o "balance factor" de um elemento de uma arvore binaria.
*/
int bintree_balance(BTlink head)
{
    if(head == NULL) return 0;
    return bintree_height(head->l) - bintree_height(head->r);
}

/*
Equilibra uma ramo de uma arvore binaria.
Retorna o elemento atualizado.
*/
BTlink bintree_AVLbalance(BTlink head){
    int balanceFactor, hleft, hright;
    if (head == NULL) return head;
    balanceFactor = bintree_balance(head);
    if(balanceFactor > 1) { /* mais peso para a esquerda */
        if (bintree_balance(head->l) >= 0){
            head = rotR(head);
        }else{
            head = rotLR(head);
        }
    }else if(balanceFactor < -1){ /* mais peso para a direita*/
        if (bintree_balance(head->r) <= 0){
            head = rotL(head);
        }else{
            head = rotRL(head);
        }
    }
    else{
        hleft = bintree_height(head->l);
        hright = bintree_height(head->r);
        head->height = hleft > hright ? hleft + 1 : hright + 1;
    }
    return head;
}

/*
Funcao auxiliar que percorre uma arvore binaria ate chegar ao fim e, ai, adiciona um novo elemento;
Para comparacao e usada a funcao "compare" passada como argumento.
Caso o elemento ja exista na arvore, retorna 1.
*/
int bintree_add_item_aux(BTlink *head, BTlink node,void* (*get_info)(void*),int (*compare)(void*,void*)){
    /* comparar a informacao existente na node a avaliar com a informacao dada */
    int aux=compare(get_info((*head)->data),get_info(node->data));
    int res= 0;

    if (aux == 0) return 1;

    if(aux > 0){
        if ((*head)->r == NULL){
            (*head)->r = node;
        }else{
            res = bintree_add_item_aux(&(*head)->r,node,get_info,compare);
        }
    }else{
        if ((*head)->l == NULL){
            (*head)->l = node;
        }else{
            res = bintree_add_item_aux(&(*head)->l,node,get_info,compare);
        }
    }   
    *head = bintree_AVLbalance(*head);
    return res;
}

/*
Adiciona um novo elemento a uma arvore binaria;
*/
/*
*Os argumentos data e size sao necessarios para a criacao de um elemento da arvore binaria, sendo "data" a informacao que se deseja armazenar e "size" o tamanho em bytes desta informacao
*Para eventual libertacao do elemento criado, e tambem necessaria a passagem da funcao de libertacao especifica ao tipo de informacao armazenada. 
*Para comparacao e usada a funcao "compare" passada como argumento.
*A funcao get_info serve para obter a informacao que se deseja comparar a partir do que esta guardado na arvore
*info e a informacao que se deseja comparar
*compare e a funcao usada para comparar a informacao
*Esta funcao de comparacao deve retornar:
- 0 se ARG1 == ARG2;
- >0 se ARG1 > ARG2;
- <0 se ARG1 < ARG2;
Esta funcao retorna 0 e caso de sucesso.
Caso o elemento ja exista na arvore, retorna 1.
*/
int bintree_add_item(BTlink* head,void* data,int size,void (*free_data)(void *),void*(*get_info)(void*),int (*compare)(void*,void*)){
    BTlink node = btnode_create(data,size);
    if (*head != NULL){
        if (bintree_add_item_aux(head,node,get_info,compare)){
            btnode_free(node,free_data);
            return 1;
        }
        return 0;
    }else{
        *head = node;
        return 0;
    }
}

/*
 Elimina um elemento da lista;
*/
/*
*Para libertacao do elemento eliminado, e tambem necessaria a passagem da funcao de libertacao especifica ao tipo de informacao armazenada. 
*A funcao get_info serve para obter a informacao que se deseja comparar a partir do que esta guardado na arvore
*info e a informacao que se deseja comparar
*compare e a funcao usada para comparar a informacao
*Esta funcao de comparacao deve retornar:
- 0 se ARG1 == ARG2;
- >0 se ARG1 > ARG2;
- <0 se ARG1 < ARG2;
*/
void bintree_delete_item(BTlink* head,void *info,void *(*get_info)(void*),void (*free_data)(void *),int (*compare)(void *,void*)){
    int cmp_aux = compare(info,get_info((*head)->data));
    BTlink aux;
    void *data_aux;

    if (cmp_aux != 0){
        /* Caso a informacao da node nao seja igual a informacao a comparar... */
        if (cmp_aux > 0){
            if (((*head)->l == NULL))return;
            bintree_delete_item(&(*head)->l,info,get_info,free_data,compare);
        }else{
            if (((*head)->r == NULL))return;
            bintree_delete_item(&(*head)->r,info,get_info,free_data,compare);
        }
    }else{ /* Se encontrar o elemento em questao... */
        if (((*head)->r != NULL) && ((*head)->l != NULL)){
            /* Caso a node da arvore tenha ambos os ramos */
            aux=bintree_max((*head)->l);
            /* aux vai ser uma copia do elemento maximo do ramo da esquerda, para o eliminar */
            /* data_aux vai ser auxiliar para fazer troca de informacao de aux com a informacao de head*/
            data_aux = (*head)->data;
            (*head)->data = aux->data;
            aux->data = data_aux;

            /* Eliminar aux */
            bintree_delete_item(&(*head)->l, get_info(aux->data),get_info,free_data,compare);
        }else{  
            aux = *head; /* Guardar a node em aux para libertar a informacao mais tarde */
            if (((*head)->l == NULL) && ((*head)->r == NULL)){ /* Caso o elemento se situe no fim da arvore*/
                *head = NULL;       
            }else if ((*head)->l == NULL){
                *head = (*head)->r;
            }else{
                *head = (*head)->l;
            }
            btnode_free(aux,free_data);
        }
    }
    *head = bintree_AVLbalance(*head);
}

/*
Funcao auxiliar
*/
void bintree_array_aux(BTlink head,void **array,int *i,int size){
    if (head == NULL) return;
    bintree_array_aux(head->l,array,i,size);
    array[(*i)++] = head->data;
    bintree_array_aux(head->r,array,i,size);
}

/*
Copia a informacao de uma arvore binaria para um array
*/
void bintree_array(BTlink head,void **array,int size){
    int i = 0;
    bintree_array_aux(head,array,&i,size);
}

/*
Funcao auxiliar
*/
void bintree_to_list_condition_aux(BTlink head,Link *lista,void (*condition)(void *,Link *)){
    if (head == NULL) return;
    bintree_to_list_condition_aux(head->l,lista,condition);
    condition(head->data,lista);
    bintree_to_list_condition_aux(head->r,lista,condition);
}

/*
Cria uma lista e percorre a arvore binaria.
Para cada elemento e realizada a funcao condition que atua sobre o elemento e a lista criada 
*/
Link bintree_to_list_condition(BTlink head,void (*condition)(void *,Link *)){
    Link lista = linkedlist_create();
    bintree_to_list_condition_aux(head,&lista,condition);
    return lista;
}