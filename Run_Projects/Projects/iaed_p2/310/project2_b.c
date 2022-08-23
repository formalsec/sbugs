#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Numero maximo de carcateres do nome/equipas */ 
#define Max_Buffer 1023
/* Tamanho das hash tables */
#define HTable_Size 2089

/* estrutura do jogo */
typedef struct jogo
{
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1;
    int score2;
}*pJogo;  

typedef struct equipa
{
    char *nome;
    int vitorias;
}*pEquipa;

typedef struct jogos
{
    pJogo jogo;
    struct jogos *next;
}*pJogos;

typedef struct equipas
{
    pEquipa equipa;
    struct equipas *next;
}*pEquipas;   

pJogos hJogos = NULL;
pJogos *TableJogos;

pEquipas *TableEquipas;
pEquipas gEquipas = NULL;

/* contador do numero do comando */
int NL = 1;

/* prototipos das funcoes */
int getCommand();
void funcao_a();
void funcao_A();
void funcao_l();
void funcao_p();
void funcao_P();
void funcao_r();
void funcao_s();
void funcao_g();
void funcao_x();
pEquipas NewEquipa();
pEquipas AdicionarEquipa();
pEquipas searchEquipa();
void FreeEquipas();
void FreeEquipa();
pJogos NewJogo();
pJogos AdicionarJogo();
pJogos searchJogo();
void FreeJogos();
void FreeJogo();
pJogos DeleteJogo();
void InitHashTableEquipas();
void FreeHashTableEquipas();
void InitHashTableJogos();
void FreeHashTableJogos();
pEquipas AdicionarEquipag();

int main()
{
    InitHashTableEquipas();
    InitHashTableJogos();
    getCommand();
    FreeJogos(hJogos);
    FreeHashTableJogos(TableJogos);
    FreeHashTableEquipas(TableEquipas);
    return 0;
}

/* executar a accao correspondente ao comando */
int getCommand()
{
    while (1)
    {
        int command = getchar();
        switch (command)
        {
        case 'a':
            getchar();
            funcao_a();
            NL ++;
            break;
        case 'A':
            getchar();
            funcao_A();
            NL ++;
            break;
        case 'l':
            funcao_l();
            NL ++;
            break;
        case 'p':
            getchar();
            funcao_p();
            NL ++;
            break;
        case 'P':
            getchar();
            funcao_P();
            NL ++;
            break;
        case 'r':
            getchar();
            funcao_r();
            NL ++;
            break;
        case 's':
            getchar();
            funcao_s();
            NL ++;
            break;
        case 'g':
            funcao_g();
            NL ++;
            break;
        case 'x':
            return 0;
        default:
            break;
        }
    }
    return 0;
}
/* Inicializacao da hashtable para os jogos */
void InitHashTableJogos()
{
    int i;
    TableJogos = malloc(sizeof(struct jogos)*HTable_Size);
    for(i = 0; i < HTable_Size; i++){
        TableJogos[i] = NULL;
    }
}

/* Free da hashtable dos jogos */
void FreeHashTableJogos(pEquipas *TableJogos)
{
    int i;
    for(i = 0; i < HTable_Size; i++){
        FreeJogos(TableJogos[i]);
    }
    free(TableJogos);
}

/* Inicializacao da hastable das equipas */
void InitHashTableEquipas()
{
    int i;
    TableEquipas = malloc(sizeof(struct equipas)*HTable_Size);
    for(i = 0; i < HTable_Size; i++){
        TableEquipas[i] = NULL;
    }
}

/* Algoritmo de criacao de index da hashtable */
int Hash(char *nome)
{
    int h, a = 127;
    for(h = 0; *nome != '\0'; nome++){
        h = (a*h + *nome) % HTable_Size;
    }
    return h;
}

/* Free da hashtable das equipas */
void FreeHashTableEquipas(pEquipas *TableEquipas)
{
    int i;
    for(i = 0; i < HTable_Size; i++){
        FreeEquipas(TableEquipas[i]);
    }
    free(TableEquipas);
}

/* Criacao do node de uma equipa(alocacao de memoria) */
pEquipas NewEquipa(char *buffer)
{
    pEquipas x = malloc(sizeof(struct equipas));
    x->equipa = malloc(sizeof(struct equipa));
    x->equipa->nome = malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(x->equipa->nome, buffer);
    x->equipa->vitorias = 0;
    x->next = NULL;
    return x;
}

/* Adicionar uma equipa a uma lista ligada de equipas */
pEquipas AdicionarEquipa(pEquipas hEquipas, char *nome)
{
    pEquipas NovaEquipa = NewEquipa(nome);
    pEquipas x;
    /* No caso da lista estar vazia */
    if (hEquipas == NULL){
        return NovaEquipa;
    }
    /* Se a lista ja tiver equipas introduz no fim */
    else
    {
        for(x = hEquipas; x->next != NULL; x = x->next);
        x->next = NovaEquipa;
        return hEquipas;
    } 
}

