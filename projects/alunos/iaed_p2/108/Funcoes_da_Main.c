#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Funcoes_da_Main.h"
#define String_Max 1024

/*Codigo das funcoes que estao no main */


char *__strdup (const char *nome){  
  size_t tam_string = strlen (nome) + 1;
  void *novo = can_fail_malloc (tam_string);
  if (novo == NULL)
    return NULL;
  return (char *) memcpy (novo, nome, tam_string);
}



int compara (const void * nome1, const void * nome2 ) {
    /*Obtenho  pointers para os nomes */
    const char *p_nome1 = *(const char**)nome1;
    const char *p_nome2 = *(const char**)nome2;
    return strcmp(p_nome1,p_nome2);
}





void a(int contador,int *max_jogos,int *max_equipas ,int *n_jogos, p_jogo **p_tab_j,p_equipa **p_tab_e,link *head,link *tail){
    char temp[String_Max];char equipa1[String_Max];char equipa2[String_Max];
    int score1;int score2;
    char *nome;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",temp,equipa1,equipa2,&score1,&score2);
    if(JogoProcura(max_jogos,temp,p_tab_j) != NULL){
        printf("%d Jogo existente.\n",contador);
    }
    else{
        p_equipa pont_e1; p_equipa pont_e2;
        pont_e1 = EquipaProcura(max_equipas,equipa1,p_tab_e);
        pont_e2 = EquipaProcura(max_equipas,equipa2,p_tab_e);
        if(pont_e1 == NULL || pont_e2 == NULL){
            printf("%d Equipa inexistente.\n",contador);
        }
        else{ /* Quando as equipas existem */
            /*Inicializa-se o jogo e as suas componentes */
            p_jogo jogo;
            jogo = can_fail_malloc(sizeof(struct jogo));
            nome = __strdup(temp);jogo->nome_j = nome;
            jogo->score1 = score1; jogo->score2 =score2;
            /* Adicona a vitoria a respetiva vencedora */
            if(score1 > score2)
                pont_e1->jogos_ganhos += 1; 
            else if(score1 < score2)
                pont_e2->jogos_ganhos += 1;
            jogo->equipa1 = pont_e1; jogo->equipa2 = pont_e2;
            JogoInsereLista(jogo,head,tail);
            JogoInsereHash(max_jogos,n_jogos,jogo,p_tab_j);
        }
    }
}


void p(int contador,int *max_jogos,p_jogo **p_tab_j){
    char nome[String_Max]; p_jogo jogo;
    scanf(" %[^:\n]",nome);
    jogo = JogoProcura(max_jogos,nome,p_tab_j);
    if (jogo == NULL){
       printf("%d Jogo inexistente.\n",contador);
    }
    else{
        char *nome_e1; char *nome_e2;
        nome_e1 = jogo->equipa1->nome;
        nome_e2 =  jogo->equipa2->nome;
        printf("%d %s %s %s %d %d\n",contador,jogo->nome_j,nome_e1,nome_e2,jogo->score1,jogo->score2);
    }
}


void s(int contador,int *max_jogos,p_jogo **p_tab_j){
    char nome[String_Max];int novo_score1;int novo_score2; p_jogo jogo;
    scanf(" %[^:\n]:%d:%d",nome,&novo_score1,&novo_score2);
    jogo = JogoProcura(max_jogos,nome,p_tab_j);
    if (jogo == NULL){
       printf("%d Jogo inexistente.\n",contador);
    }
    else{
        /*Adiciona-se uma vitoria a quem ganhou no novo score */
        if(novo_score1 > novo_score2)
            jogo->equipa1->jogos_ganhos += 1;
        if(novo_score2 > novo_score1)
            jogo->equipa2->jogos_ganhos += 1;
        /*Retira-se uma vitoria a quem tinha ganho anteriormente */
        if(jogo->score1 > jogo->score2)
            jogo->equipa1->jogos_ganhos -= 1;
        if(jogo->score2 > jogo->score1)
            jogo->equipa2->jogos_ganhos -= 1;
        
        jogo->score1 = novo_score1; jogo->score2 = novo_score2;
    }
}

