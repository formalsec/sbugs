#include "comandos.h"

int le_comandos(link_equi *equipas,link_jogo * jogos_hashtable,
Lista_jogos jogos_ls){
    int NL=1;
    
    while (1) {
        char command;
        command = getchar();
        switch (command) {
            case 'a':
                a_executa(NL, jogos_hashtable, jogos_ls,equipas);
                NL++;
                break;
            case 'l':
                l_executa(NL, jogos_ls);
                NL++;
                break;
            case 'p':
                p_executa(NL, jogos_hashtable);
                NL++;
                break;
                /* Apaga um jogo dado um nome. */
            case 'r':
                r_executa(NL, jogos_hashtable, equipas);
                NL++;
                break;
                /* altera o score dum jogo */
            case 's':
                s_executa(NL,jogos_hashtable,equipas);
                NL++;
                break;
                /* Chama a funcao responsavel por adicionar equipa */
            case 'A':
                A_executa(NL,equipas,TAM_HASHTABLE_EQUI);
                NL++;
                break;
                /* Procura uma equipa dado um nome */
            case 'P':
                P_executa(NL,equipas,TAM_HASHTABLE_EQUI);
                NL++;
                break;
                /* Encontra as equipas que ganharam mais jogos
                 lista por ordem lexicografica (do nome da equipa). */
            case 'g':
                g_executa(NL,equipas);
                NL++;
                break;
                
            case 'x':
            /* Termina o programa com sucesso (STDLIB) */
                return EXIT;
        }
     
    }
}
/* Adiciona um jogo  a hashtable e a lista de jogos */
void a_executa(int NL,link_jogo * jogos_hashtable,Lista_jogos jogos_ls,link_equi* equipas){
    char nome[MAX_PAL],e1[MAX_PAL],e2[MAX_PAL];
    int s1,s2;
    Jogo jogo = NULL;
    Equipa campea,equipa1,equipa2;
    
    
    scanf(" %[^:\n]",nome);
    scanf(":%[^:\n]",e1);
    scanf(":%[^:\n]",e2);
    scanf(":%d:%d",&s1,&s2);

    if( procura_tab_jogo(nome, jogos_hashtable) != NULL){
        printf("%d Jogo existente.\n",NL);
        return;
    }
    
    equipa1 = procura_tab_equi(e1, equipas, TAM_HASHTABLE_EQUI);
    equipa2 = procura_tab_equi(e2, equipas, TAM_HASHTABLE_EQUI);
    
    if(equipa1 == NULL || equipa2 == NULL){
        printf("%d Equipa inexistente.\n",NL);
        return;
    }
    
    jogo = novo_jogo(nome, e1, e2, s1, s2);
    insere_tab_jogo(jogo, jogos_hashtable);
    adiciona_jogo_ls(jogo, jogos_ls);
    
    if(s1>s2){
        campea = procura_tab_equi(e1, equipas, TAM_HASHTABLE_EQUI);
        campea->vitorias++;
    }
    
    if(s2>s1){
        campea = procura_tab_equi(e2, equipas, TAM_HASHTABLE_EQUI);
        campea->vitorias++;
    }
}

/* lista todos os jogos por ordem lexiocgrafica */
void l_executa(int NL,Lista_jogos jogos_ls){
    link_jogo_ls temp;
    temp = jogos_ls->cabeca;
    while(temp != NULL){
        if(temp->jogo && strcmp("APAGADO", temp->jogo->nome) != 0){
            printf("%d %s %s %s %d %d\n",NL, temp->jogo->nome,temp->jogo->equipa1,temp->jogo->equipa2,temp->jogo->score_e1,temp->jogo->score_e2);
        }
        temp = temp->next;
    }
}

/* procura um jogo  */
void p_executa(int NL,link_jogo * jogos_hashtable){
    char buffer[MAX_PAL];
    Jogo jogo = NULL;
    scanf(" %[^:\n]",buffer);
    
    jogo = procura_tab_jogo(buffer, jogos_hashtable);
    if( jogo == NULL){
        printf("%d Jogo inexistente.\n",NL);
        return;
     }
    
    /* NL nome equipa1 equipa2 score1 score2 */
    printf("%d %s %s %s %d %d\n",NL,jogo->nome,jogo->equipa1,jogo->equipa2,jogo->score_e1,jogo->score_e2);
}


