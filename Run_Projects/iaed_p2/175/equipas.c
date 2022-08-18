#include "library.h"

/*-------------------------- Funcoes auxiliares --------------------------------------*/

/* incializa (a NULL) uma hash de ponteiros para equipas e 
devolve o endereco de memoria da hash */
ptr_equipa* Init_hash_equipa(int e, ptr_equipa* h_equipa) {
    int i;
    h_equipa = (ptr_equipa*) malloc(e*sizeof(ptr_equipa));
    for (i = 0; i < e; i++) h_equipa[i] = NULL;
    return h_equipa;
}

void free_equipa(ptr_equipa ptr_e) {
    free(ptr_e ->nome);
    free(ptr_e);
}

void free_hash_equipa (int e, ptr_equipa* h_equipa) {
    int i;
    ptr_equipa elem,aux;
    for (i = 0; i < e; i++) {
        elem = h_equipa[i];
        while (elem != NULL) {
            aux = elem -> next;
            free_equipa(elem);
            elem = aux;
        }
    }
    free(h_equipa);
}

/* ordena alfabeticamente na hashtable */
int ptr_ord_equipa(ptr_equipa fila, ptr_equipa ptr) {
    int anterior,proximo;
    ptr_equipa elem;
    elem = fila;

    while (elem != NULL) {
        anterior = strcmp(elem->nome,ptr->nome);
        if (anterior == 0)
            return 1;
        
        else if (elem -> next == NULL) {
            elem -> next = ptr;
            return 0;
        }
        proximo = strcmp(elem->next->nome,ptr->nome);
        if (proximo == 0)
            return 1;
        else if (anterior < 0 && proximo > 0) {
            ptr -> next = elem -> next;
            elem -> next = ptr;
            return 0;
        }
        elem = elem -> next;
    }
    
    return 0;
}

/* percorre todos os elementos que correspondem ao indice da hash
(util para ver se a equipa ja esta na hash) */
ptr_equipa devolve_ptr_e(ptr_equipa fila,char* nome_e){
    ptr_equipa elem;
    elem = fila;
    while (elem != NULL) {
        if (strcmp(elem -> nome,nome_e)==0) {
            return elem;
        }
        else if(strcmp(elem -> nome,nome_e) > 0) break;
        elem = elem->next;
    }
    return NULL;
}

/* percorre a fila de equipas e devolve o ponteiro da equipa asseguir a posicao 
onde a equipa em questao deveria de estar, esta e usada apenas quando a equipa 
ganha um jogo (ou seja percorre para tras) */
ptr_equipa percorre_mais(ptr_equipa posicao,ptr_equipa equipa) {
    ptr_equipa elem;
    elem = posicao;
    while (elem-> last_ordem != NULL) {
        if (elem -> last_ordem -> jogos_ganhos < equipa -> jogos_ganhos) {
            elem = elem -> last_ordem;
            continue;
        }
        else if (elem -> last_ordem -> jogos_ganhos > equipa -> jogos_ganhos) 
            return elem;

        else if ((elem -> last_ordem -> jogos_ganhos == equipa -> jogos_ganhos)&&(strcmp(elem->last_ordem->nome,equipa->nome)<0))
            return elem;
        
        /*quando esta entre equipas com os mesmos jogos ganhos*/
        else if(strcmp(elem-> last_ordem->nome,equipa->nome)<0 && strcmp(elem-> nome,equipa->nome)>0){
            return elem;
        }
        elem = elem -> last_ordem;
    }
    /* head */
    return elem;
}

/* faz o mesmo que a percorre_mais mas no sentido oposto
e usada apenas quando a equipa perde jogos (quando e removido ou score alterado)*/
ptr_equipa percorre_menos(ptr_equipa posicao,ptr_equipa equipa) {
    ptr_equipa elem;
    elem = posicao;
    while (elem-> next_ordem != NULL) {
        if (elem -> next_ordem -> jogos_ganhos > equipa -> jogos_ganhos) {
            elem = elem -> next_ordem;
            continue;
        }
        else if (elem -> next_ordem -> jogos_ganhos < equipa -> jogos_ganhos) 
            return elem;

        else if ((elem -> next_ordem -> jogos_ganhos == equipa -> jogos_ganhos) && (strcmp(elem->next_ordem-> nome,equipa -> nome)>0))
            return elem;
        
        else if(strcmp(elem-> next_ordem->nome,equipa->nome)>0 && strcmp(elem-> nome,equipa->nome)<0){
            return elem;
        }
        elem = elem -> next_ordem;
    }
    /* tail */
    return elem;
}

