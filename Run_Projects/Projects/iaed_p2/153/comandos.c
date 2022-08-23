#include "proj2.h"

/*Funcao que adiciona um novo jogo ao sistema, atraves de uma lista interligada*/
linkjogo a(linkjogo headjogo,linkequipa headequipa,int contlinha){
    /*Variaveis usadas para armazenar os conteudos do input,neste caso, 
    nome do jogo, 2 nomes das equipas e 2 scores, um para cada equipa*/
    char nome[maxchar],equipa1[maxchar],equipa2[maxchar];
    int score1,score2,cont=0,cont1=0,cont2=0;
    linkjogo a;
    linkequipa b,c;
    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d\n",nome,equipa1,equipa2,&score1,&score2);
    if(headjogo != NULL){
        for(a=headjogo;a != NULL;a=a->next){
            if(strcmp(a->nome,nome)==0){
                cont++;
                break;
            }
        }
        if(cont == 1){
            printf("%d Jogo existente.\n",contlinha);
        }
        else{
            for(b=headequipa;b != NULL;b=b->next){
                if(strcmp(b->nome,equipa1)==0 || strcmp(b->nome,equipa2)==0){
                    cont1++;
                }
            }
            if(cont1 != 2){
                printf("%d Equipa inexistente.\n",contlinha);
            }
            else{
                headjogo=insertEndJogo(headjogo,nome,equipa1,equipa2,score1,score2);
            }
        }
    }
    else if(headequipa == NULL){
        printf("%d Equipa inexistente.\n",contlinha);
    }
    else if(headequipa != NULL){
        for(c=headequipa;c != NULL;c=c->next){
            if(strcmp(c->nome,equipa1)==0 || strcmp(c->nome,equipa2)==0){
                cont2++;
            }
        }
        if(cont2 != 2){
            printf("%d Equipa inexistente.\n",contlinha);
        }
        else{
            headjogo=insertEndJogo(headjogo,nome,equipa1,equipa2,score1,score2);
        }
    }
    return headjogo;
}

/*Funcao que adiciona uma equipa nova ao sistema atraves da adicao a uma lista
interligada de equipas*/
linkequipa A(linkequipa headequipa,int contlinha){
    linkequipa aux;
    char nome_equipa[maxchar];   /*Usado para armazenar o nome da equipa*/
    int cont=0;
    scanf("%[^:\n]\n",nome_equipa);
    if(headequipa == NULL){
        headequipa = insertEndEquipa(headequipa,nome_equipa);
    }
    else{
        for(aux=headequipa;aux != NULL;aux=aux->next){
            if(strcmp(aux->nome,nome_equipa)==0){
                cont++;
            }
        }
        if(cont>0){
            printf("%d Equipa existente.\n",contlinha);
        }
        else{
            headequipa = insertEndEquipa(headequipa,nome_equipa);
        }
    }
    return headequipa;
}

/*Funcao que altera o score de um jogo dado o nome*/
linkjogo s(linkjogo headjogo,int contlinha){
    linkjogo aux;
    char nome_jogo[maxchar];   /*Usado para guardar o nome do jogo*/
    int score1,score2,cont=0;   /*2 variaveis para guardar o novo score*/
    scanf("%[^:\n]:%d:%d\n",nome_jogo,&score1,&score2);
    for(aux=headjogo;aux != NULL;aux=aux->next){
        if(strcmp(nome_jogo,aux->nome)==0){
            cont++;
            break;
        }
    }
    if(cont != 1){
        printf("%d Jogo inexistente.\n",contlinha);
    }
    else{
        aux->score1 = score1;
        aux->score2 = score2;
    }
    return headjogo;
}

/*Funcao que apaga um jogo do sistema dado o nome e liberta a memoria
alocada para o jogo a remover*/
linkjogo r(linkjogo headjogo,int contlinha){
    linkjogo aux;
    char nome_jogo[maxchar];    /*Usado para guardar o nome do jogo*/
    int cont=0;
    scanf("%[^:\n]\n",nome_jogo);
    for(aux=headjogo;aux != NULL;aux=aux->next){
        if(strcmp(aux->nome,nome_jogo)==0){
            cont++;
            break;
        }
    }
    if(cont != 1){
        printf("%d Jogo inexistente.\n",contlinha);
    }
    else{
        headjogo = removeJogo(headjogo,nome_jogo);
    }
    return headjogo;
}

/*Funcao que procura uma equipa dado o nome e devolve o seu nome
e o numero de jogos ganhos*/
void P(linkjogo headjogo,linkequipa headequipa,int contlinha){
    linkequipa aux;
    char nome[maxchar];    /*Usado para armazenar o nome da equipa*/
    int cont=0;
    scanf("%[^:\n]\n",nome);
    for(aux=headequipa;aux != NULL;aux=aux->next){
        if(strcmp(aux->nome,nome)==0){
            cont++;
            break;
        }
    }
    if(cont != 1){
        printf("%d Equipa inexistente.\n",contlinha);
    }
    else{
        procuraEquipa(headjogo,nome,contlinha);
    }
}

/*Funcao que procura um jogo dado o nome e devolve o seu nome, o nome
das equipas envolvidas e o score do jogo*/
void p(linkjogo headjogo,int contlinha){
    linkjogo aux;
    char nome_jogo[maxchar];    /*Usado para armazenar o nome do jogo*/
    int cont=0;
    scanf("%[^:\n]\n",nome_jogo);
    for(aux=headjogo;aux != NULL;aux=aux->next){
        if(strcmp(aux->nome,nome_jogo)==0){
            cont++;
            break;
        }
    }
    if(cont != 1){
        printf("%d Jogo inexistente.\n",contlinha);
    }
    else{
        printf("%d %s %s %s %d %d\n",contlinha,nome_jogo,
        aux->equipa1,aux->equipa2,aux->score1,aux->score2);
    }
}

/*Funcao que lista todos os jogos no sistema, imprimindo para cada um
o seu nome, as equipas envolvidas e o score*/
void l(linkjogo headjogo,int contlinha){
    linkjogo aux;
    scanf("\n");
    if( headjogo == NULL){
        ;
    }
    else{
        for(aux=headjogo;aux != NULL;aux=aux->next){
            printf("%d %s %s %s %d %d\n",contlinha,aux->nome,
            aux->equipa1,aux->equipa2,aux->score1,aux->score2);
        }
    }
}

/*Funcao que lista as equipas que ganharam mais jogos por ordem lexicografica*/
void g(linkjogo headjogo,linkequipa headequipa,int contlinha){
    linkjogo jogo;
    linkequipa equipa;
    /*Variavel soma usada para ir armazenando o numero de vitorias de
    uma equipa; variavel max usada para armazenar o maior numero de vitorias;
    variavel quant usada para armazenar o numero de equipas que o numero
    de vitorias igual a max*/
    int soma=0,max=0,quant=1;
    scanf("\n");
    if(headequipa == NULL){
        ;
    }
    else if(headjogo == NULL){
        for(equipa=headequipa;equipa != NULL;equipa=equipa->next){
            quant++;
        }
        quant--;
        listaGanhos(headjogo,headequipa,contlinha,max,quant);
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
            if(soma>max){
                max=soma;
                soma=0;
                quant=1;
            }
            else if(soma==max){
                soma=0;
                quant++;
            }
            else{
                soma=0;
            }
        }
        listaGanhos(headjogo,headequipa,contlinha,max,quant);
    }
}