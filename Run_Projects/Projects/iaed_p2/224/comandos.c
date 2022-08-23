#include "comandos.h"
#include "core.h"


/*
Comando a: Adiciona um novo jogo ao sistema
Input: 'a nome:equipa1:equipa2:score1:score2'
Output: Ponteiro para o jogo criado 
*/
Jogo *CriaJogo(char input_separado[MAX_PARAM][MAX_STR]){
    char *nome = input_separado[0], *equipaX = input_separado[1], *equipaY = input_separado[2];
    int scoreX = atoi(input_separado[3]), scoreY = atoi(input_separado[4]);
    Jogo *jogo;

    jogo = (Jogo *) malloc(sizeof(Jogo));

    jogo -> nome = (char *) malloc((strlen(nome)+1)*sizeof(char));
    strcpy(jogo -> nome, nome);

    jogo -> equipaX = (char *) malloc((strlen(equipaX)+1)*sizeof(char));
    strcpy(jogo -> equipaX, equipaX);

    jogo -> equipaY = (char *) malloc((strlen(equipaY)+1)*sizeof(char));
    strcpy(jogo -> equipaY, equipaY);

    jogo -> scoreX = scoreX;
    jogo -> scoreY = scoreY;

    jogo -> drt = NULL;
    jogo -> esq = NULL;

    return jogo;
}


/* Adiciona o jogo criado no camando 'a' a uma lista e a uma hash table */
void AdicionaNovoJogo(int NL, Jogo *jogo, Node **hash_table_jogos, Node **hash_table_equipas, Lista *lista_jogos){
    char *nome = jogo -> nome, *nome_equipaX = jogo -> equipaX, *nome_equipaY = jogo -> equipaY;
    Node *node_jogo;
    Equipa *equipaX = NULL, *equipaY = NULL;

    int existeJogo = !!ProcuraNaHashTable(nome, hash_table_jogos, 0);
    equipaX = ProcuraNaHashTable(nome_equipaX, hash_table_equipas, 1);
    equipaY = ProcuraNaHashTable(nome_equipaY, hash_table_equipas, 1);

    if(!existeJogo && !!equipaX && !!equipaY){

        if(jogo -> scoreX > jogo -> scoreY)
            (equipaX -> jogos_ganhos)++;

        else if(jogo -> scoreX < jogo -> scoreY)
            (equipaY -> jogos_ganhos)++;

        node_jogo = CriaNode(jogo);
        InsereNaHashTable(hash_table_jogos, node_jogo, 0);
        InsereNaLista(lista_jogos, jogo, 0);
    }

    else{
        DestroiJogo(jogo);
        existeJogo ? printf("%d Jogo existente.\n", NL) : (!equipaX || !equipaY) ? printf("%d Equipa inexistente.\n", NL) : 0;
    }

}


/*
Comando l: Lista todos os jogos introduzidos pela ordem em que foram introduzidos
Input: 'l'
Output: Uma linha por jogo no formato 'NL nome-jogo nome-equipa1 nome-equipa2 score1 score 2' 
*/
void ListaJogosIntroduzidos(int NL, Lista *lista_jogos){
    Jogo *jogo = lista_jogos -> cabeca;

    while(jogo){
        printf("%d %s %s %s %d %d\n", NL, jogo->nome, jogo->equipaX, jogo->equipaY, jogo->scoreX, jogo->scoreY);
        jogo = jogo->drt;
    }

}


/*
Comando p: Procura um jogo com o nome dado
Input: 'p nome'
Output: 'NL nome-jogo nome-equipa1 nome-equipa2 score1 score 2' ou erro, se aplicavel
*/
void ProcuraJogo(int NL, char input_separado[MAX_PARAM][MAX_STR], Node **hash_table_jogos){
    char *nome = input_separado[0];
    Jogo *jogo;

    jogo = ProcuraNaHashTable(nome, hash_table_jogos, 0);

    if(jogo)
        printf("%d %s %s %s %d %d\n", NL, jogo->nome, jogo->equipaX, jogo->equipaY, jogo->scoreX, jogo->scoreY);

    else
        printf("%d Jogo inexistente.\n", NL);

}