/* apaga um jogo */
void r_executa(int NL, link_jogo * jogos_hashtable,link_equi* equipas){
    char buffer[MAX_PAL];
    Jogo jogo;
    Equipa equipa1,equipa2;
    scanf(" %[^:\n]",buffer);
    
    jogo = procura_tab_jogo(buffer, jogos_hashtable);
    
    if(jogo == NULL){
        printf("%d Jogo inexistente.\n",NL);
        return;
    }
    
    equipa1 = procura_tab_equi(jogo->equipa1, equipas,TAM_HASHTABLE_EQUI);
    equipa2 = procura_tab_equi(jogo->equipa2, equipas,TAM_HASHTABLE_EQUI);
        
    if(jogo->score_e1>jogo->score_e2)
        equipa1->vitorias --;
        
    if(jogo->score_e2>jogo->score_e1)
        equipa2->vitorias --;
    apaga_tab_jogo(jogos_hashtable, jogo->nome);
}

/* Altera o score de um jogo dado o nome. */
void s_executa(int NL, link_jogo * jogos_hashtable,link_equi* equipas){
    char buffer[MAX_PAL];
    int s1,s2;
    Jogo jogo;
    Equipa equipa1,equipa2;
    scanf(" %[^:\n]:%d:%d",buffer,&s1,&s2);
    jogo = procura_tab_jogo(buffer, jogos_hashtable);
    
    if(jogo == NULL){
        printf("%d Jogo inexistente.\n",NL);
        return;
    }
    equipa1 = procura_tab_equi(jogo->equipa1, equipas,TAM_HASHTABLE_EQUI);
    equipa2 = procura_tab_equi(jogo->equipa2, equipas,TAM_HASHTABLE_EQUI);
        
    if(jogo->score_e1>jogo->score_e2)
        equipa1->vitorias --;
        
    if(jogo->score_e2>jogo->score_e1)
        equipa2->vitorias --;
        
    jogo->score_e1 = s1;
    jogo->score_e2 = s2;
        
    if(jogo->score_e1>jogo->score_e2)
        equipa1->vitorias ++;
        
    if(jogo->score_e2>jogo->score_e1)
        equipa2->vitorias ++;
}


/* Adiciona uma nova equipa. */
void A_executa(int NL,link_equi *equipas,int tamanho){
    char nome[MAX_PAL];
    Equipa equipa = NULL;
    
    scanf(" %[^:\n]",nome);
    
    if( procura_tab_equi(nome,equipas,tamanho) != NULL){
        printf("%d Equipa existente.\n",NL);
        return;
    }
    
    equipa = nova_Equipa(nome);
    insere_tab_equi(equipa,equipas,tamanho);
}


/* Procura uma equipa dado um nome.*/
void P_executa(int NL,link_equi *equipas, int tamanho){
    char buffer[MAX_PAL];
    Equipa equipa = NULL;
    scanf(" %[^:\n]",buffer);
   
    equipa = procura_tab_equi(buffer,equipas,tamanho);
    if( equipa == NULL){
        printf("%d Equipa inexistente.\n",NL);
        return;
    }
    printf("%d %s %d\n",NL,equipa->nome,equipa->vitorias);
}


void g_executa(int NL,link_equi *equipas){
    int i,e = 0,max_vitorias = 0, n_equipas = 0,estado = N_EXISTE;
    link_equi link_temp = NULL;
    Equipa equi_temp = NULL;
    char* nomes_equipas[MAX_EQUIPAS_VITORIAS];
    
    /* percorre a tabela de forma a encotrar
     o maior numero de vitorias */
    for(i=0; i<TAM_HASHTABLE_EQUI; i++){
        if(equipas[i] != NULL){
            link_temp = equipas[i];
            while(link_temp != NULL){
                equi_temp = link_temp->equipa;
                estado = EXISTE;
                if(equi_temp->vitorias > max_vitorias)
                    max_vitorias = equi_temp -> vitorias;
                link_temp = link_temp->next;
            }
        }
    }
    
    /* percorre de novo a tabela de forma a adiconar a um vetor o nome das equipas que tem o numero max de vitorias */
    if(estado == EXISTE){
        for(i=0; i<TAM_HASHTABLE_EQUI; i++){
            if(equipas[i] != NULL){
                link_temp = equipas[i];
                while(link_temp != NULL){
                    equi_temp = link_temp->equipa;
                    if(equi_temp->vitorias == max_vitorias){
                        nomes_equipas[e] = equi_temp->nome;
                        e++;
                    }
                    link_temp = link_temp->next;
                }
            }
        }
        n_equipas = e;
        
        /* ordena o nome das equipas com num max de vitorias por ordem lexicografica */
        qsort (nomes_equipas, n_equipas, sizeof(char*), compara_equipas);
        printf("%d Melhores %d\n",NL,max_vitorias);
        
        for(i=0; i< n_equipas; i++){
            if(nomes_equipas[i] != NULL)
                printf("%d * %s\n",NL,nomes_equipas[i]);
        }
    }
}









