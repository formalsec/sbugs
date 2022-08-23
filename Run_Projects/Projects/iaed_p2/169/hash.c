#include "hash.h"

/* funcao que recebe uma string e um numero para o tamanho e 
   devolve o numero da posicao na hashtable */
int hash(char *v, int M){

    int h, a = 31415, b = 27183;
    for (h = 0; strcmp(v, "\0") != 0; v++, a = a*b % (M-1)){
        h = (a*h + *v) % M;
    }
    return h;
}

/* funcao que recebe um numero para o tamanho e inicializa a hastable */
link2* STinitE(int m){

    int i;
    link2 *hashtable = (link2*)malloc(m*sizeof(link2));
    for (i = 0; i < m; i++){
        hashtable[i] = NULL;
    } 
    return hashtable;
}

link1* STinitJ(int m){

    int i;
    link1 *hashtable = (link1*)malloc(m*sizeof(link1));
    for (i = 0; i < m; i++){
        hashtable[i] = NULL;
    } 
    return hashtable;
}

/* funcao auxiliar que recebe um buffer e cria um node onde guarda o nome da equipa */
link2 NEWE(char* buffer){

    link2 x = (link2)malloc(sizeof(struct node2));
    x->equipa = (char*)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(x->equipa, buffer);
    x->vitorias = 0;
    x->next = NULL;
    return x;
}

/* funcao auxiliar que recebe head e um nome e da return ao node */
link2 insertBeginE(link2 head, char* nome){

    link2 x = NEWE(nome);
    x->next = head;
    return x;
}

/* funcao que recebe um nome uma hashtable e um numero para o tamanho
   e que insere no inicio de uma certa posicao da hashtable o node */
link2 STinsertE(char* nome, link2 *hashtable, int m){

    int i = hash(nome, m);
    hashtable[i] = insertBeginE(hashtable[i], nome);
    return hashtable[i];
} 

/* funcao auxiliar que recebe head e um nome e que da return ao node com nome
   igual ao recebido caso exista */
link2 lookupE(link2 head, char* nome){
    
    link2 t;
    for(t = head; t != NULL; t = t->next){
        if(strcmp(t->equipa, nome) == 0){
            return t;
        }
    }
    return NULL;
}

/* funcao que recebe um nome uma hashtable e um numero para o tamanho e que da 
   return ao node da hashtable com o mesmo nome que o recebido caso existo */
link2 STsearchE(char* nome, link2 *hashtable, int m){

    int i = hash(nome, m);
    return lookupE(hashtable[i], nome);
}

/* funcao auxiliar que recebe tres buffers e dois numeros e devolve o node 
   onde esta guardado o nome do jogo os nomes das equipas e os scores do jogo */
link1 NEWJ(char* buffer1, char* buffer2, char* buffer3, int n, int m){

    link1 x = (link1)malloc(sizeof(struct node1)); 
    x->Jogo = (pJogo)malloc(sizeof(jogo));
    x->Jogo->nome = (char*)malloc(sizeof(char)*(strlen(buffer1)+1));
    strcpy(x->Jogo->nome, buffer1);
    x->Jogo->equipa1 = (char*)malloc(sizeof(char)*(strlen(buffer2)+1));
    strcpy(x->Jogo->equipa1, buffer2);
    x->Jogo->equipa2 = (char*)malloc(sizeof(char)*(strlen(buffer3)+1));
    strcpy(x->Jogo->equipa2, buffer3);
    x->Jogo->score1 = n;
    x->Jogo->score2 = m;
    x->next = NULL;
    return x;
}

/* funcao auxiliar que recebe head um nome duas equipas e dois scores e devolve o node */
link1 insertBeginJ(link1 head, char* nome, char* equipa1, char* equipa2, int score1, int score2){
    
    link1 x = NEWJ(nome, equipa1, equipa2, score1, score2);
    x->next = head;
    return x;
}

/* funcao que recebe um nome duas equipas dois scores uma hashtable e um numero
   para o tamanho e que insere no inicio de uma certa posicao da hashtable o node */
link1 STinsertJ(char* nome, char* equipa1, char* equipa2, int score1, int score2, link1 *hashtable, int m){

    int i = hash(nome, m);
    hashtable[i] = insertBeginJ(hashtable[i], nome, equipa1, equipa2, score1, score2);
    return hashtable[i];
} 

/* funcao auxiliar que recebe head e um nome e apaga o node contem o jogo */
link1 delete(link1 head, char* nome){
    
    link1 t, prev;
    for(t = head, prev = NULL; t != NULL; prev = t, t = t->next){
        if(strcmp(t->Jogo->nome, nome) == 0){
            if(t == head){
                head = t->next;
            }
            else{
                prev->next = t->next;
            }
            free(t->Jogo->nome);
            free(t->Jogo->equipa1);
            free(t->Jogo->equipa2);
            free(t->Jogo);
            free(t);
            break;
        }
    }
    return head;
}

/* funcao que recebe um nome uma hashtable e um numero para o tamanho que 
   apaga o node da hashtable dos jogos com nome igual ao que foi recebido */
void STdelete(char* nome, link1 *hashtable, int m){

    int i = hash(nome, m);
    hashtable[i] = delete(hashtable[i], nome);
}

/* funcao auxiliar que recebe head e um nome e que devolve o nome com nome
   igual ao que foi recebido caso exista */
link1 lookupJ(link1 head, char* nome){
    
    link1 t;
    for(t = head; t != NULL; t = t->next){
        if(strcmp(t->Jogo->nome, nome) == 0){
            return t;
        }
    }
    return NULL;
}

/* funcao que recebe um nome uma hashtable e um numero para o tamanho 
   e que devolve o node da hashtable que tem nome igual ao recebido */
link1 STsearchJ(char* nome, link1 *hashtable, int m){

    int i = hash(nome, m);
    return lookupJ(hashtable[i], nome);
}