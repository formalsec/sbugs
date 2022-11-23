#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"
#include "sistema.h"


/*hash table onde guardo o as equipas e o numero de vitorias de cada equipa*/

/*Inicializa a hash table onde vou guardar as equipas
 e o numero de vitorias de cada equipa.*/
sistema inicializa_sistema(sistema st1, int m) {
    int i; 
    st1=(sistema)can_fail_malloc(sizeof(struct sis));
    st1->tamanho=m;
    st1->elementos=0;
    st1->v = (sist*)can_fail_malloc(st1->tamanho*sizeof(sist));
    /*inicializo tudo a NULL*/
    for (i = 0; i < m; i++){
        st1->v[i] = NULL; 
    }
    return st1;
}

/*Liberta toda a memoria ocupada pela hash table.*/
sistema destroi_sistema(sistema st){
    int i;
    for (i=0; i<st->tamanho; i++){
        if (st->v[i]!=NULL){
            free(st->v[i]->equipa);
            free(st->v[i]);
        }
    }
    free(st->v);
    free(st);
    return st;
}

/*Funcao auxiliar da funcao re_hash.*/
sistema insere_eq(sistema st, char *nome, int ganhos){
    int i;
    i=hash(nome, st->tamanho);
    while (st->v[i]!=NULL){
        i = (i+1) % st->tamanho;
    }
    st->v[i] = (sist)can_fail_malloc(sizeof(struct no));
    st->v[i]->ganhos = ganhos;
    st->v[i]->equipa =(char*)can_fail_malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(st->v[i]->equipa, nome);
    return st;
}

/*Fucao auxiliar da funcao insere_equipa. Insere todos os elementos
da hash antiga numa nova mas com o dobro do tamanho.*/
sistema re_hash(sistema st, char *nome, int ganhos){
    sistema st1=NULL;
    int i;
    /*a nova hash table e inicializada com o dobro do tamanho*/
    st1=inicializa_sistema(st1, st->tamanho*2);
    st1->elementos=st->elementos;
    /*os elemenotos da hash antiga sao inseridos na nova*/
    for (i=0; i<st->tamanho; i++){
        if (st->v[i]!=NULL){
            st1=insere_eq(st1, st->v[i]->equipa, st->v[i]->ganhos);
        }
    }
    st1=insere_eq(st1, nome, ganhos);
    /*toda a memoria associada a hash antiga e libertada*/
    st=destroi_sistema(st);
    return st1;
}

/*Insere uma nova equipa na hash table e caso o numero 
de elementos seja metade do tamanho da hash aumenta o seu
tamanho para o dobro.*/
sistema insere_equipa(sistema st, char*name, int ganhos) {
    st->elementos+=1;
    /*caso o numero de elementos seja metade do tamanho
    o tamanho da hash passa para o dobro*/
    if (2*st->elementos>=st->tamanho){
        st=re_hash(st, name, ganhos);
        return st;
    }
    /*caso contrario a equipa e nserida na hash*/
    st=insere_eq(st, name, ganhos);
    return st;
}

/*Averigua se existe alguma equipa com o nome nome na hash table.
Caso exista retorna 1 e caso contrario retorna 0.*/
int pertence_equipa(sistema st1, char *name){
    int i;
    i=hash(name, st1->tamanho);
    while (st1->v[i] != NULL){
        if (strcmp(st1->v[i]->equipa, name)==0){
            return 1;
        }
        else{
            i = (i+1) % st1->tamanho;
        }
    }
    return 0;
}

/*Averigua qual das equipas, equipa1 e equipa2, tem um score mais elevado, 
e caso isso aconteca retorna a equipa vencedora.*/
char *vencedor(char *equipa1, char *equipa2, int score1, int score2){
    char *vencedor;
    /*caso a equipa1 seja a vencedora*/
    if (score1>score2){
        vencedor=(char*)can_fail_malloc(sizeof(char)*(strlen(equipa1)+1));
        strcpy(vencedor, equipa1);
        return vencedor;
    }
    /*caso a equipa2 seja a vencedora*/
    else if (score1<score2){
        vencedor=(char*)can_fail_malloc(sizeof(char)*(strlen(equipa2)+1));
        strcpy(vencedor, equipa2);
        return vencedor;
    }
    /*caso as equipas empatem*/
    vencedor=(char*)can_fail_malloc(sizeof(char));
    return vencedor;
}

