#include <stdio.h>
#include <string.h>
#include "jogo.h"
#include "equipa.h"
#define MAXSTR 2024
#define hashM 631


void AddJogo(linkJogo *pheadj,linkJogo *ptailj, linkJogo tabJogos[hashM], linkEquipa *pheade,linkEquipa *ptaile, linkEquipa tabEquipas[hashM], int NL){
    /*Funcao adiciona um novo jogo ao sistema (variaveis de input necessarias devido as estruturas usadas)*/
    
    char strings[3][MAXSTR], c;
    int i = 0, e = 0, s1, s2;
    linkJogo j;
    linkEquipa e1, e2;
    
    /*Define os nomes necessarios (mais rapido que scanf("%[^:]:%d:%d",...)*/
    getchar();
    for(;i<3;i++){
        c = getchar();
        while (c != ':'){
            strings[i][e] = c;
            e++;
            c = getchar();
        }
        strings[i][e] = '\0';
        e = 0;
    }
    scanf("%d:%d", &s1, &s2);

    if ( ProcuraJHash(tabJogos,strings[0]) != NULL){ /*Verifica se o jogo ainda nao existe*/
        printf("%d Jogo existente.\n", NL);
        return;
    }

    if ((e1 = ProcuraEHash(tabEquipas,strings[1])) == NULL || 
        (e2 = ProcuraEHash(tabEquipas,strings[2])) == NULL){ /*Verifica se as equipas existem e guarda-as*/

        printf("%d Equipa inexistente.\n", NL);
        return;
    }

    /*Identifica vencedor e incrementa as suas vitorias*/
    if (s1 > s2){
        *(e1->equipa->vit)  = *(e1->equipa->vit) +1;
        ReposCima(pheade, ptaile, e1);
    }
    else if (s1 < s2){
        *(e2->equipa->vit)  = *(e2->equipa->vit) +1;
        ReposCima(pheade, ptaile, e2);
    }

    /*cria o novo e insere-o na estrutura*/
    j = NovoJogo(strings[0], strings[1], strings[2], s1, s2);

    InserirJogo(pheadj, ptailj, tabJogos, j);
    

}

void AddEquipa(linkEquipa *pheade,linkEquipa *ptaile, linkEquipa tabEquipas[hashM], int NL){
    /*Funcao adiciona uma nova equipa ao sistema (variaveis de input necessarias devido a estrutura usada)*/
    
    char string[MAXSTR], c;
    int i=0;
    linkEquipa e;


    /*Define os nomes necessarios (mais rapido que scanf("%[^:]:%d:%d",...)*/
    getchar();
    c = getchar();
    while (c != '\n'){
        string[i] = c;
        i++;
        c = getchar();
    }
    string[i] = '\0';

    /*Verifica se a equipa ainda nao existe*/
    if (ProcuraEHash(tabEquipas,string) != NULL){
        printf("%d Equipa existente.\n", NL);
        return;
    }

    /*Cria a nova equipa e insere-a na estrutura*/
    e = NovaEquipa(string);
    InserirEquipa(pheade, ptaile, tabEquipas, e);

}

void ListaJogos(linkJogo headj, int NL){
    /*Funcao percorre a lista (que esta por ordem de introducao) listando-os*/
    linkJogo aux;

    getchar();/*Caso a lista esteja vazia nao lista nada*/
    if (headj == NULL) return;

    aux = headj;
    while(aux != NULL){
        printf("%d %s %s %s %d %d\n", NL, aux->jogo->nome, aux->jogo->equipa1, aux->jogo->equipa2, *(aux->jogo->score1), *(aux->jogo->score2));
        aux = aux->nextList;
    }
}

