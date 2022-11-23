#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "futebol.h"

struct _equipa{
    char *nome_equipa;
    int score;
};

struct _jogo{
    char *nome_jogo;
    equipa *eq1;
    equipa *eq2;
    int sc1;
    int sc2;
};


ptr_jogo procurajogo(hashtable* hjogos, char* nome){
    ptr_jogo procura;
    link node_aux;
    list* l;
    l = lehash(hjogos, nome); /*lista do indice correspondente a nome do jogo*/

    if (l==NULL){
        return NULL;
    }

    /*head da lista onde esta o jogo*/
    node_aux = headlista(l);

    /*percorre lista ate encontrar o jogo e retorna o pointer para o jogo caso existe, senao retorna NULL*/
    while(node_aux != NULL){

        procura = (ptr_jogo)lenode(node_aux);

        if(!strcmp(procura->nome_jogo,nome)){

            return procura;
        }

        node_aux = nextnode(node_aux);
    }

    return NULL;

}

ptr_equipa procuraequipa(hashtable* hequipas, char* nome){
    ptr_equipa procura;
    link node_aux;
    list* l;

    l = lehash(hequipas, nome); /*lista do indice correspondente a nome da equipa*/
    
    if (l==NULL){

        return NULL;
    }

    /*head da lista onde esta a equipa*/
    node_aux = headlista(l);

    /*percorre lista ate encontrar a equipa e retorna o pointer para a equipa caso existe, senao retorna NULL*/
    while(node_aux != NULL){

        procura = (ptr_equipa)lenode(node_aux);

        if(!strcmp(procura->nome_equipa,nome)){

            return procura;
        }

        node_aux = nextnode(node_aux);
    }

    return NULL;

}

void adiciona_jogo(char *nome,char *eq1,char *eq2, int sc1, int sc2, hashtable* hequipas, hashtable* hjogos, list* ljogos,int NL){
    
    ptr_jogo j;
    ptr_equipa e1;
    ptr_equipa e2;

    /*se ja houver um jogo, retorna erro*/
    if(procurajogo(hjogos, nome)!=NULL){
        printf("%d Jogo existente.\n", NL);
        return;
    }

    /*ponteiro para equipas do jogo*/
    e1 = procuraequipa(hequipas, eq1);
    e2 = procuraequipa(hequipas, eq2);


    /*se alguma das equipas nao existir, o seu ponteiro estara a apontar para NULL. se nao existir equipa, retorna erro*/
    if((e1==NULL) || (e2==NULL)){
        printf("%d Equipa inexistente.\n", NL);
        return;
    }

    j = (ptr_jogo)can_fail_malloc(sizeof(jogo));

    j->nome_jogo = (char*)can_fail_malloc(sizeof(char)*(strlen(nome)+1));

    strcpy(j->nome_jogo,nome);

    /*eq1 e eq2 de jogo sao pointer para equipa 1 e equipa 2*/
    j->eq1 = e1;

    j->eq2 = e2;

    j->sc1 = sc1;

    j->sc2 = sc2;

    /*atualiza vitoria da equipa 1 ou da equipa 2, em caso de empate nada muda*/
    if (sc1>sc2){
        e1->score += 1;
    }
    if (sc2>sc1){
        e2->score += 1;
    }

    /*adicionar j a lista e hash*/
    adicionalista(ljogos, (Item)j);
    inserehash(hjogos, (Item)j, nome);

    return;

}

void lista_jogos(list* ljogos,int NL){
    /*pointer tipo link para percorrer cada node da lista jogos*/
    link node_aux;
    /*pointer tipo jogo para aceder a cada item de cada no da lista*/
    ptr_jogo elemento;

    node_aux = headlista(ljogos);

    while(node_aux != NULL){

        /*aceder ao item do node*/
        elemento = (ptr_jogo)lenode(node_aux);

        printf("%d %s %s %s %d %d\n", NL, elemento->nome_jogo, elemento->eq1->nome_equipa, elemento->eq2->nome_equipa, elemento->sc1, elemento->sc2);
        
        /*avancar para o proximo node*/
        node_aux = nextnode(node_aux);
    }

    return;

}