/* Procura de uma equipa pelo nome numa lista de equipas */
pEquipas searchEquipa(pEquipas hEquipas, char *nome)
{
    pEquipas x;
    for(x = hEquipas; x != NULL; x = x->next){
        if(strcmp(x->equipa->nome, nome)==0)
            return x;
    }
    return NULL;
}

/* Free de uma lista de equipas */
void FreeEquipas(pEquipas hEquipas)
{
    pEquipas x = hEquipas;
    pEquipas y;
    while(x != NULL){
        y = x->next;
        FreeEquipa(x);
        x = y;
    }
    hEquipas = NULL;
}

/* Free de uma equipa */
void FreeEquipa(pEquipas hEquipas)
{
    free(hEquipas->equipa->nome);
    free(hEquipas->equipa);
    free(hEquipas);    
}

/* Criacao do node de um jogo(alocacao de memoria) */
pJogos NewJogo(char *nome, char *equipa1, char *equipa2, int score1, int score2)
{
    pJogos x = malloc(sizeof(struct jogos));
    x->jogo = malloc(sizeof(struct jogo));
    x->jogo->nome = malloc(sizeof(char)*(strlen(nome)+1));
    x->jogo->equipa1 = malloc(sizeof(char)*(strlen(equipa1)+1));
    x->jogo->equipa2 = malloc(sizeof(char)*(strlen(equipa2)+1));
    strcpy(x->jogo->nome, nome);
    strcpy(x->jogo->equipa1, equipa1);
    strcpy(x->jogo->equipa2, equipa2);
    x->jogo->score1 = score1;
    x->jogo->score2 = score2;
    x->next = NULL;
    return x;
}

/* Adicionar um jogo a uma lista ligada de jogos */
pJogos AdicionarJogo(pJogos hJogos, char *nome, char *equipa1, char *equipa2, int s1, int s2)
{
    pJogos NovoJogo = NewJogo(nome, equipa1, equipa2, s1, s2);
    pJogos x;
    /* No caso da lista estar vazia */
    if(hJogos == NULL){
        return NovoJogo;
    }
    /* Se a lista ja tiver equipas introduz no fim */
    else{
        for(x = hJogos; x->next != NULL; x = x->next);
        x->next = NovoJogo;
        return hJogos;
    }
}

/* Procura de um jogo pelo nome numa lista de jogos */
pJogos searchJogo(pJogos hJogos, char *nome)
{
    pJogos x;
    for(x = hJogos; x != NULL; x = x->next)
        if(strcmp(x->jogo->nome, nome) == 0)
            return x;
    return NULL;
}

/* Free de uma lista de jogos */
void FreeJogos(pJogos hJogos)
{
    pJogos x = hJogos;
    pJogos y;
    while(x != NULL){
        y = x->next;
        FreeJogo(x);
        x = y;
    }
    hJogos = NULL;
}

/* Free de um jogo */
void FreeJogo(pJogos hJogos)
{
    free(hJogos->jogo->nome);
    free(hJogos->jogo->equipa1);
    free(hJogos->jogo->equipa2);
    free(hJogos->jogo);
    free(hJogos);
}

/* Procura um jogo numa lista e apaga(da free da memoria) */
pJogos DeleteJogo(pJogos hJogos, char *nome)
{
    pJogos x, prev;
    for(x = hJogos, prev = NULL; x != NULL; prev = x, x = x->next){
        if(strcmp(x->jogo->nome, nome) == 0){
            if(x == hJogos)
                hJogos = x->next;
            else
                prev->next = x->next;
            FreeJogo(x);
            break;
        }
    }
    return hJogos;
}

