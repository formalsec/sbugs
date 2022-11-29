#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "core.h"


/*
Separa o input recebido em diferentes parametros
Input: String que e dada pelo utilizador, matriz onde sera colocado o input sem ':'
Output: Comando a executar
 */
char SeparaInput(char input[MAX_INPUT], char input_separado[MAX_PARAM][MAX_STR]){
    int a=0, i=0;
    char *token = NULL, comando = '\0';

    token = strtok(input, "\n");
    token = strtok(token, " ");
    comando = *token;

    token = strtok(NULL, ":");

    for(a=0; a<MAX_PARAM; a++)
        strcpy(input_separado[a],"\0");

    while (token != NULL){
        strcpy(input_separado[i],token);
        token = strtok(NULL, ":");
        i++;
    }

    return comando;
}


/* Cria um elemento do tipo Lista e inicializa os seus valores */
Lista *CriaLista(){
    Lista *nova_lista = (Lista *) can_fail_malloc(sizeof(Lista));
    nova_lista -> cabeca = NULL;
    nova_lista -> ultimo = NULL;

    return nova_lista;
}


/* Cria uma nova hash table e inicializa-a */
Node **CriaHashTable(){
    int i;
    Node **Hash_Table;

    Hash_Table = (Node**) can_fail_malloc(CAPACIDADE_HASH * sizeof(Node*));

    for(i=0; i < CAPACIDADE_HASH; i++)
        Hash_Table[i] = NULL;

    return Hash_Table;
}


/* Inicializa uma estrutura do tipo Node e associa-lhe informacao */
Node *CriaNode(void *tipo_node){
    Node *node = (Node *) can_fail_malloc(sizeof(Node));

    node -> drt = NULL;
    node -> esq = NULL;
    node -> tipo_node = tipo_node;

    return node;
}


/* Recebe uma string e retorna o valor ascii correspondente da hash */
int GeraHash(char *str){
    int i, valor_ascii=0;

    for(i=0; str[i] != '\0'; i++)
        valor_ascii += str[i];
        
    return valor_ascii % CAPACIDADE_HASH;
}


/* Insere um novo elemento numa hash table */
void InsereNaHashTable(Node **hash_table, Node *node, int tipo){
    int i=0;
    Node *atual;
    
    i = GeraHash(tipo == 0 ? ((Jogo *)node->tipo_node)->nome : ((Equipa *)node->tipo_node)->nome);

    if (hash_table[i]){
        atual = hash_table[i];

        while(atual -> drt)
            atual = atual->drt;
        
        node -> esq = atual;
        atual -> drt = node;
    }

    else
        hash_table[i] = node;
}


/* Procura um elemento na hash table */
void *ProcuraNaHashTable(char *nome, Node **hash_table, int tipo){
    int v = GeraHash(nome);
    Node *node = hash_table[v];

    while(node){
        if(!strcmp((tipo == 0 ? ((Jogo *)node->tipo_node)->nome : ((Equipa *)node->tipo_node)->nome), nome)){
            
            return node->tipo_node;
        }
        node = node->drt;
    }
    return NULL; 
}


/* Insere um elemento numa lista */
void InsereNaLista(Lista *lista, void *el, int tipo){
    if(!(lista -> cabeca)){
        lista -> cabeca = el;
        lista -> ultimo = el;
    }

    else{
        if(tipo == 0){
            ((Jogo*)el) -> esq = lista -> ultimo;
            ((Jogo*)lista -> ultimo) -> drt = el;
        }
        
        else if(tipo == 1){
            ((Equipa*)el) -> esq = lista -> ultimo;
            ((Equipa*)lista -> ultimo) -> drt = el;
        }
        
        lista -> ultimo = el;
    }
}


/* Destroi um jogo */
void *DestroiJogo(void *jogo){
    void *drt = ((Jogo *)jogo) -> drt;
    free(((Jogo *)jogo) -> nome);
    free(((Jogo *)jogo) -> equipaX);
    free(((Jogo *)jogo) -> equipaY);
    free(jogo);
    return drt;
}