void procura_jogo(hashtable* hjogos, char* nome, int NL){
    ptr_jogo jogo_encontrar;
    /*retorna o pointer para o jogo caso exista, ou NULL caso nao exista*/
    jogo_encontrar = procurajogo(hjogos, nome);
    
    if (jogo_encontrar==NULL){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    printf("%d %s %s %s %d %d\n", NL, jogo_encontrar->nome_jogo, jogo_encontrar->eq1->nome_equipa, jogo_encontrar->eq2->nome_equipa, jogo_encontrar->sc1, jogo_encontrar->sc2);
    return;
}


void apaga_jogo(hashtable* hjogos, list* ljogos, char* nome, int NL){

    ptr_jogo jogo_eliminar;
    /*retorna o pointer para o jogo caso exista, ou NULL caso nao exista*/
    jogo_eliminar = procurajogo(hjogos, nome);

    if(jogo_eliminar==NULL){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    /*mudar o numero de vitorias da equipa vencedora*/
    if (jogo_eliminar->sc1>jogo_eliminar->sc2){
        jogo_eliminar->eq1->score-=1;
    }

    if (jogo_eliminar->sc2>jogo_eliminar->sc1){
        jogo_eliminar->eq2->score-=1;
    }

    removehash(hjogos, (Item)jogo_eliminar, nome);    
    removelista(ljogos, (Item)jogo_eliminar);
    /*free jogo*/ 
    freejogo(jogo_eliminar);

    return;

}

void altera_score(hashtable* hjogos, char* nome, int newsc1, int newsc2, int NL){

    ptr_jogo jogo_mudar;
    jogo_mudar = procurajogo(hjogos, nome);


    /*caso nao exista nenhum jogo com o nome dado registado, retorna erro*/
    if (jogo_mudar==NULL){

        printf("%d Jogo inexistente.\n", NL);
        return;

    }

    /*mudar total vitorias da equipa vencedora, se esse for o caso*/
    /*a equipa 1 vence com a alteracao do jogo*/
    if (newsc1>newsc2){

        /*caso a eq2 fosse a antiga vencedora, tira uma vitoria a eq2 e adiciona vitoria a eq1*/
        if(jogo_mudar->sc2 > jogo_mudar->sc1){
            jogo_mudar->eq2->score-=1;
            jogo_mudar->eq1->score+=1;
        }

        /*caso nenhuma das equipa tivesse ganho, adiciona vitoria a eq1*/
        if(jogo_mudar->sc1 == jogo_mudar->sc2){
            jogo_mudar->eq1->score+=1;
        }


    }

    /*a equipa 2 vence com a alteracao do jogo*/
    if (newsc2>newsc1){

        /*caso a eq1 fosse a antiga vencedora, tira uma vitoria a eq1 e adiciona vitoria a eq2*/
        if(jogo_mudar->sc1 > jogo_mudar->sc2){
            jogo_mudar->eq1->score-=1;
            jogo_mudar->eq2->score+=1;
        }

        /*caso nenhuma das equipa tivesse ganho, adiciona vitoria a eq2*/
        if(jogo_mudar->sc1 == jogo_mudar->sc2){
            jogo_mudar->eq2->score+=1;
        }
        
    }

    /*com a alteracao do jogo, nao ha vencedor*/
    if (newsc2==newsc1){

        /*caso a eq1 fosse a antiga vencedora, tira uma vitoria a eq1*/
        if(jogo_mudar->sc1 > jogo_mudar->sc2){
            jogo_mudar->eq1->score-=1;
        }

        /*caso a eq2 fosse a antiga vencedora, tira uma vitoria a eq2*/
        if(jogo_mudar->sc2 > jogo_mudar->sc1){
            jogo_mudar->eq2->score-=1;
        }
    }

    /*mudar score jogo*/
    jogo_mudar->sc1 = newsc1;
    jogo_mudar->sc2 = newsc2;

    return;

}

void adiciona_equipa(char *nome, hashtable* hequipas, int NL){
    ptr_equipa e;

    /*se ja houver a equipa, retorna erro*/
    if(procuraequipa(hequipas, nome)!=NULL){
        printf("%d Equipa existente.\n", NL);
        return;
    }    

    e = (ptr_equipa)can_fail_malloc(sizeof(equipa));

    e->nome_equipa = (char*)can_fail_malloc(sizeof(char)*(strlen(nome)+1));

    strcpy(e->nome_equipa,nome);

    e->score = 0;

    /*adicionar equipa a hash*/
    inserehash(hequipas, (Item)e, nome);

    return;

}

void procura_equipa(hashtable* hequipas, char* nome, int NL){
    ptr_equipa equipa_encontrar;
    /*retorna o pointer para a equipa caso exista, ou NULL caso nao exista*/
    equipa_encontrar = procuraequipa(hequipas, nome);
    
    if (equipa_encontrar==NULL){
        printf("%d Equipa inexistente.\n", NL);
        return;
    }

    printf("%d %s %d\n", NL, equipa_encontrar->nome_equipa, equipa_encontrar->score);
    return;
}


void freejogo(Item _item){
    /*transformar Item em ptr_jogo, para aceder a nome_jogo*/
    ptr_jogo j;
    j = (ptr_jogo)_item;
    free(j->nome_jogo);
    free(j);
} 

void freeequipa(Item _item){
   /*transformar Item em ptr_equipa, para aceder a nome_equipa*/
    ptr_equipa e;
    e = (ptr_equipa)_item;
    free(e->nome_equipa);
    free(e);
} 

void mais_vitorias(hashtable* hequipas, int M, int NL){
    /*ptr para cada lista de cada indice da hashtable*/
    list* ptr_lista;

    /*pointer node para percorrer os node de cada lista*/
    link ptr_node;

    /*pointer para cada equipa da lista*/
    ptr_equipa eq;

    /*lista onde se vai acumulando as equipas com o max numero de vitorias*/
    list* vitorias;

    /*pointer para head da tree inicializado a NULL*/
    nodetree* arvore = NULL;

    /*pointer chars correspondente aos nomes das equipas com mais vitorias a inserir na arvore*/
    char* item_tree;

    int i;
    int max;
    max = 0;

    /*lista das equipas com maximo de vitorias*/
    vitorias = crialista();

    /*percorrer a hastable, M tamanho da hashtable*/
    for(i=0;i<M;i++){

        ptr_lista = indice_hastable(hequipas, i);

        if(ptr_lista==NULL){

            continue;

        }
        
        /*caso haja uma lista num indice i, percorrer a lista e verificar se ha alteracoes no max de vitorias ou equipas a adicionar a lista vitorias*/
        for(ptr_node = headlista(ptr_lista); ptr_node!=NULL; ptr_node=nextnode(ptr_node)){

            eq = (ptr_equipa)lenode(ptr_node);

            /*se score avaliado for menor do que o max, avanca*/
            if (max > (eq->score)){

                continue;
            }

            /*se score avaliado for igual ao max, adiciona a lista vitorias*/
            if (max == (eq->score)){

                adicionalista(vitorias, (Item)(eq->nome_equipa));

                continue;
            }

            /*se score avaliado for maior do que o max, max atualiza e passa a ter o valor do score, free da lista atual vitorias, criar uma nova lista vitorias e adicionar a nova lista a equipa*/
            if (max < (eq->score)){

                max = (eq->score);

                freelista(vitorias, 0, free);

                vitorias = crialista();

                adicionalista(vitorias, (Item)(eq->nome_equipa));

                continue;
            }
        }
    }

    /*caso nao hajam equipas, nao imprime nada*/
    if (lista_vazia(vitorias)){
        free(vitorias);
        return;
    }

    printf("%d Melhores %d\n",NL,max);

    /*adicionar os nomes de cada equipa de vitorias, a uma arvore onde vao ser adicionadas por ordem alfabetica*/
    for(ptr_node = headlista(vitorias); ptr_node!=NULL; ptr_node=nextnode(ptr_node)){

        item_tree = (char*)lenode(ptr_node);
        arvore = insere_tree(arvore, item_tree);

    }    

    /*print das equipas por ordem alfabetica*/
    imprime_eq_vitorias(arvore, NL);        
    /*free da lista vitorias, sem se dar free a equipas*/
    freelista(vitorias, 0, free);

    return;

}


void imprime_eq_vitorias(nodetree* nt, int NL){

    if(nt != NULL){

        /*visita a raiz depois do filho esquerdo e antes do direito*/
        imprime_eq_vitorias(nodetree_left(nt), NL); 
        printf("%d * %s\n", NL, nodetree_item(nt)); 
        imprime_eq_vitorias(nodetree_right(nt), NL);
        free(nt);
    }
}

