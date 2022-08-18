#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

/* ---INICIO DAS FUNCOES COMPLEMENTARES---*/

/* Funcao que adiciona uma equipa a lista de equipas.
*   Esta adicao e feita por ordem alfabetica, ou seja,
*   a lista e percorrida ate encontrar um elemento
*   lexicamente superior (e1), colocando a nova equipa entre
*   e1 e o elemento anterior da lista.                  */  
void adiciona_equipa_lista(equipa *e){
    node_e *n=malloc(sizeof(node_e)),*tmp=head_e;
    n->seguinte=NULL;
    n->equipa=e;
    n->anterior=NULL;
    if(tmp==NULL){head_e=n;return;}
    while (strcmp(e->nome,tmp->equipa->nome)>0 && tmp->seguinte != NULL){
        tmp=tmp->seguinte;
    }
    if (tmp->seguinte==NULL && strcmp(e->nome,tmp->equipa->nome)>0){
        tmp->seguinte=n;
        n->anterior=tmp;
    } else if (tmp==head_e && strcmp(e->nome,tmp->equipa->nome)<0){
        tmp->anterior=n;
        n->seguinte=tmp;
        head_e=n;
    } else {
        tmp->anterior->seguinte=n;
        n->anterior=tmp->anterior;
        n->seguinte=tmp;
        tmp->anterior=n;
    }
}

/* Funcao que adiciona um jogo a lista de jogos (sempre na tail da mesma) */
void adiciona_jogo_lista(jogo *j){
    node_j *n=malloc(sizeof(node_j));
    n->seguinte=NULL;
    n->anterior=tail_j;
    n->jogo=j;
    if(tail_j !=NULL){
        tail_j->seguinte = n;
    }
    tail_j=n;
    if(head_j == NULL){head_j=n;}
}

/*Funcao que devolve a chave para a hashkey,
utilizando o comprimento do nome e as letras que o constituem */

unsigned int hash(char *nome){          
    int length = strlen(nome),i;
    unsigned int hash_value = 0;
    for (i=0;i<length;i++){
        hash_value += nome[i];
        hash_value = (nome[i] * hash_value) % MAX_HASH;
    }
    return hash_value;
}

/*Utiliza a chave obtida na funcao hash
* para colocar uma equipa na hash. No caso de colisao,
* esta e colocada na tail da linked list la presente */
int adiciona_equipa_hash(equipa *e){
    int i=hash(e->nome);
    e->seguinte=hash_equipas[i];
    hash_equipas[i] = e;
    return i;
}

/* Utiliza a chave obtida na funcao hash
* para colocar um jogo na hash. No caso de colisao,
* esta e colocada na tail da linked list la presente */

void adiciona_jogo_hash(jogo *j){
    int i=hash(j->nome);
    j->seguinte=hash_jogos[i];
    hash_jogos[i] = j;
}

/*Funcao auxiliar que altera o numero de vitorias das equipas
* de acordo com o resultado dos jogos */

void adiciona_jogo_aux(equipa *e1,equipa *e2,jogo *j){
    if (j->score1 > j->score2){
        e1->vitorias = e1->vitorias + 1;
    } else if (j->score2 > j->score1){
        e2->vitorias = e2->vitorias + 1;
    }
}
        
/*Funcao que recebe o nome de uma equipa e verifica 
* se a mesma ja se encontra no sistema.
* Se sim, devolve a equipa.
* Se nao, devolve NULL.  */
equipa *procura_equipa_hash(char *nome){
    int index=hash(nome);
    equipa *tmp = hash_equipas[index];
    while (tmp != NULL && strcmp(tmp->nome,nome)!=0){tmp=tmp->seguinte;}
    return tmp;
}
/*Funcao que recebe o nome de um jogo e verifica 
* se o mesmo ja se encontra no sistema.
* Se sim, devolve a equipa.
* Se nao, devolve NULL.  */
jogo *procura_jogo_hash(char *nome){
    int index=hash(nome);
    jogo *tmp = hash_jogos[index];
    while (tmp != NULL && strcmp(tmp->nome,nome)!=0){tmp=tmp->seguinte;}
    return tmp;
}


/*Funcao que recebe o nome de um jogo e verifica 
* se o mesmo ja se encontra no sistema utilizando a
* funcao procura_jogo_hash.
* Se sim, remove o jogo da hash table.
* Se nao, devolve NULL.  */

