#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comandos.h"
#include "estruturasAlgoritmos.h"

/* funcao auxiliar que aloca espaco para uma cadeia de caracteres e copia-a para la */
char* stringalloc(char *buff){
    char *new;
    if(buff == NULL) return NULL;
    new = (char*)malloc(sizeof(char)*(strlen(buff)+1));
    strcpy(new,buff);
    return new;
}

/* funcao auxiliar que cria um jogo ou uma equipa */
dados *novoDado(char *nomeBuff,char *eq1Buff,char *eq2Buff,int scr1,int scr2){
    dados *new;
    new = (dados*)malloc(sizeof(dados));
    new->nome = stringalloc(nomeBuff);
    new->eq1 = stringalloc(eq1Buff);
    new->eq2 = stringalloc(eq2Buff);
    new->scr[0] = scr1;
    new->scr[1] = scr2;
    return new;
}

/* os prototipos das funcoes anteriores nao foram colocados no ficheiro comandos.h pois estas apenas sao utilizadas neste
ficheiro */

/* funcao auxiliar que devolve o ponteiro para o vencedor de uma partida ou 
em caso de empate para NULLitem */
dados* vencedor(dados *eq1,dados *eq2,int scr1, int scr2){
    if(scr1==scr2) return NULLitem;
    return (scr1 > scr2 ? eq1 : eq2);
}

/* funcao "a" que adiciona um jogo ao sistema */
void a(tabela *jogos,tabela *equipas,int NL,lista *jogosL){
    char nomeBuff[TAM_BUFFER],eq1Buff[TAM_BUFFER],eq2Buff[TAM_BUFFER];
    int scr1,scr2;
    /* Ponteiros que apontam para onde vao ser guardados os dados lidos */
    dados *jogo,*eq1,*eq2;
    /* uso o getchar para ler o espaco */
    getchar();
    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nomeBuff,eq1Buff,eq2Buff,&scr1,&scr2);
    if(procuraTabela(jogos,nomeBuff) != NULLitem){
        printf("%d Jogo existente.\n",NL);
    }
    else if((eq1 = procuraTabela(equipas,eq1Buff)) == NULLitem || (eq2 = procuraTabela(equipas,eq2Buff)) == NULLitem){
        printf("%d Equipa inexistente.\n",NL);
    }
    else{
        /* Uso eq1 apenas para nao ter de criar uma variavel nova */
        if((eq1 = vencedor(eq1,eq2,scr1,scr2)) != NULL) /* se o jogo nao for um empate adiciono uma vitoria a equipa vencedora */
            eq1->scr[1]++;
        jogo = novoDado(nomeBuff,eq1Buff,eq2Buff,scr1,scr2);
        insereTabela(jogos,jogo);
        insereFinalLista(jogosL,jogo);
    }
}

/* funcao "A" que adiciona uma equipa ao sistema */
void A(tabela *equipas,int NL,lista *equipasL){
    char buffer[TAM_BUFFER];
    /* uso o getchar para ler o espaco */
    getchar();
    scanf("%[^:\n]",buffer);
    if(procuraTabela(equipas,buffer) != NULLitem)
        printf("%d Equipa existente.\n",NL);
    else{
        dados *equipa;
        equipa = novoDado(buffer,NULL,NULL,EQUIPA,0);/*uma equipa e representada pela estrutura dados*/
        insereTabela(equipas,equipa);      /*igualmente aos jogos mas os ponteiros eq1,eq2 apontam para NULL*/
        insereFinalLista(equipasL,equipa);              /*e a pontuacao que seria correspondente a equipa 1 e negativa */
    }
}

/* funcao "l" que lista todos os jogos pela ordem em que foram inseridos */
void l(lista *jogosL,int NL){
    int i;
    for(i = 0;i < jogosL->n;i++)
        if((jogosL->vetor[i]->scr[1] > EQUIPA))/*quando apago um elemento da tabela de dispersao dou free nas strings mas nao dou free no ponteiro do dado*/
            printf("%d %s %s %s %d %d\n",NL,jogosL->vetor[i]->nome,jogosL->vetor[i]->eq1,jogosL->vetor[i]->eq2,jogosL->vetor[i]->scr[0],jogosL->vetor[i]->scr[1]);
}                                       /*entao coloco a pontuacao da 2a equipa negativa para distinguir dos que nao foram removidos */

/* funcao "p" que procura um jogo na tabela de dispersao*/
void p(tabela *jogos,int NL){
    char buff[TAM_BUFFER];
    dados *jogo;
    /* uso o getchar para ler o espaco */
    getchar();
    scanf("%[^:\n]",buff);
    if((jogo = procuraTabela(jogos,buff)) == NULLitem) /* se a procura retornar NULLitem entao o jogo nao existe */
        printf("%d Jogo inexistente.\n",NL);
    else
        printf("%d %s %s %s %d %d\n",NL,jogo->nome,jogo->eq1,jogo->eq2,jogo->scr[0],jogo->scr[1]);
}

