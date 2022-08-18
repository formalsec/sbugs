#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Projeto2.h"

/*Esta funcao mete o jogo no fim da lista, ficando assim por ordem de entrada.*/
void atualiza_lista(jogo_pont *lista_jogos_inicio, jogo_pont *lista_jogos_fim, jogo_pont jogo_adici){
    if(*lista_jogos_fim == NULL){
        *lista_jogos_inicio = jogo_adici;
        *lista_jogos_fim = jogo_adici;
        (*lista_jogos_fim) -> prox_jogo_lista = NULL;
    }
    else {
        (*lista_jogos_fim) -> prox_jogo_lista = jogo_adici;
        *lista_jogos_fim = jogo_adici;
        (*lista_jogos_fim) -> prox_jogo_lista = NULL;
    }
}

/*Esta funcao verifica se a equipa ja existe no sistema.*/
equipa_pont encontra_equipa(char* nome_equipa, equipa_pont *tabela_hash_equipas, jogo_pont *jogo_adici, int equipa){
    int indice;
    equipa_pont e, aux = NULL;
 
    indice = hash(nome_equipa, Hash_equipas);

    /*Percorre a tabela_hash_equipas ate encontrar uma equipa com o nome
      pretendido ou ate chegar ao fim, sendo que se chegar ao fim quer dizer
      que nao havia nenhuma equipa com o mesmo nome no sistema.*/
    for (e = tabela_hash_equipas[indice]; e != NULL; e = e->prox_equipa){
        if ((strcmp(e -> nome_equipa, nome_equipa) == 0) && (equipa == 1)){
            (*jogo_adici) -> equipa1 = e -> nome_equipa;
            aux = e;
        }
        if ((strcmp(e -> nome_equipa, nome_equipa) == 0) && (equipa == 2)){
            (*jogo_adici) -> equipa2 = e -> nome_equipa;
            aux = e;
        }
    }
    return aux;
}

/*Esta funcao adiciona o jogo a tabela hash de jogos.*/
void mete_jogo_hash(jogo_pont *jogo_adici, char *n_jogo, int resultado1, int resultado2, jogo_pont *tabela_hash_jogos, int indice){
    (*jogo_adici) -> nome_jogo = (char*)malloc(sizeof(char)*(strlen(n_jogo)+1));
    strcpy((*jogo_adici)->nome_jogo, n_jogo);

    (*jogo_adici) -> golos1 = (int*)malloc(sizeof(int));
    *(*jogo_adici) -> golos1 = resultado1;

    (*jogo_adici) -> golos2 = (int*)malloc(sizeof(int));
    *(*jogo_adici) -> golos2 = resultado2;

    (*jogo_adici) -> prox_jogo = tabela_hash_jogos[indice];
    tabela_hash_jogos[indice] = *jogo_adici;
}

/*Esta funcao adiciona um jogo ao sistema.
  Esta funcao ira gerar um erro se o nome do jogo ja existir no sistema 
  ou se uma das equipas nao existir no sistema.*/
