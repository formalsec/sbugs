#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogos_equipas.h"

/*
Funcao 'str_duplicate':
    Argumentos - ponteiro para a string a ser copiada;
    Descricao - copia a a string que entra por argumento para um bloco de 
                memoria alocado na heap apenas com o tamanho necessario;
    Valor de Retorno - ponteiro para uma string alocada na heap;
*/
char* str_duplicate(char str[]){
    int i, len = strlen(str);
    char* copia;
    copia = (char*) malloc(sizeof(char)*(len+1));
    for (i = 0; i < len; ++i){
        copia[i] = str[i];
    }
    copia[i] = '\0';
    return copia;
}
/*
Funcao 'str_duplicate':
    Argumentos - ponteiro para uma string e um inteiro >0;
    Descricao -  calcula a hash correspondente a string inserida;
    Valor de Retorno - um inteiro com a hash calculada;
*/
long hash_func(char* nome, int size){
    long h, a = 31415;
    int b = 27183;   
    for (h = 0; *nome != '\0'; nome++, a = a*b % (size - 1))
        h = (a*h + *nome) % size;
    return h;
}
/*
Funcao 'cria_equipa':
    Argumentos - ponteiro para uma string;
    Descricao -  cria uma nova equipa com o nome correspondente a string inserida;
    Valor de Retorno - um ponteiro para a equipa criada;
*/
pEquipa cria_equipa(char str[1024]){
    pEquipa nova_equipa;
    nova_equipa = (pEquipa) malloc(sizeof(equipa));
    nova_equipa->nome = str_duplicate(str);
    nova_equipa->vit = 0;
    return nova_equipa;
}
/*
Funcao 'cria_tabela_equi':
    Argumentos - void;
    Descricao - cria uma nova tabela de ponteiros para equipas com tamanho
                igual ao valor de tabEq_size e inicializa rodas as entradas
                para o ponterio nulo (NULL);
    Valor de Retorno - um ponteiro para a tabela criada;
*/
pEquipa* cria_tabela_equi(){
    long i;
    pEquipa* tabela;
    tabela = (pEquipa*) malloc(sizeof(pEquipa)*tabEq_size);
    for (i = 0; i < tabEq_size; ++i)
        tabela[i] = NULL;
    return tabela;
}
/*
Funcao 'expandEq':
    Argumentos - void;
    Descricao - duplica o tamanho da tabela de equipas, tabela_Equi, e reinsere
                todas as equipas ja na tabela;
    Valor de Retorno - void;
*/
void expandEq(){
    long j, i = tabEq_size;
    pEquipa* tabAux;
    tabEq_size = tabEq_size*2;
    tabAux = tabela_Equi;
    tabela_Equi = cria_tabela_equi();
    for (j = 0; j < i; ++j)
        if (tabAux[j] != NULL)
            insert_Eq(tabAux[j]);
    free(tabAux);
}
/*
Funcao 'insert_Eq':
    Argumentos - ponteiro para uma equipa;
    Descricao - insere o ponteiro que entra como argumento na tabela 
                de equipas, tabela_Equi;
    Valor de Retorno - void;
*/
void insert_Eq(pEquipa eq){
    long i;
    for(i = hash_func(eq->nome, tabEq_size); tabela_Equi[i] != NULL; i = (i+1)%tabEq_size);
    tabela_Equi[i] = eq;
    if (tabEq_ocup++ >= tabEq_size/2)
        expandEq();
}
/*
Funcao 'search_Eq':
    Argumentos - ponteiro para uma string;
    Descricao - procura a equipa com o nome inserido na tabela 
                de equipas, tabela_Equi;
    Valor de Retorno - Ou retorna o indice da tabela onde se encontra a equipa 
                       ou a constante NOT_FOUND se a equipa nao existe;
*/
long search_Eq(char* nome){
    long i;
    for (i = hash_func(nome, tabEq_size); tabela_Equi[i] != NULL;i = (i+1)%tabEq_size){
        if (strcmp(tabela_Equi[i]->nome, nome) == 0)
            return i;
    }
    return NOT_FOUND;
}
/*
Funcao 'merge':
    Argumentos - vetor de ponteiros para equipas e indices esquerdo, direito e meio;
    Descricao - funcao merge do algoritmo de ordenacao mergeSort. Ordena as equipas
                por ordem lexicografica (do nome da equipa).
    Valor de Retorno - void;
*/
void merge(pEquipa *vetor, int e, int d, int m){
    int i, j, k;
    pEquipa *aux;
    aux = (pEquipa*) malloc(sizeof(pEquipa) * tabEq_ocup);
    for (i = m + 1; i > e; --i)
        aux[i-1] = vetor[i-1];
    for (j = m; j < d; ++j)
        aux[d + m - j] = vetor[j+1];
    for (k = e; k <= d; ++k)
        if (strcmp(aux[j]->nome, aux[i]->nome) < 0 || i > m){
            vetor[k] = aux[j];
            --j;
        }
        else{
            vetor[k] = aux[i];
            ++i;
        }
    free(aux);
}
/*
Funcao 'mergesort':
    Argumentos - vetor de ponteiros para equipas e indices esquerdo e direito;
    Descricao - aplica o algoritmo mergesort no vetor inserido do indice esquerdo 
                ao direito inclusive;
    Valor de Retorno - void;
*/
void mergesort(pEquipa *vetor, int e, int d){
    int m = (e + d)/2;
    if (d <= e)
        return;
    mergesort(vetor, e, m);
    mergesort(vetor, m + 1, d);
    merge(vetor, e, d, m);
}
/*
Funcao 'freeTabEq':
    Argumentos - void;
    Descricao - liberta o espaco alocado para a tabela de equipas, tabela_Equi, as equipas
                indexadas por esta e os seus nomes
    Valor de Retorno - void;
*/
void freeTabEq(){
    long i;
    for (i = 0; i < tabEq_size; ++i)
        if (tabela_Equi[i] != NULL){
            free(tabela_Equi[i]->nome);
            free(tabela_Equi[i]);
        }
    free(tabela_Equi);
}
/*
Funcao 'vencedor':
    Argumentos - dois inteiros correspondentes a pontuacoes;
    Descricao - calcula o vencedor de acordo com as pontuacoes inseridas;
    Valor de Retorno - EQUI1 se o vencedor for a equipa 1;
                       EQUI2 se o vencedor for a equipa 2;
                       NOT_FOUND se for um empate;
*/
int vencedor(int sc1, int sc2){
    if (sc1 > sc2)
        return EQUI1;
    if (sc1 < sc2)
        return EQUI2;
    return NOT_FOUND;
}
/*
Funcao 'atualiza_vencedores':
    Argumentos - dois inteiros que representam os antigos vencedor e o novo vencedor e
                 e dois ponteiros para as equipas intervenientes;
    Descricao - atualiza o numero de vitorias das equipas intervenientes de acordo com os valores
                do antigo e do novo vencedor;
    Valor de Retorno - void;
*/
void atualiza_vencedores(int ant_venc, int novo_venc, pEquipa e1, pEquipa e2){
    if (ant_venc == EQUI1 && novo_venc == EQUI2){
        e1->vit--;
        e2->vit++;
    }
    else if (ant_venc == EQUI2 && novo_venc == EQUI1){
        e1->vit++;
        e2->vit--;
    }
    else if (ant_venc == EQUI1 && novo_venc == NOT_FOUND)
        e1->vit--;
    else if (ant_venc == EQUI2 && novo_venc == NOT_FOUND)
        e2->vit--;
    else if (ant_venc == NOT_FOUND && novo_venc == EQUI1)
        e1->vit++;
    else if (ant_venc == NOT_FOUND && novo_venc == EQUI2)
        e2->vit++;
}
/*
Funcao 'cria_jogo':
    Argumentos - um ponteiro para uma string, dois ponteiros para equipas e 
                 dois inteiros que representam as pontuacoes no jogo;
    Descricao - cria um jogo com as caracteristicas inseridas, atualiza as vitorias de cada equipa
                e liga o novo jogo ao ultimo jogo inserido;
    Valor de Retorno - um ponteiro para o novo jogo criado;
*/
pJogo cria_jogo(char nome[1024], pEquipa e1, pEquipa e2, int sc1, int sc2){
    pJogo novo_jogo;
    novo_jogo = (pJogo) malloc(sizeof(jogo));
    novo_jogo->nome = str_duplicate(nome);
    novo_jogo->e1 = e1;
    novo_jogo->e2 = e2;
    novo_jogo->sc1 = sc1;
    novo_jogo->sc2 = sc2;
    novo_jogo->next = NULL;
    atualiza_vencedores(NOT_FOUND, vencedor(sc1, sc2), e1, e2);
    if (head == NULL){
        head = novo_jogo;
        tail = novo_jogo;
        novo_jogo->previous = NULL;
    }
    else{
        tail->next = novo_jogo;
        novo_jogo->previous = tail;
        tail = novo_jogo;
    }
    return novo_jogo;
}
/*
Funcao 'cria_tabela_jogo':
    Argumentos - void;
    Descricao - cria uma tabela de ponteiros para jogos com o tamanho tabJo_size;
    Valor de Retorno - um ponteiro para a nova tabela criada;
*/
pJogo* cria_tabela_jogo(){
    long i;
    pJogo* tabela;
    tabela = (pJogo*) malloc(sizeof(pJogo)*tabJo_size);
    for (i = 0; i < tabJo_size; ++i)
        tabela[i] = NULL;
    return tabela;
}
/*
Funcao 'expandJo':
    Argumentos - void;
    Descricao - duplica o tamanho da tabela de jogos, tabela_Jo, e reinsere
                todos os jogos ja na tabela;
    Valor de Retorno - void;
*/
void expandJo(){
    long j, i = tabJo_size;
    pJogo* tabAux;
    tabAux = tabela_Jo;
    tabJo_size = tabJo_size * 2;
    tabela_Jo = cria_tabela_jogo();
    for (j = 0; j < i; ++j){
        if (tabAux[j] != NULL)
            insert_Jo(tabAux[j]);
    }
    free(tabAux);
}
/*
Funcao 'insert_Jo':
    Argumentos - um ponteiro para um jogo; 
    Descricao - insere o ponteiro que entra como argumento na
                tabela de jogos, tabela_Jo;
    Valor de Retorno - void;
*/
void insert_Jo(pJogo jogo){
    long i;
    for (i = hash_func(jogo->nome, tabJo_size); tabela_Jo[i] != NULL; i = (i+1) % tabJo_size);
    tabela_Jo[i] = jogo;
    if (tabJo_ocup++ > tabJo_size/2)
        expandJo();
}
/*
Funcao 'search_Eq':
    Argumentos - ponteiro para uma string;
    Descricao - procura o jogo com o nome inserido na tabela 
                de jogos, tabela_Jo;
    Valor de Retorno - Ou retorna o indice da tabela onde se encontra o jogo 
                       ou a constante NOT_FOUND se o jogo nao existe;
*/
long search_Jo(char* nome){
    long i;
    for(i = hash_func(nome, tabJo_size); tabela_Jo[i] != NULL; i = (i+1)%tabJo_size)
        if (strcmp(tabela_Jo[i]->nome, nome) == 0)
            return i;
    return NOT_FOUND;
}
/*
Funcao 'remove_Jo':
    Argumentos - um ponteiro para uam string;
    Descricao - remove o jogo com o nome da string inserida conectando os elementos 
                anterior e posterior na ordem de introducao entre si, atualizando 
                as vitorias das equipas participantes no jogo e removendo o jogo da 
                tabela de jogos. Por fim liberta a memoria alocada para o nome do jogo
                e para o jogo em questao;
    Valor de Retorno - devolve NOT_FOUND se o jogo nao existe e RMOVED se o jogo foi 
                       removido com sucesso;
*/
int remove_Jo(char* nome){
    long i, j;
    pJogo jo;
    if ((i = search_Jo(nome)) == NOT_FOUND)
        return NOT_FOUND;

    jo = tabela_Jo[i];

    if (jo == head){
        head = head->next;
        if (jo == tail)
            tail = NULL;
    }
    else if (jo == tail){
        tail = jo->previous;
        tail->next = NULL;
    }
    else{
        jo->previous->next = jo->next;
        jo->next->previous = jo->previous;
    }

    atualiza_vencedores(vencedor(jo->sc1, jo->sc2), NOT_FOUND, jo->e1, jo->e2);

    free(jo->nome);
    free(jo);

    tabela_Jo[i] = NULL;
    tabJo_ocup--;

    for (j = (i+1) % tabJo_size; tabela_Jo[j] != NULL;j = (j+1)%tabJo_size, tabJo_ocup--){
        jo = tabela_Jo[j];
        tabela_Jo[j] = NULL;
        insert_Jo(jo);
    }
    return REMOVED;   
}
/*
Funcao 'freeTabJo':
    Argumentos - void;
    Descricao - liberta o espaco alocado para a tabela de jogos, tabela_Jo, os jogos
                indexadas por esta e os seus nomes;
    Valor de Retorno - void;
*/
void freeTabJo(){
    long i;
    for (i = 0; i < tabJo_size; ++i){
        if (tabela_Jo[i] != NULL){
        free(tabela_Jo[i]->nome);
        free(tabela_Jo[i]);
        }
    }
    free(tabela_Jo);
}
