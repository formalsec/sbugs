#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*MOD == 26, modulo das hashtables(numero de letras no alfabeto)*/
#define MOD 26

/* ADT equipa: tem o nome da equipa(char) e o nr de vitorias dessa equipa*/
typedef struct equipa {

    char *equipa;
    int vitorias;
} team;

/* ADT jogo: tem um nome(char), nomes de duas equipas(char) e dois scores(int)*/
typedef struct jogo {

    char *nome;
    team *equipa1, *equipa2;
    int score1,score2;
} game;

/* ADT node_jogo: tem um jogo(jogo) e um ponteiro para o proximo jogo. Usado para criar uma lista de jogos */
typedef struct node_jogo {

    game *jogo;
    struct node_jogo *next;

} node_jogo;

/* ADT node_equipa: tem uma equipa(char) e um ponteiro para a proxima equipa. Usado para criar uma lista de equipas */
typedef struct node_equipa {

    team *equipa;
    struct node_equipa *next;

} node_equipa;

/* lista onde vai ser guardados os jogos por ordem de criacao */
node_jogo *jogos_l = NULL;

/* lista onde vao ser guardadas as equipas por ordem de criacao */
node_equipa *equipas_l = NULL;

/* hashtable de modulo 26 onde vao ser guardadas os jogos tendo em conta a primeira letra do nome do jogo*/
node_jogo *jogos_h[MOD];

/* hashtable de modulo 26 onde vao ser guardadas as equipas tendo em conta a primeira letras do nome da equipa*/
node_equipa *equipas_h[MOD];

/* numero da linha de input*/
int NL = 1;

void novo_jogo();
void nova_equipa();
void lista_jogos();
void procura_jogo();
void procura_equipa();
void apaga_jogo();
void altera_score();
void equipa_mais_vitorias();

/*Le o comando a executar,efetua a funcao e no final, da free a memoria alocada*/
int main(){

    int i;
    char op;
    node_equipa *e_l,*aux_e_l;
    node_jogo *j_l, *aux_j_l;

    for(i = 0; i < MOD; i++){
        equipas_h[i] = NULL;
        jogos_h[i] = NULL;
    }

    op = getchar();


    while(op != 'x'){

        if (op == 'a'){
            novo_jogo();
            NL = NL + 1;
        }

        if (op == 'A'){
            nova_equipa();
            NL = NL + 1;
        }

        if (op == 'l'){
            lista_jogos();
            NL = NL + 1;
        }

        if (op == 'p'){
            procura_jogo();
            NL = NL + 1;
        }

        if (op == 'P'){
            procura_equipa();
            NL = NL + 1;
        }

        if (op == 'r'){
            apaga_jogo();
            NL = NL + 1;
        }

        if (op == 's'){
            altera_score();
            NL = NL + 1;
        }

        if (op == 'g'){
            equipa_mais_vitorias();
            NL = NL + 1;
        }
        
        op = getchar();
    }

    /*faz free aos nomes das equipas, ponteiros para equipas e nodos de equipas da lista, criados anteriormente*/
    e_l = equipas_l;
    while(e_l!= NULL){
        aux_e_l = e_l->next;
        free(e_l->equipa->equipa);
        free(e_l->equipa);
        free(e_l);
        e_l = aux_e_l;
    }

    /*faz free aos nomes dos jogos, aos ponteiros para jogos e nodos de jogos da lista,criados anteriormente*/
    j_l = jogos_l;
    while(j_l!=NULL){
        aux_j_l = j_l->next;
        free(j_l->jogo->nome);
        free(j_l->jogo);
        free(j_l);
        j_l = aux_j_l;
    }

    /*faz free da memoria das hashtables*/
    for(i = 0; i < MOD; i++){
        node_equipa *e_h,*aux_e_h;
        node_jogo *j_h,*aux_j_h;
        e_h = equipas_h[i]; 
        j_h = jogos_h[i];

        /*faz free da memoria na hashtable das equipas*/
        while(e_h!= NULL){
            aux_e_h = e_h->next;
            free(e_h);
            e_h = aux_e_h;
        }

        /*faz free na memoria na hashtable dos jogos*/
        while(j_h!=NULL){
            aux_j_h = j_h->next;
            free(j_h);
            j_h = aux_j_h;
        }
    }

    return 0;
}

