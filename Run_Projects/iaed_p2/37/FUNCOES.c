#include "FUNCOES.h"

/* 
 * Adiciona um jogo ao sistema caso o jogo ainda nao exista e apenas se ambas as equipas existirem.
 * Recebe NL, head e tail da lista de jogos, e pointer para as hash tables de equipas e de jogos.
*/
void adicionaJogo(int NL, glink* pLGhead, glink* pLGtail, tlink* HashTeams, glink* HashGames) {
    char buffer[MAXSIZE], equipa1[MAXSIZE], equipa2[MAXSIZE];
    int score1, score2, aux, indice;
    pGame NovoJogo, JogoExistente;
    pTeam pTeam1, pTeam2;
    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", buffer, equipa1, equipa2, &score1, &score2);
    aux = searchGameHash(buffer+1, HashGames, &JogoExistente); 
    /* Caso ja exista um jogo com o nome dado. */
    if (aux == 1) {       
        printf("%d Jogo existente.\n", NL);
        return;
    }
    aux = adicionaJogo_aux(equipa1, equipa2, HashTeams, &pTeam1, &pTeam2);
    /* Caso ambas as equipas existam. */
    if (aux == 0) {
        NovoJogo = malloc(sizeof(struct Game));
        NovoJogo -> score1 = score1;
        NovoJogo -> score2 = score2;
        NovoJogo -> pEquipa1 = pTeam1;
        NovoJogo -> pEquipa2 = pTeam2;
        NovoJogo -> name = malloc(sizeof(char)*(strlen(buffer)+1));
        strcpy((NovoJogo -> name), buffer+1);
        put_game(NovoJogo, pLGhead, pLGtail);  /* Coloca NovoJogo no fim da lista de jogos. */
        indice = hash(buffer+1);
        Ginsert(&HashGames[indice], NovoJogo); /* Coloca NovoJogo na hash table dos jogos. */
        atualizaVitorias(NovoJogo, 0, 0, 0);   /* Atualiza as vitorias das equipas. */
    }
    else
        printf("%d Equipa inexistente.\n", NL);
}

/*================================================================================================*/

/* 
 * Adiciona uma equipa ao sistema caso a equipa ainda nao exista.
 * Recebe NL, head e tail da lista de equipas, e pointer para a hash table de equipas.
*/
void adicionaEquipa(int NL, tlink* pLThead, tlink* pLTtail, tlink* HashTeams) {
    char buffer[MAXSIZE];
    int aux, indice;
    pTeam NovaEquipa, EquipaExistente;
    scanf("%[^\n]", buffer);
    aux = searchTeamHash(buffer+1, HashTeams, &EquipaExistente);
    /* Caso a equipa nao exista. */
    if (aux == 0) {
        NovaEquipa = malloc(sizeof(struct Team));
        NovaEquipa -> vitorias = 0;              
        NovaEquipa -> name = malloc(sizeof(char)*(strlen(buffer+1)+1));
        strcpy(NovaEquipa -> name, buffer+1);
        put_team(NovaEquipa, pLThead, pLTtail);  /* Coloca NovaEquipa no fim da lista de equipas. */
        indice = hash(buffer+1);
        Tinsert(&HashTeams[indice], NovaEquipa); /* Coloca NovaEquipa na hash table das equipas. */
    }
    else
        printf("%d Equipa existente.\n", NL);
}

/*================================================================================================*/

/* 
 * Lista todos os jogos do sistema pela ordem em que foram introduzidos.
 * Recebe NL e head da lista de jogos.
*/
void listaJogos(int NL, glink* pLGhead) {
    glink c;
    char *name, *nameTeam1, *nameTeam2;
    int score1, score2;
    /* Ciclo que percorre todos os nodes da lista de jogos, em cada iteracao "imprime" um jogo. */
    for (c = *pLGhead; c != NULL; c = c -> next) {
        name = c -> pJogo -> name;
        nameTeam1 = c -> pJogo -> pEquipa1 -> name;
        nameTeam2 = c -> pJogo -> pEquipa2 -> name;
        score1 = c -> pJogo -> score1;
        score2 = c -> pJogo -> score2;
        printf("%d %s %s %s %d %d\n", NL, name, nameTeam1, nameTeam2, score1, score2);
    }
}

/*================================================================================================*/

