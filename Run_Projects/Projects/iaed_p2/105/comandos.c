#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comandos.h"
#define MAX_TABELA 1000
#define MAX_STR 1024
#define LST_MEL 10

/*funcao auxiliar que recebe dois scores e determina qual das equipas venceu um jogo*/

int ganhou(int val1,int val2) { 
      /*funcao que ve qual a equipa vencedora*/
    if (val1 > val2) {
        return 1; /*equipa1 vence*/
    }
    else if (val2 > val1) {
        return 2; /*equipa2 vence*/
    }
    else {
        return 0; /*empate*/
    }
}


/*funcao que adiciona um jogo ao sistema*/

void adiciona_jogo(int NL,jogo *tabela_hash[MAX_TABELA],\
equipa *tabela_hash_equipa[MAX_TABELA],node_lista **inicio,node_lista **fim) {
    jogo *novo_jogo =  (jogo *) malloc(sizeof(jogo)); /* criar novo jogo */
    char str1[MAX_STR]; /*nome do jogo*/
    char str2[MAX_STR]; /*nome da equipa1*/
    char str3[MAX_STR]; /*nome da equipa2*/
    int score1,score2; /*pontuacao das esquipas*/
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",str1,str2,str3,&score1,&score2);
    /*alocar memoria necessaria para inserir os elementos na tabela*/
    novo_jogo->nome = (char*) malloc((strlen(str1)+1)*sizeof(char));
    novo_jogo->equipa1 = (char*) malloc((strlen(str2)+1)*sizeof(char));
    novo_jogo->equipa2 = (char*) malloc((strlen(str3)+1)*sizeof(char));
    novo_jogo->score1 = score1;
    novo_jogo->score2 = score2;
    strcpy(novo_jogo->nome,str1);
    strcpy(novo_jogo->equipa1,str2);
    strcpy(novo_jogo->equipa2,str3);

    if (procura_tabela(novo_jogo->nome,tabela_hash) != NULL) {
        /*caso o jogo ja exista*/
        printf("%d Jogo existente.\n",NL);
        /*libertar memoria*/
        free(novo_jogo->nome);
        free(novo_jogo->equipa1);
        free(novo_jogo->equipa2);
        free(novo_jogo);
    }

    else {

        /*ver se as equipas existe*/
        equipa* equipa1 = \
        procura_tabela_equipa(novo_jogo->equipa1,tabela_hash_equipa);
        equipa* equipa2 = \
        procura_tabela_equipa(novo_jogo->equipa2,tabela_hash_equipa);

        if (equipa1 == NULL || equipa2== NULL ) { /*caso alguma das equipas nao exista*/
            printf("%d Equipa inexistente.\n",NL);
            free(novo_jogo->nome);
            free(novo_jogo->equipa1);
            free(novo_jogo->equipa2);
            free(novo_jogo);
        }

        else {
            inserir_tabela(novo_jogo,tabela_hash); /*inserir jogo na tabela*/

            insere_fim_lista(novo_jogo->nome,inicio,fim);  /*inserir jogo na lista*/
            
            /* ver qual das duas equipas ganhou */

            if (ganhou(novo_jogo->score1,novo_jogo->score2) == 1) {
                equipa1->ganhos = equipa1->ganhos + 1; 
            }
            else if (ganhou(novo_jogo->score1,novo_jogo->score2) == 2) {
                equipa2->ganhos = equipa2->ganhos + 1;
            }
        }
    } 

}

/*funcao que adiciona uma equipa ao sistema*/

void adiciona_equipa(int NL,equipa *tabela_hash_equipa[MAX_TABELA]) {
    equipa *nova_equipa = malloc(sizeof(*nova_equipa)); /*criar nova equipa*/
    char str1[MAX_STR]; /*nome da equipa*/
    scanf(" %[^\n]",str1);
    /*alocar memoria necessaria para inserir a equipa na tabela*/
    nova_equipa->nome = (char*) malloc((strlen(str1)+1)*sizeof(char));
    strcpy(nova_equipa->nome,str1);

    if (procura_tabela_equipa(nova_equipa->nome,tabela_hash_equipa) != NULL) {
        /*caso a equipa ja exista*/
        printf("%d Equipa existente.\n",NL);
        free(nova_equipa->nome);
        free(nova_equipa);
        
    }

    else {
        /*inserir equipa na tabela*/
        inserir_tabela_equipa(nova_equipa,tabela_hash_equipa); 
        nova_equipa->ganhos = 0; 
        
    }
    

}

