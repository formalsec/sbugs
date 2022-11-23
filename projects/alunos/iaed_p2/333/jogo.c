#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "jogo.h"

/* faz a inicializacao da hash table dos jogos 
retorna a hash table */
hash_table * cria_hash_table(){
    hash_table * rv = can_fail_malloc(sizeof(hash_table));
    rv->capacidade = CAP;
    rv->tb_jogo = can_fail_calloc(rv->capacidade, sizeof(hash_node*)); /* poe tudo a zero */
    
    return rv; 
}

/* funcao que cria os nos para colocar 
na hash table e retorna o no inicial */
hash_node * cria_no( hash_node * inicio){
    hash_node * nn = can_fail_malloc(sizeof(hash_node));
    nn->proximoNo = inicio;
    inicio = nn;

    return inicio;
}

/* 
funcao que verifica se o nome do jogo 
existe dentro da hash table dos jogos
 */
int verificaExiste_jogo(hash_table * hashJogo,  char * jogo){ 
    hash_node * n;
    size_t h = hash(jogo, hashJogo->capacidade);
    for (n=hashJogo->tb_jogo[h]; n != NULL; n = n->proximoNo){
        if (strcmp(n->informacoes_jogo->nome_jogo, jogo) == 0){        /* palavra esta na hashtable  */
            return 0;
        }
    }
    return 1;
}

/* 
funcao que verifica se o nome da quipa
existe dentro da hash table das equipas
 */
int verificaEquipaDentro_aux_1(hash_table_equipa* t, char * equipa1, size_t h){
    hash_node_equipa * n;
    
    for(n=t->tb[h]; n != NULL; n = n->next){
        if ((strcmp(n->equipa1, equipa1) == 0) ){        
            return 0;                    
        }
    }            
    return 1; 
} 
/* 
funcao que verifica se o nome da quipa
existe dentro da hash table das equipas
 */
int verificaEquipaDentro_aux_2(hash_table_equipa* t, char * equipa2, size_t h){
    hash_node_equipa * n;
    
    for(n=t->tb[h]; n != NULL; n = n->next){
        if ((strcmp(n->equipa1, equipa2) == 0) ){        
            return 0;                    
        }
    }            
    return 1; 
} 


/* funcao que verifica se a equipa existe e 
se existir aumenta as vitoias dessa */
void aumentaGanhos(hash_table_equipa * hashEquipa, hash_node_equipa * equipaAux, size_t h_eq, char * equipa){
    for (equipaAux = hashEquipa->tb[h_eq]; equipaAux; equipaAux = equipaAux->next){
        if (strcmp(equipaAux->equipa1, equipa) == 0){ 
            equipaAux->vitorias += 1; 
            return;
        }
    }     
}

/* funcao que adiciona um jogo na hash table dos jogos
verifica se os nomes das equipas introduzidas
estao dentro da hash table das equipas
aumenta as vitorias a equipa que teve maior pontucao
 */