/* 
 * Procura um jogo e "imprime" as informacoes desse jogo.
 * Recebe NL e pointer para a hash table de jogos.
*/
void procuraJogo(int NL, glink* HashGames) {
    char buffer[MAXSIZE], *nameTeam1, *nameTeam2;
    int aux, score1, score2;
    pGame hit;
    scanf("%[^:\n]", buffer);
    /* hit eh um pointer para o jogo pretendido apos execucao de searchGameHash. */
    aux = searchGameHash(buffer+1, HashGames, &hit);
    /* Caso o jogo exista. */
    if (aux == 1) {
        nameTeam1 = hit -> pEquipa1 -> name;
        nameTeam2 = hit -> pEquipa2 -> name;
        score1 = hit -> score1;
        score2 = hit -> score2;
        printf("%d %s %s %s %d %d\n", NL, buffer+1, nameTeam1, nameTeam2, score1, score2);
    }
    else
        printf("%d Jogo inexistente.\n", NL);
}

/*================================================================================================*/

/* 
 * Procura uma equipa e "imprime" o seu nome e numero de vitorias.
 * Recebe NL e pointer para a hash table de equipas.
*/
void procuraEquipa(int NL, tlink* HashTeams) {
    char buffer[MAXSIZE];
    int aux;
    pTeam hit;
    scanf("%[^\n]", buffer);
    /* hit eh um pointer para a equipa pretendida apos execucao de searchTeamHash. */
    aux = searchTeamHash(buffer+1, HashTeams, &hit);
    /* Caso a equipa exista. */
    if (aux != 1 )
        printf("%d Equipa inexistente.\n", NL);
    else
        printf("%d %s %d\n", NL, hit -> name, hit -> vitorias);   
}

/*================================================================================================*/

/* 
 * Apaga um jogo do sistema caso o jogo exista.
 * Recebe NL, head e tail da lista de jogos e pointer para a hash table de jogos.
*/
void apagaJogo(int NL, glink* pLGhead, glink* pLGtail, glink* HashGames) {
    char buffer[MAXSIZE];
    int aux;
    pGame hit;
    scanf("%[^:\n]", buffer);
    /* hit eh um pointer para o jogo a ser eliminado apos execucao de searchGameHash. */
    aux = searchGameHash(buffer+1, HashGames, &hit);
    /* Caso jogo exista. */
    if (aux == 1) {
        atualizaVitorias(hit, 1, 0, 0);          /* "Remove" vitoria da equipa vencedora do jogo. */
        apagaJogoHash(buffer+1, HashGames, hit); 
        apagaJogoLista(pLGhead, pLGtail, hit);
    }
    else
        printf("%d Jogo inexistente.\n", NL);
}

/*================================================================================================*/

/* 
 * Altera score de um jogo caso o jogo exista.
 * Recebe NL e pointer para a hash table de jogos.
*/
void alteraScore(int NL, glink* HashGames) {
    char buffer[MAXSIZE];
    int aux, newscore1, newscore2;
    pGame hit;
    scanf("%[^:\n]:%d:%d", buffer, &newscore1, &newscore2);
    aux = searchGameHash(buffer+1, HashGames, &hit);
    /* Caso jogo exista. */
    if (aux == 1) {
        atualizaVitorias(hit, 2, newscore1, newscore2);
        hit -> score1 = newscore1;
        hit -> score2 = newscore2;
    }
    else
        printf("%d Jogo inexistente.\n", NL);
}

/*================================================================================================*/

/* 
 * Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica.
 * Recebe NL e head da lista de equipas.
*/
void melhoresEquipas(int NL, tlink* pLThead) {
    tlink c;
    char* melhores[MAXMELHORES];
    int i, count, maxvitorias = 0;
    /* Ciclo que descobre o numero maximo de vitorias. */
    for (c = *pLThead; c != NULL; c = c -> next) {
        if (c -> pEquipa -> vitorias > maxvitorias)
            maxvitorias = c -> pEquipa -> vitorias;
    }
    /* Ciclo que encontra as melhores equipas e adiciona o seu nome ao array melhores. */
    for (c = *pLThead, i = 0, count = 0; c != NULL; c = c -> next) {
        if (c -> pEquipa -> vitorias == maxvitorias) {
            melhores[i] = c -> pEquipa -> name;
            count++;
            i++;
        }
    }
    /* qsort ordena o array melhores por ordem lexicografica. */
    qsort(melhores, count, sizeof(char *), cstring_cmp);
    if (count != 0) {
        printf("%d Melhores %d\n", NL, maxvitorias);
        for (i = 0; i < count; i++)
            printf("%d * %s\n", NL, melhores[i]);
    }
}

/*================================================================================================*/

/* 
 * Funcao executada apenas antes do programa terminar, liberta toda a memoria alocada no heap.
 * Recebe head e tail da lista de equipas e de jogos e pointers para as duas hash tables.
*/
void sair(tlink* pLThead, tlink* pLTtail, glink* pLGh, glink* pLGt, tlink* HashT, glink* HashG) {
    limpaFilaEquipa(pLThead, pLTtail);
    limpaFilaJogo(pLGh, pLGt);
    limpaHashTeams(HashT);
    limpaHashGames(HashG);
}
