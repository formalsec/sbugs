#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "gestao.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                      GESTAO GERAL                                     */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que inicializa a memoria */
void inicializa(fila equipas, fila jogos, fila jogos_ord, fila equipas_ord)
{
    int i;

    FILAinit(jogos_ord);
    FILAinit(equipas_ord);

    /* inicializacao das tabelas - cada celula e uma fila a inicializar */
    for (i = 0; i < MAX_DIM; i++)
    {
        FILAinit(equipas + i); /* para as equipas */
        FILAinit(jogos + i); /* para os jogos */
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que liberta toda a memoria inicializada */
void liberta(fila equipas, fila jogos, fila jogos_ord, fila equipas_ord)
{
    node aux; /* o que vamos libertar */
    int i;

    /* libertacao das tabelas, das equipas e dos jogos */
    for (i = 0; i < MAX_DIM; i++)
    {
        /* comeca no primeiro elemento da tabela das equipas */
        aux = equipas[i].head;
        while(aux) /* enquanto houver equipas... */
        {
            apaga_equipa(EQUIPA(aux->elem)); /* liberta a equipa */
            aux = aux->next; /* passa para o seguinte */
        }

        /* comeca no primeiro elemento da tabela dos jogos */
        aux = jogos[i].head;
        while(aux) /* enquanto houver jogos... */
        {
            apaga_jogo(JOGO(aux->elem)); /* liberta o jogo */
            aux = aux->next; /* passa para o seguinte */
        }

        FILAclear(equipas + i); /* liberta a posicao da tabela das equipas */
        FILAclear(jogos + i); /* liberta a posicao da tabela dos jogos */
    }

    /* libertacao das filas */
    FILAclear(jogos_ord); /* libertacao da fila de jogos */
    FILAclear(equipas_ord); /* libertacao da fila de equipas */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que escreve um certo erro de introducao de input */
void escreve_erro(int nL, int erro)
{
    switch (erro) /* dependendo do codigo do erro imprime-o */
    {
    case NAO_EQ: /* se nao existir a equip */
        printf("%d Equipa inexistente.\n", nL);
        break;

    case EQ_REP: /* se ja existir a equipa */
        printf("%d Equipa existente.\n", nL);
        break;

    case NAO_JG: /* se nao existir o jogo */
        printf("%d Jogo inexistente.\n", nL);
        break;

    case JG_REP: /* se ja existir o jogo */
        printf("%d Jogo existente.\n", nL);
        break;
    }
    return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que procura um item -> equipa ou jogo <- pela chave (nome) */
void * encontra(fila Lst, chave c, int flag)
{
    node aux_b, aux_e; /* elementos avaliados - procura */

    if (!Lst->head || !Lst->tail) 
        return NOTFOUND; /* se nao houver que procurar nao se encontra */
    
    aux_b = Lst->head; /* comeca na cabeca -> andar para a frente */
    aux_e = Lst->tail; /* comeca na cauda -> andar para tras */

    while (aux_b && aux_e) /* enquanto ambos apontarem para alguma coisa */
    {
        if (flag == EQ) /* se estivermos a procura duma equipa interpretamos como equipa */
        {
            /* se encontrar a equipa, devolve-a */
            if (EQ_CERTA(EQUIPA(aux_b->elem), c))
                return aux_b->elem;
            if (EQ_CERTA(EQUIPA(aux_e->elem), c))
                return aux_e->elem;
        }
        if (flag == JG) /* se estivermos a procura de um jogo interpretamos como jogo */
        {
            /* se encontrar o jogo, devolve-o*/
            if (JG_CERTO(c, JOGO(aux_b->elem)))
                return aux_b->elem;
            if (JG_CERTO(c, JOGO(aux_e->elem)))
                return aux_e->elem;
        }
        /* se nao, anda para a frente com o aux_b e para tras com o aux_e */
        aux_b = aux_b->next;
        aux_e = aux_e->prev;
    }
    return NOTFOUND; /* se chegar aqui nao encontrou */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                INTERFACE HASH <-> JOGO                                */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que junta um jogo a uma fila (ou tabela de filas) */
void junta_j(fila jogos, jogo j, int flag)
{
    int hashJ; /* chave do jogo */

    /* dependendo da flag adiciona diretamente ao fim da fila ou calcula em que posicao da
    tabela adicionar antes de faze-lo */
    switch(flag) 
    {
        case FILA:

            FILAadd(jogos , j); /* junta ao fim da fila */
            break;

        case TABELA:

            hashJ = hash(CHAVE_JG(j)); /* junta tambem ao fim da fila mas antes calcula(...)*/
            FILAadd(jogos + hashJ, j); /* (...) a fila a que junta */
            break;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que encontra um jogo numa fila */
jogo encontra_j_lst(fila jogos, chave nome)
{
    jogo j; /* jogo a procurar */

    j = JOGO(encontra(jogos, nome, JG)); /* procura na fila e faz o cast */

    return j;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que encontra um jogo numa tabela de filas - hash */
jogo encontra_j_tab(fila jogos, chave nome)
{
    int hashJ; /* chave do jogo */
    jogo j; /* jogo que estamos a procurar */

    hashJ = hash(nome); /* calcula a chave do jogo: posicao da tabela onde esta */

    j = encontra_j_lst(jogos + hashJ, nome); /* procura o jogo na fila certa */

    return j;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que retira um jogo de uma fila (ou tabela de filas - hash) */
void tira_j(fila jogos, jogo j, int flag)
{
    int hashJ; /* chave do jogo */

    /* dependendo da flag retira diretamente da fila ou calcula em que posicao da tabela  
    faze-lo */
    switch(flag)
    {
        case FILA:

            FILAremove(jogos, j); /* retira o elemento da fila */
            break;

        case TABELA:

            hashJ = hash(CHAVE_JG(j)); /* tambem retira da fila mas antes calcula(...)*/
            FILAremove(jogos + hashJ, j);                      /* (...) a fila em que o faz */
            break;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que imprime uma fila de jogos */
void escreve_j_lst(int nL, fila jogos)
{
    node aux; /* cada elemento a imprimir */

    aux = jogos->head; /* comeca no primeiro e imprime todos */
    while (aux) /* enquando houver algo a imprimir */
    {
        escreve_jogo(nL, JOGO(aux->elem));
        aux = aux->next;
    }  
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                               INTERFACE HASH <-> EQUIPA                               */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que junta uma equipa a uma fila (ou tabela de filas - hash) */
void junta_e(fila equipas, equipa e, int flag)
{
    int hashE; /* chave da equipa */

    /* dependendo da flag adiciona diretamente ao fim da fila ou calcula em que posicao da
    tabela adicionar antes de faze-lo */
    switch(flag)
    {
        case FILA:

            FILAadd(equipas , e); /* junta ao fim da fila */
            break;

        case TABELA:

            hashE = hash(CHAVE_EQ(e)); /* calcula a chave - fila a que junta */
            /* adiciona a equipa ao fim da fila (que esta na posicao da tabela calculada) */
            FILAadd(equipas + hashE, e);
            break;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que encontra uma equipa numa fila (auxiliar a encontra_e_tab) */
equipa encontra_e_lst(fila equipas, chave nome)
{
    equipa e; /* equipa a procurar */

    e = EQUIPA(encontra(equipas, nome, EQ)); /* procura na fila e faz o cast */

    return e;
} 

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que encontra uma equipa numa tabela de filas - hash */
equipa encontra_e_tab(fila equipas, chave nome)
{
    int hashE; /* chave da equipa */
    equipa e; /* equipa que estamos a procurar */

    hashE = hash(nome); /* calcula a chave da equipa: posicao da tabela onde esta */

    e = encontra_e_lst(equipas + hashE, nome); /* procura a equipa na fila certa */

    return e;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que encontra o numero maximo de vitorias */
par_resultado maximo_vitorias(fila equipas_ord)
{
    node aux_b, aux_e; /* elementos analisados */
    par_resultado max; /* maximo a calcular */
    equipa e1, e2; /* transformacao dos nos em equipas */

    max.maximo = NOMAX; /* inicializa o maximo */
    max.num_venc = NOMAX; /* e o numero de vencedores */

    aux_b = equipas_ord->head; /* comeca na cabeca e percorre para a frente */
    aux_e = equipas_ord->tail; /* comeca na cauda e percorre para tras */

    /* enquanto ambos existirem e nao se intersetarem */
    while (aux_b && aux_e && aux_e->next != aux_b)
    {
        e1 = EQUIPA(aux_b->elem);
        e2 = EQUIPA(aux_e->elem);
        /* se algum dos elementos em analise tiver um numero maior de vitorias, passa a 
        ser esse o maximo */
        /* se tiver um numero igual de vitorias, incrementa o numero de vencedores */
        if (e1->vitorias == max.maximo)
            max.num_venc++;
        else if (e1->vitorias > max.maximo)
        {
            max.maximo = e1->vitorias;
            max.num_venc = 1;
        }
        if (e2->vitorias == max.maximo)
            max.num_venc++;
        else if (e2->vitorias > max.maximo)
        {
            max.maximo = e2->vitorias;
            max.num_venc = 1;
        }

        /* continua a analisar */
        aux_b = aux_b->next; /* anda para a frente com o aux_b */
        aux_e = aux_e->prev; /* anda para tras com o aux_e */
    }
    return max;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                               INTERFACE ARVORE <-> EQUIPA                             */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que constroi uma arvore a partir duma fila, filtrando-a */
arvore * ARVbuild(arvore * raiz, fila equipas_ord, int maximo, int num_venc)
{
    node aux_b, aux_e; /* elementos a filtrar da fila equipas_ord */
    int i = 0; /* variavel auxiliar de controlo de ciclo */

    aux_b = equipas_ord->head; /* comecamos no inicio da fila */
    aux_e = equipas_ord->tail; /* e no fim tambem */

    while (i < num_venc) /* enquanto houver vencedoras a adicionar: vamos adiciona-las */
    {
        equipa e1, e2; /* equipas a adicionar a arvore */
        e1 = EQUIPA(aux_b->elem); /* fazemos o cast para equipa nos elementos */
        e2 = EQUIPA(aux_e->elem);

        /* vemos se os adicionamos a arvore */
        if (e1->vitorias == maximo) /* se o numero de vitorias for igual ao maximo */
        {
            raiz = ARVadd(raiz, e1); /* adiciona a arvore */
            i++; /* aumenta o numero de equipas adicionadas */
        }
        if (e2->vitorias == maximo)
        {
            raiz = ARVadd(raiz, e2);
            i++;
        }

        /* passamos para os proximos elementos */
        aux_b = aux_b->next; /* proximo */
        aux_e = aux_e->prev; /* anterior */
    }
    return raiz;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