void adiciona_jogo(hash_table * hash_jogo, int * Nr_linha, hash_table_equipa * hashEquipa, inicioFimJogos * Lista_jogos){
    char nome_jogo[MAX], equipa1[MAX], equipa2[MAX]; int pontos1, pontos2; hash_node_equipa * equipa_aux ; 
    NoListaJogos * novo_jogo; size_t h, h_eq1, h_eq2; hash_node * n;
    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome_jogo, equipa1, equipa2, &pontos1, &pontos2);
    h = hash(nome_jogo, hash_jogo->capacidade);
    for (n=hash_jogo->tb_jogo[h]; n != NULL; n = n->proximoNo){
        if (strcmp(n->informacoes_jogo->nome_jogo, nome_jogo) == 0){ 
            printf("%d Jogo existente.\n", *Nr_linha); *Nr_linha += 1; return; }
    } 
    h_eq1 = hash(equipa1, hashEquipa->capacidade_equipa); h_eq2 = hash(equipa2, hashEquipa->capacidade_equipa);
    
    if ((verificaEquipaDentro_aux_1(hashEquipa, equipa1, h_eq1) == 1) || 
        verificaEquipaDentro_aux_2(hashEquipa, equipa2, h_eq2) == 1){
        printf("%d Equipa inexistente.\n", *Nr_linha); *Nr_linha += 1; return; }  

    if (pontos1 > pontos2){ equipa_aux = hashEquipa->tb[h_eq1]; aumentaGanhos(hashEquipa, equipa_aux, h_eq1, equipa1);}
    if (pontos1 < pontos2){ equipa_aux = hashEquipa->tb[h_eq2]; aumentaGanhos(hashEquipa, equipa_aux, h_eq2, equipa2);}

    novo_jogo = can_fail_malloc(sizeof(NoListaJogos)); hash_jogo->tb_jogo[h] = cria_no( hash_jogo->tb_jogo[h]);
    novo_jogo->nome_jogo = aloca_memoria(nome_jogo); novo_jogo->equipa1 = aloca_memoria(equipa1); 
    novo_jogo->equipa2 = aloca_memoria(equipa2); novo_jogo->pontos1 = pontos1; novo_jogo->pontos2 = pontos2;       
    novo_jogo->anterior = Lista_jogos->fim; novo_jogo->proximo = NULL;
    
    if (Lista_jogos->fim != NULL){ Lista_jogos->fim->proximo = novo_jogo; } 
    else{ Lista_jogos->inicio = novo_jogo; }
    /* coloca na hash table */
    Lista_jogos->fim = novo_jogo; hash_jogo->tb_jogo[h]->informacoes_jogo = novo_jogo; 
    *Nr_linha += 1; 
}


/* printa a informacao reletivamente ao jogo */
void print_info_jogo(int * Nr_linha, hash_node *cp) {
    printf("%d %s %s %s %d %d\n",*Nr_linha, 
    cp->informacoes_jogo->nome_jogo, 
    cp->informacoes_jogo->equipa1, 
    cp->informacoes_jogo->equipa2, 
    cp->informacoes_jogo->pontos1, 
    cp->informacoes_jogo->pontos2);
}

/* funcao que verifica se um jogo existe dentro da hash table dos jogos e printa toda a sua informacao*/
void procura_jogo(hash_table * t, int *Nr_linha){ /* fazer a procura  */
    char jogo[MAX];
    hash_node * jogo_aux;
    size_t h;
    
    scanf("%[^:\n]", jogo);
    h = hash(jogo, t->capacidade);
    for (jogo_aux = t->tb_jogo[h]; jogo_aux; jogo_aux = jogo_aux->proximoNo){ /* percorre toda a hash_jogo */
        if (strcmp(jogo_aux->informacoes_jogo->nome_jogo, jogo) == 0){
            print_info_jogo(Nr_linha, jogo_aux);
            *Nr_linha += 1;
            return;
        }   
    } 
    printf("%d Jogo inexistente.\n", *Nr_linha);
    *Nr_linha += 1;
}



/* funcao que verifica se a equipa existe e entao
caso exista diminui o nr de vitorias dessa equipa*/
void tiraVitorias(hash_table_equipa *eq, hash_node_equipa *equipa_aux, char * equipa, size_t h_eq){
    for (equipa_aux = eq->tb[h_eq]; equipa_aux; equipa_aux = equipa_aux->next){
        if( strcmp(equipa_aux->equipa1, equipa) == 0){ 
            equipa_aux->vitorias -= 1; 
            return;
        }
    }
}

/* funcao que verifica se a equipa existe e entao
caso exista aumenta o nr de vitorias dessa equipa*/
void acrescenta_vitorias(hash_table_equipa *eq, hash_node_equipa *equipa_aux,  char *equipa, size_t h_eq){
    for (equipa_aux = eq->tb[h_eq]; equipa_aux; equipa_aux = equipa_aux->next){
        if (strcmp(equipa_aux->equipa1, equipa) == 0){ 
            equipa_aux->vitorias += 1; 
            return;
        }
    }
}