/* funcao "r" que apaga um jogo do sistema */
void r(tabela *jogos,tabela *equipas,int NL){
    char buff[TAM_BUFFER];
    dados *jogo;
    /* uso o getchar para ler o espaco */
    getchar();
    scanf("%[^:\n]",buff);
    if((jogo = procuraTabela(jogos,buff)) == NULLitem)
        printf("%d Jogo inexistente.\n",NL);
    else{
        dados *eq1,*eq2;
        jogo = procuraTabela(jogos,jogo->nome);
        eq1 = procuraTabela(equipas,jogo->eq1);
        eq2 = procuraTabela(equipas,jogo->eq2);
        if((eq1 = vencedor(eq1,eq2,jogo->scr[0],jogo->scr[1])) != NULL) /* se o resultado do jogo nao for empate removo uma vitoria */
            eq1->scr[1]--;
        jogo->scr[1] = ITEM_APAGADO;
    }
}

/* funcao "s" que altera a pontuacao de um jogo */
void s(tabela *jogos,tabela *equipas,int NL){
    int scr1,scr2;
    char buff[TAM_BUFFER];
    dados *jogo;
    /* uso o getchar para ler o espaco */
    getchar();
    scanf("%[^:\n]:%d:%d",buff,&scr1,&scr2);
    if((jogo = procuraTabela(jogos,buff)) == NULLitem)
        printf("%d Jogo inexistente.\n",NL);
    else{
        dados *eq1,*eq2,*res1,*res2;
        eq1 = procuraTabela(equipas,jogo->eq1);
        eq2 = procuraTabela(equipas,jogo->eq2);
        res1 = vencedor(eq1,eq2,jogo->scr[0],jogo->scr[1]);
        res2 = vencedor(eq1,eq2,scr1,scr2);
        if(res1 != res2){ /* se os resultados do jogo mudarem altero as pontuacoes das equipas */
            if(res1==eq1){ /* se o vencedor antes da mudanca era a equipa 1 */
                if(res2==NULL) /* se passou a um empate removo uma vitoria a equipa 1*/
                    eq1->scr[1]--;
                else if(res2==eq2){ /* se passou a uma vitoria da equipa 2 removo uma vitoria a equipa 1 */
                    eq1->scr[1]--; /* e adiciono uma vitoria a equipa 2 */
                    eq2->scr[1]++;
                }
            }else if(res1==NULL){ /* se o resultado era um empate */
                res2->scr[1]++;
                /* adiciono uma vitoria a equipa vencedora */
            }else{ /* se o vencedor era a equipa 2 */
                if(res2==eq1){ /* se o vencedor passou a ser a equipa 1 removo 1 ponto a equipa 2 e coloco o na equipa 1 */
                    eq2->scr[1]--;
                    eq1->scr[1]++;
                }else if(res2 == NULL) /* se o resultado passou a ser um empate removo uma vitoria a equipa 2 */
                    eq2->scr[1]--;
            }
        }
        jogo->scr[0] = scr1;
        jogo->scr[1] = scr2;
    }
}

/* funcao "P" que procura uma equipa no sistema */
void P(tabela *equipas,int NL){
    char buff[TAM_BUFFER];
    dados *equipa;
    /* uso o getchar para ler o espaco */
    getchar();
    scanf("%[^:\n]",buff);
    if((equipa = procuraTabela(equipas,buff)) == NULLitem)/* se a procura retornar NULLitem entao a equipa nao existe no sistema */
        printf("%d Equipa inexistente.\n",NL);
    else
        printf("%d %s %d\n",NL,equipa->nome,equipa->scr[1]);
}

/* funcao "g" que encontra o maior numero de vitorias e lista ordenadamente as equipas com esse numero de vitorias */
void g(lista *equipasL,int NL){ /* caso nao haja nenhuma equipa a funcao nao imprime nada */
    int max,i;
    lista *queue = novaLista(equipasL->n);
    for(i = 0,max = 0;i < equipasL->n;i++) /* encontra o maximo e guarda esse valor */
        if(equipasL->vetor[i]->scr[1] > max){
            max = equipasL->vetor[i]->scr[1];
        }
    /* percorre todas as equipas desde e coloca numa lista as que tem esse numero maximo de vitorias */
    for(i = 0;i < equipasL->n;i++)
        if(equipasL->vetor[i]->scr[1] == max)
            queue = insereFinalLista(queue,equipasL->vetor[i]);;
    if(queue->n == 0){
        libLista(queue);
        return;
    } else if(queue->n > 1)
        insertionSort(queue,0,queue->n); /* ordeno-as por ordem lexicografica */
    printf("%d Melhores %d\n",NL,max);
    for(i = 0;i < queue->n;i++)
        printf("%d * %s\n",NL,queue->vetor[i]->nome);
    libLista(queue);
}
