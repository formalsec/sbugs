#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "commands.h"



void a(Hashtable_JOGOS HTj, Hashtable_EQUIPAS HTe) {
    char nome[STRINGSIZE], equipa1[STRINGSIZE], equipa2[STRINGSIZE];
    int score1=0, score2=0;
    int key=0;
    jogo j;
    linkPEquipa p;
    
    /*leitura o input*/
    getchar();
    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);

    if(score1>=0 && score2>=0) {
        /*verifica se o jogo ja existe na lista de jogos*/
        if (HashtableSearch_JOGOS(nome, HTj)) {
            /*ERRO*/
            if (NL==0) printf("%d Jogo existente.\n", 1);
            else printf("%ld Jogo existente.\n", NL);

        }else{
            /*verifica se a equipa ainda nao existe na lista de equipas*/
            if (!HashtableSearch_EQUIPAS(equipa1, HTe) || !HashtableSearch_EQUIPAS(equipa2, HTe)
                || !(HashtableSearch_EQUIPAS(equipa1, HTe)&&HashtableSearch_EQUIPAS(equipa2, HTe))) {
                /*ERRO*/
                if (NL==0) printf("%d Equipa inexistente.\n", 1);
                else printf("%ld Equipa inexistente.\n", NL);

            }else{

                /*copia do input para a variavel j (jogo)*/
                strcpy(j.nome, nome);
                strcpy(j.equipa1, equipa1);
                strcpy(j.equipa2, equipa2);
                j.score1=score1;
                j.score2=score2;
                
                /*insercao na lista de jogos e na hash table de ponteiros para os jogos*/
                HashtableInsert_JOGOS(HTj, insertNodeJogo(&listaDeJogos, j));

                /*verifica se a equipa vencedora foi a equipa1*/
                if (score1>score2) {
                    /*calculo da chave para a equipa1*/
                    key = hashU_EQUIPAS(equipa1, HTe);
                    /*incrementacao das vitorias da equipa1*/
                    for (p=HTe->adj[key]; p!=NULL; p=p->next)
                        if (!strcmp(p->e->e.nome, equipa1))
                            p->e->e.vitorias = p->e->e.vitorias + 1;
                }
                
                /*verifica se a equipa vencedora foi a equipa1*/
                if (score1<score2) {
                    /*calculo da chave para a equipa2*/
                    key = hashU_EQUIPAS(equipa2, HTe);
                    /*incrementacao das vitorias da equipa2*/
                    for (p=HTe->adj[key]; p!=NULL; p=p->next)
                        if (!strcmp(p->e->e.nome, equipa2))
                            p->e->e.vitorias = p->e->e.vitorias + 1;
                }
            }
            
        }
    }

    if(NL==0) NL=NL+2; else NL++;
}



void A(Hashtable_EQUIPAS HTe) {
    char nome[STRINGSIZE];
    equipa e;

    /*leitura o input*/
    getchar();
    scanf("%[^\n]", nome);

    /*verifica se a equipa ja existe na lista de equipas*/
    if (!HashtableSearch_EQUIPAS(nome, HTe)) {
        strcpy(e.nome, nome);
        e.vitorias = 0;
        /*insercao na lista de equipas e na hash table de ponteiros para os equipas*/
        HashtableInsert_EQUIPAS(HTe, insertNodeEquipa(&listaDeEquipas, e));

    }else{
        /*ERRO*/
        if (NL==0) printf("%d Equipa existente.\n", 1);
        else printf("%ld Equipa existente.\n", NL);

    }
    
    if(NL==0) NL=NL+2; else NL++;
}



void l() {
    linkJogo p;
    if (listaDeJogos==NULL) {
        if(NL==0) NL=NL+2; else NL++;
        return;
    } else {
        for (p = listaDeJogos; p != NULL; p = p->next) {
            printf("%ld %s %s %s %d %d\n", NL, p->j.nome, p->j.equipa1, p->j.equipa2, p->j.score1, p->j.score2);
        }
    }
    if(NL==0) NL=NL+2; else NL++;
}