/* esta funcao comeca por verificar qual das equipas do jogo 
tem maior pontucao e remove a vitoria pois caso a equipa 
cuja pontucao foi alterada tiver maior pontuacao nao pode ganhar duas vezes
no final verifica qual das equipas tem maior pontucao e aumenta a vitoria da maior */
void altera_score(hash_table * t, int * Nr_linha, hash_table_equipa * eq){ 
    int pontos_novo1, pontos_novo2; char jogo[MAX]; size_t h_eq1, h_eq2, h;
    hash_node_equipa * equipa_aux; hash_node * jogo_aux; scanf("%[^:\n]:%d:%d", jogo, &pontos_novo1, &pontos_novo2);
    
    if (verificaExiste_jogo(t, jogo) == 1){ printf("%d Jogo inexistente.\n", *Nr_linha); *Nr_linha += 1; return; }
    h = hash(jogo, t->capacidade); 
    for (jogo_aux = t->tb_jogo[h]; jogo_aux; jogo_aux = jogo_aux->proximoNo){
        if (strcmp(jogo_aux->informacoes_jogo->nome_jogo, jogo) == 0){
            h_eq1 = hash(jogo_aux->informacoes_jogo->equipa1, eq->capacidade_equipa);
            h_eq2 = hash(jogo_aux->informacoes_jogo->equipa2, eq->capacidade_equipa);
            if (jogo_aux->informacoes_jogo->pontos1 > jogo_aux->informacoes_jogo->pontos2){ 
                equipa_aux = eq->tb[h_eq1];
                tiraVitorias( eq, equipa_aux, jogo_aux->informacoes_jogo->equipa1, h_eq1);
            }
            if (jogo_aux->informacoes_jogo->pontos2 > jogo_aux->informacoes_jogo->pontos1){
                equipa_aux = eq->tb[h_eq2];
                tiraVitorias( eq, equipa_aux, jogo_aux->informacoes_jogo->equipa2, h_eq2);
            }
            jogo_aux->informacoes_jogo->pontos1 = pontos_novo1; jogo_aux->informacoes_jogo->pontos2 = pontos_novo2;
            if (pontos_novo1 > pontos_novo2){  
                equipa_aux = eq->tb[h_eq1];
                acrescenta_vitorias(eq, equipa_aux, jogo_aux->informacoes_jogo->equipa1, h_eq1);   
            }
            if (pontos_novo2 > pontos_novo1){ equipa_aux = eq->tb[h_eq2];
                acrescenta_vitorias(eq, equipa_aux, jogo_aux->informacoes_jogo->equipa2, h_eq2);
            }
        }
    } *Nr_linha += 1;
}

/* elimina a informacao contida 
no no da hash table dos jogos */
void remove_no(inicioFimJogos * lista, hash_node * jogo_aux){
    if (jogo_aux->informacoes_jogo->anterior == NULL){
        lista->inicio = jogo_aux->informacoes_jogo->proximo;
    }
    else{
        jogo_aux->informacoes_jogo->anterior->proximo = jogo_aux->informacoes_jogo->proximo;
    }
    if (jogo_aux->informacoes_jogo->proximo == NULL){
        lista->fim = jogo_aux->informacoes_jogo->anterior;
    }
    else{
        jogo_aux->informacoes_jogo->proximo->anterior = jogo_aux->informacoes_jogo->anterior;
    } 
    free(jogo_aux->informacoes_jogo->equipa1);
    free(jogo_aux->informacoes_jogo->equipa2);
}

/* remove o jogo da hash table elimina 
as informacoes do no e o no em si */
void removeDaHash(hash_node * temp, hash_node * ant, hash_table * t, char * nome_jogo, size_t h){
    if (strcmp(temp->informacoes_jogo->nome_jogo, nome_jogo ) == 0 ){
        t->tb_jogo[h] = temp->proximoNo; 
        free(temp); 
        return; 
    } 
    while (temp != NULL &&  strcmp(temp->informacoes_jogo->nome_jogo, nome_jogo )!= 0){ 
            ant = temp; 
            temp = temp->proximoNo; 
    } 
    if (temp == NULL){  
        return; 
    } 
    ant->proximoNo = temp->proximoNo; 
    free(temp->informacoes_jogo->nome_jogo);
    free(temp->informacoes_jogo); 
    free(temp);
}