/*funcao que imprime todos os elementos da lista*/

void lista_jogos(int NL,jogo *tabela_hash[MAX_TABELA],node_lista **inicio) {
    node_lista *aux = *inicio; /*iniciar na cabeca da lista*/
    while(aux != NULL) {
        jogo* el = procura_tabela(aux->nome,tabela_hash);
        if (el != NULL) { /*imprimir o jogo*/
        printf("%d %s %s %s %d %d\n",NL,\
        el->nome,el->equipa1,el->equipa2,el->score1,el->score2);
        }
        aux = aux->next;
    }


}

/*funcao que procura um jogo no sistema*/

void procura_jogo(int NL,jogo *tabela_hash[MAX_TABELA]) {
    char nome[MAX_STR]; /*nome do jogo a procurar*/
    jogo *aux; 
    scanf(" %[^\n]",nome);
    /*ponteiro aux para o jogo a procurar*/
    aux = procura_tabela(nome,tabela_hash); 
    if (aux != NULL) { /*caso o jogo exista*/
        printf("%d %s %s %s %d %d\n",NL, \
        aux->nome,aux->equipa1,aux->equipa2,aux->score1,aux->score2); 
        /*imprime jogo*/
    }

    else { /*caso o jogo nao exista*/
        printf("%d Jogo inexistente.\n",NL);
    }

}

/*funcao que procura uma equipa no sistema*/

void procura_equipa(int NL,equipa *tabela_hash_equipa[MAX_TABELA]) {
    char nome[MAX_STR]; /*nome da equipa a procurar*/
    equipa *aux;
    scanf(" %[^\n]",nome);
    /*ponteiro aux para a equipa a procurar*/
    aux = procura_tabela_equipa(nome,tabela_hash_equipa);
    if (aux != NULL) { /*caso a equipa exista*/
        printf("%d %s %d\n",NL,aux->nome,aux->ganhos);
    }

    else { /*caso nao exista*/
        printf("%d Equipa inexistente.\n",NL);
    }

}

/*funcao que apaga um jogo do sistema*/

void apaga_jogo(int NL,jogo *tabela_hash[MAX_TABELA],\
equipa *tabela_hash_equipa[MAX_TABELA],node_lista **inicio,node_lista **fim) {
    char nome[MAX_STR]; /*nome do jogo a apagar*/
    jogo *aux;
    scanf(" %[^\n]",nome);
    aux = procura_tabela(nome,tabela_hash); /*ponteiro aux para o jogo a apagar*/
    if (aux != NULL) { /*caso exista*/
        if (ganhou(aux->score1,aux->score2) == 1) { /*se a equipa1 ganhou o jogo*/
            equipa* equipa1 = procura_tabela_equipa(aux->equipa1,tabela_hash_equipa);
            equipa1->ganhos = equipa1->ganhos - 1; /*retira uma vitoria a equipa1*/
        }
        else if (ganhou(aux->score1,aux->score2) == 2) { /*se a equipa2 ganhou o jogo*/
            equipa* equipa2 = procura_tabela_equipa(aux->equipa2,tabela_hash_equipa);
            equipa2->ganhos = equipa2->ganhos - 1; /*retira uma vitoria a equipa2*/
        }
        
        remove_el_lista(aux->nome,inicio,fim); /*remove elemento da tabela*/
        apaga_tabela(aux->nome,tabela_hash); /*remove elemento da lista*/
    }

    else { /*caso nao exista*/
        printf("%d Jogo inexistente.\n",NL);
    }
}

/*funcao que altera a pontuacao de um jogo*/