void p(Hashtable_JOGOS HTj) {
    char nome[STRINGSIZE];
    int key=0;
    linkPJogo p;

    /*leitura o input*/
    getchar();
    scanf("%[^\n]", nome);

    /*verifica se a jogo ja existe na lista de jogos*/
    if (HashtableSearch_JOGOS(nome, HTj)) {

        /*calculo da chave para o nome do jogo*/
        key=hashU_JOGOS(nome, HTj);

        for (p=HTj->adj[key]; p!=NULL; p=p->next)
            if (!strcmp(p->j->j.nome, nome))
                printf("%ld %s %s %s %d %d\n", NL, p->j->j.nome, p->j->j.equipa1, p->j->j.equipa2, p->j->j.score1, p->j->j.score2);

    }else{
        /*ERRO*/
        if (NL==0) printf("%d Jogo inexistente.\n", 1);
        else printf("%ld Jogo inexistente.\n", NL);

    }

    if(NL==0) NL=NL+2; else NL++;
}



void P(Hashtable_EQUIPAS HTe) {
    char nome[STRINGSIZE];
    int key=0;
    linkPEquipa p;

    /*leitura o input*/
    getchar();
    scanf("%[^\n]", nome);

    /*verifica se a equipa ja existe na lista de equipas*/
    if (HashtableSearch_EQUIPAS(nome, HTe)) {

        /*calculo da chave para o nome da equipa*/
        key=hashU_EQUIPAS(nome, HTe);

        for (p=HTe->adj[key]; p!=NULL; p=p->next)
            if (!strcmp(p->e->e.nome, nome))
                printf("%ld %s %d\n", NL, p->e->e.nome, p->e->e.vitorias);
 
    }else{
        /*ERRO*/
        if (NL==0) printf("%d Equipa inexistente.\n", 1);
        else printf("%ld Equipa inexistente.\n", NL);
     
    }
    
    if(NL==0) NL=NL+2; else NL++;
}



void r(Hashtable_JOGOS HTj, Hashtable_EQUIPAS HTe) {
    char nome[STRINGSIZE];
    int key=0;
    linkPJogo pj;
    linkPEquipa pe;

    /*leitura o input*/
    getchar();
    scanf("%[^\n]", nome);

    /*verifica se a jogo ja existe na lista de jogos*/
    if (HashtableSearch_JOGOS(nome, HTj)) {
        
        /*calculo da chave para o nome do jogo*/
        key = hashU_JOGOS(nome, HTj);

        for (pj=HTj->adj[key]; pj!=NULL; pj=pj->next) {
            if (!strcmp(pj->j->j.nome, nome)) {

                /*verifica se a equipa vencedora foi a equipa1*/
                if (pj->j->j.score1>pj->j->j.score2) {
                    
                    /*calculo da chave para o nome da equipa1*/
                    key = hashU_EQUIPAS(pj->j->j.equipa1, HTe);
                    
                    /*decrementa as vitorias da equipa1*/
                    for (pe=HTe->adj[key]; pe!=NULL; pe=pe->next)
                        if (!strcmp(pe->e->e.nome, pj->j->j.equipa1))
                            pe->e->e.vitorias = pe->e->e.vitorias - 1;
                }

                /*verifica se a equipa vencedora foi a equipa2*/
                if (pj->j->j.score1<pj->j->j.score2) {
                    
                    /*calculo da chave para o nome da equipa2*/
                    key = hashU_EQUIPAS(pj->j->j.equipa2, HTe);
                    
                    /*decrementa as vitorias da equipa2*/
                    for (pe=HTe->adj[key]; pe!=NULL; pe=pe->next)
                        if (!strcmp(pe->e->e.nome, pj->j->j.equipa2))
                            pe->e->e.vitorias = pe->e->e.vitorias - 1;
                }
            }
        }

        /*remocao do jogo da lista de jogos e do ponteiro para os jogos 
          na hash table dos ponteiros para os jogos*/
        HashtableDelete_JOGOS (nome, &listaDeJogos, HTj);

    }else{
        /*ERRO*/
        if (NL==0) printf("%d Jogo inexistente.\n", 1);
        else printf("%ld Jogo inexistente.\n", NL);
    
    }

    if(NL==0) NL=NL+2; else NL++;
}



