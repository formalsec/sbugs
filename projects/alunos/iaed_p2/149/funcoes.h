#ifndef FUNCOES_H
#define FUNCOES_H
#include "hash_tables.h"

/*Adiciona uma nova equipa recebendo o nome*/
void executa_A(hash_table_equipa * hash_table_equipa_p,lista* Equipa_lista,int NL){
        char buffer[TAMANHO_DE_STRING];
        str_node * Test; 
        scanf(" %[^:\n]",buffer); /*Guardar no buffer a palavra*/
        Test = hash_table_lookup_equipa(hash_table_equipa_p,buffer);
        if (Test == NULL){
            struct str_node* Temp = NULL; /*Onde vamos guardar a proxima equipa*/
            Temp = (struct str_node*)malloc(sizeof(struct str_node)); /*pointer para esta nova equipa (guardar espaco para ela)*/
            Temp->equipa.nome = (char*)malloc(sizeof(char)*(strlen(buffer)+1)); /*Arranjar o espaco mas so usando a memoria necessaria*/
            strcpy(Temp->equipa.nome,buffer);/*por a palavra no temp*/
            if (Equipa_lista->head == NULL){ /*Se for o primeiro termo*/
                Temp->previous = NULL; /*nao ha previous*/
                Equipa_lista->last = Temp;} /*ultimo da lista e este*/
            else
            {   Equipa_lista->head->next = Temp; /*o next do ultimo e o Temp*/
                Temp ->previous = Equipa_lista->head;}/*ultimo e o head*/
            Temp->next= NULL;/*proximo por agora e NULL*/
            Temp->equipa.score = 0;
            Equipa_lista->head = Temp; /*head e agora o temporario*/
            hash_table_equipa_insert(hash_table_equipa_p,Temp,Equipa_lista);
            }
        else{
            printf("%d Equipa existente.\n",NL);}
}