/*
Comando r: Apaga um jogo dado um nome
Input: 'r nome'
Output: Nada, excepto erro
*/
void ApagaJogo(int NL, char input_separado[MAX_PARAM][MAX_STR], Node **hash_table_jogos, Node **hash_table_equipas, Lista *lista_jogos){
    char *nome = input_separado[0];
    Jogo *jogo;
    Equipa *equipaX, *equipaY;

    jogo = ProcuraNaHashTable(nome, hash_table_jogos, 0);

    if(!jogo)
        printf("%d Jogo inexistente.\n", NL);

    else{

        equipaX = ProcuraNaHashTable(jogo -> equipaX, hash_table_equipas, 1);
        equipaY = ProcuraNaHashTable(jogo -> equipaY, hash_table_equipas, 1);

        if(jogo->scoreX > jogo->scoreY)
            (equipaX -> jogos_ganhos)--;

        else if(jogo->scoreY > jogo->scoreX)
            (equipaY -> jogos_ganhos)--;

        LimpaElemento(nome, hash_table_jogos, lista_jogos, DestroiJogo, 1);
    }

}


/*
Comando s: Altera o score de um jogo dado o nome
Input: 's nome:score1:score2'
Output: Nada, excepto erro
*/
void AlteraScore(int NL, char input_separado[MAX_PARAM][MAX_STR], Node **hash_table_jogos, Node **hash_table_equipas){
    char *nome = input_separado[0];
    int scoreX_novo = atoi(input_separado[1]), scoreY_novo = atoi(input_separado[2]);
    
    Jogo *jogo;
    Equipa *equipaX, *equipaY;

    jogo = ProcuraNaHashTable(nome, hash_table_jogos, 0);

    if(!jogo)
        printf("%d Jogo inexistente.\n", NL);

    else{

        equipaX = ProcuraNaHashTable(jogo -> equipaX, hash_table_equipas, 1);
        equipaY = ProcuraNaHashTable(jogo -> equipaY, hash_table_equipas, 1);

        if(scoreX_novo > scoreY_novo && jogo->scoreX < jogo->scoreY){
            (equipaX -> jogos_ganhos)++;
            (equipaY -> jogos_ganhos)--;
        }

        else if(scoreX_novo > scoreY_novo && jogo->scoreX == jogo->scoreY)
            (equipaX -> jogos_ganhos)++;

        else if(scoreY_novo > scoreX_novo && jogo->scoreY < jogo->scoreX){
            (equipaY -> jogos_ganhos)++;
            (equipaX -> jogos_ganhos)--;
        }

        else if(scoreY_novo > scoreX_novo && jogo->scoreY == jogo->scoreX)
            (equipaY -> jogos_ganhos)++;

        else if(scoreX_novo == scoreY_novo && jogo->scoreX > jogo->scoreY) 
            (equipaX -> jogos_ganhos)--;

        else if(scoreX_novo == scoreY_novo && jogo->scoreY > jogo->scoreX) 
            (equipaY -> jogos_ganhos)--;

        jogo -> scoreX = scoreX_novo;
        jogo -> scoreY = scoreY_novo;       

    }

}


/*
Comando A: Adiciona uma nova equipa ao sistema 
Input: 'A nome'
Output: Ponteiro para a equipa criada 
*/
Equipa *CriaEquipa(char input_separado[MAX_PARAM][MAX_STR]){
    char *nome = input_separado[0];
    Equipa *equipa;

    equipa = (Equipa *) malloc(sizeof(Equipa));

    equipa -> nome = (char *) malloc((strlen(nome)+1)*sizeof(char));
    strcpy(equipa -> nome, nome);

    equipa -> jogos_ganhos = 0;

    equipa -> drt = NULL;
    equipa -> esq = NULL;

    return equipa;
}