/*Cria um jogo e adiciona-o a jogos_l e jogos_h*/
void novo_jogo(){
    
    /*cria-se 2 vetores para o nome do jogo, um para ler o input e outro para se alocar simplesmente a memoria necessaria*/
    char j_aux[1023],*j_aux1;

    /*cria-se 2 vetores,um para ler do input o nome da equipa1 e outro para ler do input o nome da equipa2*/
    char e1_aux[1023],e2_aux[1023];

    /*cria-se 2 ints score1,score2 para ler do input o score das equipas respetivas e 2 variaveis de controlo q verificam se as equipas existem (0 == nao existe, 1 == existe)*/
    int score1,score2,existe_equipa1 = 0,existe_equipa2 = 0;

    /*lenght_j:tamanho da string de input com o nome do jogo,j:posicao do jogo na hash,
    g_1:posicao da equipa 1 na hash, g_2: posicao da equipa 2 na hash*/
    int lenght_j,j,g_1,g_2;

    /*nodo auxiliar*/
    node_jogo *k;

    /*cria 2 nodos de equipa*/
    node_equipa *e1,*e2;

    /*cria 2 ponteiros para equipa para poder depois atribui-los ao jogo*/
    team *equipa1, *equipa2;

    /*cria ponteiros para o jogo e os nodos de jogo*/
    game *jogo;
    node_jogo *j1, *j2;

    /*inicializacao do input*/
    getchar();
    scanf("%[^:\n]",j_aux);
    getchar();
    scanf("%[^:\n]",e1_aux);
    getchar();
    scanf("%[^:\n]",e2_aux);
    getchar();
    scanf("%d",&score1);
    getchar();
    scanf("%d",&score2);

    /*alocacao de memoria para o nome do jogo*/
    lenght_j = strlen(j_aux);
    j_aux1 = (char*) malloc(lenght_j * sizeof(char) + 1);
    strcpy(j_aux1,j_aux);

    /*utilizando a primeira letra do nome do jogo, verifica a posicao do jogo na hashtable*/
    j = j_aux1[0] % MOD;
    
    /*verifica se o jogo ja existe. caso sim, imprime um erro*/
    for(k = jogos_h[j]; k!= NULL; k = k->next)
        if(strcmp(j_aux1,k->jogo->nome) == 0 ){
            printf("%d Jogo existente.\n",NL);
            free(j_aux1);
            return;
        }

    /*verifica a posicao das equipas na hash,utilizando a primeira letro do nome das equipas */
    g_1 = e1_aux[0] % MOD;
    g_2 = e2_aux[0] % MOD;

    /*verifica se a equipa1 existe*/
    for(e1 = equipas_h[g_1]; e1 != NULL; e1 = e1->next)
        if (strcmp(e1_aux,e1->equipa->equipa) == 0){
            existe_equipa1 = 1;
            equipa1 = e1->equipa;
            break;
        }

    /*verifica se a equipa2 existe*/
    for(e2 = equipas_h[g_2]; e2 != NULL; e2 = e2->next)
        if (strcmp(e2_aux,e2->equipa->equipa) == 0){
            existe_equipa2 = 1;
            equipa2 = e2->equipa; 
            break;
        }

    /*caso alguma nao exista, imprime um erro*/
    if(existe_equipa1 == 0 || existe_equipa2 == 0){
        printf("%d Equipa inexistente.\n",NL);
        free(j_aux1);
        return;
    }

    /*aloca memoria para o jogo e os nodos*/
    jogo = (game*) malloc(sizeof(game));
    j1 = (node_jogo*) malloc(sizeof(node_jogo));
    j2 = (node_jogo*) malloc(sizeof(node_jogo));

    /*inicializa o jogo com os parametros correspondentes*/
    jogo->score1 = score1;
    jogo->score2 = score2;
    jogo->equipa1 = equipa1;
    jogo->equipa2 = equipa2;
    jogo->nome = j_aux1;

    /*acrescenta uma vitoria a equipa com o score mais alto*/
    if(score1>score2)
        jogo->equipa1->vitorias++;
    
    else if(score2>score1)
        jogo->equipa2->vitorias++;

    /*inicializa os nodos com os parametros correspondentes*/
    j1->jogo = jogo; j1->next = NULL;
    j2->jogo = jogo; j2->next = NULL;

    /*verifica se a lista de jogos esta vazia. se estiver, o jogo e a cabeca*/
    if(jogos_l == NULL)
        jogos_l = j1; 

    /*caso a lista tenha elementos, procura o ultimo e insere o jogo la*/
    else{
        
        node_jogo *i1 = jogos_l;
        for(;i1->next!=NULL;i1 = i1->next);
        i1->next = j1;
    }

    /*se a posicao da hash correspondente estiver vazia, o jogo fica a cabeca*/
    if(jogos_h[j] == NULL)
        jogos_h[j] = j2;

    /*se a posicao da hash correspondente tiver elementos, insere-se o jogo no inicio*/
    else{
        node_jogo *aux;
        aux = jogos_h[j];
        j2->next = aux;
        jogos_h[j] = j2;
    }
}

