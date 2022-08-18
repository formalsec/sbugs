#include "library.h"

/*-------------------------- Funcoes auxiliares --------------------------------------*/

/* incializa (a NULL) uma hash de ponteiros para jogos e 
devolve o endereco de memoria da hash */
ptr_jogo* Init_hash_jogo(int j, ptr_jogo* h_jogo) {
    int i;
    h_jogo = (ptr_jogo*) malloc(j*sizeof(ptr_jogo));
    for (i = 0; i < j; i++) h_jogo[i] = NULL;
    return h_jogo;
}

void free_jogo(ptr_jogo ptr_j) {
    free(ptr_j ->nome);
    free(ptr_j);
}

void free_hash_jogo (int j, ptr_jogo* h_jogo) {
    int i;
    ptr_jogo elem,aux;
    for (i = 0; i < j; i++) {
        elem = h_jogo[i];
        while (elem != NULL) {
            aux = elem -> next;
            free_jogo(elem);
            elem = aux;
        }
    }
    free(h_jogo);
}

/* adiciona na fila da hash correspondente alfabeticamente*/
void ptr_ord_jogo(ptr_jogo fila,ptr_jogo ptr) {
    int anterior,proximo;
    ptr_jogo elem;
    elem = fila;

while (elem != NULL) {
        anterior = strcmp(elem->nome,ptr->nome);
        if (anterior == 0)
            return;
        
        else if (elem -> next == NULL) {
            elem -> next = ptr;
            ptr -> last = elem;
            return;
        }
        proximo = strcmp(elem->next->nome,ptr->nome);
        if (proximo == 0)
            return;
        else if (anterior < 0 && proximo > 0) {
            ptr -> next = elem -> next;
            elem -> next = ptr;
            ptr -> next -> last = ptr;
            ptr -> last = elem;
            return ;
        }
        elem = elem -> next;
    }
    return ;
}

/* percorre todos os elementos que correspondem ao indice da hash
(util para ver se o jogo ja esta na hash) */
ptr_jogo percorre_fila(ptr_jogo elem,char *nome) {
    while (elem != NULL){
        if (strcmp(elem -> nome,nome)==0) {
            return elem;
        }
        else if(strcmp(elem -> nome,nome) > 0) break;
        elem = elem->next;
    }
    return NULL;
}

/* adiciona o jogo a fila de jogos (ordem de entrada) */
void add_jogo_lista(ptr_jogo* head,ptr_jogo* tail, ptr_jogo jogo) {
    if (head[0] == NULL) {
        head[0] = jogo;
        return;
    }
    else if(head[0] -> next_ordem == NULL) {
        tail[0] = jogo;
        head[0] -> next_ordem = tail[0];
        tail[0] -> last_ordem = head[0];
        return;
    }
    jogo -> last_ordem = tail[0];
    tail[0] -> next_ordem = jogo;
    tail[0] = tail[0] -> next_ordem; 
    return;
}

/* remove jogo da fila de jogos */
void remove_jogo_lista(ptr_jogo* head, ptr_jogo* tail, ptr_jogo jogo) {
    /*caso tenha sido o primeiro jogo inserido*/
    if (head[0] == jogo) {
        if (head[0]->next_ordem == NULL) {
            head[0] = NULL;
            return;
        }
        else if(head[0]-> next_ordem == tail[0]) {
            head[0] = tail[0];
            head[0] -> last_ordem = NULL;
            tail[0] = NULL;
            return;
        }
        head[0] = head[0] -> next_ordem;
        head[0] -> last_ordem = NULL; 
        return;
    }
    else if (tail[0] == jogo) {
        if (tail[0] -> last_ordem == head[0]) {
            head[0] -> next_ordem = NULL;
            tail[0] = NULL;
            return;
        }
        tail[0] = tail[0] -> last_ordem;
        tail[0] -> next_ordem = NULL;
        return;
    }
    jogo -> last_ordem -> next_ordem = jogo -> next_ordem;
    jogo -> next_ordem -> last_ordem = jogo -> last_ordem;
    return;
}