/* Destroi uma equipa */
void *DestroiEquipa(void *equipa){
    void *drt = ((Equipa *)equipa) -> drt;
    free(((Equipa *)equipa) -> nome);
    free(equipa);
    return drt;
}


/* Elimina um elemento do tipo jogo (sel=0) ou equipa (sel=1) da hash table e da lista */
void LimpaElemento(char *nome, Node **hash_table, Lista *lista, void *(*LimpaEl)(void *), int sel){
    int v = 0;
    Node *node = NULL;
    v = GeraHash(nome);

    if(hash_table[v]){
        node = hash_table[v];

        while (strcmp((sel == 0 ? ((Jogo*)node -> tipo_node) -> nome : ((Equipa*)node -> tipo_node) -> nome), nome)){
            node = node -> drt;
            if (!node) 
                return;
        }

        if(sel == 0){
            if(((Jogo*)node -> tipo_node) -> drt && ((Jogo*)node -> tipo_node) -> esq){
                ((Jogo*)node -> tipo_node) -> esq -> drt = ((Jogo*)node -> tipo_node) -> drt;
                ((Jogo*)node -> tipo_node) -> drt -> esq = ((Jogo*)node -> tipo_node) -> esq;
            }
            else if(((Jogo*)node -> tipo_node) -> esq){
                ((Jogo*)node -> tipo_node) -> esq -> drt = NULL;
                lista -> ultimo = ((Jogo*)node -> tipo_node) -> esq;
            }
            else if(((Jogo*)node -> tipo_node) -> drt){
                ((Jogo*)node -> tipo_node) -> drt -> esq = NULL;
                lista -> cabeca = ((Jogo*)node -> tipo_node) -> drt;
            }
            else{
                lista -> cabeca = NULL;
                lista -> ultimo = NULL;
            }
        }

        else if(sel == 1){
            if(((Equipa*)node -> tipo_node) -> drt && ((Equipa*)node -> tipo_node) -> esq){
                ((Equipa*)node -> tipo_node) -> esq -> drt = ((Equipa*)node -> tipo_node) -> drt;
                ((Equipa*)node -> tipo_node) -> drt -> esq = ((Equipa*)node -> tipo_node) -> esq;
            }
            else if(((Equipa*)node -> tipo_node) -> esq){
                ((Equipa*)node -> tipo_node) -> esq -> drt = NULL;
                lista -> ultimo = ((Equipa*)node -> tipo_node) -> esq;
            }
            else if(((Equipa*)node -> tipo_node) -> drt){
                ((Equipa*)node -> tipo_node) -> drt -> esq = NULL;
                lista -> cabeca = ((Equipa*)node -> tipo_node) -> drt;
            }
            else{
                lista -> cabeca = NULL;
                lista -> ultimo = NULL;
            }
        }

        LimpaEl(node -> tipo_node);
        
        if(node -> esq && node -> drt){
            node -> esq -> drt = node -> drt;
            node -> drt -> esq = node -> esq;
        }
        else if(node -> esq)
            node -> esq -> drt = NULL;
        
        else if(node -> drt){
            node -> drt -> esq = NULL;
            hash_table[v] = node -> drt;
        }
        else
            hash_table[v] = NULL;

        free(node);
        
    }
}


/* Destroi os dados alocados durante a execucao do programa */
void LimpezaGeral(Node **hash_table, Lista *lista, void *(*LimpaEl)(void *)) {
    int i;
    void *lista_aux = lista -> cabeca;
    Node *node_aux = NULL, *del_aux = NULL;

    while(lista_aux)
        lista_aux = LimpaEl(lista_aux);
    
    free(lista);

    for(i=0; i < CAPACIDADE_HASH; i++){

        if(hash_table[i]){
            node_aux = hash_table[i];

            while (node_aux){
                del_aux = node_aux;
                node_aux = node_aux -> drt;
                free(del_aux);
            }
        }
    }
    free(hash_table);
}