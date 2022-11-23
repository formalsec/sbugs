#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Equipas.h"
#include "Jogos.h"
#include "Misc.h"

/* FUNCOES BASICAS SOBRE EQUIPAS (adicao, procura e listagem das que possuem mais vitorias):
 * Estas funcoes recorrem a estruturas e outras funcoes presentes nos ficheiros Equipas.c e Equipas.h. */

/* Adiciona uma equipa ao sistema, caso ainda nao exista uma com o mesmo nome. */
equipa** adiciona_equipa(int cont_linhas, equipa** h_equipas, int* tam_h_equipas, int* cont_equipas)
{
    char nome[MAX];
    equipa* nova_equipa;
    scanf(" %1023[^:\n]", nome);
    if (procura_equipa_h(nome, h_equipas, *tam_h_equipas))
    {
        printf("%d Equipa existente.\n", cont_linhas);
        return h_equipas;
    }
    (*cont_equipas)++;
    nova_equipa = cria_equipa(nome);
    h_equipas = insere_equipa_h(h_equipas, nova_equipa, cont_equipas, tam_h_equipas);
    return h_equipas;
}

/* Procura uma equipa no sistema e devolve o seu nome e numero de vitorias, caso exista. */
void procura_equipa(int cont_linhas, equipa** h_equipas, int tam_h_equipas)
{
    char nome[MAX];
    equipa* equipa;
    scanf(" %1023[^:\n]", nome);
    if ((equipa = procura_equipa_h(nome, h_equipas, tam_h_equipas)))
    {
        printf("%d %s %d\n", cont_linhas, equipa -> nome, equipa -> vitorias);
        return;
    }
    printf("%d Equipa inexistente.\n", cont_linhas);
}

/* Exibe no ecran as equipas no sistema com mais vitorias, por ordem lexicografica,
 * caso exista pelo menos uma equipa no sistema. Se nao existir, esta funcao nada devolve.  
 * A hash table com as equipas e percorrida duas vezes: para obter o numero
 * maximo de vitorias e o numero de ocorrencias desse valor, e depois para
 * copiar os nomes das equipas corresponentes, sendo ordenado o array desses valores
 * antes de os apresentar. */
void encontra_melhores_equipas(int cont_linhas, equipa** h_equipas, int tam_h_equipas, int cont_equipas)
{
    if (cont_equipas)
    {
        int max = -1, num_max = 0, i, j = 0, k, l;
        char** melhores_equipas; /* Array usado para ordenar os nomes das melhores equipas no sistema. */
        for (i = 0; i < tam_h_equipas; i++)
        {
            if (h_equipas[i])
            {
                if (h_equipas[i] -> vitorias > max)
                {
                    max = h_equipas[i] -> vitorias;
                    num_max = 1;
                }
                else if (h_equipas[i] -> vitorias == max)
                    num_max++;
            }
        }
        melhores_equipas = (char**) can_fail_malloc (sizeof(char*) * num_max);
        for (k = 0; k < tam_h_equipas; k++)
            if (h_equipas[k] && h_equipas[k] -> vitorias == max)
                melhores_equipas[j++] = h_equipas[k] -> nome;
        qsort(melhores_equipas, num_max, sizeof(char*), comparador);
        printf("%d Melhores %d\n", cont_linhas, max);
        for (l = 0; l < j; l++)
        {
            printf("%d * %s\n", cont_linhas, melhores_equipas[l]);
        }
        free(melhores_equipas);
    }
}


/* FUNCOES BASICAS SOBRE JOGOS (adicao, procura, remocao, alteracao de resultados e
 * listagem por ordem de insercao): Estas funcoes recorrem a estruturas e outras funcoes 
 * presentes nos ficheiros Jogos.c, Jogos.h, Equipas.c e Equipas.h (em funcoes particulares). */

/* Adiciona um jogo novo ao sistema, caso ainda nao exista um com o mesmo nome,
 * e as equipas que se defrontam ja existam no sistema. */