/*Decrementa o numero de vitorias da equipa vencedor.*/
sistema decrementa_jogos_ganhos(sistema st, char *vencedor){
    int e2=hash(vencedor, st->tamanho);
    while (st->v[e2] != NULL){
        if (strcmp(st->v[e2]->equipa, vencedor)==0){
            st->v[e2]->ganhos-=1;
            free(vencedor);
            return st;
        }
        else{
            e2 = (e2+1) % st->tamanho;
        }
    }
    return st;
}

/*Incrementa o numero de vitorias da equipa vencedor.*/
sistema incrementa_jogos_ganhos(sistema st, char *vencedor){
    int e2=hash(vencedor, st->tamanho);
    while (st->v[e2] != NULL){
        if (strcmp(st->v[e2]->equipa, vencedor)==0){
            st->v[e2]->ganhos+=1;
            free(vencedor);
            return st;
        }
        else{
            e2 = (e2+1) % st->tamanho;
        }
    }
    return st;
}


/*Averigua se com a alteracao do score se altera o numero de vitorias 
de alguma equipa e em caso afirmativo altera esse numero.*/
sistema atualiza_vitoria(sistema st, jogo st1, char *nome, int score1, int score2){
    char *vencedor1;
    char *vencedor2;
    int e2;
    e2 = hash(nome,st1->tamanho);
    /*caso com os novos scores as equipas empatem*/
    if (score1==score2){
        while (st1->v[e2] != NULL){
            /*caso as equipas antes tambem tivessem empatado o numero de jogos ganhos nao se altera*/
            if (strcmp(st1->v[e2]->nome, nome)==0 && st1->v[e2]->eliminado==0){
                if (st1->v[e2]->score1==st1->v[e2]->score2){
                    return st;
                }
                /*caso contrario o numero de vitorias do vencedor com os novos scores e incrementado*/
                vencedor1=vencedor(st1->v[e2]->equipa1,st1->v[e2]->equipa2, st1->v[e2]->score1, st1->v[e2]->score2);
                st=decrementa_jogos_ganhos(st, vencedor1);
                return st;
            }
            else{
                e2 = (e2+1) % st1->tamanho;
            }
        }
    }
    /*caso com os novos scores haja um vencedor*/
    e2 = hash(nome,st1->tamanho);
    while (st1->v[e2] != NULL){
        if (strcmp(st1->v[e2]->nome, nome)==0 && st1->v[e2]->eliminado==0){
            /*caso anteriormente houvesse um empate nesse jogo o numero de vitorias
             da equipa que fica agora a ganhar e incrementado*/
            if (st1->v[e2]->score1==st1->v[e2]->score2){
                vencedor2=vencedor(st1->v[e2]->equipa1,st1->v[e2]->equipa2, score1, score2);
                st=incrementa_jogos_ganhos(st, vencedor2);
                return st;
            }
            /*caso anteriormente tambem houvesse um vencedor*/
            /*vencedor antes da alteracao do score*/
            vencedor1=vencedor(st1->v[e2]->equipa1,st1->v[e2]->equipa2, st1->v[e2]->score1, st1->v[e2]->score2);  
            /*vencedor depois da alteracao do score*/
            vencedor2=vencedor(st1->v[e2]->equipa1,st1->v[e2]->equipa2, score1, score2); 
            break;
        }
        else{
            e2 = (e2+1) % st1->tamanho;
        }
    }
    /*se o vencedor antes e depois da alteracao do score 
    for o mesmo o numero de vitorias nao e alterado*/
    if (strcmp(vencedor1, vencedor2)==0){
        free(vencedor1);
        free(vencedor2);
        return st;
    }
    /*caso contrario o numero de vitorias do novo vencedor e 
    incrementado e o numero de vitorias do antigo vencedor e 
    decrementado*/
    st=incrementa_jogos_ganhos(st, vencedor2);
    st=decrementa_jogos_ganhos(st, vencedor1);
    return st;
}