/*Cria uma equipa e adiciona_a a equipas_l e equipas_h*/
void nova_equipa(){
    
    /*cria-se 2 vetores,um para ler o nome da equipa do input(e_aux) e outro para alocar o espaco necessario(e_aux1)*/
    char e_aux[1023], *e_aux1;

    /*cria-se uma equipa*/
    team *equipa;

    /*cria-se dois nodos de equipa, um para a lista e outro para a hashtable*/
    node_equipa *e1,*e2;

    /*inteiro lenght: tamanho da string de input, j: posicao na hash da equipa*/
    int lenght,j;
    
    /*nodo auxiliar*/
    node_equipa *k;

    /*inicializacao do input*/
    getchar();
    scanf("%[^:\n]",e_aux);

    /*alocacao da memoria necessaria para o nome da equipa*/
    lenght = strlen(e_aux);
    e_aux1 = (char*) malloc((lenght+1) * sizeof(char));
    strcpy(e_aux1,e_aux);

    /*utiliza-se a primeira letra para verificar a posicao correspondente na hashtable*/
    j = e_aux1[0] % MOD;

    /*verifica se a equipa ja foi criada. caso sim, da erro, caso nao, cria-se a equipa*/
    for(k = equipas_h[j]; k != NULL; k = k->next)
        if(strcmp(e_aux1,k->equipa->equipa) == 0){
            printf("%d Equipa existente.\n",NL);
            free(e_aux1);
            return;
        }

    /* alocar memoria para a equipa e os nodos */
    equipa = (team*) malloc(sizeof(team));
    e1 = (node_equipa*) malloc(sizeof(node_equipa));
    e2 = (node_equipa*) malloc(sizeof(node_equipa));

    /*inicializa-se a equipa e os nodos com os valores correspondentes */
    equipa->equipa = e_aux1; equipa->vitorias = 0;
    e1->equipa = equipa; e1->next = NULL;
    e2->equipa = equipa; e2->next = NULL;

    /*caso a lista nao tenha elementos(i == NULL), e1 fica a cabeca*/
    if (equipas_l == NULL){
        equipas_l = e1;
        e1->next = NULL;
        }

    /*caso tenha elementos,procura-se a posicao em que e1 seja alfabeticamente maior q o elemento anterior e que e1 seja alfabeticamente menor que o elemento seguinte */
    else{
        node_equipa *i;
        for(i = equipas_l; i!= NULL; i = i->next){
            
            /*caso 1: caso a equipa a adicionar seja alfabeticamente menor que a cabeca da lista*/
            if(strcmp(e1->equipa->equipa,equipas_l->equipa->equipa) < 0){
                e1->next = equipas_l;
                equipas_l = e1;
                break;
            }

            /*caso 2: caso a equipa a adicionar seja alfabeticamente maior que a ultima equipa da lista*/
            else if(i->next == NULL && strcmp(e1->equipa->equipa,i->equipa->equipa) >= 0 ){
                e1->next = i->next;
                i->next = e1;
                break;
            }

            /*caso 3: caso a equipa a adicionar seja alfabeticamente menor que um elemento no meio da lista*/
            else if(strcmp(e1->equipa->equipa,i->next->equipa->equipa) < 0){
                e1->next = i->next;
                i->next = e1;
                break;
            }

        }
    }

    /*se a posicao correspondente a hash estiver vazia(equipas_h[j] == NULL), e2 fica a cabeca*/
    if (equipas_h[j] == NULL)
        equipas_h[j] = e2;
    
    /*caso tenha elementos,insere-se a equipa no inicio*/
    else {
        node_equipa *aux;
        aux = equipas_h[j];
        e2->next = aux;
        equipas_h[j] = e2;
    }
}