void adic_jogo(jogo_pont *lista_jogos_inicio, jogo_pont *lista_jogos_fim, jogo_pont *tabela_hash_jogos, equipa_pont *tabela_hash_equipas, int nl){
    char n_jogo[Nome], nome_equipa1[Nome], nome_equipa2[Nome];
    int resultado1, resultado2, indice1;
    jogo_pont jogo_adici, i;
    equipa_pont aux1, aux2;
    
    jogo_adici = (jogo_pont)malloc(sizeof(struct jogo));

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", n_jogo, nome_equipa1, nome_equipa2, &resultado1, &resultado2);
    
    indice1 = hash(n_jogo, Hash_jogos);
    
    /*Se nao existir nenhum jogo no sistema com o nome igual devolve um erro.*/
    for (i = tabela_hash_jogos[indice1]; i != NULL; i = i->prox_jogo){
        if (strcmp(i->nome_jogo, n_jogo) == 0){
            printf("%d Jogo existente.\n", nl);
            free(jogo_adici);
            return;
        }
    }

    aux1 = encontra_equipa(nome_equipa1, tabela_hash_equipas, &jogo_adici, 1);
    
    /*A variavel aux1 ser igual a NULL quer dizer que nao foi encontrado 
      nenhuma equipa com o mesmo nome no sistema.*/
    if (aux1 == NULL){
        printf("%d Equipa inexistente.\n", nl);
        free(jogo_adici);
        return;
    }

    aux2 = encontra_equipa(nome_equipa2, tabela_hash_equipas, &jogo_adici, 2);

    /*A variavel aux2 ser igual a NULL quer dizer que nao foi encontrado 
      nenhuma equipa com o mesmo nome no sistema.*/
    if (aux2 == NULL){
        printf("%d Equipa inexistente.\n", nl);
        free(jogo_adici);
        return;
    }
    
    /*Atualiza  numero de vitorias da equipa que ganhou, caso haja alguma.*/
    if (resultado1 > resultado2){
        (*aux1 -> vitorias)++;
    }
    else if (resultado1 < resultado2){
        (*aux2 -> vitorias)++;
    }
    
    mete_jogo_hash(&jogo_adici, n_jogo, resultado1, resultado2, tabela_hash_jogos, indice1);

    atualiza_lista(lista_jogos_inicio, lista_jogos_fim, jogo_adici);

    return;
}

/*Esta funcao devolve por ordem de entrada os jogos existentes.*/
void jogos_introduzidos(jogo_pont lista_jogos_inicio, int nl){
    jogo_pont i;

    for (i = lista_jogos_inicio; i != NULL; i = i -> prox_jogo_lista){
        printf("%d %s %s %s %d %d\n", nl, i -> nome_jogo, i -> equipa1, i -> equipa2, *i -> golos1, *i -> golos2);
    }
}

/*Esta funcao procura um jogo no sistema.
  Esta funcao ira gerar um erro se o nome do jogo nao existir no sistema.*/
void procura_jogo(jogo_pont *tabela_hash_jogos, int nl){
    char nome[Nome];
    int indice;
    jogo_pont i;

    scanf(" %s", nome);

    indice = hash(nome, Hash_jogos);

    /*Percorre a tabela ate encontrar um jogo com o mesmo nome que o pretendido
      ou ate chegar ao fim, sendo que se chegar ao fim quer dizer que nao havia 
      nenhum jogo no sistema com o mesmo nome.*/
    for (i = tabela_hash_jogos[indice]; i != NULL; i = i -> prox_jogo){
        if (strcmp(nome, i -> nome_jogo) == 0){
            printf("%d %s %s %s %d %d\n", nl, i -> nome_jogo, i -> equipa1, i -> equipa2, *i -> golos1, *i -> golos2);
            return;
        }
    }
    printf("%d Jogo inexistente.\n", nl);
    
}

/*Esta funcao serve para atualizar as vitorias da primeira equipa.*/
void atualiza_vitorias_equipa1 (equipa_pont *tabela_hash_equipas, int ctrl, jogo_pont aux){
    int indice;
    equipa_pont e;

    indice = hash(aux -> equipa1, Hash_equipas);

    /*A variavel ctrl e que define se a equipa precisa de manter,
      aumentar ou diminuir o numero de vitorias.*/
    if ((ctrl == 1) || (ctrl == 2) || (ctrl == 3) || (ctrl == 5)){
        for (e = tabela_hash_equipas[indice]; e != NULL; e = e -> prox_equipa){
            if ((strcmp(aux -> equipa1, e -> nome_equipa) == 0) && ((ctrl == 3) || (ctrl == 5))){
                (*e -> vitorias)++;
                return;
            }
            if ((strcmp(aux -> equipa1, e -> nome_equipa) == 0) && ((ctrl == 1) || (ctrl == 2))){
                (*e -> vitorias)--;
                return;
            }
        }
    }
}