jogo** adiciona_jogo(int cont_linhas, jogo** h_jogos, lista_jogos* lst_jogos, int* tam_h_jogos, int* cont_jogos, equipa** h_equipas, int* tam_h_equipas)
{
    char nome_jogo[MAX], nome_casa[MAX], nome_fora[MAX];
    equipa *eq_casa, *eq_fora;
    int golos_casa, golos_fora;
    jogo* novo_jogo;
    scanf(" %1023[^:\n]:%1023[^:\n]:%1023[^:\n]:%d:%d", nome_jogo, nome_casa, nome_fora, &golos_casa, &golos_fora);
    if (procura_jogo_h(nome_jogo, h_jogos, *tam_h_jogos))
    {
        printf("%d Jogo existente.\n", cont_linhas);
        return h_jogos;
    }
    if (!((eq_casa = procura_equipa_h(nome_casa, h_equipas, *tam_h_equipas)) &&
          (eq_fora = procura_equipa_h(nome_fora, h_equipas, *tam_h_equipas))))
    {
        printf("%d Equipa inexistente.\n", cont_linhas);
        return h_jogos;
    }
    (*cont_jogos)++;
    novo_jogo = cria_jogo(nome_jogo, eq_casa, eq_fora, golos_casa, golos_fora);
    insere_fim_jogo(lst_jogos, novo_jogo);
    h_jogos = insere_jogo_h(h_jogos, novo_jogo, cont_jogos, tam_h_jogos);
    return h_jogos;
}

/* Procura um jogo no sistema e devolve o seu nome as equipas
 * que se defrontam e o resultado do jogo, caso este exista. */ 
void procura_jogo(int cont_linhas, jogo** h_jogos, int tam_h_jogos)
{
    char nome[MAX];
    jogo* jogo;
    scanf(" %1023[^:\n]", nome);
    if ((jogo = procura_jogo_h(nome, h_jogos, tam_h_jogos)))
    {
        printf("%d %s %s %s %d %d\n", cont_linhas, jogo -> nome, jogo -> eq_casa -> nome,
        jogo -> eq_fora -> nome, jogo -> golos_casa, jogo -> golos_fora);
        return;
    }
    printf("%d Jogo inexistente.\n", cont_linhas);
}

/* Remove um jogo do sistema (retirando da hash table e da lista dos jogos), caso exista. */
jogo** remove_jogo(int cont_linhas, jogo** h_jogos, lista_jogos* lst_jogos, int* tam_h_jogos, int* cont_jogos)
{
    char nome[MAX];
    int i, j;
    jogo* aux;
    scanf(" %1023[^:\n]", nome);
    i = hash(nome, *tam_h_jogos);
    for (; h_jogos[i]; i = (i+1) % (*tam_h_jogos))
        if (!strcmp(h_jogos[i] -> nome, nome))
        {
            repor_score(h_jogos[i] -> eq_casa, h_jogos[i] -> eq_fora,
                        h_jogos[i] -> golos_casa, h_jogos[i] -> golos_fora);
            remove_jogo_lst(lst_jogos, nome);
            free(h_jogos[i] -> nome);
            free(h_jogos[i]);
            h_jogos[i] = NULL;
            (*cont_jogos)--;
            for (j = (i+1) % (*tam_h_jogos); h_jogos[j]; j = (j+1) % (*tam_h_jogos))
            {
                (*cont_jogos)--;
                aux = h_jogos[j];
                h_jogos[j] = NULL;
                h_jogos = insere_jogo_h(h_jogos, aux, cont_jogos, tam_h_jogos);
            }
            return h_jogos;
        }
    printf("%d Jogo inexistente.\n", cont_linhas);
    return h_jogos;
}

/* Altera o resultado de um jogo (e, por consequencia, atualiza o
 * numero de vitorias das equipas que se defrontam), caso exista. */