/*Percorre todos os jogos por ordem de criacao e imprime-os*/
void lista_jogos(){
    
    /*nodo da lista de jogos*/
    node_jogo *i = jogos_l;

    /*percorre a lista de jogos e imprime os jogos*/
    for(;i != NULL; i = i->next)
        printf("%d %s %s %s %d %d\n", NL,i->jogo->nome,i->jogo->equipa1->equipa,\
        i->jogo->equipa2->equipa,i->jogo->score1,i->jogo->score2);
}

/*Procura pelo jogo e caso ele exista, imprime-o*/
void procura_jogo(){
    
    /*vetor para onde vai ser inicializado o input*/
    char j_aux[1023];

    /*j: posicao do jogo na hash, existe:variavel de controlo, existe == 0: nao existe o jogo, existe == 1: existe o jogo*/
    int j,existe = 0;

    /*ponteiro auxiliar*/
    node_jogo *k;

    /*inicializacao do input*/
    getchar();
    scanf("%[^:\n]",j_aux);

    /*posicao da hash onde o jogo podera estar*/
    j = j_aux[0] % MOD;

    /*verifica se o jogo existe, caso sim, imprime-o*/
    for(k = jogos_h[j]; k != NULL; k = k->next)
        if (strcmp(j_aux,k->jogo->nome) == 0){
            printf("%d %s %s %s %d %d\n",NL,j_aux,k->jogo->equipa1->equipa,\
            k->jogo->equipa2->equipa,k->jogo->score1,k->jogo->score2);
            existe = 1;
            break;
        }

    /*caso nao exista, imprime um erro*/
    if (existe == 0)
        printf("%d Jogo inexistente.\n",NL);
}

/*Procura pela equipa e caso ela exista, imprime-a*/
void procura_equipa(){
    
    /*cria-se 2 vetores,um para ler o nome da equipa do input(e_aux) e outro para alocar o espaco necessario(e_aux1)*/
    char e_aux[1023];

    /*variavel auxiliar para verificar se a equipa existe(existe == 1) ou nao(existe == 0)*/
    int existe = 0;

    /*lugar da hash onde a equipa podera estar*/
    int j;

    /*nodo auxiliar*/
    node_equipa *k;

    /*inicializacao do input*/
    getchar();
    scanf("%[^:\n]",e_aux);
    
    /*utiliza-se a primeira letra para verificar a posicao correspondente na hashtable*/
    j = e_aux[0] % MOD;
    
    /*verifica se a equipa existe. caso exista,imprime o nome e o numero de vitorias*/
    for(k = equipas_h[j]; k != NULL; k = k->next)
        if(strcmp(e_aux,k->equipa->equipa) == 0){
            printf("%d %s %d\n",NL, k->equipa->equipa, k->equipa->vitorias);
            existe = 1;
            break;
        }
    
    /*caso nao exista, da erro*/
    if (existe == 0)
        printf("%d Equipa inexistente.\n",NL);
}

