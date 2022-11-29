#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "principal.h"
#include "codigoAux.h"
#include "jogo.h"
#include "listaJogo.h"
#include "hashtableJogo.h"
#include "equipa.h"
#include "listaEquipa.h"
#include "hashtableEquipa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Le o comando e executa-o */
void analisaComando(char* comando, listaJogo** headsJogos, listaEquipa** headsEquipas, listaJogo* listaDeJogos, listaEquipa* listaDeEquipas, int M_J, int M_E, int* pNL) { 
    switch (comando[0]) {
        case 'a':
            a_adicionaJogo(comando, headsJogos, headsEquipas, listaDeJogos, M_J, M_E, pNL);
            break;
        case 'l':
            l_listaJogos(listaDeJogos, pNL);
            break;
        case 'p':
            p_procuraJogo(comando, headsJogos, M_J, pNL);
            break;
        case 'r':
            r_apagaJogo(comando, headsJogos, listaDeJogos, headsEquipas, M_J, M_E, pNL);
            break;
        case 's':
            s_alteraScoreJogo(comando, headsJogos, headsEquipas, M_J, M_E, pNL);
            break;
        case 'A':
            A_adicionaEquipa(comando, headsEquipas, listaDeEquipas, M_E, pNL);
            break;
        case 'P':
            P_procuraEquipa(comando, headsEquipas, M_E, pNL);
            break;
        case 'g':
            g_listaEquipasComMaisVitorias(listaDeEquipas, pNL);
            break;
        default:
            break;
    }
}

/* Adiciona um novo jogo ao sistema (ah hash table e ah lista de jogos) */
void a_adicionaJogo(char* comando, listaJogo** headsJogos, listaEquipa** headsEquipas, listaJogo* listaDeJogos, int M_J, int M_E, int* pNL) {
    int   i = 2;
    int*  pi = &i;
    char* auxNomeJogo, * auxEquipa1, * auxEquipa2;
    int   auxScore1, auxScore2;
    jogo* novoJogo;

    /* Obtem os nomes do comando; obtemString faz can_fail_malloc */
    auxNomeJogo = obtemString(comando, pi);
    auxEquipa1  = obtemString(comando, pi);
    auxEquipa2  = obtemString(comando, pi);

    /* Obtem os numeros do comando */
    auxScore1   = obtemNumero(comando, pi);
    auxScore2   = obtemNumero(comando, pi);

    if (jogoExiste(headsJogos, auxNomeJogo, M_J)) {
        printf("%d Jogo existente.\n", *pNL);

        /* Faz free das strings auxiliares */
        free(auxNomeJogo);
        free(auxEquipa1);
        free(auxEquipa2);
        return;
    }

    if ((!equipaExiste(headsEquipas, auxEquipa1, M_E)) || (!equipaExiste(headsEquipas, auxEquipa2, M_E))) {
        printf("%d Equipa inexistente.\n", *pNL);

        /* Faz free das strings auxiliares */
        free(auxNomeJogo);
        free(auxEquipa1);
        free(auxEquipa2);
        return;
    }

    /* Cria um jogo novo */
    novoJogo = criaJogo(auxNomeJogo, auxEquipa1, auxEquipa2, auxScore1, auxScore2, headsEquipas, M_E);
    /* Adiciona o jogo ah hash table */
    headsJogos = insereHashTableJogo(headsJogos, novoJogo, M_J);
    /* Adiciona o jogo ah lista ligada que mantem ordem de insercao */
    listaDeJogos = insereFimListaJogo(listaDeJogos, novoJogo);

    /* Faz free das strings auxiliares */
    free(auxNomeJogo);
    free(auxEquipa1);
    free(auxEquipa2);
}

/* Lista todos os jogos do sistema pela ordem de introducao */
void l_listaJogos(listaJogo* Lista, int* pNL) {
    /* Se a lista nao tiver sido inicializada ou estiver vazia */
    if (Lista->head == NULL || Lista == NULL) {
        return;
    }
    printListaJogo(Lista, pNL);
}

