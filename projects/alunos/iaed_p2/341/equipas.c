#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "equipas.h"


/*Funcao auxiliar que recebendo a Hash Table das equipas, uma hash(int) e o nome de uma equipa
 procura se a equipa dada ja foi adicionada retorna um ponteiro para o No de Hash Table desta,
 caso contrario retorna NULL*/
HashNoEquipas * EquipaJaAdicionada(HashTableEquipas * HTE,int hash, char * nome){
    
    HashNoEquipas * aux = HTE->listasequi[hash];
    
    for(;aux; aux = aux->proxequipah){
        if(!strcmp(aux->dadosequipa->equipa,nome)){
            return aux;
        }
    }
    return NULL;
}


/*Funcao que corresponde ao comando "A",le do stdin o nome de uma equipa e recebe 
um ponteiro para o "conta-comandos",um ponteiro para a Hash Table das equipas e um ponteiro
 para a cabeca(no inicial) da lista das equipas, o ponteiro para a nova cabeca da lista das 
 equipas(equipa nova adicionada)(baseada na pilha dos labs)*/
NoSimplesEquipas * AdicionarEquipa(int * contacomandos,HashTableEquipas * HTE,NoSimplesEquipas * listaequipas){
    
    char bufferequipa[MAXNOMEEQUIPA+1];
    int hashbuffer;
    NoSimplesEquipas * nova;
    
    getchar(); /*Retira o espaco apos o comando*/
    scanf(LEITURA_NOME_EQUIPA,bufferequipa);
    
    hashbuffer = Hash(bufferequipa,HTE->capacidade);
    
    if(EquipaJaAdicionada(HTE,hashbuffer,bufferequipa)!=NULL){
        printf("%d Equipa existente.\n",*contacomandos);
        (*contacomandos)++;
        return listaequipas;
    }else{
        /*Inicializacao do novo no da lista simplesmente ligada das equipas*/
        nova = can_fail_malloc(sizeof(NoSimplesEquipas));
        nova->equipa = can_fail_malloc((sizeof(char))*(strlen(bufferequipa)+1));
        strcpy(nova->equipa,bufferequipa);
        nova->proxequipa = listaequipas;
        nova->vitorias = 0;
        listaequipas = nova;
        AdicionarHTEquipas(HTE,hashbuffer,nova);
        (*contacomandos)++;
        return listaequipas;
    }

}


/*Funcao que corresponde ao comando "P",le do stdin o nome de uma equipa e recebe  um ponteiro
 para o "conta-comandos",um ponteiro para a Hash Table das equipas e um ponteiro para a cabeca da 
 lista das equipas e escreve no stdout as informacoes relativas a equipa cujo nome foi lido
  do stdin*/
void ProcuraEquipa(int * contacomandos,HashTableEquipas * HTE){
    
    int hashbuffer;
    char buffer[MAXNOMEEQUIPA+1];
    HashNoEquipas * aux;

    getchar();/*Retirar o espaco apos o comando*/
    scanf(LEITURA_NOME_EQUIPA,buffer);
    
    hashbuffer = Hash(buffer,HTE->capacidade);
    /*Encontra a equipa dentro da Hash Table ou NULL quando nao esta na Hash Table*/
    aux = EquipaJaAdicionada(HTE,hashbuffer,buffer);
    
    if(aux){
        printf("%d %s %d\n",*contacomandos,buffer,aux->dadosequipa->vitorias);
        (*contacomandos)++;
        return;
    }
    printf("%d Equipa inexistente.\n",*contacomandos);
    
    (*contacomandos)++;
}


/*Funcao de comparacao de strings necessaria para utilizar a funcao qsort built-in de stdlib.h 
(Faz cast dos ponteiros de void* para char*) retirada de "man qsort"*/
int ComparaStrings(const void *str1, const void *str2){
    return strcmp(* (char * const *) str1, * (char * const *) str2);
}


/*Funcao auxiliar que recebe um ponteiro para a cabeca da lista de equipas e retorna um array 
de 2 inteiros: o numero maximo de vitorias e a quantas equipas tem o numero maximo de vitorias*/
int * EncontraMaiorNVitorias(NoSimplesEquipas * equipas){
    int vitoriasmax = 0,maiorescount = 0;
    int * maxecountmax = can_fail_malloc(2*sizeof(int));
    NoSimplesEquipas * aux;

    for(aux = equipas;aux;aux = aux->proxequipa){
        
        if(aux->vitorias > vitoriasmax){ /*da reset ao contador de equipas com max 
                                            e altera para o novo maximo */
            vitoriasmax = aux->vitorias;
            maiorescount = 1;
        }else if (aux->vitorias == vitoriasmax)
        {
            maiorescount++;
        }        
    }
    *maxecountmax = vitoriasmax;
    *(maxecountmax+1) = maiorescount;

    return maxecountmax;
}


/*Funcao que corresponde ao comando "g",recebe  um ponteiro para o "conta-comandos", 
e um ponteiro para a cabeca da lista das equipas,e escreve no stdout 
uma lista ordenada lexicograficamente das equipas com o numero maior de vitorias*/
void ListaMaisVitorias(int * contacomandos,NoSimplesEquipas * equipas){
    int * auxmax = EncontraMaiorNVitorias(equipas);
    int vitoriasmax = auxmax[0],maiorescount = auxmax[1],count;
    char ** maiores = can_fail_malloc(maiorescount * sizeof(char*));
    NoSimplesEquipas * aux;

    if(maiorescount == 0){
        (*contacomandos)++;
        free(auxmax); 
        free(maiores);
        return;
    }
    for(aux = equipas,count = 0;count < maiorescount;aux = aux->proxequipa){
        if(aux->vitorias == vitoriasmax){
            maiores[count] = aux->equipa;
            count++;
        }
    }
    /* Ordena com quicksort as strings na auxiliar maiores*/
    qsort(maiores,maiorescount,sizeof(char*),ComparaStrings);
    printf("%d Melhores %d\n",*contacomandos,vitoriasmax);
    for (count = 0;count < maiorescount;count++){
        printf("%d * %s\n",*contacomandos,maiores[count]);
    }
    
    (*contacomandos)++;
    free(auxmax); 
    free(maiores);
    
}


/*Funcao auxiliar que recebe a cabeca da lista das equipas e liberta toda a memoria ocupada 
pela lista e informacoes das equipas*/
void ApagarEquipas(NoSimplesEquipas * equipas){
    NoSimplesEquipas * aux;
    while (equipas){
        aux = equipas;
        equipas = equipas->proxequipa;
        free(aux->equipa);
        free(aux);
    }
}
