#include "jogo.h"
#include "equipa.h"


/*Recebe o nome, as equipas e o score e cria o jogo correspondente ao input.
Retorna um ponteiro para o o node de jogo criado*/
no_jogo_tabela *cria_jogo(char nome[],char equipa1[],char equipa2[],int score1,int score2){
    no_jogo_tabela *novo = (no_jogo_tabela*) malloc(sizeof(no_jogo_tabela));
    novo->proximo = NULL;
    novo->pos_fila = NULL;
    novo->anterior = NULL;
    novo->jogo1.nome = malloc((strlen(nome)+1)*sizeof(char));
    strcpy(novo->jogo1.nome,nome);
    novo->jogo1.equipa1 = malloc((strlen(equipa1)+1)*sizeof(char));
    strcpy(novo->jogo1.equipa1,equipa1);
    novo->jogo1.equipa2 = malloc((strlen(equipa2)+1)*sizeof(char));
    strcpy(novo->jogo1.equipa2,equipa2);
    novo->jogo1.score1 = score1;
    novo->jogo1.score2 = score2;
    return novo;
}

/*Recebe o nome, as equipas e o score. Adiciona o jogo correspondente ao input
a tabela global que contem os jogos todos e coloca o pointeiro da fila a apontar para o jogo.
Nao tem retorno.*/
void adiciona_jogo(no_equipa *tabela_equipas[],lista_jogos **fila_jogos,no_jogo_tabela *tabela_jogos[],
char nome[],char equipa1[],char equipa2[],int score1,int score2){
    no_jogo_tabela *novo = cria_jogo(nome,equipa1,equipa2,score1,score2);
    no_jogos *novo_no = malloc(sizeof(no_jogos));
    int pos = hash(nome);
    equipa *alvo;
    novo_no->proximo = NULL;
    novo_no->anterior = NULL;
    novo_no->jogo_n = novo;
    novo->pos_fila = novo_no;
    /*adiciona o jogo a lista*/
    if(!(*fila_jogos)->inicio) (*fila_jogos)->inicio = novo_no;
    if((*fila_jogos)->fim) {
        (*fila_jogos)->fim->proximo = novo_no;
        novo_no->anterior = (*fila_jogos)->fim;
    }
    (*fila_jogos)->fim = novo_no;
    /*adiciona o jogo a tabela de jogos*/
     /*cabeca vazia?*/
    if(!tabela_jogos[pos]) tabela_jogos[pos] = novo;
    else
    {   /*nao e por isso adiciona na cabeca*/
         novo->proximo = tabela_jogos[pos];
         tabela_jogos[pos]->anterior = novo;
         tabela_jogos[pos] = novo;
    }
    /*adiciona a vitoria a quem ganhou*/
    if (ganhou(score1,score2)){
       alvo = procura_equipa_lista(tabela_equipas,equipa1);
       alvo->vitorias++;
    }
    else if(ganhou(score2,score1))
    {  
       alvo = procura_equipa_lista(tabela_equipas,equipa2);
       alvo->vitorias++;
    }
}

/*Recebe o nome do jogo e procura-o na tabela de jogos, retornando um ponteiro
para o no deste caso exista. Retorna um ponteiro nulo caso contrario*/
no_jogo_tabela *procura_jogo_lista(no_jogo_tabela *tabela_jogos[],char nome[]){
    no_jogo_tabela *i;
    int pos = hash(nome);
    for(i = tabela_jogos[pos];i ;i=i->proximo){
        if(!strcmp(nome,i->jogo1.nome)){ /*encontrado logo retorna-o*/
            return i;
        }
    }
    /*nao existe, logo retorna o ponteiro nulo*/
    return NULL;
}

/*Lista todos os jogos guardados. Nao retorna nada*/
void lista_todos_jogos(lista_jogos *fila_jogos,int linha){
    no_jogos *i;
    for (i = fila_jogos->inicio;i ;i=i->proximo){
        printf("%d %s %s %s %d %d\n",linha,
        i->jogo_n->jogo1.nome,i->jogo_n->jogo1.equipa1,i->jogo_n->jogo1.equipa2,
        i->jogo_n->jogo1.score1,i->jogo_n->jogo1.score2);
    }
}