/* dependendo do argumento valor, 0 quando a equipa perde um jogo 
e 1 quando ganha um, vai utilizar as funcoes percorre_mais e percorre_menos
para depois poder atualizar a posicao da equipa na fila */
void altera_fila(ptr_equipa* head, ptr_equipa* tail, ptr_equipa equipa,int valor) {
    ptr_equipa anterior,proximo;
    
    /* ja era a head e os jogos ganhos aumenta */
    if (equipa == head[0] && valor == 1) return;
    /* equipa ja era a tail e jogos ganhos diminui */
    else if (equipa == tail[0] && valor == 0) return;

    else if (valor == 0) {
        anterior = percorre_menos(equipa ,equipa);
        if (anterior == equipa) return; /* nao precisa atualizar */
        else if (equipa == head[0] && anterior == head[0]) return;
        else if (equipa == head[0]) {
            head[0] = head[0] -> next_ordem;
            head[0] -> last_ordem = NULL;
        }
        else {
            equipa -> last_ordem -> next_ordem = equipa -> next_ordem;
            equipa -> next_ordem -> last_ordem = equipa -> last_ordem;
        }
        if (anterior == tail[0]) {
            tail[0] -> next_ordem = equipa;
            equipa -> last_ordem = tail[0];
            tail[0] = equipa;
            tail[0] -> next_ordem = NULL;
            return;
        }
        anterior -> next_ordem -> last_ordem = equipa;
        equipa -> next_ordem = anterior -> next_ordem;
        anterior -> next_ordem = equipa;
        equipa -> last_ordem = anterior;
        return;
    }
    proximo = percorre_mais(equipa,equipa);
    if (equipa == proximo) return; /* nao precisa atualizar */
    else if (equipa == tail[0] && proximo == tail[0]) return;
    else if (equipa == tail[0]) {
        tail[0] = tail[0] -> last_ordem;
        tail[0] -> next_ordem = NULL;
    }
    else {
        equipa -> last_ordem -> next_ordem = equipa -> next_ordem;
        equipa -> next_ordem -> last_ordem = equipa -> last_ordem;
    }
    if (proximo == head[0]) {
            head[0] -> last_ordem = equipa;
            equipa -> next_ordem = head[0];
            head[0] = equipa;
            head[0] -> last_ordem = NULL;
            return;
        }
    proximo -> last_ordem ->next_ordem = equipa;
    equipa -> last_ordem = proximo -> last_ordem;
    proximo -> last_ordem = equipa;
    equipa -> next_ordem = proximo;
}

/* adiciona a fila de equipas de acordo com o que e pedido no comando 'g' */
void add_equipa_lista (ptr_equipa* head, ptr_equipa* tail, ptr_equipa equipa) {
    ptr_equipa proximo;
    /* primeiro elemento */
    if (head[0] == NULL) {
        head[0] = equipa;
        return;
    }
    /* segundo elemento */
    else if (head[0]->next_ordem == NULL) {
        if (strcmp(head[0]->nome,equipa -> nome) >0) {
            tail[0] = head[0];
            head[0] = equipa;
            head[0] -> next_ordem = tail[0];
            tail[0] -> last_ordem = head[0];
            return;
        }
        tail[0] = equipa;
        head[0] -> next_ordem = tail[0];
        tail[0] -> last_ordem = head[0];
        return;
    }
    /* quando uma equipa e adicionada e passa a ser a nova head*/
    else if ((head[0]-> jogos_ganhos == 0) && strcmp(head[0]->nome,equipa -> nome)>0) {
        equipa -> next_ordem = head[0];
        head[0] -> last_ordem = equipa;
        head[0] = equipa;
        head[0] -> last_ordem = NULL;
        return;
    }
    else {
        /* no caso da equipa ser a nova tail*/
        if (tail[0]->jogos_ganhos > 0 || (tail[0]->jogos_ganhos == 0 && strcmp(tail[0]->nome,equipa-> nome)<0)){
            tail[0] -> next_ordem = equipa;
            equipa -> last_ordem = tail[0];
            tail[0] = equipa;
            tail[0] -> next_ordem = NULL;
            return;
        }
        proximo = percorre_mais(tail[0],equipa);

        proximo -> last_ordem -> next_ordem = equipa;
        equipa -> last_ordem = proximo -> last_ordem;
        proximo -> last_ordem = equipa;
        equipa -> next_ordem = proximo;
    }
}