/*Esta funcao serve para atualizar as vitorias da segunda equipa.*/
void atualiza_vitorias_equipa2 (equipa_pont *tabela_hash_equipas, int ctrl, jogo_pont aux){
    int indice;
    equipa_pont e;

    indice = hash(aux -> equipa2, Hash_equipas);

    /*A variavel ctrl e que define se a equipa precisa de manter,
      aumentar ou diminuir o numero de vitorias.*/
    if ((ctrl == 1) || (ctrl == 4) || (ctrl == 5) || (ctrl == 6)){
        for (e = tabela_hash_equipas[indice]; e != NULL; e = e -> prox_equipa){
            if ((strcmp(aux -> equipa2, e -> nome_equipa) == 0) && ((ctrl == 1) || (ctrl == 4))){
                (*e -> vitorias)++;
                return;
            }
            if ((strcmp(aux -> equipa2, e -> nome_equipa) == 0) && ((ctrl == 5) || (ctrl == 6))){
                (*e -> vitorias)--;
                return;
            }
        }
    }
}

/*Esta funcao verifica se as equipas precisam de diminuir, 
  aumentar ou manter o numero de vitorias.*/
int obtem_ctrl (jogo_pont i, int resultado1, int resultado2){

    if (*i -> golos1 > *i -> golos2) {
        if (resultado1 < resultado2) return 1;
        else if (resultado1 == resultado2) return 2;
    }
    else if (*i -> golos1 == *i ->golos2) {
        if (resultado1 > resultado2) return 3;
        else if (resultado1 < resultado2) return 4;
    }
    else if (*i -> golos1 < *i ->golos2) {
        if (resultado1 > resultado2) return 5;
        else if (resultado1 == resultado2) return 6;
    }
    return 0;
}

/*Esta funcao altera o resultado de um jogo do sistema.
  Esta funcao ira gerar um erro se nao existir nenhum jogo com o nome no sistema.*/
void altera_resultado(jogo_pont *tabela_hash_jogos, equipa_pont *tabela_hash_equipas, int nl){
    int resultado1, resultado2, indice1, ctrl = 0, ctrl_jogo = 0;
    char nome[Nome];
    jogo_pont i, aux;

    scanf(" %[^:\n]:%d:%d", nome, &resultado1, &resultado2);
    
    indice1 = hash(nome, Hash_jogos);

    /*Percorre a tabela ate encontrar um jogo com o mesmo nome que o pretendido
      ou ate chegar ao fim, sendo que se chegar ao fim quer dizer que nao havia 
      nenhum jogo no sistema com o mesmo nome.*/
    for (i = tabela_hash_jogos[indice1]; i != NULL; i = i -> prox_jogo){
        if (strcmp(nome, i -> nome_jogo) == 0){

            ctrl = obtem_ctrl(i, resultado1, resultado2);
            *i -> golos1 = resultado1;
            *i -> golos2 = resultado2;
            aux = i;
            ctrl_jogo = 1;
        }
    }

    if (ctrl_jogo == 0){
        printf("%d Jogo inexistente.\n", nl);
        return;
    }

    if (ctrl == 0){
        return;
    }

    atualiza_vitorias_equipa1(tabela_hash_equipas, ctrl, aux);
    atualiza_vitorias_equipa2(tabela_hash_equipas, ctrl, aux);
    
}

/*Esta funcao serve para remover um jogo da lista de jogos.*/
int remove_jogo_lista(jogo_pont *lista_jogos, jogo_pont *lista_jogos_fim, char *nome){
    jogo_pont i, aux;
    int ctrl = 0;
    /*A variavel ctrl serve para verificar se houve algum jogo a ser removido 1-sim, 0-nao.*/

    for (i = *lista_jogos, aux = NULL; i != NULL; aux = i, i = i -> prox_jogo_lista){
        /*A funcao verifica se e preciso atualizar o inicio e/ou fim da lista.*/
        if (strcmp(nome, i -> nome_jogo) == 0){
            if ((i == *lista_jogos) && (i -> prox_jogo_lista == NULL)){
                *lista_jogos = NULL;
                *lista_jogos_fim = NULL;
                return ++ctrl;
            }
            else if (i == *lista_jogos){
                *lista_jogos = (*lista_jogos) -> prox_jogo_lista;
                return ++ctrl;
            }
            else if (i -> prox_jogo_lista == NULL){
                *lista_jogos_fim = aux;
                (*lista_jogos_fim) -> prox_jogo_lista = NULL;
                return ++ctrl;
            }
            else {
                aux -> prox_jogo_lista = i -> prox_jogo_lista;
                return ++ctrl;
            }
        }
    }
    return ctrl;
}