/*Recebe um nome de um jogo e apaga-o da lista de jogos, libertando a memoria associada,
e retirado a vitoria a equipa necessaria.Nao retorna nada*/
void apaga_jogo(no_equipa *tabela_equipas[],lista_jogos **fila_jogos,no_jogo_tabela *tabela_jogos[],char nome[]){
    no_jogo_tabela *i;
    /*acede a posicao do jogo*/
    i = procura_jogo_lista(tabela_jogos,nome);
    /*remove na tabela*/
    if (i->anterior){
        /*nao e o primeiro da tabela, logo altera o anterior*/
        i->anterior->proximo = i->proximo;

    }
    else
    {   /*sendo o primeiro da tabela atualiza a cabeca*/
        int pos = hash(nome);
        tabela_jogos[pos] = i->proximo;
    }
    if(i->proximo){ /*se tiver proximo atualiza-o*/
        i->proximo->anterior = i->anterior;
    }
    /*remove na lista*/
    /*fim e inicio apontam para o mesmo?*/
    if(i->pos_fila == (*fila_jogos)->fim && i->pos_fila == (*fila_jogos)->inicio){
        (*fila_jogos)->inicio = i->pos_fila->proximo;
        (*fila_jogos)->fim = i->pos_fila->proximo;
    }
    else if(!i->pos_fila->anterior){ /*a remocao e no primeiro elemento?*/
        (*fila_jogos)->inicio = i->pos_fila->proximo;
        (*fila_jogos)->inicio->anterior = NULL;
    }
        
    else if(i->pos_fila == (*fila_jogos)->fim){ /*a remocao e no ultimo elemento?*/
        (*fila_jogos)->fim = i->pos_fila->anterior;
        (*fila_jogos)->fim->proximo = NULL;
    }
    else
    {   /*logo e no meio*/
       i->pos_fila->anterior->proximo = i->pos_fila->proximo;
       i->pos_fila->proximo->anterior = i->pos_fila->anterior;
    }
    
    /*retira a vitoria deste jogo, ja que e apagado*/
    if(ganhou(i->jogo1.score1,i->jogo1.score2))
        altera_vitoria_equipa(tabela_equipas,i->jogo1.equipa1,RETIRA);
    else if(ganhou(i->jogo1.score2,i->jogo1.score1))
    {
        altera_vitoria_equipa(tabela_equipas,i->jogo1.equipa2,RETIRA);
    }
    /*liberta_memoria*/
    free(i->pos_fila);
    free(i->jogo1.nome);
    free(i->jogo1.equipa1);
    free(i->jogo1.equipa2);
    free(i);
}

/*Recebe o nome do jogo, e os novos score e atuliza o jogo e as vitorias
de cada equipa. Nao retorna nada*/
void altera_score(no_equipa *tabela_equipas[],no_jogo_tabela *tabela_jogos[],char nome[],int score_novo1,int score_novo2){
    jogo *jogo_alvo;
    no_jogo_tabela *aux = procura_jogo_lista(tabela_jogos,nome);
    jogo_alvo = &(aux->jogo1);
    /*acerta o numero de vitorias com o novo score*/
    if(empate(score_novo1,score_novo2)){
        /*sendo agora empate, a que ganhava perde a vitoria*/
        if(ganhou(jogo_alvo->score1,jogo_alvo->score2))
            altera_vitoria_equipa(tabela_equipas,jogo_alvo->equipa1,RETIRA);
        else if(ganhou(jogo_alvo->score2,jogo_alvo->score1))
        {
            altera_vitoria_equipa(tabela_equipas,jogo_alvo->equipa2,RETIRA);
        } 
    }
    /*se era empate adiciona apenas a vitoria ao vencedor*/
    else if(empate(jogo_alvo->score1,jogo_alvo->score2)){
        if(ganhou(score_novo1,score_novo2))
            altera_vitoria_equipa(tabela_equipas,jogo_alvo->equipa1,ADICIONA);
        else
        {
            altera_vitoria_equipa(tabela_equipas,jogo_alvo->equipa2,ADICIONA);
        } 
    }
    /*se agora a outra equipa ganha, acerta-se as vitorias*/
    else if(ganhou(score_novo1,score_novo2) && !ganhou(jogo_alvo->score1,jogo_alvo->score2)){
         altera_vitoria_equipa(tabela_equipas,jogo_alvo->equipa2,RETIRA);
         altera_vitoria_equipa(tabela_equipas,jogo_alvo->equipa1,ADICIONA);
    }
    else if(ganhou(score_novo2,score_novo1) && !ganhou(jogo_alvo->score2,jogo_alvo->score1)){
        altera_vitoria_equipa(tabela_equipas,jogo_alvo->equipa2,ADICIONA);
        altera_vitoria_equipa(tabela_equipas,jogo_alvo->equipa1,RETIRA);
    }
    /*atualiza os scores*/
    jogo_alvo->score1 = score_novo1;
    jogo_alvo->score2 = score_novo2;
}