void r(int contador,int *max_jogos,int *n_jogos,p_jogo **p_tab_j,link *head,link *tail){
    char nome[String_Max];p_jogo jogo;
    scanf(" %[^:\n]",nome);
    jogo = JogoProcura(max_jogos,nome,p_tab_j);
    if(jogo == NULL)
        printf("%d Jogo inexistente.\n",contador);
    else{
        /* Retira uma vitoria de quem tinha ganho */
        if(jogo->score1 > jogo->score2)
            jogo->equipa1->jogos_ganhos -= 1;
        else if(jogo->score1 < jogo->score2)
            jogo->equipa2->jogos_ganhos -= 1;
        JogoApagaHash(jogo,max_jogos,n_jogos,p_tab_j);
        JogoApagaLista(jogo,head,tail);
    }
}

void l(int contador,link head){
        link t;
        for(t = head; t != NULL; t = t->next){
            printf("%d %s %s %s %d %d\n",contador,t->jogo->nome_j,t->jogo->equipa1->nome,t->jogo->equipa2->nome,t->jogo->score1,t->jogo->score2);
        }
          
}


void g(int contador,int n_equipas,int max_equipas,p_equipa *tab_e){
    if (n_equipas > 0){ 
        int maior;int i;int j;int n_vencedores; const char **lista_vencedores;
        lista_vencedores = can_fail_malloc(n_equipas * sizeof(char*)); 
        /* Lista com tamanho do n_equipas para garantir que tem espaco suficiente para todos os vencedores */
        
        maior = 0; j = 0; n_vencedores = 0;
        for(i = 0;i < max_equipas;i++){ /*Obtenho o maior numero de vitorias */
            if(tab_e[i] != NULL && tab_e[i]->jogos_ganhos > maior )
                maior = tab_e[i]->jogos_ganhos;
        }
        for(i = 0;i < max_equipas;i++){ /*Guardo na lista quem tem o maior numero de vitorias */
            if(tab_e[i] != NULL && tab_e[i]->jogos_ganhos == maior){
                lista_vencedores[j] = tab_e[i]->nome;
                j += 1; n_vencedores += 1;
            }
        }
        qsort(lista_vencedores, n_vencedores, sizeof(char *), compara); /*Ordeno lexicograficamente */
        printf("%d Melhores %d\n",contador,maior);
        for(i = 0; i < n_vencedores;i++){
            printf("%d * %s\n",contador,lista_vencedores[i]);
        }
        free(lista_vencedores);
    }
}


void A(int contador,int *max_equipas,int *n_equipas,p_equipa **p_tab_e){
    char temp[String_Max];char *nome;
    scanf(" %[^:\n]",temp);
    if(EquipaProcura(max_equipas,temp,p_tab_e) != NULL){
        printf("%d Equipa existente.\n",contador);
    }
    else{
        /*Inicializa a equipa e as suas componentes*/
        p_equipa equipa;
        nome = __strdup(temp);
        equipa = can_fail_malloc(sizeof(struct equipa));
        equipa->jogos_ganhos = 0;
        equipa ->nome = nome;
        EquipaInsere(max_equipas,n_equipas,equipa,p_tab_e);
    }
}


void P(int contador,int *max_equipas, p_equipa **p_tab_e){
    char nome[String_Max];p_equipa equipa;
    scanf(" %[^:\n]",nome);
    equipa = EquipaProcura(max_equipas,nome,p_tab_e);
    if(equipa == NULL){
        printf("%d Equipa inexistente.\n",contador);
    }
    else{
        printf("%d %s %d\n",contador,equipa->nome,equipa->jogos_ganhos);
    }
}


void liberta(int max_equipas,p_equipa *tab_e,p_jogo *tab_j,link head){
    link t;link aux;int i;
        for(i = 0;i <max_equipas;i++){  /*Liberta as equipas */
                if(tab_e[i] != NULL){
                    free(tab_e[i]->nome);
                    free(tab_e[i]);
                }
            }
            free(tab_e);free(tab_j);
            t = head;
            while(t != NULL){ /*Liberta os jogos */
                    aux = t-> next;
                    free(t->jogo->nome_j);
                    free(t->jogo);
                    free(t);
                    t = aux;
            }
}
