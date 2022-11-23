#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "estruturas.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*Funcao responsavel por adicionar uma equipa, uso da funcao SearchEquipa para verificar a existencia
da equipa se ja existir a funcao retorna erro dizendo que ja existe essa equipa*/
void cmd_A(char * nome, equipa * HTequipa, int NL){
    if(SearchEquipa(nome,HTequipa) == NULL) InsertEquipa(nome, HTequipa); /* insercao da equipa na hash table de equipas*/
    else printf("%d Equipa existente.\n", NL);
}

/*Funcao responsavel por adicionar um jogo, uso das funcoes SearchJogo e SearchEquipa para verificar a exitencia do jogo
e de ambas as equipas respetivamente, se o jogo ja exitir retorna erro da existencia do jogo 
e se nao existir uma das equipas retorna erro dizendo que nao existe a/as equipas*/
int cmd_a(char * nome, char * eq1, char * eq2, int sc1, int sc2, jogo * HTjogo, equipa * HTequipa, int NL, int id){
    if(SearchJogo(nome, HTjogo) == NULL){
        if((SearchEquipa(eq1,HTequipa) != NULL) && (SearchEquipa(eq2, HTequipa) != NULL)){
            InsertJogo(nome,eq1,eq2,sc1,sc2,HTjogo,id); /*insercao do jogo na hash table de jogos*/
            if(sc1 > sc2){ /* verifica a equipa vencedora*/
                equipa aux = SearchEquipa(eq1,HTequipa); /* procura a equipa1 e incrementa o numero de vitorias*/
                aux->vitorias += 1;
            }else if (sc2 > sc1){
                equipa aux = SearchEquipa(eq2,HTequipa); /*procura a equipa2 e incrementa o numero de vitorias*/
                aux->vitorias += 1;
            }return 1;
        }else printf("%d Equipa inexistente.\n", NL);
    }else printf("%d Jogo existente.\n", NL);
    return 0;
}

/*Funcao responsavel por procurar um jogo e imprimir o respetivo, se o jogo nao existir retorna erro mostrando
que o jogo nao existe*/
void cmd_p(char * nome, jogo * HTjogo, int NL){
    jogo aux = SearchJogo(nome, HTjogo); /*uso da funcao SearchJogo para procurar o respetivo jogo*/
    if(aux) printf("%d %s %s %s %d %d\n",NL, aux->nome, aux->eq1, aux->eq2, aux->sc1, aux->sc2);
    else printf("%d Jogo inexistente.\n",NL);
    
}

/*Funcao responsavel por procurar uma equipa e imprimir a respetiva, se a equipa nao existir retorna erro mostrando
que a equipa nao existe*/
void cmd_P(char * nome, equipa * HTequipa, int NL){
    equipa aux = SearchEquipa(nome, HTequipa);/*uso da funcao SearchEquipa para procurar a respetiva equipa*/
    if(aux) printf("%d %s %d\n",NL, aux->nome, aux->vitorias);
    else printf("%d Equipa inexistente.\n", NL);
}

/*Funcao responsavel por listar os jogos por ordem de insercao no programa*/
void cmd_l(jogo * HTjogo, int NL, int id){
    int i,j;
    jogo aux;
    for(i = 0; i < id; i++){ /*ciclo usado para iterar sobre o numero de jogos existentes*/
        for(j = 0; j < TABLE_SIZE; j++){ /*ciclo usado para percorrer a hash table dos jogos*/
            for(aux = HTjogo[j]; aux != NULL; aux = aux->nextJ){
                if(aux->id == i){ /*se o id do jogo for igual ao numero do jogo que se quere imprime o jogo*/
                    printf("%d %s %s %s %d %d\n", NL, aux->nome, aux->eq1, aux->eq2, aux->sc1, aux->sc2);
                    break; /*assim que encontrado o jogo salta para o proximo id de jogo*/
                }
            }  
        }
    }
}