jogo *remove_jogo_hash(char *nome){
    int index=hash(nome);
    jogo *tmp = hash_jogos[index];
    jogo *anterior = NULL;
    while (tmp != NULL && strcmp(tmp->nome,nome)!=0){
        anterior=tmp;
        tmp=tmp->seguinte;
    }
    if (tmp==NULL){return NULL;}
    if(anterior == NULL){
        hash_jogos[index]= tmp->seguinte;
    } else {
        anterior->seguinte=tmp->seguinte;
    }
    return tmp;
}

/*Funcao que recebe um jogo e o remove da lista de jogos.*/

void remove_jogo_lista(jogo *j){
    int i=0;
    node_j *tmp,*anterior,*seguinte;
    if (j==head_j->jogo){i++,tmp=head_j,head_j=head_j->seguinte;}
    if (j==tail_j->jogo){i++,tmp=tail_j,tail_j=tail_j->anterior;}
    if (i==0){
    anterior=head_j;
    tmp=head_j->seguinte;
    seguinte=tmp->seguinte;
    while (j!=tmp->jogo){
        anterior=anterior->seguinte;
        tmp=tmp->seguinte;
        seguinte=seguinte->seguinte;
    }
    anterior->seguinte=seguinte;
    seguinte->anterior=anterior;
    }
    free(tmp);
}


/*Funcao auxiliar que altera o numero de vitorias das equipas
* de acordo com o resultado do jogo, anulando as alteracoes feitas
* quando este foi adicionado. */
void reverte(jogo *tmp){
    equipa *e1,*e2;
    e1=procura_equipa_hash(tmp->equipa1);
    e2=procura_equipa_hash(tmp->equipa2);
    if (tmp->score1 > tmp->score2){
        e1->vitorias = e1->vitorias - 1;
    }
    if (tmp->score2 > tmp->score1){
        e2->vitorias = e2->vitorias - 1;
    }
}

/*Funcao que recebe o nome de um jogo e muda os scores do mesmo.
    Se o jogo nao existir, retorna NULL sem alterar nada. */

jogo *altera_jogo_hash(char *nome_jogo,int score1_n,int score2_n){
    equipa *e1,*e2;
    jogo *tmp=procura_jogo_hash(nome_jogo);
    if (tmp==NULL){return(tmp);}
    reverte(tmp);
    tmp->score1=score1_n;
    tmp->score2=score2_n;
    e1=procura_equipa_hash(tmp->equipa1);
    e2=procura_equipa_hash(tmp->equipa2);
    adiciona_jogo_aux(e1,e2,tmp);
    return(tmp);
}

/*Funcao auxiliar que percorre a lista das equipas e devolve
  o numero de vitorias maximo entre todas as equipas */

int maximo(){
    int i=0;
    node_e *tmp=head_e; 
    while (tmp != NULL){
        if (tmp->equipa->vitorias > i){
            i=tmp->equipa->vitorias;
        }
        tmp=tmp->seguinte;
    }
    return i;
}

/* Funcao final que liberta toda a memoria alocada ao longo do programa,
* percorrendo primeiramente a lista de equipas e depois a lista dos jogos*/

void finaliza(int equipas){
    node_e *tmp1=head_e;
    node_j *tmp2=head_j;
    if(equipas==0){return;}
        while (tmp1->seguinte!=NULL){
            free(tmp1->equipa->nome);
            free(tmp1->equipa);
            tmp1=tmp1->seguinte;
            free(tmp1->anterior);
        }
    free(tmp1->equipa->nome),free(tmp1->equipa),free(tmp1);
    if(tail_j==NULL){return;}
        while (tmp2!=tail_j){
            free(tmp2->jogo->nome),free(tmp2->jogo->equipa1),free(tmp2->jogo->equipa2);
            free(tmp2->jogo);
            tmp2=tmp2->seguinte;
            free(tmp2->anterior);
        }
        free(tmp2->jogo->nome),free(tmp2->jogo->equipa1),free(tmp2->jogo->equipa2),free(tmp2->jogo),free(tmp2);
}


/* FIM DAS FUNCOES COMPLEMENTARES */


/* INICIO DAS FUNCOES PRINCIPAIS */

/* Funcao chamada pelo comando a:
* 1-Recebe a string dados e separa-a,
* 2-Procura o jogo na hash_table (Se este existir, da erro e sai da funcao)
* 3-Procura ambas as equipas na hash_table (Se alguma destas nao estiver,
*   da erro e sai da funcao)
* 4-Aloca a memoria necessaria para um jogo e passa os dados do mesmo para a struct
* 5-Adiciona o jogo a lista e hash_table, alterando as vitorias das equipas caso necessario */