/*Elimina o jogo pretendido*/
void apaga_jogo(){

    /*vetor para onde sera lido o nome do jogo a procurar*/
    char j_aux[1023];

    /*variavel de estado em que existe == 0 -> jogo nao existe, existe == 1-> jogo existe*/
    int existe = 0;

    /*lugar da hash onde a equipa podera estar*/
    int j;

    /*nodo auxiliar*/
    node_jogo *k;

    /*inicializacao do input*/
    getchar();
    scanf("%[^:\n]",j_aux);

    /*verifica a posicao na hash do jogo, utilizando a primeira letra do nome do jogo*/
    j = j_aux[0] % MOD;

    /*verifica se o jogo existe,e caso exista, ajusta as vitorias*/
    for(k = jogos_h[j]; k!= NULL; k = k->next){
        if(strcmp(j_aux,k->jogo->nome)== 0){
            existe = 1;
            if(k->jogo->score1 > k->jogo->score2)
                k->jogo->equipa1->vitorias--;

            else if(k->jogo->score1 < k->jogo->score2)
                k->jogo->equipa2->vitorias--;

            break;
        }
    }

    /*caso nao exista,imprime um erro*/
    if (existe == 0){
        printf("%d Jogo inexistente.\n",NL);
        return;
    }

    /*caso exista,vai eliminar o jogo*/
    else{
        /*nodos utilizados para percorrer a lista existente na hash de jogos na posicao j*/
        node_jogo *prev_h,*i_h,*aux_h;

        /*nodos utilizados para percorrer a lista de jogos*/
        node_jogo *prev_l,*i_l,*aux_l;

        /*inicializacao dos ponteiros para percorrer a lista da hash de jogos*/
        prev_h = jogos_h[j];
        i_h = prev_h->next;

        /*inicializacao dos ponteiros para percorrer a lista de jogos*/
        prev_l = jogos_l;
        i_l = prev_l->next;

        /*caso 1: o jogo e o unico elemento da lista*/
        if(strcmp(j_aux,jogos_h[j]->jogo->nome) == 0 && i_h == NULL){
                aux_h = jogos_h[j];
                jogos_h[j] = i_h;
                free(aux_h);
        }

        for(; i_h != NULL; prev_h = prev_h->next, i_h = i_h->next){
            /*caso 2: o jogo e o primeiro elemento da lista*/
            if(strcmp(j_aux,jogos_h[j]->jogo->nome) == 0){
                aux_h = jogos_h[j];
                jogos_h[j] = i_h;
                free(aux_h);
                break;
            }

            /*caso 3: o jogo e o ultimo elemento da lista*/
            else if(strcmp(j_aux,i_h->jogo->nome) == 0 && i_h->next == NULL){
                prev_h->next = NULL;
                free(i_h);
                break;
            }

            /*caso 4: o jogo esta no meio da lista*/
            else if(strcmp(j_aux,i_h->jogo->nome) == 0){
                aux_h = i_h;
                prev_h->next = i_h->next;
                free(aux_h);
                break;
            }
        }

        /*caso 1: o jogo e o unico elemento da lista*/
        if(strcmp(j_aux,jogos_l->jogo->nome) == 0 && i_l == NULL){
                aux_l = jogos_l;
                jogos_l = i_l;
                free(aux_l->jogo->nome);
                free(aux_l->jogo);
                free(aux_l);
            }

        for(; i_l != NULL; prev_l = prev_l->next, i_l = i_l->next){

            /*caso 2: o jogo e o primeiro elemento da lista*/
            if(strcmp(j_aux,prev_l->jogo->nome) == 0){
                aux_l = jogos_l;
                jogos_l = i_l;
                free(aux_l->jogo->nome);
                free(aux_l->jogo);
                free(aux_l);
                break;
            }   

            /*caso 3: o jogo e o ultimo elemento da lista*/
            else if(strcmp(j_aux,i_l->jogo->nome) == 0 && i_l->next == NULL){
                prev_l->next = NULL;
                free(i_l->jogo->nome);
                free(i_l->jogo);
                free(i_l);
                break;
            }

            /*caso 4: o jogo esta no meio da lista*/
            else if(strcmp(j_aux,i_l->jogo->nome) == 0){
                aux_l = i_l;
                prev_l->next = i_l->next;
                free(aux_l->jogo->nome);
                free(aux_l->jogo);
                free(aux_l);
                break;
            }
        }
    }
}

