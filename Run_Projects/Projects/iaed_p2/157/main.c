#include <stdio.h>
#include "jogos.h"


/* Adiciona um novo jogo, e devolve a tabela de jogos atualizada */
link_jogo * a (int NL, pt_nome * nomes_jogos, link_jogo * jogos, link_equipa * equipas)
{
    int score1, score2;
    
    char nome[WORD_SIZE], equipa1[WORD_SIZE], equipa2[WORD_SIZE];
    
    pt_jogo jogo_novo;

    
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);

    /* Levantar erros caso o jogo ja exista, ou uma das equipas nao exista */
    if (jogo_existe(nome, jogos)) {
        printf("%d Jogo existente.\n", NL);
        return jogos;

    } else if (!equipa_existe(equipa1, equipas)) {
        printf("%d Equipa inexistente.\n", NL);
        return jogos;

    } else if (!equipa_existe(equipa2, equipas)) {
        printf("%d Equipa inexistente.\n", NL);
        return jogos;
    }

    /* Cria um jogo novo e insere-o na tabela */
    jogo_novo = novo_jogo(nome, equipa1, equipa2, score1, score2, equipas);
    insere_jogo_tabela(jogo_novo, jogos);

    /* Adiciona o nome do jogo a lista de nomes */
    *nomes_jogos = novo_nome(nome, *nomes_jogos);

    /* Incrementa o numero de vitorias da equipa vencedora caso exista */
    if (score1 > score2)
        jogo_novo->equipa1->vitorias++;
        
    else if (score2 > score1)
        jogo_novo->equipa2->vitorias++;
    

    return jogos;
}


/* Adiciona uma nova equipa, devolve a tabela de equipas atualizada */
link_equipa * A(int NL, link_equipa * equipas)
{
    char nome[WORD_SIZE];
    pt_equipa equipa;

    scanf(" %[^:\n]", nome);

    /* Levanta erro caso a equipa ja exista */
    if (equipa_existe(nome, equipas)) {
        printf("%d Equipa existente.\n", NL);

        return equipas;

    } else {
        /* Cria nova equipa */
        equipa = nova_equipa(nome);

        /* Insere a nova equipa na tabela */
        insere_equipa_tabela(equipa, equipas);

        return equipas;
    }
}


/* Lista todos os jogos pela ordem em que foram introduzidos */
void l(int NL, pt_nome nomes_jogos, link_jogo * jogos)
{
    pt_jogo jogo;

    /* Percorre a lista de nomes, para cada um encontra o respetivo jogo e faz o print */
    while (nomes_jogos->next != NULL)
    {
        jogo = procura_jogo(nomes_jogos->nome, jogos);
        
        printf("%d %s %s %s %d %d\n", NL, nomes_jogos->nome, jogo->equipa1->nome, 
            jogo->equipa2->nome, jogo->score1, jogo->score2);

        nomes_jogos = nomes_jogos->next;
    }
}


/* Procura um jogo */
void p(int NL, link_jogo * jogos)
{
    char nome[WORD_SIZE];
    pt_jogo jogo;

    scanf(" %[^:\n]", nome);

    /* Procura o jogo na tabela */
    jogo = procura_jogo(nome, jogos);

    /* Se for NULL o jogo nao existe no sistema, caso contrario faz o print */
    if (jogo == NULL) 
        printf("%d Jogo inexistente.\n", NL);
    else
        printf("%d %s %s %s %d %d\n", NL, nome, jogo->equipa1->nome,
            jogo->equipa2->nome, jogo->score1, jogo->score2);
}


/* Procura uma equipa */
void P(int NL, link_equipa * equipas)
{
    char nome[WORD_SIZE];
    pt_equipa equipa;

    scanf(" %[^:\n]", nome);

    /* Procura a equipa na tabela */
    equipa = procura_equipa(nome, equipas);

    /* Se for NULL a equipa nao existe no sistema, caso contrario faz o print */
    if (equipa == NULL)
        printf("%d Equipa inexistente.\n", NL);

    else
        printf("%d %s %d\n", NL, nome, equipa->vitorias);
}


/* Apaga um jogo, devolve a tabela atualizada */
link_jogo * r(int NL, pt_nome * nomes_jogos, link_jogo * jogos)
{
    char nome[WORD_SIZE];

    scanf(" %[^:\n]", nome);

    /* Levanta erro caso o jogo nao exista */
    if (!jogo_existe(nome, jogos)) {
        printf("%d Jogo inexistente.\n", NL);
        return jogos;

    } else {
        /* Apaga o jogo da tabela */
        apaga_jogo_tabela(nome, jogos);

        /* Apaga o nome do jogo da lista de nomes */
        *nomes_jogos = apaga_nome_lista(*nomes_jogos, nome);

        return jogos;
    }
}


