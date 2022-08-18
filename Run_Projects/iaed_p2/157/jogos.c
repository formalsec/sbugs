#include "jogos.h"


pt_jogo novo_jogo (char * nome, char * equipa1, char * equipa2, int score1, int score2, link_equipa * equipas)
{
    pt_jogo jogo_novo;

    int comp = (strlen(nome) + 1);  /* '/0' */  

    /* Cria ponteiros para as equipas do jogo */
    pt_equipa pt_equipa1 = procura_equipa(equipa1, equipas);
    pt_equipa pt_equipa2 = procura_equipa(equipa2, equipas);
        
    /* Aloca espaco para o novo jogo */
    jogo_novo = (pt_jogo) malloc(sizeof(struct jogo));

    /* Aloca espaco para o nome do jogo e atribui-lo */
    jogo_novo->nome = (char*) malloc(comp * sizeof(char));
    strcpy(jogo_novo->nome, nome);

    /* Atribui os ponteiros */
    jogo_novo->equipa1 = pt_equipa1;
    jogo_novo->equipa2 = pt_equipa2;
    
    /* Atribui as pontuacoes as respetivas equipas */
    jogo_novo->score1 = score1;
    jogo_novo->score2 = score2;

    return jogo_novo;
}


pt_jogo procura_jogo (char * nome, link_jogo * jogos)
{
    /* Encontra o indice do jogo na tabela */
    int indice = hash_jogo(nome);
    
    link_jogo tmp;

    /* Ponteiro temporario aponta para primeiro elemento do indice */
    tmp = jogos[indice];

    /* Percorre os elementos desse indice ate ao fim ou ate encontrar o jogo pretendido */
    while (tmp != NULL && (strcmp(tmp->jogo->nome, nome) != 0))
        tmp = tmp->next;
    
    /* Devolve ponteiro para jogo caso encontre, NULL caso contrario */
    if (tmp == NULL)
        return NULL;
    else
        return tmp->jogo;
}


void apaga_jogo_tabela (char * nome, link_jogo * jogos)
{
    /* Encontra o indice do jogo na tabela */    
    int indice = hash_jogo(nome);
    
    link_jogo tmp, aux;

    /* tmp aponta para o primeiro elemento do indice */
    tmp = jogos[indice];

    /* Caso o jogo que queremos apagar seja o primeiro do indice */
    if (strcmp(tmp->jogo->nome, nome) == 0){
        /* Segundo elemento passa a ser o primeiro */
        jogos[indice] = tmp->next;
        
        
        /* Retira uma vitoria a equipa que tinha ganho, no caso de nao ser empate */
        if (tmp->jogo->score1 > tmp->jogo->score2)
            tmp->jogo->equipa1->vitorias--;
        
        else if (tmp->jogo->score1 < tmp->jogo->score2)
            tmp->jogo->equipa2->vitorias--;
        
        
        /* Liberta o espaco alocado para o jogo a apagar */
        free_jogo(tmp->jogo);
        /* Liberta tmp */
        free(tmp);


    } else { /* Percorrer os restantes jogos do indice ate encontrar */
        while ((strcmp(tmp->next->jogo->nome, nome) != 0))
            tmp = tmp->next;
        /* Agora tmp->next e o jogo que queremos apagar */

        
        /* Ponteiro auxiliar aponta para o jogo a apagar */
        aux = tmp->next;
        /* O elemento anterior aponta agora para o seguinte */
        tmp->next = tmp->next->next;

        
        /* Retira uma vitoria a equipa que tinha ganho, no caso de nao ser empate */
        if (aux->jogo->score1 > aux->jogo->score2)
            aux->jogo->equipa1->vitorias--;
        
        else if (aux->jogo->score1 < aux->jogo->score2)
            aux->jogo->equipa2->vitorias--;
        

        /* Liberta o espaco alocado para o jogo a apagar */
        free_jogo(aux->jogo);
        /* Liberta aux */
        free(aux);
        /* Liberta tmp */
        free(tmp);
    }
}


bool jogo_existe (char * nome, link_jogo * jogos)
{
    /* Caso o procura jogo devolva NULL, o jogo nao existe no sistema */
    return (procura_jogo(nome, jogos) != NULL);
}