/*-------------------------- Funcoes Principais --------------------------------------*/

/* verifica se ja existe uma jogo com o nome introduzido, caso nao haja adiciona 
alfabeticamente na fila da hash correta e adiciona no fim da fila de jogos */
void novo_jogo(int NL,ptr_jogo* h_jogo,ptr_equipa* h_equipa,int j,int e,
ptr_jogo* head_jogo, ptr_jogo* tail_jogo, ptr_equipa* head_equipa, ptr_equipa* tail_equipa) {
    
    int h_indice_e,h_indice_j,score1,score2;
    char nome_j[1024],n_equipa1[1024],n_equipa2[1024];
    ptr_equipa p_equipa1, p_equipa2;
    ptr_jogo ptr_j,aux;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome_j, n_equipa1, n_equipa2, &score1, &score2);

    ptr_j = (ptr_jogo) malloc(sizeof(jogo));

    ptr_j -> nome = copia_string(nome_j);
    h_indice_j = hash(ptr_j ->nome,j);
    aux = percorre_fila (h_jogo[h_indice_j],ptr_j->nome);

    /* verifica se o jogo ja existe */
    if(h_jogo[h_indice_j] != NULL && aux != NULL) {
        printf("%d Jogo existente.\n",NL);
        free_jogo(ptr_j);
        return;
    }
    h_indice_e = hash(n_equipa1,e);
    p_equipa1 = devolve_ptr_e (h_equipa[h_indice_e],n_equipa1);
    
    if (p_equipa1 == NULL) {
        printf("%d Equipa inexistente.\n",NL);
        free_jogo(ptr_j);
        return;
    }
    ptr_j -> equipa1 = p_equipa1;
    
    h_indice_e = hash(n_equipa2,e);
    p_equipa2 = devolve_ptr_e (h_equipa[h_indice_e],n_equipa2);
    if(p_equipa2 == NULL){
        printf("%d Equipa inexistente.\n",NL);
        free_jogo(ptr_j);
        return;
    }
    ptr_j -> equipa2 = p_equipa2;
    ptr_j -> score1 = score1;
    ptr_j -> score2 = score2;
    ptr_j -> next = NULL;
    ptr_j -> next_ordem = NULL;
    ptr_j -> last = NULL;
    ptr_j -> last_ordem = NULL;

    if (h_jogo[h_indice_j] == NULL) {
        h_jogo[h_indice_j] = ptr_j;
        add_jogo_lista(head_jogo,tail_jogo,ptr_j);
        if (score1 < score2) {
            ptr_j -> equipa2 -> jogos_ganhos++;
            altera_fila(head_equipa,tail_equipa,ptr_j -> equipa2,1);
        }
        else if (score1 > score2) {
            ptr_j -> equipa1 ->jogos_ganhos++;
            altera_fila(head_equipa,tail_equipa,ptr_j -> equipa1,1);
        }
        return;
    }