/* Altera a pontuacao de um jogo, devolve a tabela atualizada */
link_jogo * s(int NL, link_jogo * jogos)
{
    char nome[WORD_SIZE];
    pt_jogo jogo;
    int score1, score2;

    scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);
    
    /* Procura o jogo na tabela */
    jogo = procura_jogo(nome, jogos);

    /* Se o resultado for NULL ele nao existe*/
    if (jogo == NULL){
        printf("%d Jogo inexistente.\n", NL);
        return jogos;

    } else
    {
        /* Casos em que troca a equipa vencedora*/
        if ((jogo->score1 > jogo->score2) && (score1 < score2)){
            jogo->equipa1->vitorias--;
            jogo->equipa2->vitorias++;

        } else if ((jogo->score1 < jogo->score2) && (score1 > score2)){
            jogo->equipa2->vitorias--;
            jogo->equipa1->vitorias++;

        /* Casos em que passa a empate */
        } else if ((jogo->score1 > jogo->score2) && (score1 == score2))
            jogo->equipa1->vitorias--;

        else if ((jogo->score1 < jogo->score2) && (score1 == score2))
            jogo->equipa2->vitorias--;
        
        /* Casos em que passa a estar uma equipa a ganhar */
        else if ((jogo->score1 == jogo->score2) && (score1 > score2))
            jogo->equipa1->vitorias++;
        
        else if ((jogo->score1 == jogo->score2) && (score1 < score2))
            jogo->equipa2->vitorias++;

        
        /* Atualiza as pontuacoes do jogo */
        jogo->score1 = score1;
        jogo->score2 = score2;
    
        return jogos;   
    }
}


/* Encontra as equipas que venceram mais jogos */
void g(int NL, link_equipa * equipas)
{
    pt_nome nomes[WORD_SIZE];
    link_equipa aux;
    
    int i;
    /* Comprimento de cada nome (comp) e comprimento da maior palavra (para o qsort) */
    int comp, max_comp = 0;
    /* Numero de nomes a listar (size) e o respetivo numero de vitorias (max_score) */
    int size, max_score = max_vitorias(equipas);

    /* Guarda o numero de nomes adicionados a lista de nomes */
    size = 0;
    
    /* Percorre a tabela e, para cada equipa com o score maximo, guarda o nome */
    /* na lista nomes e vai guardando o maior comprimento de nome que encontra em max_comp */
    for (i = 0; i < (TAB_SIZE/2); i++) {
        aux = equipas[i];
        
        while(aux != NULL)
        {            
            if (aux->equipa->vitorias == max_score) {
                comp = strlen(aux->equipa->nome) + 1;

                if (comp > max_comp) max_comp = comp;

                nomes[size] = (pt_nome) malloc(sizeof(struct nome));
                nomes[size]->nome = (char*) malloc(comp * sizeof(char));
                
                strcpy(nomes[size]->nome, aux->equipa->nome);

                size++;
            }
            
            aux = aux->next;
        }        
    }

    qsort(nomes, size, max_comp, compara);

    if(size > 0) printf("%d Melhores %d\n", NL, max_score);
    
    for (i = 0; i < size; i++){
        printf("%d * %s\n", NL, nomes[i]->nome);
    
        free(nomes[i]->nome);
        free(nomes[i]);
    }
}


/* MAIN */
int main()
{
    /* Comando */
    char com;
    /* Numero da linha */
    int NL = 0;

    /* tabela de jogos */
    link_jogo * jogos;
    
    /* tabela de equipas */
    link_equipa * equipas;

    /* lista de nomes de jogos criados por ordem de insercao */
    pt_nome nomes_jogos = (pt_nome) malloc(sizeof(struct nome));

    nomes_jogos->next = NULL;

    jogos = (link_jogo*) malloc(TAB_SIZE * sizeof(struct node_jogo));   
    jogos = init_jogos(jogos);

    equipas = (link_equipa*) malloc((TAB_SIZE / 2) * sizeof(struct node_equipa)); 
    equipas = init_equipas(equipas);


    /* Loop que recebe os comandos */
    while ((com = getchar()) != 'x')
    {
        switch (com)
        {
            case 'a':
                NL++;
                jogos = a(NL, &nomes_jogos, jogos, equipas);
                break;
            
            case 'A':
                NL++;
                equipas = A(NL, equipas);
                break;
            
            case 'l':
                NL++;
                l(NL, nomes_jogos, jogos);
                break;

            case 'p':
                NL++;
                p(NL, jogos);
                break;
            
            case 'P':
                NL++;
                P(NL, equipas);
                break;

            case 'r':
                NL++;
                r(NL, &nomes_jogos, jogos);
                break;

            case 's':
                NL++;
                s(NL, jogos);
                break;            
            
            
            case 'g':
                NL++;
                g(NL, equipas);
                break;

            default:
                break;
        }
    }

    free_all(jogos, equipas, nomes_jogos);
    
    return 0;
}
