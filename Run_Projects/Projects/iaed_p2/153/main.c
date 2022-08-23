#include "proj2.h"

/*Funcao principal que inicializa as cabecas das listas a NULL, o contador
de linha a 1 e que le o caracter no inicio de cada linha do input para
determinar qual o comando a ser usado*/
int main(){
    /*Variavel headjogo usada como cabeca da lista dos jogos*/
    linkjogo aux_jogo,aux_jogo2,headjogo = NULL;
    /*Variavel headequipa usada como cabeca da lista das equipas*/
    linkequipa aux_equipa,aux_equipa2,headequipa = NULL;
    int contlinha=1;    /*Variavel usada como contador de linhas do input*/
    int c;
    c=getchar();    /*Variavel que armazena o primeiro caracter do input*/
    while(c!=EOF && c!='\n'){
        if(c=='a'){
            getchar();
            headjogo=a(headjogo,headequipa,contlinha);
        }
        if(c=='A'){
            getchar();
            headequipa=A(headequipa,contlinha);
        }
        
        if(c=='s'){
            getchar();
            headjogo=s(headjogo,contlinha);
        }

        if(c=='r'){
            getchar();
            headjogo=r(headjogo,contlinha);
        }

        if(c=='P'){
            getchar();
            P(headjogo,headequipa,contlinha);
        }

        if(c=='p'){
            getchar();
            p(headjogo,contlinha);
        }

        if(c=='l'){
            l(headjogo,contlinha);
        }

        if(c=='g'){
            g(headjogo,headequipa,contlinha);
        }
        
        if(c=='x'){
            for(aux_jogo=headjogo;aux_jogo != NULL;aux_jogo=aux_jogo2){
                aux_jogo2=aux_jogo->next;
                headjogo=removeJogo(headjogo,aux_jogo->nome);
            }
            for(aux_equipa=headequipa;aux_equipa != NULL;aux_equipa=aux_equipa2){
                aux_equipa2=aux_equipa->next;
                headequipa=removeEquipa(headequipa,aux_equipa->nome);
            }
            break;
        }
        contlinha++;
        c=getchar();
    }
    return 0;
}