/* Adiciona a equipa criada no camando 'A' a uma lista e a uma hash table */
void AdicionaNovaEquipa(int NL, Equipa *equipa, Node **hash_table_equipas, Lista *lista_equipas){
    Node *node_equipa;
    char *nome = equipa -> nome;

    int existeEquipa = !!ProcuraNaHashTable(nome, hash_table_equipas, 1);

    if(!existeEquipa){
        node_equipa = CriaNode(equipa);
        InsereNaHashTable(hash_table_equipas, node_equipa, 1);
        InsereNaLista(lista_equipas, equipa, 1);
    }
    
    else{
        DestroiEquipa(equipa);
        existeEquipa ? printf("%d Equipa existente.\n", NL) : 0;
    }

}


/*
Comando P: Procura uma equipa dado um nome
Input: 'P nome'
Output: 'NL nome numero-de-jogos-ganhos' ou erro
*/
void ProcuraEquipa(int NL, char input_separado[MAX_PARAM][MAX_STR], Node **hash_table_equipas){
    char *nome = input_separado[0];

    Equipa *equipa = ProcuraNaHashTable(nome, hash_table_equipas, 1);

    if(!!equipa)
        printf("%d %s %d\n", NL, nome, equipa -> jogos_ganhos);

    else
        printf("%d Equipa inexistente.\n", NL);

}


/* Funcao para trocar dados de duas equipas (a e b) */
void Trocar(Equipa *a, Equipa *b){
    char *temp_nome = a -> nome;
    int temp_jogos_ganhos = a -> jogos_ganhos;

    a -> nome = b -> nome;
    a -> jogos_ganhos = b -> jogos_ganhos;

    b -> nome = temp_nome;
    b -> jogos_ganhos = temp_jogos_ganhos;
}


/* Algoritmo de ordenacao para o comando g */
void BubbleSort(Equipa *inicial){
    int trocado; 
    Equipa *equipaA; 
    Equipa *equipaB = NULL; 
  
    if (inicial == NULL) 
        return; 
  
    do{
        trocado = 0; 
        equipaA = inicial; 
  
        while (equipaA -> drt != equipaB){
            if (strcmp(equipaA -> nome , equipaA -> drt -> nome) > 0){
                Trocar(equipaA, equipaA -> drt);
                trocado = 1; 
            }
            equipaA = equipaA -> drt;
        }
        equipaB = equipaA; 
    } 
    while (trocado); 
} 


/*
Comando g: Encontra as equipas que ganharam mais jogos e lista por ordem alfabetica (do nome da equipa)
Input: 'g'
Output: Lista ordenada das equipas ou erro
*/
void OrdenaEquipas(int NL, Lista *lista){
    int mais_jogos_ganhos=0;

    Equipa *equipa_aux = lista -> cabeca, *copia = NULL, *aux_apagar = NULL;

    Lista *lista_aux_equipas = CriaLista();

    /*Calcula numero maximo de jogos que uma equipa ganhou*/
    while(equipa_aux){
        if(equipa_aux -> jogos_ganhos > mais_jogos_ganhos)
            mais_jogos_ganhos = equipa_aux -> jogos_ganhos;

        equipa_aux = equipa_aux -> drt;
    }
    equipa_aux = lista -> cabeca;


    /*Insere numa lista a parte as equipas que ganharam mais jogos*/
    while(equipa_aux){
        if(equipa_aux -> jogos_ganhos == mais_jogos_ganhos){
            copia = malloc(sizeof(Equipa));

            copia -> nome = (char *) malloc((strlen(equipa_aux -> nome)+1)*sizeof(char));
            strcpy(copia -> nome, equipa_aux -> nome);

            copia -> jogos_ganhos = equipa_aux -> jogos_ganhos;

            copia -> drt = NULL;
            copia -> esq = NULL;

            InsereNaLista(lista_aux_equipas, copia, 1);
        }
        equipa_aux = equipa_aux -> drt;
    }

    if(lista_aux_equipas -> cabeca){

        BubbleSort(lista_aux_equipas -> cabeca);

        printf("%d Melhores %d\n", NL, mais_jogos_ganhos);

        equipa_aux = lista_aux_equipas -> cabeca;

        while(equipa_aux){
            printf("%d * %s\n", NL, equipa_aux->nome);
            aux_apagar = equipa_aux;
            equipa_aux = equipa_aux -> drt;
            free(aux_apagar -> nome);
            free(aux_apagar);
        }

    }
    free(lista_aux_equipas);
}