/* Adiciona um jogo ao sistema, aloca memoria, introduz o jogo numa lista ligada e na hashtable, atualiza o numero de vitorias das equipas*/
void funcao_a()
{
    char bufferNome[Max_Buffer];
    char bufferEquipa1[Max_Buffer];
    char bufferEquipa2[Max_Buffer];
    int s1,s2,h0,h1,h2;
    pEquipas x;
    scanf("%[^:]:%[^:]:%[^:]:%d:%d", bufferNome, bufferEquipa1, bufferEquipa2, &s1, &s2);
    h0 = Hash(bufferNome);
    h1 = Hash(bufferEquipa1);
    h2 = Hash(bufferEquipa2);
    if(searchJogo(TableJogos[h0], bufferNome) != NULL){
        printf("%d Jogo existente.\n", NL);
        return;
    }
    else if(searchEquipa(TableEquipas[h1], bufferEquipa1) == NULL || searchEquipa(TableEquipas[h2], bufferEquipa2) == NULL){
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    /* Adicionar  na lista de jogos e na hashtable de jogos*/
    hJogos = AdicionarJogo(hJogos, bufferNome, bufferEquipa1, bufferEquipa2, s1, s2);
    TableJogos[h0] = AdicionarJogo(TableJogos[h0], bufferNome, bufferEquipa1, bufferEquipa2, s1, s2);
    /* Atualiza as vitorias da equipa vencedora */
    if(s1 > s2){
        x = searchEquipa(TableEquipas[h1], bufferEquipa1);
        x->equipa->vitorias++;
    }
    else if(s2 > s1){
        x = searchEquipa(TableEquipas[h2], bufferEquipa2);
        x->equipa->vitorias++;
    }

}

/* Print de todos os jogos pela ordem de entrada */
void funcao_l()
{
    pJogos x;
    for(x = hJogos; x != NULL; x = x->next)
        printf("%d %s %s %s %d %d\n", NL, x->jogo->nome, x->jogo->equipa1, x->jogo->equipa2, x->jogo->score1, x->jogo->score2);
}

/* Print de um jogo(nome, equipas e resultado)*/
void funcao_p()
{
    char bufferNome[Max_Buffer];
    pJogos x;
    int h;
    scanf("%[^\n]%*c", bufferNome);
    h = Hash(bufferNome);
    if(searchJogo(TableJogos[h], bufferNome) == NULL){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    /* associar a variavel x o node do jogo */
    x = searchJogo(TableJogos[h], bufferNome);
    printf("%d %s %s %s %d %d\n", NL, x->jogo->nome, x->jogo->equipa1, x->jogo->equipa2, x->jogo->score1, x->jogo->score2);
}
/*  Apaga um jogo do sistema, apaga o jogo da lista de jogos, da hashtable dos jogos e recalcula as vitorias das equipas */
void funcao_r()
{
    char bufferNome[Max_Buffer];
    pJogos x;
    pEquipas y;
    int h;
    scanf("%[^\n]%*c", bufferNome);
    h = Hash(bufferNome);
    if(searchJogo(TableJogos[h], bufferNome) == NULL){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    /* Atualizar o numero de vitorias das equipas participantes no jogo */
    x = searchJogo(TableJogos[h], bufferNome);
    if(x->jogo->score1 > x->jogo->score2){
        y = searchEquipa(TableEquipas[Hash(x->jogo->equipa1)], x->jogo->equipa1);
        y->equipa->vitorias--;
    }
    else if(x->jogo->score2 > x->jogo->score1){
        y = searchEquipa(TableEquipas[Hash(x->jogo->equipa2)], x->jogo->equipa2);
        y->equipa->vitorias--;
    }
    /* Apagar o jogo da lista de jogos e da hastable de jogos(faz free da memoria alocada)*/
    hJogos = DeleteJogo(hJogos, bufferNome);
    TableJogos[h] = DeleteJogo(TableJogos[h], bufferNome);
}

/* Altera o score de um jogo, atualiza o numero de vitorias das equipas que participam no jogo*/
void funcao_s()
{
    char bufferNome[Max_Buffer];
    int s1, s2, h0, h1, h2;
    pJogos x;
    pJogos x2;
    pEquipas y;
    scanf("%[^:]:%d:%d", bufferNome, &s1, &s2);
    h0 = Hash(bufferNome);
    if(searchJogo(TableJogos[h0], bufferNome) == NULL){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    x = searchJogo(TableJogos[h0], bufferNome);
    x2 = searchJogo(hJogos, bufferNome);
    h1 = Hash(x->jogo->equipa1);
    h2 = Hash(x->jogo->equipa2);
    /* Alterar o numero de vitorias das equipas, diminuir a vitoria que tinha e introduzir a nova vitoria no citio certo */
    if(x->jogo->score1 > x->jogo->score2){
        y = searchEquipa(TableEquipas[h1], x->jogo->equipa1);
        y->equipa->vitorias--;
    }
    else if(x->jogo->score2 > x->jogo->score1){
        y = searchEquipa(TableEquipas[h2], x->jogo->equipa2);
        y->equipa->vitorias--;
    }
    if(s1 > s2){
        y = searchEquipa(TableEquipas[h1], x->jogo->equipa1);
        y->equipa->vitorias++;
    }
    else if(s2 > s1){
        y = searchEquipa(TableEquipas[h2], x->jogo->equipa2);
        y->equipa->vitorias++;
    }
    /* Atualiza o score do jogo */
    x->jogo->score1 = s1;
    x->jogo->score2 = s2;
    x2->jogo->score1 = s1;
    x2->jogo->score2 = s2;
}

/* Adiciona uma equipa ao sistema, adiciona a uma hashtable de equipas */
void funcao_A()
{
    char bufferNome[Max_Buffer];
    int x;
    scanf("%[^\n]%*c", bufferNome);
    if(searchEquipa(TableEquipas[Hash(bufferNome)], bufferNome) != NULL ){
        printf("%d Equipa existente.\n", NL);
        return;
    }
    x = Hash(bufferNome);
    /* Adicionar a hashtable */
    TableEquipas[x] = AdicionarEquipa(TableEquipas[x], bufferNome);
}

/* Print de um equipa existente no sistema */
void funcao_P()
{
    char bufferNome[Max_Buffer];
    pEquipas x;
    int y;
    scanf("%[^\n]%*c", bufferNome);
    y = Hash(bufferNome);
    if(searchEquipa(TableEquipas[y], bufferNome) == NULL ){
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    x = searchEquipa(TableEquipas[y], bufferNome);
    printf("%d %s %d\n", NL, bufferNome, x->equipa->vitorias);
}

/* Lista as equipas com o maior numero de vitorias por ordem alfabetica */
void funcao_g()
{
    pEquipas x;
    int i, max = 0;
    /* Procura todas as equipas no sistema */
    for(i = 0; i < HTable_Size; i++){
        if(TableEquipas[i] != NULL){
            for(x = TableEquipas[i]; x!= NULL; x = x->next){
                /* Se o numero de vitorias for maior ou igual ao numero de vitorias encontrado ate ao momento, adiciona a equipa a lista de equipas com o maximo de vitorias */
                if(x->equipa->vitorias >= max){
                    /* Se o numero de vitorias for superior ao maximo, apaga a lista anteriormente criada, e cria uma nova */
                    if(x->equipa->vitorias > max){
                        FreeEquipas(gEquipas);
                        gEquipas = NULL;    
                        max = x->equipa->vitorias;
                    }
                    gEquipas = AdicionarEquipag(gEquipas, x->equipa->nome);
                }
            }
        }
    }
    /* Print das equipas com mais vitorias */
    if(gEquipas != NULL){
        printf("%d Melhores %d\n", NL, max);
        for(x = gEquipas; x != NULL; x = x->next)
            printf("%d * %s\n", NL, x->equipa->nome);
        /* Libertar memoria alocada para esta lista de equipas */
        FreeEquipas(gEquipas);
        gEquipas = NULL;
    }
}
/* Adiciona uma equipa a uma lista de equipas de modo a que esta fique ordenada por ordem alfabetica */
pEquipas AdicionarEquipag(pEquipas hEquipas, char *nome)
{
    pEquipas NovaEquipa = NewEquipa(nome);
    pEquipas x;
    int menor;
    int small = 0;  
    /* Se a entrada da lista tiver vazia, preenche */
    if (hEquipas == NULL){
        return NovaEquipa;
    }
    /* Se o nome da nova equipa for antes do nome da equipa na entrada, a nova entrada e a nova equipa */
    if(strlen(NovaEquipa->equipa->nome) > strlen(hEquipas->equipa->nome)){
        menor = strlen(hEquipas->equipa->nome);
        small = 0;
        }
    else{
        menor = strlen(NovaEquipa->equipa->nome);
        small = 1;
    }
    if(strncmp(NovaEquipa->equipa->nome, hEquipas->equipa->nome, menor) < 0 || (strncmp(NovaEquipa->equipa->nome, hEquipas->equipa->nome, menor) == 0 && small == 1)){
        NovaEquipa->next = hEquipas;
        hEquipas = NovaEquipa;
        return hEquipas;
    }
    /* Percorre a lista de equipas, se o nome da nova equipa por ordem alfabetica for antes de alguma equipa, introduz a nova equipa antes dessa equipa de comparacao*/
    for(x = hEquipas; x->next != NULL; x = x->next){
        if(strlen(NovaEquipa->equipa->nome) > strlen(x->next->equipa->nome)){
            menor = strlen(x->next->equipa->nome);
            small = 0;
        }
        else{
            menor = strlen(NovaEquipa->equipa->nome);
            small = 1;
        }
        if(strncmp(NovaEquipa->equipa->nome, x->next->equipa->nome, menor) < 0 || (strncmp(NovaEquipa->equipa->nome, x->next->equipa->nome, menor) == 0 && small == 1)){
            NovaEquipa->next = x->next;
            x->next = NovaEquipa;
            return hEquipas;
        }
    }
    /* Em ultimo caso, o nome da nova equipa por ordem alfabetica e depois de todos os outros, assim sendo, introduz no final */ 
    x->next = NovaEquipa;
    return hEquipas;
} 