int AdicionarJogo(int nl,char dados[3098],int jogos){
    char equipa1[MAX_CARACTERES],equipa2[MAX_CARACTERES],nome_jogo[MAX_CARACTERES];
    int score1,score2;
    jogo *j1,*tmp;
    equipa *e1,*e2;
    strcpy(nome_jogo, strtok(dados,":"));
    strcpy(equipa1, strtok(NULL,":"));
    strcpy(equipa2, strtok(NULL,":"));
    score1=atoi(strtok(NULL,":"));
    score2=atoi(strtok(NULL,"\n"));
    tmp=procura_jogo_hash(nome_jogo);
    if(tmp!=NULL){
        printf("%d Jogo existente.\n",nl);
        return jogos;
    }
    e1=procura_equipa_hash(equipa1);
    e2=procura_equipa_hash(equipa2);
    if(e1==NULL || e2==NULL){
        printf("%d Equipa inexistente.\n",nl);
        if(e1==NULL){free(e1);}
        if(e2==NULL){free(e2);}
        free(tmp);
        return jogos;
    }
    j1=malloc(sizeof(jogo));
    j1->nome=malloc(sizeof(char)*(strlen(nome_jogo)+1));
    j1->equipa1=malloc(sizeof(char)*(strlen(equipa1)+1));
    j1->equipa2=malloc(sizeof(char)*(strlen(equipa2)+1));
    j1->score1=score1;
    j1->score2=score2;
    strcpy(j1->nome, nome_jogo);
    strcpy(j1->equipa1, equipa1);
    strcpy(j1->equipa2, equipa2);
    adiciona_jogo_hash(j1);
    adiciona_jogo_lista(j1);
    adiciona_jogo_aux(e1,e2,j1);
    free(tmp);
    return ++jogos;
}

/* Funcao chamada pelo comando A:
* 1-Recebe a string dados e separa-a,
* 2-Procura a equipa na hash_table (Se esta existir, da erro e sai da funcao)
* 3-Aloca a memoria necessaria para uma equipa e passa os dados da mesma para a struct */

int AdicionarEquipa(int nl,char dados[3098],int equipas){
    equipa *e, *tmp;
    char nome[MAX_CARACTERES];
    strcpy(nome,strtok(dados,"\n"));
    tmp= procura_equipa_hash(nome);
    if(tmp==NULL){
        e=malloc(sizeof(equipa));
        e->nome=malloc(sizeof(char)*(strlen(nome)+1));
        e->vitorias=0;
        strcpy(e->nome,nome);
        adiciona_equipa_hash(e);
        adiciona_equipa_lista(e);
        free(tmp);
        return ++equipas;
    } else {
        printf("%d Equipa existente.\n",nl);
        return equipas;
    }
}

/* Funcao chamada pelo comando l:
* 1-Lista os jogos comecando pela head_l
*/

void ListaJogos(int nl,int jogos){
    node_j *tmp=head_j;
    jogo *j;
    if (jogos==0){return;}
    if (jogos==1){
        j=tmp->jogo;
        printf("%d %s %s %s %d %d\n",nl,j->nome,j->equipa1,j->equipa2,j->score1,j->score2);
        return;
    }
    while(tmp!=NULL){
        j=tmp->jogo;
        printf("%d %s %s %s %d %d\n",nl,j->nome,j->equipa1,j->equipa2,j->score1,j->score2);
        tmp=tmp->seguinte;
    }
}

/* Funcao chamada pelo comando p:
* 1-Procura o jogo na hash_table (Se nao o encontrar, da erro e sai da funcao)
* 2-Imprime as informacoes do jogo (nome,equipas e resultado)
*/

void ProcuraJogo(int nl,char dados[3098]){
    char nome_jogo[MAX_CARACTERES];
    jogo *tmp;
    strcpy(nome_jogo, strtok(dados,"\n"));
    tmp=procura_jogo_hash(nome_jogo);
    if (tmp==NULL){
        printf("%d Jogo inexistente.\n",nl),free(tmp);
    } else {
        printf("%d %s %s %s %d %d\n",nl,tmp->nome,tmp->equipa1,tmp->equipa2,tmp->score1,tmp->score2);
    }
}