/* Procura um jogo no sistema (na hash table de jogos) */
void p_procuraJogo(char* comando, listaJogo** headsJogos, int M_J, int* pNL) {
    int   i = 2;
    int*  pi = &i;
    char* auxNome;
    jogo* jogoEncontrado;

    /* Obtem o nome do comando; obtemString faz can_fail_malloc */
    auxNome = obtemString(comando, pi);
 
    if (!jogoExiste(headsJogos, auxNome, M_J)) {
        printf("%d Jogo inexistente.\n", *pNL);

        /* Faz free da string auxiliar */
        free(auxNome);
        return;
    }

    jogoEncontrado = procuraHashTableJogo(headsJogos, auxNome, M_J);
    printJogo(jogoEncontrado, pNL);

    /* Faz free da string auxiliar */
    free(auxNome);
}

/* Apaga um jogo do sistema (na hash table e na lista de jogos) */
void r_apagaJogo(char* comando, listaJogo** headsJogos, listaJogo* Lista, listaEquipa** headsEquipas, int M_J, int M_E, int* pNL) {
    int     i = 2;
    int*    pi = &i;
    char*   auxNome;
    int     score1, score2;
    jogo*   auxJogo;
    equipa* auxEquipa;

    /* Obtem o nome do comando; obtemString faz can_fail_malloc */
    auxNome = obtemString(comando, pi);

    if (!jogoExiste(headsJogos, auxNome, M_J)) {
        printf("%d Jogo inexistente.\n", *pNL);

        /* Faz free da string auxiliar */
        free(auxNome);
        return;
    }

    auxJogo = procuraHashTableJogo(headsJogos, auxNome, M_J);
    score1 = auxJogo->score1;
    score2 = auxJogo->score2;

    /* Ao remover um jogo remover vitoria (se nao for empate) */
    if (score1 > score2) {
        auxEquipa = procuraHashTableEquipa(headsEquipas, auxJogo->equipa1, M_E);
        auxEquipa->numeroVitorias -= 1;
    }
    else if (score1 < score2) {
        auxEquipa = procuraHashTableEquipa(headsEquipas, auxJogo->equipa2, M_E);
        auxEquipa->numeroVitorias -= 1;
    }

    /* Remove o jogo da lista e da hash table */
    Lista = removeListaJogo(Lista, auxNome);
    headsJogos = removeHashTableJogo(headsJogos, auxNome, M_J);

    /* Liberta a memoria associada ao jogo */
    freeJogo(auxJogo);

    /* Faz free da string auxiliar */
    free(auxNome);
}