/*No caso de so ter um elemento*/
else if (h_jogo[h_indice_j] != NULL && h_jogo[h_indice_j] -> next == NULL) {
    /*o jogo inserido vem depois do primeiro*/
        if (strcmp(h_jogo[h_indice_j]->nome,ptr_j ->nome)<0 ){
            ptr_j -> last = h_jogo[h_indice_j];
            h_jogo[h_indice_j] -> next = ptr_j;
            add_jogo_lista(head_jogo,tail_jogo,ptr_j);
            if (score1 < score2) {
            ptr_j -> equipa2 -> jogos_ganhos++;
            altera_fila(head_equipa,tail_equipa,ptr_j -> equipa2,1);
            }
            else if (score1 > score2) {
            ptr_j -> equipa1 ->jogos_ganhos++;
            altera_fila(head_equipa,tail_equipa,ptr_j -> equipa1,1);
            }
            return;
        }
        /*o jogo inserido vem antes do primeiro*/
        else if (strcmp(h_jogo[h_indice_j]->nome,ptr_j ->nome)>0){
            h_jogo[h_indice_j] -> last = ptr_j;
            ptr_j -> next = h_jogo[h_indice_j];
            h_jogo[h_indice_j] = ptr_j;
            add_jogo_lista(head_jogo,tail_jogo,ptr_j);
            if (score1 < score2) {
            ptr_j -> equipa2 -> jogos_ganhos++;
            altera_fila(head_equipa,tail_equipa,ptr_j -> equipa2,1);
            }
            else if (score1 > score2) {
            ptr_j -> equipa1 ->jogos_ganhos++;
            altera_fila(head_equipa,tail_equipa,ptr_j -> equipa1,1);
            }
            return;
        }
    }
    /* caso o primeiro seja maior que o jogo inserido*/
    else if (strcmp(h_jogo[h_indice_j]->nome, ptr_j->nome)>0) {
            h_jogo[h_indice_j] -> last = ptr_j;
            ptr_j -> next = h_jogo[h_indice_j];
            h_jogo[h_indice_j] = ptr_j;
            add_jogo_lista(head_jogo,tail_jogo,ptr_j);
            if (score1 < score2) {
            ptr_j -> equipa2 -> jogos_ganhos++;
            altera_fila(head_equipa,tail_equipa,ptr_j -> equipa2,1);
            }
            else if (score1 > score2) {
            ptr_j -> equipa1 ->jogos_ganhos++;
            altera_fila(head_equipa,tail_equipa,ptr_j -> equipa1,1);
            }
            return;
    }
else {
        ptr_ord_jogo(h_jogo[h_indice_j],ptr_j);
        add_jogo_lista(head_jogo,tail_jogo,ptr_j);
        if (score1 < score2) {
            ptr_j -> equipa2 -> jogos_ganhos++;
            altera_fila(head_equipa,tail_equipa,ptr_j -> equipa2,1);
            }
        else if (score1 > score2) {
            ptr_j -> equipa1 ->jogos_ganhos++;
            altera_fila(head_equipa,tail_equipa,ptr_j -> equipa1,1);
        }
    }
}

/* verifica se na fila (obtida atraves da hash) existe um jogo com o nome inserido */
void procura_jogo(int NL,ptr_jogo* h_jogo,int j) {
    int h_indice;
    char nome_j[1024];
    ptr_jogo elem;
    scanf(" %[^:\n]",nome_j);

    h_indice = hash(nome_j, j);
    elem = h_jogo[h_indice];
    elem = percorre_fila(elem,nome_j);
    if (elem != NULL) {
        printf("%d %s %s %s %d %d\n",NL,elem->nome,elem->equipa1->nome,
        elem->equipa2->nome,elem->score1,elem->score2);
        return;
    }
    printf("%d Jogo inexistente.\n",NL);
    return;
}