/* Funcao chamada pelo comando P:
* 1-Procura a equipa na hash_table (Se nao a encontrar, da erro e sai da funcao)
* 2-Imprime as informacoes da equipa (nome e vitorias)
*/

void ProcuraEquipa(int nl,char dados[3098]){
    char nome[MAX_CARACTERES];
    equipa *tmp;
    strcpy(nome, strtok(dados,"\n"));
    tmp=procura_equipa_hash(nome);
    if (tmp==NULL){
        printf("%d Equipa inexistente.\n",nl),free(tmp);
    } else {
        printf("%d %s %d\n",nl,tmp->nome,tmp->vitorias);
    }
}

/* Funcao chamada pelo comando r:
* 1-Procura o jogo na hash_table e remove-o (Se nao o encontrar, da erro e sai da funcao)
* 2-Remove o jogo da lista de jogos
* 3-Anula as vitorias obtidas no jogo
* 4-Liberta a memoria alocada pelo jogo
*/


int RemoveJogo(int nl,char dados[3098],int jogos){
    char nome_jogo[MAX_CARACTERES];
    jogo *tmp;
    strcpy(nome_jogo, strtok(dados,"\n"));
    tmp=remove_jogo_hash(nome_jogo);
    if (tmp==NULL){
        printf("%d Jogo inexistente.\n",nl);
        free(tmp);
        return jogos;    
    }
    remove_jogo_lista(tmp);
    reverte(tmp);
    free(tmp->nome),free(tmp->equipa1),free(tmp->equipa2);
    free(tmp);
    if (jogos==1){
        head_j=NULL;
        tail_j=NULL;
    }
    return --jogos;
}

/* Funcao chamada pelo comando s:
* 1-Procura o jogo na hash_table e altera-o (Se nao o encontrar, da erro e sai da funcao)
*/

void AlteraScore(int nl,char dados[3098]){
    char nome_jogo[MAX_CARACTERES];
    int score1,score2;
    jogo *tmp;
    strcpy(nome_jogo, strtok(dados,":"));
    score1=atoi(strtok(NULL,":"));
    score2=atoi(strtok(NULL,"\n"));
    tmp=altera_jogo_hash(nome_jogo,score1,score2);
    if (tmp==NULL){printf("%d Jogo inexistente.\n",nl),free(tmp);}
}
/* Funcao chamada pelo comando g:
* 1-Utiliza a funcao maximo() para encontrar o numero de jogos ganhos pelos vencedores
* 2-Imprime o nome das equipas que tem o numero de vitorias
*/

void Vencedores(int nl,int equipas){
    node_e *tmp;
    int i;
    if(equipas==0){return;}
    i=maximo();
    tmp=head_e;
    printf("%d Melhores %d\n",nl,i);
    while (tmp!=NULL){
        if(tmp->equipa->vitorias == i){
            printf("%d * %s\n",nl,tmp->equipa->nome);
        }
        tmp=tmp->seguinte;
    }
}
/*Funcao main que recebe o input do utilizador, 
* retira o comando e altera a string deixando apenas as variaveis */

int main(){
    char c,dados[3100];             /*c vai guardar o comando e dados e a string de input*/
    int nl=0,equipas=0,jogos=0;     /*nl regista o numero de comandos inseridos,
                                    equipas o num de equipas e jogos o num de jogos*/
    while(1){                       /* ciclo infinito quebrado pelo comando x*/
    nl+=1;                          /*incrementa nl sempre que o ciclo e corrido*/
    fgets(dados,3100,stdin);        /*recebe a string do utilizador*/
    c=dados[0];                     /*atribui a c o comando inserido*/
    memmove(dados,dados+2,3098);    /*altera a sting de modo a deixar apenas os dados para cada comando*/
        switch(c){                  
            case 'a':jogos=AdicionarJogo(nl,dados,jogos);break;                     
            case 'A':equipas=AdicionarEquipa(nl,dados,equipas);break;                                                                   
            case 'l':ListaJogos(nl,jogos);break;                                                                                         
            case 'p':ProcuraJogo(nl,dados);break;                      
            case 'P':ProcuraEquipa(nl,dados);break;                                                                         
            case 'r':jogos=RemoveJogo(nl,dados,jogos);break;                                            
            case 's':AlteraScore(nl,dados);break;                                                    
            case 'g':Vencedores(nl,equipas);break;                                                                    
            case 'x':finaliza(equipas);return 0;                                      
        }                                                                                      
    }
}

/* FIM DAS FUNCOES PRINCIPAIS (e do programa) */