void s(Hashtable_JOGOS HTj, Hashtable_EQUIPAS HTe) {
    char nome[STRINGSIZE];
    int score1=0, score2=0;
    int key=0;
    linkPJogo pj;
    linkPEquipa pe;

    /*leitura o input*/
    getchar();
    scanf("%[^:\n]:%d:%d", nome, &score1, &score2);

    /*verifica se a jogo ja existe na lista de jogos*/
    if (HashtableSearch_JOGOS(nome, HTj)) {
        
        /*calculo da chave para o nome do jogo*/
        key=hashU_JOGOS(nome, HTj);

        for (pj=HTj->adj[key]; pj!=NULL; pj=pj->next) {

            if (!strcmp(pj->j->j.nome, nome)) {

                /*caso as equipas estejam empatadas*/
                if (pj->j->j.score1 == pj->j->j.score2) {
                    /*caso a equipa1 fique a ganhar a equipa2*/
                    if (score1 > score2) {
                        /*incrementa as vitorias da equipa1*/
                        key = hashU_EQUIPAS(pj->j->j.equipa1, HTe);
                        for (pe=HTe->adj[key]; pe!=NULL; pe=pe->next)
                            if (!strcmp(pe->e->e.nome, pj->j->j.equipa1))
                                pe->e->e.vitorias = pe->e->e.vitorias + 1;
                    }
                    /*caso a equipa2 fique a ganhar a equipa1*/
                    if (score1 < score2) {
                        /*incrementa as vitorias da equipa2*/
                        key = hashU_EQUIPAS(pj->j->j.equipa2, HTe);
                        for (pe=HTe->adj[key]; pe!=NULL; pe=pe->next)
                            if (!strcmp(pe->e->e.nome, pj->j->j.equipa2))
                                pe->e->e.vitorias = pe->e->e.vitorias + 1;
                    }
                    /*ataualizacao da score de cada equipa*/
                    pj->j->j.score1 = score1;
                    pj->j->j.score2 = score2;
                }

                /*caso a equipa1 esteja a ganhar a equipa2*/
                if (pj->j->j.score1 > pj->j->j.score2) {
                    /*caso a equipa2 fique empatada com equipa1*/
                    if (score1 == score2) {
                        /*decrementa as vitorias da equipa1*/
                        key = hashU_EQUIPAS(pj->j->j.equipa1, HTe);
                        for (pe=HTe->adj[key]; pe!=NULL; pe=pe->next)
                            if (!strcmp(pe->e->e.nome, pj->j->j.equipa1))
                                if (pe->e->e.vitorias >= 1)
                                    pe->e->e.vitorias = pe->e->e.vitorias - 1;
                    }
                    /*caso a equipa2 fique a ganhar a equipa1*/
                    if (score1 < score2) {
                        /*incrementa as vitorias da equipa2*/
                        key = hashU_EQUIPAS(pj->j->j.equipa2, HTe);
                        for (pe=HTe->adj[key]; pe!=NULL; pe=pe->next)
                            if (!strcmp(pe->e->e.nome, pj->j->j.equipa2))
                                pe->e->e.vitorias = pe->e->e.vitorias + 1;     
                        key = hashU_EQUIPAS(pj->j->j.equipa1, HTe);
                        /*decrementa as vitorias da equipa1*/
                        for (pe=HTe->adj[key]; pe!=NULL; pe=pe->next)
                            if (!strcmp(pe->e->e.nome, pj->j->j.equipa1))
                                if (pe->e->e.vitorias >= 1)
                                    pe->e->e.vitorias = pe->e->e.vitorias - 1;            
                    }
                    
                    /*ataualizacao da score de cada equipa*/
                    pj->j->j.score1 = score1;
                    pj->j->j.score2 = score2;
                }

                /*caso a equipa2 esteja a ganhar a equipa1*/
                if (pj->j->j.score1 < pj->j->j.score2) {
                    /*caso a equipa2 fique empatada com equipa1*/
                    if (score1 == score2) {
                        /*decrementa as vitorias da equipa2*/
                        key = hashU_EQUIPAS(pj->j->j.equipa2, HTe);
                        for (pe=HTe->adj[key]; pe!=NULL; pe=pe->next)
                            if (!strcmp(pe->e->e.nome, pj->j->j.equipa2))
                                if (pe->e->e.vitorias >= 1)
                                    pe->e->e.vitorias = pe->e->e.vitorias - 1;
                    }
                    /*caso a equipa1 fique a ganhar a equipa2*/
                    if (score1 > score2) {
                        /*incrementa as vitorias da equipa1*/
                        key = hashU_EQUIPAS(pj->j->j.equipa1, HTe);
                        for (pe=HTe->adj[key]; pe!=NULL; pe=pe->next)
                            if (!strcmp(pe->e->e.nome, pj->j->j.equipa1))
                                pe->e->e.vitorias = pe->e->e.vitorias + 1;
                        /*decrementa as vitorias da equipa2*/
                        key = hashU_EQUIPAS(pj->j->j.equipa2, HTe);
                        for (pe=HTe->adj[key]; pe!=NULL; pe=pe->next)
                            if (!strcmp(pe->e->e.nome, pj->j->j.equipa2))
                                if (pe->e->e.vitorias >= 1)
                                    pe->e->e.vitorias = pe->e->e.vitorias - 1;                   
                    }
                    /*ataualizacao da score de cada equipa*/
                    pj->j->j.score1 = score1;
                    pj->j->j.score2 = score2;
                }
            }
        }
                
        
    }else{
        /*ERRO*/
        if (NL==0) printf("%d Jogo inexistente.\n", 1);
        else printf("%ld Jogo inexistente.\n", NL);
        
    }
    
    if(NL==0) NL=NL+2; else NL++;
}



