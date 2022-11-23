#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "main.h"

/* Leitura e execucao os comandos. */
int main()
{

    HashTable jogos = HASHinit(M);
    HashTable equipas = HASHinit(M);
    LinkedList jogos_list = list_init();
    LinkedList equipas_list = list_init();

    int NL = 0;
    while (1)
    {
        char comando;
        NL++;
        /* Consoante o caracter fornecido eh chamada a funcao correspondente. */
        switch ((comando = getchar()))
        {
        case 'a':
            a(jogos, equipas, jogos_list, NL);
            break;
        case 'A':
            A(equipas, equipas_list, NL);
            break;
        case 'l':
            getchar();
            l(jogos_list, NL);
            break;
        case 'p':
            p(jogos, NL);
            break;
        case 'P':
            P(equipas, NL);
            break;
        case 'r':
            r(jogos, equipas, jogos_list, NL);
            break;
        case 's':
            s(jogos, equipas, NL);
            break;
        case 'g':
            getchar();
            g(equipas_list, NL);
            break;
        case 'x':
            destroy_hash(equipas);
            destroy_hash(jogos);
            destroy_list_nodes(jogos_list);
            destroy_list_nodes(equipas_list);
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

/* a Adiciona um novo jogo. */
void a(HashTable jogos, HashTable equipas, LinkedList jogos_list, int NL)
{
    /*Key nome, equipa1, equipa2;*/
    Jogo *j;
    Item new;
    char buffer[MAX_CHAR_NOME];
    char buffer1[MAX_CHAR_NOME];
    char buffer2[MAX_CHAR_NOME];
    int score1, score2;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d \n", buffer, buffer1, buffer2, &score1, &score2);
    /* se o jogo ja existe no sistema */
    if (search(jogos, buffer))
    {
        printf("%d Jogo existente.\n", NL);
    }
    /* se uma das equipas nao existe no sistema */
    else if (!search(equipas, buffer1) || !search(equipas, buffer2))
    {
        printf("%d Equipa inexistente.\n", NL);
    }
    else
    {
        j = can_fail_malloc(sizeof(Jogo));
        j->nome = strdup(buffer);
        j->equipa1 = strdup(buffer1);
        j->equipa2 = strdup(buffer2);
        j->score1 = score1;
        j->score2 = score2;
        new = newItem(JOGO, j);
        insert(jogos, new);
        append(jogos_list, new);
        if (score1 > score2)
        {
            atualiza_score(equipas, buffer1, 1);
        }
        else if (score2 > score1)
        {
            atualiza_score(equipas, buffer2, 1);
        }
    }
}

/* A Adiciona uma nova equipa. */
void A(HashTable equipas, LinkedList equipas_list, int NL)
{
    Item new;
    Equipa *e;
    char buffer[MAX_CHAR_NOME];

    scanf(" %[^:\n] ", buffer);

    if (search(equipas, buffer))
    {
        printf("%d Equipa existente.\n", NL);
    }
    else
    {
        e = can_fail_malloc(sizeof(Equipa));
        e->nome = strdup(buffer);
        e->jogos_ganhos = 0;
        new = newItem(EQUIPA, e);
        insert(equipas, new);
        append(equipas_list, new);
    }
}
/* l Lista todos os jogos pela ordem em que foram introduzidos. */
void l(LinkedList jogos_list, int NL)
{

    Jogo *j;
    Link atual;
    if (!is_empty(jogos_list))
    {
        for (atual = jogos_list->head; atual != NULL; atual = atual->next)
        {
            j = atual->item->data.jogo;
            printf("%d %s %s %s %d %d\n", NL, j->nome, j->equipa1, j->equipa2, j->score1, j->score2);
        }
    }
}
/* p Procura um jogo. */
void p(HashTable jogos, int NL)
{
    Jogo *j;
    char buffer[MAX_CHAR_NOME];
    Item jogo_item;
    scanf(" %s\n", buffer);
    jogo_item = search(jogos, buffer);
    if (jogo_item)
    {
        j = jogo_item->data.jogo;
        printf("%d %s %s %s %d %d\n", NL, buffer, j->equipa1, j->equipa2, j->score1, j->score2);
    }
    else
    {
        printf("%d Jogo inexistente.\n", NL);
    }
}
/* P Procura uma equipa. */
void P(HashTable equipas, int NL)
{
    char buffer[MAX_CHAR_NOME];
    Item equipa_node;
    scanf(" %[^:\n] ", buffer);
    equipa_node = search(equipas, buffer);
    if (equipa_node)
    {
        printf("%d %s %d\n", NL, buffer, equipa_node->data.equipa->jogos_ganhos);
    }
    else
    {
        printf("%d Equipa inexistente.\n", NL);
    }
}
/* r Apaga um jogo. */
void r(HashTable jogos, HashTable equipas, LinkedList jogos_list, int NL)
{
    char buffer[MAX_CHAR_NOME];
    char *vencedor;
    Jogo *jogo;
    Item jogo_item;
    scanf(" %[^:\n] ", buffer);
    jogo_item = search(jogos, buffer);
    if (jogo_item)
    {
        jogo = jogo_item->data.jogo;
        if (encontra_vencedor(jogo))
        {
            vencedor = strdup(encontra_vencedor(jogo));
        }
        else
        {
            vencedor = NULL;
        }
        destroy_list_node(jogos_list, buffer);
        delete (jogos, buffer);
        /* Atualiza o numero de vitorias das equipas */
        if (vencedor)
        {
            atualiza_score(equipas, vencedor, -1);
        }
        free(vencedor);
    }
    else
    {
        printf("%d Jogo inexistente.\n", NL);
    }
}
/* s Altera a pontuacao (_score_) de um jogo. */
void s(HashTable jogos, HashTable equipas, int NL)
{
    char buffer[MAX_CHAR_NOME];
    Key nome;
    Key vencedor;
    Key vencedor_apos_update;
    int score1, score2;
    Item jogo_item;
    Jogo *jogo;
    scanf(" %[^:\n]:%d:%d\n ", buffer, &score1, &score2);
    nome = strdup(buffer);
    jogo_item = search(jogos, buffer);
    if (jogo_item)
    {
        jogo = jogo_item->data.jogo;
        vencedor = encontra_vencedor(jogo);
        jogo->score1 = score1;
        jogo->score2 = score2;

        vencedor_apos_update = encontra_vencedor(jogo);

        if (vencedor && vencedor_apos_update)
        {
            if (strcmp(vencedor, vencedor_apos_update) != 0) /* se o vencedor mudou*/
            {
                atualiza_score(equipas, vencedor_apos_update, PLUS_ONE);
                atualiza_score(equipas, vencedor, MINUS_ONE);
            }
        }
        else if (vencedor && !vencedor_apos_update) /* empate apos update */
        {
            atualiza_score(equipas, vencedor, MINUS_ONE);
        }
        else if (!vencedor && vencedor_apos_update) /* de empate para uma vitoria*/
        {
            atualiza_score(equipas, vencedor_apos_update, PLUS_ONE);
        }
    }
    else
    {
        printf("%d Jogo inexistente.\n", NL);
    }
    free(nome);
}
/* g Encontra as equipas que venceram mais jogos. */
void g(LinkedList equipas_list, int NL)
{
    int max;
    Item e;
    Link atual;
    LinkedList sortedMaxEquipas;
    sortedMaxEquipas = findMaxVitorias(equipas_list);

    if (!is_empty(sortedMaxEquipas))
    {
        max = get_first_item(sortedMaxEquipas)->data.equipa->jogos_ganhos;
        printf("%d Melhores %d\n", NL, max);
        for (atual = sortedMaxEquipas->head; atual != NULL; atual = atual->next)
        {
            e = atual->item;
            printf("%d * %s\n", NL, e->value);
        }
    }
    destroy_list_nodes(sortedMaxEquipas);
}

/* Retorna lista com equipas que tem mais vitorias */
LinkedList findMaxVitorias(LinkedList equipas)
{
    Link current;
    int aux;
    LinkedList maxEquipas = list_init();
    int max = MIN;
    for (current = equipas->head; current; current = current->next)
    {
        aux = current->item->data.equipa->jogos_ganhos;
        if (aux > max)
        {
            max = aux;
            destroy_list_nodes(maxEquipas);
            maxEquipas = list_init();
            insertInOrder(maxEquipas, current->item);
        }
        else if (aux == max)
        {
            insertInOrder(maxEquipas, current->item);
        }
    }
    return maxEquipas;
}

/* atualiza score da equipa */
void atualiza_score(HashTable equipas, Key equipa, int change)
{
    Equipa *e;
    Item item;
    item = search(equipas, equipa);
    e = item->data.equipa;
    e->jogos_ganhos += change;
}

/* Retorna o nome do vencedor de um dado jogo */
char *encontra_vencedor(Jogo *jogo)
{
    if (jogo->score1 > jogo->score2)

    {
        return jogo->equipa1;
    }
    else if (jogo->score2 > jogo->score1)
    {
        return jogo->equipa2;
    }
    return DRAW;
}