void FindJogo(linkJogo tabJogos[hashM], int NL){
    /*Funcao acede a tabela de dispersao de jogos e identifica um jogo*/

    char string[MAXSTR], c;
    int i=0;
    linkJogo j;

    /*Define o nome a procurar (mais rapido que scanf("%[^:]:%d:%d",...)*/
    getchar();
    c = getchar();
    while (c != '\n'){
        string[i] = c;
        i++;
        c = getchar();
    }
    string[i] = '\0';

    /*Efetua a procura*/
    j = ProcuraJHash(tabJogos,string);

    if (j == NULL){ /*Caso nao exista nenhum jogo com o nome procurado*/
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    printf("%d %s %s %s %d %d\n", NL, string, j->jogo->equipa1, j->jogo->equipa2, *(j->jogo->score1), *(j->jogo->score2));
}

void FindEquipa(linkEquipa tabEquipas[hashM], int NL){
    /*Funcao acede a tabela de dispersao de equipas e identifica uma equipa*/
    
    char string[MAXSTR], c;
    int i=0;
    linkEquipa e;

    /*Define o nome a procurar (mais rapido que scanf("%[^:]:%d:%d",...)*/
    getchar();
    c = getchar();
    while (c != '\n'){
        string[i] = c;
        i++;
        c = getchar();
    }
    string[i] = '\0';

    /*Efetua a procura*/
    e = ProcuraEHash(tabEquipas,string);

    if (e == NULL){ /*Caso nao exista nenhuma equipa com o nome procurado*/
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    printf("%d %s %d\n", NL, string, *(e->equipa->vit));

}

void RemoveJogo(linkJogo *pheadj, linkJogo *ptailj, linkJogo tabJogos[hashM], linkEquipa *pheade, linkEquipa *ptaile, linkEquipa tabEquipas[hashM], int NL){
    /*Funcao recebe o nome de um jogo e, caso este exista, remove-o*/
    char string[MAXSTR], c;
    int i=0;
    linkJogo j;
    linkEquipa e;

    /*Define o nome do jogo (mais rapido que scanf("%[^:]:%d:%d",...)*/
    getchar();
    c = getchar();
    while (c != '\n'){
        string[i] = c;
        i++;
        c = getchar();
    }
    string[i] = '\0';

    /*Encontra o jogo (atravez da tabela de dispersao)*/
    j = ProcuraJHash(tabJogos,string);

    if (j == NULL){/*Caso nao exista nenhum jogo com o nome procurado*/
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    
    /*Caso o jogo removido nao seja um empate ajusta as vitorias das equipas*/
    if(*(j->jogo->score1) > *(j->jogo->score2)){
        e = ProcuraEHash(tabEquipas, j->jogo->equipa1);/*encontra equipa*/
        *(e->equipa->vit) = *(e->equipa->vit) - 1; /*altera o numero de vitorias*/
        ReposBaixo(pheade, ptaile, e);  /*Reposiciona a equipa na lista de equipas (ordenada por vitorias)*/
    }
    else if(*(j->jogo->score2) > *(j->jogo->score1)){
        e = ProcuraEHash(tabEquipas, j->jogo->equipa2);
        *(e->equipa->vit) = *(e->equipa->vit) - 1;
        ReposBaixo(pheade, ptaile, e);
    }

    /*Removo o jogo da estrutura permanentemente*/
    RemoverJogo(pheadj, ptailj, tabJogos,  j);
}

void AltScore(linkJogo tabJogos[hashM], linkEquipa *pheade,linkEquipa *ptaile, linkEquipa tabEquipas[hashM], int NL){
    /*Funcao altera o resultado de um jogo*/
    char string[MAXSTR], c;
    int i=0, s1, s2, ps1, ps2;
    linkJogo j;
    int *v1, *v2;
    linkEquipa e1, e2;

    /*Define o nome do jogo (mais rapido que scanf("%[^:]:%d:%d",...)*/
    getchar();
    c = getchar();
    while (c != ':'){
        string[i] = c;
        i++;
        c = getchar();
    }
    string[i] = '\0';

    scanf("%d:%d", &s1, &s2);

    /*Encontra o jogo a alterar*/
    j = ProcuraJHash(tabJogos,string);

    if (j == NULL){ /*Caso nao exista nenhum jogo com o nome procurado*/
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    /*Define os valores necessarios para as alteracoes*/
    e1 = ProcuraEHash(tabEquipas, j->jogo->equipa1);/*Equipas envolventes*/
    e2 = ProcuraEHash(tabEquipas, j->jogo->equipa2);
    v1 = e1->equipa->vit;   /*Guarda em v1 e v2 as vitorias das equipas*/
    v2 = e2->equipa->vit;
    ps1 = *(j->jogo->score1);/*Guarda em ps1 e ps2 o antigo resultado do jogo*/
    ps2 = *(j->jogo->score2);

    if(ps1>ps2){ /*Caso previamente a equipa 1 tivesse ganho*/
        if (s1<s2){ /*Caso depois da alteracao passe a ganhar a equipa2*/
            *v1 = *v1 - 1;
            ReposBaixo(pheade, ptaile, e1);
            *v2 = *v2 + 1;
            ReposCima(pheade, ptaile, e2);/*Altera valores e reposiciona na lista*/
        }
        else if (s1==s2){/*Caso depois da alteracao passe a empate*/
            *v1 = *v1 - 1;
            ReposBaixo(pheade, ptaile, e1);
        }
    }
    else if (ps1<ps2){/*Caso previamente a equipa 1 tivesse ganho*/
        if (s1>s2){ /*Caso depois da alteracao passe a ganhar a equipa1*/
            *v1 = *v1 + 1;
            ReposCima(pheade, ptaile, e1);
            *v2 = *v2 - 1;
            ReposBaixo(pheade, ptaile, e2);/*Altera valores e reposiciona na lista*/
        }
        else if (s1==s2){/*Caso depois da alteracao passe a empate*/
            *v2 = *v2 - 1;
            ReposBaixo(pheade, ptaile, e2);
        }
    }
    else{/*Caso previamente fosse empate*/
        if (s1>s2){/*Caso depois da alteracao passe a ganhar a equipa1*/
            *v1 = *v1 + 1;
            ReposCima(pheade, ptaile, e1);
        }
        else if (s1<s2){/*Caso depois da alteracao passe a ganhar a equipa2*/
            *v2 = *v2 + 1;
            ReposCima(pheade, ptaile, e2);
        }
    }

    *(j->jogo->score1) = s1;
    *(j->jogo->score2) = s2;


}

void ListMelhores(linkEquipa taile, int NL){
    /*Funcao lista as equipas com maior numero de vitorias alfabeticamente*/
    linkEquipa aux;

    if(taile == NULL) return; /*caso nao existam equipas*/

    printf("%d Melhores %d\n", NL, *(taile->equipa->vit));

    aux = taile;
    printf("%d * %s\n", NL, aux->equipa->nome);
    /*Percorre a lista da frente para tras listando ate uma equipa com menos vitorias*/
    while (aux->prevList != NULL && *(aux->equipa->vit) == *(aux->prevList->equipa->vit) ){
        aux = aux->prevList;
        printf("%d * %s\n", NL, aux->equipa->nome);
    }
}

int main(){
    int c=0, i=0, NL =1;

    /*Variaveis da estrutura de jogos*/
    linkJogo headj = NULL;
    linkJogo tailj = NULL;
    linkJogo tabJogos[hashM];

    /*Variaveis da estrutura de equipas*/
    linkEquipa heade = NULL;
    linkEquipa taile = NULL;
    linkEquipa tabEquipas[hashM];

    for (;i<hashM;i++){tabJogos[i] = NULL;}/*inicializacao de jogos*/

    for (i=0;i<hashM;i++){tabEquipas[i] = NULL;}/*inicializacao de equipas*/

    /*Recebe o caracter do comando e executa a funcao correspondente (Mais compacto que switch)*/
    c = getchar();
    while (c != 'x'){
        if (c == 'a')
            AddJogo(&headj, &tailj, tabJogos, &heade, &taile, tabEquipas, NL);
        else if (c == 'A')
            AddEquipa(&heade, &taile, tabEquipas, NL);
        else if (c == 'l')
            ListaJogos(headj, NL);
        else if (c == 'p')
            FindJogo(tabJogos, NL);
        else if (c == 'P')
            FindEquipa(tabEquipas, NL);
        else if (c == 'r')
            RemoveJogo(&headj, &tailj, tabJogos, &heade, &taile, tabEquipas, NL);
        else if (c == 's')
            AltScore(tabJogos, &heade, &taile, tabEquipas, NL);
        else if (c == 'g')
            ListMelhores(taile, NL);

        c = getchar();
        if(c!='\n')
            NL++;
    }
    
    /*Liberta a alocacao dinamica de memoria restante*/
    if (headj != NULL)
        freeLinkJogo(headj);
    
    for (i=0;i<hashM;i++)
        if (tabEquipas[i] !=NULL)
            freeLinkEquipa(tabEquipas[i]);
    
        
    return 0;
}
