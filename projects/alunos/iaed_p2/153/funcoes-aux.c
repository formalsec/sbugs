#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "proj2.h"

/*Funcao auxiliar que cria um novo nodo de jogo, alocando a memoria necessaria*/
linkjogo NEWjogo(char *nome,char *equipa1,char *equipa2,int score1,int score2){
    linkjogo x = (linkjogo) can_fail_malloc(sizeof(struct jogo));
    x->nome=(char*) can_fail_malloc(sizeof(char)*(strlen(nome)+1));
    x->equipa1=(char*) can_fail_malloc(sizeof(char)*(strlen(equipa1)+1));
    x->equipa2=(char*) can_fail_malloc(sizeof(char)*(strlen(equipa2)+1));
    strcpy(x->nome,nome);
    strcpy(x->equipa1,equipa1);
    strcpy(x->equipa2,equipa2);
    x->score1=score1;
    x->score2=score2;
    x->next=NULL;
    return x;
}

/*Funcao auxiliar que cria um novo nodo de qeuipa, alocando memoria necessaria*/
linkequipa NEWequipa(char *nome_equipa){
    linkequipa e = (linkequipa) can_fail_malloc(sizeof(struct equipa));
    e->nome = (char*) can_fail_malloc(sizeof(char)*(strlen(nome_equipa)+1));
    strcpy(e->nome,nome_equipa);
    e->next = NULL;
    return e;
}

/*Funcao que insere um novo jogo no fim da lista interligada de jogos*/
linkjogo insertEndJogo(linkjogo headjogo,char *nome,char *equipa1,
char *equipa2,int score1,int score2){
    linkjogo x;
    if(headjogo == NULL){
        return NEWjogo(nome,equipa1,equipa2,score1,score2);
    }
    for(x = headjogo;x->next != NULL;x = x->next){
        ;
    }
    x->next = NEWjogo(nome,equipa1,equipa2,score1,score2);
    return headjogo;
}

/*Funcao que insere uma nova equipa no fim da lista interligada de equipas*/
linkequipa insertEndEquipa(linkequipa headequipa,char *nome_equipa){
    linkequipa e;
    if(headequipa == NULL){
        return NEWequipa(nome_equipa);
    }
    for(e=headequipa;e->next != NULL;e=e->next){
        ;
    }
    e->next=NEWequipa(nome_equipa);
    return headequipa;
}

/*Funcao que remove um certo jogo da lista atraves do nome dado e liberta
a memoria alocada para tal jogo*/
linkjogo removeJogo(linkjogo headjogo,char *nome_jogo){
    linkjogo prev,t;
    for(t=headjogo,prev=NULL;t != NULL;prev=t,t=t->next){
        if(strcmp(t->nome,nome_jogo)==0){
            if(t == headjogo){
                headjogo=t->next;
            }
            else{
                prev->next=t->next;
            }
            free(t->nome);
            free(t->equipa1);
            free(t->equipa2);
            free(t);
            break;
        }
    }
    return headjogo;
}

/*Funcao que remove uma equipa da lista de equipas pelo nome da equipa
e liberta a memoria alocada previamente*/
linkequipa removeEquipa(linkequipa headequipa,char *nome_equipa){
    linkequipa prev,t;
    for(t=headequipa,prev=NULL;t != NULL;prev=t,t=t->next){
        if(strcmp(t->nome,nome_equipa)==0){
            if(t == headequipa){
                headequipa=t->next;
            }
            else{
                prev->next=t->next;
            }
            free(t->nome);
            free(t);
            break;
        }
    }
    return headequipa;
}

/*Funcao auxiliar que executa a procura de uma determinada equipa
a partir do nome e imprime o seu nome e o numero de jogos ganhos*/
void procuraEquipa(linkjogo headjogo,char *nome,int contlinha){
    linkjogo aux;
    int soma=0;   /*variavel que armazena o numero de jogos ganhos da equipa*/
    for(aux=headjogo;aux != NULL;aux=aux->next){
        if(strcmp(aux->equipa1,nome)==0){
            if(aux->score1 > aux->score2){
                soma++;
            }
        }
        else if(strcmp(aux->equipa2,nome)==0){
            if(aux->score2 > aux->score1){
                soma++;
            }
        }
    }
    printf("%d %s %d\n",contlinha,nome,soma);
}

/*Funcao auxiliar usada como funcao de comparaco para o qsort*/
int compare(const void *p1,const void *p2){
    char **a,**b;
    a=(char**) p1;
    b=(char**) p2;
    return strcmp(*a,*b);
}

/*Funcao auxiliar para listar as equipas com mais jogos ganhos
por ordem lexicografica*/
void listaGanhos(linkjogo headjogo,linkequipa headequipa,int contlinha,
int max_g,int quant_g){
    linkjogo jogo;
    linkequipa equipa;
    /*Variavel soma  para armazenar o numero de vitorias de uma certa equipa
    e depois comparar com max, a qual e uma variavel que contem o maior
    numero de jogos ganhos; vaiavel quant usada para saber quantas equipas
    tem o numero de jogos ganhos em max*/
    int i=0,soma=0,max=max_g,quant=quant_g;
    char buffer[maxchar];   /*Usado para armazenar o nome de uma equipa*/
    char** equipas;     /*Contem ponteiros para cada um do nome das equipas*/
    equipas=(char**)can_fail_malloc(sizeof(char*)*quant);
    if(headjogo == NULL){
        for(equipa=headequipa;equipa != NULL;equipa=equipa->next){
            strcpy(buffer,equipa->nome);
            equipas[i]=(char*)can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
            strcpy(equipas[i],buffer);
            i++;
        }
    }
    else{
        for(equipa=headequipa;equipa != NULL;equipa=equipa->next){
            for(jogo=headjogo;jogo != NULL;jogo=jogo->next){
                if(strcmp(equipa->nome,jogo->equipa1)==0 && jogo->score1 > jogo->score2){
                    soma++;
                }
                else if(strcmp(equipa->nome,jogo->equipa2)==0 && jogo->score2 > jogo->score1){
                    soma++;
                }
            }
            if(soma==max){
                strcpy(buffer,equipa->nome);
                equipas[i]=(char*)can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
                strcpy(equipas[i],buffer);
                i++;
                soma=0;
            }
            else{
                soma=0;
            }
        }
    }
    qsort(equipas,quant,sizeof(char*),compare);
    printf("%d Melhores %d\n",contlinha,max);
    for(i=0;i<quant;i++){
        printf("%d * %s\n",contlinha,equipas[i]);
        free(equipas[i]);
    }
    free(equipas);
}