/* esta funcao verifica qual das quipas do jogo tem 
maior pontucao e retira a vitoria se seguida elimina o 
a o no e remove da hash */
void remove_jogo_aux(hash_table * t, hash_table_equipa * eq, inicioFimJogos * lista, char * nome_jogo){
    hash_node_equipa * equipa_aux; hash_node_equipa * equipa_aux_2;  
    size_t h_eq1, h_eq2, h = hash(nome_jogo, t->capacidade);
    hash_node * jogo_aux; hash_node * temp = t->tb_jogo[h]; hash_node * ant = t->tb_jogo[h];
    
    for (jogo_aux = t->tb_jogo[h]; jogo_aux; jogo_aux = jogo_aux->proximoNo){
        if (strcmp(jogo_aux->informacoes_jogo->nome_jogo, nome_jogo) == 0){
            if (jogo_aux->informacoes_jogo->pontos1 > jogo_aux->informacoes_jogo->pontos2){  
                h_eq1 = hash(jogo_aux->informacoes_jogo->equipa1, eq->capacidade_equipa); 
                equipa_aux = eq->tb[h_eq1];
                tiraVitorias(eq, equipa_aux, jogo_aux->informacoes_jogo->equipa1, h_eq1);
                remove_no(lista, jogo_aux); removeDaHash(temp,  ant,  t,  nome_jogo,  h); 
                return;
            }
            if (jogo_aux->informacoes_jogo->pontos2 > jogo_aux->informacoes_jogo->pontos1){  
                h_eq2 = hash(jogo_aux->informacoes_jogo->equipa2, eq->capacidade_equipa);
                equipa_aux_2 = eq->tb[h_eq2];
                tiraVitorias(eq, equipa_aux_2, jogo_aux->informacoes_jogo->equipa2, h_eq2);
                remove_no( lista, jogo_aux); removeDaHash(temp,  ant,  t,  nome_jogo,  h); 
                return;
            }
            if (jogo_aux->informacoes_jogo->pontos2 == jogo_aux->informacoes_jogo->pontos1){  
                remove_no( lista, jogo_aux); removeDaHash(temp,  ant,  t,  nome_jogo,  h); 
                return;
            }
        }
    }
}
                
/* verifica se uma dado jogo existe 
e entao remove o jogo da hash table*/
void remove_jogo(hash_table * t, hash_table_equipa * eq, inicioFimJogos * lista,  int * Nr_linha){
    char nome_jogo[MAX]; 
    
    scanf("%[^:\n]", nome_jogo);

    if (verificaExiste_jogo(t, nome_jogo) == 1){
        printf("%d Jogo inexistente.\n", *Nr_linha); 
        *Nr_linha += 1; return;
    }
    *Nr_linha += 1;
        
    remove_jogo_aux(t, eq, lista, nome_jogo);
}      

/* printa todos os jogos existentes */
void lista_todos(inicioFimJogos * inicioFim, int * Nr_linha) {
    NoListaJogos * aux = inicioFim->inicio;

    if (aux == NULL){
        *Nr_linha += 1;
        return;
    }

    while (aux != NULL){
        printf("%d %s %s %s %d %d\n",*Nr_linha, 
        aux->nome_jogo,aux->equipa1,
        aux->equipa2,aux->pontos1,
        aux->pontos2); 
        aux = aux->proximo;
    }  
    *Nr_linha += 1; 
}


/* liberta a memoria 
armazenada na hash table do jogo */
void free_hash_table_jogo(hash_table * t) {
    hash_node * a;
    size_t i;
    for (i=0; i< t->capacidade; i++){
        while(t->tb_jogo[i]) {
            a = t->tb_jogo[i]->proximoNo;
            free(t->tb_jogo[i]);    /* free de todos os nos dessa tabela */
            
            t->tb_jogo[i] = a;
        }
    }  
    free(t->tb_jogo);
    free(t);  
}
        
/* liberta a memoria armazenada na
 lista duplamente ligada */            
void liberta_dupla(inicioFimJogos * lista){
    while (lista->inicio){
        NoListaJogos * temp = lista->inicio;
        if (lista->inicio){
            lista->inicio= lista->inicio->proximo;
            free(temp->nome_jogo);
            free(temp->equipa1);
            free(temp->equipa2);
            free(temp);
        }
    }
    free(lista);
}
