/*Procura uma equipa atraves do nome e da print da equipa e do score*/
void executa_P(hash_table_equipa * hash_table_equipa_p,int NL){
        char buffer[TAMANHO_DE_STRING];
        str_node * Test; 
        scanf(" %[^:\n]",buffer); /*Guardar no buffer a palavra*/
        Test = hash_table_lookup_equipa(hash_table_equipa_p,buffer); /*usar a funcao lookup e receber o pointer se existir*/
        if (Test != NULL){
            printf("%d %s %d\n",NL,Test->equipa.nome,Test->equipa.score);
        }
        else
        {
            printf("%d Equipa inexistente.\n",NL);}
}
/*Adiciona um novo jogo dando um nome, nome de equipas e o score do jogo*/
void executa_a(hash_table_equipa * hash_table_equipa_p,hash_table_jogo * hash_table_jogo_p,lista2 *Jogos_lista_pointer,int NL){
        char buffer_nome[TAMANHO_DE_STRING],buffer_equipa1[TAMANHO_DE_STRING],buffer_equipa2[TAMANHO_DE_STRING];
        int score1,score2;
        str_node_jogo * Test1;
        str_node *point1, *point2;
        scanf(" %[^:]:%[^:]:%[^:]:%d:%d",buffer_nome,buffer_equipa1,buffer_equipa2,&score1,&score2);
        Test1 =hash_table_jogo_lookup(hash_table_jogo_p,buffer_nome); /*Ver se as equipas existem e se ja ha um jogo com este nome*/
        point1 = hash_table_lookup_equipa(hash_table_equipa_p,buffer_equipa1);
        point2 = hash_table_lookup_equipa(hash_table_equipa_p,buffer_equipa2);
        if (Test1 == NULL){
            if (point1 != NULL && point2 != NULL){
                struct str_node_jogo *Temp = NULL; /*Onde vamos guardar o proximo jogo*/
                Temp = (struct str_node_jogo*)malloc(sizeof(struct str_node_jogo)); /*pointer para este novo jogo (guardar espaco para ela)*/
                Temp->jogo.nome = (char*)malloc(sizeof(char)*(strlen(buffer_nome)+1)); /*Arranjar o espaco mas so usando a memoria necessaria*/
                strcpy(Temp->jogo.nome,buffer_nome);/*por a palavra no temp*/
                Temp->jogo.equipa1 = point1; /*Por os pointers de cada equipa na estrutura jogo*/
                Temp->jogo.equipa2 = point2;
                /*aumentar o score total das equipas*/
                if (score1 -score2 < 0)
                {
                    point2->equipa.score = point2->equipa.score+1;
                }
                else if (score1 - score2 > 0)
                {
                    point1->equipa.score = point1->equipa.score+1;
                }
                Temp->jogo.score[0] =score1; /*guardar o score no jogo*/
                Temp->jogo.score[1] = score2;
                if (Jogos_lista_pointer->last == NULL){ /*se for o primeiro, nao ha previous e e o ultimo*/
                    Temp->previous = NULL;
                    Jogos_lista_pointer->last = Temp;
                    }
                else
                {
                    Jogos_lista_pointer->head->next = Temp; /*no ultimo, o proximo e o Temp*/
                    Temp->previous = Jogos_lista_pointer->head; /*o previous era a head*/
                }
                Temp->next= NULL;/*proximo por agora e NULL*/
                Jogos_lista_pointer->head = Temp; /*head e agora o temporario*/
                hash_table_jogo_insert(hash_table_jogo_p,Temp,Jogos_lista_pointer);
            }
            else{
                printf("%d Equipa inexistente.\n",NL);
            }
        
        }
        else{
            printf("%d Jogo existente.\n",NL);}
        
}
/*Procura uma equipa atraves do nome*/
void executa_p(hash_table_jogo * hash_table_jogo_p,int NL){
        char buffer[TAMANHO_DE_STRING];
        str_node_jogo * Test; 
        scanf(" %[^:\n]",buffer); /*Guardar no buffer a palavra*/
        Test = hash_table_jogo_lookup(hash_table_jogo_p,buffer);/*Procurar a equipa e recebe o pointer se existir senao NULL*/
        if (Test != NULL){
            printf("%d %s %s %s %d %d\n",NL,Test->jogo.nome,Test->jogo.equipa1->equipa.nome,Test->jogo.equipa2->equipa.nome,Test->jogo.score[0],Test->jogo.score[1]);
            }
        else
        {
            printf("%d Jogo inexistente.\n",NL);
        }
}
/*Lista todos os jogos pela ordem em que foi introduzidos*/
void executa_l(lista2* Jogos_lista_pointer,int NL){
        str_node_jogo* Temp;
        Temp = Jogos_lista_pointer->last;/*Comecar a dar print pelo primeiro membro da linked list*/ 
        while (Temp != NULL){
            printf("%d %s %s %s %d %d\n",NL,Temp->jogo.nome,Temp->jogo.equipa1->equipa.nome,Temp->jogo.equipa2->equipa.nome,Temp->jogo.score[0],Temp->jogo.score[1]);
            Temp = Temp->next;}/*Passar para o proximo */
}
/*Altera a pontuacao de um jogo*/
void executa_s(hash_table_jogo * hash_table_jogo_p,int NL){
        char buffer[TAMANHO_DE_STRING];
        int novo_scor1,novo_scor2;
        str_node_jogo * Temp;
        scanf(" %[^:]:%d:%d",buffer,&novo_scor1,&novo_scor2);
        Temp = hash_table_jogo_lookup(hash_table_jogo_p,buffer); /*Verifica se o jogo existe*/
        if (Temp != NULL){
                if (Temp->jogo.score[0] - Temp->jogo.score[1] < 0){ /*Verifica qual deles temos que subtrair*/
                    Temp->jogo.equipa2->equipa.score = Temp->jogo.equipa2->equipa.score -1;
                }
                else if (Temp->jogo.score[0] - Temp->jogo.score[1] > 0){
                    Temp->jogo.equipa1->equipa.score = Temp->jogo.equipa1->equipa.score-1;
                }
                if (novo_scor1 -novo_scor2 < 0){ /*Verifica qual deles somar a um pontuacao*/
                    Temp->jogo.equipa2->equipa.score = Temp->jogo.equipa2->equipa.score+1;
                }
                else if (novo_scor1 - novo_scor2 > 0){
                    Temp->jogo.equipa1->equipa.score = Temp->jogo.equipa1->equipa.score+1;}
            Temp->jogo.score[0] = novo_scor1; /*Atualizar as pontuacoes*/
            Temp->jogo.score[1] = novo_scor2;}
        else
        {
            printf("%d Jogo inexistente.\n",NL);
        }
}
/*Remove um jogo atraves do nome*/
void executa_r(hash_table_jogo * hash_table_jogo_p,lista2 *Jogos_lista,int NL){
        char buffer[TAMANHO_DE_STRING];
        int headd = 0,lastt = 0;
        str_node_jogo * Temp;
        str_node_jogo *prev = NULL;
        str_node_jogo *other =NULL;
        scanf(" %[^:\n]",buffer);
        Temp = hash_table_jogo_lookup(hash_table_jogo_p,buffer); /*Verifica se existe jogo com este nome*/
        if (Temp != NULL){
            int index;
            index = hash(buffer,hash_table_jogo_p->M);
            other = hash_table_jogo_p->entries[index];
            while (strcmp(other->jogo.nome,buffer)!= 0) /*Verificar se e o primeiro neste local da hash table*/
            {
                prev = other;
                other= other->jogo.next;
            }
            if (prev == NULL){ /*Se for o primeiro*/
                hash_table_jogo_p->entries[index] = Temp->jogo.next;}
            else{ /*Se nao for o primeiro*/ 
                prev->jogo.next= Temp->jogo.next;}
                
            if (Temp->next != NULL){ /*Ver em que lugar esta na linked list*/
                Temp->next->previous = Temp->previous;
                lastt = 1;
            }
            if (Temp->previous != NULL){
                Temp->previous->next = Temp->next;
                headd= 1;}

            if (lastt == 0 && headd ==0){ /*Alterar de forma boa caso seja o unico ou o primeiro/ultimo*/
                Jogos_lista->head = NULL,Jogos_lista->last = NULL;
            }
            else if (headd == 0){
                Jogos_lista->last = Temp->next;
            }
            else if (lastt == 0){
                Jogos_lista->head = Temp->previous;
            }
            if (Temp->jogo.score[0] - Temp->jogo.score[1] < 0){ /*Tirar o score do jogo a equipa correspondente*/
                Temp->jogo.equipa2->equipa.score = Temp->jogo.equipa2->equipa.score -1;
            }
            else if (Temp->jogo.score[0] - Temp->jogo.score[1] > 0){
                Temp->jogo.equipa1->equipa.score = Temp->jogo.equipa1->equipa.score-1;
            }
            free(Temp->jogo.nome); /*free do alloc */
            free(Temp);}
        else
        {
            printf("%d Jogo inexistente.\n",NL);
        }
}
/*Comparar os nomes de duas equipas*/
int comparador(const void *a,const void *b){
        equipa *equipaA = (equipa *)a;
        equipa *equipaB = (equipa *)b;
    return strcmp(equipaA->nome,equipaB->nome);
}
/*Encontra as equipas que venceram mais jogos e organizam de forma alfabetica*/
void executa_g(lista* Equipa_lista,int NL){
        str_node* Temp;
        int maior = 0;
        int i = 0,e;
        struct equipa vencedores[TAMANHO_DE_STRING]; /*array grande para guardar os vencedores*/ 
        Temp = Equipa_lista->last;
        while (Temp != NULL){
            if (Temp->equipa.score > maior){ /*Encontrar o maior score, ou seja, o score da equipa vencedora*/
                memset(vencedores,0,i); /*Por a equipa a zeros se o novo for maior*/
                i = 1;
                maior = Temp->equipa.score;
                vencedores[0] = Temp->equipa;
            }
            else if (Temp->equipa.score == maior){ /*Adiciona se tiver o mesmo score que o maior*/
                vencedores[i] = Temp->equipa;
                i = i +1;
            }
            Temp = Temp->next;
        }
        if (i != 0){
            printf("%d Melhores %d\n",NL,maior); 
            qsort(vencedores,i,sizeof(vencedores[0]),comparador); /*Ordenar de forma alfabetica com o qsort*/
            for (e=0; e<i; e++){ /*printf a todos os vencedores*/
                printf("%d * %s\n",NL,vencedores[e].nome);
            }
        }
}
/*Funcao para libertar o que foi guardado pelo alloc*/
void liberta_espacos(lista *Equipa_lista,lista2 *Jogos_lista,hash_table_equipa * hash_table_equipa_p,hash_table_jogo * hash_table_jogo_p){
    str_node *current = Equipa_lista->last;
    str_node* tmp;
    str_node_jogo *current2 = Jogos_lista->last;
    str_node_jogo *tmp2;
    while (current != NULL){ /*Limpa as equipas e o nome das linked list*/
        tmp = current;
        current = current->next;
        free(tmp->equipa.nome);
        free(tmp);
    }
    while (current2 != NULL ){ /*Limpa os jogos e o seu nome das linked list*/
        tmp2 = current2;
        current2 = current2->next;
        free(tmp2->jogo.nome);
        free(tmp2);
    }
    free(hash_table_equipa_p->entries); /*Limpa as entries da hash da equipa*/
    free(hash_table_equipa_p); /*Limpa a hash de equipa*/
    free(hash_table_jogo_p->entries); /*Limpa as entries da hash do jogo*/
    free(hash_table_jogo_p); /*Limpa a hash dos jogos*/
}

#endif