/* verifica se o jogo existe, caso exista remove da fila de jogos, se apagar 
o jogo influenciar a quantidade de jogos_ganhos em alguma das equipas atualiza 
a fila de equipas e por fim remove da hashtable */
void r_jogo(int NL, ptr_jogo* h_jogo, ptr_jogo* head_jogo, ptr_jogo *tail_jogo,
int j, ptr_equipa*head_equipa, ptr_equipa*tail_equipa) { 
    
    ptr_jogo elem,anterior,proximo;
    int h_indice;
    char nome_j[1024];
    scanf(" %[^:\n]",nome_j);
    
    h_indice = hash(nome_j, j);
    elem = h_jogo[h_indice];
    elem = percorre_fila(elem,nome_j);
    if (elem != NULL) {
        /* se precisar de atualizar jogos_ganhos */
        if (elem -> score1 < elem -> score2) {
            elem -> equipa2 -> jogos_ganhos--;
            altera_fila(head_equipa,tail_equipa,elem -> equipa2,0);
        }
        else if (elem -> score1 > elem ->score2) {
            elem -> equipa1 ->jogos_ganhos--;
            altera_fila(head_equipa,tail_equipa,elem -> equipa1,0);
        }        
        /* caso seja o primeiro elemento da fila da hashtable*/
        if (elem == h_jogo[h_indice]) {
            if (elem -> next == NULL) {
                remove_jogo_lista(head_jogo,tail_jogo,elem);
                free_jogo(elem);
                h_jogo[h_indice] = NULL;
                return;
            }
            remove_jogo_lista(head_jogo,tail_jogo,elem);
            h_jogo[h_indice] = elem -> next;
            h_jogo[h_indice] -> last = NULL;
            free_jogo(elem);
            return;
        }
        /* caso seja o ultimo da fila */
        else if (elem -> next == NULL) {
            remove_jogo_lista(head_jogo,tail_jogo,elem);
            elem -> last -> next = NULL;
            free_jogo(elem);
            return;
        }
        remove_jogo_lista(head_jogo,tail_jogo,elem);
        anterior = elem -> last;
        proximo = elem -> next;
        anterior -> next = proximo;
        proximo -> last = anterior;
        free_jogo(elem);
        return;
    }
    printf("%d Jogo inexistente.\n",NL);
    return;
}

/* verifica se o jogo existe, caso exista e se a mudanca do score alterar
a quantidade de jogos_ganhos em alguma das equipas atualiza a fila de equipas */
void altera_score(int NL, ptr_jogo* h_jogo, int j,ptr_equipa* head, ptr_equipa* tail) {
    ptr_jogo elem;
    int h_indice,score1,score2;
    char nome_j[1024];
    scanf(" %[^:\n]:%d:%d",nome_j,&score1,&score2);
    
    h_indice = hash(nome_j, j);
    elem = h_jogo[h_indice];
    elem = percorre_fila(elem,nome_j);
    if (elem != NULL) {
        if (elem -> score1 == elem -> score2) {
            if (score1 > score2) {
                elem -> equipa1 -> jogos_ganhos++;
                altera_fila(head,tail,elem->equipa1,1);
            }
            else if (score1 < score2) {
                elem -> equipa2 -> jogos_ganhos++;
                altera_fila(head,tail,elem->equipa2,1);
            }
        }
        else if (elem -> score1 > elem-> score2) {
            if (score1 == score2) {
                elem -> equipa1 -> jogos_ganhos--;
                altera_fila(head,tail,elem->equipa1,0);
            }
            else if (score1 < score2) {
                elem -> equipa1 -> jogos_ganhos--;
                altera_fila(head,tail,elem->equipa1,0);
                elem -> equipa2 -> jogos_ganhos++;
                altera_fila(head,tail,elem->equipa2,1);
            }
        }
        else if (elem-> score1 < elem -> score2) {
            if (score1 == score2) {
                elem -> equipa2 -> jogos_ganhos--;
                altera_fila(head,tail,elem->equipa2,0);
            }
            else if (score1 > score2) {
                elem -> equipa2 -> jogos_ganhos--;
                altera_fila(head,tail,elem->equipa2,0);
                elem->equipa1 ->jogos_ganhos++;
                altera_fila(head,tail,elem->equipa1,1);
            }
        }
        elem -> score1 = score1;
        elem -> score2 = score2;
        return;
    }

    printf("%d Jogo inexistente.\n",NL);
    return;
}

/* lista todos os jogos da fila de jogos */
void lista_jogos (int NL, ptr_jogo* head) {
    ptr_jogo elem = head[0];
    if (head[0] == NULL) return;
    while (elem != NULL) {
        printf("%d %s %s %s %d %d\n",NL,elem -> nome, elem -> equipa1 -> nome, elem -> equipa2 -> nome,elem -> score1,elem -> score2);
        elem = elem -> next_ordem;
    }
    return;
}