/*Funcao responsavel por eliminar um jogo da hash table e acertar o numero de vitorias da equipa que tenha ganho anteriormente,
caso o jogo nao exista a funcao retorna erro dizendo que o jogo nao existe*/
void cmd_r(char * nome, jogo * HTjogo, equipa * HTequipa, int NL){
    int i = Hash(nome, TABLE_SIZE); /*descobre o indice da hash table em que o jogo esta guardado*/
    jogo aux = SearchJogo(nome, HTjogo); /*procura o jogo que e para remover*/
    equipa temp;
    if(aux){ 
        if(aux->sc1 > aux->sc2){ /*verifica a equipa vencedora do jogo antes de ser apagado*/
            temp = SearchEquipa(aux->eq1, HTequipa); /*no caso da equipa1 procura a equipa e decrementa o numero de vitorias*/
            temp->vitorias -= 1;
        }else if( aux->sc2 > aux->sc1){
            temp = SearchEquipa(aux->eq2, HTequipa);/*no caso da equipa2 procura a equipa e descrementa o numero de vitorias*/
            temp->vitorias -= 1;
        }HTjogo[i] = RemoveJogo(HTjogo[i], nome);/*uso da funcao RemoveJogo para remover o jogo e devolve a hash table ja modificada*/
    } else printf("%d Jogo inexistente.\n", NL);
}

/*Funcao responsavel por alterar o score a um jogo e modificar o numero de vitorias dependendo do resultado modificado,
retorna erro se o jogo nao existir*/
void cmd_s(char * nome, jogo *HTjogo, int sc1, int sc2, equipa * HTequipa, int NL){
    jogo aux = SearchJogo(nome, HTjogo); /*procura o jogo que vai ser alterado*/
    equipa eq1,eq2;
    if(aux){
        eq1 = SearchEquipa(aux->eq1, HTequipa);/*procura as equipas do jogo*/
        eq2 = SearchEquipa(aux->eq2, HTequipa);
        if(sc1 > sc2){ /*se for a equipa2 que passe a ganhar*/
           if(aux->sc1 == aux->sc2) eq1->vitorias += 1; /*se antes era empate incrementa o numero de vitorias da equipa1*/
            else if(aux->sc1 < aux->sc2){ /*se ganhava a equipa2 decrementa as suas vitorias e incrementa as da equipa1*/
                eq2->vitorias -=1;
                eq1->vitorias += 1;
            }
        }else if(sc2 > sc1){ /*se for a equipa2 que passe a ganhar*/
            if(aux->sc1 == aux->sc2) eq2->vitorias += 1; /*se antes era empate incrementa o numero de vitorias da equipa2*/
            else if(aux->sc2 < aux->sc1){ /*se ganhava a equipa1 decrementa as suas vitorias e incrementa as da equipa2*/
                eq1->vitorias -=1;
                eq2->vitorias += 1;
            }
        }else if(sc1 == sc2){ /*se antes era empate, decrementa o numero de vitorias da equipa que ganhou anteriormente*/
            if(aux->sc1 > aux->sc2) eq1->vitorias -=1;
            else if(aux->sc2 > aux->sc1) eq2->vitorias -=1;
        }aux->sc1 = sc1; /*modifica os scores de ambas as equipas*/
         aux->sc2 = sc2;
    }else printf("%d Jogo inexistente.\n", NL);
}

/*Funcao responsavel por listar as equipas com o maior numero de vitorias por ordem lexicografica se existir mais que 1 equipa*/
void cmd_g(equipa * HTequipa, int NL){
    int i, maior = 0;
    equipa aux, lista = NULL;
    for(i = 0; i < TABLE_SIZE; i++){ /*ciclo para obtencao do maior numero de vitorias*/
        for(aux = HTequipa[i]; aux != NULL; aux = aux->nextE){
            if(aux->vitorias >= maior) maior = aux->vitorias;
        }
    }
    for(i = 0; i < TABLE_SIZE; i++){ /*ciclo usado para filtrar as equipas que tem o maior numero de vitorias*/
        for(aux = HTequipa[i]; aux != NULL; aux = aux->nextE){
            if(aux->vitorias == maior){
                lista = ListaEquipas(lista, aux->nome, aux->vitorias);/*uso da funcao ListaEquipas para listar as equipas por ordem*/                                                                         
            }                           
        }
    }
    if(lista){ /*se a lista nao for vazia imprime as equipas*/
        printf("%d Melhores %d\n", NL, maior);
        for(aux = lista; aux != NULL; aux = aux->nextE)
            printf("%d * %s\n", NL, aux->nome);
        FreeListE(lista); /*liberta a memoria usada pela lista*/
    }
}