/*-------------------------- Funcoes Principais --------------------------------------*/

/* verifica se ja existe uma equipa com o nome introduzido, caso nao haja adiciona 
alfabeticamente na fila correta da hash e adiciona na fila de equipas com o add_equipa_lista */
void nova_equipa(int NL,ptr_equipa* h_equipa,int e,ptr_equipa*head_equipa,
ptr_equipa*tail_equipa) {
    
    int h_indice,valor;
    char nome_e[1024];
    ptr_equipa ptr_e;
    scanf(" %[^:\n]",nome_e);

    ptr_e = (ptr_equipa) malloc(sizeof(equipa));

    ptr_e -> nome = copia_string(nome_e);
    ptr_e -> jogos_ganhos = 0;
    ptr_e -> next = NULL;
    ptr_e -> next_ordem = NULL;
    ptr_e -> last_ordem = NULL;

    h_indice = hash(ptr_e -> nome,e);

    if (h_equipa[h_indice] == NULL) {
        h_equipa[h_indice] = ptr_e;
        add_equipa_lista(head_equipa,tail_equipa,ptr_e);
        return;
    }
    /* caso so tenha um elemento */
    else if (h_equipa[h_indice] != NULL && h_equipa[h_indice] -> next == NULL) {
        if (strcmp(h_equipa[h_indice]->nome,ptr_e ->nome)<0 ){
            h_equipa[h_indice] -> next = ptr_e;
            add_equipa_lista(head_equipa,tail_equipa,ptr_e);
            return;
        }
        else if (strcmp(h_equipa[h_indice]->nome,ptr_e ->nome)>0){
            ptr_e -> next = h_equipa[h_indice];
            h_equipa[h_indice] = ptr_e;
            add_equipa_lista(head_equipa,tail_equipa,ptr_e);
            return;
        }
        else {
            printf("%d Equipa existente.\n",NL);
            free_equipa(ptr_e);
            return;
        }
    }
    /* caso o primeiro seja maior que a equipa inserida*/
    else if (strcmp(h_equipa[h_indice]->nome,ptr_e->nome)>0) {
            ptr_e -> next = h_equipa[h_indice];
            h_equipa[h_indice] = ptr_e;
            add_equipa_lista(head_equipa,tail_equipa,ptr_e);
            return;
    }
    else {
        valor = ptr_ord_equipa(h_equipa[h_indice],ptr_e);
        if (valor == 1) {
            printf("%d Equipa existente.\n",NL);
            free_equipa(ptr_e);
            return;
        }
        add_equipa_lista(head_equipa,tail_equipa,ptr_e);
    }
}

/* verifica se na fila (obtida atraves da hash) existe uma equipa com o nome inserido */
void procura_equipa(int NL,ptr_equipa* h_equipa,int e) {
    int h_indice;
    char nome_e[1024];
    ptr_equipa elem;
    scanf(" %[^:\n]",nome_e);

    h_indice = hash(nome_e, e);
    elem = h_equipa[h_indice];
    while (elem != NULL){
        if (strcmp(elem -> nome,nome_e)==0) {
            printf("%d %s %d\n",NL,elem->nome,elem->jogos_ganhos);
            return;
        }
        else if(strcmp(elem -> nome,nome_e) > 0) break;
        elem = elem->next;
    }
    printf("%d Equipa inexistente.\n",NL);
    return;
}

/* da print de todas as equipas que tem a mesma quantidade
de jogos ganhos que a primeira da fila*/
void melhores_equipas(int NL, ptr_equipa *head) {
    int max_ganhos;
    ptr_equipa elem = head[0];
    if (head[0] == NULL) return;
    max_ganhos = head[0]-> jogos_ganhos;
    printf("%d Melhores %d\n",NL,max_ganhos);
    while (elem != NULL && elem -> jogos_ganhos == max_ganhos ) {
        printf("%d * %s\n",NL, elem -> nome);
        elem = elem -> next_ordem;
    }
    return;
}