void altera_score(int cont_linhas, jogo** h_jogos, int tam_h_jogos)
{
    char nome[MAX];
    int novos_golos_casa, novos_golos_fora;
    jogo* jogo;
    scanf(" %1023[^:\n]:%d:%d", nome, &novos_golos_casa, &novos_golos_fora);
    if (!(jogo = procura_jogo_h(nome, h_jogos, tam_h_jogos)))
        printf("%d Jogo inexistente.\n", cont_linhas);
    else
    {
        repor_score(jogo -> eq_casa, jogo -> eq_fora, jogo -> golos_casa, jogo -> golos_fora);
        jogo -> golos_casa = novos_golos_casa;
        jogo -> golos_fora = novos_golos_fora;
        atribui_vitoria(jogo -> eq_casa, jogo -> eq_fora, jogo -> golos_casa, jogo -> golos_fora);
    } 
}

/* Apresenta todos os jogos existentes no sistema pela ordem de
 * insercao, com recurso a uma lista duplamente ligada de jogos. */
void listar_jogos(int cont_linhas, lista_jogos* lst_jogos)
{
    node_jogo* aux = lst_jogos -> inicio;
    while (aux)
    {
        if (aux -> jogo)
            printf("%d %s %s %s %d %d\n", cont_linhas, aux -> jogo -> nome, aux -> jogo -> eq_casa -> nome,
            aux -> jogo -> eq_fora -> nome, aux -> jogo -> golos_casa, aux -> jogo -> golos_fora);
        aux = aux -> prox;
    }
}

/* Recebe uma letra como comando e invoca a funcao correspondente, como
descrito no enunciado do projeto. O comando 'x' encerra o programa. */
int main()
{
    /* Inicializacao do numero da linha do input, de equipas e de jogos no sistema, alem do tamanho das hash tables correspondentes. */
    int cont_linhas = 0, cont_equipas = 0, cont_jogos = 0, tam_h_equipas = HASH, tam_h_jogos = HASH;
    /* Inicializacao das hash tables das equipas e dos jogos, alem da lista de jogos que permite listar, por ordem de insercao, as equipas do sistema. */
    equipa** h_equipas = (equipa**) can_fail_calloc (tam_h_equipas, sizeof(equipa*)); 
    jogo** h_jogos = (jogo**) can_fail_calloc (tam_h_jogos, sizeof(jogo));
    lista_jogos* lst_jogos = cria_lst_jogos();
    char comm; /* Inicializacao do caracter usado como comando do programa. */
    while ((comm = getchar()) != 'x') /* Introducao do comando. */
    {
        switch (comm)
        {
            case 'a':
                h_jogos = adiciona_jogo(++cont_linhas, h_jogos, lst_jogos, &tam_h_jogos, &cont_jogos, h_equipas, &tam_h_equipas);
                break;
            case 'A':
                h_equipas = adiciona_equipa(++cont_linhas, h_equipas, &tam_h_equipas, &cont_equipas);
                break;
            case 'l':
                listar_jogos(++cont_linhas, lst_jogos);
                break;
            case 'p':
                procura_jogo(++cont_linhas, h_jogos, tam_h_jogos);
                break;
            case 'P':
                procura_equipa(++cont_linhas, h_equipas, tam_h_equipas);
                break;
            case 'r':
                h_jogos = remove_jogo(++cont_linhas, h_jogos, lst_jogos, &tam_h_jogos, &cont_jogos);
                break;
            case 's':
                altera_score(++cont_linhas, h_jogos, tam_h_jogos);
                break;
            case 'g':
                encontra_melhores_equipas(++cont_linhas, h_equipas, tam_h_equipas, cont_equipas);
                break;
        }
    }
    destroi_h_jogos(h_jogos, tam_h_jogos);
    destroi_lst_jogos(lst_jogos);
    destroi_h_equipas(h_equipas, tam_h_equipas);
    return 0;
}