/*Verifica se com a remocao de um jogo se altera o numero de vitorias 
de alguma equipa e em caso afirmativo altera esse numero.*/
sistema elimina_vitoria(sistema st, jogo st1, char *nome){
    char *vencedor1;
    int e2;
    e2 = hash(nome,st1->tamanho);
    while (st1->v[e2] != NULL){
        if (strcmp(st1->v[e2]->nome, nome)==0 && st1->v[e2]->eliminado==0){
            /*caso nao houvesse vencedor o numero de vitorias nao se altera*/
            if (st1->v[e2]->score1==st1->v[e2]->score2){
                return st;
            }
            /*vencedor antes do jogo ser removido*/
            vencedor1=vencedor(st1->v[e2]->equipa1,st1->v[e2]->equipa2, st1->v[e2]->score1, st1->v[e2]->score2); 
            break;
        }
        else{
            e2 = (e2+1) % st1->tamanho;
        }
    }
    st=decrementa_jogos_ganhos(st, vencedor1);
    return st;
}

/*Atualiza o numero de vitorias das equipas presentes
no novo jogo inserido na hash table dos jogos.*/
sistema insere_vitoria(sistema st, char *equipa1,char *equipa2, int score1, int score2){  
    char *vencedor1;
    /*caso nao haja vencedor o numero de vitorias nao se altera*/
    if (score1==score2){
        return st;
    }
    vencedor1=vencedor(equipa1, equipa2, score1, score2);
    st=incrementa_jogos_ganhos(st, vencedor1);
    return st;
}

/*Retorna o numero de jogos ganhos da equipanome.*/
int jogos_ganhos(sistema st1, char *name){
    int i, ganhos;
    i=hash(name, st1->tamanho);
    while (st1->v[i] != NULL){
        if (strcmp(st1->v[i]->equipa, name)==0){
            ganhos=st1->v[i]->ganhos;
            return ganhos;
        }
        else{
            i = (i+1) % st1->tamanho;
        }
    }
    return 0;
}

/*Funcao auxiliar do algoritmo de ordenacao qsort.*/
int comparastr(const void *pa, const void *pb){
    char **v1, **v2;
    v1=(char**) pa;
    v2=(char**) pb;
    return strcmp(*v1,*v2);
}

/*Averigua quais as equipas com mais vitorias e faz print 
dessas equipas por ordem lexicografica.*/
void tabela(sistema st, int nl){
    int i, e;
    int cont=0, maior=0, n=0;
    char **vencedoras;
    /*ciclo que determina qual o maior numero de vitorias 
    e o numero de equipas com esse numero de vitorias*/
    for (e=0; e<st->tamanho; e++){
        if (st->v[e]!=NULL){
            i=st->v[e]->ganhos;
            if (i>maior){
                maior=i;
                n=1;
            }
            else if (i==maior){
                n+=1;
            }
        }
    }
    if (n==0){
        return;
    }
    vencedoras=(char**)can_fail_malloc(sizeof(char*)*n);
    /*as equipas vencedoras sao colocadas no vetor de ponteiros vencedoras*/
    for (e=0; e<st->tamanho; e++){
        if (st->v[e]!=NULL){
            i=st->v[e]->ganhos;
            if (i==maior){
                vencedoras[cont]=(char*)can_fail_malloc(sizeof(char)*(strlen(st->v[e]->equipa)+1));
                strcpy(vencedoras[cont],st->v[e]->equipa);
                cont+=1;
            }
        }
    }
    qsort(vencedoras, n, sizeof(char*), comparastr);
    printf("%d Melhores %d\n", nl, maior);
    for (cont=0; cont<n; cont++){
        printf("%d * %s\n", nl, vencedoras[cont]);
        free(vencedoras[cont]);
    }
    free(vencedoras);
    return;
}
