#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "estruturas_equipa.h"

/*
  init_equipas: () -> Equipas
  Retorna um ponteiro para uma estrutura Equipas ja inicializada
*/
Equipas init_equipas(){
    return can_fail_calloc(1,sizeof(struct equipas));
}

/*
  insere_equipa: (Equipas, Equipa) -> ()
  Insere uma equipa na estrutura Equipas
*/
void insere_equipa(Equipas equipas, Equipa equipa){
    int ind;

    /*obtem a hash do nome da equipa*/
    ind = hash(nome_equipa(equipa),M_equipas);

    /*insere o elemento na entrada hash da hashtable*/
    equipas->ht[ind] = push_equipa(equipas->ht[ind],equipa);

    /*verifica se a equipa e a primera inserida*/
    if(equipas->primeiro == NULL)
        equipas->primeiro = equipas->ht[ind];

    else
        equipas->ultimo->prox_inserido = equipas->ht[ind];

    /*define a equipa como a ultima inserida*/
    equipas->ht[ind]->prox_inserido = NULL;
    equipas->ultimo = equipas->ht[ind];
}

/*
  push_equipa: (No_Equipa, Equipa) -> ()
  Insere um equipa na entrada da hashtable selecionada
*/
No_Equipa push_equipa(No_Equipa atual, Equipa equipa){
    No_Equipa novo;

    novo = can_fail_malloc(sizeof(struct no_equipa));
    novo->equipa = equipa;
    novo->prox = atual;

    /*coloca a equipa na cabeca da entrada da hashtable*/
    return novo;
}

/*
  procura_equipa: (Equipas, char*) -> Equipa
  Procura uma equipa
*/
Equipa procura_equipa(Equipas equipas, char* nome){
    int ind;

    ind = hash(nome,M_equipas);
    
    return procura_ht_equipas(equipas->ht[ind],nome);
}

/*
  procura_ht_equipas: (No_Equipa, char*) -> Equipa
  Procura uma equipa na entrada da hashtable correspondente
*/
Equipa procura_ht_equipas(No_Equipa no, char* nome){
    while(no != NULL){
        if(!strcmp(nome,nome_equipa(no->equipa)))
            return no->equipa;

        no = no->prox;
    }

    /*retorna NULL caso o jogo nao exista*/
    return NULL;
}

/*
  destroi_equipas: (Equipas) -> ()
  Liberta o espaco usado pelas estruturas de Equipas assim como destroi todas 
  as equipas existentes
*/
void destroi_equipas(Equipas equipas){
    No_Equipa temp;

    /*percorre a linked list*/
    while(equipas->primeiro != NULL){
        temp = equipas->primeiro->prox_inserido;
        free_equipa(equipas->primeiro->equipa);      
        free(equipas->primeiro);
        equipas->primeiro = temp;
    }

    /*liberta a estrutura*/
    free(equipas);
}

/*
  print_vencedores: (Equipas, unsigned int) -> ()
  Imprime as equipas que teem mais vitorias por ordem lexicografica
*/
void print_vencedores(Equipas equipas, unsigned int NL){
    No_Equipa no;
    char **vencedores, **tmp;
    int i, max = 0; 
    int size_max = 1;
    int size = 0;

    /*caso a lista seja vazia nao imprime nada*/
    if(equipas->primeiro == NULL)
        return;
   
    no = equipas->primeiro;
    vencedores = can_fail_malloc(size_max*sizeof(char *));

    /*percorre a linked list*/
    while(no != NULL){
        /*caso um novo maximo seja encontrado reescreve o vetor*/
        if(vitorias_equipa(no->equipa) > max){
            max = vitorias_equipa(no->equipa);
            size = 0;
            vencedores[size++] = nome_equipa(no->equipa);
        }
                
        else if(vitorias_equipa(no->equipa) == max){
            vencedores[size++] = nome_equipa(no->equipa);
        } 
        
        /*se o nr de equipas encontradas for maior que o tamanho
          do vetor aloca mais espaco*/
        if(size >= size_max){
            size_max++;
            tmp = can_fail_realloc(vencedores,size_max*sizeof(char *));

            /*can_fail_realloc fail check*/
            if(tmp == NULL)
                return;
            
            else
                vencedores = tmp;
        }

        no = no->prox_inserido;
    }
    
    /*ordena o vetor de strings*/
    qsort(vencedores,size,sizeof(char*),compara_strings);

    printf("%u Melhores %d\n",NL,max);

    for(i=0; i<size; i++)
        printf("%u * %s\n",NL,vencedores[i]);

    /*liberta a estrutura temporaria*/
    free(vencedores);
}