/*Altera a pontuacao(score) do jogo pretendido*/
void altera_score(){
    
    /*cria-se um vetor para ler o nome do jogo do input*/
    char j_aux[1023];

    /*cria-se 4 ints, 2 para ler do input os novos scores, 2 para ler do jogo os scores antigos*/
    int new_score1,new_score2,old_score1,old_score2;

    /*variavel de controlo existe. existe == 0 caso o jogo nao exista, existe == 1 caso o jogo exista*/
    int existe = 0;

    /*lugar da hash onde a equipa podera estar*/
    int j;

    /*nodo auxiliar*/
    node_jogo *k;

    /*inicializacao do input*/
    getchar();
    scanf("%[^:\n]",j_aux);
    getchar();
    scanf("%d",&new_score1);
    getchar();
    scanf("%d",&new_score2);

    /*verificar em q posicao da hash esta o jogo, utilizando a primeira letra*/
    j = j_aux[0] % MOD;

    /*verifica se o jogo existe*/
    for(k = jogos_h[j]; k!= NULL; k = k->next)
        if(strcmp(j_aux,k->jogo->nome) == 0){
            existe = 1;
            break;
        }

    /*caso exista, trocamos os scores antigos pelos novos, guardando os antigos*/
    if(existe == 1){
        old_score1 = k->jogo->score1;
        old_score2 = k->jogo->score2;
        k->jogo->score1 = new_score1;
        k->jogo->score2 = new_score2;

        /*caso a equipa1 tenha perdido, quando antes tinha ganho, acerta-se as vitorias*/
        if(old_score1>old_score2 && new_score1<new_score2){
            if(k->jogo->equipa1->vitorias != 0)
                k->jogo->equipa1->vitorias--;
            k->jogo->equipa2->vitorias++;
        }

        /*caso a equipa1 tenha ganho, quando antes tinha perdido, acerta-se as vitorias*/
        else if(old_score1<old_score2 && new_score1>new_score2){
            k->jogo->equipa1->vitorias++;
            if(k->jogo->equipa2->vitorias != 0)
                k->jogo->equipa2->vitorias--;
        }

        else if(old_score1==old_score2 && new_score1>new_score2)
            k->jogo->equipa1->vitorias++;

        else if(old_score1==old_score2 && new_score1<new_score2)
            k->jogo->equipa2->vitorias++;

        /*caso o resultado anterior tenha sido uma vitoria para a equipa2 e agora seja um empate, acerta-se as vitorias*/
        else if(old_score1<old_score2 && new_score1==new_score2) {
            k->jogo->equipa2->vitorias--;
        }

        /*caso o resultado anterior tenha sido uma vitoria para a equipa1 e agora seja um empate, acerta-se as vitorias*/
        else if(old_score1>old_score2 && new_score1==new_score2) {
            k->jogo->equipa1->vitorias--;
        }
    }
    /*caso o jogo nao exista, imprime um erro*/
    else{
        printf("%d Jogo inexistente.\n",NL);
    }
}

/*Procura as equipas com mais vitorias e imprime-as por ordem alfabetica*/
void equipa_mais_vitorias(){

    /*se a lista de equipas estiver vazia(head == NULL), nao imprime nada*/
    if (equipas_l == NULL)
        return;

    else{

        /*nodos auxiliares para percorrer a lista de equipas*/
        node_equipa *i,*j;

        /*variavel onde vai ser guardado o numero maximo de vitorias que uma equipa tem*/
        int max = 0;

        /*percorre a lista uma vez e determina o numero maximo de jogos ganhos por uma equipa*/
        for(i = equipas_l; i!= NULL;i = i->next)
            if(i->equipa->vitorias > max)
                max = i->equipa->vitorias;

        /*percorre a lista uma segunda vez e imprime as equipas que tem um numero de vitorias == max*/
        printf("%d Melhores %d\n", NL,max);
        for(j = equipas_l; j!= NULL; j = j->next)
            if(j->equipa->vitorias == max)
                printf("%d * %s\n",NL,j->equipa->equipa);
        
    } 
}