void altera_score(int NL,jogo *tabela_hash[MAX_TABELA],equipa *tabela_hash_equipa[MAX_TABELA]) {
    char nome[MAX_STR]; /*nome do jogo a alterar*/
    int novo_score1,novo_score2;
    jogo *aux;
    scanf(" %[^:\n]:%d:%d",nome,&novo_score1,&novo_score2);
    /*ponteiro aux para jogo a alterar*/
    aux = procura_tabela(nome,tabela_hash);
    if(aux != NULL) { /*caso exista*/
        equipa* equipa1; 
        equipa* equipa2;
        /*ponteiro equipa1 para alterar vitorias da equipa1*/
        equipa1 = procura_tabela_equipa(aux->equipa1,tabela_hash_equipa);
        /*ponteiro equipa2 para alterar vitorias da equipa2*/
        equipa2 = procura_tabela_equipa(aux->equipa2,tabela_hash_equipa);

        /*caso de empate no jogo original*/
        if (aux->score1 == aux->score2) {
            /*caso de vitoria da equipa2 com o novo score*/
            if (ganhou(novo_score1,novo_score2) == 2) {
                equipa2->ganhos = equipa2->ganhos + 1;
            }

            /*caso de vitoria da equipa1 com o novo_score*/
            else if (ganhou(novo_score1,novo_score2) == 1) {
                equipa1->ganhos = equipa1->ganhos + 1;

            }
        }

        /*caso de empate no novo score*/
        else if (novo_score1 == novo_score2) {
            /*caso de vitoria da equipa2 no original*/
            if (ganhou(aux->score1,aux->score2) == 2) {
                equipa2->ganhos = equipa2->ganhos - 1;
            }

            /*caso de vitoria da equipa1 no original*/
            else if (ganhou(aux->score1,aux->score2) == 1) {
                equipa1->ganhos = equipa1->ganhos - 1;

            }
        }
        
        /*caso de vitoria da equipa1 no original e derrota no novo score*/
        else if (ganhou(aux->score1,aux->score2) == 1 \
        && ganhou(novo_score1,novo_score2) == 2) {
            equipa1->ganhos = equipa1->ganhos - 1;
            equipa2->ganhos = equipa2->ganhos + 1;
        }

        /*caso de vitoria da equipa2 no original e derrota no novo score*/
        else if (ganhou(aux->score1,aux->score2) == 2 \
        && ganhou(novo_score1,novo_score2) == 1) {
            equipa2->ganhos = equipa2->ganhos - 1;
            equipa1->ganhos = equipa1->ganhos + 1;
        }

        /*alterar o score*/
        aux->score1 = novo_score1;
        aux->score2 = novo_score2;
    }

    else { /*caso nao exista*/

        printf("%d Jogo inexistente.\n",NL);
    }
}


/*funcao auxiliar que compara dois valores (a e b) por ordem lexiografica*/

int compara (const void * a, const void * b ) {
    const char **pa = (const char**)a;
    const char **pb = (const char**)b;

    return strcmp(*pa,*pb); /*comparar alfabeticamente*/
}

/*funcao que determina as equipas que venceram mais jogos*/

void equipas_mais_jogos(int NL,equipa *tabela_hash_equipa[MAX_TABELA]) {
    int maior = 0; /*maior score*/
    char *melhores[LST_MEL]; /*vetor com todos as equipas com maior score*/
    int i;
    int j = 0; /*tamanho do vetor*/
    int k;
    for(i = 0; i < MAX_TABELA; i++) {
        equipa *aux = tabela_hash_equipa[i];
        while(aux != NULL) {
            if(aux->ganhos > maior) {
                /*atualizar maior elemento*/
                maior = aux->ganhos;
                /*reiniciar vetor*/
                melhores[0] = aux->nome;
                j = 1;
            }

            else if(aux->ganhos == maior) {
                /*adicionar elemento ao vetor*/
                melhores[j] = aux->nome;
                j = j + 1;
            }

            aux = aux -> next;
        }
    }

    if (j != 0) {
        printf("%d Melhores %d\n",NL,maior);
        /*ordenar os elementos do vetor*/
        qsort (melhores,j,sizeof(char *),compara);
        /*imprimir vetor*/
        for (k = 0; k < j; ++k) {
            printf("%d * %s\n",NL,melhores[k]);
        }
    }


}



