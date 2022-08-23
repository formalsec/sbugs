#include "funcoestabelas.h"

/*Funcao que inicia uma Hash Table de jogos alocando a sua memoria e com a capacidade definida por 
TAMANHOHT retorna o ponteiro para memoria alocada */
HashTableJogos * IniciarHTJogos(){
    HashTableJogos * HTJ;
    HTJ = malloc(sizeof(HashTableJogos));
    HTJ->capacidade = TAMANHOHT;
    /* Aloca memoria a todas as cabecas das listas das colisoes */
    HTJ->listasjog = calloc(TAMANHOHT,sizeof(HashNoJogos*));

    return HTJ;
}

/*Funcao que inicia uma Hash Table de equipas alocando a sua memoria e com a capacidade definida 
por TAMANHOHT retorna o ponteiro para memoria alocada */
HashTableEquipas * IniciarHTEquipas(){
    HashTableEquipas * HTE;
    HTE = malloc(sizeof(HashTableEquipas));
    HTE->capacidade = TAMANHOHT;
    /* Aloca memoria a todas as cabecas das listas das colisoes */
    HTE->listasequi = calloc(HTE->capacidade,sizeof(HashNoEquipas*));

    return HTE;
}

/*Funcao que adiciona um ponteiro para o no da lista das equipas a lista de colisoes da respetiva 
hash na Hash Table das equipas,recebe um ponteiro para a Hash Table das equipas uma hash e 
o ponteiro a adicionar */
void AdicionarHTEquipas(HashTableEquipas * HTE,int hash,NoSimplesEquipas * novo_no){
      
    HashNoEquipas * aux = malloc(sizeof(HashNoEquipas));
    aux->dadosequipa = novo_no;
    aux->proxequipah = HTE->listasequi[hash];
    HTE->listasequi[hash] = aux;
    
}

/*Funcao que adiciona um ponteiro para um no da lista dos jogos na lista de colisoes da respetiva
 hash na Hash Table dos jogos,recebe um ponteiro para a Hash Table dos jogos uma hash e o 
 ponteiro para o no a adicionar */
void AdicionarHTJogos(HashTableJogos * HTJ,int hash,NoDuploJogos * novo_no){
    
    HashNoJogos * aux = malloc(sizeof(HashNoJogos));
    aux->dadosjogo = novo_no;
    aux->proxjogoh = HTJ->listasjog[hash];
    HTJ->listasjog[hash] = aux;
}

/*Funcao auxiliar ao comando "x" que liberta a memoria das Hash Tables dos jogos e das equipas*/
void ApagarHTs(HashTableEquipas * HTE,HashTableJogos * HTJ){
    HashNoJogos * auxjog; 
    HashNoEquipas * auxequi;
    int lime = HTE->capacidade,limj = HTJ->capacidade,counte,countj;
    

    for(counte = 0;counte < lime;counte++){
        while(HTE->listasequi[counte]){
            auxequi = HTE->listasequi[counte];
            HTE ->listasequi[counte] = HTE->listasequi[counte]->proxequipah;
            free(auxequi);
        }
    }
    
    free(HTE->listasequi);
    free(HTE);

    for(countj = 0;countj < limj;countj++){
        while(HTJ->listasjog[countj]){
            auxjog = HTJ->listasjog[countj];
            HTJ->listasjog[countj] = HTJ->listasjog[countj]->proxjogoh;
            free(auxjog);
        }
    }
    free(HTJ->listasjog);
    free(HTJ);

}

/*Funcao que corresponde ao comando "x" que liberta a memoria das Hash Tables e das listas 
dos jogos e das equipas recebe ponteiros para as Hash Tables e listas das equipas e dos jogos */
void ApagaTudo(HashTableEquipas * HTE,HashTableJogos * HTJ,NoSimplesEquipas * equipas,ListaDuplaJogo * jogos){
    ApagarJogos(jogos);
    ApagarEquipas(equipas);
    ApagarHTs(HTE,HTJ);

}
