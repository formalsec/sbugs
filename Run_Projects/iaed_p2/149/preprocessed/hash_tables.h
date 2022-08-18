#ifndef HASH_TABLES_H
#define HASH_TABLES_H
#include "Estruturas.h"
/*Calcula o indice das tables*/
int hash(char *v,int m){
    int h = 0, a= 127; 
    for (; *v != '\0';v++)
        h = (a*h + *v) % m;
    return h;
}

/*Inicia a hash table com tudo a NULL*/
hash_table_equipa*init_hash_Equipa(int M){ 
    int i;
    hash_table_equipa *hash_table_equipa_p= malloc(sizeof(hash_table_equipa)); /*Espaco para a hash_Table*/
    hash_table_equipa_p->entries=malloc(sizeof(str_node*)* M); 
    for (i = 0; i< M; i++) /*Por tudo a NULL*/
        hash_table_equipa_p->entries[i] = NULL;
    hash_table_equipa_p->M = M;
    hash_table_equipa_p->N = 0;
    return hash_table_equipa_p;
}

/*inicia a table dos jogos com NULL*/
hash_table_jogo*init_hash_jogos(int M){
        int i;
        hash_table_jogo * hash_table_jogo_p = malloc(sizeof(hash_table_jogo)); /*Espacos para a table*/
        hash_table_jogo_p->entries = malloc(sizeof(str_node_jogo*)*M);
        for (i= 0; i< M;i++){ /*Por tudo para NULL*/
            hash_table_jogo_p->entries[i] = NULL;
        }
        hash_table_jogo_p->M = M;
        hash_table_jogo_p->N = 0;
        return hash_table_jogo_p;
}
/*Funcao expand aumenta a table para dobro*/
void expand_equipa(hash_table_equipa * hash_table_equipa_p,lista* Equipa_lista);

/*Insere na equipa table o str_node na table, e se tiver mais de metade aumenta a table*/
void hash_table_equipa_insert(hash_table_equipa * hash_table_equipa_p,str_node *e,lista* Equipa_lista){
    int index = hash(e->equipa.nome,hash_table_equipa_p->M);
    e->equipa.next =hash_table_equipa_p->entries[index]; 
    hash_table_equipa_p->entries[index] = e;/*guardar na table*/
    if (hash_table_equipa_p->N++ > hash_table_equipa_p->M/2){ /*Se for preciso aumentar para o dobro*/
        expand_equipa(hash_table_equipa_p,Equipa_lista);
    }
}
/*expand a tabela para o dobro*/
void expand_equipa(hash_table_equipa * hash_table_equipa_p,lista* Equipa_lista){
    str_node *Temp;
    int M;
    hash_table_equipa * hash_table_equipa_temp;
    Temp = Equipa_lista->last; /*Temp e onde comecar*/
    M =hash_table_equipa_p->M*2;
    free(hash_table_equipa_p->entries);
    hash_table_equipa_temp= init_hash_Equipa(M);
    while (Temp != NULL){ /*Guardar na nova table as equipas e tirar o next*/
        Temp->equipa.next = NULL;
        hash_table_equipa_insert(hash_table_equipa_temp,Temp,Equipa_lista);
        Temp = Temp->next;
    }
    hash_table_equipa_p->entries=hash_table_equipa_temp->entries; /*Trocar as entries para as das novas tables*/
    hash_table_equipa_p->M = M;
    free(hash_table_equipa_temp);
}
/*Expand a para o dobro*/
void expand_jogo(hash_table_jogo * hash_table_jogo_p,lista2* Jogos_lista);

void test(str_node_jogo * Temp){
    while(Temp != NULL){
        printf("%s nome do jogo --\n",Temp->jogo.nome);
        Temp = Temp->jogo.next;
    }
}

/*mete na table o novo e expande se for preciso*/
void hash_table_jogo_insert(hash_table_jogo * hash_table_jogo_p,str_node_jogo *e,lista2* Jogos_lista){
        int index = hash(e->jogo.nome,hash_table_jogo_p->M);
        e->jogo.next = hash_table_jogo_p->entries[index]; /*Guardar o novo jogo na hash table*/
        hash_table_jogo_p->entries[index] = e;
        
        if (hash_table_jogo_p->N++ >hash_table_jogo_p->M/2){/*Se for preciso duplicar a table*/
            expand_jogo(hash_table_jogo_p,Jogos_lista);
        }
}
/*Aumentar para o dobro*/
void expand_jogo(hash_table_jogo * hash_table_jogo_p,lista2* Jogos_lista){
    str_node_jogo *Temp;
    int M;
    hash_table_jogo * hash_table_jogo_t;
    Temp = Jogos_lista->last; /*Onde comecar para guardar os jogos ja criados*/
    M = hash_table_jogo_p->M*2;
    free(hash_table_jogo_p->entries); /*free as entries da tabela anterior*/
    hash_table_jogo_t = init_hash_jogos(M);
    while (Temp != NULL){
        Temp->jogo.next = NULL;/*Trocar o next para NULL*/
        hash_table_jogo_insert(hash_table_jogo_t,Temp,Jogos_lista);
        Temp = Temp->next;
    }
    hash_table_jogo_p->entries = hash_table_jogo_t->entries;/*Trocar o pointer das entries*/
    hash_table_jogo_p->M=M;
    free(hash_table_jogo_t);/*free a temporaria*/
}

/*encontrar uma equipa a partir do nome*/
str_node *hash_table_lookup_equipa(hash_table_equipa * hash_table_equipa_p,char *nome){
        int index = hash(nome,hash_table_equipa_p->M);  
        str_node *tmp;
        tmp= hash_table_equipa_p->entries[index]; /*tmp e a entry na table com o index correspondente a este*/
        while (tmp != NULL && strcmp(tmp->equipa.nome,nome)!= 0){
            tmp = tmp->equipa.next; /*Percorrer a lista ate encontrar um NULL ou igual ao nome*/
        }
        return tmp;
}

/*encontrar um jogo a partir do nome*/
str_node_jogo *hash_table_jogo_lookup(hash_table_jogo * hash_table_jogo_p,char *nome){
        int index =hash(nome,hash_table_jogo_p->M);
        str_node_jogo*tmp;
        tmp = hash_table_jogo_p->entries[index];/*tmp e a entry na table com o index correspondente a este*/
        while (tmp != NULL && strcmp(tmp->jogo.nome,nome)!= 0){
            tmp = tmp->jogo.next; /*Percorrer a lista ate encontrar um NULL ou igual ao nome*/
        }
        return tmp;
}
#endif