void g() {
    equipa array[1000];
    int i=0, j=0, best=0;
    linkEquipa p;

    if (listaDeEquipas!=NULL) {
        /*encontra o maior numero de vitorias*/
        for(p=listaDeEquipas;p!=NULL;p=p->next) {
            if (p->e.vitorias > best) best = p->e.vitorias;
        }

        for(p=listaDeEquipas;p!=NULL;p=p->next) {
            /*copia das equipas da lista para o array*/
            if (p->e.vitorias == best) {
                strcpy(array[j].nome, p->e.nome);
                array[j].vitorias = p->e.vitorias;
                j++;
            }
        }

        /*quick sort do array*/
        qsort(array, j, sizeof(equipa), cstring_cmp);
        
        /*print do output*/
        printf("%ld Melhores %d\n", NL, best);
        for(i=0; i<j; i++) {
            printf("%ld * %s\n", NL, array[i].nome);
        }
 
    }
    if(NL==0) NL=NL+2; else NL++;
}

int cstring_cmp(const void *a, const void *b) { 

    equipa *equipaA = (equipa *)a;
    equipa *equipaB = (equipa *)b;

    return strcmp(equipaA->nome, equipaB->nome);
} 

void x(Hashtable_JOGOS HTj, Hashtable_EQUIPAS HTe) {
    /*apaga hash table dos ponteiro para os jogos e a lista de jogos*/
    HashtableDeleteAll_JOGOS (HTj, &listaDeJogos);
    /*apaga hash table dos ponteiro para as equipas e a lista de equipas*/
    HashtableDeleteAll_EQUIPAS (HTe, &listaDeEquipas);
}