/*Esta funcao serve para retirar um jogo da tabela de jogos, ou seja do sistema.*/
jogo_pont remove_jogo_hash(jogo_pont *tabela_hash_jogos, char* nome, int *resultado1, int *resultado2, char *equipa1, char *equipa2){
    int indice;
    jogo_pont aux, i, aux_free;

    indice = hash(nome, Hash_jogos);

    for(i = tabela_hash_jogos[indice], aux = NULL; i != NULL; aux = i, i = i -> prox_jogo){
        if (strcmp(nome, i-> nome_jogo) == 0){
            /*A funcao verifica se e preciso atualizar o inicio ou o fim da lista.*/
            if (i == tabela_hash_jogos[indice]){
                tabela_hash_jogos[indice] = i -> prox_jogo;
                (*resultado1) = *i -> golos1;
                (*resultado2) = *i -> golos2;
                strcpy(equipa1, i -> equipa1);
                strcpy(equipa2, i -> equipa2);
                return i;
            }
            else if (i -> prox_jogo == NULL){
                (*resultado1) = *i -> golos1;
                (*resultado2) = *i -> golos2;
                strcpy(equipa1, i -> equipa1);
                strcpy(equipa2, i -> equipa2);
                aux_free = i;
                i = aux;
                i -> prox_jogo = NULL;
                return aux_free;
            }
            else {
                aux -> prox_jogo = i -> prox_jogo;
                (*resultado1) = *i -> golos1;
                (*resultado2) = *i -> golos2;
                strcpy(equipa1, i -> equipa1);
                strcpy(equipa2, i -> equipa2);
                return i;
            }
        }
    }
    return NULL;
}

/*Esta funcao remove um jogo do sistema.
  Esta funcao ira gerar um erro se nao existir nenhum jogo com o nome no sistema.*/
void apaga_jogo(jogo_pont *tabela_hash_jogos, equipa_pont *tabela_hash_equipas, jogo_pont *lista_jogos, jogo_pont *lista_jogos_fim, int nl){
    jogo_pont aux_free;
    equipa_pont e;
    int indice, ctrl = 0, resultado1, resultado2 = 0;
    char nome[Nome], equipa1[Nome], equipa2[Nome];


    scanf(" %[^:\n]", nome);

    ctrl = remove_jogo_lista(lista_jogos, lista_jogos_fim, nome);

    if (ctrl == 0){
        printf("%d Jogo inexistente.\n", nl);
        return;
    }

    /*A variavel aux_free corresponde ao jogo que vai ser removido.*/
    aux_free = remove_jogo_hash(tabela_hash_jogos, nome, &resultado1, &resultado2, equipa1, equipa2);
    
    /*Esta condicao serve reduzir em 1 a equipa que ganhou, caso alguma tenha ganho.*/
    if (resultado1 > resultado2){
        indice = hash(equipa1, Hash_equipas);
        for (e = tabela_hash_equipas[indice]; e != NULL; e = e -> prox_equipa){
            if (strcmp(equipa1, e -> nome_equipa) == 0){
                (*e -> vitorias)--;
            }
        }
    }

    else if (resultado1 < resultado2){
        indice = hash(equipa2, Hash_equipas);
        for (e = tabela_hash_equipas[indice]; e != NULL; e = e -> prox_equipa){
            if (strcmp(equipa2, e -> nome_equipa) == 0){
                (*e -> vitorias)--;
            }
        }
    }
    
    free(aux_free -> nome_jogo);
    free(aux_free -> golos1);
    free(aux_free -> golos2);
    free(aux_free);

    return;
}