/* Altera o score de um jogo do sistema e, se for o caso, o numero de vitorias das equipas envolvidas */
void s_alteraScoreJogo(char* comando, listaJogo** headsJogos, listaEquipa** headsEquipas, int M_J, int M_E, int* pNL) {
    int     i = 2, novoScore1, novoScore2, score1Antigo, score2Antigo;
    int*    pi = &i;
    char*   auxNome;
    jogo*   jogoAux;
    equipa* equipaAux;

    /* Obtem o nome e os scores do comando; obtemString faz can_fail_malloc */
    auxNome = obtemString(comando, pi);
    novoScore1 = obtemNumero(comando, pi);
    novoScore2 = obtemNumero(comando, pi);

    if (!jogoExiste(headsJogos, auxNome, M_J)) {
        printf("%d Jogo inexistente.\n", *pNL);

        /* Faz free da string auxiliar */
        free(auxNome);
        return;
    }

    jogoAux = procuraHashTableJogo(headsJogos, auxNome, M_J);

    /* Guarda os scores antigos */
    score1Antigo = jogoAux->score1;
    score2Antigo = jogoAux->score2;

    /* Muda os scores */
    jogoAux->score1 = novoScore1;
    jogoAux->score2 = novoScore2;

    /* Se no novo score as equipas empataram */
    if (novoScore1 == novoScore2) {
            /* Se antes a equipa1 tinha ganho */ {
            if (score1Antigo > score2Antigo) {
                equipaAux = procuraHashTableEquipa(headsEquipas, jogoAux->equipa1, M_E);
                equipaAux->numeroVitorias -= 1;
            }
            /* Se antes a equipa2 tinha ganho */
            else if (score1Antigo < score2Antigo) {
                equipaAux = procuraHashTableEquipa(headsEquipas, jogoAux->equipa2, M_E);
                equipaAux->numeroVitorias -= 1;
            }
        }
    }

    /* Se antes da alteracao a equipa1 tinha ganho... */
    if (score1Antigo > score2Antigo) {
        /* ...e depois da alteracao quem ganhou foi a equipa2 */
        if (novoScore1 < novoScore2) {
            equipaAux = procuraHashTableEquipa(headsEquipas, jogoAux->equipa1, M_E);
            equipaAux->numeroVitorias -= 1;
            equipaAux = procuraHashTableEquipa(headsEquipas, jogoAux->equipa2, M_E);
            equipaAux->numeroVitorias += 1;
        }
    }
    /* Se antes da alteracao a equipa2 tinha ganho... */
    else if (score1Antigo < score2Antigo) {
        /* ...e depois da alteracao quem ganhou foi a equipa1 */
        if (novoScore1 > novoScore2) {
            equipaAux = procuraHashTableEquipa(headsEquipas, jogoAux->equipa2, M_E);
            equipaAux->numeroVitorias -= 1;
            equipaAux = procuraHashTableEquipa(headsEquipas, jogoAux->equipa1, M_E);
            equipaAux->numeroVitorias += 1;
        }
    }
    /* Se antes da alteracao as equipas tinham empatado... */
    else if (score1Antigo == score2Antigo) {
        /* ...e depois da alteracao quem ganhou foi a equipa2 */
        if (novoScore1 < novoScore2) {
            equipaAux = procuraHashTableEquipa(headsEquipas, jogoAux->equipa2, M_E);
            equipaAux->numeroVitorias += 1;
        }
        /* ...e depois da alteracao quem ganhou foi a equipa1 */
        else if (novoScore1 > novoScore2) {
            equipaAux = procuraHashTableEquipa(headsEquipas, jogoAux->equipa1, M_E);
            equipaAux->numeroVitorias += 1;
        }
    }

    /* Faz free da string auxiliar */
    free(auxNome);
}

/* Adiciona uma nova equipa ao sistema (ah hash table de equipas e ah lista de equipas) */
void A_adicionaEquipa(char* comando, listaEquipa** headsEquipas, listaEquipa* listaDeEquipas, int M_E, int* pNL) {
    int     i = 2;
    int*    pi = &i;
    char*   auxNome;
    equipa* novaEquipa;

    /* Obtem o nome do comando; obtemString faz can_fail_malloc */
    auxNome = obtemString(comando, pi);

    if (equipaExiste(headsEquipas, auxNome, M_E)) {
        printf("%d Equipa existente.\n", *pNL);

        /* Faz free da string auxiliar */
        free(auxNome);
        return;
    }

    /* Cria uma equipa nova */
    novaEquipa = criaEquipa(auxNome);
    /* Guarda-a na hash table */
    headsEquipas = insereHashTableEquipa(headsEquipas, novaEquipa, M_E);
    /* Adiciona a equipa ah lista ligada */
    listaDeEquipas = insereFimListaEquipa(listaDeEquipas, novaEquipa);

    /* Faz free da string auxiliar */
    free(auxNome);
}

/* Procura uma equipa no sistema (na hash table de equipas) */
void P_procuraEquipa(char* comando, listaEquipa** headsEquipas, int M_E, int* pNL) {
    int     i = 2;
    int*    pi = &i;
    char*   auxNome;
    equipa* equipaEncontrada;
    
    /* Obtem o nome do comando; obtemString faz can_fail_malloc */
    auxNome = obtemString(comando, pi);

    if (!equipaExiste(headsEquipas, auxNome, M_E)) {
        printf("%d Equipa inexistente.\n", *pNL);

        /* Faz free da string auxiliar */
        free(auxNome);
        return;
    }

    equipaEncontrada = procuraHashTableEquipa(headsEquipas, auxNome, M_E);
    printEquipa(equipaEncontrada, pNL);

    /* Faz free da string auxiliar */
    free(auxNome);
}