void insere_jogo_tabela (pt_jogo jogo, link_jogo * jogos)
{
    /* Encontra o indice do jogo na tabela */
    int indice = hash_jogo(jogo->nome);

    /* Aloca espaco para o novo elemento da tabela */
    link_jogo new = (link_jogo) malloc(sizeof(struct node_jogo));

    /* Adiciona o jogo ao inicio da lista ligada do seu indice */
    new->jogo = jogo;
    new->next = jogos[indice];
    jogos[indice] = new;
}


void free_jogo(pt_jogo jogo)
{
    /* Liberta espaco associado ao jogo e ao seu nome */
    free(jogo->nome);
    free(jogo);
}


link_jogo * init_jogos (link_jogo * tabela)
{
    int i;
    
    for (i = 0; i < TAB_SIZE; i++)
        tabela[i] = NULL;

    return tabela;
}


pt_nome apaga_nome_lista (pt_nome nomes_jogos, char * nome)
{
    pt_nome aux;
    pt_nome head = nomes_jogos;
    
    /* Caso o nome a apagar seja a cabeca da lista */
    if (strcmp(nomes_jogos->nome, nome) == 0) {
        /* Atualiza cabeca para segundo elemento */
        head = nomes_jogos->next;
        
        /* Liberta espaco associado ao struct nome e o seu nome */
        free(nomes_jogos->nome);
        free(nomes_jogos);

    } else { /* Percorrer o resto da lista ate encontrar */
        while (nomes_jogos->next != NULL && strcmp(nomes_jogos->next->nome, nome) != 0)
            nomes_jogos = nomes_jogos->next;
        /* Agora nomes_jogos->next e o elemento que queremos apagar */
        
        /* Ponteiro auxiliar aponta para o nome a apagar */
        aux = nomes_jogos->next;
        /* Nome anterior passa a apontar para o seguinte */
        nomes_jogos->next = nomes_jogos->next->next;

        /* Liberta o espaco associado ao struct nome e o seu nome */
        free(aux->nome);
        free(aux);
    }
    
    /* Devolve a cabeca da lista atualizada */
    return head;
}


void free_all (link_jogo * jogos, link_equipa * equipas, pt_nome nomes_jogos)
{
    int i;
    
    pt_nome aux_nome;
    link_equipa aux_equipa;
    link_jogo aux_jogo;

    /* Percorre a tabela de jogos, libertando o espaco associado a todos os elementos */
    for (i = 0; i < TAB_SIZE; i++)
    {
        while (jogos[i] != NULL) {                
            free_jogo(jogos[i]->jogo);

            aux_jogo = jogos[i];

            jogos[i] = jogos[i]->next;

            free(aux_jogo);
        }
    }

    /* Percorre a tabela de equipas, libertando o espaco associado a todos os elementos */
    for (i = 0; i < (TAB_SIZE/2); i++)
    {
        while(equipas[i] != NULL){
            free_equipa(equipas[i]->equipa);
            
            aux_equipa = equipas[i];

            equipas[i] = equipas[i]->next;

            free(aux_equipa);
        }       
    }

    /* Percorre a lista de nomes, libertando o espaco associado a todos os elementos */
    while (nomes_jogos->next != NULL)
    {
        free(nomes_jogos->nome);
        
        aux_nome = nomes_jogos;
        nomes_jogos = nomes_jogos->next;
        
        free(aux_nome);
    }

    /* Liberta o espaco associado as estruturas em si */
    free(jogos);
    free(equipas);
    free(nomes_jogos);
}


pt_nome novo_nome (char * nome, pt_nome nomes_jogos)
{
    /* Comprimento do nome dado */
    int comp;

    pt_nome novo_nome;

    pt_nome head = nomes_jogos;

    /* Aloca espaco para novo struct nome */
    novo_nome = (pt_nome) malloc(sizeof(struct nome));
    novo_nome->next = NULL;
    
    /* Encontra ultimo elemento da lista */
    while (nomes_jogos->next != NULL)
        nomes_jogos = nomes_jogos->next;
    
    /* Coloca novo elemento no fim da lista */
    nomes_jogos->next = novo_nome;

    /* Aloca espaco para o nome (string) */
    comp = strlen(nome) + 1;    
    nomes_jogos->nome = (char*) malloc(comp * sizeof(char));

    /* Atribui o nome ao agora penultimo elemento da lista */
    strcpy(nomes_jogos->nome, nome);
    
    /* Devolve a cabeca da lista */
    return head;
}
