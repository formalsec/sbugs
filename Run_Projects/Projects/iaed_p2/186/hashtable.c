#include "hashtable.h"


/* atribui uma chave a uma string nome, correspondente 'a posicao que o item com este nome fica na hashtable  */
unsigned int hash(char* nome){
    int comprimento = strlen(nome), chave = 0, i;

    for (i = 0; i < comprimento; i++){
        chave = chave + nome[i];
        chave = (chave * nome[i]) % TAMANHO_TAB; /* chave e' um valor menor que o tamanho da hashtable */
    }

    return chave;
}


/* inicia a hashtable, atribuindo a todas as posicoes o valor NULL */
void init_hashtable(Item ** hashtable){
    int i;

    for (i = 0; i < TAMANHO_TAB; i++){
        hashtable[i] = NULL;
    } 
}


/* insere o item na posicao correspondente na hashtable */
void insere_hashtable(Item * item, Item ** hashtable){
    int chave = hash(item->nome); /* encotra a posicao correspondente*/

    /* insere na hashtable, o novo item torna-se cabeca da lista dos itens dessa posicao  */
    if (!hashtable[chave]){ /* caso a posicao esteja vazia */
        hashtable[chave] = item;
    }
    else{ /* caso ja esteja preenchida */
        item->next_hash = hashtable[chave];
        hashtable[chave] = item;
    }
}


/* procura um item na hashtable dado um nome e devolve o item caso este exista */
Item * procura_item(char* nome, Item ** hashtable){
    int chave = hash(nome);
    Item * item; 

    /* encontra a cabeca da lista na posicao da hashtable correspondente ao nome */
    item = hashtable[chave];

    /* caso a posicao esteja vazia, devolve NULL */
    if (!item){
        return NULL;
    }
    /* caso nao esteja vazia, percorre a lista e devolve o item caso o encontre*/
    else{
        while(item){
            if (strcmp(item->nome, nome) == 0){
                return item;
            } 
            item = item->next_hash;
        }
        return NULL;
    }
}


/* recebe um jogo e retorna a equipa com a melhor pontuacao */
Item * equipa_vencedora(Item ** hashtable, Item * jogo){

    /* ve qual foi a equipa com a melhor pontuacao e procura-a na hashtable */
    if (jogo->score1 > jogo->score2){
        return procura_item(jogo->equipa1, hashtable);
    }
    else{
        return procura_item(jogo->equipa2, hashtable);
    }

}


/* recebe um jogo e aumneta o numero de vitorias da equipa vencedora */
void adiciona_vitoria(Item ** hashtable, Item * jogo){
   
    /* nao faz nada se o resultado for um empate */
    if (jogo->score1 != jogo->score2){
        /* procura a equipa vencedora */
        Item * vencedor = equipa_vencedora(hashtable, jogo);

        /* aumenta o numero de vitorias 'a equipa vencedora */
        vencedor->vitorias++;
    }
}


/* recebe um jogo e diminui o numero de vitorias da equipa vencedora */
void retira_vitoria(Item ** hashtable, Item * jogo){
 
    /* nao faz nada se o resultado for um empate */
    if (jogo->score1 != jogo->score2){
        /* procura a equipa vencedora */
        Item * vencedor = equipa_vencedora(hashtable, jogo);

        /* aumenta o numero de vitorias 'a equipa vencedora */
        vencedor->vitorias--;
    }
}


/* recebe o nome de um jogo e apaga esse jogo do sistema */
int apaga_jogo(char* nome, Item ** hashtable_jogo, Item ** hashtable_equipa, lista_jogo * lst_jogo){
    int chave = hash(nome), cont = 0;
    /* vai 'a posicao da hashtable de jogos correspondente ao nome e encontra a cabeca da lista */
    Item * jogo = hashtable_jogo[chave], * anterior; 

    /* verifica se a posicao se encontra fazia*/
    if (!jogo){
        return FALSE;
    } 
    /* caso a posicao esteja preenchida*/
    while(jogo){
        cont++; /* contador para saber quantos itens existem na posicao*/

        /* percorre a lista 'a procura do jogo correspondente ao nome */
        if (strcmp(nome, jogo->nome) == 0){
            /* retira a vitoria correspondente 'a equipa vencedora deste jogo */
            retira_vitoria(hashtable_equipa, jogo);
            
            /* remove o endereco do jogo na hashtable */
            if (!jogo->next_hash && cont == 1){ /* caso o jogo seja o unico elemento da lista*/
                hashtable_jogo[chave] = NULL;
            }
            else{
                if (jogo == hashtable_jogo[chave]){ /*caso o jogo seja o primeiro elemento da lista */
                    hashtable_jogo[chave] = jogo->next_hash;
                }
                else{
                    anterior->next_hash = jogo->next_hash; /* restantes casos */
                }
            }

            /* remove o endereco do jogo na lista ordenada de jogos */
            if (jogo == lst_jogo->head){ /* caso o jogo seja o primeiro elemento */
                lst_jogo->head = jogo->next;
            } 
            else{ /* restantes casos */
                jogo->prev->next = jogo->next;
            }
            if (jogo == lst_jogo->last){ /* caso o jogo seja o primeiro elemento */
                lst_jogo->last = jogo->prev;
            } 
            else{ /* restantes casos */
                jogo->next->prev = jogo->prev;
            }

            /* apaga toda a memoria associada a este jogo jogo */
            free(jogo->nome);
            free(jogo->equipa1);
            free(jogo->equipa2);
            free(jogo);
            return TRUE;
        }

        anterior = jogo;
        jogo = jogo->next_hash;
    }

    return FALSE;
}