/* Imprime as equipas que venceram mais jogos por ordem lexicografica */
void g_listaEquipasComMaisVitorias(listaEquipa* ListaDeEquipas, int* pNL) {
    int         maxVitorias;
    int         tamanho = 0, i = 0;
    int*        pTamanho = &tamanho;
    nodeEquipa* auxNode;

    /* Array de strings que vai guardar o nome das equipas com mais vitorias */
    char equipasComMaisVitorias[500][MAXCAR];

    /* Se nao houver equipas no sistema */
    if (ListaDeEquipas == NULL || ListaDeEquipas->head == NULL) {
        return;
    }

    /* Se so existir uma equipa no sistema */
    if (ListaDeEquipas->head->next == NULL) {
        printf("%d Melhores %d\n", *pNL, ListaDeEquipas->head->Equipa->numeroVitorias);
        printf("%d * %s\n", *pNL, ListaDeEquipas->head->Equipa->nome);
        return;
    }

    /* Obtem o maximo de vitorias */
    maxVitorias = encontraMaxVitorias(ListaDeEquipas);

    /* Se Lista nao for vazia */
    auxNode = ListaDeEquipas->head;

    /* O while termina quando chego ao fim da lista */
    while (auxNode != NULL) {
        /* Se a equipa deste node tiver as mesmas vitorias que o maximo de vitorias */
        if (auxNode->Equipa->numeroVitorias == maxVitorias) {
            /* Copio o nome da equipa para o array de strings que esta a guardar os nomes */
            copia_String(equipasComMaisVitorias[i], auxNode->Equipa->nome);

            *pTamanho += 1;
            i++;
        }
        auxNode = auxNode->next;
    }

    /* Ordena lexicograficamente as equipas */
    qsort(equipasComMaisVitorias, *pTamanho, MAXCAR, comparaStrings);

    /* Output */
    printf("%d Melhores %d\n", *pNL, maxVitorias);
    for(i = 0; i < *pTamanho; i++) {
        printf("%d * %s\n", *pNL, equipasComMaisVitorias[i]);
    }
}

/* Compara duas strings e retorna um inteiro negativo, positivo ou 0 */
int comparaStrings(const void* string1, const void* string2) {
    return strcmp(string1, string2);
}

/* Le e retorna o numero seguinte da string comando */
int obtemNumero(char* comando, int* pi) {
    int  j = 0;
    char arrayNumero[MAXCAR];

    /* Enquanto eh um carater invalido salta */
    while (comando[*pi] < '0' || comando[*pi] > '9') {
        *pi += 1;
    }
    /* Enquanto eh um carater valido acrescenta ao numero a retornar */
    while (comando[*pi] >= '0' && comando[*pi] <= '9') {
        arrayNumero[j] = comando[*pi];
        *pi += 1;
        j++;
    }
    arrayNumero[j] = '\0';
    return atoi(arrayNumero);
}

/* Le e retorna a string seguinte da string comando; Aloca a string de forma dinamica */
char* obtemString(char* comando, int* pi) {
    int   j = 0;
    char  buffer[MAXCAR];
    char* aRetornar;

    /* Enquanto eh um carater invalido salta */
    while ( (comando[*pi] < '0' && comando[*pi] != '-' && comando[*pi] != 32 && comando[*pi] != '.' && comando[*pi] != '-' && comando[*pi] != '\'' && comando[*pi] != '(' && comando[*pi] != ')')
         || (comando[*pi] > '9' && comando[*pi] < 'A') 
         || (comando[*pi] > 'Z' && comando[*pi] < 'a')
         || (comando[*pi] > 'z') ) {
             *pi += 1;
         }
    /* Enquanto eh um carater valido acrescenta ah string a retornar */
    while ( (comando[*pi] >= '0' && comando[*pi] <= '9')
         || (comando[*pi] >= 'A' && comando[*pi] <= 'Z')
         || (comando[*pi] >= 'a' && comando[*pi] <= 'z')
         || (comando[*pi] == '-')
         || (comando[*pi] == '.')
         || (comando[*pi] == '\'')
         || (comando[*pi] == '(')
         || (comando[*pi] == ')')
         || (comando[*pi] == 32) ) {
            buffer[j++] = comando[*pi];
            *pi += 1;
         }

    *pi += 1;
    buffer[j] = '\0';

    /* Aloca a memoria necessaria e copia a buffer para a string alocada */
    aRetornar = (char*)can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
    copia_String(aRetornar, buffer);

    return aRetornar;
}

